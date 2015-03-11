/*------------------------------------------------------------------------------
SPEEDS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "driverlib/rom.h"
#include        "driverlib/uart.h"
#include        "inc/hw_memmap.h"
#include        "../memory/mem_ports.h"
#include        "../hardware/system_clock.h"
#include        "../serial/ports.h"
#include        "speeds.h"
#include        "speeds_storage.h"



// ������ ��������� ������
ulong const             mpdwSpeeds[bSPEEDS] =
{ 1200, 2400, 4800, 9600, 19200, 38400, 57600, 115200, 230400 };

// ������ ��������� �� ���� ��� ������ RS-232 (����� �������� 100 ��� �� ������ ��������)
static uint const       mpwInDelaySlave[bSPEEDS] =
{
  (uint)(wFREQUENCY_T0*0.0833),
  (uint)(wFREQUENCY_T0*0.0417),
  (uint)(wFREQUENCY_T0*0.0208),
  (uint)(wFREQUENCY_T0*0.0104),
  (uint)(wFREQUENCY_T0*0.0052),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035),
  (uint)(wFREQUENCY_T0*0.0035)
};

// ������ ��������� �� ���� ��� ����� RS-485 (300 ����������� ���� ����� �������� 1000 ��� �� ������ ��������)
static uint const       mpwInDelayMaster[bSPEEDS] =
{
  (uint)(wFREQUENCY_T0*1.1333),
  (uint)(wFREQUENCY_T0*0.7167),
  (uint)(wFREQUENCY_T0*0.5083),
  (uint)(wFREQUENCY_T0*0.4042),
  (uint)(wFREQUENCY_T0*0.3521),
  (uint)(wFREQUENCY_T0*0.3260),
  (uint)(wFREQUENCY_T0*0.3174),
  (uint)(wFREQUENCY_T0*0.3087),
  (uint)(wFREQUENCY_T0*0.3044)
};



void     SetUART(uchar  ibPrt, ulong  dwBase)
{
//  ROM_UARTConfigSetExpClk(dwBase, GetSystemClockFrequency(), 9600, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}



void    SetSpeed0(void)
{
  SetUART(0, UART0_BASE);
}


void    SetSpeed1(void)
{
  SetUART(1, UART1_BASE);
}


void    SetSpeed2(void)
{
  SetUART(2, UART2_BASE);
}


void    SetSpeed3(void)
{
  SetUART(3, UART3_BASE);
}



bool    IsMaster(uchar  ibPrt)
{
  return((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || (mppoPorts[ibPrt].enStream == STR_MASTERMODEM));
}


bool    IsSlave(uchar  ibPrt)
{
  return( ~IsMaster(ibPrt) );
}



void    SetCorrectLimit(uchar  ibPrt)
{
//  mpbCorrectLimit[ibPrt] = (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
}


void    CheckCorrectLimit(uchar  ibPrt)
{
//  if (mpbCorrectLimit[ibPrt] < bCORRECT_MINIMUM) SetCorrectLimit(ibPrt);
//  if (mpbCorrectLimit[ibPrt] > bCORRECT_MAXIMUM) mpbCorrectLimit[ibPrt] = bCORRECT_MAXIMUM;
}


void    MakeCorrectLimit(void)
{
//  if (diT.bDevice == 24) mpbCorrectLimit[diT.ibPort] = bCORRECT_DEVICE_S;
}



void    SetDefaultDelay(uchar  ibPrt)
{
uint    w;

  mpSerial[ibPrt] = SER_BEGIN;

  if ((mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) || 
      (mppoPorts[ibPrt].enStream == STR_MASTERMODEM))
    w = mpwInDelayMaster[ mppoPorts[ibPrt].ibSpeed ];
  else
    w = mpwInDelaySlave[ mppoPorts[ibPrt].ibSpeed ];

  mpwMajorInDelay[ibPrt] = w;
  mpwMinorInDelay[ibPrt] = w;

  SaveMajorInDelay();
  SaveMinorInDelay();
}



void    SetSpeed(uchar  ibPrt)
{
  mpSerial[ibPrt] = SER_BEGIN;

  switch (ibPrt)
  {
    case 0:  SetSpeed0();  break;
    case 1:  SetSpeed1();  break;
    case 2:  SetSpeed2();  break;
    case 3:  SetSpeed3();  break;
  }

  SavePorts();
}



void    InitSpeeds(void)
{
uchar   p;

  LoadPorts();
  LoadMajorInDelay();
  LoadMinorInDelay();

  for (p=0; p<bPORTS; p++)
  {
    if (mppoPorts[p].ibSpeed >= bSPEEDS)
    {
      mppoPorts[p].ibSpeed = 0;
      SetDefaultDelay(p);
    }

    if (mppoPorts[p].enStream >= bSTREAMS)
      mppoPorts[p].enStream = STR_SLAVEESC;

    SetSpeed(p);
    CheckCorrectLimit(p);
  }
}



void    ResetSpeeds(void)
{  
uchar   p;

  mppoPorts[0].enStream = STR_SLAVEESC;
  mppoPorts[1].enStream = STR_SLAVEESC;
  mppoPorts[2].enStream = STR_MASTERDIRECT;
  mppoPorts[3].enStream = STR_MASTERDIRECT;

  for (p=0; p<bPORTS; p++)
  {
    mppoPorts[p].ibSpeed  = 3;
    mppoPorts[p].ibParity = 0;

    SetDefaultDelay(p);
    SetCorrectLimit(p);
  }

  SavePorts();
  SaveMajorInDelay();
  SaveMinorInDelay();
}
