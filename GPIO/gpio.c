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
// Source code for the GPIO Functions
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "gpio.h"
#include "iodefine.h"


//============================================================================
// Defines
//============================================================================
 const struct GPIO_pin GPIO_List[]=
{
  {GPIO_LED1  ,3,&PMC10,&PM10,&PPR10,&PIBC10,&P10},
  {GPIO_LED2  ,5,&PMC8 ,&PM8 ,&PPR8, &PIBC8, &P8},
  {GPIO_APO   ,1,&PMC0 ,&PM0 ,&PPR0, &PIBC0, &P0},
  {GPIO_DPO   ,0,&PMC0 ,&PM0 ,&PPR0, &PIBC0, &P0},
  {GPIO_DIN   ,1,&PMC8 ,&PM8 ,&PPR8, &PIBC8, &P8},
  {GPIO_SELDP0,4,&PMC0 ,&PM0 ,&PPR0, &PIBC0, &P0},
  {GPIO_SELDP1,5,&PMC0 ,&PM0 ,&PPR0, &PIBC0, &P0},
  {GPIO_SELDP2,6,&PMC0 ,&PM0 ,&PPR0, &PIBC0, &P0},
  {GPIO_INTP  ,9,&PMC0 ,&PM0 ,&PPR0, &PIBC0, &P0}
};

//============================================================================
// Functions
//============================================================================

/******************************************************************************
** Function:    GPIO_init_output
** Description: The Pin of the chosen GPIO function is set as GPO
** Parameter:   GPIO function from the GPIO list
** Return:      None
******************************************************************************/
void GPIO_init_output(enum GPIO_Name PortPin)
{
        *(GPIO_List[PortPin].P_Reg) &= ~(1 << GPIO_List[PortPin].PinNumber);
        *(GPIO_List[PortPin].PM_Reg) &= ~(1 << GPIO_List[PortPin].PinNumber);
        *(GPIO_List[PortPin].PMC_Reg) &= ~(1 << GPIO_List[PortPin].PinNumber);
}

/******************************************************************************
** Function:    GPIO_init_input
** Description: The Pin of the chosen GPIO function is set as GPI
** Parameter:   GPIO function from the GPIO list
** Return:      None
******************************************************************************/
void GPIO_init_input(enum GPIO_Name PortPin)
{
        *GPIO_List[PortPin].PM_Reg |= (1 << GPIO_List[PortPin].PinNumber);
        *GPIO_List[PortPin].PIBC_Reg |= (1 << GPIO_List[PortPin].PinNumber);
        *GPIO_List[PortPin].PMC_Reg &= ~(1 << GPIO_List[PortPin].PinNumber); 
}

/******************************************************************************
** Function:    GPIO_ouput_off
** Description: The Pin of the chosen GPO is low
** Parameter:   GPIO function from the GPIO list
** Return:      None
******************************************************************************/
void GPIO_output_off(enum GPIO_Name PortPin)
{
    *GPIO_List[PortPin].P_Reg &= ~(1 << GPIO_List[PortPin].PinNumber);
}

/******************************************************************************
** Function:    GPIO_ouput_on
** Description: The Pin of the chosen GPO is high
** Parameter:   GPIO function from the GPIO list
** Return:      None
******************************************************************************/
void GPIO_output_on(enum GPIO_Name PortPin)
{
    *GPIO_List[PortPin].P_Reg |= (1 << GPIO_List[PortPin].PinNumber);
}

/******************************************************************************
** Function:    GPIO_input_read
** Description: Reads the actual status of the chosen GPI 
** Parameter:   GPIO function from the GPIO list
** Return:      Pin status
******************************************************************************/
unsigned char GPIO_input_read(enum GPIO_Name PortPin)
{
    return ((*GPIO_List[PortPin].PPR_Reg) >> GPIO_List[PortPin].PinNumber);
}

/******************************************************************************
** Function:    GPIO_deinit
** Description: Resets the configuration of chosen GPIO function
** Parameter:   GPIO function from the GPIO list
** Return:      None
******************************************************************************/
void GPIO_deinit(enum GPIO_Name PortPin)
{
        *GPIO_List[PortPin].PM_Reg |= (1 << GPIO_List[PortPin].PinNumber);
        *GPIO_List[PortPin].PIBC_Reg &= ~(1 << GPIO_List[PortPin].PinNumber); 
        *GPIO_List[PortPin].PMC_Reg &= ~(1 << GPIO_List[PortPin].PinNumber); 
}
