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
// Source code for the PulseWidth Functions
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "pwm.h"
#include "iodefine.h"

//============================================================================
// Functions
//============================================================================
/******************************************************************************
** Function:    PWMD_init
** Description: Initializes the PWM for the chosen LED
** Parameter:   LED1
**              LED2
**              HPLED1
**              HPLED2
** Return:      None
******************************************************************************/
void PWMD_init (LEDs LED)
{
    /* Configure PWGA output port */
    switch(LED)
    {
        /* Configure P10_3 as 3rd alternative output PWGA3 */
        case LED1:
            PMC10 |= 1<<3;
            PM10 &= ~(1<<3);
            PFCE10 |= 1<<3;
            PFC10 &= ~(1<<3);
            PFCAE10&= ~(1<<3);
            /* PWM Channel 3 */
            PWGA3.CTL = 0x00;     //Use PWMCLK0
            PWGA3.CSDR = 0x00;    //Delay = 0
            PWGA3.CRDR = 0x00;    //Duty cycle = 0. This will be updated via duty function 
        break;
        
        /* Configure P8_5 as 3rd alternative output PWGA37 */
        case LED2:
            PMC8 |= 1<<5;
            PM8 &= ~(1<<5);
            PFCE8 |= 1<<5;
            PFC8 &= ~(1<<5);
            /* PWM Channel 37 */
            PWGA37.CTL = 0x00;     //Use PWMCLK0
            PWGA37.CSDR = 0x00;    //Delay = 0
            PWGA37.CRDR = 0x00;    //Duty cycle = 0. This will be updated via duty function 
        break;
        
        /* Configure P10_1 as 3rd alternative output PWGA1 */
        case HPLED1:
            PMC10 |= 1<<1;
            PM10 &= ~(1<<1);
            PFCE10 |= 1<<1;
            PFC10 &= ~(1<<1);
            PFCAE10&= ~(1<<1);
            /* PWM Channel 1 */
            PWGA1.CTL = 0x00;     //Use PWMCLK0
            PWGA1.CSDR = 0x00;    //Delay = 0
            PWGA1.CTDR = 73;      //Set the trigger for the PWSA to ~30ms ((4096/PWMClock)*PWGA1CTDR)
            PWGA1.CRDR = 0x00;    //Duty cycle = 0. This will be updated via duty function 
        break;
        
        /* Configure P10_2 as 3rd alternative output PWGA2 */
        case HPLED2:
            PMC10 |= 1 << 2;
            PM10 &= ~(1 << 2);
            PFCE10 |= 1 << 2;
            PFC10 &= ~(1 << 2);
            PFCAE10&= ~(1 << 2);
            /* PWM Channel 2 */
            PWGA2.CTL = 0x00;      //Use PWMCLK0
            PWGA2.CSDR = 0x000;    //Delay = 0
            PWGA2.CTDR = 73;       //Set the trigger for the PWSA to ~30ms ((4096/PWMClock)*PWGA2CTDR)
            PWGA2.CRDR = 0x000;    //Duty cycle = 0. This will be updated via duty function 
        break;
        
        default:
        break;
    }
}

/******************************************************************************
** Function:    PWMD_deinit
** Description: Deinitializes the PWM for the chosen LED
** Parameter:   LED1
**              LED2
**              HPLED1
**              HPLED2
** Return:      None
******************************************************************************/
void PWMD_deinit(LEDs LED)
{
    switch(LED)
    {
        /* Reset PWGA3 Port Pins, P10_3 */
        case LED1:
            PMC10 &= ~(1<<3);
            PM10 |= (1<<3);
            SLPWGA0 &= ~(1<<3);    //Stop Channel 3
        break;
        
        /* Reset PWGA37 Port Pins, P8_5 */
        case LED2:
            PMC8 &= ~(1<<5);
            PM8 |= (1<<5);
            SLPWGA1 &= ~(1<<5);    //Stop Channel 37
        break;
        
        /* Reset PWGA1 Port Pins, P10_1 */
        case HPLED1:
            PMC10 &= ~(1<<1);
            PM10 |= (1<<1);
            SLPWGA0 &= ~(1<<1);    //Stop Channel 1
        
        break;
        
        /* Reset PWGA2 Port Pins, P10_2 */
        case HPLED2:
            PMC10 &= ~(1<<2);
            PM10 |= (1<<2);
            SLPWGA0 &= ~(1<<2);    //Stop Channel 2
        break;
    }
}

/******************************************************************************
** Function:    PWMD_start
** Description: Starts the PWM output for the chosen LED
** Parameter:   LED1
**              LED2
**              HPLED1
**              HPLED2
** Return:      None
******************************************************************************/
void PWMD_start(LEDs LED)
{
    switch(LED)
    {
        case LED1:
            SLPWGA0 |= 1<<3;    //Start Channel 3
        break;
        
        case LED2:
            SLPWGA1 |= 1<<5;    //Start Channel 37
        break;
        
        case HPLED1:
            SLPWGA0 |= 1<<1;    //Start Channel 1
        break;
        
        case HPLED2:
            SLPWGA0 |= 1<<2;    //Start Channel 2
        break;
        
        default:
        break;
    }
}

