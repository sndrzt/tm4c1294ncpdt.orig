/*------------------------------------------------------------------------------
DEVICE_P.C

 Elster A1140
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
#include "../digitals/digitals.h"
#include "../digitals/current/current_run.h"
#include "../digitals/limits.h"
#include "../special/special.h"
#include "../hardware/watchdog.h"
#include "../flash/records.h"
#include "automatic_p.h"
#include "device_p.h"
//#include        "main.h"
//#include        "xdata.h"
//#include        "x_digitals.h"
//#include        "ports.h"
//#include        "engine.h"
//#include        "energy.h"
//#include        "essential.h"
//#include        "timedate.h"
//#include        "delay.h"
//#include        "lines.h"
//#include        "display.h"
//#include        "limits.h"
//#include        "digitals.h"
//#include        "sensors.h"
//#include        "special.h"
//#include        "record.h"
//#include        "_timedate.h"


//#define TRANSIT_ENABLED


#ifndef SKIP_P

uchar   FromCharEls(uchar  bT)
{
  if ((bT >= '0') && (bT <= '9'))
    return bT - '0'; 
  else if ((bT >= 'A') && (bT <= 'F'))
    return 10 + bT - 'A';
  else 
    return 0;
}


uchar   ToHalfEls(uchar  bT)
{
  if ((bT >= 0) && (bT <= 9))
    return bT + '0';
  else if ((bT >= 0xA) && (bT <= 0xF))
    return bT + 'A' - 10;
  else
    return 0;
}


uchar   PopChar1Els(void)
{
  return  FromCharEls(PopChar());
}


uint    PopChar4Els(void)
{
uint  w;

  w = PopChar1Els()*0x10 + PopChar1Els();
  w <<= 8;   
  w += PopChar1Els()*0x10 + PopChar1Els();
  return w;
}


void    PushCharEls(uchar  bT)
{
  PushChar(szDigits[bT / 0x10]);
  PushChar(szDigits[bT % 0x10]);
}


void    QueryStopP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('B');
  PushChar('0');
  PushChar(0x03);

#ifdef TRANSIT_ENABLED	
  ElsQueryIO(100, 4+1);
  Delay(5000);
#else
  ElsQueryIO(0, 4+1);
  Delay(300);
#endif
}


void    QueryCloseP(void)
{
  uchar i;
  for (i=0; i<3; i++)
    QueryStopP();
}


void    QueryOpenP(void)
{
uchar i;

  QueryStopP();

  InitPush(0);
  PushChar('/');
  PushChar('?');

  i = diCurr.bAddress;

  PushChar(szDigits[ i/100 ]);
  PushChar(szDigits[ (i%100) / 10 ]);
  PushChar(szDigits[ i%10 ]);

  PushChar('!');
  PushChar(0x0D);
  PushChar(0x0A);

#ifdef  TRANSIT_ENABLED	
  QueryT(23, 6+2, 1);
#else
  Query(23, 6+2, 1);
#endif
}


void    QueryCorrectP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('W');
  PushChar('1');
  PushChar(0x02);

  PushChar('8');
  PushChar('6');
  PushChar('2');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushCharEls(iwMajor / 0x100);
  PushCharEls(iwMajor % 0x100);
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1, 4+13+1);
}


void    QueryTimeP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('8');
  PushChar('6');
  PushChar('1');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushChar('0');
  PushChar('7');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+17+1, 4+11+1);
}


time    ReadTimeP(void)
{
  InitPop(2);

  time tiAlt;

  tiAlt.bSecond = PopChar1Els()*10 + PopChar1Els();
  tiAlt.bMinute = PopChar1Els()*10 + PopChar1Els();
  tiAlt.bHour   = PopChar1Els()*10 + PopChar1Els();

  uint w = PopChar4Els();

  tiAlt.bDay    = FromBCD((w & 0x3F00) / 0x100);
  tiAlt.bMonth  = FromBCD(w & 0x001F);
    
  PopChar();
  PopChar();
  tiAlt.bYear   = PopChar1Els()*10 + PopChar1Els();

  return tiAlt;
}


void    QueryEngAbsP(uchar  bPart)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('5');
  PushChar('0');
  PushChar('7');
  PushChar('0');
  PushChar('0');
  (bPart == 0) ? PushChar('1') : PushChar('2');
  PushChar('(');
  PushChar('4');
  PushChar('0');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+131+1, 4+11+1);
}


void    ReadEngAbsP(uchar  bPart)
{
uchar i,j;

  InitPop(2);
  for (i=0; i<8; i++)
  {
    double dbA = 0;
    double dbB = 1;
    for (j=0; j<8; j++)
    {
      dbA += dbB*(PopChar1Els()*10 + PopChar1Els());
      dbB *= 100;
    }  
    mpdbChannelsC[bPart*8 + i] = dbA/1e6;
  }

  InitPop(2);
  for (i=0; i<8; i++)
  {
    mpdwChannelsB[bPart*8 + i] = 0;
    ulong dw = 1;
    for (j=0; j<8; j++)
    {
      mpdwChannelsB[bPart*8 + i] += dw*(PopChar1Els()*10 + PopChar1Els());
      dw *= 100;
    }  
  }
}


void    ReadEngAbsP_RD(void)
{
uchar i,j;

  InitPop(4);
  for (i=0; i<22; i++)
  {
    double dbA = 0;
    double dbB = 1;
    for (j=0; j<8; j++)
    {
      uchar k = PopChar();
      dbA += dbB*((k / 0x10)*10 + (k % 0x10));
      dbB *= 100;
    }  
    mpreChannelsB[i] = dbA/1e6;
  }
}


void    QueryTransP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('6');
  PushChar('1');
  PushChar('6');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushChar('0');
  PushChar('8');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+19+1, 4+11+1);
}


void    ReadTransP(void)
{
  InitPop(2);

  ulong dw = (PopChar4Els() << 16) + PopChar4Els();
  float flA = dw;

  dw = (PopChar4Els() << 16) + PopChar4Els();
  float flB = dw;

  dbKtrans = flA / flB;
}


void    QueryModeP(void)
{
  InitPush(0);
  PushChar(0x06);
  PushChar('0');
  PushChar('5');
  PushChar('6');

  PushChar(0x0D);
  PushChar(0x0A);

#ifdef  TRANSIT_ENABLED	
  QueryT(1+22+1, 4+2, 1);
#else
  Query(1+22+1, 4+2, 1);
#endif
}


void    QueryPasswordP(void)
{
uchar i,a,b;

  if (boEnblKeys != true)
    for (i=0; i<8; i++) mpbPasswordEls[i] = '0';
  else 
  {
    phT = mpphKeys[ibDig];
    for (i=0; i<8; i++) mpbPasswordEls[i] = phT.szNumber[i];  
  }

  InitPop(0);
  for (i=0; i<16; i++) mpbRandomEls[i] = InBuff(i+5);

  for (i=0; i<8; i++)
  {
    a = FromCharEls(mpbRandomEls[2*i]);
    b = FromCharEls(mpbRandomEls[2*i+1]);
    mpbEls1[i] = a*0x10 + b;
    mpbEls2[i] = mpbEls1[i] ^ mpbPasswordEls[i];
  }

  mpbEls2[8] = 0;
  
  for (i=0; i<8; i++)
  {
    a = (mpbEls2[i] + mpbEls2[i+7]) % 0x100;
    mpbEls2[i+8] = a;
    mpbResultEls[i*2] = ToHalfEls((a & 0xF0) >> 4);
    mpbResultEls[i*2+1] = ToHalfEls(a & 0x0F);
  }

  InitPush(0);
  PushChar(0x01);
  PushChar('P');
  PushChar('2');
  PushChar(0x02);

  PushChar('(');
  for (i=0; i<16; i++) PushChar(mpbResultEls[i]);
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1, 4+19+1);
  cwTimeLockoutP = 0;
}

void    QueryRepasswordP(void)
{  
uchar i;

  InitPush(0);
  PushChar(0x01);
  PushChar('P');
  PushChar('2');
  PushChar(0x02);

  PushChar('(');
  for (i=0; i<16; i++) PushChar(mpbResultEls[i]);
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1, 4+19+1);
  cwTimeLockoutP = 0;
}

void    QueryRegisterP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('7');
  PushChar('7');
  PushChar('7');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushChar('0');
  PushChar('2');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+7+1, 4+11+1);
}


void    ReadRegisterP(void)
{
uchar i;
uint  w;

  InitPop(2);
  w = PopChar4Els();

  for (i=0; i<4; i++) mpbMappingEls[i] = 0xFF;

  ibMinorMax = 0;
  for (i=0; i<16; i++)
    if ((w & (uint)(1 << i)) != 0) 
    {
      if (ibMinorMax < 4) mpbMappingEls[ibMinorMax] = i;
      ibMinorMax++; 
    }
  
  if (ibMinorMax > 4) ibMinorMax = 4;
//  if (ibMinorMax == 0) { sprintf(szLo, "������ �� ������"); DelayMsg(); }
}


void    Setup1P(void)
{
  if (!UseBounds())
    ibMinor = 1;
  else 
  {
    if (mpboStartCan[ibDig] == false) 
    {
      ibMinor = 1;
      if (boShowMessages == true) sprintf(szLo," ������ ������  ");
    }
    else 
    {
      ibMinor = mpcwStartAbs16Can[ibDig];
      if (boShowMessages == true) sprintf(szLo,"  �����������   ");
    }

    if (boShowMessages == true) DelayInf();
  }

  bFlagElsPrev = 0;
  iwDigHou = 0xFFFF;

  boTimeChangeP = false;

  dwHouIndexP1 = 0;
  dwHouIndexP2 = 0;
}


void    QuerySetValueP(void)
{ 
  Clear();
  if (boShowMessages == true) { sprintf(szLo+2,"������: -%-2bu",ibMinor); DelayInf(); }

  bFlagElsCurr = 0;
  bFirstEls = 0;
  cwDigHou = 0;

  InitPush(0);
  PushChar(0x01);
  PushChar('W');
  PushChar('1');
  PushChar(0x02);

  PushChar('5');
  PushChar('5');
  PushChar('1');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushCharEls(ibMinor % 0x100);
  PushCharEls(ibMinor / 0x100);
  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar('0');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1, 4+17+1);
}


void    QueryGetValueP(void)
{
  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('5');
  PushChar('5');
  PushChar('1');
  PushChar('0');
  PushChar('0');
  PushChar('1');
  PushChar('(');
  PushChar('0');
  PushChar('2');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+7+1, 4+11+1);
}


void    ReadGetValueP(void)
{
  InitPop(2);
  wBaseCurr = 1;
  wBaseLast = PopChar4Els();

  pbPutEls = 0;
  pbGetEls = 0;
  cbSizeEls = 0;
}


void    QueryProfileP(void)
{
uint  w;

  Clear();
  if (boShowMessages == true) sprintf(szLo+1,"����: %u - %u",wBaseCurr,wBaseLast);

  InitPush(0);
  PushChar(0x01);
  PushChar('R');
  PushChar('1');
  PushChar(0x02);

  PushChar('5');
  PushChar('5');
  PushChar('0');

  w = wBaseCurr;
  PushChar(szDigits[ w/0x100 ]);
  PushChar(szDigits[ (w%0x100) / 0x10 ]);
  PushChar(szDigits[ w%0x10 ]);

  PushChar('(');
  PushChar('4');
  PushChar('0');
  PushChar(')');
  PushChar(0x03);

  ElsQueryIO(1+131+1, 4+11+1);
}


void   SkipByteEls(void) 
{
  pbGetEls = ++pbGetEls % 128;
  cbSizeEls--;
}


uchar   GetByteEls(void) 
{
uchar i;

  i = mpbBuffEls[pbGetEls];
  pbGetEls = ++pbGetEls % 128;
  cbSizeEls--;

  return i;
}


bool   GetConfig(uchar  bT)
{
uchar i,j;

  switch (bT) 
  {
    case 0xE4: j = 8; break;
    case 0xE5: j = 5; break;
    case 0xE6: j = 5; break;
    case 0xE8: j = 8; break;
    case 0xEA: j = 5; boTimeChangeP = true; dwHouIndexP2 = dwHouIndexP1; break;
    case 0xEB: j = 5; break;
    case 0xED: j = 5; break;
    default:   j = 5; 
  }

  if (j > cbSizeEls) return 1;
  
  SkipByteEls();  // status

  coTrue.mpbBuff[3] = GetByteEls();
  coTrue.mpbBuff[2] = GetByteEls();
  coTrue.mpbBuff[1] = GetByteEls();
  coTrue.mpbBuff[0] = GetByteEls();

  if (bFlagElsCurr == 0)
  {
    bFlagElsCurr = 1;
    bCodeElsCurr = bT;
    dwStampElsCurr = coTrue.dwBuff;
  } 

  bBreakEls = 0;
  if (bFlagElsPrev == 1)
  {
    if ((bCodeElsPrev == bT) && (dwStampElsPrev == coTrue.dwBuff))
      bBreakEls = 1;
  }

  dwBuffC = coTrue.dwBuff - (ulong)(23*365 + 7*366)*24*60*60;
  SecIndexToDate(dwBuffC);

  dwHouIndex = DateToHouIndex();


  for (i=0; i<j-5; i++) SkipByteEls();
  
  return 0;
}


void  Setup2P(void) 
{
  bFlagElsPrev = 1;
  bCodeElsPrev = bCodeElsCurr;
  dwStampElsPrev = dwStampElsCurr;
}


bool   GetProfile(void)
{
uchar i,j;

  if (1 + 3*ibMinorMax > cbSizeEls) return 1;

  SkipByteEls();  // status

  uchar ibCan;
  for (ibCan=0; ibCan<ibMinorMax; ibCan++)
  {
    dwBuffC = 0;
    i = GetByteEls();
    dwBuffC += ((i & 0xF0) >> 4) * (ulong)10000;
    dwBuffC += (i & 0x0F) * 1000;
    i = GetByteEls();
    dwBuffC += ((i & 0xF0) >> 4) * 100;
    dwBuffC += (i & 0x0F) * 10;
    i = GetByteEls();
    dwBuffC += ((i & 0xF0) >> 4);

    reBuffA = 1;
    j = i & 0x0F;
    for (i=0; i<j; i++) reBuffA *= 10;
    reBuffA *= dwBuffC;

    mpreChannelsA[ibCan] = reBuffA/2e6;
  }

  cwDigHou++;

  dwHouIndexP1 = dwHouIndex;
  if ((boTimeChangeP == true) && (dwHouIndexP1 > dwHouIndexP2))
  {
     boTimeChangeP = false;
  }

  HouIndexToDate(dwHouIndex++);
  sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu ", tiAlt.bHour,tiAlt.bMinute, tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear);

  tiDig = tiAlt;
  if (SearchDefHouIndex() == 1) 
  {
    iwMajor = 0;
    if (bFirstEls == 0) { ShowProgressDigHou(); bFirstEls = 1; }

    double dbPulse = mpdbPulseHou[ibDig];
    for (ibCan=0; ibCan<ibMinorMax; ibCan++)        
    {
      reBuffA = mpreChannelsA[ibCan];
      mpflEngFracDigCan[ibDig][ibCan] += reBuffA;

      uint w = (uint)(mpflEngFracDigCan[ibDig][ibCan]*dbPulse);
      mpwChannels[ibCan] = w;

      mpflEngFracDigCan[ibDig][ibCan] -= (float)w/dbPulse;
    }

    if (!IsDefect(ibDig) && (boTimeChangeP == true))
    {
      szLo[0] = '!';

      LoadCurrDigital(ibDig);
      for (ibCan=0; ibCan<bCANALS; ibCan++)
      {
        LoadPrevDigital(ibCan);
        if (CompareCurrPrevLines() == 1)
        {
          mpwImpHouCanSpec[ibCan] += mpwChannels[diPrev.ibLine];
          mpwChannels[diPrev.ibLine] = 0;
        }
      }

      SaveImpHouSpec(0,iwDigHou); 

      AddDigRecord(EVE_DEVICE_P_DEFECT);
      boRecalcCurr = true;      
    }

    tiAlt = tiDig;
    MakePrevHou();
  } 
  else 
  { 
    iwMajor++;
    szLo[15] = '?'; DelayOff(); 
  }

  return 0;
}


void    ReadProfileP(void)
{
uchar i;

  HideCurrTime(1);

  InitPop(2);
  for (i=0; i<64; i++) 
  {
    mpbBuffEls[pbPutEls] = PopChar1Els()*0x10 + PopChar1Els();
    pbPutEls = ++pbPutEls % 128;
  }  

  cbSizeEls += 64;

  while (1)
  {
    if (cbSizeEls == 0) break;

    i = mpbBuffEls[pbGetEls];
    if ((i & 0xF0) == 0xE0) 
    {
      if (GetConfig(i) == 1) break;
      if (bBreakEls == 1) break;
    } 
    else 
    {
      if ((i & 0x80) == 0) 
      {
        if (GetProfile() == 1) break;
      }  
      else
        SkipByteEls();
    }  
  }  
}


bool    BreakP(void)
{
  if (cwDigHou == 0)
  {
    sprintf(szLo," ���������: %-2bu  ",++cbDigDay); DelayInf();
    if (cbDigDay >= 10) 
      return 1;
  }
  else cbDigDay = 0;
  return 0;
}


void    ReadCurrentP(void)
{
  double dbPulse = mpdbPulseMnt[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    if (mpbMappingEls[i] >= 16) 
    {
      dwBuffC = 0;
    }
    else
    {
      dwBuffC = mpdwChannelsB[mpbMappingEls[i]];
      dwBuffC /= (1e6/dbPulse);
    } 
    mpdwBaseDig[i] = dwBuffC;
  }

  MakeCurrent();
}



bool    QueryEnergyP_Full(uchar  bPart)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngAbsP(bPart);

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(70+bPart);

  ReadEngAbsP(bPart);

  return(1);
}


#endif

