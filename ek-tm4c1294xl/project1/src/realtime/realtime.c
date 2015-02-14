/*------------------------------------------------------------------------------
REALTIME.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_energy.h"
#include        "../decret.h"
#include        "../energy.h"
#include        "../keyboard/key_timedate.h"


/*
// ������� �������� �� �������� ����� � ������� �����
bit                     fSeason;

// �������� �������� �� �������� ����� ��� ����������� ���������
bit                     fSummer,fWinter;
*/
// ������� ������ � �������� ������
bool                    fActive;
/*
// �������� ��� ������� ��������� �����
bit                     fProfile,fCurrent;

// ������� ������ ������� �� ���������������� ������
bit                     fSendAT;

        

void    ClearNewTime(void)
{
  boNewSec = boNewMin = boNewMnt = boNewHou = boNewDay = boNewMon = boNewYea = boTrue;
}



uchar   PrevSoftMnt(void)
{
  if (ibSoftMnt > 0) return(ibSoftMnt - 1);
  else               return(bMINUTES-1);
}



uchar   PrevSoftHou(void)
{
  if (ibSoftHou > 0) return(0);
  else               return(1);
}


uint    PrevHardHou(void)
{
  if (iwHardHou > 0) return(iwHardHou - 1);
  else               return(wHOURS-1);
}



uchar   PrevSoftDay(void)
{
  if (ibSoftDay > 0) return(0);
  else               return(1);
}


uchar   PrevHardDay(void)
{
  if (ibHardDay > 0) return(ibHardDay - 1);
  else               return(bDAYS-1);
}



uchar   PrevSoftMon(void)
{
  if (ibSoftMon > 0) return(0);
  else               return(1);
}


uchar   PrevHardMon(void)
{
  if (ibHardMon > 0) return(ibHardMon - 1);
  else               return(bMONTHS-1);
}



uchar   PrevSoftTim(void)
{
  if (ibSoftTim > 0) return(0);
  else               return(1);
}

/ *
uint    PrevHardTim(void)
{
  if (iwHardTim > 0) return(iwHardTim - 1);
  else               return(wTIMES-1);
}
* /


// ���������� ������ �������� ��������
uchar   GetHouIndex(void)
{
  return(tiCurr.bHour*2 + tiCurr.bMinute/30);
}


// ���������� ������ �� ������ ������� ��������� ����� �����
uint    PrevDayIndex(uchar  bDay)
{
uchar   i;
uint    j;

  // ������ �� ������ ������� ������� �����
  j = (wHOURS+iwHardHou-GetHouIndex()) % wHOURS;

  // ������� �� ������ �������� ����� �����
  for (i=0; i<bDay; i++) j = (wHOURS+j-48) % wHOURS;

  // ������ �� ������ ������� ��������� �����
  return(j);
}



void    MakeCurrHouCan(void)
{
uchar   i;

  for (i=0; i<bCANALS; i++)
  {
    if ((GetDigitalDevice(i) != 0) && (IsSpecCurrent(GetDigitalDevice(i)) == 0)) 
      SetCanInt(mpwImpHouCan[ibSoftHou], i, 0xFFFF); 
  }
}


void    MakeCurrTimPar(void)
{
}



// ��������� �������� �� ��������� ��������
void    ProcessNextTim(void)
{
  SaveParTim(iwHardTim,ibSoftTim);

  if (++iwHardTim >= wTIMES) iwHardTim = 0;
  if (++ibSoftTim >= 2)      ibSoftTim = 0; 

  memset(&mpreParBuff[ibSoftTim], 0xFF, sizeof(real)*wPARAMS);

  if (cwParamTim < wTIMES-1) cwParamTim++;

  MakeCurrTimPar(); 
}
*/

// ��������� �������� �� ��������� ��� ������
void    ProcessNextMnt(void)
{
  memset(&mpwImpMntCan[(ibSoftMnt+1) % bMINUTES], 0, sizeof(uint)*bCANALS); // TODO Init/Reset mpwImpMntCan

//  ET0 = 0;
//  memcpy(&mpwImpCurrMntCan, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
//  if (++ibSoftMnt >= bMINUTES) ibSoftMnt = 0;
//  ET0 = 1;

  MakeImpulse();

  cdwMinutes3++;
}


