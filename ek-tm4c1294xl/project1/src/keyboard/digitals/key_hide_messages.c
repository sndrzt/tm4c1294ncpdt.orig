/*------------------------------------------------------------------------------
KEY_HIDE_MESSAGES.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_digitals.h"
#include        "../../digitals/digitals_run.h"
#include        "../key_flag.h"



//                                           0123456789ABCDEF
static char const       szHideMessages1[] = "���������� �����",
                        szHideMessages2[] = "  �� ���������  ";

static char const       *pszHideMessages[] = { szHideMessages1, szHideMessages2, "" };



void    key_SetHideMessages(void)
{
  key_SetFlag(&flHideMessages, pszHideMessages);
}
