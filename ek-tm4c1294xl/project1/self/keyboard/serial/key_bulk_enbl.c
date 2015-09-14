/*------------------------------------------------------------------------------
KEY_BULK_ENABLE.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_program.h"
#include "../common/key_bool.h"
#include "key_bulk_enbl.h"



#ifdef  BULK

//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   ����������   ",
                        szMessage2[]    = "    ��������    ",
                        szMessage3[]    = "   �������� ?   ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, "" };



void    key_SetBulkEnable(void)
{
  key_SetBool(&chBulkEnbl, pszMessages);
}

#endif

