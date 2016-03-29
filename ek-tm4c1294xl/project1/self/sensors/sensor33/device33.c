/*------------------------------------------------------------------------------
DEVICE32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../time/timedate.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals_messages.h"
#include "../sensor31/automatic31.h"
#include "automatic32.h"
#include "device32.h"



#ifndef SKIP_32

static uchar            bVersion32;



ulong   PopChar3Big32(void)
{
  return PopChar()*0x10000 + PopChar()*0x100 + PopChar();
}



void    QueryClose32(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  Query32(0, 3+1);
}


void    QueryOpen32(void)
{
  QueryClose32();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

  Query32(3+8+1, 3+8+1);
}


bool    ReadOpen32(void)
{
  InitPop(3);

  bVersion32 = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  Clear(); sprintf(szLo+3,"������: %2u",bVersion32);
  DelayInf(); Clear();

  if ((bVersion32 == 51) ||
      (bVersion32 == 52) ||
      (bVersion32 == 53) ||
      (bVersion32 == 54))
    return true;

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}


uchar   GetVersion32(void)
{
  return bVersion32;
}


bool    OldVersion32(void)
{
  return false;
}



void    QueryTime32(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x07);

  Query32(3+8+1, 3+1);
}


time    ReadTime32(void)
{
  InitPop(3);

  time ti;
  ti.bSecond = PopChar();
  ti.bMinute = PopChar();
  ti.bHour   = PopChar();
               PopChar();
  ti.bDay    = PopChar();
  ti.bMonth  = PopChar();
  ti.bYear   = PopChar();

  return ti;
}


time    ReadPackTime32(void)
{
  InitPop(3);

  uchar a = PopChar();
  uchar b = PopChar();

  time ti;

  ti.bHour   = (b >> 2) & 0x1F;
  ti.bMinute = (b & 0x03)*15;
  ti.bSecond = 0;

  ti.bDay    = ((0x100*a+b) >> 7) & 0x1F;
  ti.bMonth  = (a >> 4) & 0x0F;
  ti.bYear   = (ti.bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  return ti;
}



void    QueryControl32(time  ti)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x08); // "������ ������� � ���� � �������"

  PushCharCod(ti.bSecond);
  PushCharCod(ti.bMinute);
  PushCharCod(ti.bHour);

  PushCharCod(GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) + 1); // "���� ������ (1..7, 1-�����������)"

  PushCharCod(ti.bDay);
  PushCharCod(ti.bMonth);

  PushCharCod(ti.bYear);
  PushCharCod(20);

  Query32(3+1, 3+8+1);
}



void    QueryEngAbs32(uchar  ibTrf)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x04); // "����������� ������� �� �������"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query32(3+14+1, 3+3+1);
}



bool    Checksum32(uchar  bSize)
{
  if (OldVersion32())
  {
    uint wCRC = MakeCrc16Bit32InBuff(3, bSize-2);
    return (wCRC == InBuff(3+bSize-2) + InBuff(3+bSize-1)*0x100);
  }
  else
  {
    uint wCRC = MakeCrc16Bit32InBuff(3, bSize);
    return (wCRC == 0);
  }
}

#endif
