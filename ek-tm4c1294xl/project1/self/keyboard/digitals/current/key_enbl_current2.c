/*------------------------------------------------------------------------------
KEY_ENBL_CURRENT2.C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../memory/mem_current.h"
#include "../../../digitals/current/current2.h"
#include "../../common/key_bool.h"
#include "key_enbl_current2.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ����������   ",
                        szMessage2[]     = "  ������������  ",
                        szMessage3[]     = "  �������� ���  ",
                        szMessage4[]     = " �������������  ",
                        szMessage5[]     = "  ��������� ?   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, "" };



void    key_SetEnblCurrent2(void)
{
  key_SetBool(&chEnblCurrent2, pszMessages);
}
