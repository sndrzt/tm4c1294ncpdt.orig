/*------------------------------------------------------------------------------
KEY_ENBL_PROFILE,C

 ���� ���������� ��������������� ������ ����������� ��������
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_digitals.h"
#include "../../../digitals/profile/profile_core.h"
#include "../../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = "30-���. ������ ?";

static char const       *pszMessages[]   = { szMessage1, szMessage2, "" };



void    key_SetEnblProfile(void)
{
  key_SetBool(&chEnblProfile, pszMessages);
}
