/*------------------------------------------------------------------------------
KEY_ENBL_PARAMS,C

 ���� ���������� ������ ���������� ����������
------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/params/params.h"
#include "../../key_bool.h"


//                                         0123456789ABCDEF
static char const       szMessage[]     = "��������� ?     ";

static char const       *pszMessages[]  = { szMessage, "" };



void    key_SetEnblParams(void)
{
  key_SetBool(&flParamsFlag, pszMessages);
}
