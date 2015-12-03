/*------------------------------------------------------------------------------
DEVICES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_params.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_current.h"
#include "../memory/mem_energy_spec.h"
#include "../memory/mem_limits.h"
#include "../memory/mem_phones.h"
#include "../memory/mem_flow.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/time/key_timedate.h"
#include "../realtime/realtime.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_status.h"
#include "../digitals/digitals_pause.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/digitals_display.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../digitals/current/current_run.h"
#include "../digitals/profile/profile_run.h"
#include "../digitals/profile/profile_link.h"
#include "../digitals/checkup/checkup_run.h"
#include "../digitals/params/params2.h"
#include "../digitals/max_repeats.h"
#include "../digitals/correct_limit.h"
#include "../digitals/max_shutdown.h"
#include "../special/recalc_def.h"
#include "../special/defects.h"
#include "../sensors/device_a.h"
#include "../sensors/device_b.h"
#include "../sensors/device_b2.h"
#include "../sensors/device_b12.h"
#include "../sensors/device_c.h"
#include "../sensors/device_e.h"
#include "../sensors/device_k.h"
#include "../sensors/device_p.h"
#include "../sensors/device_q.h"
#include "../sensors/device_s.h"
#include "../sensors/device_u.h"
#include "../sensors/device_u2.h"
#include "../sensors/device_v.h"
#include "../serial/ports.h"
#include "../serial/ports_modems.h"
#include "../serial/modems.h"
#include "../serial/speeds_display.h"
#include "../digitals/dsbl_answer.h"
#include "../digitals/limits.h"
#include "../digitals/digitals_display.h"
#include "../digitals/extended/extended_0.h"
#include "../digitals/extended/extended_1.h"
#include "../digitals/extended/extended_3.h"
#include "../digitals/extended/extended_4.h"
#include "../digitals/extended/extended_4t.h"
#include "../digitals/extended/extended_5.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "../time/timedate.h"
#include "../time/calendar.h"
#include "../time/delay.h"
#include "devices_input.h"
#include "devices_postinput.h"
#include "devices_pause.h"
#include "devices_init.h"
#include "devices.h"



// ������� ��������
uchar                   cbRepeat, cbRepeat2;

// ������� ��������� �������
uchar                   cbCorrects;

// ������� ����������� ������ ������� ��������
//bit                     fBreakRead;

// ������ �������� ��������� ��������
uchar                   ibDig;

//
time                    tiDig, tiDigPrev;

// ��� ������ ���������
extended                exExtended;

// ������� ��������� � ������� connect ������
bool                    fConnect;

// �������
uchar                   cbWaitOnline;

// ������� ������� ��������� ��� ������� ������
bool                    fKeyOn;



void    ShowRepeat(void)
{
  Clear();
  sprintf(szLo+3,"������: %u",cbRepeat); DelayInf();
}


void    ShowProgressDigHou(void)
{
  uint i = (ulong)100*((wHOURS+iwHardHou-iwDigHou)%wHOURS)/mpcwStopCan[ibDig];
  if (i > 100) i = 100;

  ShowProgress(12,i);
}


bool    MakeStopHou(uint  wAdd)
{
  if (((wHOURS+iwHardHou-iwDigHou) % wHOURS) < (mpcwStopCan[ibDig]+wAdd))
  {
    NewBoundsRel((wHOURS+iwHardHou-iwDigHou) % wHOURS);
    return(1);
  }
  else
  {
    NewLimits(); // ������� ������� �� ������� ���������
    return(0);
  }
}


void    ErrorLink(void)
{
  IncProfileLinkWrn(diCurr.ibPort, GetCurrHouIndex());

  ShowLo(szNoLink);
  sprintf(szLo+14,"%2u",cbRepeat); DelayInf();
}



void    RunDevices(void)
{
  if (fFlow == 1) return;

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;


  if ((fConnect == 1) && (wProgram != 0))
  {
    if ((cbWaitOnline > 0) && (cbWaitOnline % 10 == 5))
    {
      SaveDisplay();
      ShowHi(szManual); Clear();

      if (cbWaitOnline <= bMAXWAITONLINE)
        sprintf(szLo,"  ��������: %u c ",(uchar)(bMAXWAITONLINE-cbWaitOnline));
      else
        sprintf(szLo,"����������: %u c ",(uchar)bMAXWAITONLINE);

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
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3u",cbWaitAnswer); HideCurrTime(1);
      break;

#ifndef SKIP_E
    case DEV_ENERGY_E2:
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); HideCurrTime(1);
      if (IndexInBuff() > 0) sprintf(szLo," �����: %-4u ",IndexInBuff());
      break;
#endif
  }


  if ((mpSerial[ibPort] == SER_INPUT_MASTER))
  {
    DevicesInput();
  }

  if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
  {
    DevicesPostInput();
  }

  else if ((mpSerial[ibPort] == SER_OVERFLOW) ||
           (mpSerial[ibPort] == SER_BADLINK)  ||
           (mpSerial[ibPort] == SER_POSTANSWER_MODEM)  ||
           (mpSerial[ibPort] == SER_PAUSE))
  {
    DevicesPause();
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
      cbRepeat = GetMaxRepeats();

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
          ShowRepeat();

          QueryModemBaud(1);
          MakeLongPause(DEV_MODEM_BAUD,1);

          AddModRecord(EVE_MODEMBAUD_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTBAUD:
      cbRepeat = GetMaxRepeats();

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
          ShowRepeat();

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
          ShowRepeat();

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
          ShowRepeat();

          QueryModemCommon(1);
          MakeLongPause(DEV_MODEM_COMMON,1);

          AddModRecord(EVE_MODEMCOMMON2_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCOMMON:
      if (boCustomModem == true)
        MakePause(DEV_MODEM_NORMAL);
      else
        MakePause(DEV_MODEM_POSTCUSTOM);
      break;

    case DEV_MODEM_NORMAL:
      cbRepeat = GetMaxRepeats();

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
          ShowRepeat();

          QueryModemCustom();
          MakeLongPause(DEV_MODEM_CUSTOM,1);

          AddModRecord(EVE_MODEMCUSTOM_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCUSTOM:
      InitWaitAnswer();

      cbRepeat = GetMaxRepeats();

      fConnect = 1;
      QueryModemConnect();
      MakeLongPause(DEV_MODEM_CONNECT,bMaxConnect);

      AddModRecord(EVE_MODEMCONNECT);
      break;

    case DEV_MODEM_CONNECT:
      if ((mpSerial[ibPort] == SER_POSTANSWER_MODEM) && (ShowModemConnect() == 1))
      {
        ShowCanalNumber(ibDig);

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
          ShowRepeat();

          InitWaitAnswer();

          fConnect = 1;
          QueryModemConnect();
          MakeLongPause(DEV_MODEM_CONNECT, bMaxConnect);

          AddModRecord(EVE_MODEMCONNECT_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTCONNECT:

      if (exExtended == EXT_PROFILE_30MIN)
      {
        if (MakeExtended0() == 0) { MakePause(DEV_MODEM_STOP); break; }
        MakeExtended1();
        MakeExtended3();
        MakeExtended4();
        MakeExtended5();
        MakeExtended4T();
      }

      if ((exExtended == EXT_PROFILE_30MIN) && (boMntParams == false))
        MakeExtended2();

      if ((exExtended == EXT_CURRENT_3MIN) && (boMntParams == true))
        MakeExtended2();

      HideCurrTime(1);
      MakePause(GetNext());
      break;



    case DEV_MODEM_STOP:
      if (fKeyOn == 0)
        ShowCanalNumber(ibDig);
      else
        ShowHi(szManual);

      if ((diCurr.ibPhone != 0) && (fConnect == 1))
        MakePause(DEV_MODEM_POSTSTOP);
      else
        MakePause(DEV_MODEM_POSTBREAK);
      break;

    case DEV_MODEM_POSTSTOP:
      cbRepeat = GetMaxRepeats();

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
          ShowRepeat();

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
          ShowRepeat();

          QueryModemEscape();
          MakeLongPause(DEV_MODEM_ESCAPE,3);

          AddModRecord(EVE_MODEMESCAPE3_NEXT);
        }
      }
      break;

    case DEV_MODEM_POSTESCAPE:
      cbRepeat = GetMaxRepeats();

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
          ShowRepeat();

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

#ifndef SKIP_A

    case DEV_START_A2:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A2);
      break;

    case DEV_OPENCANAL_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_A2);
        else
          MakePause(DEV_POSTCORRECT_A2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenA();
          SetCurr(DEV_OPENCANAL_A2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_A2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeA();
      SetCurr(DEV_TIME_A2);
      break;

    case DEV_TIME_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueA = ReadTimeA();
        MakePause(DEV_POSTTIME_A2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeA();
          SetCurr(DEV_TIME_A2);
        }
      }
      break;


    case DEV_POSTTIME_A2:
      {
        uint iwDay1 = GetDayIndexMD(tiValueA.bMonth, tiValueA.bDay);
        ulong dwSecond1 = GetSecondIndex(tiValueA);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);

          if (dwDelta < GetCorrectLimit())                                        // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_A2); }
          else if (dwDelta < bMAJORCORRECT_A)                                     // ������� ���������
          {
            if (cbCorrects == 0)
            { ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_A2); }
            else
            {
              if (boManageTime == true)
              { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else if (dwDelta < wLIMITCORRECT_A)                                     // ������� ���������
          {
            if (boManageTime == true)
            { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
            else
            { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_A2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_A2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlA();
        SetCurr(DEV_POSTCONTROL_A2);
      }
      break;

    case DEV_POSTCONTROL_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_A2);   // �� !
        else
        {
          DelayOff(); // ErrorLink();
          cbRepeat--;

          QueryControlA();
          SetCurr(DEV_POSTCONTROL_A2);
        }
      }
      break;

    case DEV_MANAGE_A2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_A2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryManageA();
        SetCurr(DEV_POSTMANAGE_A2);
      }
      break;

    case DEV_POSTMANAGE_A2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTOPENCANAL_A2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryManageA();
          SetCurr(DEV_POSTMANAGE_A2);
        }
      }
      break;


    case DEV_POSTCORRECT_A2:
      Clear();

      cbRepeat = GetMaxRepeats();
      QueryTopA();
      SetCurr(DEV_TOP_A2);
      break;

    case DEV_TOP_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTopA();
        MakePause(DEV_POSTTOP_A2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTopA();
          SetCurr(DEV_TOP_A2);
        }
      }
      break;

    case DEV_POSTTOP_A2:
      cbRepeat2 = 0;
      if (diCurr.bDevice == 1)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderA();
        SetCurr(DEV_HEADER_A2);
      }
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderA_Plus(bBLOCKS_A);
        SetCurr(DEV_HEADER_A2PLUS);
      }
      break;

    case DEV_HEADER_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadHeaderA();
        MakePause(DEV_POSTHEADER_A2);
      }
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR1_A2);
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA();
          SetCurr(DEV_HEADER_A2);
        }*/
      }
      break;

    case DEV_ERROR1_A2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryIdA();
        SetCurr(DEV_POSTERROR1_A2);
      }
      break;

    case DEV_POSTERROR1_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdA() == 1)
        {
          QueryHeaderA();
          SetCurr(DEV_HEADER_A2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR1_A2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdA();
          SetCurr(DEV_POSTERROR1_A2);
        }
      }
      break;

    case DEV_POSTHEADER_A2:
      cbRepeat2 = 0;
      cbRepeat = GetMaxRepeats();
      QueryDataA();
      SetCurr(DEV_DATA_A2);
      break;

    case DEV_DATA_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTDATA_A2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR2_A2);
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDataA();
          SetCurr(DEV_DATA_A2);
        }*/
      }
      break;

    case DEV_ERROR2_A2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryIdA();
        SetCurr(DEV_POSTERROR2_A2);
      }
      break;

    case DEV_POSTERROR2_A2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdA() == 1)
        {
          QueryDataA();
          SetCurr(DEV_DATA_A2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR2_A2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdA();
          SetCurr(DEV_POSTERROR2_A2);
        }
      }
      break;

    case DEV_POSTDATA_A2:
      cbRepeat2 = 0;
      NewBoundsAbs16(iwMajor);
      if (ReadDataA() == 0)
        DoneProfile();
      else
      {
        (iwMajor == 0) ? (iwMajor = 8192/3 - 1) : (iwMajor--);

        cbRepeat = GetMaxRepeats();
        QueryHeaderA();
        SetCurr(DEV_HEADER_A2);
      }
      break;

    case DEV_HEADER_A2PLUS:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_DATA_A2PLUS);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
      break;

    case DEV_DATA_A2PLUS:
    {
      uchar i;
      for (i=0; i<bBLOCKS_A; i++)
        if (TestDataA_Plus(i) == 0) break;

      if (i != bBLOCKS_A)
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
      else
      {
        NewBoundsAbs16(iwMajor);
        for (i=0; i<bBLOCKS_A; i++)
        {
          if (ReadDataA_Plus(i) == 0) break;
          (iwMajor == 0) ? (iwMajor = 8192/3 - 1) : (iwMajor--);
        }

        if (i != bBLOCKS_A)
          DoneProfile();
        else
        {
          cbRepeat = GetMaxRepeats();
          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
    }
      break;

#endif

#ifndef SKIP_A

    case DEV_START_A3:
      cbRepeat = GetMaxRepeats();

      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A3);
      break;

    case DEV_OPENCANAL_A3:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
        MakePause(DEV_POSTOPENCANAL_A3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenA();
          SetCurr(DEV_OPENCANAL_A3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_A3:
      cbRepeat = GetMaxRepeats();
      QueryEnergyA(0);
      SetCurr(DEV_ENERGY_A3);
      break;

    case DEV_ENERGY_A3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentA();
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergyA(0);
          SetCurr(DEV_ENERGY_A3);
        }
      }
      break;

#endif

#ifndef SKIP_B

    case DEV_START_B2:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrl == true)
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
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeB();
      SetCurr(DEV_TIME_B2);
      break;

    case DEV_TIME_B2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueB = ReadTimeB();
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
      {
        uint iwDay1 = GetDayIndexMD(tiValueB.bMonth, tiValueB.bDay);
        ulong dwSecond1 = GetSecondIndex(tiValueB);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          ulong dwDelta = AbsLong(dwSecond1 - dwSecond2);

          if (dwDelta < GetCorrectLimit())                                        // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
          else if (dwDelta < bMAJORCORRECT_B)                                     // ������� ���������
          {
            if (cbCorrects == 0)
            {
              bDeltaOld = (uchar)dwDelta;
              (boShowMessages == true) ? DelayMsg() : DelayInf();
              ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_B2);
            }
            else
            {
              bDeltaNew = (uchar)dwDelta;
              if ((bDeltaNew < bDeltaOld) && (cbCorrects < 100))
              {
                bDeltaOld = bDeltaNew;
                cbCorrects++;
                MakePause(DEV_POSTOPENCANAL_B2);
              }
              else if (GetCurrHouIndex() == (tiValueB.bHour*2 + tiValueB.bMinute/30))
              { ShowLo(szCorrectNext); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
              else
              { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
            }
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_B2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = GetMaxRepeats();
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
/*
    case DEV_MANAGE_B2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_B2);
      else
      {
        cbRepeat = GetMaxRepeats();
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
*/

    case DEV_POSTCORRECT_B2:
      Clear();

      cbRepeat = GetMaxRepeats();
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

      cbRepeat = GetMaxRepeats();
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
          cbRepeat = GetMaxRepeats();
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
        else
        {
          cbRepeat = GetMaxRepeats();
          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }
      }
      else
      {
        cbRepeat = GetMaxRepeats();
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
/*
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderB();
          SetCurr(DEV_HEADER_B2);
        }*/
      }
      break;

    case DEV_ERROR_B2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
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
      NewBoundsAbs16(wBaseCurr);
      if (ReadHeaderB(0,0) == 0)
        DoneProfile();
      else
      {
        (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);

        cbRepeat = GetMaxRepeats();
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
    {
      uchar i;
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
        NewBoundsAbs16(wBaseCurr);
        for (i=0; i<bBLOCKS_B; i++)
        {
          if (ReadHeaderB(i,1) == 0) break;
          (wBaseCurr == 0) ? (wBaseCurr = 0xFFF0) : (wBaseCurr -= 0x0010);
        }

        if (i != bBLOCKS_B)
          DoneProfile();
        else
        {
          cbRepeat = GetMaxRepeats();
          QueryHeaderB_Plus(bBLOCKS_B);
          SetCurr(DEV_HEADER_B2PLUS);
        }
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
    {
        NewBoundsAbs32(dwBaseCurr);
        uchar i;
        for (i=0; i<17; i++)
        {
          if (ReadHeaderBNew(i,1) == 0) break;
          (dwBaseCurr == 0) ? (dwBaseCurr = 0x1FFF0) : (dwBaseCurr -= 0x0010);
        }

        if (i != 17)
          DoneProfile();
        else
        {
          cbRepeat = GetMaxRepeats();
          QueryHeaderBNew();
          SetCurr(DEV_HEADER_B2NEXT);
        }
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

#ifndef SKIP_B

    case DEV_START_B312:
      cbRepeat = GetMaxRepeats();
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B312);
      break;

    case DEV_OPENCANAL_B312:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
        MakePause(DEV_POSTOPENCANAL_B312);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenB();
          SetCurr(DEV_OPENCANAL_B312);
        }
      }
      break;

    case DEV_POSTOPENCANAL_B312:
      cbRepeat = GetMaxRepeats();
      QueryEnergyB(0);
      SetCurr(DEV_ENERGY_B312);
      break;

    case DEV_ENERGY_B312:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentB12();
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergyB(0);
          SetCurr(DEV_ENERGY_B312);
        }
      }
      break;

