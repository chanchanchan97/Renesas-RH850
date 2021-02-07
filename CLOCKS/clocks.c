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
// Source code for the Clock Functions
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "clocks.h"
#include "iodefine.h"

//============================================================================
// Functions
//============================================================================
/******************************************************************************
** Function:    CLOCKS_init
** Description: This function generated the 80MHz Main Clock and enabled the SubOsc
** Parameter:   None
** Return:      None
******************************************************************************/
void CLOCKS_init(void)
{
  /* Prepare 8MHz MainOsz */
  MOSCC=0x05;                            // Set MainOSC gain (8MHz < MOSC frequency =< 16MHz)
  MOSCST=0xFFFF;                         // Set MainOSC stabilization time to max (8,19 ms)
  //protected_write(PROTCMD0,MOSCE,0x01);  // Trigger Enable (protected write)
  PROTCMD0=0xa5;
  MOSCE=0x01;
  MOSCE=~0x01;
  MOSCE=0x01;
  while ((MOSCS&0x04) != 0x4);           // Wait for aktive MainOSC
  
  /* Prepare PLL*/
  PLLC=0x00000a27;                       //16 MHz MainOSC -> 80MHz PLL 
  //protected_write(PROTCMD1,PLLE,0x01);   //enable PLL
  PROTCMD1=0xa5;
  PLLE=0x01;
  PLLE=~0x01;
  PLLE=0x01;
  while((PLLS&0x04) != 0x04);            //Wait for aktive PLL

  /* CPU Clock devider = /1 */
  //protected_write(PROTCMD1,CKSC_CPUCLKD_CTL,0x01);
  PROTCMD1=0xa5;
  CKSC_CPUCLKD_CTL=0x01;
  CKSC_CPUCLKD_CTL=~0x01;
  CKSC_CPUCLKD_CTL=0x01;
  while(CKSC_CPUCLKD_ACT!=0x01);

  /* PLL -> CPU Clock */ 
  //protected_write(PROTCMD1,CKSC_CPUCLKS_CTL,0x03);
  PROTCMD1=0xa5;
  CKSC_CPUCLKS_CTL=0x03;
  CKSC_CPUCLKS_CTL=~0x03;
  CKSC_CPUCLKS_CTL=0x03;
  while(CKSC_CPUCLKS_ACT!=0x03);
  
  /* SubOsc Enable */  
  //protected_write(PROTCMD0,SOSCE,0x01);
  PROTCMD0=0xa5;
  SOSCE=0x01;
  SOSCE=~0x01;
  SOSCE=0x01;
}


