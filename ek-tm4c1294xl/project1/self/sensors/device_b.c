/*------------------------------------------------------------------------------
DEVICE_B.C

 ��������-230
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
#include "../digitals/digitals_messages.h"
#include "../digitals/limits.h"
#include "../digitals/profile/refill.h"
#include "../special/special.h"
#include "../flash/records.h"
#include "../energy.h"
#include "device_b.h"



#ifndef SKIP_B

// ������
uchar                   bVersionB1, bVersionB2, bVersionB3;



// �������� �������� ������
bool    ReadAddressB(void)
{
//  return(InBuff(0) == diCurr.bAddress);
  return(1);
}


// �������� ���������� ��������
bool    ReadResultB(void)
{
  TestResult(InBuff(1));
  return(ReadAddressB() && (InBuff(1) == 0));
}



// �������� ������ �����
void    QueryOpenB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(1);         

  PushChar(bKeysLevelB);

  if (boEnblKeys != true)
  {
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
    PushChar(2);
  }
  else
  {
    line ph = mpphKeys[ibDig];
    bool  f = 0;
    uchar i;
    for (i=0; i<6; i++)
    {
      if (ph.szLine[i] == 0) f = 1;

      if (f == 0)
        PushChar(ph.szLine[i] - '0');
      else
        PushChar(0);
    }
  }

  QueryIO(2+2, 2+1+6+2);
}



// ������� ������� �� ������ ������
void    QueryVersionB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(3);

  QueryIO(1+3+2, 3+0+2);
}


// ������ ������
void    ReadVersionB(void)
{
  InitPop(1);

  bVersionB1 = FromBCD( PopChar() );
  bVersionB2 = FromBCD( PopChar() );
  bVersionB3 = FromBCD( PopChar() );
  
  Clear();
  sprintf(szLo+1, "������ %u.%u.%u", bVersionB1, bVersionB2, bVersionB3);
  (boShowMessages == true) ? DelayMsg() : DelayInf();
}


// �������� ������: 7.1.0 � ����
bool    TestVersionB710(void)
{
  return ((uint)100*bVersionB1 + 10*bVersionB2 + bVersionB3 >= 710);
}



// ������� ������� �� ������ ����������� ������
void    QueryIdB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(5);

  QueryIO(1+2+2, 3+0+2);
}


// ������ ����������� ������
bool    ReadIdB(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if ((PopChar() != diCurr.bAddress) && (0 != diCurr.bAddress)) return 0;

  return 1;
}



// ������� ������� �� ������ �������
void    QueryEnergyB(uchar  bTime)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(5);                          // ������ ����������� �������

  PushChar(bTime);                      // ��� �������
  PushChar(0);                          // �� ���� �������

  QueryIO(1+16+2, 2+2+2);
}


// ������ �������
void    ReadEnergyB(void)
{
uchar   i;

  InitPop(1);

  for (i=0; i<4; i++)
  {
    coEnergy.mpbBuff[2] = PopChar();
    coEnergy.mpbBuff[3] = PopChar();
    coEnergy.mpbBuff[0] = PopChar();
    coEnergy.mpbBuff[1] = PopChar();

    if ((coEnergy.mpbBuff[0] == 0xFF) &&
        (coEnergy.mpbBuff[1] == 0xFF) &&
        (coEnergy.mpbBuff[2] == 0xFF) &&
        (coEnergy.mpbBuff[3] == 0xFF)) coEnergy.dwBuff = 0;

    mpdwChannelsA[i] = coEnergy.dwBuff;
  }

  coEnergy.dwBuff = mpdwChannelsA[diCurr.ibLine];
}



// ������� ������� �� ��������� �������
void    QueryControlB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0D);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  QueryIO(1+1+2, 3+3+2);
}


/*
// ������� ������� �� ��������� �������
void    QueryManageB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0C);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  tiAlt = tiCurr;
  PushChar(Weekday()+1);

  PushChar( ToBCD(tiCurr.bDay)   );
  PushChar( ToBCD(tiCurr.bMonth) );
  PushChar( ToBCD(tiCurr.bYear)  );

  tiAlt = tiCurr;
  PushChar(Season());

  QueryIO(1+1+2, 3+8+2);
}
*/


// ����� �������/����
void    QueryTimeB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);       
  PushChar(4);
  PushChar(0);

  QueryIO(1+8+2, 3+0+2);
}


// ������ �������/����
time    ReadTimeB(void)
{
time  ti;

  InitPop(1);

  ti.bSecond = FromBCD( PopChar() );
  ti.bMinute = FromBCD( PopChar() );
  ti.bHour   = FromBCD( PopChar() );

  PopChar();

  ti.bDay    = FromBCD( PopChar() );
  ti.bMonth  = FromBCD( PopChar() );
  ti.bYear   = FromBCD( PopChar() );

  return ti;
}



// ������� ������� �� ������ ������� �������
void    QueryTopB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(8);      
  PushChar(0x13);      

  QueryIO(1+9+2, 2+1+2);
}


