/*------------------------------------------------------------------------------
_CLEAR.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_energy_spec.h"
#include "../../memory/mem_profile.h"
#include "../../console.h"
//#include "../../access.h"
#include "../../realtime/realtime.h"
#include "../../realtime/realtime_spec.h"
#include "../../impulses/energy_spec.h"
#include "../../digitals/digitals.h"
#include "../../special/calc.h"
#include "../../special/recalc.h"



//                                         0123456789ABCDEF
static char const       szClearCanals1[]  = "�������������   ",
                        szClearCanals2[]  = "������� ������� ",
                        szCanalsTitle[]   = "������:         ",
                        szDateFrom[]      = "���� ��:        ",
                        szDateTo[]        = "���� ��:        ",
                        szTimeFrom[]      = "����� ��:       ",
                        szTimeTo[]        = "����� ��:       ",
                        szCanalFrom[]     = " ��: __",
                        szCanalTo[]       = " ��: __";



static uchar            ibXmin, ibXmax, ibYmin, ibYmax, ibZmin, ibZmax;
static uint             iwA, iwAmin, iwAmax;



void    ShowDateClear(uchar  j)
{
  tiAlt = tiCurr;
  ulong dwBuffC = DateToHouIndex();

  dwBuffC -= (uint)48*j + GetHouIndex();

  HouIndexToDate(dwBuffC);

  sprintf(szLo+7,"%02u.%02u.%02u",tiAlt.bDay,tiAlt.bMonth,tiAlt.bYear);
  sprintf(szHi+13,".%02u",j);
}


void    ShowTimeClear(uchar  j)
{
  sprintf(szLo+1,"%02u:%02u",j/2,(j%2)*30);
  sprintf(szHi+13,".%02u",j);
}


void    ShowAnswerClear(void)
{
  Clear();
  ShowBoolean(enKeyboard != KBD_INPUT5);
}



void    key_ClearCanals(void)
{ 
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;

      ShowHi(szClearCanals2);
      Clear(); DelayInf();

      ShowHi(szCanalsTitle);
      strcpy(szLo+0,szCanalFrom);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      ibXmin = GetCharLo(5,6) - 1;
      if (ibXmin < bCANALS)
      {
        enKeyboard = KBD_INPUT2;
        strcpy(szLo+8,szCanalTo);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      ibXmax = GetCharLo(13,14) - 1;
      if ((ibXmax < bCANALS) && (ibXmax >= ibXmin))
      {
        enKeyboard = KBD_INPUT3;
        ShowHi(szDateFrom); Clear();

        ibZmin = 0;
        ShowDateClear(ibZmin);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_INPUT3)
    {
      enKeyboard = KBD_POSTINPUT3;
      ShowHi(szTimeFrom);

      ibYmin = 0;
      ShowTimeClear(ibYmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      enKeyboard = KBD_INPUT4;
      ShowHi(szDateTo);
      Clear();

      ibZmax = ibZmin;
      ShowDateClear(ibZmax);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      enKeyboard = KBD_POSTINPUT4;
      ShowHi(szTimeTo);

      (ibZmax == ibZmin) ? (ibYmax = ibYmin) : (ibYmax = 0);
      ShowTimeClear(ibYmax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      iwAmin = (PrevDayIndex(ibZmin) + ibYmin) % wHOURS;
      iwAmax = (PrevDayIndex(ibZmax) + ibYmax) % wHOURS;

      enKeyboard = KBD_INPUT5;

      ShowHi(szClearCanals2);
      ShowAnswerClear();
    }
    else if (enKeyboard == KBD_POSTINPUT5)
    {
      enKeyboard = KBD_SHOW;
      Clear();

      (ClearCanals(1) == 1) ? OK() : Error();

      ShowHi(szCanalsTitle);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_INPUT3)
    {
      if (++ibZmin >= wHOURS/48) ibZmin = 0;
      ShowDateClear(ibZmin);
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      if (++ibYmin >= 48) ibYmin = 0;
      ShowTimeClear(ibYmin);
    }
    else if (enKeyboard == KBD_INPUT4)
    {
      (ibZmax > 0) ? (ibZmax--) : (ibZmax = ibZmin);
      ShowDateClear(ibZmax);
    }
    else if (enKeyboard == KBD_POSTINPUT4)
    {
      if (ibZmax == ibZmin)
      { if (++ibYmax >= 48) ibYmax = ibYmin; }
      else
      { if (++ibYmax >= 48) ibYmax = 0; }
      
      ShowTimeClear(ibYmax);
    }
    else if ((enKeyboard == KBD_INPUT5) || (enKeyboard == KBD_POSTINPUT5))
    {           
      (enKeyboard == KBD_INPUT5) ? (enKeyboard = KBD_POSTINPUT5) : (enKeyboard = KBD_INPUT5);
      ShowAnswerClear(); 
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(13,14);
    }
    else Beep(); 
  }
  else Beep();
}

