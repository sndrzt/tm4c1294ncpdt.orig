/*------------------------------------------------------------------------------
_SEASON.C

 ��������� � �������� ��� ��������� �� �������� �����
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_settings.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../beep.h"
#include        "../rtc.h"
#include        "../timedate.h"



//                                         0123456789ABCDEF
static char const       szMaskSeason[]  = "     __ __      ",
                        szWinter[]      = "������ �����    ",
                        szSummer[]      = "������ �����    ";



void    ShowSummer(void)
{
  sprintf(szLo+5,"%02u.%02u",
                 tiSummer.bDay,   
                 tiSummer.bMonth);
}



void    ShowWinter(void)
{
  sprintf(szLo+5,"%02u.%02u",
                 tiWinter.bDay,   
                 tiWinter.bMonth);
}



void    key_SetSeason(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      Clear();

      switch (bProgram)
      {
        case bSET_SUMMER:  ShowHi(szSummer); 
                           ShowSummer();  break;
        case bSET_WINTER:  ShowHi(szWinter); 
                           ShowWinter();  break;
      }
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      tiKey.bDay = GetChar(5,6);

      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT2;
        szLo[7] = '.';
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      tiKey.bMonth = GetChar(8,9);
      tiKey.bYear  = (*PGetCurrTimeDate()).bYear;

      if ((tiKey.bMonth > 0) && (tiKey.bMonth <= 12))
      {
        memcpy(&tiAlt, &tiKey, sizeof(time));

        if (tiKey.bDay <= DaysInMonth())
        {
          enKeyboard = KBD_POSTENTER;

          switch (bProgram)
          {
            case bSET_SUMMER:  memcpy(&tiSummer, &tiKey, sizeof(time)); 
                               ShowSummer();  break;
            case bSET_WINTER:  memcpy(&tiWinter, &tiKey, sizeof(time)); 
                               ShowWinter();  break;
          }
        }
        else
        {  
          enKeyboard = KBD_INPUT1;
          LongBeep();

          ShowLo(szMaskSeason);
        }
      }
      else Beep();
    }
  }


  else if (bKey < 10)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
      {
        if (deDecret != DEC_CUSTOM)        
          NeedProgram(bSET_DECRET); 
        else  
        {
          enKeyboard = KBD_INPUT1;
          ShowLo(szMaskSeason);
        }
      }
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(5,6);
    }
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(8,9);
    }
  }
  else Beep();
}
