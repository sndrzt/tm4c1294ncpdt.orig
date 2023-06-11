/*------------------------------------------------------------------------------
profile_interval.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "profile_interval.h"



bool                    boProfileInterval;
cache const             chProfileInterval = {PROFILE_INTERVAL, &boProfileInterval, sizeof(bool)};

uchar                   bProfileIntervalDirect;
cache const             chProfileIntervalDirect = {PROFILE_INTERVAL_DIRECT, &bProfileIntervalDirect, sizeof(uchar)};

uchar                   bProfileIntervalModem;
cache const             chProfileIntervalModem = {PROFILE_INTERVAL_MODEM, &bProfileIntervalModem, sizeof(uchar)};



static uchar            ibProfileIntervalDig;



void    InitProfileInterval(void)
{
  LoadCacheBool(&chProfileInterval, false);
  LoadCacheChar(&chProfileIntervalDirect, 1, 250, 60);
  LoadCacheChar(&chProfileIntervalModem, 1, 250, 120);

  ibProfileIntervalDig = 0xFF;
}


void    ResetProfileInterval(void)
{
  SaveCacheBool(&chProfileInterval, false);
  SaveCacheChar(&chProfileIntervalDirect, 60);
  SaveCacheChar(&chProfileIntervalModem, 120);
}



uchar   GetProfileIntervalTimeout(void)
{
  return diCurr.ibPhone == 0 ? bProfileIntervalDirect : bProfileIntervalModem;
}


bool    IsFinishedProfileInterval(void)
{
  return ((tiCurr.bMinute % 30)*60 + tiCurr.bSecond >= (uint)30*60 - GetProfileIntervalTimeout());
}



uchar   GetProfileIntervalDig(void)
{
  return ibProfileIntervalDig;
}


uchar   GetAndResetProfileIntervalDig(void)
{
  uchar c = ibProfileIntervalDig;
  ibProfileIntervalDig = 0xFF;
  return c;
}


void    SetProfileIntervalDig(uchar  c)
{
  ibProfileIntervalDig = c;
}



void    ShowProfileIntervalInitMesage(void)
{
  ShowLo(" ������������...");
  DelayMsg();
}


void    ShowProfileIntervalBeforeMesage(void)
{
  ShowHi(" ����� �������� ");
  ShowLo("����� ��������� ");
  DelayMsg();

  ShowHi(" ����� �������� ");
  ShowLo(" ����� �������  ");
  DelayMsg();
}


void    ShowProfileIntervalAfterMesage(void)
{
  ShowHi("  �����������   ");
  ShowLo("������ �������� ");
  DelayMsg();

  ShowHi(" ����� �������� ");
  ShowLo(" ����� �������  ");
  DelayMsg();
}
