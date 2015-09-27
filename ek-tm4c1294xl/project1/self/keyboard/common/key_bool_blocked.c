/*------------------------------------------------------------------------------
KEY_BOOL_BLOCKED,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "key_bool_blocked.h"



//                                            0123456789ABCDEF
static char const       szBlocked[]        = "���������:      ";



void    key_SetBoolBlocked(cache const  *pch, char const  *pszMessages[], bool  fNonBlocked, uint  wProgram)
{
  bool *pboValue = (bool *) pch->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)  
    {
      if (fNonBlocked)
      {
        enKeyboard = KBD_INPUT1;
        Clear();

        LoadSlide(pszMessages);
        ShowBool(*pboValue);
      }
      else
      {
        ShowHi(szBlocked);
        Clear();
        sprintf(szLo+1,"���������� %u",wProgram);
      }
    }
    else Beep();
  }
  

  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {           
        *pboValue = InvertBool(*pboValue);
        SaveCache(pch);

        ShowBool(*pboValue);
      }
      else Beep(); 
    }
    else Beep(); 
  } 
  else Beep(); 
}
