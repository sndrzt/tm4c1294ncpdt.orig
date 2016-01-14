/*------------------------------------------------------------------------------
DEVICE_W!C

Rovalant ���-3
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../serial/monitor.h"
#include "../display/display.h"
#include "../keyboard/time/key_timedate.h"
#include "../time/timedate.h"
#include "../time/delay.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
#include "../digitals/current/current_run.h"
#include "../digitals/limits.h"
#include "../special/special.h"
#include "automatic_w.h"
#include "device_k.h"
#include "device_w.h"



#ifndef SKIP_W

uchar                   ibLineW;

time                    tiProfileW;

slong                   dwCorrectW;

uint                    wProfileW;



double  PopDoubleW(void)
{
  bool begin = false;
  bool point = false;

  double dbA = 0;
  double dbB = 1;
  double dbC = 0.1;

  while (GetPopSize() < IndexInBuff())
  {
//    MonitorString("\n"); MonitorIntDec(GetPopSize()); MonitorString(" ? "); MonitorIntDec(IndexInBuff());

    uchar b = PopChar0Bcc();
    if (begin == false)
    {
      if (b == '(')
        begin = true;
    }
    else
    {
      if (b == '.')
        point = true;
      else if (b == ')')
      {
        dbA *= dbC;
        return dbA;
      }
      else
      {
        if ((b >= '0') && (b <= '9'))
        {
          b -= '0';
          dbA += dbB*b;
          dbB /= 10;

          if (point == false)
            dbC *= 10;
        }
        else break;
      }
    }
  }

  return -1;
}


time    PopTimeW(void)
{
  while (GetPopSize() < IndexInBuff())
  {
//    MonitorString("\n"); MonitorIntDec(GetPopSize()); MonitorString(" ? "); MonitorIntDec(IndexInBuff());

    uchar b = PopChar0Bcc();
    if (b == '(')
    {
   	  time ti;

      ti.bYear   = PopChar2Bcc(); PopChar();
      ti.bMonth  = PopChar2Bcc(); PopChar();
      ti.bDay    = PopChar2Bcc(); PopChar();
      ti.bHour   = PopChar2Bcc(); PopChar();
      ti.bMinute = PopChar2Bcc(); PopChar();
      ti.bSecond = 0;

      return ti;
    }
  }

  return tiZero;
}



void    QueryCloseW(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('B');
  PushChar1Bcc('0');
  PushChar1Bcc(0x03);

  QueryW(0, 0);
  DelayOff();
}



uchar   PushAddress1W(void)
{
  InitPush(0);
  PushChar1Bcc('/');
  PushChar1Bcc('?');

  uchar n = PushNumberBcc(mpdwAddress1[diCurr.bAddress-1]);

  PushChar1Bcc('!');
  return 2+n+1;
}


uchar   PushAddress2W(void)
{
  uchar n = PushAddress1W();

  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  return n+3;
}



void    QueryOpenW(void)
{
  QueryCloseW();

  uchar n = PushAddress1W();

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(2000, n+2, 1);
}



void    QueryTypeW(void)
{
  PushAddress2W();

  PushStringBcc("0-0:");
  PushStringBcc("96.53.0");
  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}


void    ReadTypeW(void)
{
  Clear();
  InitPop(1);

  bool f = false;

  uchar i = 0;
  while (true)
  {
    uchar b = PopChar0Bcc();

    if (b == ')') break;
    if (i >= 16) break;

    if (b == '\\') b = '/';
    if (f) szLo[i++] = b;

    if (b == '(') f = true;
  }
}


void    QueryTimeW_Profile(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-0:0.9.1");
  PushChar1Bcc(0x03);

  QueryW(1+28+2, 0);
}


void    QueryTimeW(void)
{
  uchar n = PushAddress2W();

  PushStringBcc("1-0:0.9.1");
  PushChar1Bcc(0x03);

  QueryW(1+28+2, 0);
}


time    ReadTimeW(void)
{
  InitPop(11);

  time ti;

  ti.bYear   = PopChar2Bcc(); PopChar();
  ti.bMonth  = PopChar2Bcc(); PopChar();
  ti.bDay    = PopChar2Bcc(); PopChar();
  ti.bHour   = PopChar2Bcc(); PopChar();
  ti.bMinute = PopChar2Bcc(); PopChar();
  ti.bSecond = PopChar2Bcc(); PopChar();

  return ti;
}


void    QueryControlW(time  ti)
{
  Clear(); sprintf(szLo+3,"���������");

  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('W');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-0:0.9.1");

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc('-');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('-');
  PushChar2Bcc(ti.bDay);
  PushChar1Bcc(' ');
  PushChar2Bcc(ti.bHour);
  PushChar1Bcc(':');
  PushChar2Bcc(ti.bMinute);
  PushChar1Bcc(':');
  PushChar2Bcc(ti.bSecond);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  QueryW(1+1, 0);
}



void    QueryGetCorrectW(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("0-0:96.52.0");

  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}


uint    ReadGetCorrectW(void)
{
  InitPop(1);
  uint w = PopDoubleW();

  Clear(); sprintf(szLo+2,"�����: %u",w);

  return w;
}


void    QuerySetCorrectW(sint  wSecond)
{
  Clear(); sprintf(szLo+1,"���������: %d",wSecond);

  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('W');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("0-0:96.51.0");
  PushChar1Bcc('(');
  if (wSecond < 0) PushChar1Bcc('-');
  PushNumberBcc(AbsInt(wSecond));
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  QueryW(1+1, 0);
}


void    QueryOptionW(void)
{
  InitPush(0);
  PushChar1Bcc(0x06);

  uchar i;
  switch (mppoPorts[ diCurr.ibPort ].ibBaud)
  {
    case 0:  i = '2'; break;
    case 1:  i = '3'; break;
    case 2:  i = '4'; break;
    case 3:  i = '5'; break;
    case 4:  i = '6'; break;
    default: i = '7'; break;
  }

  PushChar1Bcc('0');
  PushChar1Bcc(i);
  PushChar1Bcc('1');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  cbHeaderBcc = 1;
  cwInBuffBcc = 0;

  Query(1000, 4+2, 1);
}


void    QueryPasswordW(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('P');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);
  PushChar1Bcc('(');

  PushNumberBcc(mpdwAddress2[diCurr.bAddress-1]);

  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  QueryW(1+1, 0);
}



void    QueryKtransW(uchar  ibKtrans)
{
  ASSERT(ibKtrans < 2);

  PushAddress2W();

  PushStringBcc("0-0:");
  PushStringBcc("96.68.");
  PushChar1Bcc('0'+ibKtrans);
  PushChar1Bcc(0x03);

  QueryW(1000, 1);
}



void    QueryEngAbsW_Current(uchar  ibLine)
{
  ASSERT(ibLine < MAX_LINE_W);

  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".8.0");
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngAbsW(uchar  ibLine)
{
  ASSERT(ibLine < MAX_LINE_W);

  if ((diCurr.bDevice == 29) && (ibLine == 0)) ibLine = 14;

  PushAddress2W();

  PushStringBcc("1-1:");
  PushNumberBcc(ibLine+1);
  PushStringBcc(".8.0");
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngMonW(uchar  ibLine, uchar  bTime)
{
  ASSERT(ibLine < MAX_LINE_W);

  if ((diCurr.bDevice == 29) && (ibLine == 0)) ibLine = 14;

  PushAddress2W();

  PushStringBcc("1-1:");
  PushNumberBcc(ibLine+1);
  PushStringBcc(".129.0*");
  PushNumberBcc(bTime);
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngDayW(uchar  ibLine, uchar  bTime)
{
  ASSERT(ibLine < MAX_LINE_W);

  PushAddress2W();

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".128.0*");
  PushNumberBcc(bTime);
  PushStringBcc("(1)");
  PushChar1Bcc(0x03);

  QueryW(1000, 2);
}


void    QueryEngMonTrfW(uchar  ibLine, uchar  bTime)
{
  ASSERT(ibLine < MAX_LINE_W);

  PushAddress2W();

  PushStringBcc("1-1:");
  PushChar1Bcc('1'+ibLine);
  PushStringBcc(".129.0*");
  PushNumberBcc(bTime);
  PushStringBcc("(5)");
  PushChar1Bcc(0x03);

  QueryW(1000, 6);
}


void    ReadEngW(uchar  ibLine)
{
  ASSERT(ibLine < MAX_LINE_W);

  InitPop(1);
  mpdbChannelsC[ibLine] = PopDoubleW()/1000;
}


void    ReadEngTrfW(uchar  ibLine, uchar  ibTrf)
{
  ASSERT(ibLine < MAX_LINE_W);
  ASSERT(ibTrf < 4);

  InitPop(1);

  uchar t;
  for (t=0; t<ibTrf+2; t++)
  {
    mpdbChannelsC[ibLine] = PopDoubleW()/1000;
  }
}


void    InitProfileW(void)
{
  if (!UseBounds())
    wProfileW = 0;
  else
  {
    wProfileW = mpcwStartRelCan[ibDig];
    sprintf(szLo," ������ %04u:%02u ",wProfileW,(uchar)(wProfileW/48 + 1));
    if (boShowMessages == true) DelayMsg();
  }

  MonitorString("\n\n start index "); MonitorIntDec(wProfileW);
}


void    QueryProfileW(void)
{
  HideCurrTime(1);


  MonitorString("\n\n index "); MonitorIntDec(wProfileW);


  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushStringBcc("1-1:1.29.0*");
  PushNumberBcc(wProfileW);
  PushStringBcc("(4)");
  PushChar1Bcc(0x03);

  QueryW(1000, 5);
}


bool    ReadProfileW(void)
{
  InitPop(1);

  double dbK = mpdbPulseHou[ibDig]/2000;

  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    ulong dw = PopDoubleW();
    MonitorString("\n value "); MonitorLongDec(dw);

    mpdbEngFracDigCan[ibDig][i] += (double)dw;

    uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbK);
    MonitorString(" "); MonitorIntDec(w);
    mpwChannels[i] = w;

    mpdbEngFracDigCan[ibDig][i] -= (double)w/dbK;
  }

  time ti = PopTimeW();
  MonitorString("\n time "); MonitorTime(ti);


  sprintf(szLo," %02u    %02u.%02u.%02u", ti.bHour, ti.bDay,ti.bMonth,ti.bYear);
  if (SearchDefHouIndex(ti) == 0) return true;
  ShowProgressDigHou();


  MakeSpecial(ti);
  return MakeStopHou2(0,wProfileW);
}



void    ReadCurrentW(void)
{
  uchar i;
  for (i=0; i<MAX_LINE_W; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}

#endif
