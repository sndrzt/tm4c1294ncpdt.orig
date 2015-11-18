/*------------------------------------------------------------------------------
DEVICE_U!C

 ���������� ��301
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../display/display.h"
#include "../keyboard/time/key_timedate.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../serial/ports_common.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
#include "../digitals/current/current_run.h"
#include "../digitals/limits.h"
#include "../special/special.h"
#include "../hardware/watchdog.h"
#include "device_k.h"
#include "device_q.h"
#include "device_u.h"



#ifndef SKIP_U

void    QueryCloseU(void)
{
  QueryCloseK();
}



void    QueryOptionU(void)
{
uchar   i;

  InitPush(0);
  PushChar1Bcc(0x06);

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


void    QueryCorrectU(void)
{
  InitPush(0);

  PushChar1Bcc('/');
  PushChar1Bcc('?');

  PushChar1Bcc('C');
  PushChar1Bcc('T');
  PushChar1Bcc('I');
  PushChar1Bcc('M');
  PushChar1Bcc('E');
  PushChar1Bcc('!');

  PushChar1Bcc(0x0D);
  PushChar1Bcc(0x0A);

  Query(1000, 2+6+2, 1);
}


void    QueryEnergyAbsU(uchar  ibLine)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+8+1, 6);
}


void    QueryEnergyDayU(uchar  ibLine, time  ti)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('D');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+16+1, 6);
}


void    QueryEnergyMonU(uchar  ibLine, time  ti)
{
  PushAddress2Bcc();

  PushChar1Bcc('E');
  PushChar1Bcc('N');
  PushChar1Bcc('M');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar2Bcc(ti.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(ti.bYear);
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+6*28+2, 15+13+1, 6);
}


void    QueryEnergySpecU(uchar  ibLine)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('E');
  PushChar1Bcc('T');
  PushChar1Bcc('0');
  PushChar1Bcc('P');
  PushChar1Bcc((ibLine == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO1(1+6*28+2, 4+8+1, 6);
}


void    ReadEnergyU(uchar  ibLine)
{
  InitPop(1);

  mpdbChannelsC[ibLine] = PopDoubleQ();
}


void    ReadEnergyU_SkipLine(uchar  ibLine)
{
  mpdbChannelsC[ibLine] = 0;
}


void    InitHeaderU(void)
{
  if (!UseBounds())
    wBaseCurr = 0;  // ������� �����
  else
  {
    wBaseCurr = mpcwStartAbs16Can[ibDig];
    sprintf(szLo,"   ������ %2u    ",wBaseCurr);
    if (boShowMessages == true) DelayMsg();
  }

  tiDigPrev = tiCurr;
}


void    QueryHeaderU_26(void)
{
  InitPush(0);

  PushChar1Bcc(0x01);
  PushChar1Bcc('R');
  PushChar1Bcc('1');
  PushChar1Bcc(0x02);

  PushChar1Bcc('G');
  PushChar1Bcc('R');
  PushChar1Bcc('A');
  PushChar1Bcc('P');
  PushChar1Bcc((ibMinor == 0) ? 'E' : 'I');

  PushChar1Bcc('(');
  PushChar2Bcc(tiDig.bDay);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bMonth);
  PushChar1Bcc('.');
  PushChar2Bcc(tiDig.bYear);
  PushChar1Bcc(')');

  PushChar1Bcc(0x03);

  BccQueryIO1(2000, 4+16+1, 48);
}


void    QueryHeaderU(void)
{
	HideCurrTime(1);

  if (wBaseCurr == 0)
    tiDig = tiDigPrev;
  else
  {
    ulong dw = DateToDayIndex(tiDigPrev);
    dw -= wBaseCurr;
    tiDig = DayIndexToDate(dw);

    tiDig.bHour   = 23;
    tiDig.bMinute = 30;
  }

  szHi[10] = 'A' + ibMinor;

  ibMinorMax = 2;
  QueryHeaderU_26();
}



void    ReadHeaderU(void)
{
  InitPop(1);

  uchar i;
  for (i=0; i<48; i++)
  {
    mpflBuffCanHou[ibMinor][i] = PopDoubleQ()/2;
  }
}


void    ReadHeaderU_SkipLine(uchar  ibLine)
{
  uchar i;
  for (i=0; i<48; i++)
  {
    mpflBuffCanHou[ibLine][i] = 0;
  }
}



void    MakeDataU(uchar  ibHou)
{
  ShowProgressDigHou();

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<ibMinorMax; i++)
  {
    float fl = mpflBuffCanHou[i][ibHou];
    mpflEngFracDigCan[ibDig][i] += fl;

    uint w = (uint)(mpflEngFracDigCan[ibDig][i]*dbPulse);
    mpwChannels[i] = w;

    mpflEngFracDigCan[ibDig][i] -= (float)w/dbPulse;
  }
}


bool    ReadDataU(void)
{
uchar   j;

  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if (SearchDefHouIndex(tiDig) == 0) return(1);

  if ((tiDig.bDay   == tiCurr.bDay)   &&
      (tiDig.bMonth == tiCurr.bMonth) &&
      (tiDig.bYear  == tiCurr.bYear))
    j = 47-(tiCurr.bHour*2+tiCurr.bMinute/30);
  else
    j = 0;

  ulong dwHouIndex = DateToHouIndex(tiDig);

  uchar i;
  for (i=j; i<48; i++)
  {
    ResetWatchdog();
    MakeDataU(47-i);

    MakeSpecial(tiDig);
    if (MakeStopHou(0) == 0) return(0);

    dwHouIndex--;

    tiDig = HouIndexToDate(dwHouIndex);

    iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;
  }

  NewBoundsAbs16(++wBaseCurr);
  return(1);
}



void    ReadCurrentU(void)
{
  uchar i;
  for (i=0; i<2; i++)
  {
    mpdwBaseDig[i] = mpdbChannelsC[i] * mpdbPulseHou[ibDig];
  }

  MakeCurrent();
}



void    QueryParamU1(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('C');
  PushChar1Bcc('U');
  PushChar1Bcc('R');
  PushChar1Bcc('R');
  PushChar1Bcc('E');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+3*28+2, 15+8+1, 3);
}


void    QueryParamU2(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('V');
  PushChar1Bcc('O');
  PushChar1Bcc('L');
  PushChar1Bcc('T');
  PushChar1Bcc('A');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+3*28+2, 15+8+1, 3);
}


void    QueryParamU3(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('P');
  PushChar1Bcc('O');
  PushChar1Bcc('W');
  PushChar1Bcc('P');
  PushChar1Bcc('P');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+3*28+2, 15+8+1, 3);
}


void    QueryParamU4(void)
{
  PushAddress2Bcc();

  PushChar1Bcc('F');
  PushChar1Bcc('R');
  PushChar1Bcc('E');
  PushChar1Bcc('Q');
  PushChar1Bcc('U');

  PushChar1Bcc('(');
  PushChar1Bcc(')');
  PushChar1Bcc(0x03);

  BccQueryIO2(1+1*28+2, 15+8+1, 1);
}

#endif
