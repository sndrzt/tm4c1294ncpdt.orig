/*------------------------------------------------------------------------------
RESPONSE1_CRC.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_settings.h"
#include        "../include/states.h"
#include        "../serial/ports.h"
#include        "out_rtc.h"
#include        "out_groups.h"
#include        "out_tariffs.h"
#include        "out_digitals.h"
#include        "out_flash.h"
#include        "out_delay.h"
#include        "out_console.h"
#include        "response_crc.h"
#include        "response254_crc.h"
#include        "response255_crc.h"



void    Response1_CRC(void)
{
    switch (bInBuff4)
    {
      case bINQ_GETGLOBAL:
        LongResult(enGlobal);
        break;

      case bINQ_GETCURRTIME:
        OutGetCurrTimeDate();
        break;

      case bINQ_GETGROUP:
        OutGetGroup();
        break;

      case bINQ_SETGROUP:
        OutSetGroup();
        break;

      case bINQ_GETPUBLIC_TARIFFS: OutGetPublicTariffs(); break;
      case bINQ_SETPUBLIC_TARIFFS: OutSetPublicTariffs(); break;

      case bINQ_GETOLDPOWTARIFFS: OutGetOldPowTariffs(); break;
      case bINQ_SETOLDPOWTARIFFS: OutSetOldPowTariffs(); break;

      case bINQ_GETOLDENGTARIFFS: OutGetOldEngTariffs(); break;
      case bINQ_SETOLDENGTARIFFS: OutSetOldEngTariffs(); break;

      case bINQ_GETOLDPUBTARIFFS: OutGetOldPubTariffs(); break;
      case bINQ_SETOLDPUBTARIFFS: OutSetOldPubTariffs(); break;

      case bINQ_GETNEWPOWTARIFFS: OutGetNewPowTariffs(); break;
      case bINQ_SETNEWPOWTARIFFS: OutSetNewPowTariffs(); break;

      case bINQ_GETNEWENGTARIFFS: OutGetNewEngTariffs(); break;
      case bINQ_SETNEWENGTARIFFS: OutSetNewEngTariffs(); break;

      case bINQ_GETNEWPUBTARIFFS: OutGetNewPubTariffs(); break;
      case bINQ_SETNEWPUBTARIFFS: OutSetNewPubTariffs(); break;

      case bINQ_GETTRANS_ENG: Common(mpreTransEng, sizeof(real)*bCANALS); break;
      case bINQ_GETTRANS_CNT: Common(mpreTransCnt, sizeof(real)*bCANALS); break;
      case bINQ_GETPULSE_HOU: Common(mprePulseHou, sizeof(real)*bCANALS); break;
      case bINQ_GETPULSE_MNT: Common(mprePulseMnt, sizeof(real)*bCANALS); break;
      case bINQ_GETCOUNT: Common(mpreCount, sizeof(real)*bCANALS); break;
      case bINQ_GETLOSSE: Common(mpreLosse, sizeof(real)*bCANALS); break;
      case bINQ_GETLEVEL: Common(mpreLevelDiv, sizeof(real)*bCANALS); break;

      case bINQ_GETDIGITAL: OutGetDigital(); break;
      case bINQ_SETDIGITAL: OutSetDigital(); break;

      case bINQ_GETTARIFFSDAY: OutGetTariffsDay(); break;

      case bINQ_GETFLASHPAGE:
        OutFlashPage();
        break;

      case bINQ_SETDELAY:
        OutSetDelay();
        break;

      case bINQ_SETKEY:
        OutSetKey();
        break;

      case bINQ_GETDISPLAY:
        OutGetDisplay();
        break;

      case bINQ_RESPONSE_254:
      	Response254_CRC();
        break;

      case bINQ_RESPONSE_255:
      	Response255_CRC();
        break;

      default:
        ShowTestResponse(bSTA_BADCOMMAND);
        Result(bRES_BADCOMMAND);
        break;
  }
}
