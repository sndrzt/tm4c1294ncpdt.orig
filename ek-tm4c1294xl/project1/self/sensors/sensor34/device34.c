/*------------------------------------------------------------------------------
DEVICE34.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
//#include "../../memory/mem_current.h"
//#include "../../memory/mem_factors.h"
//#include "../../memory/mem_realtime.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
//#include "../../display/display.h"
//#include "../../time/timedate.h"
//#include "../../time/delay.h"
//#include "../../devices/devices.h"
//#include "../../digitals/current/current_run.h"
//#include "../../digitals/digitals_messages.h"
//#include "../sensor31/automatic31.h"
//#include "automatic33.h"
#include "device34.h"


/*
#ifndef SKIP_33

static uchar            bVersion33;



uint    PopInt33(void)
{
  return (bVersion33 == 16) ? PopIntLtl() : PopIntBig();
}


ulong   PopLong33(void)
{
  return (bVersion33 == 16) ? PopLongLtl() : PopLongBig();
}



void    QueryClose33(void)
{
  InitPush(0);

  PushChar(0x7E);
  PushChar(0x00);
  PushChar(0x02);

  Query33(0, 3+1);
}


void    QueryOpen33(void)
{
  QueryClose33();
  DelayOff();

  memset(&mpbCoder, 0, sizeof(mpbCoder));

  InitPush(0);

  PushChar(0x7E);
  PushChar(0x08);
  PushChar(0x03);

  PushLongBig(mpdwAddress1[diCurr.bAddress-1]);
  PushLongBig(mpdwAddress2[diCurr.bAddress-1]);

  Query33(3+8+1, 3+8+1);
}


bool    ReadOpen33(void)
{
  InitPop(3);

  bVersion33 = PopChar();

  mpbCoder[0] = PopChar();
  mpbCoder[1] = PopChar();
  mpbCoder[2] = PopChar();
  mpbCoder[3] = PopChar();

  Clear(); sprintf(szLo+3,"������: %2u",bVersion33);
  DelayInf(); Clear();

  if ((bVersion33 == 16) ||
      (bVersion33 == 18))
    return true;

  ShowLo(szNoVersion);
  DelayInf(); Clear();

  return false;
}


uchar   GetVersion33(void)
{
  return bVersion33;
}
*/


void    QueryTime34(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(0x64);
  PushChar(0x00);
  PushChar(0x46);
  PushChar(0x00);
  PushChar(0x09);

  QueryIO(3+18+2, 6+2);
}


time convertUnixTimeToDate(uint32_t  t)
{
   uint32_t a;
   uint32_t b;
   uint32_t c;
   uint32_t d;
   uint32_t e;
   uint32_t f;

   time ti;

   // negative Unix time values are not supported
   if (t < 1)
      t = 0;

   // retrieve hours, minutes and seconds
   ti.bSecond = t % 60;
   t /= 60;
   ti.bMinute = t % 60;
   t /= 60;
   ti.bHour = t % 24;
   t /= 24;

   // convert Unix time to date
   a = (uint32_t) ((4 * t + 102032) / 146097 + 15);
   b = (uint32_t) (t + 2442113 + a - (a / 4));
   c = (20 * b - 2442) / 7305;
   d = b - 365 * c - (c / 4);
   e = d * 1000 / 30601;
   f = d - e * 30 - e * 601 / 1000;

   // January and February are counted as months 13 and 14 of the previous year
   if(e <= 13)
   {
      c -= 4716;
      e -= 1;
   }
   else
   {
      c -= 4715;
      e -= 13;
   }

   // retrieve year, month and day
   ti.bYear = c % 2000;
   ti.bMonth = e;
   ti.bDay = f;

   return ti;
}


time    ReadTime34(void)
{
  InitPop(3);
  return convertUnixTimeToDate(PopLongLtl());
}

/*
time    ReadPackTime33(void)
{
  InitPop(3);

  uchar a,b;
  if (GetVersion33() == 16)
  {
    b = PopChar();
    a = PopChar();
  }
  else
  {
    a = PopChar();
    b = PopChar();
  }

  time ti;

  ti.bHour   = (b >> 2) & 0x1F;
  ti.bMinute = (b & 0x03)*15;
  ti.bSecond = 0;

  ti.bDay    = ((0x100*a+b) >> 7) & 0x1F;
  ti.bMonth  = (a >> 4) & 0x0F;
  ti.bYear   = (ti.bMonth > tiCurr.bMonth) ? tiCurr.bYear-1 : tiCurr.bYear;

  return ti;
}



void    QueryControl33(time  ti)
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

  Query33(3+1, 3+8+1);
}



void    QueryEngAbs33(uchar  ibTrf)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x04); // "����������� ������� �� �������"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query33(3+14+1, 3+3+1);
}



bool    Checksum33(uchar  bSize)
{
  if (bVersion33 == 16)
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
*/
