/*------------------------------------------------------------------------------
RESPONSE252_CRC,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../memory/mem_energy_spec.h"
#include "../include/states.h"
#include "../hardware/beep.h"
#include "../serial/ports.h"
#include "../output/response_crc.h"
#include "../output/out_delay.h"
#include "../output/out_realtime.h"
#include "../output/out_flash_stack.h"
#include "../output/out_nvram_stack.h"
#include "../output/out_health.h"
#include "../output/out_tariffs.h"
#include "../output/out_defects1.h"
#include "../output/out_nvram.h"
#include "../output/out_flash.h"
#include "../kernel/asserts.h"
#include "../output/profile/out_profile_link.h"
#include "../serial/slave_modem.h"
#include "../realtime/throughput.h"



void    Response252_CRC(void)
{
  switch (bInBuff5)
  {
    case 0: Beep(); break;

    case 1: OutDelay(); break;

    case 2: OutRealtime(); break;

    case 3: OutFlashStack(); break;
    case 7: OutNvramStack(); break;

    case 4: OutHealth(); break;

    case 5: OutGetAllPowTariffs(); break;
    case 6: OutGetAllEngTariffs(); break;

    case 8: OutDefectsDay(); break;
    case 9: OutDefectsMon(); break;

    case 10: OutNvram(); break;
//    case 11: OutFlash(); break;

    case 12: OutNvramCounters(); break;
    case 13: ResetNvramCounters(); break;

    case 14: OutFlashCounters(); break;
    case 15: ResetFlashCounters(); break;

    case 16: OutAsserts(); break;

    case 17: OutGetProfileLinkWrn(); break;
    case 18: OutGetProfileLinkErr(); break;
    case 19: OutResetProfileLinkWrn(); break;
    case 20: OutResetProfileLinkErr(); break;

    case 21: OutSlaveModem(); break;

    case 22: OutThroughput(); break;

    default:
      ShowResponseCRC(bSTA_BADCOMMAND);
      Result(bRES_BADCOMMAND);
      break;
  }
}
