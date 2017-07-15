/*------------------------------------------------------------------------------
KEY_ENBL_DIAGRAM,C


------------------------------------------------------------------------------*/

#include "../../../main.h"
#include "../../../digitals/extended/diagram.h"
#include "../../common/key_bool.h"



//                                          0123456789ABCDEF
static char const       szMessage1[]     = "   ���������    ",
                        szMessage2[]     = "����. ��������� ",
                        szMessage3[]     = "  �� ���������  ",
                        szMessage4[]     = "   �� ����� ?   ";

static char const       *pszMessages[]   = { szMessage1, szMessage2, szMessage3, szMessage4, "" };



void    key_SetEnblDiagram(void)
{
  key_SetBool(&chEnblDiagram, pszMessages);
}
