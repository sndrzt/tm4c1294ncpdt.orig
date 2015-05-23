/*------------------------------------------------------------------------------
KEY_MNT_PARAMS,C


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/params/params.h"
#include "../../key_flag.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "����� ����������",
                        szMessage2[]    = " ��� ���������� ",
                        szTrue[]        = " 3 ������       ",
                        szFalse[]       = " 30 �����       ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetMntParams(void)
{
  key_SetFlag(&flMntParams, pszMessages, szTrue, szFalse);
}
