/*------------------------------------------------------------------------------
DIGITALS_RUN.C
              

------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "digitals2.h"
#include        "label.h"
#include        "programs.h"
#include        "display.h"
#include        "keyboard.h"
#include        "access.h"
#include        "devices.h"
#include        "devices_far.h"
#include        "device_a.h"
#include        "device_b.h"
#include        "device_b2.h"
#include        "device_b12.h"
#include        "device_c.h"
#include        "device_c2.h"
#include        "device_d.h"
#include        "device_d2.h"
#include        "device_e.h"
#include        "device_f.h"
#include        "device_g.h"
#include        "device_h.h"
#include        "device_i.h"
#include        "device_k.h"
#include        "device_m.h"
#include        "device_n.h"
#include        "device_o.h"
#include        "device_p.h"
#include        "device_q.h"
#include        "device_r.h"
#include        "device_s.h"
#include        "device_t.h"
#include        "device_u.h"
#include        "device_u2.h"
#include        "device_z.h"
#include        "decompress_c.h"
#include        "decompress_g.h"
#include        "decompress_k.h"
#include        "decompress_s.h"
#include        "beep.h"
#include        "engine.h"
#include        "energy.h"
#include        "crc-16.h"
#include        "rtc.h"
#include        "nexttime.h"
#include        "timedate.h"
#include        "delay.h"
#include        "display.h"
#include        "defects.h"
#include        "essential.h"
#include        "ports.h"
#include        "status.h"
#include        "pause.h"
#include        "sensors.h"
#include        "modems.h"
#include        "speed.h"
#include        "hours.h"
#include        "c_digitals.h"
#include        "log.h"
#include        "limits.h"
#include        "groups.h"
#include        "decret.h"
#include        "flow.h"
#include        "info.h"
#include        "contacts.h"
#include        "current.h"
#include        "record.h"
#include        "dtr.h"
#include        "recalc_cust.h"
#include        "calc3.h"
#include        "extended_3.h"
#include        "extended_4.h"
#include        "extended_4t.h"
#include        "extended_5.h"
#include        "phones2.h"
#include        "answer_flag.h"
#include        "max_repeats.h"
#include        "checkup_loader.h"
#include        "checkup.h"
#include        "checkup_b.h"
#include        "checkup_c.h"
#include        "_timedate.h"



//                                         0123456789ABCDEF
uchar           code    szBaudOK[]      = "   �����: OK    ",
                        szCommonOK[]    = " ��������� 1: OK",
                        szCustomOK[]    = " ��������� 2: OK",
                        szEscapeOK[]    = "     +++: OK    ",
                        szHookOffOK[]   = " ����������: OK ",
                        szOpen[]        = " ����� ...      ",
                        szOpenOK[]      = " �����: OK      ",
                        szRepeats[]     = " ������   ...   ",
                        szCorrectNo[]   = " ���������: ��� ",
                        szCorrectYes[]  = " ���������: ����",
                        szCorrectNext[] = " ��� ���������  ",
                        szManageNo[]    = " ��������: ���  ",
                        szManageYes[]   = " ��������: ���� ",
                        szCorrectBig[]  = "  ���������� !  ",
                        szBadDates[]    = "����: �������� !",
                        szBadClock[]    = "������ ������� !",
                        szStamp[]       = " �����/���� ... ",
                        szStampOK[]     = " �����/����: OK ",
                        szDelay[]       = " �������� 1 ... ",
                        szDefect[]      = " �������� 2 ... ",
                        szIndex[]       = " �������� ...   ",
                        szIndexOK[]     = " ��������: OK   ",
                        szManual[]      = "����������      ",
                        szPause[]       = "��������:       ",
                        szModemStop[]   = "   ����������   ",
                        szDisabledHou[] = "������� ��������",
                        szDisabledCan[] = " ����� �������� ",
                        szNoLink[]      = "  ��� ����� !   ",
                        szNoDevice[]    = " ������ ����� ! ",
                        szNoData[]      = "������ �� ������",
                        szNoVersion[]   = "������ ������ ! ",
                        szPowerOK[]     = "  ��������: OK  ",
                        szPowerNo[]     = "  ��������: ��� ",
                        szNewSeason[]   = "����� ������:   ",
                        szIsWinter[]    = "�� ����� �����  ",
                        szClosing[]     = "   ��������...  ",
                        szNoRecalc[]    = "��� ����������� ",
                        szCorrectQ1[]   = " ���������...   ",
                        szCorrectQ2[]   = " ���������...OK ",
                        szWorkDone[]    = "����� ��������  ",
                        szFailure1[]    = " ���� ������ !  ",
                        szFailure2[]    = " ���� ������ !  ",
                        szFailure20[]   = "���� ������ !   ";


// ������� ��������
uchar           data    cbRepeat;

// ������� ����������� ������ ������� ��������
bit                     fBreakRead;

// ������� ��������� � ������� connect
bit                     fConnect;

// ������� ������� ��������� ��� ������� ������
bit                     fKeyOn;

// ������� ��������� ������� ��� ������ �������� ���������
bit                     fCurrCtrlHou;



// �������������� ������ connect ��� ��������/����������� ����������
void    KeyBreakConnect(void)
{
  if (fConnect == 1)
  {
    ShowHi(szPause);
    ShowLo(szModemStop);

    fSlide = 0;
    DelayMsg();
  }
  else Stop();  

  enKeyboard = KBD_BEGIN;
  bProgram = 0; wProgram = 0;

  fKeyOn = 1;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_KEYBREAK);
}



// ��������� ������������� ����������
void    InitDigitals(void)
{
uchar   i,j;

  if (GetLabelXDATA() == 0)
  { 
    MakeDigitals();

    for (i=0; i<bCANALS; i++) mpboBase[i] = boFalse;

    for (i=0; i<bCANALS; i++) mpreEngFrac[i] = 0;

    for (i=0; i<bCANALS; i++) 
      for (j=0; j<6; j++) mpreEngFracDigCan[i][j] = 0;
  }

  SetCurr(DEV_BEGIN);
  SetPause(DEV_BEGIN);

  InitWaitAnswer();
  cbWaitOnline = 0;

  InitConnectKey();
  InfoBegin();

  ibPortPause = 0xFF;
  EnableAnswer();

  InitDeviceR();
  InitMaxRepeats();
  InitCurrent2();

  InitExtended4();
  InitExtended4T();

  if ((bPlcUSize < 1) || (bPlcUSize > 8)) bPlcUSize = 6;
  if ((wPlcUShutdown < 10) || (wPlcUShutdown > 500)) wPlcUShutdown = 100;
}



bit     StartProfile(uchar  ibCanal)
{
//uint    i;

  ibDig = ibCanal;  
  while (ibDig < bCANALS)               // ��������� ��� �������� ���������
  {
    LoadCurrDigital(ibDig);

    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) ||
        (diCurr.bDevice ==  3) ||
        (diCurr.bDevice ==  4) ||
        (diCurr.bDevice ==  5) || (diCurr.bDevice ==  7) ||
        (diCurr.bDevice ==  6) ||
        (diCurr.bDevice ==  9) || (diCurr.bDevice == 10) ||
        (diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25) ||
        (diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
        (diCurr.bDevice == 21) ||
        (diCurr.bDevice == 22) || (diCurr.bDevice == 26) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24) ||
        (diCurr.bDevice == 99))   
    {
      if (mpboReadyCan[ibDig] == boFalse)
      {
        if (mpboEnblCan[ibDig] == boFalse)  
        {
          sprintf(szHi,"�����: %-2bu       ",ibDig+1);
          ShowLo(szDisabledCan); if (boHideMessages == boFalse) DelayInf();
          AddDigRecord(EVE_CANAL_DISABLED);
        }
        else if ((GetEnblPorHou(diCurr.ibPort,GetHouIndex()) == boFalse) && (boManual == boFalse))
        {
          sprintf(szHi,"�����: %-2bu       ",ibDig+1);
          sprintf(szHi+14,"%02bu",GetHouIndex());
          ShowLo(szDisabledHou); if (boHideMessages == boFalse) DelayMsg();
          AddDigRecord(EVE_PROFILE_DISABLED);
        }
        else break;   
      }
    }

    ibDig++;
  }

  if (ibDig >= bCANALS) return(0);

/ *
  cwDefHou = 0;                         // ���������� ������� ����� ����� �� ���������
  for (i=0; i<wHOURS; i++)               
  {
    LoadAltDefHou(i);
    stAlt = GetStatus(ibDig);

    if ((stAlt == STA_NONE) || (stAlt == STA_DATAOFF)) cwDefHou++;
  }

  if (cwDefHou == 0) return(0);  
* /


  tiAlt = tiCurr;
  if (IsWinterAlt())
  {
    ShowHi(szNewSeason);
    ShowLo(szIsWinter); DelayMsg();
    Work(); OK();
    return(0);                          // ��������� ������� �� ������ �����
  }
/ *
#ifdef  DS80C400  
  if ((GetEnblPorHou(diCurr.ibPort,GetHouIndex()) == boFalse) && (boManual == boFalse))
  {
    sprintf(szHi,"�������: %-2bu     ",GetHouIndex());
    ShowLo(szDisabledHou); DelayMsg();

    AddDigRecord(EVE_PROFILE_DISABLED);
    Work(); OK();
    return(0);                          // ��������� ����������� ������� � ������ �������
  }
#endif
* /

  boRecalcCurr = mpboRecalcHou[GetHouIndex()];

  AddDigRecord(EVE_PROFILE2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILE);

  mpboDefEscV[ibDig] = boFalse;
  mpboDefEscS[ibDig] = boFalse;
  mpboDefEscU[ibDig] = boFalse;

  if (boManual == boFalse) 
  {
    AddDigRecord(EVE_PROFILEOPEN); 
    if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOPEN);
  }
  else 
  {
    AddDigRecord(EVE_SPECIALOPEN);
    if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_SPECIALOPEN);
  }


  NoShowTime(1);
  ShowDigitalHi(); Clear();
  InfoDigital();

//  cwDefects1 = cwDefHou;
  cwHouRead = 0;

  fBreakRead = 0;

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  SetNext(DEV_START_A2);  break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  SetNext(DEV_START_B2);  break;
#endif

#ifndef SKIP_C
    case 3:  SetNext(DEV_START_C2);  break;
#endif

#ifndef SKIP_D
    case 4:  SetNext(DEV_START_D2);  break;
#endif

#ifndef SKIP_E
    case 7:
    case 5:  SetNext(DEV_START_E2);  break;
#endif

#ifndef SKIP_F
    case 6:  SetNext(DEV_START_F2);  break;
#endif

#ifndef SKIP_G
    case 9:  SetNext(DEV_START_G2);  break;
#endif

#ifndef SKIP_H
    case 10: SetNext(DEV_START_H2);  break;
#endif

#ifndef SKIP_I
    case 11: SetNext(DEV_START_I2);  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: SetNext(DEV_START_K2);  break;
#endif

#ifndef SKIP_O
    case 20: SetNext(DEV_START_O2);  break;
#endif

#ifndef SKIP_P
    case 21: SetNext(DEV_START_P2);  break;
#endif

#ifndef SKIP_Q
    case 22: SetNext(DEV_START_Q2);  break;
#endif

#ifndef SKIP_R
    case 23: SetNext(DEV_START_R2);  break;
#endif

#ifndef SKIP_S
    case 24: SetNext(DEV_START_S2);  break;
#endif

#ifndef SKIP_T
    case 25: SetNext(DEV_START_T2);  break;
#endif

#ifndef SKIP_U
    case 26: SetNext(DEV_START_U2);  break;
#endif

#ifndef SKIP_Z
    case 99: SetNext(DEV_START_Z2);  break;
#endif
  }

  exExtended = EXT_PROFILE_30MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}


void    RunProfile(bit  fCtrlHou)
{
  if (boLoadHou == boTrue) 
  {
#ifdef  FLOW
    CloseFlow();
#endif

    InfoRun();

    fCurrCtrlHou = fCtrlHou;
    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
    cwHouLength = 0;
  
    Log(LOG_BEG_RUNPROFILE);
//    if (boShowMessages == boTrue) LongBeep();

    if (boDTREnable == boTrue) DTROff_All();

    if (StartProfile(0) == 1) { OpenSpecial(); DisableAnswer(); } else { Work(); OK(); }
  }
  else BlockProgramExt(bSET_ENABLELOADHOU);
}


void    NextProfile(void)
{
//  cwDefects2 = cwDefHou;

  if (boHideMessages == boFalse)
  {
//    sprintf(szLo,"   %04u/%04u    ",cwDefects1,cwDefects2);
    sprintf(szLo," �������: %04u  ",cwHouRead);
    DelayMsg();
  }

  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) mpcwProfile_OK[ibCan]++;
  }

  AddDigRecord(EVE_PROFILE_OK2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEOK);


  if (cwHouRead == 0)
  {
    // ��������� ���������� ������ ������, ������������� �������� ��������
    LoadCurrDigital(ibDig);      
    for (ibCan=0; ibCan<bCANALS; ibCan++)                           
    {
      LoadPrevDigital(ibCan);
      if (CompareCurrPrevLines() == 1) mpboReadyCan[ibCan] = boTrue;
    }

    ShowLo(szNoData); if (boHideMessages == boFalse) DelayMsg();
  }

  Clear();


  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_D
    case 4:  QueryCloseD(1); break;
#endif
#ifndef SKIP_K
    case 14:
    case 13: QueryCloseK();  break;
#endif
#ifndef SKIP_P
    case 21: QueryCloseP();  break;
#endif
#ifndef SKIP_Q
    case 22: QueryCloseQ();  break;
#endif
#ifndef SKIP_U
    case 26: QueryCloseU();  break;
#endif
  }    

  if (StartProfile(ibDig+1) == 0)       // ����� ��������
  {
    ShowHi(szWorkDone); 
    sprintf(szLo+4,"�� %u:%02bu", (uint)(cwHouLength / 60), (uchar)(cwHouLength % 60)); if (boHideMessages == boFalse) DelayMsg();

    SetCurr(DEV_BEGIN);

    Log(LOG_END_RUNPROFILE);
    Log(LOG_BEG_CALCPROFILE);

    InfoEnd();
    OnHours();
    AddDigRecord(EVE_PROFILECLOSE2);

    if (boDTREnable == boTrue) DTROff_All();

    / *if (CheckAllGroupsNeg() == 1) {
      if (boRecalcCurr != boTrue) {
        ShowLo(szNoRecalc); DelayMsg();
        AddDigRecord(EVE_RECALCFREE);
      }
      else {
        if (boRecalcAlways == boTrue) {
          AddDigRecord(EVE_RECALC20);
          Recalc(1,1); 
          AddDigRecord(EVE_RECALC21);
        }
        else {   
          AddDigRecord(EVE_RECALC10);
          Recalc(0,1); 
          AddDigRecord(EVE_RECALC11);
        }
      }
    } 
    else* / if ((boRecalcCurr == boTrue) / *&& (boRecalcAlways == boTrue)* /) {
      AddDigRecord(EVE_RECALC20);
      Recalc(1,1); 
      AddDigRecord(EVE_RECALC21);
    } else if (boRecalcMaxPowCurrDay == boTrue)
      Recalc_MaxPowCurrDay();

    if ((boRecalcCurr == boTrue) && (boRecalcEnable == boTrue))
      Recalc_Cust();

    Work(); OK();

    boNewDay = boFalse;
    boNewHou = boFalse;

    boManual = boFalse;

    ibPortPause = 0xFF;

    Log(LOG_END_CALCPROFILE);
    EnableAnswer();

    if (mpboCheckupHou[GetHouIndex()] == boTrue) cbCheckupRun = 10;
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;
//  ResetAllSerial();
}



#ifdef  POWER

bit     StartCurrent(uchar  ibCanal)
{
  ibDig = ibCanal;

  while (ibDig < bCANALS)               // ��������� ��� �������� ���������
  {
    LoadCurrDigital(ibDig);

    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) || (diCurr.bDevice == 12) ||
        (diCurr.bDevice ==  3) ||
        (diCurr.bDevice ==  4) ||
        (diCurr.bDevice ==  6) ||
        (diCurr.bDevice ==  9) ||
        (diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25) ||
        (diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
        (diCurr.bDevice == 16) || (diCurr.bDevice == 17) ||
        (diCurr.bDevice == 18) ||
        (diCurr.bDevice == 19) ||
        (diCurr.bDevice == 21) ||
        (diCurr.bDevice == 22) || (diCurr.bDevice == 26) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24))
    {
      if (mpboReadyCan[ibDig] == boFalse)
      {
        if (mpboEnblCan[ibDig] == boFalse)  
        {
          sprintf(szHi,"�����: %-2bu       ",ibDig+1);
          ShowLo(szDisabledCan); if (boHideMessages == boFalse) Delay(300);
        }
        else break;   
      }
    }

    ibDig++;
  }

  if (ibDig >= bCANALS) return(0);  

  
  NoShowTime(1);
  ShowDigitalHi(); Clear();

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  SetNext(DEV_START_A3);  break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  SetNext(DEV_START_B3);  break;
#endif

#ifndef SKIP_B
    case 12: SetNext(DEV_START_B312);  break;
#endif

#ifndef SKIP_C
    case 3:  SetNext(DEV_START_C3);  break;
#endif

#ifndef SKIP_D
    case 4:  SetNext(DEV_START_D3);  break;
#endif

#ifndef SKIP_F
    case 6:  SetNext(DEV_START_F3);  break;
#endif

#ifndef SKIP_G
    case 9:  SetNext(DEV_START_G3);  break;
#endif

#ifndef SKIP_I
    case 11: SetNext(DEV_START_I3);  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: SetNext(DEV_START_K3);  break;
#endif

#ifndef SKIP_L
    case 16:
    case 17: SetNext(DEV_START_K3);  break;
#endif

#ifndef SKIP_M
    case 18: SetNext(DEV_START_M3);  break;
#endif

#ifndef SKIP_N
    case 19: SetNext(DEV_START_N3);  break;
#endif

#ifndef SKIP_O
    case 20: SetNext(DEV_START_O3);  break;
#endif

#ifndef SKIP_P
    case 21: SetNext(DEV_START_P3);  break;
#endif

#ifndef SKIP_Q
    case 22: SetNext(DEV_START_Q3);  break;
#endif

#ifndef SKIP_R
    case 23: SetNext(DEV_START_R3);  break;
#endif

#ifndef SKIP_S
    case 24: SetNext(DEV_START_S3);  break;
#endif

#ifndef SKIP_T
    case 25: SetNext(DEV_START_T3);  break;
#endif

#ifndef SKIP_U
    case 26: SetNext(DEV_START_U3);  break;
#endif
  }

  exExtended = EXT_CURRENT_3MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}


void    RunCurrent(void)
{
  if (boLoadMnt == boTrue) 
  {
#ifdef  FLOW
    CloseFlow();
#endif

    if (GetCurr() == DEV_PAUSE) return;
    if (fConnect == 1) return;

    enModbusCurrent = MB1_PROGRESS;
    boErrorCurrent = boFalse;

    StartCurrent2();
    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));  
    if (StartCurrent(0) == 0)
    {
      fCurrent = 0;
      Work(); OK();

      bProgram = 0; wProgram = 0;
      cbShowTime = 2;
    }
  }
//  else BlockProgram(bSET_ENABLELOADMNT);
}


void    NextCurrent(void)
{
  Clear();

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_D
    case 4:  QueryCloseD(0); break;
#endif
#ifndef SKIP_K
    case 14:
    case 13: QueryCloseK();  break;
#endif
#ifndef SKIP_L
    case 16:
    case 17: QueryCloseK();  break;
#endif
#ifndef SKIP_P
    case 21: QueryCloseP();  break;
#endif
#ifndef SKIP_Q
    case 22: QueryCloseQ();  break;
#endif
#ifndef SKIP_U
    case 26: QueryCloseU();  break;
#endif
  }    

  mpSerial[diCurr.ibPort] = SER_BEGIN;

  if (StartCurrent(ibDig+1) == 0)       // ����� �������� 
  {
    SetCurr(DEV_BEGIN);

    fCurrent = 0;
    MakeContacts1();
    MakeContacts4();
    StopCurrent2();
    Work(); OK();

    bProgram = 0; wProgram = 0;
    cbShowTime = 2;

    ibPortPause = 0xFF;

    bDelayPhone2 = 3;
    enModbusCurrent = (boErrorCurrent == boFalse) ? MB1_READY : MB1_ERROR;
  }
}



void    MakeCurrent(void)
{
  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      mpbCurrent2Curr[ibCan/8] |= (0x80 >> ibCan%8); 

      if (boMntEscS == boTrue)
      {
        mpreEsc_S[ibCan] = mpreValueCntHou[ibCan] * mpdwBase[ibCan];
        mptiEsc_S[ibCan] = *PGetCurrTimeDate();
      }

      mpboReadyCan[ibCan] = boTrue;

      mpwTrue[ibCan]++;
      if (mpboBase[ibCan] == boFalse)
      {
        mpboBase[ibCan] = boTrue;

        mpdwBase[ibCan] = mpdwBaseDig[ diPrev.ibLine ];
        mpreBase[ibCan] = 0;
        mptiBase[ibCan] = *PGetCurrTimeDate();
        mptiOffs[ibCan] = tiOffs;
      }
      else
      {
        tiDig = *PGetCurrTimeDate();      
        tiAlt = mptiBase[ibCan];

        if (CompareAltDig(0x07) == 1)           // ����������: ����, �����, ���
          dwBuffC = 0;
        else
          dwBuffC = (ulong)24*3600;

        dwUpdate = mpdwBaseDig[ GetDigitalLine(ibCan) ] - mpdwBase[ibCan];
        mpdwBase[ibCan] = mpdwBaseDig[ GetDigitalLine(ibCan) ];

        tiAlt = tiDig;
        dwBuffC += GetSecondIndex();
        tiAlt = mptiBase[ibCan];
        dwBuffC -= GetSecondIndex();

        mptiBase[ibCan] = tiDig;
        mptiOffs[ibCan] = tiOffs;

        mptiBaseOK[ibCan] = *PGetCurrTimeDate();

        if ((dwBuffC > 0) && (dwBuffC < 1800))
          mpreBase[ibCan] += (real)180*dwUpdate/dwBuffC;

        dwUpdate = mpreBase[ibCan];
        mpreBase[ibCan] -= dwUpdate;

        if (dwUpdate > 100) mpwMore100[ibCan]++;
        if (dwUpdate > 1000) mpwMore1000[ibCan]++;
        if (dwUpdate > 10000) mpwMore10000[ibCan]++;

        if (dwUpdate > 0xFFFF)                  // ������������
          mpwMore[ibCan]++;
        else
        if (dwUpdate < 0)                       // ���
          mpwLess[ibCan]++;
        else
        {
          mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = (uint)dwUpdate;
          MakeSpecCurrent();
        }
      }
    }
  }

  NextCurrent();
}

#endif



void    ErrorLink(void)
{
  ShowLo(szNoLink);
  sprintf(szLo+14,"%2bu",cbRepeat); DelayInf();
}


// ��������� ������� �� ��������� �����
void    ErrorProfile(void)
{
  InfoError();
  SaveDisplay();

  ShowHi(szWarning);
  sprintf(szLo,"������� %02bX.%02bX.%02bX",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) mpcwProfile_Error[ibCan]++;
  }

  AddDigRecord(EVE_PROFILE_ERROR2);
  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEERROR2);


  DelayMsg();
  LoadDisplay();

  // ��������� ���������� ������ ������, ������������� �������� ��������
  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) mpboReadyCan[ibCan] = boTrue;
  }

  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);
}


// ���������� ������� �� ��������� �����
void    DoneProfile(void)
{
  NewLimits();                                      // ������� ������� �� ������� ��������

  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEDONE1);
}


// ���������� ������� �� ��������� �����
void    DoneProfile_Stop(void)
{
  fKeyOn = 0;
  MakePause(DEV_MODEM_STOP);

  if (diCurr.ibPhone != 0) AddModRecord(EVE_MODEM_PROFILEDONE2);
}



#ifdef  POWER

void    ErrorCurrent(void)
{
  boErrorCurrent = boTrue;
  SaveDisplay();

  ShowHi(szWarning);
  sprintf(szLo,"������� %02bX.%02bX.%02bX",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  DelayMsg();
  LoadDisplay();

  // ��������� ���������� ������ ������, ������������� �������� ��������
  LoadCurrDigital(ibDig);      
  for (ibCan=0; ibCan<bCANALS; ibCan++)                           
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1) 
    {
      mpboReadyCan[ibCan] = boTrue;

      mptiBaseError[ibCan] = *PGetCurrTimeDate();
      mpwFalse[ibCan]++;
    }
  }

  SetCurr(DEV_BEGIN);
  NextCurrent();    
}

#endif



void    ShowProgressRepeat(void)
{
  sprintf(szLo,"   ������: %bu    ",cbRepeat); DelayInf();
//  sprintf(szHi+14,"*%1bu",cbRepeat);
//  ShowProgress(12,(ulong)100* /(bMINORREPEATS-1));
}


void    ShowProgressDigHou(void)
{
uint    i;

  i = (ulong)100*((wHOURS+iwHardHou-iwDigHou)%wHOURS)/mpcwStopCan[ibDig];
  if (i > 100) i = 100;

  ShowProgress(12,i);
  InfoProgress(i);
}



// ������� ������������ ������ ��������� ���������
void    Digitals(void)
{
uchar   i,bT;

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;



  if ((fConnect == 1) && (bProgram != 0))
  {
    if ((cbWaitOnline > 0) && (cbWaitOnline % 10 == 5))
    {
      SaveDisplay();
      ShowHi(szManual); Clear();

      if (cbWaitOnline <= bMAXWAITONLINE)
        sprintf(szLo,"  ��������: %bu c ",(uchar)(bMAXWAITONLINE-cbWaitOnline)); 
      else
        sprintf(szLo,"����������: %bu c ",(uchar)bMAXWAITONLINE); 

      DelayMsg();
      LoadDisplay();

      if (cbWaitOnline > bMAXWAITONLINE) KeyBreakConnect();
    }
  }



  switch (GetPause())
  {
#ifndef SKIP_E
    case DEV_OPENCANAL_E2:
#endif

    case DEV_MODEM_CONNECT:
      cbWaitQuery = bWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); NoShowTime(1);
      break;

#ifndef SKIP_E
    case DEV_ENERGY_E2:      
      cbWaitQuery = bWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); NoShowTime(1);
      if (IndexInBuff() > 0) sprintf(szLo," �����: %-4u ",IndexInBuff());
      break;
#endif
  }


  if ((mpSerial[ibPort] == SER_INPUT_MASTER))
  {

#ifndef SKIP_C
    if (diCurr.bDevice == 3)
    {
      if (GetCurr() == DEV_HEADER_1_C2)
        DecompressC();
    }
#endif

#ifndef SKIP_G
    if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
    {
      if ((InBuff(0) == 0x7E) && (IndexInBuff() > 3) && (IndexInBuff() == InBuff(1)+4))
        mpSerial[ibPort] = SER_BADLINK;
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))
    {
      if ((GetCurr() == DEV_OPENCANAL_K2) || (GetCurr() == DEV_OPENCANAL_K3))
      {
        bT = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((bT == '\r') || (bT == '\n'))   
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if (GetCurr() == DEV_PASSWORD_K2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_POSTCONTROL_K2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_HEADER_K2)
        DecompressK(1);
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if ((GetCurr() == DEV_OPENCANAL_Q2) || (GetCurr() == DEV_OPENCANAL_Q3))
      {
        bT = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((bT == '\r') || (bT == '\n'))   
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if (GetCurr() == DEV_PASSWORD_Q2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_POSTCONTROL_Q2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_HEADER_Q2)
        DecompressK(1);

      else if (GetCurr() == DEV_ENERGY_Q3)
        DecompressK(1);
    }
#endif

#ifndef SKIP_S
    else if (diCurr.bDevice == 24)
    {
      DecompressS();
    }
#endif

#ifndef SKIP_U
    else if (diCurr.bDevice == 26)
    {
      if ((GetCurr() == DEV_OPENCANAL_U2) || (GetCurr() == DEV_OPENCANAL_U3))
      {
        bT = InBuff(IndexInBuff() - 1) & 0x7F;
        if ((bT == '\r') || (bT == '\n'))   
          mpSerial[ibPort] = SER_BADLINK;
      }

      else if (GetCurr() == DEV_PASSWORD_U2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if (GetCurr() == DEV_POSTCONTROL_U2)
      {
        if (IndexInBuff() > 0)
          mpSerial[ibPort] = SER_BADLINK;
      } 

      else if ((GetCurr() == DEV_OPTION_U2) || (GetCurr() == DEV_OPTION_U3))
        DecompressK2(1, 4);

      else if ((GetCurr() == DEV_HEADER_U2) || (GetCurr() == DEV_HEADER_U4))
        DecompressK(1);

      else if (GetCurr() == DEV_ENERGY_U3)
        DecompressK(1);
    }
#endif
  }


  if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
  {
    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) || (diCurr.bDevice == 12) ||
        (diCurr.bDevice ==  6) || 
        (diCurr.bDevice == 18) ||
        (diCurr.bDevice == 19))
    {
      MakeCRC16InBuff( 0, CountInBuff() );

      if ((bCRCHi == 0) && (bCRCLo == 0))
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }

#ifndef SKIP_C
    else if (diCurr.bDevice == 3)
    {
      MakeCRC16InBuff( 0, CountInBuff()-2 );

      if ((bCRCHi == InBuff( CountInBuff()-1 )) &&
          (bCRCLo == InBuff( CountInBuff()-2 ))) {

        if (RevLinkErrors() == 0) 
          mpSerial[ibPort] = SER_GOODCHECK;
        else
          mpSerial[ibPort] = SER_BADCHECK;
      }
      else {
        mpSerial[ibPort] = SER_BADCHECK;
        ChecksumError();
      }
    }
#endif

#ifndef SKIP_D
    else if (diCurr.bDevice == 4)
    {
      MakeCRC12InBuff( 0, CountInBuff() );

      if (wCRC == 0)
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_E
    else if ((diCurr.bDevice == 5) || (diCurr.bDevice == 7))
    {
      if ( MakeEscInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_G
    else if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
    {
      MakeCRC8InBuff( 1, CountInBuff()-1 );

      if (bCRC == 0)
      {
        DecompressG();
        mpSerial[ibPort] = SER_GOODCHECK;
      }
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_I
    else if ((diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25))
    {
      InitPop(0);

      bT = 0;
      for (i=0; i<CountInBuff()-3; i++) bT += PopChar();

      if ((bT/0x10 == PopChar1Txt()) && (bT%0x10 == PopChar1Txt()))
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))  
    {
      if ( MakeBccInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_P
    else if (diCurr.bDevice == 21)
    {
      if ((GetCurr() == DEV_PASSWORD_P3) ||
          (GetCurr() == DEV_PASSWORD_P2) || (GetCurr() == DEV_REPASSWORD_P2) || (GetCurr() == DEV_SETVALUE_P2) ||
          (GetCurr() == DEV_CORRECT_P2))
      {
        if ( MakeElsInBuff2() ) {
          mpSerial[ibPort] = SER_GOODCHECK; 
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK; 
        }
      } 
      else if ((GetCurr() == DEV_OPENCANAL_P3) || 
               (GetCurr() == DEV_OPENCANAL_P2))
      {
        if ( MakeElsInBuff1() ) {
          mpSerial[ibPort] = SER_GOODCHECK; 
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK; 
        }
      } 
      else
      {
        if ( MakeElsInBuff0() ) {
          mpSerial[ibPort] = SER_GOODCHECK; 
        }
        else {
          mpSerial[ibPort] = SER_BADCHECK; 
        }
      }
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if ( MakeBccInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_R
    if (diCurr.bDevice == 23)
    {
      mpSerial[ibPort] = SER_GOODCHECK;
    }
#endif

#ifndef SKIP_S
    if (diCurr.bDevice == 24)
    {
      if (ChecksumS() == 0)
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_U
    else if (diCurr.bDevice == 26)
    {
      if ( MakeBccInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif

#ifndef SKIP_Z
    else if (diCurr.bDevice == 99)
    {
      if ( MakeZetInBuff() )
        mpSerial[ibPort] = SER_GOODCHECK;
      else 
        mpSerial[ibPort] = SER_BADCHECK;
    }
#endif
  }
  else if ((mpSerial[ibPort] == SER_OVERFLOW) || 
           (mpSerial[ibPort] == SER_BADLINK)  ||
           (mpSerial[ibPort] == SER_POSTANSWER_MODEM)  ||
           (mpSerial[ibPort] == SER_PAUSE))
  {
    // ������ ��������

#ifndef SKIP_G
    if ((diCurr.bDevice == 9) || (diCurr.bDevice == 10))
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        MakeCRC8InBuff( 1, IndexInBuff()-1 );

        if (bCRC == 0)
        {
          DecompressG();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else 
          mpSerial[ibPort] = SER_BADCHECK;
      }
    }
#endif

#ifndef SKIP_K
    else if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
             (diCurr.bDevice == 16) || (diCurr.bDevice == 17))
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        if ((GetCurr() == DEV_OPENCANAL_K2) || (GetCurr() == DEV_OPENCANAL_K3))
        {
          bT = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((bT == '\r') || (bT == '\n')) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_K2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))   
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_K2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06)) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_HEADER_K2)
        {
          if (IndexInBuff() == 10)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        if ((GetCurr() == DEV_OPENCANAL_Q2) || (GetCurr() == DEV_OPENCANAL_Q3))
        {
          bT = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((bT == '\r') || (bT == '\n')) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_Q2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))   
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_Q2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06)) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_HEADER_Q2)
        {
          if (IndexInBuff() == 10)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_U
    else if (diCurr.bDevice == 26)
    {
      if ((mpSerial[ibPort] == SER_BADLINK) && (fFlow == 0)) 
      {
        if ((GetCurr() == DEV_OPENCANAL_U2) || (GetCurr() == DEV_OPENCANAL_U3))
        {
          bT = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((bT == '\r') || (bT == '\n')) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_U2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))   
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_U2)
        {
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06)) 
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if ((GetCurr() == DEV_HEADER_U2) || (GetCurr() == DEV_HEADER_U4))
        {
          if (IndexInBuff() == 3)
            mpSerial[ibPort] = SER_GOODCHECK;
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

  }
  else return;



  switch (GetCurr())
  {
    case DEV_PAUSE:
      if (mpSerial[ibPort] == SER_POSTANSWER_MODEM) 
        SetCurr(GetPause());
      break;



    case DEV_MODEM_START:
      if ((exExtended == EXT_CURRENT_3MIN) && (diCurr.ibPhone != 0)) 
      {
        ShowLo(szPowerNo); DelayInf();
        cbWaitQuery = 3;
        NextCurrent();
      }
      else
      {
        fConnect = 0;
        if (StreamPortCan(diCurr.ibPort,ibDig) == 0) 
        {
          fKeyOn = 0;
          MakePause(DEV_MODEM_STOP);

          AddModRecord(EVE_MODEM_ERROR); 
        }
        else if (diCurr.ibPhone != 0) 
          MakePause(DEV_MODEM_POSTSTART);
        else
          MakePause(DEV_MODEM_POSTCONNECT);
      }
      break;

    case DEV_MODEM_POSTSTART:
      cbRepeat = bMINORREPEATS;

      QueryModemBaud(1);
      MakeLongPause(DEV_MODEM_BAUD,1);        

      AddDigRecord(EVE_MODEMCONNECT1);
      AddModRecord(EVE_MODEMBAUD); 
      break;

    case DEV_MODEM_BAUD:
      if (ModSerialOK() == 1)
      {
        ShowLo(szBaudOK); DelayInf();
        mpcwBaud[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTBAUD);

        AddModRecord(EVE_MODEMBAUD_OK); 
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTBAUD); 
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
  
          QueryModemBaud(1);
          MakeLongPause(DEV_MODEM_BAUD,1);        

          AddModRecord(EVE_MODEMBAUD_NEXT);
        } 
      }
      break;

    case DEV_MODEM_POSTBAUD:
      cbRepeat = bMINORREPEATS;

      QueryModemCommon(1);
      MakeLongPause(DEV_MODEM_COMMON,1);

      AddModRecord(EVE_MODEMCOMMON1);
      break;

    case DEV_MODEM_COMMON:
      if (ModSerialOK() == 1)
      {
        ShowLo(szCommonOK); DelayInf();
        mpcwCommon[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCOMMON);

        AddModRecord(EVE_MODEMCOMMON1_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          if (cbRepeat == bMINORREPEATS-1)
          {
            QueryModemCommon(1);
            MakeLongPause(DEV_MODEM_COMMON,1);        

            AddModRecord(EVE_MODEMCOMMON1_NEXT);
          }
          else
          {
            QueryModemEscape();
            MakeLongPause(DEV_MODEM_ONLINE,1);        

            AddModRecord(EVE_MODEMESCAPE1_NEXT);
          }
        }
      }
      break;

    case DEV_MODEM_ONLINE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szEscapeOK); DelayInf();
        mpcwEscape[diCurr.ibPort]++;

        QueryModemHookOff();
        MakeLongPause(DEV_MODEM_POSTONLINE,1);        

        AddModRecord(EVE_MODEMHOOKOFF1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();

          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_POSTONLINE,1);        

          AddModRecord(EVE_MODEMHOOKOFF1_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTONLINE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();
        mpcwHookOff[diCurr.ibPort]++;

        QueryModemCommon(1);
        MakeLongPause(DEV_MODEM_COMMON,1);        

        AddModRecord(EVE_MODEMCOMMON2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();

          QueryModemCommon(1);
          MakeLongPause(DEV_MODEM_COMMON,1);        

          AddModRecord(EVE_MODEMCOMMON2_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCOMMON:
      if (boCustomModem == boTrue)
        MakePause(DEV_MODEM_NORMAL);
      else
        MakePause(DEV_MODEM_POSTCUSTOM);
      break;

    case DEV_MODEM_NORMAL:
      cbRepeat = bMINORREPEATS;

      QueryModemCustom();
      MakeLongPause(DEV_MODEM_CUSTOM,1);

      AddModRecord(EVE_MODEMCUSTOM);
      break;

    case DEV_MODEM_CUSTOM:
      if (ModSerialOK() == 1)
      {
        ShowLo(szCustomOK); DelayInf();
        mpcwCustom[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCUSTOM);

        AddModRecord(EVE_MODEMCUSTOM_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemCustom();
          MakeLongPause(DEV_MODEM_CUSTOM,1);

          AddModRecord(EVE_MODEMCUSTOM_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCUSTOM:
      InitWaitAnswer();

      cbRepeat = bMINORREPEATS;

      fConnect = 1;
      QueryModemConnect();
      MakeLongPause(DEV_MODEM_CONNECT,bConnect);

      AddModRecord(EVE_MODEMCONNECT);
      break;

    case DEV_MODEM_CONNECT:
      if ((mpSerial[ibPort] == SER_POSTANSWER_MODEM) && (ShowModemConnect() == 1)) 
      {
        ShowDigitalHi();

        cbWaitOnline = 0;

        mpcwConnect[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTCONNECT);

        AddDigRecord(EVE_MODEMCONNECT2);
        AddModRecord(EVE_MODEMCONNECT_OK);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          InitWaitAnswer();

          fConnect = 1;
          QueryModemConnect();
          MakeLongPause(DEV_MODEM_CONNECT,bConnect);

          AddModRecord(EVE_MODEMCONNECT_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCONNECT:
      if (exExtended == EXT_PROFILE_30MIN)
      {
        MakeExtended1();
        MakeExtended4();
        MakeExtended5();
        MakeExtended3();
        MakeExtended4T();
      }

      if ((exExtended == EXT_PROFILE_30MIN) && (boQuickParam == boFalse)) 
        MakeExtended2();

      if ((exExtended == EXT_CURRENT_3MIN) && (boQuickParam == boTrue)) 
        MakeExtended2();

      NoShowTime(1);
      MakePause(GetNext());
      break;



    case DEV_MODEM_STOP:
      if (fKeyOn == 0)
        ShowDigitalHi();
      else
        ShowHi(szManual);

      if ((diCurr.ibPhone != 0) && (fConnect == 1))
        MakePause(DEV_MODEM_POSTSTOP);
      else 
        MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_POSTSTOP:
      cbRepeat = bMINORREPEATS;

      QueryModemEscape();
      MakeLongPause(DEV_MODEM_ESCAPE,3);        

      AddDigRecord(EVE_MODEMBREAK1);
      AddModRecord(EVE_MODEMESCAPE2);
      break;

    case DEV_MODEM_ESCAPE:
      if (ModSerialOK() == 1)
      {
        ShowLo(szEscapeOK); DelayInf();

        mpcwEscape[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTESCAPE);

        AddModRecord(EVE_MODEMESCAPE2_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTESCAPE);
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_PREVHOOKOFF,1);        

          AddModRecord(EVE_MODEMHOOKOFF2_NEXT);
        }
      }
      break;

    case DEV_MODEM_PREVHOOKOFF:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();

        mpcwHookOff[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTHOOKOFF);

        AddModRecord(EVE_MODEMHOOKOFF2_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_POSTESCAPE);
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemEscape();
          MakeLongPause(DEV_MODEM_ESCAPE,3);

          AddModRecord(EVE_MODEMESCAPE3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTESCAPE:
      cbRepeat = bMINORREPEATS;

      QueryModemHookOff();
      MakeLongPause(DEV_MODEM_HOOKOFF,1);        

      AddModRecord(EVE_MODEMHOOKOFF3);
      break;

    case DEV_MODEM_HOOKOFF:
      if (ModSerialOK() == 1)
      {
        ShowLo(szHookOffOK); DelayInf();

        mpcwHookOff[diCurr.ibPort]++;
        MakePause(DEV_MODEM_POSTHOOKOFF);

        AddDigRecord(EVE_MODEMBREAK2);
        AddModRecord(EVE_MODEMHOOKOFF3_OK);
      }
      else
      {
        if (cbRepeat == 0) MakePause(DEV_MODEM_BREAK);
        else
        {
          cbRepeat--;
          ShowProgressRepeat();
          
          QueryModemHookOff();
          MakeLongPause(DEV_MODEM_HOOKOFF,1);

          AddModRecord(EVE_MODEMHOOKOFF3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTHOOKOFF:
      MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_BREAK:
      ModemDTROff();
      mpcwDTROff[diCurr.ibPort]++;

      MakePause(DEV_MODEM_POSTBREAK);

      AddModRecord(EVE_MODEMDTROFF);
      break;

    case DEV_MODEM_POSTBREAK:
      fConnect = 0;
      mpSerial[diCurr.ibPort] = SER_BEGIN;
      if (fKeyOn == 1)
      {
        SetCurr(DEV_BEGIN);
        SetPause(DEV_BEGIN);

        Work(); OK();  
      }
      else 
      {
        if (exExtended == EXT_PROFILE_30MIN)
          NextProfile();
        else
          NextCheckup();
      }
      break;

#ifndef SKIP_B

    case DEV_START_B2:                     
      cbCorrects = 0;

      cbRepeat = bMINORREPEATS;
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrlHou == 1)
          MakePause(DEV_POSTOPENCANAL_B2);
        else
          MakePause(DEV_POSTCORRECT_B2);  
      }
      else                                      
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B2);
        }
      }  
      break;

    case DEV_POSTOPENCANAL_B2:                  
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1bu",cbCorrects+1); DelayInf();

      cbRepeat = bMINORREPEATS;
      QueryTimeB();                          
      SetCurr(DEV_TIME_B2);          
      break;

    case DEV_TIME_B2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltB();                  
        ReadTimeDigB();                  
        MakePause(DEV_POSTTIME_B2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeB();
          SetCurr(DEV_TIME_B2);
        }
      } 
      break;


    case DEV_POSTTIME_B2:
      wBuffD  = GetDayIndex();              // ���������� ���� � ������ ���� �������� ��������
      dwBuffC = GetSecondIndex();           // ���������� ������ �������� ��������

      tiAlt = tiCurr;                       // ������� �����/���� ���������

      if (wBuffD != GetDayIndex())          
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ���������� 
      else 
      {
        if (dwBuffC > GetSecondIndex())                                         // ���������� ��������� ������� �������� �������� �����
          ShowDeltaNeg();
        else
          ShowDeltaPos();

        if (dwBuffC < MinorCorrect())                                           // ��� ���������
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }     
        else if (dwBuffC < bMAJORCORRECT_B)                                     // ������� ��������� 
        {
          if (cbCorrects == 0)
          { 
            bDeltaOld = (uchar)dwBuffC;
            (boShowMessages == boTrue) ? DelayMsg() : DelayInf();
            ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_B2); 
          }
          else
          {
            bDeltaNew = (uchar)dwBuffC;
            if ((bDeltaNew < bDeltaOld) && (cbCorrects < 100))
            {
              bDeltaOld = bDeltaNew;
              cbCorrects++;
              MakePause(DEV_POSTOPENCANAL_B2);
            }
            else if (GetHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))
            { ShowLo(szCorrectNext); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }     
            else
            { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
          }
        } 
        else                                                                    
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
      }
      break;


    case DEV_CONTROL_B2: 
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = bMINORREPEATS;                         
        QueryControlB();                          
        SetCurr(DEV_POSTCONTROL_B2);
      }
      break;

    case DEV_POSTCONTROL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // �� !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;
          
          QueryControlB();
          SetCurr(DEV_POSTCONTROL_B2);
        }
      } 
      break;
/ *
    case DEV_MANAGE_B2:                  
      if (++cbCorrects > bMINORREPEATS)          
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryManageB();                          
        SetCurr(DEV_POSTMANAGE_B2);
      }
      break;

    case DEV_POSTMANAGE_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B2);
      else                                    
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_B2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryManageB();
          SetCurr(DEV_POSTMANAGE_B2);
        }
      } 
      break;
* /

    case DEV_POSTCORRECT_B2:                  
      Clear();

      cbRepeat = bMINORREPEATS;
      QueryVersionB();
      SetCurr(DEV_VERSION_B2);
      break;

    case DEV_VERSION_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionB();
        MakePause(DEV_POSTVERSION_B2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryVersionB();
          SetCurr(DEV_VERSION_B2);
        }
      } 
      break;

    case DEV_POSTVERSION_B2:
      Clear();

      cbRepeat = bMINORREPEATS;
      QueryTopB();                          
      SetCurr(DEV_TOP_B2);
      break;

    case DEV_TOP_B2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (TestVersionB710()) ReadTopBNew(); else ReadTopBOld();
        MakePause(DEV_POSTTOP_B2);
      }
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTopB();
          SetCurr(DEV_TOP_B2);
        }
      } 
      break;

    case DEV_POSTTOP_B2:              
      cbRepeat2 = 0;
      if (diCurr.bDevice == 2)
      {
        if (TestVersionB710())
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
        else
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
      }
      else
      { 
        cbRepeat = bMINORREPEATS;
        QueryHeaderB_Plus(bBLOCKS_B);                         
        SetCurr(DEV_HEADER_B2PLUS);
      }
      break;

    case DEV_HEADER_B2:                    
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2);
      else                                  
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_B2);
/ *
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }* /
      } 
      break;

    case DEV_ERROR_B2: 
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else 
      {
        cbRepeat = bMINORREPEATS;
        QueryIdB();
        SetCurr(DEV_POSTERROR_B2);
      }
      break;

    case DEV_POSTERROR_B2: 
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdB() == 1)
        {
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_B2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdB();
          SetCurr(DEV_POSTERROR_B2);
        }
      } 
      break;

    case DEV_POSTHEADER_B2:                   
      cbRepeat2 = 0;
      NewBoundsAbs(wBaseCurr);
      if (ReadHeaderB(0,0) == 0)
        DoneProfile();  
      else 
      { 
        (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);

        cbRepeat = bMINORREPEATS;
        QueryHeaderB();
        SetCurr(DEV_HEADER_B2);
      }
      break;

    case DEV_HEADER_B2PLUS:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2PLUS);
      else                                  
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      } 
      break;

    case DEV_POSTHEADER_B2PLUS:
      for (i=0; i<bBLOCKS_B; i++)
        if (TestHeaderB(i) == 0) break;

      if (i != bBLOCKS_B)
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      else
      {
        NewBoundsAbs(wBaseCurr);
        for (i=0; i<bBLOCKS_B; i++)
        {
          if (ReadHeaderB(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != bBLOCKS_B)
          DoneProfile();
        else 
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
      }
      break;

    case DEV_HEADER_B2NEXT:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_B2NEXT);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
      } 
      break;

    case DEV_POSTHEADER_B2NEXT:
        NewBoundsAbs2(dwBaseCurr);
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBNew(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else 
        {
          cbRepeat = bMINORREPEATS;
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
      break;

#endif

#ifndef SKIP_B

    case DEV_START_B3:
      cbRepeat = GetMaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B3);             
      break;

    case DEV_OPENCANAL_B3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B3:
      cbRepeat = GetMaxRepeats();
      QueryEnergyB(0);
      SetCurr(DEV_ENERGY_B3);
      break;

    case DEV_ENERGY_B3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentB();
      else 
      {
        if (cbRepeat == 0)
          ErrorCurrent(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryEnergyB(0);
          SetCurr(DEV_ENERGY_B3);
        }
      } 
      break;

#endif

#ifndef SKIP_Z

    case DEV_START_Z2:                     
      if (fCurrCtrlHou == 1)
        MakePause(DEV_POSTOPENCANAL_Z2);
      else
        MakePause(DEV_POSTCORRECT_Z2);  
      break;

    case DEV_POSTOPENCANAL_Z2:                  
      cbRepeat = bMINORREPEATS;
      QueryTimeZ();                          
      SetCurr(DEV_TIME_Z2);          
      break;

    case DEV_TIME_Z2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTIME_Z2);
      else                                    
      {
        if (cbRepeat == 0) ErrorProfile(); 
        else
        {
          ErrorLink();
          cbRepeat--;
          
          QueryTimeZ();
          SetCurr(DEV_TIME_Z2);
        }
      } 
      break;

    case DEV_POSTTIME_Z2:
      ReadTimeAltZ();                  
      ReadTimeDigZ();                  

      if (TrueTimeDate() == 0) 
        ShowLo(szBadClock);
      else
      {
        if ((tiCurr.bDay   != tiAlt.bDay)   ||
            (tiCurr.bMonth != tiAlt.bMonth) ||
            (tiCurr.bYear  != tiAlt.bYear))
          ShowLo(szBadDates);
        else
        if (GetHouIndex() != (tiAlt.bHour*2 + tiAlt.bMinute/30))
          ShowLo(szCorrectBig);
        else
        {
          dwBuffC = GetSecondIndex();
          tiAlt = tiCurr;

          if (dwBuffC > GetSecondIndex()) 
            dwBuffC = dwBuffC - GetSecondIndex();
          else
            dwBuffC = GetSecondIndex() - dwBuffC;

          tiSetRTC = tiDig;
          SetCurrTime();

          Clear();
          sprintf(szLo+1,"�����: +%lu �", dwBuffC); 

          DelayMsg();
          ShowLo(szCorrectYes);
        }
      }

      DelayMsg();
      MakePause(DEV_POSTCORRECT_Z2);
      break;

    case DEV_POSTCORRECT_Z2:
      DoneProfile();  
      break;

#endif

  }
}
*/
