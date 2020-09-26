/*------------------------------------------------------------------------------
DEVICE_B!C

 ��������-230
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_limits.h"
#include "../../display/display.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/delay.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_common.h"
#include "../../devices/devices.h"
#include "../../devices/devices_time.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals_messages.h"
#include "../../digitals/limits.h"
#include "../../digitals/profile/refill.h"
#include "../../digitals/max_shutdown.h"
#include "../../special/special.h"
#include "../../flash/records.h"
#include "../../energy.h"
#include "device2.h"



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
    line ln = mpphKeys[ibDig];
    bool f = 0;

    uchar i;
    for (i=0; i<6; i++)
    {
      if (ln.szLine[i] == 0) f = 1;

      if (f == 0)
        PushChar(ln.szLine[i] - '0');
      else
        PushChar(0);
    }
  }

  QueryIO(2+2, 2+1+6+2);
}



void    QuerySerialB(void)
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(8);
  PushChar(0);

  QueryIO(1+4+3+2, 3+0+2);
}


ulong   ReadSerialB(void)
{
  InitPop(1);

  ulong dw = PopChar()*1000000;
  dw += PopChar()*10000;
  dw += PopChar()*100;
  dw += PopChar();

  return dw;
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



void    ReadCurrentB(void)
{
  ReadEnergyB();
  double db = mpdbLevel[ibDig];

  uchar i;
  for (i=0; i<4; i++)
  {
    mpdwBaseDig[i] = mpdwChannelsA[i] * db;
  }

  MakeCurrent();
}


#endif
