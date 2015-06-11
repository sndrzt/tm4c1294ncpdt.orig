/*------------------------------------------------------------------------------
23x1024.�


------------------------------------------------------------------------------*/
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../time/delay.h"
#include "23x1024.h"



//����� ����� ������
#define MAX_SIZE_23LC1024 (128 * 1024) //128��
//���������� �������� ��� ��������� ������ � ����
#define MAXREPEATS_23LC1024    10

  //���� ���������� SPI
  #define SPI_BIT_SO    0x0001 //PF0
  #define SPI_BIT_SI    0x0002 //PF1
  #define SPI_BIT_CS    0x0004 //PF2
  #define SPI_BIT_SCK   0x0008 //PF3

  //������ ����� ���������� SPI
  #define GPIO_DATABIT_SO  (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0004)//PF0
  #define GPIO_DATABIT_SI  (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0008)//PF1
  #define GPIO_DATABIT_CS  (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0010)//PF2
  #define GPIO_DATABIT_SCK (GPIO_PORTF_BASE + GPIO_O_DATA + 0x0020)//PF3

 #define DELAY_NEW_STAT_PIN 1

static void Delay_1(ulong ulgTime)
{
 while(ulgTime--);
}

//�������� ������ �����
//���� �������� ����������� ���� �� ��������� ������
static void  CharOut(uchar bI)
{
 uchar bK;

 for(bK=0; bK<8; bK++)
 {
  if(bI & (0x80 >> bK )) HWREG(GPIO_DATABIT_SI) = SPI_BIT_SI;
  else HWREG(GPIO_DATABIT_SI) = ~SPI_BIT_SI;
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
}//end CharOut

//����� ������ �����
//���� ����������� ����������� ���� � ������� ���������� �������� (������� ������� �� SCK)
static uchar  CharIn(void)
{
 uchar bRez, bK;

 bRez = 0;
 for(bK=0; bK<8; bK++)
 {
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x80 >> bK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
 return(bRez);
}//end CharIn
/*
//���� �������������
static void  OnePulse_1(void)
{
 HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
}//end OnePulse
*/
//���������� � ������ ������ �� SPI
static void Start(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
 Delay_1(DELAY_NEW_STAT_PIN);
}

//��������� ������ �� SPI
static void Stop(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 Delay_1(DELAY_NEW_STAT_PIN);
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
}

//��������� ������������� SPI
//�� ��������� �����: Sequential mode (����� ������������ ������/������ �� ����� ������ ����)
void Init_EOZU(void)
{
 //��������� ���������
 HWREG(SYSCTL_RCGCGPIO) |= 0x00000020;//������ "F"

 DelayGPIO();

 //��� ����� "F" (SPI+CE)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DIR)   |= 0x000E;//���� �� �������� (PF0 �� �����)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DEN)   |= 0x000F;//�������� ������

 Stop();
}

//������ � ����� *ptrMas, ������� � ����� lgAddr ���������� ���� lgSize
void LoadBytes_EOZU(uchar *ptrMass, ulong lgAddr, ulong lgSize)
{
 if(((lgAddr + lgSize) > MAX_SIZE_23LC1024) || (lgSize == 0)) return;//���������� ���������� ������ SRAM

 Start();
 CharOut(0x03);//������
 CharOut(*((uchar*)(&lgAddr)+2)); //24-� ������ �����
 CharOut(*((uchar*)(&lgAddr)+1));
 CharOut(*((uchar*)(&lgAddr)+0));

 while(lgSize--)
 {
  *(ptrMass++) = CharIn();
 }

 Stop();
}


//������ �� ������ *ptrMas, ������� � ����� lgAddr ���������� ���� lgSize
//=1 - ������ ������
//=0 - ������ ������� ���������
uchar SaveBytes_EOZU(uchar *ptrMass, ulong lgAddr, ulong lgSize)
{
 ulong lgSaveSize;
 uchar bi;

 if(((lgAddr + lgSize) > MAX_SIZE_23LC1024) || (lgSize == 0)) return(1);//���������� ���������� ������ SRAM

 lgSaveSize = lgSize;

 for(bi=0; bi<MAXREPEATS_23LC1024; bi++)
 {
  lgSize = lgSaveSize;

  //������ �������
  Start();
  CharOut(0x02);//������
  CharOut(*((uchar*)(&lgAddr)+2)); //24-� ������ �����
  CharOut(*((uchar*)(&lgAddr)+1));
  CharOut(*((uchar*)(&lgAddr)+0));

  while(lgSize--)
  {
   CharOut(*(ptrMass++));
  }
  Stop();

  //�������� ���������� ������
  lgSize = lgSaveSize;
  ptrMass -= lgSize;

  Start();
  CharOut(0x03);//������
  CharOut(*((uchar*)(&lgAddr)+2)); //24-� ������ �����
  CharOut(*((uchar*)(&lgAddr)+1));
  CharOut(*((uchar*)(&lgAddr)+0));

  while(lgSize--)
  {
   if(*(ptrMass++) != CharIn()) break;
  }
  Stop();

  if((++lgSize) == 0) break;//��� ����� - �������
  else
  {//����� ��������� ������, ������� � ��������� �����
   lgAddr += (lgSaveSize-lgSize);
   ptrMass--;
   lgSaveSize = lgSize;
  }
 }//for(bi=0; bi<MAXREPEATS_23LC1024; bi++)

 if(bi == MAXREPEATS_23LC1024) return(1);
 else return(0);
}

//������ �������� ������ ������ ����
uchar ReadModeReg_EOZU(void)
{
 uchar bRez;

 Start();
 CharOut(0x05);
 bRez = CharIn();
 Stop();

 return(bRez);
}
