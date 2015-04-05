/*------------------------------------------------------------------------------
DEVICES.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_energy_spec.h"
#include        "../memory/mem_limits.h"
#include        "../memory/mem_phones.h"
#include        "../display/display.h"
#include        "../keyboard/keyboard.h"
#include        "../keyboard/key_timedate.h"
#include        "../realtime/realtime.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_status.h"
#include        "../digitals/digitals_pause.h"
#include        "../digitals/digitals_messages.h"
#include        "../digitals/digitals_display.h"
#include        "../digitals/wait_answer.h"
#include        "../digitals/wait_query.h"
#include        "../digitals/current/current_run.h"
#include        "../digitals/profile/profile_run.h"
#include        "../digitals/checkup/checkup_run.h"
#include        "../digitals/params/params2.h"
#include        "../digitals/max_repeats.h"
#include        "../digitals/correct_limit.h"
#include        "../special/recalc_def.h"
#include        "../special/defects.h"
#include        "../sensors/device_a.h"
#include        "../sensors/device_b.h"
#include        "../sensors/device_b2.h"
#include        "../sensors/device_b12.h"
#include        "../sensors/device_c.h"
#include        "../serial/ports.h"
#include        "../serial/ports_modems.h"
#include        "../serial/modems.h"
#include        "../serial/speeds_display.h"
#include        "../digitals/answer.h"
#include        "../digitals/limits.h"
#include        "../digitals/digitals_display.h"
#include        "../flash/files.h"
#include        "../flash/records.h"
#include        "../time/timedate.h"
#include        "../time/delay.h"
#include        "devices_input.h"
#include        "devices_postinput.h"
#include        "devices_pause.h"
#include        "devices_init.h"
#include        "extended_1.h"
#include        "devices.h"



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



void    ShowProgressRepeat(void)
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
  ShowLo(szNoLink);
  sprintf(szLo+14,"%2u",cbRepeat); DelayInf();
}



void    RunDevices(void)
{
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
      sprintf(szLo+13,"%3u",cbWaitAnswer); HideCurrentTime(1);
      break;

#ifndef SKIP_E
    case DEV_ENERGY_E2:
      cbWaitQuery = bMAXWAITQUERY;
      sprintf(szLo+13,"%3bu",cbWaitAnswer); HideCurrentTime(1);
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
      if (boCustomModem == TRUE)
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
          ShowProgressRepeat();

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
        MakeExtended1();
//        MakeExtended4();
//        MakeExtended5();
//        MakeExtended3();
//        MakeExtended4T();
      }

      if ((exExtended == EXT_PROFILE_30MIN) && (boMntParams == FALSE))
        MakeExtended2();

      if ((exExtended == EXT_CURRENT_3MIN) && (boMntParams == TRUE))
        MakeExtended2();

      HideCurrentTime(1);
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

#ifndef SKIP_A

    case DEV_START_A2:                     
      cbCorrects = 0;

      cbRepeat = bMINORREPEATS;
      QueryOpenA();
      SetCurr(DEV_OPENCANAL_A2);
      break;

    case DEV_OPENCANAL_A2:                     
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultA() == 1))
      {
        if (fCurrCtrl == 1)
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

      cbRepeat = bMINORREPEATS;
      QueryTimeA();                          
      SetCurr(DEV_TIME_A2);          
      break;

    case DEV_TIME_A2:                      
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltA();                  
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
      uint iwDay1 = GetDayIndexMD(tiAlt.bMonth, tiAlt.bDay);                    // ���������� ���� � ������ ���� �������� ��������
      ulong dwSecond1 = GetSecondIndex(&tiAlt);                                 // ���������� ������ �������� ��������

      uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);                  // ���������� ���� � ������ ���� ���������
      ulong dwSecond2 = GetSecondIndex(&tiCurr);                                // ���������� ������ ���������

      if (iwDay1 != iwDay2)
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
      else
      {
        ulong dwDelta;
        if (dwSecond1 > dwSecond2)
        {
          dwDelta = dwSecond1 - dwSecond2;
          ShowDeltaTimeNegative(ibDig, dwDelta);
        }
        else
        {
          dwDelta = dwSecond2 - dwSecond1;
          ShowDeltaTimePositive(ibDig, dwDelta);
        }

        if (dwDelta < MinorCorrect())                                           // ��� ���������
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_A2); }     
        else if (dwDelta < bMAJORCORRECT_A)                                     // ������� ���������
        {
          if (cbCorrects == 0)
          { ShowLo(szCorrectYes); DelayInf();  MakePause(DEV_CONTROL_A2); }
          else
          {
            if (boManageTime == TRUE)
            { ShowLo(szManageYes); DelayInf();  MakePause(DEV_MANAGE_A2); }
            else
            { ShowLo(szManageNo); DelayMsg();  ErrorProfile(); }
          }
        }
        else if (dwDelta < wLIMITCORRECT_A)                                     // ������� ���������
        {
          if (boManageTime == TRUE)
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
        cbRepeat = bMINORREPEATS;                         
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
        cbRepeat = bMINORREPEATS;
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

      cbRepeat = bMINORREPEATS;
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
        cbRepeat = bMINORREPEATS;
        QueryHeaderA();
        SetCurr(DEV_HEADER_A2);
      }
      else
      {
        cbRepeat = bMINORREPEATS;
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
        cbRepeat = bMINORREPEATS;
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
      cbRepeat = bMINORREPEATS;
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
        cbRepeat = bMINORREPEATS;
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

        cbRepeat = bMINORREPEATS;
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
          cbRepeat = bMINORREPEATS;
          QueryHeaderA_Plus(bBLOCKS_A);
          SetCurr(DEV_HEADER_A2PLUS);
        }
      }
    }
      break;

#endif

#ifndef SKIP_A

    case DEV_START_A3:
      cbRepeat = bMINORREPEATS;

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
      cbRepeat = bMINORREPEATS;
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

      cbRepeat = bMINORREPEATS;
      QueryOpenB();
      SetCurr(DEV_OPENCANAL_B2);
      break;

    case DEV_OPENCANAL_B2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultB() == 1))
      {
        if (fCurrCtrl == 1)
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
    {
      uint iwDay1 = GetDayIndexMD(tiAlt.bMonth, tiAlt.bDay);                    // ���������� ���� � ������ ���� �������� ��������
      ulong dwSecond1 = GetSecondIndex(&tiAlt);                                 // ���������� ������ �������� ��������

      uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);                  // ���������� ���� � ������ ���� ���������
      ulong dwSecond2 = GetSecondIndex(&tiCurr);                                // ���������� ������ ���������

      if (iwDay1 != iwDay2)
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
      else
      {
        ulong dwDelta;
        if (dwSecond1 > dwSecond2)
        {
          dwDelta = dwSecond1 - dwSecond2;
          ShowDeltaTimeNegative(ibDig, dwDelta);
        }
        else
        {
          dwDelta = dwSecond2 - dwSecond1;
          ShowDeltaTimePositive(ibDig, dwDelta);
        }

        if (dwDelta < MinorCorrect())                                           // ��� ���������
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_B2); }
        else if (dwDelta < bMAJORCORRECT_B)                                     // ������� ���������
        {
          if (cbCorrects == 0)
          {
            bDeltaOld = (uchar)dwDelta;
            (boShowMessages == TRUE) ? DelayMsg() : DelayInf();
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
            else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))
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
/*
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
*/

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
      NewBoundsAbs16(wBaseCurr);
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
          cbRepeat = bMINORREPEATS;
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
          cbRepeat = bMINORREPEATS;
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
  }

}
