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
// Source code for the ADC Functions
//
//============================================================================

//============================================================================
// Includes
//============================================================================
//#include "device.h"
#include "adc.h"
#include "iodefine.h"

//============================================================================
// Functions
//============================================================================

/******************************************************************************
** Function:    INTADCA0ERR
** Description: Error interrupt is generated when the PWM-Diagnostic of the HPLEDs
**              is out of expected range. It creates a call back in the tasks source
** Parameter:   None
** Return:      None
******************************************************************************/
//#pragma interrupt INTADCA0ERR_interrupt( enable=false , channel=47 , callt=false , fpu=false )
//void INTADCA0ERR_interrupt( void )
//{
//  ADCA0_error_cb(ADCA0.ULER.UINT32);  //Upper/Lower Error information is given to the error call back function
//  ADCA0.ECR.UINT32 = 0x08;            //Set the ULEC bit of the ErrorClearRegister of ADCA1 to clear the upper/lower limit error flag
//  RFADCA0ERR = 0;             //Reset InterreuptRequestFlag
//}


/******************************************************************************
** Function:    AP_init
** Description: This function initializes the analogue ports for ADC/PWSA usage
** Parameter:   None
** Return:      None
******************************************************************************/
void AP_init(void)
{
    APM0 |= 1<<0;  //AP0_0 SpecialFunct(ADCA0 Ch0)
    APM0 |= 1<<1;  //AP0_1 SpecialFunct(PWGADIN Ch1)
    APM0 |= 1<<2;  //AP0_2 SpecialFunct(PWGADIN Ch2)
    APM0 |= 1<<3;  //AP0_3 SpecialFunct(PWGADIN Ch3)
    APM0 |= 1<<4;  //AP0_4 SpecialFunct(PWGADIN Ch4)
    APM0 |= 1<<5;  //AP0_5 SpecialFunct(PWGADIN Ch5)
    APM0 |= 1<<6;  //AP0_6 SpecialFunct(PWGADIN Ch6)
    APM0 |= 1<<7;  //AP0_7 SpecialFunct(PWGADIN Ch7)
    
    APM1 |= 1<<0;  //AP1_0 SpecialFunct(ADCA1)
}


/******************************************************************************
** Function:    AP_deinit
** Description: This function deinitializes the analogue ports for ADC/PWSA usage
** Parameter:   None
** Return:      None
******************************************************************************/
void AP_deinit(void)
{
//  APM0 &= ~(1<<1);  //AP0_1 SpecialFunct(PWGADIN Ch1)
//  APM0 &= ~(1<<2);  //AP0_2 SpecialFunct(PWGADIN Ch2)
//  APM0 &= ~(1<<0);  //AP0_0 SpecialFunct(ADCA0)
//	APM0 &= ~(1<<6);  //AP0_6 SpecialFunct(ADCA0)	

	APM1 &= ~(1<<0);  //AP1_0 SpecialFunct(ADCA1)
}

/******************************************************************************
** Function:    ADC_interrupt_enable
** Description: This function enables the error table interrupt for ADCA0/ADCA1
** Parameter :  None
** Return:      None
******************************************************************************/
void ADC_interrupt_enable(void)
{
  /* Error TableInterrupt for ADCA0 enabled */
  TBADCA0ERR = 1;  //Error table interrupt is enabled by setting the table bit to 1
  MKADCA0ERR = 0;  //Error interrupt is unmasked by setting the mask bit to 0

  /* Error TableInterrupt for ADCA1 enabled */
  TBADCA1ERR = 1;  //Error table interrupt is enabled by setting the table bit to 1
  MKADCA1ERR = 0;  //Error interrupt is unmasked by setting the mask bit to 0
}

