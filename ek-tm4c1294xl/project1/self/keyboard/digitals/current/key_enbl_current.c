/*------------------------------------------------------------------------------
KEY_ENBL_CURRENT,C

 ���� ���������� ������ ������������ ��������
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../../digitals/profile/profile_core.h"
#include "../../key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = " 3-���. ������ ?";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetEnblCurrent(void)
{
  key_SetBool(&chEnblCurrent, pszMessages);
}
