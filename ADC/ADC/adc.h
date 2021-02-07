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
// Header file for the ADC source code
//
//============================================================================
#ifndef _ADC_H
#define _ADC_H

//============================================================================
// Defines
//============================================================================
#define Poti1 1
#define Poti2 2
/* Define weak function for call back */
//#pragma weak ADCA0_error_cb

//============================================================================
// Function defines
//============================================================================
//void ADCA0_error_cb(unsigned int ULER);
void AP_init(void);
void APO_init(void);
void APO_deinit(void);
void ADC_channel_init(void);
unsigned short ADC_read(unsigned short adc_channel);
void ADC_LPS_init(void);
void ADCA0_limit(unsigned int limit_channel, unsigned int upper, unsigned int lower);
void ADC_interrupt_enable(void);
void ADC_interrupt_disable(void);

#endif