/*------------------------------------------------------------------------------
KEY_TIMEDATE!C

 ��������� � �������� �������� ������� � ����
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_program.h"
#include "../../memory/mem_realtime.h"
#include "../../console.h"
#include "../../settings.h"
#include "../../isr/timer3.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../time/timedate_display.h"
#include "../../time/decret.h"
#include "../../time/correct1.h"
#include "../../time/correct3.h"
#include "key_timedate.h"



//                                         0123456789ABCDEF
static char const       szTime[]        = "������� �����   ",
                        szDate[]        = "������� ����    ",
                        szCorrectTime[] = "��������� ������",
                        szStartDate[]   = "���� �������    ",
                        szStartTime[]   = "����� �������   ",
                        szMaskTime[]    = "    __ __ __    ",
                        szMaskDate[]    = "    __ __ __    ";


static char             bSecondPrev;



void    key_SetCurrTime(void)
{
static time tiT;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      bSecondPrev = 60;

      ShowHi(szTime);
      Clear();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((tiT.bMinute = GetCharLo(7,8)) < 60)
      {
        tiT.bSecond = 0;

        enKeyboard = KBD_POSTENTER;
        bSecondPrev = 60;

        SetCurrTime(tiT);

        boSetTime = true;
        SaveCache(&chSetTime);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      tiT.bSecond = 0;

      enKeyboard = KBD_POSTENTER;
      bSecondPrev = 60;

      SetCurrTime(tiT);

      boSetTime = true;
      SaveCache(&chSetTime);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if ((tiT.bSecond = GetCharLo(10,11)) < 60)
      {
        enKeyboard = KBD_POSTENTER;
        bSecondPrev = 60;

        SetCurrTime(tiT);

        boSetTime = true;
        SaveCache(&chSetTime);
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((tiT.bHour = GetCharLo(4,5)) < 24)
      {
        enKeyboard = KBD_INPUT2;
        szLo[6] = ':';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((tiT.bMinute = GetCharLo(7,8)) < 60)
      {
        enKeyboard = KBD_INPUT3;
        szLo[9] = ':';
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal == GLB_PROGRAM)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMaskTime);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,5);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(7,8);
    }
    else if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetCurrTime(void)
{
  if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_SHOW))
  {
    if (f10Hz == true)
    {
      f10Hz = false;

      uchar bSecond = GetCurrTimeDate()->bSecond;
      if (bSecond != bSecondPrev)
      {
        bSecondPrev = bSecond;
        ShowTime(*GetCurrTimeDate());
      }
    }
  }
}



void    key_SetCurrDate(void)
{
static time tiT;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      bSecondPrev = 60;

      ShowHi(szDate);
      Clear();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      tiT.bYear = GetCharLo(10,11);

      if ((tiT.bYear >= bMINYEAR) &&
          (tiT.bYear <= bMAXYEAR) &&
          (tiT.bDay <= GetDaysInMonthYM(tiT.bYear, tiT.bMonth)))
      {
        enKeyboard = KBD_POSTENTER;
        bSecondPrev = 60;

        SetCurrDate(tiT);

        boSetDate = true;
        SaveCache(&chSetDate);

        MakeDecret();
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskDate);
      }
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      tiT.bDay = GetCharLo(4,5);

      if ((tiT.bDay > 0) && (tiT.bDay <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[6] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      tiT.bMonth = GetCharLo(7,8);

      if ((tiT.bMonth >= 1) && (tiT.bMonth <= 12))
      {
        enKeyboard = KBD_INPUT3;
        szLo[9] = '.';
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal == GLB_PROGRAM)
      {
        enKeyboard = KBD_INPUT1;
        ShowLo(szMaskDate);
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(4,5);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(7,8);
    }
    else if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,11);
    }
    else Beep();
  }
  else Beep();
}


void   auto_GetCurrDate(void)
{
  if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_SHOW))
  {
    if (f10Hz == true)
    {
      f10Hz = false;

      uchar bSecond = GetCurrTimeDate()->bSecond;
      if (bSecond != bSecondPrev)
      {
        bSecondPrev = bSecond;
        ShowDate(*GetCurrTimeDate());
      }
    }
  }
}



void    key_CorrectTime(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (Correct3Disabled())
      {
        Correct3(EVE_PROGRAM_2);
        BlockPrograms(bSET_CORRECT3_FLAG, bSET_CORRECT3_INFO);
      }
      else
      {
        enKeyboard = KBD_POSTENTER;
        bSecondPrev = 60;

        ShowHi(szCorrectTime);
        Clear();
      }
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (CorrectTime_Full(EVE_PROGRAM_2) == true)
        enKeyboard = KBD_SHOW;
      else
        LongBeep();
    }
    else Beep();
  }
  else Beep();
}



void    key_GetProgram18(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szStartDate);
      Clear();

      ShowDate(tiStart);
    }
    else Beep();
  }
  else Beep();
}


void    key_GetProgram19(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;

      ShowHi(szStartTime);
      Clear();

      ShowTime(tiStart);
    }
    else Beep();
  }
  else Beep();
}



// ��������� ��������� �������� ������� ��� ����������� ������������
void    ShowCurrTime(void)
{
  wProgram = bGET_CURRTIME;
  fSlide = 0;

  enKeyboard = KBD_POSTENTER;
  bSecondPrev = 60;

  ShowHi(szTime);
  Clear();
}


// ���������� ��������� �������� �������
void    HideCurrTime(bool  fClearProgram)
{
  cbShowCurrTime = 0;
  fSlide = false;

  if (fClearProgram == true)
  {
    enKeyboard = KBD_BEGIN;
    wProgram = 0;
  }
}
