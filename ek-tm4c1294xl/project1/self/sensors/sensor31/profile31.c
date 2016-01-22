/*------------------------------------------------------------------------------
PROFILE31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../memory/mem_digitals.h"
//#include "../memory/mem_current.h"
//#include "../memory/mem_factors.h"
////#include "../memory/mem_realtime.h"
////#include "../memory/mem_energy_spec.h"
////#include "../memory/mem_profile.h"
////#include "../memory/mem_limits.h"
//#include "../serial/ports.h"
//#include "../serial/ports_devices.h"
////#include "../serial/monitor.h"
//#include "../display/display.h"
////#include "../keyboard/time/key_timedate.h"
////#include "../time/timedate.h"
//#include "../time/delay.h"
//#include "../devices/devices.h"
////#include "../devices/devices_time.h"
//#include "../digitals/current/current_run.h"
////#include "../digitals/limits.h"
//#include "../digitals/digitals_messages.h"
////#include "../special/special.h"
//#include "automatic_n31.h"
#include "device31.h"
#include "profile31.h"



#ifndef SKIP_N31

time                    tiProfileN31;

static uint             wBaseCurr, wBaseLast, wOffsCurr;

/*
// ������ ������� ��� �������� �������-9
bit     ReadEnergyAllN31(void)
{
  ReadPackTimeDigN31();

  if ((tiDig.bSecond == 0) &&
      (tiDig.bMinute == 0) &&
      (tiDig.bHour   == 0) &&
      (tiDig.bDay    == 0) &&
      (tiDig.bMonth  == 0) &&
      (tiDig.bYear   == 0)) return(0);

  return(1);
}
*/


// ������� �� ���������� ������
bool    DecIndexN31(void)
{
  if (wBaseLast == wBaseCurr)
  {
    if (wOffsCurr != 0) wOffsCurr--; else return(0);
  }
  else
  {
    if (wOffsCurr != 0) wOffsCurr--; else wOffsCurr = wBaseLast-1;
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

  CodQueryIO(3+13+1, 3+3+1);
}



bool    ReadTopN31(void)
{
  InitPop(3+2);

  wBaseCurr = PopIntLtl()(); // ������ ������� ������
  wBaseLast = PopIntLtl()(); // ���������� �������
  wOffsCurr = wBaseCurr;

  Clear(); sprintf(szLo+2,"%5u:%-5u",wBaseLast,wBaseCurr); DelayInf();

  return( DecIndexN31() );
}


/*
// ������� ������� �� ������ ��������� �������� ����� ��� �������� �������-9
void    QueryHeaderN31(void)
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  if (ExtVersionCod())
    PushCharCod(0x0E);
  else
    PushCharCod(0x19);

  PushCharCod(wOffsCurr / 0x100);
  PushCharCod(wOffsCurr % 0x100);

  if (ExtVersionCod())
    CodQueryIO(3+102+1, 3+3+1);
  else
    CodQueryIO(3+24+1, 3+3+1);
}


// ������ ��������� �������� ����� ��� �������� �������-9
bit     ReadHeaderN31(void)
{
  NoShowTime(1);

  if (ExtVersionCod())
  {
    MakeCRC13InBuff(3, 100);
    if (wCRC != InBuff(103) + InBuff(104)*0x100)
    {
      sprintf(szLo,"   ������: %-4u    ",++iwMajor);
      return(iwMajor < 48);
    }
  }

/ *
  MakeCRC12InBuff(3, 24);
  if (wCRC != 0) { sprintf(szLo," ���������: %-4u   ",++iwMajor); return(iwMajor < 48); }
* /

  ReadPackTimeDigN31();
  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",
          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);

  if ((tiDig.bMinute % 30) != 0) { szLo[4] = '?'; DelayInf(); }


  if (SearchDefHouIndex() == 0) return(++iwMajor < 48);
  iwMajor = 0;


  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // ����� ������ ������ �������������� ������ ������������ �����

  tiAlt = tiCurr;
  dwBuffC = DateToHouIndex();

  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
  HouIndexToDate(dwBuffC);


  ShowProgressDigHou();
  reBuffB = mprePulseHou[ibDig];

  if (ExtVersionCod()) InitPop(3+4+4*6*3);
  for (ibCan=0; ibCan<6; ibCan++)
  {
    if (ExtVersionCod())
      PopRealExtN31();
    else
      PopRealN31();

    mpreEngFracDigCan[ibDig][ibCan] += reBuffA;

    if (tiDig.bMinute % 30 == 0)
    {
      wBuffD = (uint)(mpreEngFracDigCan[ibDig][ibCan]*reBuffB);
      mpwChannels[ibCan] = wBuffD;

      mpreEngFracDigCan[ibDig][ibCan] -= (real)wBuffD/reBuffB;
    }
  }

  MakePrevHou();
  return(MakeStopHou(0));
}
*/

#endif