#endif

#ifndef SKIP_C

    case DEV_START_C2:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C2);
      break;

    case DEV_OPENCANAL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_C2);
        else
          MakePause(DEV_POSTCORRECT_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_C2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeC();
      SetCurr(DEV_TIME_C2);
      break;

    case DEV_TIME_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        MakePause(DEV_POSTTIME_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_TIME_C2);
        }
      }
      break;


    case DEV_POSTTIME_C2:
      {
        uint iwDay1 = GetDayIndexMD(tiValueC.bMonth, tiValueC.bDay);
        ulong dwSecond1 = GetSecondIndex(tiValueC);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_C2); }
          else if (GetCurrHouIndex() == (tiValueC.bHour*2 + tiValueC.bMinute/30)) // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_C2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_C2:
      if (++cbCorrects > 3)
        MakePause(DEV_POSTCORRECT_C2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlC();
        SetCurr(DEV_POSTCONTROL_C2);
      }
      break;

    case DEV_POSTCONTROL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultC() == 1))
        MakePause(DEV_POSTOPENCANAL_C2);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTOPENCANAL_C2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlC();
          SetCurr(DEV_POSTCONTROL_C2);
        }
      }
      break;


    case DEV_POSTCORRECT_C2:
      cbRepeat = GetMaxRepeats();
      QueryVersionC();
      SetCurr(DEV_VERSION_C2);
      break;

    case DEV_VERSION_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionC();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_C2, 1);
        else
          MakePause(DEV_POSTVERSION_C2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionC();
          SetCurr(DEV_VERSION_C2);
        }
      }
      break;

    case DEV_POSTVERSION_C2:
      cbRepeat = GetMaxRepeats();
      QueryTimeC();
      SetCurr(DEV_VALUE_C2);
      break;

    case DEV_VALUE_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        dwValueC = DateToHouIndex(tiValueC);
        MakePause(DEV_POSTVALUE_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_VALUE_C2);
        }
      }
      break;

    case DEV_POSTVALUE_C2:
      /*if (mpbHouCheck[ibDig] != 0)
      {
        Clear(); sprintf(szLo+2,"��������: %bu",mpbHouCheck[ibDig]);
        MakeLongPause(DEV_INIT_61_C2, 1);
      }
      else*/
      cbRepeat2 = 0;
      if (boShortProfileC == false)
      {
        InitHeaderC_6();

        cbRepeat = GetMaxRepeats();
        QueryHeaderC_6();
        SetCurr(DEV_HEADER_6_C2);
      }
      else
      {
        InitHeaderC_1();

        cbRepeat = GetMaxRepeats();
        QueryHeaderC_1();
        SetCurr(DEV_HEADER_1_C2);
      }
      break;

    case DEV_HEADER_6_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_6_C2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_6_C2);
