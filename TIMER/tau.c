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
#include "tau.h"
#include "iodefine.h"
#include "gpio.h"
#include "rlin21.h"

//============================================================================
// Variables
//============================================================================
volatile unsigned short j = 0, t = 0;
volatile unsigned short Encoder_CNT;
volatile unsigned char msg[8] = {0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55};
volatile unsigned char CAN0_Status;

//============================================================================
// Functions
//============================================================================

/******************************************************************************
** Function:    INTTAUJ0I0
** Description: This interrupt is generated every 10ms for LIN frame  
**              transmission. It creates a call back in the Tasks source
** Parameter:   None
** Return:      None
******************************************************************************/
#pragma interrupt INTTAUJ0I0_interrupt( enable=false , channel=72 , callt=false , fpu=false )
void INTTAUJ0I0_interrupt( void )
{

	if( t == 0 )
	{
	    RLIN21_Master_test(0x28);
	    RLIN21_start();
	}
	else if( t == 1 )
	{
	    RLIN21_Master_test(0x29);
	    RLIN21_start();
	}
	
	t++;
	if( t > 9 )
	    t = 0;

  	RFTAUJ0I0 = 0;    //Reset TAUJ0I0 InterruptRequestFlag
}

/******************************************************************************
** Function:    INTTAUJ0I1
** Description: This interrupt is generated in a specified cycle for the 
**              alternating LED signal
**              It creates a call back in the Tasks source
** Parameter:   None
** Return:      None
******************************************************************************/
#pragma interrupt INTTAUJ0I1_interrupt( enable=false , channel=73 , callt=false , fpu=false )
void INTTAUJ0I1_interrupt( void )
{
    j++;
    if( j >= 100 )
        j = 0;
		
//    CAN0_Status = Can_C0TrmByTxBuf(0x205, 0x08, msg);

    RFTAUJ0I1 = 0;    //Reset TAUJ0I1 InterruptRequestFlag
}

/******************************************************************************
** Function:    TAUJ0_init
** Description: Initializes the TAUJ0 functionality for LED2, LPS and Interrupt
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_init(void)
{
  /* Initital TAUJ clock setting */ 
  PROTCMD0=0xa5;
  CKSC_ATAUJS_CTL=0x03;
  CKSC_ATAUJS_CTL=~0x03;
  CKSC_ATAUJS_CTL=0x03;
  //protected_write(PROTCMD0,CKSC_ATAUJS_CTL,0x03);   //Select the Low Speed IntOsc(240kHz) as clock source
  while(CKSC_ATAUJS_CTL!=0x03);
  
  //protected_write(PROTCMD0,CKSC_ATAUJD_STPM,0x01); //The clock is not stopped in stand by
  PROTCMD0=0xa5;
  CKSC_ATAUJD_STPM=0x01;
  CKSC_ATAUJD_STPM=~0x01;
  CKSC_ATAUJD_STPM=0x01;
  while(CKSC_ATAUJD_STPM!=0x01);
  
  TAUJ0.TPS = 0xfff4;                             //Set the TAUJ0 prescaler CK0=PCLK/16=15kHz
   
  /* TAUJ channel 0: interval timer for interrupt generation */
  TAUJ0.CMOR0 = 0x0000;                           //Select CK0
  TAUJ0.CMUR0 = 0x00;    
  TAUJ0.CDR0 = 0x0095;                            //Set interval to 10ms (0x0095+1/15kHz)
  
  TBTAUJ0I0 = 1;                                   //Table interrupt is enabled by setting the table bit to 1
  MKTAUJ0I0 = 0;                                   //Interrupt is unmasked by setting the mas bit to 0
  
  /* TAUJ channel 1: interval timer for interrupt generation */
  TAUJ0.CMOR1 = 0x0000;                            //Select CK0
  TAUJ0.CMUR1 = 0x00;    
  TAUJ0.CDR1 = 0x0095;                             //Set interval to 10ms (0x0095+1/15kHz)

  TBTAUJ0I1 = 1;                                   //Table interrupt is enabled by setting the table bit to 1
  MKTAUJ0I1 = 0;                                   //Interrupt is unmasked by setting the mas bit to 0
  
  /* TAUJ channel 2 & 3: PWM for LED2*/
  TAUJ0.CMOR2 = 0x0801;                           //Select CK0 / Channel 2 Master
  TAUJ0.CMOR3 = 0x0409;                           //Select CK0 / Channel 3 Slave
  TAUJ0.CMUR2 = 0x00;
  TAUJ0.CMUR3 = 0x00;
  TAUJ0.CDR2 = 0x0095;                            //The interval is 2s (0x752F+1/15KHz)
  TAUJ0.CDR3 = 0x0000;                            //5% Duty (0x05DC/0x752F+1)
  
  TAUJ0.RDE = 0x0C;                               //Enable simultaneous rewrite
  TAUJ0.RDM = 0x00;                               //The simultaneous rewrite trigger signal is generated when the master channel starts counting
  TAUJ0.TOE  = 0x08;                              //Enables Independent Channel 3 Output Mode
  TAUJ0.TOM |= 0x08;                              //Synchronous channel 3 operation 
  TAUJ0.TOC &= 0x07;                              //Set channel3 output as Operation mode
  TAUJ0.TOL &= 0x07;                              //Set channel3 output as positive logic
  
