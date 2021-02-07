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
// Source code for the LIN Functions
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "rlin21.h"
#include "iodefine.h"

//============================================================================
// Variables
//============================================================================
volatile unsigned char n;
volatile unsigned char VDCM_ERelay_Cmd, VDCM_ERelay_Cmd_Vld;

//============================================================================
// Functions
//============================================================================
/******************************************************************************
** Function:    INTRLIN1
** Description: This interrupt is generated by the LIN master interface
**              It creates a call back in the Tasks source
** Parameter:   None
** Return:      None
******************************************************************************/
/* This interrupt generates a CallBack in Task.c */
#pragma interrupt INTRLIN1_interrupt( enable=false , channel=51 , callt=false , fpu=false )
void INTRLIN1_interrupt( void )
{
    n++;

    RFRLIN24 = 0;    //Reset RLIN24 InterruptRequestFlag
}

/******************************************************************************
** Function:    PID_calculator
** Description: calculate bit P0 and P1 according to the frame ID
** Parameter:   Frame_ID
** Return:      8 bit protected Identifier
******************************************************************************/
unsigned char PID_calculator(unsigned char Frame_ID)
{
  unsigned char Protected_ID = 0x00;
  unsigned char PID_P0 = 0x00;
  unsigned char PID_P1 = 0x00;
  
  PID_P0 = (Frame_ID ^ (Frame_ID >> 1) ^ (Frame_ID >> 2) ^ (Frame_ID >> 4)) & 0x01;
  PID_P1 = ~((Frame_ID >> 1) ^ (Frame_ID >> 3) ^ (Frame_ID >> 4) ^ (Frame_ID >> 5) & 0x01);
  
  Protected_ID = (PID_P1 << 7) | (PID_P0 << 6) | Frame_ID;
  
  return Protected_ID;
}

/******************************************************************************
** Function:    RLIN21_Test
** Description: Checks the LIN-Macro function by sending and verifying data
** Parameter:   None
** Return:      no error    0
**              error       ErrorStatusRegister
******************************************************************************/
void RLIN21_Test(void)
{
  /* Reset is caused */ 
  do
  {
      RLN2401.L1CUC = 0x00;
  }while(RLN2401.L1MST != 0x00);
  
    /* LIN Mode Register */
  RLN2401.L1MD = 0x00;      //LIN System Clock: fa
  
  /* LIN Break Field Configuration Register */
  RLN2401.L1BFC = 0x00;
  
  /* LIN Wake-up Baud Rate Selector register  */
  RLN240.GLWBR = 0x01;
  
  /* LIN Baud Rate Prescaler1 */
  //Baudrate = PCLK / (((BRP value) + 1)*(number of samples per bit)).
  RLN240.GLBRP0 = 0x81;    //40MHZ/((0x2b5+1)*6)= 9600 baud???

  RLN2401.L1IE = 0x07;     //Tx/Rx interrupt enabled
  MKRLIN21 = 0;            //Interrupt is unmasked by setting the mask bit to 0
  TBRLIN21 = 1;            //Table interrupt is enabled by setting the table bit to 1
  ICRLIN21L = 0x40;
  
  /* LIN Error Detection Enable Register */
  RLN2401.L1EDE = 0x0f;    //Enable all error detection

  RLN2401.L1SC = 0x17;     //Inter-byte(header/response) 7Tbits and interbyte 1Tbit 
  
  /* Reset is cancelled / operating mode is caused */ 
  do{
      RLN2401.L1CUC = 0x03;
  }while(RLN2401.L1MST != 0x03);
  
//  RLN2401.L1IDB = PID_calculator(0x28);    //LIN ID Buffer Register ID and parity settings
  
  /* Fill LIN data buffer register */
//  RLN2401.L1DBR1 = 0x55;    
//  RLN2401.L1DBR2 = 0x55;    
//  RLN2401.L1DBR3 = 0x55;
//  RLN2401.L1DBR4 = 0x55;
//  RLN2401.L1DBR5 = 0x55;
//  RLN2401.L1DBR6 = 0x55;
//  RLN2401.L1DBR7 = 0x55;
//  RLN2401.L1DBR8 = 0x55;
  
//  RLN2401.L1DFC = 0x18;    //Response field length 8byte + checksum, Response direction is Transmission
  
//  RLN2401.L1TRC |= 0x01;   //Set start bit
  
//  while(RLN2401.L1ST!=129)     //Wait while frame transmission not completed 
//  {    
//      if(RLN2401.L1ST==8)      //If error occurred
//      {        
//          return RLN2401.L1EST;//Return error
//      }    
//  }
  
//  return 0;
 
}

/******************************************************************************
** Function:    RLIN21_port_init
** Description: Configures P0_8 as alternative function RLIN21TX 
**              Configures P0_7 as alternative function RLIN21RX 
** Parameter:   None
** Return:      None
******************************************************************************/
void RLIN21_port_init(void)
{
    /* Config RLIN21 Port Pins */ 
    /* Configure P0_8 as 1st alternative output RLIN21TX */
    PMC0  |= 1 << 8;
    PFCE0 &= ~(1 << 8);
    PFC0  &= ~(1 << 8);
    PFCAE0&= ~(1 << 8);
    PM0   &= ~(1 << 8);
    
    /* Configure P0_7 as 1st alternative input RLIN21RX */
    PMC0  |= 1 << 7;
    PFCE0 &= ~(1 << 7);
    PFC0  &= ~(1 << 7);
    PFCAE0&= ~(1 << 7);
    PM0   |= 1 << 7;
}

/******************************************************************************
** Function:    RLIN21_start
** Description: Starts the RLIN21 output
** Parameter:   None
** Return:      None
******************************************************************************/
void RLIN21_start(void)
{
    RLN2401.L1TRC |= 0x01;   //Set start bit
}

/******************************************************************************
** Function:    RLIN21_Master_test
** Description: Set the information on the frame
** Parameter:   None
** Return:      None
******************************************************************************/
void RLIN21_Master_test(unsigned char Protected_ID)
{
    RLN2401.L1IDB = PID_calculator(Protected_ID);    //LIN ID Buffer Register ID and parity settings

    if( Protected_ID == 0x28 )
    {
        RLN2401.L1DFC = 0x38;    //Response field length 8byte + checksum, Response direction is Transmission
	
	/* Fill LIN data buffer register */
    	RLN2401.L1DBR1 = ((VDCM_ERelay_Cmd & 0x07) & ((VDCM_ERelay_Cmd_Vld << 3) & 0x08)) & 0x0f;    
    	RLN2401.L1DBR2 = 0x00;    
    	RLN2401.L1DBR3 = 0x00;
    	RLN2401.L1DBR4 = 0x00;
    	RLN2401.L1DBR5 = 0x00;
    	RLN2401.L1DBR6 = 0x00;
    	RLN2401.L1DBR7 = 0x00;
    	RLN2401.L1DBR8 = 0x00;
    }
    else
    	RLN2401.L1DFC = 0x28;    //Response field length 8byte + checksum, Response direction is Reception
}