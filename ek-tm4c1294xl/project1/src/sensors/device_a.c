/*------------------------------------------------------------------------------
DEVICE_A.C
              
 ������������ ������� � ��������� �������� ���-4��
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_current.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy_spec.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_limits.h"
#include        "../display/display.h"
#include        "../keyboard/key_timedate.h"
#include        "../time/timedate.h"
#include        "../time/calendar.h"
#include        "../time/delay.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "../serial/ports_common.h"
#include        "../devices/devices.h"
#include        "../devices/devices_time.h"
#include        "../digitals/current/current_run.h"
#include        "../digitals/digitals_messages.h"
#include        "../digitals/limits.h"
#include        "../digitals/profile/refill.h"
#include        "../special/special.h"
#include        "../flash/records.h"
#include        "../energy.h"
#include        "device_a.h"



#ifndef SKIP_A

// �������� �������� ������ ��� ��������� ���-4��
bool    ReadAddressA(void)
{
//  return(InBuff(0) == diCurr.bAddress);
  return(1);
}


// �������� ���������� �������� ��� ��������� ���-4��
bool    ReadResultA(void)
{
  TestResult(InBuff(1));
  return(ReadAddressA() && (InBuff(1) == 0));
}



// ������� ������� �� �������� ������ ����� ��� �������� ���-4��
void    QueryOpenA(void)
{
  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(1);      

  if (boEnableKeys != boTrue)
  {
    PushChar('0');                        
    PushChar('0');         
    PushChar('0');
    PushChar('0');
    PushChar('0');
    PushChar('0');
  }
  else
  {
    uchar  i;

    phT = mpphKeys[ibDig]; fAlt = 0;

    for (i=0; i<6; i++)
    {
      if (phT.szNumber[i] == 0) fAlt = 1;

      if (fAlt == 0)
        PushChar(phT.szNumber[i]);
      else  
        PushChar(0);
    }
  }

  QueryIO(2+2, 2+6+2);
}
 


// ������� ������� �� ������ ����������� ������ ��� �������� ���-4��
void    QueryIdA(void)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(5);

  QueryIO(1+2+2, 3+0+2);
}


// ������ ����������� ������ ��� �������� ���-4��
bool    ReadIdA(void)
{
  InitPop(0);
  if (PopChar() != diCurr.bAddress) return 0;
  if (PopChar() != 0) return 0;
  if ((PopChar() != diCurr.bAddress) && (0 != diCurr.bAddress)) return 0;

  return 1;
}



// ������� ������� �� ������ ������� ��� ��������� ���-4��
void    QueryEnergyA(uchar  bTime)
{
  InitPush();

  PushChar(diCurr.bAddress);           
  PushChar(5);                          // ������ ����������� �������

  PushChar(bTime);                      // ��� �������
  PushChar(0);                          // �� ���� �������

  QueryIO(1+16+2, 2+2+2);
}


// ������ ������� ��� �������� ���-4��
void    ReadEnergyA(void)
{
uchar   i;

  InitPop(1);

  for (i=0; i<4; i++)
  {
    coEnergy.mpbBuff[0] = PopChar();
    coEnergy.mpbBuff[1] = PopChar();
    coEnergy.mpbBuff[2] = PopChar();
    coEnergy.mpbBuff[3] = PopChar();

    dwBuffC = coEnergy.dwBuff;
    SetCanLong(mpdwChannelsA, i);
  }

  coEnergy.dwBuff = *PGetCanLong(&mpdwChannelsA, diCurr.ibLine);
}



// ������� ������� �� ��������� ������� ��� �������� ���-4��
void    QueryControlA(void)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(3);      
  PushChar(0x0D);      

  PushChar( ToBCD(tiCurr.bSecond) );
  PushChar( ToBCD(tiCurr.bMinute) );
  PushChar( ToBCD(tiCurr.bHour)   );

  QueryIO(1+1+2, 3+3+2);
}



// ������� ������� �� ��������� ������� ��� �������� ���-4��
void    QueryManageA(void)
{
  InitPush();

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



// ������� ������� �� ����� �������/���� ��� �������� ���-4��
void    QueryTimeA(void)
{
  InitPush();

  PushChar(diCurr.bAddress);       
  PushChar(4);
  PushChar(0);

  QueryIO(1+8+2, 3+0+2);
}


// ������ �������/���� ��� �������� ���-4��
void    ReadTimeAltA(void)
{
  InitPop(1);

  tiAlt.bSecond = FromBCD( PopChar() );
  tiAlt.bMinute = FromBCD( PopChar() );
  tiAlt.bHour   = FromBCD( PopChar() );

  PopChar();

  tiAlt.bDay    = FromBCD( PopChar() );
  tiAlt.bMonth  = FromBCD( PopChar() );
  tiAlt.bYear   = FromBCD( PopChar() );
}



// ������� ������� �� ������ ������� ������� ��� �������� ���-4��
void    QueryTopA(void)
{
  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(8);      
  PushChar(4);      

  QueryIO(1+7+2, 2+1+2);
}


// ������ ������� ������� ��� �������� ���-4��
void    ReadTopA(void)
{
  // ������ �������� ��������
  bCurrHouIndex = FromBCD(InBuff(2))*2 + FromBCD(InBuff(1) & 0x7F)/30;


  // ������ �������� �����
  if (!UseBounds())
  {
    iwMajor = (InBuff(6)*0x100 + InBuff(7)) / 24;
    ResetLimitsAux(ibDig);
  }
  else 
  {
    if (mpboStartCan[ibDig] == boFalse) 
    {
      iwMajor = (InBuff(6)*0x100 + InBuff(7)) / 24;
      if (boShowMessages == boTrue) sprintf(szLo,"  ������ %04X * ",iwMajor);
      ResetLimitsAux(ibDig);
    }
    else 
    {
      iwMajor = mpcwStartAbsCan[ibDig];
      if (boShowMessages == boTrue) sprintf(szLo,"  ������ %04X   ",iwMajor);
      AddDigRecord(EVE_PREVIOUS_TOP);
    }

    if (boShowMessages == boTrue) DelayMsg();
  }

  // ����� ��������� �������� �����
  wBaseCurr = iwMajor*24;


  // ������� ����������� ������
  cwDigHou = 0;

  // ������� ����������� �������
  ibMinor = 0;
}



void    QueryHeaderA(void)
{
  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(3);      

  wBaseLast = iwMajor*24;

  PushChar(wBaseLast / 0x100);      
  PushChar(wBaseLast % 0x100);      

  PushChar(8);      

  QueryIO(1+8+2, 3+3+2);
}


void    QueryHeaderA_Plus(uchar  bSize)
{
  ShowLo(szWaiting); 

  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(5);      

  wBaseLast = iwMajor*24;

  PushChar(wBaseLast / 0x100);      
  PushChar(wBaseLast % 0x100);      

  PushChar(bSize);      

  QueryIO((uint)30*bSize+2, 3+3+2);
}



void    ReadHeaderA(void)
{
  SaveInBuff();
}



void    QueryDataA(void)
{
uint    i;

  InitPush();

  PushChar(diCurr.bAddress);         
  PushChar(6);      
  PushChar(3);      

  i = iwMajor*24 + 8;

  PushChar(i / 0x100);      
  PushChar(i % 0x100);      

  PushChar(16);      

  QueryIO(1+16+2, 3+3+2);
}



bool    ReadDataBlockA(uchar  bOffset, uchar  ibRecord, uchar  ibBlock)
{
  if (++cwDigHou >= 8192/3) return(0);


  tiDig = tiDigPrev;                                    // ���������������...

  tiDig.bMinute = ibRecord*30;                          // ������������ ������ ������ �� �������� �����

  if (SearchDefHouIndex() == 0)                         // �����: ������� ���� �� ������� � ������� ������������ �����
  {
    if (++ibMinor > 48) return(0);
    if (ibMinor > 2) sprintf(szLo," ���������: %-2bu   ",ibMinor);
    
    return(1);
  }
  else ibMinor = 0;


  tiAlt = tiDig;

  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",           // ���������� �����/���� �������� �����
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  ShowProgressDigHou();        
    
  if ((wBaseCurr == wBaseLast) && (GetHouIndex() != bCurrHouIndex))
    return(1);                                          // �����: ������� ���� �� �����

  InitPop(bOffset+ibRecord*8+ibBlock*30);               // ������ ���������� ��������� �� �������: A+,A-,R+,R-

  for (ibCan=0; ibCan<4; ibCan++)        
    mpwChannels[ibCan] = (PopChar()*0x100 + PopChar()) & 0x7FFF;

  MakePrevHou();
  return(MakeStopHou(0));  
}


bool    ReadDataA(void)
{
  NoShowTime(1);                                        // ��������� �������������� ����������� �������
    
  tiDig.bHour  = FromBCD( mpbInBuffSave[1] );           // �����/���� �������� �����
  tiDig.bDay   = FromBCD( mpbInBuffSave[2] );
  tiDig.bMonth = FromBCD( mpbInBuffSave[3] );
  tiDig.bYear  = FromBCD( mpbInBuffSave[4] );
 
  tiDigPrev = tiDig;                                    // ���������...

  if (mpbInBuffSave[1] +                                // �����: ������������ ����������� ����� �������� �����
      mpbInBuffSave[2] +                                
      mpbInBuffSave[3] + 
      mpbInBuffSave[4] + 
      mpbInBuffSave[5] + 
      mpbInBuffSave[6] != mpbInBuffSave[7]) return(1);

  if (mpbInBuffSave[6] != 30) return(1);                // �����: ������������ ������ ��������������
  
  if (ReadDataBlockA(1,0,0) == 0) return(0);
  if (ReadDataBlockA(1,1,0) == 0) return(0);

  return(1);
}



bool    TestDataA_Plus(uchar  ibBlock)
{
  tiDig.bHour  = FromBCD( InBuff((uint)1+ibBlock*30) ); // �����/���� �������� �����
  tiDig.bDay   = FromBCD( InBuff((uint)2+ibBlock*30) );
  tiDig.bMonth = FromBCD( InBuff((uint)3+ibBlock*30) );
  tiDig.bYear  = FromBCD( InBuff((uint)4+ibBlock*30) );

  if ((tiDig.bHour   == 99) &&                          // ������ ���������������
      (tiDig.bDay    == 99) &&
      (tiDig.bMonth  == 99) &&
      (tiDig.bYear   == 99)) 
  {
    ShowLo(szNoDevice); DelayMsg();
    return(0);
  }

  return(1);
}


bool    ReadDataA_Plus(uchar  ibBlock)
{
  NoShowTime(1);                                        // ��������� �������������� ����������� �������
  DelayOff();
        
  tiDig.bHour  = FromBCD( InBuff((uint)1+ibBlock*30) ); // �����/���� �������� �����
  tiDig.bDay   = FromBCD( InBuff((uint)2+ibBlock*30) );
  tiDig.bMonth = FromBCD( InBuff((uint)3+ibBlock*30) );
  tiDig.bYear  = FromBCD( InBuff((uint)4+ibBlock*30) );

  tiDigPrev = tiDig;                                    // ���������...
 
  if (InBuff((uint)1+ibBlock*30) +                      // �����: ������������ ����������� ����� �������� �����
      InBuff((uint)2+ibBlock*30) +                      
      InBuff((uint)3+ibBlock*30) + 
      InBuff((uint)4+ibBlock*30) + 
      InBuff((uint)5+ibBlock*30) + 
      InBuff((uint)6+ibBlock*30) != InBuff((uint)7+ibBlock*30)) return(1);

  if (InBuff((uint)6+ibBlock*30) != 30) return(1);      // �����: ������������ ������ ��������������
  
  if (ReadDataBlockA(12,0,ibBlock) == 0) return(0);
  if (ReadDataBlockA(12,1,ibBlock) == 0) return(0);

  return(1);
}



void    ReadCurrentA(void)
{
uchar   i;

  ReadEnergyA();

  for (i=0; i<4; i++)
  {
    dwBuffC = *PGetCanLong(mpdwChannelsA, i);
    SetCanLong(mpdwBaseDig, i);
  }

  MakeCurrent();
}

#endif

