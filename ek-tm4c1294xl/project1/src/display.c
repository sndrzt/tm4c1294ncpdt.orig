/*------------------------------------------------------------------------------
DISPLAY.C


------------------------------------------------------------------------------*/

#include        <string.h>
#include        "main.h"



char                    szHi[bDISPLAY + bMARGIN],
                        szLo[bDISPLAY + bMARGIN];



void    InitDisplay(void) {
  strcpy(szHi, "     ���+2      ");
  strcpy(szLo, "  [---------]   ");
}
