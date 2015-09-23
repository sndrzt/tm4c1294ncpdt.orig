/*------------------------------------------------------------------------------
RTC2!C
              

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../time/timedate.h"
#include "../display/lines.h"
#include 		"inc/hw_sysctl.h"
#include 		"inc/hw_gpio.h"
#include 		"inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "rtc.h"
#include "rtc2.h"



#ifdef NATIVE_RTC

void    InitGPIO_RTC() {
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R1;

  DelayGPIO();

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR)   |= 0x000E;
  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DIR)   &= 0xFFFE;

  HWREG(GPIO_PORTB_AHB_BASE + GPIO_O_DEN)   |= 0x000F;
}

#endif
