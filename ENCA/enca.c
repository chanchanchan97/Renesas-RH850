//============================================================================
// PROJECT  :  F1L StarterKit
//============================================================================
//                           C O P Y R I G H T
//============================================================================
// Copyright (c) 2013 by Renesas Electronics  GmbH. All rights reserved.
// Arcadiastr.10
// D-40472 Duesseldorf
// Germany
//============================================================================
//
// Warranty Disclaimer :
// Because the Product(s) is licensed free of charge, there is no warranty of
// any kind whatsoever and expressly disclaimed and excluded by Renesas, either
// expressed or implied, including but not limited to those for non-
// infringement of intellectual property, merchantability and/or fitness for
// the particular purpose. Renesas shall not have any obligation to maintain,
// service or provide bug fixes for the supplied Product(s) and/or the
// Application.
//
// Each User is solely responsible for determining the appropriateness of
// using the Product(s) and assumes all risks associated with its exercise
// of rights under this Agreement, including, but not limited to the risks
// and costs of program errors, compliance with applicable laws, damage to
// or loss of data, programs or equipment, and unavailability or
// interruption of operations.
//
// Limitation of Liability :
// In no event shall Renesas be liable to the User for any incidental,
// consequential, indirect, or punitive damage (including but not limited to
// lost profits) regardless of whether such liability is based on breach of
// contract, tort, strict liability, breach of warranties, failure of
// essential purpose or otherwise and even if advised of the possibility of
// such damages. Renesas shall not be liable for any services or products provided
// by third party vendors, developers or consultants identified or referred
// to the User by Renesas in connection with the Product(s) and/or the
// Application.
//
//============================================================================
//
// Source code for the TimerArrayUnit
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "iodefine.h" 
#include "enca.h"

//============================================================================
// Variables
//============================================================================
volatile unsigned short k = 0, m = 0;

//============================================================================
// Functions
//============================================================================
/******************************************************************************
** Function:    ENCATIEC
** Description: Interrupt is generated.
** Parameter:   None
** Return:      None
******************************************************************************/
/*
#pragma interrupt ENCATIEC_interrupt( enable=false , channel=81 , callt=false , fpu=false )
void ENCATIEC_interrupt( void )
{
	k++;
		
	RFENCA0IEC = 0;             //Reset InterreuptRequestFlag
}
*/
/******************************************************************************
** Function:    ENCATIEC
** Description: Interrupt is generated.
** Parameter:   None
** Return:      None
******************************************************************************/
/*
#pragma interrupt ENCATINT0_interrupt( enable=false , channel=81 , callt=false , fpu=false )
void ENCATINT0_interrupt( void )
{
	m++;
		
	RFENCA0I0 = 0;             //Reset InterreuptRequestFlag
}
*/
/******************************************************************************
** Function:    ENCA0_init
** Description: Initializes the ENCA functionality
** Parameter:   None
** Return:      None
******************************************************************************/
void ENCA_init(void)
{
	/* Initital ENCA clock setting */ 
  	PROTCMD1=0xa5;
  	CKSC_IPERI1S_CTL=0x01;
  	CKSC_IPERI1S_CTL=~0x01;
  	CKSC_IPERI1S_CTL=0x01;
 	while(CKSC_IPERI1S_CTL!=0x01);

	ENCA0.CTL = 0x0017;
										
	ENCA0.IOC1 = 0xf0;
	
	ENCA0.CCR0 = 359 * 4;
//	ENCA0.CCR1 = 359 * 4;
	
	ENCA0.CNT = 0x0000;

	PIBC10 &= ~(1<<9);	      //Disables the input buffer
	PMC10 |= (1<<9);		  //Specifies alternative mode of the corresponding pin
  	PM10 |= (1<<9);		  	  //Specifies input mode of the corresponding pin
  	PFCAE10 &= ~(1<<9);	      //Specifies the alternative function of the pin
  	PFCE10 |= (1<<9);
  	PFC10 &= ~(1<<9);
	
  	PIBC10 &= ~(1<<10);	  	  //Disables the input buffer
  	PMC10 |= (1<<10);		  //Specifies alternative mode of the corresponding pin
  	PM10 |= (1<<10);		  //Specifies input mode of the corresponding pin
  	PFCAE10 &= ~(1<<10);	  //Specifies the alternative function of the pin
  	PFCE10 |= (1<<10);
  	PFC10 &= ~(1<<10);
	
	DNFAENCA0ICTL = 0x00;
	DNFAENCA0IEN = 0x0c;
	
}

/******************************************************************************
** Function:    ENCA0_start
** Description: Starts the ENCA0 output
** Parameter:   None
** Return:      None
******************************************************************************/
void ENCA_start(void)
{
	ENCA0.TS = 0x01;
}

/******************************************************************************
** Function:    ENCA_Read
** Description: Returns the value of the ENCA0 count register.
** Parameter:   None
** Return:      ENCA0CNT
******************************************************************************/
unsigned short ENCA_Read(void)
{
    return ENCA0.CNT;
}
	