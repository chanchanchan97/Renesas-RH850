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
// Source code for the Button functions
//
//============================================================================


//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "button.h"
#include "iodefine.h"
#include "gpio.h"
#include "pwm.h"

//============================================================================
// Defines
//============================================================================
#define BUTTON_PRESSED_SHORT      10    //10ms for short press
#define BUTTON_PRESSED_LONG     3000    //3s for long press

//============================================================================
// Variables
//============================================================================
volatile unsigned short button_P0_9_pinstatus = 0;
volatile unsigned int button_P0_9_count = 0;
enum button_states button_P0_9_state = button_state_none;
volatile unsigned short i, e;
extern volatile unsigned char VDCM_ERelay_Cmd, VDCM_ERelay_Cmd_Vld;


//============================================================================
// Functions
//============================================================================

/******************************************************************************
** Function:    INTP1_interrupt
** Description: Error interrupt is generated when the PWM-Diagnostic of the HPLEDs
**              is out of expected range. It creates a call back in the tasks source
** Parameter:   None
** Return:      None
******************************************************************************/
#pragma interrupt INTP1_interrupt( enable=false , channel=30 , callt=false , fpu=false )
void INTP1_interrupt( void )
{
	e++;
		
	RFP1 = 0;             //Reset InterreuptRequestFlag
}

/******************************************************************************
** Function:    INTP12_interrupt
** Description: Error interrupt is generated when the PWM-Diagnostic of the HPLEDs
**              is out of expected range. It creates a call back in the tasks source
** Parameter:   None
** Return:      None
******************************************************************************/
#pragma interrupt INTP12_interrupt( enable=false , channel=123 , callt=false , fpu=false )
void INTP12_interrupt( void )
{
//    i = TAUJ0.CDR3;
//    i++;
//    if( i >= 0x4A )
//        i = 0;
		
//    PWMJ_duty(i);

    VDCM_ERelay_Cmd = 0x01;
    VDCM_ERelay_Cmd_Vld = 0x00;
		
    RFP12 = 0;             //Reset InterreuptRequestFlag
}

/*****************************************************************************
** Function:    button_init
** Description: GPI initialization for button Pin
** Parameter:   None
** Return:      None
******************************************************************************/
void Button_init(void)
{
  /* Configures P0_9 as general purpose input  */
  PMC0 &= ~(1<<9);
  PM0 |= (1<<9);
  PIBC0 |= (1<<9);  //Enable input port buffer for P0_9
}

/*****************************************************************************
** Function:    button_handler
** Description: Checks the status and counts the time the button is pressed
** Parameter:   None
** Return:      None
******************************************************************************/

void Button_Handler(void)
{
  unsigned short current_pinstatus;
  enum button_states return_value=button_state_none;
  
  /* Read current pin status from port buffer */
  current_pinstatus=PPR0;
  
  /* Check if button P0_9 is pressed */
  if((current_pinstatus&(1<<9)) == 0 )
  {
    /* Button is pressed */
    if(button_P0_9_count >= BUTTON_PRESSED_LONG)
    {
      return_value = button_state_long;
    }
    
    button_P0_9_count++;
  }
  else
  {
    /* Button is not pressed */
    
    if(button_P0_9_count > BUTTON_PRESSED_SHORT && button_P0_9_count < BUTTON_PRESSED_LONG)
    {
      return_value = button_state_short;
    }
    
    button_P0_9_count=0;
    
  }
  
  /* Save last button event to global variable */
  button_P0_9_state=return_value;
}


/*****************************************************************************
** Function:    button__P0_9_status
** Description: This functions returns the last button event
** Parameter:   None
** Return:      button_states : last button event
******************************************************************************/
enum button_states button_P0_9_status()
{
  enum button_states return_value;
  
  return_value=button_P0_9_state;
  
  button_P0_9_state=button_state_none;
  
  return return_value;
}


/*****************************************************************************
** Function:    button__P0_9_read
** Description: This functions reads the actual button status
** Parameter:   None
** Return:      button status
******************************************************************************/
unsigned char Button_P0_9_read()
{
  return (PPR0&(1<<9))>>9;
}

/*****************************************************************************
** Function:    INTP12_init
** Description: This functions configures the button as interrupt source
** Parameter:   None
** Return:      None
******************************************************************************/
void INTP12_init(void)
{
  /* Setting P0_9 as alternative interrupt input */
  PIBC0 &= ~(1<<9);		  //Disables the input buffer
  PMC0 |= (1<<9);		  //Specifies alternative mode of the corresponding pin
  PM0 |= (1<<9);		  //Specifies input mode of the corresponding pin
  PFCAE0 &= ~(1<<9);	          //Specifies the alternative function of the pin
  PFCE0 &= ~(1<<9);
  PFC0 &= ~(1<<9);
  
  MKP12 = 0;
  TBP12 = 1;

  /* Filter setting */
  FCLA0CTL4_INTPH = 0x01; //Interrupt is generated on falling edge
}

/*****************************************************************************
** Function:    INTP1_init
** Description: This functions configures the button as interrupt source
** Parameter:   None
** Return:      None
******************************************************************************/
void INTP1_init(void)
{
  /* Setting P10_6 as alternative interrupt input */
  PIBC10 &= ~(1<<6);		  //Disables the input buffer
  PMC10 |= (1<<6);		  //Specifies alternative mode of the corresponding pin
  PM10 |= (1<<6);		  //Specifies input mode of the corresponding pin
  PFCAE10 &= ~(1<<6);	          //Specifies the alternative function of the pin
  PFCE10 |= (1<<6);
  PFC10 |= (1<<6);
  PU10 |= (1<<6);
  
  MKP1 = 0;
  TBP1 = 1;

  /* Filter setting */
  FCLA0CTL1_INTPL = 0x01; //Interrupt is generated on falling edge
}
