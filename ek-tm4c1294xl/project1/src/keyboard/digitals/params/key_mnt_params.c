/*------------------------------------------------------------------------------
KEY_MNT_PARAMS.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../digitals/params/params.h"
#include        "../../../console.h"
#include        "../../key_flag.h"



//                                         0123456789ABCDEF
static char const       szMntParams[]   = "���������: �����",
                        szMinute30[]    = " 30 �����       ",
                        szMinute3[]     = " 3 ������       ";



void    ShowMntParams(boolean  bo)
{
  if (bo == FALSE)
    strcpy(szLo,szMinute30);
  else
    strcpy(szLo,szMinute3);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetMntParams(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      Clear();

      ShowHi(szMntParams);
      ShowMntParams(boMntParams);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enGlobal != GLB_WORK)
    {
      if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
      {
        boMntParams = InvertBoolean(boMntParams);
        ShowMntParams(boMntParams);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
