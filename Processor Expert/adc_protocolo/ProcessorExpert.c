/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2018-01-26, 12:45, # CodeGen: 0
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
#include "Bit3.h"
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado = ESPERAR;
unsigned int Enviados = 2;		// Esta variable no aporta nada más sino el número de elementos del arreglo a enviar.
bool D1, D2;

typedef union{
unsigned char u8[2];
unsigned int u16;
}AMPLITUD;

volatile AMPLITUD iADC;
unsigned char Trama[3]={0x00,0x00,0x00};

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
  			AD1_Measure(TRUE);
  			AD1_GetValue16(&iADC.u16);
  			D1=Bit1_GetVal();
  			D2=Bit2_GetVal();
  			estado = ENVIAR;
  			break;
  	
  		case ENVIAR:
  			
			//Protocolo [1111000X	 0D1D2AAAAA 	0AAAAAAA] X=Numero de sensores analogicos
			//			cTrama[0]	D1D2cTrama[1]	cTrama[2]
				
			//Sensor analogico
			Trama[2]=(iADC.u16)&0x7F;    //[A16A15A14A13A12A11A10A9 A8A7A6A5A4A3A2A1]&[00000000 01111111]=[0A7A6A5A4A3A2A1A]
			Trama[1]=(iADC.u16>>7)&0x1F; //[0000000A16 A15A14A13A12A11A10A9A8]&[00000000 00011111]=[000A12A11A10A9A8]
		
			//Sensores digitales
			if(D1==0){						//Si cambia el estado del sensor digital 1 (Recordar que se utiliza logica negada)
				Trama[1] = Trama[1]|0x40; 	//[0D1D2AAAAA]|[01000000] para cambiar el bit del sensor digital 1
			}
			if(D2==0){						//Si cambia el estado del sensor digital 2 (Recordar que se utiliza logica negada)
				Trama[1] = Trama[1]|0x20; 	//[0D1D2AAAAA]|[00100000] para cambiar el bit del sensor digital 2
			}
		  
			//Encabezado de la trama para un solo canal analogico 11110001=F1		  
			Trama[0]=0xF1;
	
			AS1_SendBlock(Trama,3,&Enviados);	//Envio el bloque con el protocolo aplicado
			
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
