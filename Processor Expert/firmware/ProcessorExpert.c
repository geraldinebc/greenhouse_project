/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-03-02, 18:37, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.12
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Bit1.h"
#include "Bit2.h"
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
#include "PWM1.h"
#include "Cap1.h"
#include "Bits1.h"
#include "Bits2.h"
#include "TmDt1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado = ESPERAR;
unsigned int Enviados, n, Ultra, Nivel, cont, lluvia;
bool D1, D2, V1, V2, RI, VE, LU, alarm, rain, timer=1;
word Acele, Temp;
unsigned char medidas[7]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00};

void main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
   PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */

  for(;;){

  	switch (estado){
  		
  		case ESPERAR:
  			break;
  			
  		case MEDIR:
  			AD1_MeasureChan(TRUE,0);
  			AD1_GetChanValue(0,&Acele);				// Medida del acelerometro				Analogico 1
  			AD1_MeasureChan(TRUE,1);
  			AD1_GetChanValue(1,&Temp);				// Medida del sensor de temperatura 	Analogico 2
  			D1=Bit1_GetVal();						// Medida del sensor de luz				Digital 1
  			D2=Bit2_GetVal();						// Medida del sensor de humedad			Digital 2
  			
  			if (cont>4500){							// Intervalo donde se evalua si esta lloviendo
  				if(lluvia>700) rain=1;				// Si la variable lluvia supera 800 significa que esta lloviendo
  				else rain=0;
  				cont=0;
  				lluvia=0;
  			}
  			else cont=cont+1;
  			
  			estado = ENVIAR;
  			break;
  		
  		case ENVIAR:
  		// Se supervisa el nivel del tanque y la presencia de lluvia para controlar la valvula que se abrira
  		if(Nivel>15){								// Se verifica si el nivel del tanque esta por debajo del nivel optimo
  			if(rain==0){
  				V1=0;								// Si no esta lloviendo se activa la valvula para el paso de agua potable
  				V2=1;
  			}
  			else{
  				V2=0;								// Si esta lloviendo se activa la valvula para el paso de agua de lluvia
  				V1=1;
  			}
  		}
  	  	else{										// Si el nivel del tanque es optimo no se activa ninguna valvula
  	  		V1=1;
  	  		V2=1;
  	  	}
  		Bits1_PutBit(0,V1);							// Enciendo el led 5 -> Activo la valvula para el ingreso de agua potable
  		Bits1_PutBit(1,V2);							// Enciendo el led 4 -> Activo la valvula para el ingreso de agua de lluvia
  		
  		// Se establece una alarma para regar el cultivo
  		// Alarma de riego (Hour, Min, Sec, Sec100)
  		if(alarm==0){
  			RI=1;									// No se riega antes de las 4:10pm
  			TmDt1_SetAlarm(16, 10, 0, 0); 			// Alarma a las 4:10pm para activar riego
  		}
  		if(alarm==1){
  			RI=0;									// Se riega entre 4:10pm y 4:15pm
  			TmDt1_SetAlarm(16, 15, 0, 0); 			// Alarma a las 4:15pm para desactivar el riego
  		}
  		Bits1_PutBit(2,RI);							// Enciendo el led 3 -> Activo el sistema de riego
  		
  		// Se supervisa la temperatura para controlar si se abren las ventanas
  		if(Temp>2000) VE=0;							// Si la temperatura sobrepasa el valor optimo se abre la ventana
  		else VE=1;
  		Bits2_PutBit(0,VE);							// Enciendo el led 2 -> Abro las ventanas para el ingreso de aire
  		
  		// Se supervisa la luz para controlar el encendido de la luces
  		if(timer==0){
  			LU=1;									// Si es de noche no se encienden las luces
  			TmDt1_SetAlarm(6, 0, 0, 0); 			// Alarma a las 6am para indicar que es de dia
  		}
  		if(timer==1){
  			TmDt1_SetAlarm(18, 0, 0, 0); 			// Alarma a las 6pm para indicar que es de dia
  			if(D1==0) LU=0;							// Si es de dia y no hay luz se encienden las luces
  			else LU=1;								// Si es de dia y hay luz no se encienden las luces
  		}
  		Bits2_PutBit(1,LU);							// Enciendo el led 1 -> Aumento la luminosidad
  		
  	  	// PROTOCOLO [11110011 0D1D2AAAAA 0aaaaaaa 0D3D4BBBBB 0bbbbbbb 0D5D6CCCCC 0ccccccc]
  			
  		// Se aplica el protocolo para 3 canales analogicos y 6 digitales (solo se utilizan 3 digitales)
  	  	medidas[0]=0xF3;		 				//Encabezado de la trama para 3 canales analogicos
  		
  	  	//Sensores analogicos				// La lectura del ADC es [AAAAAaaaaaaa0000]
  		Acele=Acele>>4;						// [AAAAAaaaaaaa0000]>>4 = [xxxxAAAAAaaaaaaa]
  		medidas[1]=(Acele>>7)&(0x1F);  		// [xxxxAAAAAaaaaaaa]>>7 = [xxxAAAAA]&[00011111] = [000AAAAA]
  		medidas[2]=(Acele)&(0x7F);    		// [xxxxAAAAAaaaaaaa]&[01111111] = [0aaaaaaa]
  		
  		if(medidas[2]>0xF) lluvia=lluvia+1;	// Si sobrepasa el valor estable del acelerometro se incrementa la variable lluvia
  		
  		Temp=Temp>>4;						// [BBBBBbbbbbbb0000]>>4 = [xxxxBBBBBbbbbbbb]
  		medidas[3]=(Temp>>7)&(0x1F);  		// [xxxxBBBBBbbbbbbb]>>7 = [xxxBBBBB]&[00011111]=[000BBBBB]
  		medidas[4]=(Temp)&(0x7F);    		// [xxxxBBBBBbbbbbbb]&[01111111] = [0bbbbbbb]
  		
  		Nivel=Ultra/58;						// Convierto la medida de microsegundos a cm
  		medidas[5]=(Nivel>>7)&(0x1F); 		// [xxxxCCCCCccccccc]>>7 = [xxxCCCCC]&[00011111]=[000CCCCC]
  		medidas[6]=(Nivel)&(0x7F);    		// [xxxxCCCCCccccccc]&[01111111] = [0ccccccc]
  		
  	  	//Sensores digitales
  		if(D1==0) medidas[1]=medidas[1]|0x40;	// Cuando hay luz D1=1 y cuando no D1=0
  		if(D2==0) medidas[1]=medidas[1]|0x20;	// Cuando esta seco D2=1 y cuando esta humedo D2=0
  		if(rain==0) medidas[3]=medidas[3]|0x40;	// Cuando esta lloviendo D3=1 y cuando no D3=0
  		
  		AS1_SendBlock(medidas,sizeof(medidas),&Enviados); 	// Se envia la trama con el protocolo aplicado
  		estado = ESPERAR;
  		
  		break;
  			
  		default:
  		break;
  	}
  }
  
  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.08]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
