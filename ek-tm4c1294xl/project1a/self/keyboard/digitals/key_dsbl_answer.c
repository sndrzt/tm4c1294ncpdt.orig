/*------------------------------------------------------------------------------
KEY_DSBL_ANSWER,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../digitals/dsbl_answer.h"
#include "../common/key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " ������ ������  ",
                        szMessage2[]    = "   �� �������   ",
                        szMessage3[]    = "�� ����� ������ ",
                        szMessage4[]    = "   ���������    ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetDsblAnswer(void)
{
  key_SetBool(&chDsblAnswer, pszMessages);
}
