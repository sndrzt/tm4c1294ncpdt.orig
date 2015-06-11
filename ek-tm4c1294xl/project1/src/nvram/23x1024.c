/*------------------------------------------------------------------------------
23x1024.�


------------------------------------------------------------------------------*/
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
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

void Delay(unsigned long ulgTime)
{
 while(ulgTime--);
}

//�������� ������ �����
//���� �������� ����������� ���� �� ��������� ������
void  CharOut_1(unsigned char bI)
{
 unsigned char bK;

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
unsigned char  CharIn_1(void)
{
 unsigned char bRez, bK;

 bRez = 0;
 for(bK=0; bK<8; bK++)
 {
  HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
  if(HWREG(GPIO_DATABIT_SO)) bRez |= 0x80 >> bK;
  HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 }
 return(bRez);
}//end CharIn

//���� �������������
void  OnePulse_1(void)
{
 HWREG(GPIO_DATABIT_SCK) =  SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
}//end OnePulse

//���������� � ������ ������ �� SPI
void Start_1(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 HWREG(GPIO_DATABIT_CS)  = ~SPI_BIT_CS;
 Delay(DELAY_NEW_STAT_PIN);
}

//��������� ������ �� SPI
void Stop_1(void)
{
 HWREG(GPIO_DATABIT_SCK) = ~SPI_BIT_SCK;
 Delay(DELAY_NEW_STAT_PIN);
 HWREG(GPIO_DATABIT_CS)  = SPI_BIT_CS;
}

//��������� ������������� SPI
//�� ��������� �����: Sequential mode (����� ������������ ������/������ �� ����� ������ ����)
void Init_EOZU(void)
{
 //��������� ���������
 HWREG(SYSCTL_RCGCGPIO) |= 0x00000020;//������ "F"

 RunClocking();

 //��� ����� "F" (SPI+CE)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DIR)   |= 0x000E;//���� �� �������� (PF0 �� �����)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DEN)   |= 0x000F;//�������� ������

 Stop_1();
}

//������ � ����� *ptrMas, ������� � ����� lgAddr ���������� ���� lgSize
void LoadBytes_EOZU(unsigned char *ptrMass, unsigned long lgAddr, unsigned long lgSize)
{
 if(((lgAddr + lgSize) > MAX_SIZE_23LC1024) || (lgSize == 0)) return;//���������� ���������� ������ SRAM

 Start_1();
 CharOut_1(0x03);//������
 CharOut_1(*((unsigned char*)(&lgAddr)+2)); //24-� ������ �����
 CharOut_1(*((unsigned char*)(&lgAddr)+1));
 CharOut_1(*((unsigned char*)(&lgAddr)+0));

 while(lgSize--)
 {
  *(ptrMass++) = CharIn_1();
 }

 Stop_1();
}


//������ �� ������ *ptrMas, ������� � ����� lgAddr ���������� ���� lgSize
//=1 - ������ ������
//=0 - ������ ������� ���������
unsigned char SaveBytes_EOZU(unsigned char *ptrMass, unsigned long lgAddr, unsigned long lgSize)
{
 unsigned long lgSaveSize;
 unsigned char bi;

 if(((lgAddr + lgSize) > MAX_SIZE_23LC1024) || (lgSize == 0)) return(1);//���������� ���������� ������ SRAM

 lgSaveSize = lgSize;

 for(bi=0; bi<MAXREPEATS_23LC1024; bi++)
 {
  lgSize = lgSaveSize;

  //������ �������
  Start_1();
  CharOut_1(0x02);//������
  CharOut_1(*((unsigned char*)(&lgAddr)+2)); //24-� ������ �����
  CharOut_1(*((unsigned char*)(&lgAddr)+1));
  CharOut_1(*((unsigned char*)(&lgAddr)+0));

  while(lgSize--)
  {
   CharOut_1(*(ptrMass++));
  }
  Stop_1();

  //�������� ���������� ������
  lgSize = lgSaveSize;
  ptrMass -= lgSize;

  Start_1();
  CharOut_1(0x03);//������
  CharOut_1(*((unsigned char*)(&lgAddr)+2)); //24-� ������ �����
  CharOut_1(*((unsigned char*)(&lgAddr)+1));
  CharOut_1(*((unsigned char*)(&lgAddr)+0));

  while(lgSize--)
  {
   if(*(ptrMass++) != CharIn_1()) break;
  }
  Stop_1();

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
unsigned char ReadModeReg_EOZU(void)
{
 unsigned char bRez;

 Start_1();
 CharOut_1(0x05);
 bRez = CharIn_1();
 Stop_1();

 return(bRez);
}
