/*------------------------------------------------------------------------------
_CORRECT31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_correct3.h"
#include "../../time/correct3.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "    �������     ",
                        szMessage2[]    = " ��� ���������  ",
                        szMessage3[]    = "    �������     ",
                        szMask[]        = "      ___       ";
                        
static char const      *pszMessages[]   = { szMessage1, szMessage2, szMessage3, "" };



static void Show(void)
{
  ShowChar(bCorrect3Max);
}


void    key_SetCorrect31(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boCorrect3Flag == true)
      {
        enKeyboard = KBD_POSTENTER;

        LoadSlide(pszMessages);
        Clear();

        Show();
      } 
      else BlockProgram(bSET_CORRECT3_FLAG);
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = GetCharLo(6,8);
      if ((ibX > 0) && (ibX <= 100))
      {
        bCorrect3Max = ibX;
        Show();
      }
      else 
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMask);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMask);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
