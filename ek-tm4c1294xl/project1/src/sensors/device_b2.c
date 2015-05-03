/*------------------------------------------------------------------------------
DEVICE_B2.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_current.h"
#include "../memory/mem_factors.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_limits.h"
#include "../display/display.h"
#include "../keyboard/key_timedate.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/decret.h"
#include "../time/delay.h"
#include "../serial/ports_stack.h"
#include "../serial/ports_devices.h"
#include "../serial/ports_common.h"
#include "../devices/devices.h"
#include "../devices/devices_time.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/limits.h"
#include "../special/special.h"
#include "../flash/records.h"
#include "../energy.h"
#include "device_b2.h"



void    ReadTopBNew(void)
{
  // ����� ��������������� �����
  if (!UseBounds()) 
  {
    dwBaseCurr = InBuff(1); dwBaseCurr <<= 12; dwBaseCurr += InBuff(2) << 4;
    ResetLimitsAux(ibDig);
  }
  else 
  {
    if (mpboStartCan[ibDig] == FALSE)
    {
      dwBaseCurr = InBuff(1); dwBaseCurr <<= 12; dwBaseCurr += InBuff(2) << 4;
      if (boShowMessages == TRUE) sprintf(szLo," ������ %05lX * ",dwBaseCurr);
      ResetLimitsAux(ibDig);
    }
    else 
    {
      dwBaseCurr = mpcdwStartAbs32Can[ibDig];
      if (boShowMessages == TRUE) sprintf(szLo," ������ %05lX   ",dwBaseCurr);
      iwMajor = dwBaseCurr % 0x10000; AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == TRUE) DelayMsg();
  }

  // ������ �� ������������ �������
  iwDigHou = 0;

  // ������� ��������� � ����������� ���������
  iwMajor = 0;
}


void    QueryHeaderBNew(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  (dwBaseCurr > 0xFFFF) ? PushChar(0x83) : PushChar(0x03);    

  PushChar((dwBaseCurr % 0x10000) / 0x100);      
  PushChar(dwBaseCurr % 0x100);      

  PushChar(0xFF);      

  QueryIO((uint)(1+15*17+2), 3+3+2);
}


bool    ReadHeaderBNew(uchar  ibBlock, bool  fDelay)
{
	HideCurrentTime(1);                                   // ��������� �������������� ����������� �������
  
  InitPop((uint)(1+(16-ibBlock)*15));

  PopChar();
  tiDig.bHour   = FromBCD(PopChar());                   // �����/���� �������� �����
  tiDig.bMinute = FromBCD(PopChar());
  tiDig.bDay    = FromBCD(PopChar());
  tiDig.bMonth  = FromBCD(PopChar());
  tiDig.bYear   = FromBCD(PopChar());

  if ((tiDig.bHour   == 0) &&                           // ������������ ������ ����
      (tiDig.bMinute == 0) &&
      (tiDig.bDay    == 0) &&
      (tiDig.bMonth  == 0) &&
      (tiDig.bYear   == 0)) 
  {
    if (++iwMajor > 480) return(0);                     // ���� ������� ���� ��������� ������� �����
    sprintf(szLo," ���������: %-4u   ",iwMajor); if (fDelay == 1) DelayOff();

    if (iwDigHou != 0)
    {
       iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;

       ShowProgressDigHou();
       return(MakeStopHou(0));  
    }
    else return(1);
  }


  if ((tiDig.bDay   == tiSummer.bDay) &&
      (tiDig.bMonth == tiSummer.bMonth))
  {
    if ((tiDig.bHour   == 3) && 
        (tiDig.bMinute == 0))
    {
      tiDig.bHour   = 2;  
      tiDig.bMinute = 0;
    }
  }


  sprintf(szLo," %02u    %02u.%02u.%02u", tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0)                        // ������������ �������� ����������� ����
  {
    tiDig.bMinute = (tiDig.bMinute / 30)*30;
    if (SearchDefHouIndex(tiDig) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }

    iwDigHou = (wHOURS+iwDigHou+1)%wHOURS;   
  }
  else if (SearchDefHouIndex(tiDig) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }


  iwMajor = 0;                                          // �������� ������� ����� ��������� ���������� ������


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // ����� ������ ������ �������������� ������ ������������ �����

  ulong dwBuffC = DateToHouIndex(tiCurr);
  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  tiAlt = HouIndexToDate(dwBuffC);


  ShowProgressDigHou();      
  if (fDelay == 1) DelayOff();

  PopChar();

  uchar c;
  for (c=0; c<4; c++)
  {
    uint w = PopChar();
    w     += PopChar()*0x100;

    if (w == 0xFFFF) w = 0;
    mpwChannels[c] = w;
  }

  MakeSpecial();
  return(MakeStopHou(0));
}

