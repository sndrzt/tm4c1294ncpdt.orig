/*------------------------------------------------------------------------------
KEY_MANAGE_TIME.C


------------------------------------------------------------------------------*/

#include        "../../../main.h"
#include        "../../../memory/mem_digitals.h"
#include        "../../../devices/devices_init.h"
#include        "../../key_flag.h"



//                                         0123456789ABCDEF
static char const       szManage[]      = "������ �������� ",
                        szTime[]        = "������� � ���� ?";

static char const       *pszManageTime[] = { szManage, szTime, "" };




void    key_SetManageTime(void)
{
  key_SetFlag(&flManageTime, pszManageTime);
}