/******************************************************************************
** Function:    ADC_interrupt_disable
** Description: This function disables the error table interrupt for ADCA0/ADCA1
** Parameter:   None
** Return:      None
******************************************************************************/
void ADC_interrupt_disable(void)
{
  /* Error TableInterrupt for ADCA0 disabled */
  MKADCA0ERR = 1;  //Error table interrupt is disabled by setting the table bit to 0
  TBADCA0ERR = 0;  //Error interrupt is masked by setting the mask bit to 1

  /* Error TableInterrupt for ADCA1 disabled */
  MKADCA1ERR = 0;  //Error table interrupt is disabled by setting the table bit to 0
  TBADCA1ERR = 1;  //Error interrupt is masked by setting the mask bit to 1

}

/******************************************************************************
** Function:    ADC_init
** Description: This function initializes ADC-Function for the Potentiometers
**              and PWM diagnostic function
** Parameter:   None
** Return:      None
******************************************************************************/
void ADC_channel_init(void)
{
  /* ADCA0 */
  ADCA0.VCR00.UINT32 = 0x01;    //Virtual Channel 0 of ADCA0 is linked to physical channel ADCA0I1 
  								//Upper/lower limit not checked / No scan group interrupt is output
								
  ADCA0.VCR01.UINT32 = 0x02;    //Virtual Channel 1 of ADCA0 is linked to physical channel ADCA0I2 
  								//Upper/lower limit not checked / No scan group interrupt is output 
  
  ADCA0.ADCR.UINT32 = 0x02;     //Asynchronous suspend / 12bit mode / PWDDR and ADCA0DR00 are set to right align
                        		//The self-diagnostic voltage circuit is turned off
            
  ADCA0.SMPCR.UINT32 = 0x12;    //Set sampling time to 12*1/16MHz = 1.125us
  ADCA0.SFTCR.UINT32 = 0x08;    //Upper/Lower limit error enabled / DR/DIR registers are not cleared when read
  ADCA0.SGCR1.UINT32 = 0x10;    //ScanGroup interrupt is output when scan ends
  
  /* ScanGroup start/end registers */
  ADCA0.SGVCSP1.UINT32 = 0x00;  //ScanGroup starts at virtual channel 0
  ADCA0.SGVCEP1.UINT32 = 0x01;  //ScanGroup ends at virtual channel 1

  /* ADCA1 */
  /* Select the PPLLCLK2 as ADCA1 Clock  */  
  //protected_write(PROTCMD1,CKSC_IADCAS_CTL,0x03);
  PROTCMD1=0xa5;
  CKSC_IADCAS_CTL=0x03;
  CKSC_IADCAS_CTL=~0x03;
  CKSC_IADCAS_CTL=0x03;
  while(CKSC_IADCAS_CTL!=0x03);
  
  ADCA1.VCR00.UINT32 = 0x00;     //Virtual Channel 0 of ADCA1 is linked to physical channel ADCA1I0
                         		 //Upper/lower limit not checked / No scan group interrupt is output
  
  ADCA1.ADCR.UINT32 = 0x02;      //Asynchronous suspend / 12bit mode / ADCA1DR00 is set to right align
                         		 //The self-diagnostic voltage circuit is turned off
            
  ADCA1.SMPCR.UINT32 = 0x18;     //Set sampling time to 18*1/40MHz = 0.45us
  ADCA1.SFTCR.UINT32 = 0x08;     //Upper/Lower limit error enabled / DR/DIR registers are not cleared when read
  ADCA1.SGCR2.UINT32 = 0x10;     //ScanGroup interrupt is output when scan ends
  
  /* ScanGroup start/end registers */
  ADCA1.SGVCSP2.UINT32 = 0x00;   //ScanGroup starts at virtual channel 0
  ADCA1.SGVCEP2.UINT32 = 0x00;   //ScanGroup ends at virtual channel 0
}

