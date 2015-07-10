/*------------------------------------------------------------------------------
23x1024.�


------------------------------------------------------------------------------*/
#include "../main.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ssi.h"
#include "inc/hw_types.h"
#include "../memory/mem_nvram.h"
#include "../kernel/crc-16.h"
#include "../time/delay.h"
#include "23x1024.h"



// ���������� ��������
#define bNVRAM_REPEATS  8



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


static void CharOutCRC(uchar  b)
{
  CharOut(b);
  CalcCRC(b);
}


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


void    InitNvram(void)
{
 //��������� ���������
 HWREG(SYSCTL_RCGCGPIO) |= 0x00000020;//������ "F"

 DelayGPIO();

 //��� ����� "F" (SPI+CE)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DIR)   |= 0x000E;//���� �� �������� (PF0 �� �����)
 HWREG(GPIO_PORTF_BASE + GPIO_O_DEN)   |= 0x000F;//�������� ������

 Stop();
}



uchar   PushChar(uchar  b);

bool    PushNvramBuff(ulong  dwAddr, uint  wSize)
{
  Start();

  CharOut(0x03); // ������
  CharOut(*((uchar*)(&dwAddr)+2));
  CharOut(*((uchar*)(&dwAddr)+1));
  CharOut(*((uchar*)(&dwAddr)+0));

  uint i;
  for (i=0; i<wSize; i++)
  {
    PushChar(CharIn());
  }

  Stop();

  return true;
}


bool    ReadNvramBuff_Raw(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  Start();

  CharOut(0x03); // ������
  CharOut(*((uchar*)(&dwAddr)+2));
  CharOut(*((uchar*)(&dwAddr)+1));
  CharOut(*((uchar*)(&dwAddr)+0));

  CharIn();
  CharIn();
  CharIn();

  CharIn();
  CharIn();

  uint i;
  for (i=0; i<wSize; i++)
  {
   *(pbBuff++) = CharIn();
  }

  Stop();

  return true;
}


bool    WriteNvramBuff_Raw(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  Start();

  CharOut(0x02); // ������
  CharOut(*((uchar*)(&dwAddr)+2));
  CharOut(*((uchar*)(&dwAddr)+1));
  CharOut(*((uchar*)(&dwAddr)+0));

  InitCRC();

  CharOutCRC(*((uchar*)(&dwAddr)+2));
  CharOutCRC(*((uchar*)(&dwAddr)+1));
  CharOutCRC(*((uchar*)(&dwAddr)+0));

  CharOutCRC(wSize / 0x100);
  CharOutCRC(wSize % 0x100);

  uint i;
  for (i=0; i<wSize; i++)
  {
    CharOutCRC(*(pbBuff++));
  }

  CharOutCRC(tiCurr.bSecond);
  CharOutCRC(tiCurr.bMinute);
  CharOutCRC(tiCurr.bHour);
  CharOutCRC(tiCurr.bDay);
  CharOutCRC(tiCurr.bMonth);
  CharOutCRC(tiCurr.bYear);

  CharOut(bCRCHi);
  CharOut(bCRCLo);


  Stop();

  pbBuff -= wSize;

  Start();

  CharOut(0x03); // ������
  CharOut(*((uchar*)(&dwAddr)+2));
  CharOut(*((uchar*)(&dwAddr)+1));
  CharOut(*((uchar*)(&dwAddr)+0));

  CharIn();
  CharIn();
  CharIn();

  CharIn();
  CharIn();

  bool f = true;
  for (i=0; i<wSize; i++)
  {
    if (*(pbBuff++) != CharIn())
    {
      f = false;
      break;
    }
  }

  Stop();

  return f;
}


bool    FreeNvramBuff_Raw(ulong  dwAddr, uint  wSize)
{
  Start();

  CharOut(0x02); // ������
  CharOut(*((uchar*)(&dwAddr)+2));
  CharOut(*((uchar*)(&dwAddr)+1));
  CharOut(*((uchar*)(&dwAddr)+0));

  InitCRC();

  CharOutCRC(*((uchar*)(&dwAddr)+2));
  CharOutCRC(*((uchar*)(&dwAddr)+1));
  CharOutCRC(*((uchar*)(&dwAddr)+0));

  CharOutCRC(wSize / 0x100);
  CharOutCRC(wSize % 0x100);

  uint i;
  for (i=0; i<wSize; i++)
  {
    CharOutCRC(0);
  }

  CharOutCRC(tiCurr.bSecond);
  CharOutCRC(tiCurr.bMinute);
  CharOutCRC(tiCurr.bHour);
  CharOutCRC(tiCurr.bDay);
  CharOutCRC(tiCurr.bMonth);
  CharOutCRC(tiCurr.bYear);

  CharOut(bCRCHi);
  CharOut(bCRCLo);


  Stop();

  Start();

  CharOut(0x03); // ������
  CharOut(*((uchar*)(&dwAddr)+2));
  CharOut(*((uchar*)(&dwAddr)+1));
  CharOut(*((uchar*)(&dwAddr)+0));

  CharIn();
  CharIn();
  CharIn();

  CharIn();
  CharIn();

  bool f = true;
  for (i=0; i<wSize; i++)
  {
    if (0 != CharIn())
    {
      f = false;
      break;
    }
  }

  Stop();

  return f;
}



uchar   ReadNvramStatus(void)
{
  Start();
  CharOut(0x05);
  uchar b = CharIn();
  Stop();

  return b;
}



bool    ReadNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  cdwNvramRead++;

  uchar i;
  for (i=0; i<bNVRAM_REPEATS; i++) {
    if (ReadNvramBuff_Raw(dwAddr, pbBuff, wSize) == true) break;
    cwWrnNvramRead++;
  }

  if (i == bNVRAM_REPEATS) {
    cwErrNvramRead++;
    return false;
  } else {
    return true;
  }
}


bool    WriteNvramBuff(ulong  dwAddr, uchar  *pbBuff,  uint  wSize)
{
  cdwNvramWrite++;

  uchar i;
  for (i=0; i<bNVRAM_REPEATS; i++) {
    if (WriteNvramBuff_Raw(dwAddr, pbBuff, wSize) == true) break;
    cwWrnNvramWrite++;
  }

  if (i == bNVRAM_REPEATS) {
    cwErrNvramWrite++;
    return false;
  } else {
    return true;
  }
}


bool    FreeNvramBuff(ulong  dwAddr, uint  wSize)
{
  cdwNvramFree++;

  uchar i;
  for (i=0; i<bNVRAM_REPEATS; i++) {
    if (FreeNvramBuff_Raw(dwAddr, wSize) == true) break;
    cwWrnNvramFree++;
  }

  if (i == bNVRAM_REPEATS) {
    cwErrNvramFree++;
    return false;
  } else {
    return true;
  }
}