// ��������� �������� �� ��������� ��� ������
void    ProcessNextMntSpec(void)
{
  memset(&mpwImpMntCan[(ibSoftMnt+1) % bMINUTES], 0, sizeof(uint)*bCANALS); // TODO Init/Reset mpwImpMntCan

//  ET0 = 0;
//  memcpy(&mpwImpCurrMntCan, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
//  if (++ibSoftMnt >= bMINUTES) ibSoftMnt = 0;
//  ET0 = 1;

  MakeImpulseSpec();

  cdwMinutes3++;
}


/*
// ��������� �������� �� ��������� �������
void    ProcessNextHou(void)
{
  // ���������: ������ ������ ��������
  InfoTime();

  // ������ ���������� �������� �� ������� ����� � ����� 
  MakeAllMaxPowNow();

  // ������ �������� ������ ���������
  MakeLimits();

  SaveImpHou(0,iwHardHou,ibSoftHou);

  if (++iwHardHou >= wHOURS) iwHardHou = 0;
  if (++ibSoftHou >= 2)      ibSoftHou = 0;

  memset(&mpwImpHouCan[ibSoftHou], '\0', sizeof(uint)*bCANALS);

  MakeCurrHouCan();
  NextHouDiagram();
  NextHouLimitsAux();
  IOControl();

  if (boQuickParam == boFalse) ProcessNextTim();
  / *
  if ((fActive == 1) && (GetFlashStatus() != 0))
  {
    ShowHi(szAlarm); 
    ShowLo(szBadFlash); LongBeep();

    NoShowTime(1);
  }
  * /
  cdwMinutes30++;
}
*/


void    ProcessTime(void)
{
  // ������� �� ��������� �������
  if (tiCurr.bSecond != tiPrev.bSecond)
  {
    cdwSeconds++;
  }


  // ������� �� ��������� ������
  if (tiCurr.bMinute != tiPrev.bMinute)
  {
    cdwMinutes1++;

    if ((fActive == 1) && (enGlobal == GLB_WORK))
    {
      if (cbShowCurrentTime >= 2)
				ShowCurrentTime();
      else 
        cbShowCurrentTime++;  
    }
  }


  // ������� �� ��������� ��� ������
  if ((tiCurr.bMinute % 3 == 0) && (tiPrev.bMinute % 3 != 0))
  {
    ProcessNextMnt();
  }


  // ������� �� ��������� �������
  if ((tiCurr.bMinute % 30 == 0) && (tiPrev.bMinute % 30 != 0))
  {/*
    // ���� ����������� ������ ��������
    boNewHou = boTrue;

    // ���������� �������� DTR
    if (fActive == 1) RunDTR();

    // ������ ������ �������� ��������� �� ���������
    if (fActive == 1) fProfile = 1;

    if ((tiCurr.bDay   == tiSummer.bDay)   &&
        (tiCurr.bMonth == tiSummer.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 0))
    {
      cbSummer++;

      if (fActive == 1)
      {
        tiCurr.bHour = 3;
        tiSetRTC = tiCurr;
        SetCurrTimeDate();
      }
      else fSummer = 1;

      fSeason = 1;

      ProcessNextHou();
      ProcessNextHou();
      ProcessNextHou();
    }
    else
    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth) &&
        (tiCurr.bHour  == 3)               && (fSeason == 0))
    {
      cbWinter++;

      if (fActive == 1)
      {
        tiCurr.bHour = 2;
        tiSetRTC = tiCurr;
        SetCurrTimeDate();
      }
      else fWinter = 1;

      fSeason = 1;
    }
    else
    if ((tiCurr.bDay   == tiWinter.bDay)   &&
        (tiCurr.bMonth == tiWinter.bMonth) &&
        (tiCurr.bHour  == 2)               && (fSeason == 1))
      { }
    else
      ProcessNextHou();*/
  }


  // ������� �� ��������� �����
  if (tiCurr.bDay != tiPrev.bDay)
  {/*
    // ���� ����������� ����� �����
    boNewDay = boTrue;
    NextDayExtended4();
    NextDayExtended5();
    NextDayExtended6();
    NextDayExtended7();

    // ���������������� ������
    ResetSendAT();

    // ��������� �������� �������� �� �������� ������� � ������� �����
    fSeason = 0;

    // ������� ��������� ��������� �� �������
    MakeCounters();

    // ������� �������� �������� ������� ��� ������� �������� ������� ����� ��� ���� ������ (��� �������� � �������)
    MakeAllCurrTariffs();

    SaveImpDay(0,ibHardDay,ibSoftDay);
    SavePowDay(0,ibHardDay,ibSoftDay);

    if (++ibHardDay >= bDAYS) ibHardDay = 0;
    if (++ibSoftDay >= 2)     ibSoftDay = 0;

    memset(&mpimDayCan[ibSoftDay], '\0', sizeof(impulse)*bCANALS);
    memset(&mppoDayGrp[ibSoftDay], '\0', sizeof(power)*bGROUPS);

    // ��������� ����� �� ������
    tiAlt = tiCurr;
    MakeDefectDay(0);

    // ��������� ������������� �� ������
    NextDayDef();

    EnableAnswer();
    cwDays++;*/
  }


  // ������� �� ��������� �����
  if (tiCurr.bMonth != tiPrev.bMonth)
  {/*
    SaveImpMon(0,ibHardMon,ibSoftMon);
    SavePowMon(0,ibHardMon,ibSoftMon);
    SaveCntMon(0,ibHardMon,ibSoftMon);

    if (++ibHardMon >= bMONTHS) ibHardMon = 0;
    if (++ibSoftMon >= 2)       ibSoftMon = 0;

    memset(&mpimMonCan[ibSoftMon],    '\0', sizeof(impulse)*bCANALS);
    memset(&mppoMonGrp[ibSoftMon],    '\0', sizeof(power)*bGROUPS);
    memset(&mpreCntMonCan[ibSoftMon], '\0', sizeof(real)*bCANALS);

    NextMonExtended4();
    NextMonExtended4T();
    NextMonExtended6();

    // ��������� ����� �� �������
    tiAlt = tiCurr;
    MakeDefectMon(0);

    // ���������� ������� ��������� �� ���������� �����
    memcpy(&mpcwPosValuePrev, &mpcwPosValueCurr, sizeof(mpcwPosValuePrev));
    memcpy(&mpcwNegValuePrev, &mpcwNegValueCurr, sizeof(mpcwNegValuePrev));
    memcpy(&mpcwPosCountPrev, &mpcwPosCountCurr, sizeof(mpcwPosCountPrev));
    memcpy(&mpcwNegCountPrev, &mpcwNegCountCurr, sizeof(mpcwNegCountPrev));

    // ��������� ������� ��������� �� ������� �����
    memset(&mpcwPosValueCurr, 0, sizeof(mpcwPosValueCurr));
    memset(&mpcwNegValueCurr, 0, sizeof(mpcwNegValueCurr));
    memset(&mpcwPosCountCurr, 0, sizeof(mpcwPosCountCurr));
    memset(&mpcwNegCountCurr, 0, sizeof(mpcwNegCountCurr));

    // ��������� ������� �����������/���������� �������� �������� �������� �� ���������� �����
    boPublicPrev = boPublicCurr;

    // ������� ��������� ��������� �� �������
    MakeCounters();

    // ��������� ������������� �� �������
    NextMonDef();

    cwMonths++;*/
  }


  // ������� �� ��������� ���
  if (tiCurr.bYear != tiPrev.bYear)
  {
    cwYears++;

    MakeDecret(); // TODO persist MakeDecret
  }
}


