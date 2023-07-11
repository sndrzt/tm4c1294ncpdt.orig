/*------------------------------------------------------------------------------
KEY_MNT_ESC_S!C


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_extended_1.h"
#include "../../display/display.h"
#include "../keyboard.h"
#include "../../devices/devices_init.h"
#include "key_profile2mode.h"



//                                         0123456789ABCDEF
static char const       szMntEscS1[]    = "����� ����������",
                        szMntEscS2[]    = "    ��������    ",
                        szMntEscS3[]    = "   ���������    ",
                        szAutomatic[]   = " ������������   ",
                        szSize1[]       = " �� 1 ��������  ",
                        szSize16[]      = " �� 16 ���������",
                        szSize17[]      = " �� 17 ���������",
                        szByDigital[]   = " �� �������     ";

static char const       *pszMessages[]  = { szMntEscS1, szMntEscS2, szMntEscS3, szMntEscS4, "" };



static void Show(void)
{
  if (enProfile2Mode == P2M_SIZE_1)
    strcpy(szLo, szSize1);
  else if (enProfile2Mode == P2M_SIZE_16)
    strcpy(szLo, szSize16);
  else if (enProfile2Mode == P2M_SIZE_17)
    strcpy(szLo, szSize17);
  else if (enProfile2Mode == P2M_BY_DIGITAL)
    strcpy(szLo, szByDigital);
  else
    strcpy(szLo, szAutomatic);

  if (enGlobal != GLB_WORK)
    szLo[0] = '.';
}


void    key_SetProfile2Mode(void)
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
        if (enProfile2Mode == P2M_SIZE_1)
          enProfile2Mode = P2M_SIZE_16;
        else if (enProfile2Mode == P2M_SIZE_16)
          enProfile2Mode = P2M_SIZE_17;
        else if (enProfile2Mode == P2M_SIZE_17)
           enProfile2Mode = P2M_BY_DIGITAL;
        else
           enProfile2Mode = P2M_AUTOMATIC;

        Show();
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}
