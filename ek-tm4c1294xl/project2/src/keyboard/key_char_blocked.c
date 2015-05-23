/*------------------------------------------------------------------------------
KEY_CHAR_BLOCKED,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "key_char_blocked.h"



//                                            0123456789ABCDEF
static char const       szMaskChar[]       = "      ___       ",
                        szBlocked[]        = "���������:      ";

extern  char                    szCharLimits[bDISPLAY + bMARGIN];



void    key_SetCharBlocked(file const  *pflFile, char const  *pszSlide[], uchar  bMin, uchar  bMax, boolean  fBlocked, uint  wProgram)
{
  uchar *pbVal = (uchar *) pflFile->pbBuff;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (fBlocked == TRUE)
      {
        enKeyboard = KBD_POSTENTER;
        Clear();

        strcpy(szCharLimits, szClear);
        sprintf(szCharLimits+4, "%3u..%-3u", bMin, bMax);

        LoadSlide(pszSlide);
        ShowChar(*pbVal);
      }
      else
      {
        ShowHi(szBlocked);
        Clear();
        sprintf(szLo+1,"���������� %u",wProgram);
      }
    } 
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      uchar b = GetCharLo(6,8);
      if ((b >= bMin) && (b <= bMax))
      {
        *pbVal = b;
        SaveFile(pflFile);

        ShowChar(*pbVal);
      }
      else
      {
        enKeyboard = KBD_INPUT1;
        LongBeep();

        ShowLo(szMaskChar);
      }
    }
    else Beep();
  }


  else if (bKey < 10)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      enKeyboard = KBD_INPUT1;
      ShowLo(szMaskChar);
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }
  else Beep();
}
