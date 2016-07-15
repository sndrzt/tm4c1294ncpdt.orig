/*------------------------------------------------------------------------------
UART_LOADER!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_types.h"
#include "inc/hw_flash.h"
#include "delay.h"
#include "uart_loader.h"



// bNumPort - ����� ����� (0-A, 1-B, 2-C, 3-D, 4-E, 5-F, 6-G, 7-H)
// bNumPin - ����� ���� (0-Pin0, 1-Pin1, 2-Pin2, 3-Pin3, 4-Pin4, 5-Pin5, 6-Pin6, 7-Pin7)
// bPolarity - ���������� ������� �� ���� ����� (0 - ������� 0, 1 - ������� 1)
// bEnableNegative - ��������� ������� ���������� ��� ������ (0 - ��������� �������)
static void WriteBOOTCFG(uchar bNumPort, uchar bNumPin, uchar bPolarity, uchar bEnableNegative)
{
  ASSERT(bNumPort <= 7);
  ASSERT(bNumPin <= 7);
  ASSERT(bPolarity <= 1);
  ASSERT(bEnableNegative <= 1);

  // ������
  HWREG(FLASH_FMD) = 0xFFFF00FE + (bNumPort << 13) + (bNumPin << 10) + (bPolarity << 9 ) + (bEnableNegative << 8 );

  // ����� BOOTCFG ��� ������
  HWREG(FLASH_FMA) = 0x75100000;

  // ������ ������ � ������ 0xA442
  HWREG(FLASH_FMC) = FLASH_FMC_WRKEY + FLASH_FMC_WRITE + FLASH_FMC_COMT;

  // ������� ��������� ������ (��� 0 ������ ����������)
  while(HWREG(FLASH_FMC) & (FLASH_FMC_WRITE + FLASH_FMC_COMT));
}


void InitUARTLoader(void)
{
  HWREG(SYSCTL_RCGCGPIO) |= SYSCTL_RCGCGPIO_R2; // GPIO Port C Run Mode Clock Gating Control
  DelayGPIO();
  HWREG(GPIO_PORTP_BASE + GPIO_O_DIR) &= 0xFFEF; // GPIO Direction
  HWREG(GPIO_PORTP_BASE + GPIO_O_DEN) |= 0x0010; // GPIO Digital Enable

  if (HWREG(FLASH_BOOTCFG) == 0xFFFFFFFE)
  {
    WriteBOOTCFG(2, 4, 0, 0);
  }
}
