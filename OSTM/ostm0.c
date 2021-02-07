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
// Source code for the OperatingSystemTimer Functions
// The OSTM0 counts with CPU Clock (80MHz)
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "ostm0.h"
#include "iodefine.h"

//============================================================================
// Functions
//============================================================================

/******************************************************************************
** Function:    OSTM0_init
** Description: Initializes the OSTM0
** Parameter:   None
** Return:      None
******************************************************************************/
void OSTM0_init(void)
{
    OSTM0.EMU = 0x00;    //Counter is stopped when Debugger takes control
    OSTM0.CTL = 0x00;    //IntervalTimer Mode / Interrupt on CounterStart disabled
}

/******************************************************************************
** Function:    OSTM0_start
** Description: Starts the OSTM0 counter
** Parameter:   None
** Return:      None
******************************************************************************/
void OSTM0_start(void)
{
    OSTM0.TS = 0x01;    //StartTrigger
}

/******************************************************************************
** Function:    OSTM0_stop
** Description: Stops the OSTM0 counter
** Parameter:   None
** Return:      None
******************************************************************************/
void OSTM0_stop(void)
{
    OSTM0.TT = 0x01;    //StopTrigger
}

/******************************************************************************
** Function:    OSTM0_compare
** Description: Updates the OSTM0 compare register
** Parameter:   Compare value
** Return:      None
******************************************************************************/
void OSTM0_compare(unsigned int comp)
{
    OSTM0.CMP = comp;
}

/******************************************************************************
** Function:    OSTM0_wait_for_overflow
** Description: Waits until the count register matches the compare register
** Parameter:   Compare value
** Return:      None
******************************************************************************/
void OSTM0_wait_for_overflow()
{
    while(RFOSTM0==0);        //Wait for request flag
    RFOSTM0=0;                //Reset request flag
}