/*
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderC_6();
          SetCurr(DEV_HEADER_6_C2);
        }*/
      }
      break;

    case DEV_ERROR_6_C2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryIdC();
        SetCurr(DEV_POSTERROR_6_C2);
      }
      break;

    case DEV_POSTERROR_6_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC_6();
          SetCurr(DEV_HEADER_6_C2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_6_C2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR_6_C2);
        }
      }
      break;

    case DEV_POSTHEADER_6_C2:
      cbRepeat2 = 0;
      if (ReadHeaderC_6() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_6_C2);
      break;

    case DEV_DATA_6_C2:
      cbRepeat = GetMaxRepeats();
      QueryHeaderC_6();
      SetCurr(DEV_HEADER_6_C2);
      break;

    case DEV_HEADER_1_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        cbRepeat2 = 0;
        if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x24) && (InBuff(3) == 0x05))      // ���� ��� ��������� ������
        {
          if (++iwMajor > GetMaxShutdown())
            DoneProfile();
          else
          {
            sprintf(szLo," ���������: %-4u   ",iwMajor);   // ���������� �������

            iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
            ShowProgressDigHou();

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_1_C2);
          }
        }
        else
        {
          iwMajor = 0;                                      // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_1_C2);
        }
      }
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_1_C2);
/*
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderC_1();
          SetCurr(DEV_HEADER_1_C2);
        }*/
      }
      break;

    case DEV_ERROR_1_C2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbRepeat2 > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryIdC();
        SetCurr(DEV_POSTERROR_1_C2);
      }
      break;

    case DEV_POSTERROR_1_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC_1();
          SetCurr(DEV_HEADER_1_C2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_1_C2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTERROR_1_C2);
        }
      }
      break;

    case DEV_POSTHEADER_1_C2:
      if (ReadHeaderC_1() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_1_C2);
      break;

    case DEV_DATA_1_C2:
      if (++wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderC_1();
        SetCurr(DEV_HEADER_1_C2);
      }
      break;

