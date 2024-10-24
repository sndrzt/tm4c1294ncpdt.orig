/*------------------------------------------------------------------------------
EXTENDED_6_OUT,C

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_energy.h"
#include "../../digitals/digitals.h"
#include "../../realtime/realtime.h"
#include "../../serial/ports.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../energy2.h"
#include "extended_6.h"
#include "extended_6_out.h"



uchar   PushData6(value6  vl, bool  fDouble)
{
  uchar bSize = 0;

  bSize += PushChar(vl.bStatus);
  bSize += PushFloatOrDouble(vl.dbValue, fDouble);
  bSize += PushTime(vl.tiUpdate);

  return bSize;
}



void    OutExtended6(bool  fDouble)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else if (InBuff(6) >= bMONTHS)
    Result(bRES_BADADDRESS);
  else
  {
    LoadCntMon(InBuff(6));
    LoadCntMonCan6(InBuff(6));

    InitPushPtr();
    uint wSize = 0;

    wSize += PushIntBig(cwDayCan6);
    wSize += PushIntBig(cwMonCan6);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        if (GetDigitalDevice(c) == 0)
        {
          value6 vl;
          vl.bStatus = ST_OK;
          vl.dbValue = mpdbCntMonCan[ PrevSoftMon() ][c];
          vl.tiUpdate = tiZero;

          wSize += PushData6(vl, fDouble);
        }
        else
        {
          if (InBuff(6) == (*GetCurrTimeDate()).bMonth - 1)
            wSize += PushData6(mpCntBoxCan6[c], fDouble);
          else 
            wSize += PushData6(mpCntMonCan6[c], fDouble);
        }
      }
    }

    OutptrOutBuff(wSize);
  }
}
