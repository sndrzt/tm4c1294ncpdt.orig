/*------------------------------------------------------------------------------
KEY_GPS_SEASON.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/gps.h"
#include "../common/key_bool_blocked.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = " GPS ���������  ",
                        szMessage2[]    = "�������� ����� ?";

static char const       *pszMessages[]  = { szMessage1, szMessage2, "" };



void    key_SetGpsSeason(void)
{
  key_SetBoolBlocked(&chSeasonGps, pszMessages, ((bPortGps > 0) && (bPortGps <= bPORTS)), bSET_GPS_CONFIG);
}
