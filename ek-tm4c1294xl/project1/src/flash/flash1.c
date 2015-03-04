/*------------------------------------------------------------------------------
FLASH1.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include 		"inc/hw_gpio.h"
#include 		"inc/hw_memmap.h"
#include 		"inc/hw_sysctl.h"
#include        "inc/hw_types.h"
#include        "../time/delay.h"
#include        "at45.h"
#include        "flash1.h"



#ifndef NATIVE_FLASH

void Init_SPIhandAT45DB321(void)
{
	 //��������� ���������
	 HWREG(SYSCTL_RCGCGPIO) |= 0x4080;//������ ����������� ������ "H" � "Q"

	 RunClocking();

	 //��� ����� "Q" (SPI)
	 HWREG(GPIO_PORTQ_BASE + GPIO_O_DIR)   |= 0x0005;//���� �� �������� (PQ3 �� �����)
	 HWREG(GPIO_PORTQ_BASE + GPIO_O_DEN)   |= 0x000D;//�������� ������

	 //��� ����� "H" (CE)
	 HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DIR) |= 0x0001;//��� �� ��������
	 HWREG(GPIO_PORTH_AHB_BASE + GPIO_O_DEN) |= 0x0001;//�������� ������
}

#endif
