/*------------------------------------------------------------------------------
LCD2!C


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>

#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../main.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "cp1251.h"
#include "lcd.h"



#ifndef NO_DISPLAY

//#define PF2_TO_PD0_WR

//���� ���������� ���
/*
#define LCD_BIT_DIR  0x01 //PF0
#define LCD_BIT_RS   0x02 //PF1
#define LCD_BIT_WR   0x04 //PF2 //PD0
#define LCD_BIT_E    0x08 //PF3
*/

#define LCD_BIT_DIR  0x10 //PF4
#define LCD_BIT_RS   0x01 //PG0
#define LCD_BIT_WR   0x02 //PG1
#define LCD_BIT_E    0x08 //PQ4


static void Wait(void) // TODO
{
}

//��������� ������ ��� ���������� �� ����������� ����� ���
void SetCtrlBit_LCD(unsigned int wSetBit)
{
 if(wSetBit & LCD_BIT_DIR)
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x000040) = 0x0010;
 else
 if(wSetBit & LCD_BIT_RS)
  HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DATA + 0x000004) = 0x0001;
 else
 if(wSetBit & LCD_BIT_WR)
  HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DATA + 0x000008) = 0x0002;
 else
  HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x000040) = 0x0010;

  Wait();
/*
 #ifdef	PF2_TO_PD0_WR
  if(wSetBit & LCD_BIT_WR)
   HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0004) = 0x0001;
  else
   HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = wSetBit;
 #else
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = wSetBit;
 #endif
*/
}

//����� ������ ��� ���������� �� ����������� ����� ���
void ClearCtrlBit_LCD(unsigned int wSetBit)
{
	 if(wSetBit & LCD_BIT_DIR)
	  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + 0x000040) = ~0x0010;
	 else
	 if(wSetBit & LCD_BIT_RS)
	  HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DATA + 0x000004) = ~0x0001;
	 else
	 if(wSetBit & LCD_BIT_WR)
	  HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DATA + 0x000008) = ~0x0002;
	 else
	  HWREG(GPIO_PORTQ_BASE + GPIO_O_DATA + 0x000040) = ~0x0010;

	  Wait();

/*
 #ifdef	PF2_TO_PD0_WR
  if(wSetBit & LCD_BIT_WR)
   HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DATA + 0x0004) = 0x0000;
  else
   HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = ~wSetBit;
 #else
  HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DATA + (wSetBit << 2) ) = ~wSetBit;
 #endif
*/
}

//���� "�" �� �������� ������.
void SetPortK_Out(void)
{
 SetCtrlBit_LCD(LCD_BIT_DIR);//DIR = 1, ����� ������������ ������� �� ��������
 //HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) |= 0x000000FF;//���� ����� "�" �� ��������
 Wait();
 HWREG(GPIO_PORTL_BASE + GPIO_O_DIR) |= 0x000000FF;//
 Wait();
}

//���� "�" �� ����� ������.
void SetPortK_In(void)
{
 ClearCtrlBit_LCD(LCD_BIT_DIR);//DIR = 0, ����� ������������ ������� �� �����
 Wait();
 //HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) &= 0xFFFFFF00;//���� ����� "�" �� �����
 HWREG(GPIO_PORTL_BASE + GPIO_O_DIR) &= 0xFFFFFF00;//
 Wait();
}


//������ ����� � ���
void Write_Byte_LCD(unsigned char bflagDC, unsigned char bData)
{
 SetPortK_Out();

 if(bflagDC) SetCtrlBit_LCD(LCD_BIT_RS);  //RS=1 - ������
 else ClearCtrlBit_LCD(LCD_BIT_RS);       //RS=0 - �������
 Wait();

 ClearCtrlBit_LCD(LCD_BIT_WR);//WR=0 - ������
 Wait();

 //HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x3FC) = bData;//���������� � ���� "K" 8 ��� ������ (���� ������)
 HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + 0x3FC) = bData;//���������� � ���� "K" 8 ��� ������ (���� ������)
 Wait();

 SetCtrlBit_LCD(LCD_BIT_E);    //E=1
 Wait();
 Nop();//���. ������� 230 ����.
 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0
 Wait();
}

//������ ����� �� ���
unsigned char Read_Byte_LCD(unsigned char bflagDC)
{
 SetPortK_In();

 if(bflagDC) SetCtrlBit_LCD(LCD_BIT_RS);  //RS=1 - ������
 else ClearCtrlBit_LCD(LCD_BIT_RS);       //RS=0 - �������
 Wait();

 SetCtrlBit_LCD(LCD_BIT_WR);   //WR=1 - ������
 Wait();
 SetCtrlBit_LCD(LCD_BIT_E);    //E=1
 Nop();//���. ������� 230 ����.
 Wait();

 //bflagDC = HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x3FC);//������ �� ����� "K" 8 ��� ������ (���� ������)
 bflagDC = HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + 0x3FC);//������ �� ����� "K" 8 ��� ������ (���� ������)
 Wait();

 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0
 Wait();
 ClearCtrlBit_LCD(LCD_BIT_WR); //WR=0
 Wait();

 return(bflagDC);
}


//������������� ������ GPIO ��� ������ � �����������
void InitGPIO_LCD(void)
{
/*
 #ifdef	PF2_TO_PD0_WR
  HWREG(SYSCTL_RCGCGPIO) |= 0x0228;//������ ����������� ������ "F" � "K" � "D"
 #else
  HWREG(SYSCTL_RCGCGPIO) |= 0x0220;//������ ����������� ������ "F" � "K"
 #endif
*/

 HWREG(SYSCTL_RCGCGPIO) |= 0xFFFF;//������ ����������� ������

 DelayGPIO();
 Wait();
/*
 HWREG(GPIO_PORTK_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0F;//������ � �������� ��������
*/
 HWREG(GPIO_PORTL_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 Wait();
 HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 Wait();
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 Wait();
 HWREG(GPIO_PORTQ_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 Wait();

 SetPortK_Out();//���� ����� "�" �� �������� ������
 HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DIR) |= 0xFF;//
 Wait();
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0xFE;// !!������������ � ���
 Wait();
 HWREG(GPIO_PORTQ_BASE + GPIO_O_DIR) |= 0x10;//
 Wait();
/*
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0F;//������� ���� ����� "F" �� �������� (����������� ������ �� ��������)


 #ifdef	PF2_TO_PD0_WR
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x01;//PD0
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x01;//PD0
 #endif
*/

 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0 ��������� �� ������
 Wait();
 ClearCtrlBit_LCD(LCD_BIT_WR); //WR=0
 Wait();
}


#endif