// ������ ������� �������
void    ReadTopBOld(void)
{ 
  // ����� ��������������� �����
  if (!UseBounds())
  {
    wBaseCurr = InBuff(1)*0x100 + InBuff(2);
    ResetLimitsAux(ibDig);
  }
  else 
  {
    if (mpboStartCan[ibDig] == false) 
    {
      wBaseCurr = InBuff(1)*0x100 + InBuff(2);
      sprintf(szLo+2,"������ %04X *",wBaseCurr);
      ResetLimitsAux(ibDig);
    }
    else 
    {
      wBaseCurr = mpcwStartAbs16Can[ibDig];
      sprintf(szLo+2,"������ %04X",wBaseCurr);
      iwMajor = wBaseCurr; AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == true) DelayMsg();
  }

  // ������ �� ������������ �������
  iwDigHou = 0;

  // ������� ��������� � ����������� ���������
  iwMajor = 0;

  StartRefill();

#ifdef  DAYS100
  dwTmpPrev = 0;

  wBaseInit = InBuff(1)*0x100 + InBuff(2);
#endif
}



// ������� ������� �� ������ ��������� �������� �����
void    QueryHeaderB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(3);      

  PushChar(wBaseCurr / 0x100);      
  PushChar(wBaseCurr % 0x100);      

  PushChar(15);      

  QueryIO(1+15+2, 3+3+2);
}


// ������� ������� �� ������ ��������� �������� �����
void    QueryHeaderB_Plus(uchar  bSize)
{
  ShowLo(szWaiting); 

  InitPush(0);

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(4);      

  PushChar(wBaseCurr / 0x100);      
  PushChar(wBaseCurr % 0x100);      

  PushChar(bSize);      

  QueryIO((uint)18*bSize+2, 3+3+2);
}



bool    TestHeaderB(uchar  ibBlock)
{
  tiDig.bHour   = FromBCD( InBuff((uint)2+ibBlock*18) );// �����/���� �������� �����
  tiDig.bMinute = FromBCD( InBuff((uint)3+ibBlock*18) );
  tiDig.bDay    = FromBCD( InBuff((uint)4+ibBlock*18) );
  tiDig.bMonth  = FromBCD( InBuff((uint)5+ibBlock*18) );
  tiDig.bYear   = FromBCD( InBuff((uint)6+ibBlock*18) );

  if ((tiDig.bHour   == 99) &&                          // ������ ���������������
      (tiDig.bMinute == 99) &&
      (tiDig.bDay    == 99) &&
      (tiDig.bMonth  == 99) &&
      (tiDig.bYear   == 99)) 
  {
    ShowLo(szNoDevice); DelayMsg();
    return(0);
  }

  return(1);
}


// ������ ��������� �������� �����
bool    ReadHeaderB(uchar  ibBlock, bool  fDelay)
{
  HideCurrTime(1);                                   
  
  tiDig.bHour   = FromBCD( InBuff((uint)2+ibBlock*18) );// �����/���� �������� �����
  tiDig.bMinute = FromBCD( InBuff((uint)3+ibBlock*18) );
  tiDig.bDay    = FromBCD( InBuff((uint)4+ibBlock*18) );
  tiDig.bMonth  = FromBCD( InBuff((uint)5+ibBlock*18) );
  tiDig.bYear   = FromBCD( InBuff((uint)6+ibBlock*18) );

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
    tiDig = HouIndexToDate(DateToHouIndex(tiDig) + 1);
  }
#ifdef  DAYS100
  else if (SearchDefHouIndex2(31*48) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); } 

  if ((wBasePrev > wBaseInit) && (wBaseCurr <= wBaseInit)) return 0;
  wBasePrev = wBaseCurr;
#else
  if (SearchDefHouIndex(tiDig) == 0) { szLo[4] = '?'; if (fDelay == 1) DelayOff(); return(1); }
#endif


  iwMajor = 0;                                          // �������� ������� ����� ��������� ���������� ������


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // ����� ������ ������ �������������� ������ ������������ �����

  ulong dw = DateToHouIndex(tiCurr);
  dw -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  time ti = HouIndexToDate(dw);


  ShowProgressDigHou();      
  if (fDelay == 1) DelayOff();


  uchar c;
  for (c=0; c<4; c++)        
  {
    uint w = InBuff( (uint)8+ibBlock*18+c*2 );
    w     += InBuff( (uint)9+ibBlock*18+c*2 )*0x100;

    if (w == 0xFFFF) w = 0;
    mpwChannels[c] = w;
  }

  MakeRefillWinter(ti);
  MakeSpecial(ti);
  if (boDsblRefill == false) MakeRefill(ti);
  return(MakeStopHou(0));  
}



void    ReadCurrentB(void)
{
  ReadEnergyB();
  float re = mpdbLevel[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i] * re;
  }

  MakeCurrent();
}


#endif