/*
// ��������� ������������� ��������
void    MakeNexttime(void)
{
  ibSoftMnt = 0;

  ibSoftHou = 0;
  iwHardHou = 0;

  ibSoftDay = 0;
  ibHardDay = 0;

  ibSoftMon = 0;
  ibHardMon = *PGetCurrTimeDate()->bMonth - 1;

  ibSoftTim = 0;
  iwHardTim = 0;

  cbSummer = 0;
  cbWinter = 0;

  ET0 = 0;
  memset(&mpwImpMntCan[ibSoftMnt], '\0', sizeof(uint)*bCANALS);
  ET0 = 1;

  MakeCurrHouCan();

  MakeCurrTimPar();

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (GetDigitalDevice(ibCan) == 0)
    {
      reBuffA = *PGetCanReal(mpreCount,ibCan);
      SetCanReal(mpreCntMonCan[ ibSoftMon ],ibCan);    
    }    
  }
}



// ��������� ��������� ��������� � ����������� �������
bit     NexttimeOff(void)
{
uchar   i;

  cbWaitQuery = 0;

  fProfile = 0;
  fCurrent = 0;

  fSeason  = 0;

  if (GetLabelXDATA() == 0)
    return(1);
  else
  {
    // ����������� ������� ��������� �������
    cbPowerOn++;
    // ��������� ����� ���������� �������
    tiPowerOff = tiCurr;

    i = 0;
    while (1)
    {
      ResetWDT();

      // ������ �������� �������
      tiKey = *PGetCurrTimeDate();
      // �������� ������� ��� ������������ ���������
      tiCurr.bSecond = tiKey.bSecond;
       
      // ��������� ����� ��������� �������
      tiPowerOn = tiKey;

      if (memcmp(&tiCurr, &tiKey, sizeof(time)) == 0)
        return(1);

      // ������� ����� � ���������� � ������
      if (++tiCurr.bMinute >= 60)
      {
        tiCurr.bMinute = 0;
        if (++tiCurr.bHour >= 24)
        {
          tiCurr.bHour = 0;

          // ���������� ����� ���������� �������
          if (++i > 30) return(0);

          tiAlt = tiCurr;
          if (++tiCurr.bDay > DaysInMonth())
          {
            tiCurr.bDay = 1;
            if (++tiCurr.bMonth > 12)
            {
              tiCurr.bMonth = 1;
              tiCurr.bYear++;
            }
          }
        }
      }

      // ��������� ��������� �������
      ProcessTime();
/ *
      sprintf(szHi,"����   %02bu.%02bu.%02bu",
              tiCurr.bDay,   
              tiCurr.bMonth,
              tiCurr.bYear);

      sprintf(szLo,"�����  %02bu:%02bu:%02bu",
              tiCurr.bHour,
              tiCurr.bMinute,
              tiCurr.bSecond);
* /
      sprintf(szHi," %02bu:%02bu %02bu.%02bu.%02bu ",
                     tiCurr.bHour,
                     tiCurr.bMinute,
                     tiCurr.bDay,   
                     tiCurr.bMonth,
                     tiCurr.bYear);

      sprintf(szLo," %02bu:%02bu %02bu.%02bu.%02bu ",
                     tiKey.bHour,
                     tiKey.bMinute,
                     tiKey.bDay,   
                     tiKey.bMonth,
                     tiKey.bYear);

      // ������ ���������� �������
      tiPrev = tiCurr;
    }
  }
}



// ��������� ��������� ��������� � ����������� ������� � ���������� �� �������� �����
void    InitNexttime(void)
{
  if (GetLabelRTC() == 0) TestError(szBadRTC1);

  PGetCurrTimeDate();
  if (TrueCurrTimeDate() == 0) // TestError(szBadRTC2);
  {
    ShowHi(szAlarm); 
    ShowLo(szBadRTC2); LongBeep(); DelayMsg();
    return;
  }

  fSummer = 0;
  fWinter = 0;

  AddSysRecord(EVE_PREVNEXTTIME2);
  NexttimeOff();
  AddSysRecord(EVE_POSTNEXTTIME);

  if (fSummer == 1)
  {
    if (++tiCurr.bHour >= 24)
    {
      tiCurr.bHour = 0;

      tiAlt = tiCurr;
      if (++tiCurr.bDay > DaysInMonth())
      {
        tiCurr.bDay = 1;
        if (++tiCurr.bMonth > 12)
        {
          tiCurr.bMonth = 1;
          tiCurr.bYear++;
        }
      }
    }

    tiSetRTC = tiCurr;
    SetCurrTimeDate();
  }

  if (fWinter == 1)
  {
    if (tiCurr.bHour > 0)
      tiCurr.bHour--;
    else
    {
      tiCurr.bHour = 23;
      if (tiCurr.bDay > 1)
        tiCurr.bDay--;
      else
      {
        if (tiCurr.bMonth > 1)
          tiCurr.bMonth--;
        else
        {
          tiCurr.bMonth = 12;  
          tiCurr.bYear--; 
        }

        tiAlt = tiCurr;
        tiCurr.bDay = DaysInMonth();             
      } 
    }

    tiSetRTC = tiCurr;
    SetCurrTimeDate();
  }
}



// ��������� ��������� ��������� � �������� �������
void    Nexttime(void)
{
  if (GetLabelRTC() == 0) return;

  PGetCurrTimeDate();
  if (TrueCurrTimeDate() == 0) return;

  if (tiCurr.bSecond != tiGetRTC.bSecond)
  {
    // ������ �������� �������
    tiCurr = tiGetRTC;

    if (enGlobal != GLB_PROGRAM)
    {
      fActive = 1;
      ProcessTime();
    }
    else
    {
      fProfile = 0;
      fCurrent = 0;

      ClearNewTime();
    }

    // ������ ���������� �������
    tiPrev = tiCurr;
  }
}
*/
