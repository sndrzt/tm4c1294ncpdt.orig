/*------------------------------------------------------------------------------
PROFILE31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../memory/mem_digitals.h"
//#include "../memory/mem_current.h"
#include "../../memory/mem_factors.h"
////#include "../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
////#include "../memory/mem_limits.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
////#include "../digitals/limits.h"
//#include "../digitals/digitals_messages.h"
#include "../../special/special.h"
#include "automatic31.h"
#include "device31.h"
#include "profile31.h"



#ifndef SKIP_N31

time                    tiProfileN31;

static uint             wBaseCurr31, wBaseLast31, wOffsCurr31;

static uint             iwMajor31;



time    ReadPackTimeN31(void)
{
  InitPop(3);

  uchar d = PopChar();
  uchar c = PopChar();
  uchar b = PopChar();
  uchar a = PopChar();

  time ti;

  ti.bHour   = (c & 0xF8) >> 3;
  ti.bMinute = ((0x100*c+d) >> 5) & 0x3F;
  ti.bSecond = (d & 0x1F) << 1;

  ti.bDay    = (b & 0x1F);
  ti.bMonth  = ((0x100*a+b) >> 5) & 0x0F;
  ti.bYear   = (a & 0xFE) >> 1;

  return ti;
}


// ������� �� ���������� ������
bool    DecIndexN31(void)
{
  if (wBaseLast31 == wBaseCurr31)
  {
    if (wOffsCurr31 != 0) wOffsCurr31--; else return(0);
  }
  else
  {
    if (wOffsCurr31 != 0) wOffsCurr31--; else wOffsCurr31 = wBaseLast31-1;
  }

  return(1);
}



void    QueryTopN31(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "������ ������ �� ��������������"

  PushCharCod(0x0B); // "���������"
  PushCharCod(0x00);
  PushCharCod(0x00);

  QueryN31(3+13+1, 3+3+1);
}



bool    ReadTopN31(void)
{
  InitPop(3+2);

  wBaseCurr31 = PopIntLtl(); // ������ ������� ������
  wBaseLast31 = PopIntLtl(); // ���������� �������

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr31);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast31);

  wOffsCurr31 = wBaseCurr31;

  iwMajor31 = 0; // ���������� ������ ������

  Clear(); sprintf(szLo+2,"%5u:%-5u",wBaseLast31,wBaseCurr31); DelayInf();

  return DecIndexN31();
}


void    QueryHeaderN31(void)
{
  MonitorString("\n\n index "); MonitorIntDec(wOffsCurr31);

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "������ ������ �� ��������������"

  PushCharCod(0x0E); // "������ ��������"
  PushCharCod(wOffsCurr31 / 0x100);
  PushCharCod(wOffsCurr31 % 0x100);

  QueryN31(3+102+1, 3+3+1);
}


bool    ReadHeaderN31(void)
{
  HideCurrTime(1);

//  if (ExtVersionCod())
//  {
//    MakeCRC13InBuff(3, 100);
//    if (wCRC != InBuff(103) + InBuff(104)*0x100)
//    {
//      sprintf(szLo,"   ������: %-4u    ",++iwMajor31);
//      return(iwMajor31 < 48);
//    }
//  }
//
/// *
//  MakeCRC12InBuff(3, 24);
//  if (wCRC != 0) { sprintf(szLo," ���������: %-4u   ",++iwMajor31); return(iwMajor31 < 48); }
//* /
  InitPop(3);
  time ti = ReadPackTimeN31();

  MonitorString("\n time "); MonitorTime(ti);

  ulong dw = DateToHouIndex(ti);
  dw--;
  ti = HouIndexToDate(dw); // ����� ������ ������ �������������� ������ ������������ �����
  MonitorTime(ti);

  sprintf(szLo," %02u    %02u.%02u.%02u", ti.bHour, ti.bDay,ti.bMonth,ti.bYear);

  if ((ti.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }


  if (SearchDefHouIndex() == 0) return(++iwMajor31 < 48);
  iwMajor31 = 0;
//
//
//  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;
//
//  tiAlt = tiCurr;
//  dwBuffC = DateToHouIndex();
//
//  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
//  HouIndexToDate(dwBuffC);


  ShowProgressDigHou();
  double dbPulse = mpdbPulseHou[ibDig];

  InitPop(3+4+4*6*3);

  uchar i;
  for (i=0; i<MAX_LINE_N31; i++)
  {
    float fl = PopFloatN31();
    MonitorString("\n value "); MonitorLongDec(fl);

    fl /= 1000;
    mpdbEngFracDigCan[ibDig][i] += fl;

    if (ti.bMinute % 30 == 0)
    {
      uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
      MonitorString(" "); MonitorIntDec(w);
      mpwChannels[i] = w;

      mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
    }
  }

  MakeSpecial(ti);
  return MakeStopHou(0);
}


#endif