#endif

#ifndef SKIP_C

    case DEV_START_C3:
      cbRepeat = GetMaxRepeats();

      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C3);
      break;

    case DEV_OPENCANAL_C3:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
        MakePause(DEV_POSTOPENCANAL_C3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_C3:
      cbRepeat = GetMaxRepeats();
      QueryTimeC();
      SetCurr(DEV_TIME_C3);
      break;

    case DEV_TIME_C3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTIME_C3);
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_TIME_C3);
        }
      }
      break;

    case DEV_POSTTIME_C3:
      tiOffs = ReadTimeC();

      cbRepeat = GetMaxRepeats();
      QueryEnergyAbsC();
      SetCurr(DEV_ENERGY_C3);
      break;

    case DEV_ENERGY_C3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentC();
      else
      {
        if (cbRepeat == 0)
          ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergyAbsC();
          SetCurr(DEV_ENERGY_C3);
        }
      }
      break;

#endif

#ifndef SKIP_K

    case DEV_START_K2:
      if ((boControlK == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT2_K2);
      else
        MakePause(DEV_OPEN_K2);
      break;

    case DEV_PREVCORRECT2_K2:
      if (tiCurr.bSecond < bMINORCORRECT_K) {
        MakePause(DEV_CORRECT2_K2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT2_K2);
      }
      break;

    case DEV_CORRECT2_K2:
      ShowLo(szCorrectQ1);
      QueryCorrectK();
      SetCurr(DEV_POSTCORRECT2_K2);
      break;

    case DEV_POSTCORRECT2_K2:
      //ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_K2);
      break;

    case DEV_OPEN_K2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K2);
      break;

    case DEV_OPENCANAL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K2:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionK();
      SetCurr(DEV_OPTION_K2);
      break;

    case DEV_OPTION_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_K2);
        else
          MakePause(DEV_POSTPASSWORD_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K2);
        }
      }
      break;

    case DEV_POSTOPTION_K2:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_K2);
      break;

    case DEV_PASSWORD_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_K2);
        }
      }
      break;

    case DEV_POSTPASSWORD_K2:
      if ((boControlK != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_K2);
      else
        MakePause(DEV_POSTCORRECT_K2);
      break;

    case DEV_PREVTIME_K2:
      ShowPercent(53);

      cbRepeat = GetMaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_K2);
      break;

    case DEV_TIME_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_K2);
        }
      }
      break;

    case DEV_POSTTIME_K2:
      ShowPercent(54);

      cbRepeat = GetMaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_K2);
      break;

    case DEV_DATE_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_K2);
        }
      }
      break;


    case DEV_POSTDATE_K2:
      {
        uint iwDay1 = GetDayIndexMD(tiDig.bMonth, tiDig.bDay);
        ulong dwSecond1 = GetSecondIndex(tiDig);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_K2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_K2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_K2:
      cbRepeat = GetMaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_K2);
      break;

    case DEV_POSTCONTROL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_K2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_K2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_K2);
        }
      }
      break;


    case DEV_POSTCORRECT_K2:
      iwMajor = 0;
      ibMinor = 0;

      wBaseCurr = 0;
      tiDigPrev = tiCurr;

      cbRepeat = GetMaxRepeats();
      QueryHeaderK();
      SetCurr(DEV_HEADER_K2);
      break;

    case DEV_HEADER_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // ���� ��� ��������� ������
        {
          if (iwMajor >= 480)                           // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            uchar i;
            for (i=0; i<48; i++)
            {
              wBaseCurr++;

              sprintf(szLo," ���������: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_K2);
          }
        }
        else
        {
          ReadHeaderK();

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_K2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderK();
          SetCurr(DEV_HEADER_K2);
        }
      }
      break;

    case DEV_POSTHEADER_K2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataK() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_K2);
      }
      break;

    case DEV_DATA_K2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      break;

