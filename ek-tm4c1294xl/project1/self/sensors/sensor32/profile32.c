/*------------------------------------------------------------------------------
PROFILE32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../special/special.h"
#include "../sensor31/automatic31.h"
#include "automatic32.h"
#include "device32.h"
#include "profile32.h"



#ifndef SKIP_32

time                    tiProfile32;

static uint             wBaseCurr32, wBaseLast32, iwProfile32;

static uint             cwErrors32;



// ������� �� ���������� ������
bool    DecIndex32(void)
{
  if (wBaseLast32 == wBaseCurr32)
  {
    if (iwProfile32 != 0) iwProfile32--; else return false;
  }
  else
  {
    if (iwProfile32 != 0) iwProfile32--; else iwProfile32 = wBaseLast32-1;
  }

  return true;
}



void    QueryTop32(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "������ ������ �� ��������������"

  PushCharCod(0x0A); // "���������"
  PushCharCod(0x00);
  PushCharCod(0x00);

  Query32(3+8+1, 3+3+1);
}



bool    ReadTop32(void)
{
  InitPop(3);

  wBaseLast32 = PopIntBig(); // ���������� �������
  wBaseCurr32 = PopIntBig(); // ������ ������� ������

  MonitorString("\n\n current index "); MonitorIntDec(wBaseCurr32);
  MonitorString("\n\n number "); MonitorIntDec(wBaseLast32);

  iwProfile32 = wBaseCurr32;

  cwErrors32 = 0; // ���������� ������ ������

  Clear(); sprintf(szLo+3,"%4u:%-4u",wBaseLast32,wBaseCurr32); DelayInf();

  return DecIndex32();
}


void    QueryHeader32(void)
{
  MonitorString("\n\n index "); MonitorIntDec(iwProfile32);

  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06); // "������ ������ �� ��������������"

  PushCharCod(0x0B); // "������ ��������"
  PushCharCod(iwProfile32 / 0x100);
  PushCharCod(iwProfile32 % 0x100);

  Query32(3+7+1, 3+3+1);
}



bool    ReadHeader32(void)
{
  HideCurrTime(1);

  if (Checksum32(7) == false)
  {
    MonitorString("\n bad CRC");

    Clear(); sprintf(szLo+3,"������: %-4u",++cwErrors32);
    return (cwErrors32 < 48);
  }


  InitPop(3);
  time ti1 = ReadPackTime32();

  ShowProfileTime(ti1);
  if ((ti1.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }

  MonitorString("\n time "); MonitorTime(ti1); if ((ti1.bMinute % 30) != 0) MonitorString(" ? ");

  ulong dw = DateToHouIndex(ti1);
  if (ti1.bMinute % 30 == 0) dw--;
  time ti2 = HouIndexToDate(dw); // ����� ������ ������ �������������� ������ ������������ �����

  MonitorTime(ti2);


  if (SearchDefHouIndex(ti2) == 0) return (++cwErrors32 < 48);
  cwErrors32 = 0;

  ShowProgressDigHou();


  bool def = IsDefect(ibDig);
  MonitorString("\n def "); MonitorCharDec(def);

  double dbPulse = mpdbPulseHou[ibDig];

  uchar i;
  for (i=0; i<MAX_LINE_N32; i++)
  {
    double db = PopChar3Big32();
    MonitorString("\n value "); MonitorLongDec(db*1000); MonitorString("+"); MonitorLongDec(mpdbEngFracDigCan[ibDig][i]*1000);

    db /= 1000;
    mpdbEngFracDigCan[ibDig][i] += db;

    if (def)
    {
      uint w = (uint)(mpdbEngFracDigCan[ibDig][i]*dbPulse);
      MonitorString("="); MonitorIntDec(w);
      mpwChannels[i] = w;

      mpdbEngFracDigCan[ibDig][i] -= (double)w/dbPulse;
      MonitorString("+"); MonitorLongDec(mpdbEngFracDigCan[ibDig][i]*1000);
    }
    else
    {
      MonitorString(" skip ");
    }
  }

  if (def)
  {
    MonitorString("\n add value");
    MakeSpecial(ti2);
  }
  else
  {
    MonitorString("\n don't add value");
  }

  return MakeStopHou(0);
}

#endif
