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
// Header file for the PulseWidth source code
//
//============================================================================
#ifndef _PWM_H
#define _PWM_H

//============================================================================
// Defines
//============================================================================

typedef enum 
{
    LED1,
    LED2, 
    HPLED1, 
    HPLED2
}LEDs;

//============================================================================
// Function defines
//============================================================================
void PWMD_init (LEDs LED);
void PWMD_deinit (LEDs LED);
void PWMD_start(LEDs LED);
void PWMD_stop(LEDs LED);
void PWMDClock_init(void);
void PWMD_duty(LEDs LED, unsigned short duty);
void PWSA_init(void);
void PWSA_start(void);
void PWSA_stop(void);
void PWMJ_duty(unsigned short duty);

#endif
