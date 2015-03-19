/*------------------------------------------------------------------------------
KEY_KEYS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../keyboard.h"
#include        "../../display/display.h"
#include        "../../digitals/profile_core.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szKeys[]        = "������          ",
                        szMaskKeys[]    = "_____________";
                      


void    ShowKeys(void)
{
  Clear();

  if ((enGlobal == GLB_PROGRAM) || ((enGlobal == GLB_REPROGRAM) /*&& SuperUser()*/))
    strcpy(szLo, mpphKeys[ibX].szNumber);
  else
    strcpy(szLo, "*************");

  sprintf(szLo+14,"%2bu",ibX+1);
}



void    ShowMaskKeys(void)
{
  enKeyboard = KBD_INPUT2;
  ShowLo(szMaskKeys);

  ibY = 0;
}



void    key_SetKeys(void)
{
  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      if (boEnableKeys != boTrue)
      { BlockProgram(bSET_ENABLE_KEYS); return; }
      else
      {
        enKeyboard = KBD_INPUT1;
        Canal();

        ShowHi(szKeys);
      }
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      ibX = 0;
      ShowKeys();
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((ibX = GetCharLo(10,11) - 1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;
        ShowKeys();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibX >= bCANALS) 
        ibX = 0;

      ShowKeys();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {      
      if (ibY > 0)
      {
        enKeyboard = KBD_POSTENTER;

        szLo[ibY] = 0;

        AddSysRecordReprogram(EVE_EDIT_KEY10);
        AddSysRecordReprogram(EVE_EDIT_KEY11);
        strcpy(&mpphKeys[ibX].szNumber,szLo);
        AddSysRecordReprogram(EVE_EDIT_KEY20);
        AddSysRecordReprogram(EVE_EDIT_KEY21);
      }

      if (enKeyboard == KBD_POSTENTER)
      {
        if (++ibX >= bCANALS) 
          ibX = 0;

        ShowKeys();
      }
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enKeyboard == KBD_POSTENTER) || (enKeyboard == KBD_POSTINPUT2))
    {
      if (enGlobal != GLB_WORK)
        ShowMaskKeys();
      else Beep();
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (ibX > 0) ibX--; else  ibX = bCANALS-1;

      ShowKeys();
    }
    else Beep();
  }


  else if (bKey < 10)
  {        
    if (enKeyboard == KBD_POSTENTER)
    {
      if (enGlobal != GLB_WORK)
        ShowMaskKeys();
      else Beep();
    }

    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;

      if (ibY < bPHONENUMBER)
        szLo[ibY++] = szDigits[bKey];
      else Beep();
    }
    else Beep(); 
  }
  else Beep();
}
