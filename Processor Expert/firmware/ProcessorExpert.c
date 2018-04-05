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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado = ESPERAR;
unsigned int Enviados, n, Ultra, Nivel;
bool primero = FALSE;
bool D1, D2, V1, V2, RI, VE, LU;
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
  			estado = ENVIAR;
  			break;
  		
  		case ENVIAR:
  		
  		if(Nivel<15) V1=0;
  	  	else V1=1;
  		V1=Bits1_GetBit(0);						// Enciendo el led 5 -> Activo la valvula para el ingreso de agua potable
  		if(Nivel<15) V2=0;
  		else V2=1;
  		V2=Bits1_GetBit(1);						// Enciendo el led 4 -> Activo la valvula para el ingreso de agua de lluvia
  		//if(timer==) RI=0;
  		RI=Bits1_GetBit(2);						// Enciendo el led 3 -> Activo el sistema de riego
  		//if(temp==) VE=0;
  		VE=Bits2_GetBit(0);						// Enciendo el led 2 -> Abro las ventanas para el ingreso de aire
  		//if() LU=0;
  		LU=Bits2_GetBit(1);						// Enciendo el led 1 -> Aumento el suministro de lumenes
  		
  	  	// PROTOCOLO [11110011 0D1D2AAAAA 0aaaaaaa 0D3D4BBBBB 0bbbbbbb 0D5D6CCCCC 0ccccccc]
  			
  		// Se aplica el protocolo para 3 canales analogicos y 6 digitales
  	  	medidas[0]=0xF3;		 				//Encabezado de la trama para 3 canales analogicos
  		
  	  	//Sensores analogicos				// La lectura del ADC es [AAAAAaaaaaaa0000]
  		Acele=Acele>>4;						// [AAAAAaaaaaaa0000]>>4 = [xxxxAAAAAaaaaaaa]
  		medidas[1]=(Acele>>7)&(0x1F);  		// [xxxxAAAAAaaaaaaa]>>7 = [xxxAAAAA]&[00011111] = [000AAAAA]
  		medidas[2]=(Acele)&(0x7F);    		// [xxxxAAAAAaaaaaaa]&[01111111] = [0aaaaaaa]
 
  		Temp=Temp>>4;						// [BBBBBbbbbbbb0000]>>4 = [xxxxBBBBBbbbbbbb]
  		medidas[3]=(Temp>>7)&(0x1F);  		// [xxxxBBBBBbbbbbbb]>>7 = [xxxBBBBB]&[00011111]=[000BBBBB]
  		medidas[4]=(Temp)&(0x7F);    		// [xxxxBBBBBbbbbbbb]&[01111111] = [0bbbbbbb]
  		
  		Nivel=Ultra/58;						// Convierto la medida de microsegundos a cm
  		medidas[5]=(Nivel>>7)&(0x1F); 		// [xxxxCCCCCccccccc]>>7 = [xxxCCCCC]&[00011111]=[000CCCCC]
  		medidas[6]=(Nivel)&(0x7F);    		// [xxxxCCCCCccccccc]&[01111111] = [0ccccccc]
  		
  	  	//Sensores digitales
  		if(D1==0) medidas[1]=medidas[1]|0x40;	// Cuando hay luz D1=1 y cuando no D1=0     [00000000]|[01000000]=[0D1000000]
  		if(D2==0) medidas[1]=medidas[1]|0x20;	// Si cambia el estado del sensor digital 2 [00000000]|[00100000]=[00D200000]
  		if(V1==0) medidas[3]=medidas[3]|0x40;	// Si cambia el estado del sensor digital 3 [00000000]|[01000000]=[0D3000000]
  		if(V2==0) medidas[3]=medidas[3]|0x20;	// Si cambia el estado del sensor digital 4 [00000000]|[00100000]=[00D400000]
  		if(RI==0) medidas[5]=medidas[5]|0x40;	// Si cambia el estado del sensor digital 5 [00000000]|[01000000]=[0D5000000]
  		if(VE==0) medidas[5]=medidas[5]|0x20;	// Si cambia el estado del sensor digital 6 [00000000]|[00100000]=[00D600000]
  		
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
