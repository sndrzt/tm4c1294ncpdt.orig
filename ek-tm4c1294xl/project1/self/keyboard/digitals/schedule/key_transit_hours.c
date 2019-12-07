/*------------------------------------------------------------------------------
KEY_TRANSIT_HOURS.�

 
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../console.h"
#include "../../../memory/mem_schedule.h"
#include "../../../digitals/digitals.h"
#include "../../../digitals/schedule/schedule.h"
#include "../../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szControl[]     = "������ ���������",
                        szPort3[]       = "���� 3 ",
                        szPort4[]       = "���� 4 ",
                        szPortNo[]      = "���    ";


static void Show(uchar i)
{
  Clear();
  sprintf(szLo,"%02u:%02u", i/2, (i%2)*30);

  if (mpibAutoFlowHou[i] == 3-1)
    strcpy(szLo+7,szPort3);
  else if (mpibAutoFlowHou[i] == 4-1)
    strcpy(szLo+7,szPort4);
  else
    strcpy(szLo+7,szPortNo);

  if (enGlobal != GLB_WORK)
    szLo[6] = '.';

  sprintf(szLo+14,"%2u",i+1);
}



void    key_SetTransitHours(void)
{
static uchar i;

  if (bKey == bKEY_ENTER)
  {                                           
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT1;
      ShowHi(szControl);

      HalfHour();
    } 
    else if (enKeyboard == KBD_INPUT1)
    {
      enKeyboard = KBD_POSTENTER;

      i = 0;
      Show(i);
    }
    else if (enKeyboard == KBD_POSTINPUT1)
    {
      if ((i = GetCharLo(10,11) - 1) < 48)
      {
        enKeyboard = KBD_POSTENTER;
        Show(i);
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++i >= 48)
        i = 0;

      Show(i);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)
    {
      if (mpibAutoFlowHou[i] == 3-1)
        mpibAutoFlowHou[i] = 4-1;
      else if (mpibAutoFlowHou[i] == 4-1)
        mpibAutoFlowHou[i] = 0;
      else
        mpibAutoFlowHou[i] = 3-1;

      SaveCache(&chTransitHou);

      Show(i);
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

