/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC9S08QE128CLK
**     Version     : Driver 01.12
**     Compiler    : CodeWarrior HCS08 C Compiler
**     Date/Time   : 2014-02-18, 15:36, # CodeGen: 0
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
#include "TI1.h"
#include "AS1.h"
#include "AD1.h"
#include "Bit3.h"
#include "Bit2.h"
//#include "Cap1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

unsigned char estado = ESPERAR;
unsigned char CodError;
unsigned int Enviados = 2;		// Esta variable no aporta nada más sino el número de elementos del arreglo a enviar.
unsigned int error;
bool primero = FALSE;
unsigned int periodo;
bool D1;
bool D2;

typedef union{
unsigned char u8[2];
unsigned int u16;
}AMPLITUD;


volatile AMPLITUD iADC;
unsigned char cTrama[3]={0xFF,0x00,0x00};

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
  			CodError = AD1_Measure(TRUE);
  			CodError = AD1_GetValue16(&iADC.u16);
  			D1=Bit1_GetVal();
  			D2=Bit2_GetVal();
  			estado = ENVIAR;
  			break;
  	
  		case ENVIAR:
  			
      cTrama[2]=(iADC.u16>>4)&(0x7F);    	//Se coloca un cero al inicio de la tercera parte de la trama &[01111111]
      cTrama[1]=(iADC.u16>>11)&(0x1F);  	//Se shiftea 7 posiciones para juntar los siguientes 5 bits, se extraen con &[00011111]
      cTrama[0]=0xF1;		 			//Encabezado de la trama para un solo canal analogico

      //Sensores digitales
      if(D1==0){						//Preguntamos si cambio el estado del sensor digital 2
    	cTrama[1] = cTrama[1]|0x40; 	//or con 01000000 para cambiar el bit del sensor digital 2
      }
      if(D2==0){						//Preguntamos si cambio el estado del sensor digital 2
    	cTrama[1] = cTrama[1]|0x20; 	//or con 00100000 para cambiar el bit del sensor digital 2
      }
  			
      CodError = AS1_SendBlock(cTrama,3,&Enviados); //El arreglo con la medición está en iADC.u8 (notar que es un apuntador)
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
