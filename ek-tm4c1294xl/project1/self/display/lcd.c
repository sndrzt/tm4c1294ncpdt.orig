/*------------------------------------------------------------------------------
LCD!C


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdio.h>

#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "driverlib/interrupt.h"
#include "../main.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "../hardware/beep.h"
#include "../hardware/watchdog.h"
#include "cp1251.h"
#include "lcd.h"

#define LCD_FLAG_COMM    0x00 // �������� �������
#define LCD_FLAG_DATA    0x01 // �������� ������


static uchar const      szName[]        = "*   ���-2.01   *",
                        szTest[]        = "                ";


static uchar const      mpbUserFonts[64] =
{
  0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x16, 0x15, 0x15, 0x0E, 0x04, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


void SetCtrlBit_LCD(unsigned int wSetBit);
void ClearCtrlBit_LCD(unsigned int wSetBit);

void Write_Byte_LCD(unsigned char bflagDC, unsigned char bData);
unsigned char Read_Byte_LCD(unsigned char bflagDC);

void InitGPIO_LCD(void);

unsigned char bCursorPos;


// ��������
//~[ 1 = 440 nsec; 2300000 = 1 sec - for 25MHz]
static void _Delay(unsigned long ulgTime)
{
 while(ulgTime--);
}


/*
//�������� �������� �������
void CursorOnLCD(void)
{
  ReadyLCD();  SetCommLCD(0x0D);
}

//��������� �������� �������
void CursorOffLCD(void)
{
  ReadyLCD();  SetCommLCD(0x0C);
}

//���������� ������ � ��������� �������
void CursorClearPosLCD(void)
{
  ReadyLCD();  SetCommLCD(0x02);
  bCursorPos = 0;
}

//������� ������ ������ �� ���� ������� (���� ����� ������, �� ��������� �� ���������)
void CursorRShiftLCD(void)
{
  ReadyLCD();  SetCommLCD(0x14);
  bCursorPos++;
}

//������� ������ ����� �� ���� ������� (���� ����� ������, �� ��������� �� ���������)
void CursorLShiftLCD(void)
{
  ReadyLCD(); SetCommLCD(0x10);
  bCursorPos--;
}

//��������� ������� � �������� ������� (0..15 - ������� ������, 16..31 - ������ ������)
void CursorSetPosLCD(unsigned char bPos)
{
 if(bPos != bCursorPos)
 {
  CursorOffLCD();
  if(bPos > bCursorPos) while(bCursorPos != bPos) CursorRShiftLCD();
  else  while(bCursorPos != bPos) CursorLShiftLCD();
  CursorOnLCD();
 }
}
*/
// ������ ������� � ���������� ���
void SetCommLCD(unsigned char  bT)
{
 Write_Byte_LCD(LCD_FLAG_COMM, bT);
}

// ������ ������ � ���������� ���
void    SetDataLCD(unsigned char  bT)
{
 Write_Byte_LCD(LCD_FLAG_DATA, bT);
}

//������ ���� ����������
unsigned char GetCommLCD(void)
{
 return( Read_Byte_LCD(LCD_FLAG_COMM) & 0x80 );
}

// �������� ���������� ���
void    ReadyLCD(void)
{
 // ��� ���������� ����������� ���, ��� ���������� = 0
  while ( GetCommLCD() );
}

//����� ����� � �������� ������� ��� � HEX(��� �������)
void  ShowCharLCD_HEX(unsigned char  bPos, unsigned char  bHEX)
{
 ReadyLCD(); SetCommLCD(bPos);
 ReadyLCD(); if(((bHEX >> 4)& 0x0F) > 9) SetDataLCD( (((bHEX >> 4) & 0x0F) - 10) + 0x41);
             else SetDataLCD( ((bHEX >> 4) & 0x0F) + 0x30 );

 ReadyLCD(); SetCommLCD(bPos+1);
 ReadyLCD(); if((bHEX & 0x0F) > 9) SetDataLCD( ((bHEX & 0x0F) - 10) + 0x41);
             else SetDataLCD( (bHEX & 0x0F) + 0x30 );
}

