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
// Header file for the GPIO source code
//
//============================================================================

//============================================================================
// Defines
//============================================================================
enum GPIO_Name {     GPIO_LED1=0, 
                                    GPIO_LED2,
                                    GPIO_APO,
                                    GPIO_DPO,
                                    GPIO_DIN,
                                    GPIO_SELDP0,
                                    GPIO_SELDP1,
                                    GPIO_SELDP2,
                                    GPIO_INTP
                                }; 
 
struct GPIO_pin {
    enum GPIO_Name Name;
    unsigned char PinNumber;
    volatile unsigned short * PMC_Reg;
    volatile unsigned short * PM_Reg;
    volatile const unsigned short * PPR_Reg;
    volatile unsigned short * PIBC_Reg;
    volatile unsigned short * P_Reg;
};

//============================================================================
// Function defines
//============================================================================
void GPIO_init_output(enum GPIO_Name PortPin);
void GPIO_init_input(enum GPIO_Name PortPin);
void GPIO_output_off(enum GPIO_Name PortPin);
void GPIO_output_on(enum GPIO_Name PortPin);
unsigned char GPIO_input_read(enum GPIO_Name PortPin);
void GPIO_deinit(enum GPIO_Name PortPin);
