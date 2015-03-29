/*------------------------------------------------------------------------------
KEY_LIMITS33.�


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../memory/mem_limits.h"
#include        "../../keyboard.h"
#include        "../../../display/display.h"
#include        "../../../digitals/limits.h"



//                                         0123456789ABCDEF
static char const       szFlag[]        = "    ��������    ",
                        szStartCan[]    = " ������ ������  ";
                     
static char const       *pszLimits[]   = { szFlag, szStartCan, "" };



void    ShowLimits33(void)
{
  Clear();
  sprintf(szLo+14,"%2u",ibX+1);

  if (mpboStartCan[ibX] == FALSE)
    strcpy(szLo+8,szNo);
  else         
    strcpy(szLo+8,szYes);

  if (enGlobal != GLB_WORK)
    szLo[7] = '.';
}



void    key_SetLimits33(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      LoadSlide(pszLimits);

      Canal();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowLimits33();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowLimits33();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) ibX = 0;

      ShowLimits33();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      mpboStartCan[ibX] = InvertBoolean(mpboStartCan[ibX]);
      ShowLimits33();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else Beep(); 
  }
  else Beep();
}
