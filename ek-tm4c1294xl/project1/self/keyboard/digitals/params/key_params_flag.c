/*------------------------------------------------------------------------------
KEY_PARAMS_FLAG,C

 ���� ���������� ������ ���������� ����������
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"



//                                         0123456789ABCDEF
static char const       szMessage[]     = "��������� ?     ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetParamsFlag(void)
{
  key_SetBool(&chParamsFlag, pszMessages);
}