//����� ����� � �������� ������� ��� � BCD(��� �������)
void  ShowCharLCD_BCD(unsigned char  bPos, unsigned char  bBCD)
{
 ReadyLCD(); SetCommLCD(bPos);
 ReadyLCD(); SetDataLCD( ((bBCD >> 4) & 0x0F) + 0x30 );

 ReadyLCD(); SetCommLCD(bPos+1);
 ReadyLCD(); SetDataLCD( (bBCD & 0x0F) + 0x30 );
}

//����� ������� � �������� ������� ���
void  ShowCharLCD(unsigned char  bPos, unsigned char  bSymb)
{
 ReadyLCD();
 SetCommLCD(bPos);

 ReadyLCD();
 SetDataLCD(bSymb);
}

// ������ ������ � ������ ��� ��� ���������
void  ShowMsgLCDnCyr(uchar bT, uchar *szT)
{
 unsigned char   i;

  ReadyLCD();
  SetCommLCD(bT);

  for (i=0; i<16; i++)
  {
    if ( !*szT ) break;
    ReadyLCD();
    SetDataLCD( *szT++ );
  }
}

// ������ ������ � ������ ��� � ����������
void  ShowMsgLCD(uchar  bT, const uchar  *szT)
{
 unsigned char  i;

  ReadyLCD();
  SetCommLCD(bT);

  for (i=0; i<16; i++)
  {
    if ( !*szT ) break;
    ReadyLCD();
    SetDataLCD( mpbCyrillic[ *szT++ ] );
  }
}

void  ShowMsgLCD2(uchar  bT, char  *szT)
{
 unsigned char  i;

  ReadyLCD();
  SetCommLCD(bT);

  for (i=0; i<16; i++)
  {
    if ( !*szT ) break;
    ReadyLCD();
    SetDataLCD( mpbCyrillic[ *szT++ ] );
  }
}


// ����� ������� � ����������� ���������� �����
void    TestOK(void)
{
  ReadyLCD();   SetDataLCD('-');
}


// ����� ��������� � ������ �����
void    TestError(const char  *szT)
{
	IntMasterDisable();

  ShowMsgLCD(0x80, (const uchar *)szAlarm);
  ShowMsgLCD(0xC0, (const uchar *)szT);

  while (1)
  {
    ResetWatchdog();
    DelayMsg(); Beep();
  }
}


void    InitLCD(void)
{
uchar  i;

  InitGPIO_LCD();

  _Delay(50000);    SetCommLCD(0x30);
  _Delay(50000);    SetCommLCD(0x30);
  _Delay(50000);    SetCommLCD(0x30);

  ReadyLCD();   SetCommLCD(0x38);
  ReadyLCD();   SetCommLCD(0x08);
  ReadyLCD();   SetCommLCD(0x01);
  ReadyLCD();   SetCommLCD(0x06);
  ReadyLCD();   SetCommLCD(0x0C);

  ReadyLCD();   SetCommLCD(0x40);       // �������� �������� ������������
  for (i=0; i<64; i++)
  {
    ReadyLCD();
    SetDataLCD( mpbUserFonts[i] );
  }

  ShowMsgLCD(0x80, szName);
  ShowMsgLCD(0xC0, szTest);

  ReadyLCD();   SetCommLCD(0xC4);
}

 uchar bPos =0;
void LCD_Timer0() {
	  if (GetCommLCD() == 0)
	  {
	    if (bPos == 0)
	    {
	      SetCommLCD(0x80);
	      bPos++;
	    }
	    else
	    if (bPos <  17)
	    {
	      SetDataLCD( mpbCyrillic[ szHi[bPos-1] ] );
	      bPos++;
	    }
	    else
	    if (bPos == 17)
	    {
	      SetCommLCD(0xC0);
	      bPos++;
	    }
	    else
	    if (bPos <  34)
	    {
	      SetDataLCD( mpbCyrillic[ szLo[bPos-18] ] );
	      bPos++;
	    }
	    else
	    if (bPos >= 34)
	      bPos = 0;
	  }
}