#endif

#ifndef SKIP_K

    case DEV_START_K3:
      ShowPercent(50);
      ibMinor = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K3);
      break;

    case DEV_OPENCANAL_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionK();
      SetCurr(DEV_OPTION_K3);
      break;

    case DEV_OPTION_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K3);
        }
      }
      break;

    case DEV_POSTOPTION_K3:
      ShowPercent(52+ibMinor);

      cbRepeat = GetMaxRepeats();
      QueryEnergySpecK(ibMinor);
      SetCurr(DEV_ENERGY_K3);
      break;

    case DEV_ENERGY_K3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_K3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecK(ibMinor);
          SetCurr(DEV_ENERGY_K3);
        }
      }
      break;

    case DEV_POSTENERGY_K3:
      ReadEnergyK(ibMinor);

      if ((diCurr.bDevice == 14) ||
          (diCurr.bDevice == 17))
        ReadCurrentK(1);
      else
      {
        if (++ibMinor < 4)
          MakePause(DEV_POSTOPTION_K3);
        else
          ReadCurrentK(4);
      }
      break;

#endif

#ifndef SKIP_P

    case DEV_START_P2:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenP();
      SetCurr(DEV_OPENCANAL_P2);
    break;

    case DEV_OPENCANAL_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTOPENCANAL_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenP();
          SetCurr(DEV_OPENCANAL_P2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_P2:
      ShowPercent(60);

      cbRepeat = GetMaxRepeats();
      QueryModeP();
      SetCurr(DEV_MODE_P2);
    break;

    case DEV_MODE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTMODE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryModeP();
          SetCurr(DEV_MODE_P2);
        }
      }
      break;

    case DEV_POSTMODE_P2:
      ShowPercent(70);

      cbRepeat = GetMaxRepeats();
      QueryPasswordP();
      SetCurr(DEV_PASSWORD_P2);
    break;

    case DEV_PASSWORD_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPASSWORD_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordP();
          SetCurr(DEV_PASSWORD_P2);
        }
      }
      break;

    case DEV_POSTPASSWORD_P2:
      ShowPercent(80);

      cbRepeat = GetMaxRepeats();
      QueryTimeP();
      SetCurr(DEV_TIME_P2);
      break;

    case DEV_TIME_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeP();

        if (boControlTime == true)
          MakePause(DEV_POSTTIME_P2);
        else
          MakePause(DEV_POSTCORRECT_P2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeP();
          SetCurr(DEV_TIME_P2);
        }
      }
      break;

    case DEV_POSTTIME_P2:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (dwSecond1 == dwSecond2)
        {
          MakePause(DEV_POSTCORRECT_P2);
        }
        else if (dwSecond1 > dwSecond2)
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dw = dwSecond1 - dwSecond2;
          if (dw > 5) dw = 5;
          iwMajor = dw % 0x10000;

          Clear(); sprintf(szLo+1,"���������: -%u �", iwMajor); DelayInf();
          iwMajor |= 0x8000;

          cbRepeat = GetMaxRepeats();
          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          ulong dw = dwSecond2 - dwSecond1;
          if (dw > 5) dw = 5;
          iwMajor = dw % 0x10000;

          Clear(); sprintf(szLo+1,"���������: +%u �", iwMajor); DelayInf();

          cbRepeat = GetMaxRepeats();
          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
      }
      break;

    case DEV_CORRECT_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        Clear();
        MakePause(DEV_POSTCORRECT_P2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryCorrectP();
          SetCurr(DEV_CORRECT_P2);
        }
      }
      break;

    case DEV_POSTCORRECT_P2:
      ShowPercent(90);

      cbRepeat = GetMaxRepeats();
      QueryRegisterP();
      SetCurr(DEV_REGISTER_P2);
      break;

    case DEV_REGISTER_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadRegisterP();
        if (ibMinorMax == 0)
          ErrorProfile();
        else
          MakePause(DEV_POSTREGISTER_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRegisterP();
          SetCurr(DEV_REGISTER_P2);
        }
      }
      break;

    case DEV_POSTREGISTER_P2:
      Setup1P();

      cbRepeat = GetMaxRepeats();
      QuerySetValueP(); // ���������� (ERR5), ���� ������ ����� 6 ����� ����� ������� �2
      SetCurr(DEV_SETVALUE_P2);
      break;

    case DEV_SETVALUE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTSETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QuerySetValueP();
          SetCurr(DEV_SETVALUE_P2);
        }
      }
      break;

    case DEV_POSTSETVALUE_P2:
      cbRepeat = GetMaxRepeats();
      QueryGetValueP();
      SetCurr(DEV_GETVALUE_P2);
      break;

    case DEV_GETVALUE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadGetValueP();
        MakePause(DEV_POSTGETVALUE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryGetValueP();
          SetCurr(DEV_GETVALUE_P2);
        }
      }
      break;

    case DEV_POSTGETVALUE_P2:
      cbRepeat = GetMaxRepeats();
      QueryProfileP();
      SetCurr(DEV_PROFILE_P2);
      break;

    case DEV_PROFILE_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPROFILE_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileP();
          SetCurr(DEV_PROFILE_P2);
        }
      }
      break;

    case DEV_POSTPROFILE_P2:
      ReadProfileP(tiDig);
      if ((++wBaseCurr > wBaseLast) || (bBreakEls == 1))
      {
        Setup2P();
        if (((MakeStopHou(0) == 0) || (iwMajor > 10)) && (iwDigHou != 0xFFFF))
        {
          DoneProfile();
        }
        else
        {
          if (BreakP())
          {
            DoneProfile();
          }
          else
          {
            NewBoundsAbs16(ibMinor++);

            if (cwSecondLockoutP > 60)
            {
              cbRepeat = GetMaxRepeats();
              QueryRepasswordP();
              SetCurr(DEV_REPASSWORD_P2);
            }
            else
            {
              cbRepeat = GetMaxRepeats();
              QuerySetValueP();
              SetCurr(DEV_SETVALUE_P2);
            }
          }
        }
      }
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryProfileP();
        SetCurr(DEV_PROFILE_P2);
      }
      break;

    case DEV_REPASSWORD_P2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTREPASSWORD_P2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRepasswordP();
          SetCurr(DEV_REPASSWORD_P2);
        }
      }
      break;

    case DEV_POSTREPASSWORD_P2:
      cbRepeat = GetMaxRepeats();
      QuerySetValueP();
      SetCurr(DEV_SETVALUE_P2);
      break;

