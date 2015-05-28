/*------------------------------------------------------------------------------
KEY_BLOCK_ESC,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_esc.h"
#include "../../output/esc/esc.h"
#include "../../console.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "     ������     ",
                        szMessage2[]    = "��������� Esc ? ",
                        szNo[]          = " ���            ",
                        szPartial[]     = " ���������      ",
                        szFull[]        = " ������         ";


static char const       *pszMessages[] = { szMessage1, szMessage2, "" };



static void Show(void)
{
  if (boBlockEsc == false)
    ShowLo(szNo);
  else if (boBlockEsc == true)
    ShowLo(szPartial);
  else
    ShowLo(szFull);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}



void    key_SetBlockEsc(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      LoadSlide(pszMessages);
      Show();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        if (boBlockEsc == false)
          boBlockEsc = true;
        else if (boBlockEsc == true)
          boBlockEsc = (bool)0x55;
        else
          boBlockEsc = false;

        SaveFile(&flBlockEsc);
        Show();
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
