/*------------------------------------------------------------------------------
FLASH2.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include 				"inc/hw_gpio.h"
#include 				"inc/hw_memmap.h"
#include 				"inc/hw_sysctl.h"
#include "../time/delay.h"
#include        "at45.h"
#include        "flash1.h"



#ifdef NATIVE_FLASH


#define HWREG(x) (*((volatile uint32_t *)(x)))



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
