/*------------------------------------------------------------------------------
IO35!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../hardware/watchdog.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../serial/input_wrapper.h"
#include "../../serial/monitor.h"
#include "../../digitals/wait_answer.h"
#include "include35.h"
#include "pack35.h"
#include "router35.h"
#include "device35.h"
#include "action35.h"
#include "timer35.h"
#include "log35.h"
#include "io35.h"



#ifndef SKIP_35

static uchar                cbInSave;
static uchar                cbOutSave;
static uchar                bCommandSave;





void    Query35Internal(uchar  cbIn, uchar  cbOut, uchar  bCommand)
{
  cbInSave     = cbIn;
  cbOutSave    = cbOut;
  bCommandSave = bCommand;


  MonitorOut(cbIn, cbOut);


  if (cbOut > 0)
  {
    // ������ CRC ��������
    uchar bCrc = MakeCrcSOutBuff(1, cbOut-3);

    InitPush(0);
    PushChar(0xC0);

    uchar i;
    for (i=0; i<cbOut-3; i++) SkipChar();

    PushChar(bCrc);
    PushChar(0xC0);


#ifdef MONITOR_35
    MonitorString("\n sensor pack start");
    MonitorOut(cbIn, cbOut);
#endif


    cbOut = Pack35(cbOut);


#ifdef MONITOR_35
    MonitorString("\n sensor pack finish");
    MonitorOut(cbIn, cbOut);
#endif


    // ������� ������ �������� ������ ������ �������������
    for (i=0; i<cbOut; i++)
      SetOutBuff(cbOut+12-i, OutBuff(cbOut-1-i));
  }


  // ���������� ������ ��������������
  InitPush(0);
  PushChar(0xC0);

  PushChar(0x02); // ������������� ���������

  PushChar(0); // ����� ��������������
  PushChar(0);
  PushChar(0);
  PushChar(0);

  PushChar(0x00); // ����� ������ � �������

  PushChar(bCommand); // ��� �������

  PushModemAddress35(); // ����� ������

  PushChar(0x00);


  // ������ CRC ��������������
  InitPush(13+cbOut);

  uint w = MakeCrc35OutBuff(1, 13+cbOut-1);
  PushChar(w / 0x100);
  PushChar(w % 0x100);

  PushChar(0xC0);

  cbOut = 13+cbOut+3;


#ifdef MONITOR_35
  MonitorString("\n router pack start");
  MonitorOut(cbIn, cbOut);
#endif


  cbOut = Pack35(cbOut);


#ifdef MONITOR_35
  MonitorString("\n router pack finish");
#endif


  Query(cbIn,cbOut,true);
}


void    Query35(uchar  cbIn, uchar  cbOut)
{
  SetTimer35(0);
  Query35Internal(cbIn, cbOut, NNCL2_DATA_SET);
}


void    Query35Repeat(void)
{
  MonitorString("\n repeat last query");
  Log35(R35_REPEAT_LAST_QUERY, bCommandSave);

  Query35Internal(cbInSave, cbOutSave, bCommandSave);
}



static serial Input35Internal(void)
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
      Decompress35();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (ChecksumRouter35() == 0)
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

  return mpSerial[ibPort];
}


serial  Input35(void)
{
  SaveDisplay();

  bool repeat;
  do
  {
    Input35Internal();
    repeat = false;

    if (mpSerial[ibPort] == SER_GOODCHECK)
    {
      action35 action = Action35(false);
      if (action == A35_WAIT)
      {
        Query35Internal(250, 0, 0x12);
        repeat = true;
      }
      else if (action == A35_SUCCESS)
      {
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else if (action == A35_ERROR)
      {
        mpSerial[ibPort] = SER_BADCHECK;
      }
      else if (action == A35_BREAK)
      {
        mpSerial[ibPort] = SER_BADCHECK; // TODO 35
      }
      else
      {
        ASSERT(false);
      }
    }
  } while (repeat);

  LoadDisplay();

  return mpSerial[ibPort];
}

#endif