#endif

#ifndef SKIP_P

    case DEV_START_P3:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenP();
      SetCurr(DEV_OPENCANAL_P3);
    break;

    case DEV_OPENCANAL_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTOPENCANAL_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenP();
          SetCurr(DEV_OPENCANAL_P3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_P3:
      ShowPercent(60);

      cbRepeat = GetMaxRepeats();
      QueryModeP();
      SetCurr(DEV_MODE_P3);
    break;

    case DEV_MODE_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTMODE_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryModeP();
          SetCurr(DEV_MODE_P3);
        }
      }
      break;

    case DEV_POSTMODE_P3:
      ShowPercent(70);

      cbRepeat = GetMaxRepeats();
      QueryPasswordP();
      SetCurr(DEV_PASSWORD_P3);
    break;

    case DEV_PASSWORD_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        MakePause(DEV_POSTPASSWORD_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordP();
          SetCurr(DEV_PASSWORD_P3);
        }
      }
      break;

    case DEV_POSTPASSWORD_P3:
      ShowPercent(80);

      cbRepeat = GetMaxRepeats();
      QueryRegisterP();
      SetCurr(DEV_REGISTER_P3);
      break;

    case DEV_REGISTER_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadRegisterP();
        MakePause(DEV_POSTREGISTER_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryRegisterP();
          SetCurr(DEV_REGISTER_P3);
        }
      }
      break;

    case DEV_POSTREGISTER_P3:
      ShowPercent(90);

      cbRepeat = GetMaxRepeats();
      QueryEngAbsP(0);
      SetCurr(DEV_ENERGY0_P3);
      break;

    case DEV_ENERGY0_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngAbsP(0);
        MakePause(DEV_POSTENERGY0_P3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsP(0);
          SetCurr(DEV_ENERGY0_P3);
        }
      }
      break;

    case DEV_POSTENERGY0_P3:
      ShowPercent(91);

      cbRepeat = GetMaxRepeats();
      QueryEngAbsP(1);
      SetCurr(DEV_ENERGY1_P3);
      break;

    case DEV_ENERGY1_P3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEngAbsP(1);

        ReadCurrentP();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsP(1);
          SetCurr(DEV_ENERGY1_P3);
        }
      }
      break;

#endif

#ifndef SKIP_Q

    case DEV_START_Q2:
      if ((boControlQ == false) && (fCurrCtrl == true))
      {
        ShowLo(szCorrectQ1);
        QueryCorrectQ();
        SetCurr(DEV_CORRECT_Q2);
      }
      else MakePause(DEV_OPEN_Q2);
      break;

    case DEV_CORRECT_Q2:
      ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_Q2);
      break;

    case DEV_OPEN_Q2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q2);
      break;

    case DEV_OPENCANAL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_Q2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q2:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q2);
      break;

    case DEV_OPTION_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionQ();
          SetCurr(DEV_OPTION_Q2);
        }
      }
      break;

    case DEV_POSTOPTION_Q2:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_Q2);
      break;

    case DEV_PASSWORD_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if ((boControlQ != false) && (fCurrCtrl == true))
          MakePause(DEV_POSTPASSWORD_Q2);
        else
          MakePause(DEV_POSTCORRECT_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_Q2);
        }
      }
      break;

    case DEV_POSTPASSWORD_Q2:
      ShowPercent(53);

      cbRepeat = GetMaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_Q2);
      break;

    case DEV_TIME_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_Q2);
        }
      }
      break;

    case DEV_POSTTIME_Q2:
      ShowPercent(54);

      cbRepeat = GetMaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_Q2);
      break;

    case DEV_DATE_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_Q2);
        }
      }
      break;

/*
    case DEV_POSTDATE_Q2:
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

        if (dwBuffC < bMINORCORRECT_K)                                          // ��� ���������
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_Q2); }
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // ������� ���������
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_Q2); }
        else
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
      }
      break;


    case DEV_CONTROL_Q2:
      cbRepeat = GetMaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_Q2);
      break;

    case DEV_POSTCONTROL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_Q2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_Q2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_Q2);
        }
      }
      break;


    case DEV_POSTCORRECT_Q2:
      iwMajor = 0;
      ibMinor = 0;

      InitHeaderQ();

      cbRepeat = GetMaxRepeats();
      QueryHeaderQ();
      SetCurr(DEV_HEADER_Q2);
      break;

    case DEV_HEADER_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // ���� ��� ��������� ������
        {
          if (iwMajor >= 480)                           // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            for (i=0; i<48; i++)
            {
              wBaseCurr++;

              sprintf(szLo," ���������: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_Q2);
          }
        }
        else
        {
          ReadHeaderQ();

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_Q2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderQ();
          SetCurr(DEV_HEADER_Q2);
        }
      }
      break;

    case DEV_POSTHEADER_Q2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataQ() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_Q2);
      }
      break;

    case DEV_DATA_Q2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      break;
*/
#endif


