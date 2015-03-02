/*
 * ������������ ������ � ���
 */

//tm4c1294ncpdt.pdf :
// GPIO - page 757 


#include "../main.h"

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
#define LCD_BIT_E    0x08 //PC4

#define LCD_FLAG_COMM    0x00 // �������� �������
#define LCD_FLAG_DATA    0x01 // �������� ������

//��� ������ MS Sans Serif
unsigned char           const  mpbCyrillic[0x100] =
{
  0x20,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  // 0
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  // 1

  0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2A,0x2B,0x2C,0x2D,0x2E,0x2F,  // 2
  0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3A,0x3B,0x3C,0x3D,0x3E,0x3F,  // 3
  0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4A,0x4B,0x4C,0x4D,0x4E,0x4F,  // 4
  0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x5C,0x5D,0x5E,0x5F,  // 5
  0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,0x6E,0x6F,  // 6
  0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7A,0x7B,0x7C,0x7D,0xC5,0x01,  // 7

  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  // 8
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  // 9
  0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  // A

  0xA2,0xB5,0x20,0x20,0x20,0x20,0x20,0x02,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,  // B
  0x41,0xA0,0x42,0xA1,0xE0,0x45,0xA3,0xA4,0xA5,0xA6,0x4B,0xA7,0x4D,0x48,0x4F,0xA8,  // C
  0x50,0x43,0x54,0xA9,0xAA,0x58,0xE1,0xAB,0xAC,0xE2,0xAD,0xAE,0xC4,0xAF,0xB0,0xB1,  // D
  0x61,0xB2,0xB3,0xB4,0xE3,0x65,0xB6,0xB7,0xB8,0xB9,0xBA,0xBB,0xBC,0xBD,0x6F,0xBE,  // E
  0x70,0x63,0xBF,0x79,0xE4,0x78,0xE5,0xC0,0xC1,0xE6,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7   // F
};
//~ - ������������� ������� "�"

unsigned char bCursorPos;


/*
 void Delay(unsigned int Val)
	{
  	for(; Val != 0; Val--) __NOP();
  	}

Delay(2000000);
 */

// ��������
//~[ 1 = 440 nsec; 2300000 = 1 sec - for 25MHz]
//~[ 1 = 58 nsec; 17131970 = 1 sec - for 120MHz]
void Delay(unsigned long ulgTime)
{
 while(ulgTime--);
}

//���� "�" �� �������� ������.
void SetPortK_Out(void)
{
 SetCtrlBit_LCD(LCD_BIT_DIR);//DIR = 1, ����� ������������ ������� �� ��������
 //HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) |= 0x000000FF;//���� ����� "�" �� ��������
 HWREG(GPIO_PORTL_BASE + GPIO_O_DIR) |= 0x000000FF;//
}

//���� "�" �� ����� ������.
void SetPortK_In(void)
{
 ClearCtrlBit_LCD(LCD_BIT_DIR);//DIR = 0, ����� ������������ ������� �� �����
 //HWREG(GPIO_PORTK_BASE + GPIO_O_DIR) &= 0xFFFFFF00;//���� ����� "�" �� �����
 HWREG(GPIO_PORTL_BASE + GPIO_O_DIR) &= 0xFFFFFF00;//
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
  HWREG(GPIO_PORTC_AHB_BASE + GPIO_O_DATA + 0x000040) = 0x0010;


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
	  HWREG(GPIO_PORTC_AHB_BASE + GPIO_O_DATA + 0x000040) = ~0x0010;


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

//������ ����� � ���
void Write_Byte_LCD(unsigned char bflagDC, unsigned char bData)
{
 SetPortK_Out();

 if(bflagDC) SetCtrlBit_LCD(LCD_BIT_RS);  //RS=1 - ������
 else ClearCtrlBit_LCD(LCD_BIT_RS);       //RS=0 - �������

 ClearCtrlBit_LCD(LCD_BIT_WR);//WR=0 - ������

 //HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x3FC) = bData;//���������� � ���� "K" 8 ��� ������ (���� ������)
 HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + 0x3FC) = bData;//���������� � ���� "K" 8 ��� ������ (���� ������)

 SetCtrlBit_LCD(LCD_BIT_E);    //E=1
 _NOP();//���. ������� 230 ����.
 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0
}

//������ ����� �� ���
unsigned char Read_Byte_LCD(unsigned char bflagDC)
{
 SetPortK_In();

 if(bflagDC) SetCtrlBit_LCD(LCD_BIT_RS);  //RS=1 - ������
 else ClearCtrlBit_LCD(LCD_BIT_RS);       //RS=0 - �������

 SetCtrlBit_LCD(LCD_BIT_WR);   //WR=1 - ������
 SetCtrlBit_LCD(LCD_BIT_E);    //E=1
 _NOP();//���. ������� 230 ����.

 //bflagDC = HWREG(GPIO_PORTK_BASE + GPIO_O_DATA + 0x3FC);//������ �� ����� "K" 8 ��� ������ (���� ������)
 bflagDC = HWREG(GPIO_PORTL_BASE + GPIO_O_DATA + 0x3FC);//������ �� ����� "K" 8 ��� ������ (���� ������)

 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0
 ClearCtrlBit_LCD(LCD_BIT_WR); //WR=0

 return(bflagDC);
}

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
void  ShowMsgLCDnCyr(unsigned char bT, unsigned char *szT)
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
void  ShowMsgLCD(unsigned char  bT, unsigned char  *szT)
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

 RunClocking();
/*
 HWREG(GPIO_PORTK_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0x0F;//������ � �������� ��������
*/
 HWREG(GPIO_PORTL_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������
 HWREG(GPIO_PORTC_AHB_BASE + GPIO_O_DEN) |= 0xFF;//������ � �������� ��������

 SetPortK_Out();//���� ����� "�" �� �������� ������
 HWREG(GPIO_PORTG_AHB_BASE + GPIO_O_DIR) |= 0xFF;//
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0xFF;//
 HWREG(GPIO_PORTC_AHB_BASE + GPIO_O_DIR) |= 0xFF;//
/*
 HWREG(GPIO_PORTF_AHB_BASE + GPIO_O_DIR) |= 0x0F;//������� ���� ����� "F" �� �������� (����������� ������ �� ��������)


 #ifdef	PF2_TO_PD0_WR
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DIR) |= 0x01;//PD0
  HWREG(GPIO_PORTD_AHB_BASE + GPIO_O_DEN) |= 0x01;//PD0
 #endif
*/

 ClearCtrlBit_LCD(LCD_BIT_E);  //E=0 ��������� �� ������
 ClearCtrlBit_LCD(LCD_BIT_WR); //WR=0
}

void    InitLCD(void)
{
  InitGPIO_LCD();

  Delay(50000);    SetCommLCD(0x30);
  Delay(50000);    SetCommLCD(0x30);
  Delay(50000);    SetCommLCD(0x30);

  ReadyLCD();   SetCommLCD(0x38);
  ReadyLCD();   SetCommLCD(0x08);
  ReadyLCD();   SetCommLCD(0x01);
  ReadyLCD();   SetCommLCD(0x06);
  ReadyLCD();   SetCommLCD(0x0C);
}
