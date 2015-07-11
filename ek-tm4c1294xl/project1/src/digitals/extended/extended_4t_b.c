/*------------------------------------------------------------------------------
EXTENDED_4T_B,C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../console.h"
#include "../../serial/ports_stack.h"
#include "../../serial/ports_devices.h"
#include "../../sensors/device_b.h"

#include "../../sensors/automatic1.h"
#include "extended_4t_b.h"



static void QueryCntMonTariffB(uchar  ibMon, uchar  bTrf) // �� ������ ������
{
  InitPush(0);

  PushChar(diCurr.bAddress);
  PushChar(6);
  PushChar(2);

  uint w = 0x2BB + 0x55*ibMon + 0x11*bTrf;
  PushChar(w / 0x100);
  PushChar(w % 0x100);
  PushChar(16);

  QueryIO(1+16+2, 3+3+2);
}


static bool QueryCntMonTariffB_Full(uchar  ibMon, uchar  bTrf) // �� ������ ������
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryCntMonTariffB(ibMon, bTrf);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == true) return false;
  }

  if (i == bMINORREPEATS) return false;

  ReadEnergyB();
  return true;
}


status ReadCntMonCanTariffB(uchar  ibMon, uchar  ibTrf) // �� ������ ������
{ 
  Clear();
  if (ReadKoeffDeviceB() == 0) return ST4_BADDIGITAL;

  double dbK = dbKtrans/dbKpulse;


  if (QueryCntMonTariffB_Full(ibMon, ibTrf) == 0) return ST4_BADDIGITAL;

  ShowPercent(60+ibTrf);


  uchar i;
  for (i=0; i<4; i++) 
  {
    mpdbChannelsC[i] = mpdwChannelsA[i] * dbK;
    mpboChannelsA[i] = true;
  }

  return ST4_OK;
}