#ifndef SKIP_Q

    case DEV_START_Q3:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q3);
      break;

    case DEV_OPENCANAL_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q3);
      break;

    case DEV_OPTION_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_Q3);
        }
      }
      break;

    case DEV_POSTOPTION_Q3:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryEnergySpecQ();
      SetCurr(DEV_ENERGY_Q3);
      break;

    case DEV_ENERGY_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyQ();
        ReadCurrentQ();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecQ();
          SetCurr(DEV_ENERGY_Q3);
        }
      }
      break;

#endif

#ifndef SKIP_S

    case DEV_START_S2:
      cbRepeat = GetMaxRepeats();
      QueryVersionS();
      SetCurr(DEV_VERSION_S2);
      break;

    case DEV_VERSION_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionS();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_S2, 1);
        else
          MakePause(DEV_POSTVERSION_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionS();
          SetCurr(DEV_VERSION_S2);
        }
      }
      break;


    case DEV_POSTVERSION_S2:
      cbCorrects = 0;

      if (fCurrCtrl == true)
        MakePause(DEV_POSTOPENCANAL_S2);
      else
        MakePause(DEV_POSTCORRECT_S2);
      break;

    case DEV_POSTOPENCANAL_S2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeS();
      SetCurr(DEV_TIME_S2);
      break;

    case DEV_TIME_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeS();
        MakePause(DEV_POSTTIME_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeS();
          SetCurr(DEV_TIME_S2);
        }
      }
      break;


    case DEV_POSTTIME_S2:
      {
        uint iwDay1 = GetDayIndexMD(tiDig.bMonth, tiDig.bDay);
        ulong dwSecond1 = GetSecondIndex(tiDig);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_S2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_S2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_S2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_S2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlS(tiCurr);
        SetCurr(DEV_POSTOPENCANAL_S2);
      }
      break;


    case DEV_POSTCORRECT_S2:
      Clear(); ShowPercent(25);

      cbRepeat = GetMaxRepeats();
      QueryConfigS();
      SetCurr(DEV_CONFIG_S2);
      break;

    case DEV_CONFIG_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_S2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfigS();
          SetCurr(DEV_CONFIG_S2);
        }
      }
      break;

    case DEV_POSTCONFIG_S2:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryTimeS();
      SetCurr(DEV_VALUE_S2);
      break;

    case DEV_VALUE_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueS = ReadTimeS();
        dwValueS = DateToHouIndex(tiValueS);
        MakePause(DEV_POSTVALUE_S2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeS();
          SetCurr(DEV_VALUE_S2);
        }
      }
      break;

    case DEV_POSTVALUE_S2:
      ShowPercent(75);
      InitHeaderS();

      cbRepeat = GetMaxRepeats();
      QueryHeaderS();
      SetCurr(DEV_HEADER_S2);
      break;

    case DEV_HEADER_S2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_S2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderS();
          SetCurr(DEV_HEADER_S2);
        }
      }
      break;

    case DEV_POSTHEADER_S2:
      if (ReadHeaderS() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_S2);
      break;

    case DEV_DATA_S2:
      cbRepeat = GetMaxRepeats();
      QueryHeaderS();
      SetCurr(DEV_HEADER_S2);
      break;

#endif

#ifndef SKIP_S

    case DEV_START_S3:
      ShowPercent(25);

      cbRepeat = GetMaxRepeats();
      QueryConfigS();
      SetCurr(DEV_CONFIG_S3);
      break;

    case DEV_CONFIG_S3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadConfigS();
        MakePause(DEV_POSTCONFIG_S3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryConfigS();
          SetCurr(DEV_CONFIG_S3);
        }
      }
      break;

    case DEV_POSTCONFIG_S3:
      ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryEngMonS(0);
      SetCurr(DEV_ENERGY_S3);
      break;

    case DEV_ENERGY_S3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentS();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngMonS(0);
          SetCurr(DEV_ENERGY_S3);
        }
      }
      break;

#endif

#ifndef SKIP_U

    case DEV_START_U2:
      if ((boControlQ == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT_U2);
      else
        MakePause(DEV_OPEN_U2);
      break;

    case DEV_PREVCORRECT_U2:
      if (tiCurr.bSecond < bMINORCORRECT_U) {
        MakePause(DEV_CORRECT_U2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_U2);
      }
      break;

    case DEV_CORRECT_U2:
      ShowLo(szCorrectQ1);
      QueryCorrectU();
      SetCurr(DEV_OPEN_U2);
      break;

    case DEV_OPEN_U2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U2);
      break;

    case DEV_OPENCANAL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_U2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U2:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U2);
      break;

    case DEV_OPTION_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_U2);
        else
          MakePause(DEV_POSTPASSWORD_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionU();
          SetCurr(DEV_OPTION_U2);
        }
      }
      break;

    case DEV_POSTOPTION_U2:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_U2);
      break;

    case DEV_PASSWORD_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_U2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_U2);
        }
      }
      break;

    case DEV_POSTPASSWORD_U2:
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_U2);
      else
        MakePause(DEV_POSTCORRECT_U2);
      break;

    case DEV_PREVTIME_U2:
      ShowPercent(53);

      cbRepeat = GetMaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_U2);
      break;

    case DEV_TIME_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_U2);
        }
      }
      break;

    case DEV_POSTTIME_U2:
      ShowPercent(54);

      cbRepeat = GetMaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_U2);
      break;

    case DEV_DATE_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_U2);
        }
      }
      break;


    case DEV_POSTDATE_U2:
      {
        uint iwDay1 = GetDayIndexMD(tiDig.bMonth, tiDig.bDay);
        ulong dwSecond1 = GetSecondIndex(tiDig);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_U2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_U2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_U2:
      cbRepeat = GetMaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_U2);
      break;

    case DEV_POSTCONTROL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_U2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_U2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_U2);
        }
      }
      break;


    case DEV_POSTCORRECT_U2:
      if (boPlcUFlag == false)
        MakePause(DEV_PREVHEADER_U2);
      else
      {
        Clear();
        sprintf(szLo+4, "����: %u", bPlcUSize);
        MakeLongPause(DEV_PREVHEADER_U4, 1);
      }
      break;

    case DEV_PREVHEADER_U2:
      iwMajor = 0;
      InitHeaderU();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == 1)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = GetMaxRepeats();
      QueryHeaderU();
      SetCurr(DEV_HEADER_U2);
      break;

    case DEV_HEADER_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // ���� ��� ��������� ������
        {
          if (iwMajor >= 31)                           // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            sprintf(szLo," ���������: %-4u   ",++iwMajor);

            iwDigHou = (wHOURS+iwHardHou-wBaseCurr*48)%wHOURS;
            ShowProgressDigHou();

            NewBoundsAbs16(++wBaseCurr);

            if (wBaseCurr >= wHOURS/48)
              DoneProfile();
            else if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_U2);
          }
        }
        else
        {
          ReadHeaderU();

          if (SkipLine(ibDig, ibLineU+1) == 1)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_U2);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderU();
          SetCurr(DEV_HEADER_U2);
        }
      }
      break;

    case DEV_POSTHEADER_U2:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      else
      {
        if (ReadDataU() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U2);
      }
      break;

    case DEV_DATA_U2:
      if (wBaseCurr > wHOURS/48)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == 1)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = GetMaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      break;

