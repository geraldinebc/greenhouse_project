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
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado = ESPERAR;
unsigned int Enviados = 2;	// Esta aporta el número de elementos del arreglo a enviar
unsigned int error;
bool primero = FALSE;
unsigned int periodo;
bool D1, D2;

typedef union{
unsigned char u8[2];
unsigned int u16;
}AMPLITUD;

volatile AMPLITUD iADC1, iADC2;
word iADC3;
unsigned char cTrama[7]={0xFF,0x00,0x00,0x00,0x00,0x00,0x00};

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
  			AD1_GetChanValue(0,&iADC1.u16);		// Medida del acelerometro				Analogico 1
  			AD1_MeasureChan(TRUE,1);
  			AD1_GetChanValue(1,&iADC2.u16);		// Medida del sensor de temperatura 	Analogico 2
  			if (Cap1_GetStatus()){
  				Cap1_GetCaptureValue(&iADC3); 	// Medida del sensor ultrasonico 		Analogico 3
  			}
  			D1=Bit1_GetVal();					// Medida del sensor de humedad			Digital 1
  			D2=Bit2_GetVal();					// Medida del sensor de luz				Digital 2
  			estado = ENVIAR;
  			break;
  		
  		case ENVIAR:
  			
  	  	// PROTOCOLO [11110011 0D1D2AAAAA 0aaaaaaa 0D3D4BBBBB 0bbbbbbb 0D5D6CCCCC 0ccccccc]
  			
  		// Se aplica el protocolo para 3 canales analogicos y 6 digitales
  	  	cTrama[0]=0xF2;		 				//Encabezado de la trama para 3 canales analogicos
  		
  	  	//Sensores digitales
  		if(D1==0) cTrama[1]=cTrama[1]|0x40;	//Si cambia el estado del sensor digital 1 [00000000]|[01000000]=[0D1000000]
  		if(D2==0) cTrama[1]=cTrama[1]|0x20;	//Si cambia el estado del sensor digital 2 [00000000]|[00100000]=[00D200000]
  	  	
  	  	//Sensores analogicos				// La lectura del ADC es [AAAAAaaaaaaa0000]
  		iADC1.u16=iADC1.u16>>4;				// [AAAAAaaaaaaa0000]>>4 = [xxxxAAAAAaaaaaaa]
  		cTrama[1]=(iADC1.u16>>7)&(0x1F);  	// [xxxxAAAAAaaaaaaa]>>7 = [xxxAAAAA]&[00011111] = [000AAAAA]
  		cTrama[2]=(iADC1.u16)&(0x7F);    	// [xxxxAAAAAaaaaaaa]&[01111111] = [0aaaaaaa]
 
  		iADC2.u16=iADC2.u16>>4;				// [BBBBBbbbbbbb0000]>>4 = [xxxxBBBBBbbbbbbb]
  		cTrama[3]=(iADC2.u16>>7)&(0x1F);  	// [xxxxBBBBBbbbbbbb]>>7 = [xxxBBBBB]&[00011111]=[000BBBBB]
  		cTrama[4]=(iADC2.u16)&(0x7F);    	// [xxxxBBBBBbbbbbbb]&[01111111] = [0bbbbbbb]
  		
  		iADC3.u16=iADC3.u16>>4;				// [CCCCCccccccc0000]>>4 = [xxxxCCCCCccccccc]
  		cTrama[5]=(iADC2.u16>>7)&(0x1F);  	// [xxxxCCCCCccccccc]>>7 = [xxxCCCCC]&[00011111]=[000CCCCC]
  		cTrama[6]=(iADC2.u16)&(0x7F);    	// [xxxxCCCCCccccccc]&[01111111] = [0ccccccc]
  		
  		AS1_SendBlock(cTrama,7,&Enviados); 	// Se envia la trama con el protoclo aplicado
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