/******************************************************************************
** Function:    ADC_read
** Description: This function reads the actual status of the Potentiometers
** Parameter:   ADC Channel 0
**                          1
** Return:      ADCA0DIR00
**              ADCA1DIR00
******************************************************************************/
unsigned short ADC_read(unsigned short adc_channel)
{
  switch(adc_channel)
  {
    /* Channel 0 */
    case 0:
      ADCA0.SGSTCR1.UINT32 = 1;       //Conversion start trigger
      while(RFADCA0I0 == 0);          //Wait for conversion end interrupt request
      RFADCA0I0 = 0;                  //Reset interrupt request 
    return ADCA0.DIR00&0xffff; //Return the lower 16bit which are the read value
	
	/* Channel 1 */
	case 1:
      ADCA0.SGSTCR1.UINT32 = 1;       //Conversion start trigger
//      while(RFADCA0I0 == 0);          //Wait for conversion end interrupt request
//      RFADCA0I0 = 0;                  //Reset interrupt request 
    return ADCA0.DIR01&0xffff; //Return the lower 16bit which are the read value
    
    /* Channel 2 */
    case 2:
      ADCA1.SGSTCR2.UINT32 = 1;       //Conversion start trigger
      while(RFADCA1I1 == 0);  		  //Wait for conversion end interrupt request
      RFADCA1I1 = 0;          		  //Reset interrupt request 
    return ADCA1.DIR00&0xffff; //Return the lower 16bit which are the read value
    
    default:
    return 0;
  }
}

/******************************************************************************
** Function:    ADC_LPS_init
** Description: This function initializes ADC for LPS usage
** Parameter:   None
** Return:      None
******************************************************************************/
void ADC_LPS_init()
{
  ADCA0.VCR00.UINT32 = 0x40;  //Virtual Channel 0 of ADCA0 is linked to physical channel ADCA0I4 (LPS) / Limits checked in ADCA0ULLMTBR0
  ADCA0.ECR.UINT32 = 0x0c;    //Set the ULEC bit of the ErrorClearRegister of ADCA1 to clear the upper/lower limit error flag
  
  ADCA0.SGCR1.UINT32 = 0x00;  //Hardware trigger disabled / No interrupt is output when scan ends
  ADCA0.SFTCR.UINT32 = 0x08;  //Upper/Lower limit interrupt enabled
  ADCA0.SMPCR.UINT32 = 0x12;  //ADC Sampling Control Setting
  ADCA0.ADCR.UINT32 = 0x00;   //ADC Common Operation Control Setting
  ADCA0.SGTSEL1.UINT32 = 0x10;//LPS as hardware trigger selected
  ADCA0.SGCR1.UINT32 = 0x11;  //INT_SGx is output when the scan for SGx ends / Hardware trigger enabled
}

/******************************************************************************
** Function:    ADCA0_limit
** Description: This function sets the upper/lower limit of the ADCA0 channel
** Parameter:   Limit Channel
                Upper Limit
                Lower Limit
** Return:      None
******************************************************************************/
void ADCA0_limit(unsigned int limit_channel, unsigned int upper, unsigned int lower)
{
  /* Select the upper and lower limit values */
  switch(limit_channel)
  {
    /* Limit registers: [31:20] Upper limit, [15:4] Lower limit */
    case 0:
      ADCA0.ULLMTBR0.UINT32 = 0xfff00000;     //First set default value
      ADCA0.ULLMTBR0.UINT32 &=  (upper<<20);  //Set upper limit
      ADCA0.ULLMTBR0.UINT32 |=  (lower<<4);   //Set lower limit
    break;
    
    case 1:
      ADCA0.ULLMTBR1.UINT32 = 0xfff00000;     //First set default value
      ADCA0.ULLMTBR1.UINT32 &=  (upper<<20);  //Set upper limit
      ADCA0.ULLMTBR1.UINT32 |=  (lower<<4);   //Set lower limit
    break;
    
    case 2:
      ADCA0.ULLMTBR2.UINT32 = 0xfff00000;     //First set default value
      ADCA0.ULLMTBR2.UINT32 &=  (upper<<20);  //Set upper limit
      ADCA0.ULLMTBR2.UINT32 |=  (lower<<4);   //Set lower limit
    break;
    default:
    break;
  }
  ADCA0.ECR.UINT32 = 0x08;                    //Set the ULEC bit of the ErrorClearRegister of ADCA1 to clear the upper/lower limit error flag
}