//  TAUJ0.RDT = 0x0C;                               //Reload all modified values to the all channels
}

/******************************************************************************
** Function:    TAUJ0_LPS_start
** Description: Starts the TAUJ0 output for the LPS scan trigger
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_CH0_start(void)
{
  TAUJ0.TS |= 0x01;  //Channel 0 start trigger
}

/******************************************************************************
** Function:    TAUJ0_INT_start
** Description: Starts the TAUJ0 output for the TAU interrupt
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_CH1_start(void)
{
  TAUJ0.TS |= 0x02;  //Channel 1 start trigger
}

/******************************************************************************
** Function:    TAUJ0_LED_start
** Description: Starts the TAUJ0 output for LED2 used in DeepStop
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_LED_start()
{
  /* Configure P8_5(LED2) to alternative mode TAUJO3 */
  PMC8 |= (1<<5);
  PM8 &= ~(1<<5);
  PFCE8 &= ~(1<<5);
  PFC8 &= ~(1<<5);
  
  TAUJ0.TS = 0x0c; //Channel 2 & 3 start trigger 
}

/******************************************************************************
** Function:    TAUJ0_LPS_stop
** Description: Stops the TAUJ0 output for the LPS scan trigger
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_LPS_stop(void)
{
  TAUJ0.TT = 0x1;    //Channel 0 stop trigger
}

/******************************************************************************
** Function:    TAUJ0_INT_stop
** Description: Stops the TAUJ0 output for the TAU interrupt
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_INT_stop(void)
{
  TAUJ0.TT = 0x2;    //Channel 1 stop trigger
}

/******************************************************************************
** Function:    TAUJ0_LED_stop
** Description: Stops the TAUJ0 output for LED2 used in DeepStop
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUJ0_LED_stop()
{
  /* P8_5(LED2) deinit */
  PMC8 &= ~(1<<5);
  PM8 &= ~(1<<5);
  PFCE8 &= ~(1<<5);
  PFC8 &= ~(1<<5);
  
  TAUJ0.TT = 0xc;    //Channel 2 & 3 stop trigger  
}

/******************************************************************************
** Function:    TAUJ0_duty_update
** Description: Updates the interval time of the TAUJ0 channel: 0-3
** Parameter:   Channel 0-3
**              Duty = (tau_duty+1)/15kHz
** Return:      None
******************************************************************************/
void TAUJ0_duty_update(unsigned short tau_channel, unsigned int tau_duty)
{
  switch(tau_channel)
  {
    case 0:
      TAUJ0.CDR0 = tau_duty;  //Update channel 0
    break;
    
    case 1:
      TAUJ0.CDR1 = tau_duty;  //Update channel 1
    break;
    
    case 2:
      TAUJ0.CDR2 = tau_duty;  //Update channel 2
    break;
    
    case 3:
      TAUJ0.CDR3 = tau_duty;  //Update channel 3
    break;
    
    default:
    break;
  }
}

/******************************************************************************
** Function:    TAUD0_init
** Description: Initializes the TAUD0 functionality for TAUDTTINm input signal width measurement
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUD0_init(void)
{
  PIBC9 &= ~(1<<0);	  	  //Disables the input buffer
  PMC9 |= (1<<0);		  //Specifies alternative mode of the corresponding pin
  PM9 |= (1<<0);		  //Specifies input mode of the corresponding pin
  PFCE9 &= ~(1<<0);		  //Specifies the alternative function of the pin
  PFC9 |= (1<<0);
  
  /* Initital TAUJ clock setting */ 
  PROTCMD1=0xa5;
  CKSC_IPERI1S_CTL=0x01;
  CKSC_IPERI1S_CTL=~0x01;
  CKSC_IPERI1S_CTL=0x01;
  //protected_write(PROTCMD0,CKSC_ATAUJS_CTL,0x03);   //Select the Low Speed IntOsc(240kHz) as clock source
  while(CKSC_IPERI1S_CTL!=0x01);
  
  TAUD0.TPS = 0xfff3;
  
  /* TAUD channel 0: function for input width measurement */
  TAUD0.CMOR0 = 0x024c;
  TAUD0.CMUR0 = 0x03;
  
  TAUD0.TOE = 0x00;
  TAUD0.RDE = 0x00;
  TAUD0.RDS = 0x00;
  TAUD0.RDM = 0x00;
  TAUD0.RDC = 0x00;
  
  DNFATAUD0IENL0 = 1;
}

/******************************************************************************
** Function:    TAUD0_start
** Description: Starts the TAUD0 output for measurement
** Parameter:   None
** Return:      None
******************************************************************************/
void TAUD0_start(void)
{
  TAUD0.TS = 1;  //Channel 0 start trigger
}