/******************************************************************************
** Function:    PWMD_stop
** Description: Stops the PWM output for the chosen LED
** Parameter:   LED1
**              LED2
**              HPLED1
**              HPLED2
** Return:      None
******************************************************************************/
void PWMD_stop(LEDs LED)
{
    switch(LED)
    {
        case LED1:
            SLPWGA0 &= ~(1<<3);    //Stop Channel 3
		    P10 &= ~(1<<3);
        break;
        
        case LED2:
            SLPWGA1 &= ~(1<<5);    //Stop Channel 37
		    P8 &= ~(1<<5);
        break;
        
        case HPLED1:
            SLPWGA0 &= ~(1<<1);    //Stop Channel 1
		    P10 &= ~(1<<2);
        break;
        
        case HPLED2:
            SLPWGA0 &= ~(1<<2);    //Stop Channel 2
		    P10 &= ~(1<<2);
        break;
        
        default:
        break;
    }
}

/******************************************************************************
** Function:    PWMDClock_init
** Description: Stops the PWM output for the chosen LED
** Parameter:   LED1
**              LED2
**              HPLED1
**              HPLED2
** Return:      None
******************************************************************************/
void PWMDClock_init(void)
{
    PWGA0.CTL = 0x00;    //Select PWMCLK0
    PWBA0.BRS0 = 0x04;   //Set ClockCycle of PWMCLK0 = PCLK/(2*(PWBA0BRS0[10:0])) = 5MHz
    PWBA0.TS = 0x01;     //Starts Output of PWMCLK0
}
    
/******************************************************************************
** Function:    PWMD_duty
** Description: Updates the duty for the chosen LED
**              (In this example set to the potentiometer status read by the ADC)
** Parameter:   LED1
**              LED2
**              HPLED1
**              HPLED2
**
**              duty = 0-4095
** Return:      None
******************************************************************************/
void PWMD_duty(LEDs LED, unsigned short duty)
{
    switch(LED)
    {
        case LED1:
            PWGA3.CRDR = duty;                //LED1 duty cycle = duty/4096
            PWGA3.RDT = 1;                    //Load the new duty cycle
        break;
        
        case LED2:
            PWGA37.CRDR = duty;               //LED2 duty cycle = duty/4096
            PWGA37.RDT = 1;                   //Load the new duty cycle
        break;
        
        case HPLED1:
            PWGA1.CRDR = duty;                //HPLED1 duty cycle = duty/4096    (Division with 8 for a regulated intensity of the HPLED1)
            PWGA1.RDT = 1;                    //Load the new duty cycle
        break;
        
        case HPLED2:
            PWGA2.CRDR = duty;                //HPLED2 duty cycle = ADC/4096    (Division with 8 for a regulated intensity of the HPLED2)
            PWGA2.RDT = 1;                    //Load the new duty cycle
        break;
        
        default:
        break;
    }
}
    
/******************************************************************************
** Function:    PWSA_init
** Description: Initialize the PWM-Diagnostic function
** Parameter:   None
** Return:      None
******************************************************************************/    
void PWSA_init()
{
    PWSA0.PVCR00_01 = 0x00810000;    //[31:16]PWSA virtual channel 01: [23:22] check ADCA0ULLMTBR1 / [21:16] channel link to PWGADIN1
    PWSA0.PVCR02_03 = 0x000000c2;    //[15:0] PWSA virtual channel 02: [23:22] check ADCA0ULLMTBR2 / [21:16] channel link to PWGADIN2
}

/******************************************************************************
** Function:    PWSA_start
** Description: Starts the PWM-Diagnostic function
** Parameter:   None
** Return:      None
******************************************************************************/    
void PWSA_start()
{
    ADCA0.PWDSGCR.UINT32 = 1;         //PVCR Trigger Enabled
    PWSA0.CTL = 1;             //Start PWSA 
}

/******************************************************************************
** Function:    PWSA_stop
** Description: Stops the PWM-Diagnostic function
** Parameter:   None
** Return:      None
******************************************************************************/    
void PWSA_stop()
{
    ADCA0.PWDSGCR.UINT32 = 0;         //PVCR Trigger disabled
    PWSA0.CTL = 0;             //Stop PWSA 
}

/******************************************************************************
** Function:    PWMJ_duty
** Description: Updates the duty for output channel3 of TAUJ 
** Parameter:   duty
** Return:      None
******************************************************************************/
void PWMJ_duty(unsigned short duty)
{
	if( duty >= TAUJ0.CDR2 )
		duty = TAUJ0.CDR2;
	
	TAUJ0.CDR3 = duty;
	TAUJ0.RDT = 0x0C;                               //Reload all modified values to the all channels
}
