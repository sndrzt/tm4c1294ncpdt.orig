/*------------------------------------------------------------------------------
KEY_HEALTH,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../flash/flash.h"
#include "../nvram/23x1024.h"



//                                         0123456789ABCDEF
static char const       szHealth[]      = "���������       ",
                        szFlash1[]      = "FLASH1:         ",
                        szFlash2[]      = "FLASH2:         ",
                        szNvram[]       = "NVRAM:          ",
                        szOK[]          = "OK",
                        szError[]       = "������";



static void Show(uchar  ibVal)
{
  switch (ibVal)
  {
    case 0: 
      ShowLo(szFlash1);
      GetFlashStatus1() == 0 ? strcpy(szLo+8, szOK) : strcpy(szLo+8, szError);
      break;

    case 1: 
      ShowLo(szFlash2);
      GetFlashStatus2() == 0 ? strcpy(szLo+8, szOK) : strcpy(szLo+8, szError);
      break;

    case 2: 
      ShowLo(szNvram);
      GetNvramStatus() == 0 ? strcpy(szLo+7, szOK) : strcpy(szLo+7, szError);
      break;
  }
}



void    key_GetHealth(void)
{
static uchar ibVal;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ShowHi(szHealth);

      ibVal = 0;
      Show(ibVal);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibVal > 2) ibVal = 0;
      Show(ibVal);
    }
    else Beep();
  }
  else Beep();
}