#endif

#ifndef SKIP_U

    case DEV_START_U3:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U3);
      break;

    case DEV_OPENCANAL_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U3);
      break;

    case DEV_OPTION_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_U3);
        }
      }
      break;

    case DEV_POSTOPTION_U3:
      Clear(); ShowPercent(52);

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadEnergyU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = GetMaxRepeats();
      QueryEnergySpecU(ibLineU);
      SetCurr(DEV_ENERGY_U3);
      break;

    case DEV_ENERGY_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyU(ibLineU);

        if (SkipLine(ibDig, ibLineU+1) == true)
        {
          ReadEnergyU_SkipLine(ibLineU+1);
          ibLineU++;
        }

        uchar bMaxLine = GetMaxLine(ibDig);
        if (++ibLineU < bMaxLine)
        {
          Clear(); ShowPercent(52+ibLineU);
          QueryEnergySpecU(ibLineU);
          SetCurr(DEV_ENERGY_U3);
        }
        else
          ReadCurrentU(bMaxLine);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecU(ibLineU);
          SetCurr(DEV_ENERGY_U3);
        }
      }
      break;

#endif

#ifndef SKIP_U

    case DEV_PREVHEADER_U4:
      iwMajor = 0;
      InitHeaderU_Plc();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = GetMaxRepeats();
      QueryHeaderU_Plc();
      SetCurr(DEV_HEADER_U4);
      break;

    case DEV_HEADER_U4:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // ���� ��� ��������� ������
        {
          if (iwMajor >= wPlcUShutdown)                // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            iwMajor += bPlcUSize;
            sprintf(szLo," ���������: %-4u   ",iwMajor);

            wBaseCurr += bPlcUSize;
            iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
            ShowProgressDigHou();

            if (wBaseCurr >= wHOURS)
              DoneProfile();
            else if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_U4);
          }
        }
        else
        {
          ReadHeaderU_Plc();

          if (SkipLine(ibDig, ibLineU+1) == true)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_U4);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderU_Plc();
          SetCurr(DEV_HEADER_U4);
        }
      }
      break;

    case DEV_POSTHEADER_U4:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderU_Plc();
        SetCurr(DEV_HEADER_U4);
      }
      else
      {
        if (ReadDataU_Plc() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U4);
      }
      break;

    case DEV_DATA_U4:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == true)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = GetMaxRepeats();
        QueryHeaderU_Plc();
        SetCurr(DEV_HEADER_U4);
      }
      break;

#endif

#ifndef SKIP_V

    case DEV_START_V2:
      cbRepeat = GetMaxRepeats();
      QueryVersionV();
      SetCurr(DEV_VERSION_V2);
      break;

    case DEV_VERSION_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadVersionV() == false)
        {
          ShowHi(szBadVersion);
          DelayMsg(); ErrorProfile();
        }
        else
        {
          if (boHideMessages == false)
            MakeLongPause(DEV_POSTVERSION_V2, 1);
          else
            MakePause(DEV_POSTVERSION_V2);
        }
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionV();
          SetCurr(DEV_VERSION_V2);
        }
      }
      break;


    case DEV_POSTVERSION_V2:
      cbCorrects = 0;

      if (fCurrCtrl == true)
        MakePause(DEV_POSTOPENCANAL_V2);
      else
        MakePause(DEV_POSTCORRECT_V2);
      break;

    case DEV_POSTOPENCANAL_V2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeV();
      SetCurr(DEV_TIME_V2);
      break;

    case DEV_TIME_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeV();
        MakePause(DEV_POSTTIME_V2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeV();
          SetCurr(DEV_TIME_V2);
        }
      }
      break;


    case DEV_POSTTIME_V2:
      {
        uint iwDay1 = GetDayIndexMD(tiDig.bMonth, tiDig.bDay);
        ulong dwSecond1 = GetSecondIndex(tiDig);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_V2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_V2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_V2:
      if (++cbCorrects > bMINORREPEATS)
        MakePause(DEV_POSTCORRECT_V2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlV(tiCurr);
        SetCurr(DEV_POSTOPENCANAL_V2);
      }
      break;


    case DEV_POSTCORRECT_V2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryTimeV();
      SetCurr(DEV_VALUE_V2);
      break;

    case DEV_VALUE_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        dwTimeV = DateToHouIndex(ReadTimeV());
        MakePause(DEV_POSTVALUE_V2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeV();
          SetCurr(DEV_VALUE_V2);
        }
      }
      break;

    case DEV_POSTVALUE_V2:
      ShowPercent(75);
      InitHeaderV();

      cbRepeat = GetMaxRepeats();
      QueryHeaderV();
      SetCurr(DEV_HEADER_V2);
      break;

    case DEV_HEADER_V2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_V2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderV();
          SetCurr(DEV_HEADER_V2);
        }
      }
      break;

    case DEV_POSTHEADER_V2:
      if (ReadHeaderV() == 0)
        DoneProfile();
      else
        MakePause(DEV_DATA_V2);
      break;

    case DEV_DATA_V2:
      cbRepeat = GetMaxRepeats();
      QueryHeaderV();
      SetCurr(DEV_HEADER_V2);
      break;

#endif

#ifndef SKIP_V

    case DEV_START_V3:
      cbRepeat = GetMaxRepeats();
      QueryEngAbsV();
      SetCurr(DEV_ENERGY_V3);
      break;

    case DEV_ENERGY_V3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        ReadCurrentV();
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsV();
          SetCurr(DEV_ENERGY_V3);
        }
      }
      break;

#endif
  }

}
