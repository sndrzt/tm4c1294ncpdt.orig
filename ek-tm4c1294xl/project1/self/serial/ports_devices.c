/*------------------------------------------------------------------------------
PORTS_DEVICES.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_serial3.h"
#include "../memory/mem_profile.h"
#include "../keyboard/keyboard.h"
#include "../hardware/watchdog.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../devices/devices.h"
#include "../sensors/unpack_k.h"
#include "../isr/serial.h"
#include "../isr/serial0.h"
#include "../isr/serial1.h"
#include "../isr/serial2.h"
#include "../isr/serial3.h"
#include "../kernel/crc-16.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "../serial/monitor.h"
#include "../serial/print2.h"
#include "monitor.h"
#include "input.h"
#include "ports.h"
#include "ports_devices.h"



void    Query(uint  cwIn, uchar  cbOut, bool  fMinor)
{
  MonitorOut(cwIn, cbOut);

  // ��� �������� ���� ������������� � ������� ����� �� ���������� ��������
  mpboLocal[ibPort] = false;

  // �������� �������� �������� ��������� � ��������� (����� ������������ � ��������� ������� ����� �� ��������)
  if (cwIn != SERIAL_LOCAL) cbWaitQuery = bMAXWAITQUERY;

  switch (ibPort)
  {
    case 0:  Query0(cwIn, cbOut, fMinor);  break;
    case 1:  Query1(cwIn, cbOut, fMinor);  break;
    case 2:  Query2(cwIn, cbOut, fMinor);  break;
    case 3:  Query3(cwIn, cbOut, fMinor);  break;
    default: ASSERT(false);
  }
}



// �������� ������� �� ���������� (�� ��������� ������)
void    QueryIO(uint  cwIn, uchar  cbOut)
{
  MakeCRC16OutBuff(0,cbOut-2);

  InitPush(0);
  Skip(cbOut-2);

  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Query(cwIn,cbOut,1);
}



serial  Input(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      MakeCRC16InBuff( 0, CountInBuff() );

      if ((bCRCHi == 0) && (bCRCLo == 0))
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}



#ifndef SKIP_C

// �������� ������� �� ���������� (�� ��������� ������)
void    RevQueryIO(uint  cwIn, uchar  cbOut)
{
  MakeCRC16OutBuff(0,cbOut-2);

  InitPush(0);
  bOutputC0 = SkipChar();
  bOutputC1 = SkipChar();
  bOutputC2 = SkipChar();

  InitPush(0);
  Skip(cbOut-2);

  PushChar(bCRCLo);
  PushChar(bCRCHi);

  Query(cwIn,cbOut,1);
}


bool    RevLinkErrors(void)
{
  if (InBuff(0) != bOutputC0) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  if ((InBuff(1) & 0x7F) != bOutputC1) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  if (InBuff(2) != bOutputC2) {
    mpcwOutput0[ibDig]++;
    return 1;
  }

  return 0;
}


serial  RevInput(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      MakeCRC16InBuff( 0, CountInBuff()-2 );

      if ((bCRCHi == InBuff( CountInBuff()-1 )) &&
          (bCRCLo == InBuff( CountInBuff()-2 ))) {

          if (RevLinkErrors() == 0)
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK;
          ChecksumError();
        }

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}

#endif



void    PckQueryIO(uint  cwIn, uchar  cbOut)
{
  InitPush(0);
  Push((void *)szPacketCRC, bPACKET_HEADER);

  MakeCRC16OutBuff(bPACKET_HEADER,cbOut-2);

  InitPushPck();
  Skip(cbOut-2);

  PushChar(bCRCHi);
  PushChar(bCRCLo);

  Query(cwIn,bPACKET_HEADER+cbOut,1);
}



void    BccQueryIO(uint  cwIn, uchar  cbOut, uchar  cbHeaderMax)
{
  cbHeaderBcc = cbHeaderMax;
  cwInBuffBcc = 0;

  InitPush(0);

  uchar bSum = 0;
  bool f = false;

  uchar i;
  for (i=0; i<cbOut-1; i++)
  {
    uchar b = SkipChar();
    if (f == true) bSum += b;
    if ((b & 0x7F) == 0x01) f = true;
  }

  PushChar1Bcc(bSum);

  Query(cwIn,cbOut,1);
}


bool    MakeBccInBuff(void)
{
uchar   bT;
uint    i;

  InitPop(1);

  bT = 0;
  for (i=0; i<CountInBuff()-2; i++) bT += PopChar0Bcc();

  return((bT & 0x7F) == PopChar0Bcc());
}


serial  BccInput(void)
{
  InputStart();
  InitWaitAnswer();

  while (1)
  {
    if (fKey == true) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      DecompressK(0);

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (MakeBccInBuff())
      {
        InputGoodCheck();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else
        mpSerial[ibPort] = SER_BADCHECK;

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  MonitorIn();
  return mpSerial[ibPort];
}



void    ChecksumError(void)
{
  mpcwOutputC[ibDig]++;
}


void    TestResult(uchar  bT)
{
  if (bT != 0)
  {
    Clear();
    sprintf(szLo+1,"��� ������: %02X ",bT);
    DelayInf();
  }
}
