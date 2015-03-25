/*------------------------------------------------------------------------------
RECALC_DEF.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_energy.h"
#include        "../memory/mem_energy_spec.h"
#include        "../realtime/realtime.h"
#include        "../flash/files.h"
#include        "recalc_def.h"



bool    SaveDefDay(uchar  ibDayTo)
{
  OpenOut(FLS_DEFDAYCAN + ibDayTo*bIMPULSE_CAN);

  if (Save(mpdeDayCan, sizeof(impulse)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


bool    LoadDefDay(uchar  ibDayFrom)
{
  OpenIn(FLS_DEFDAYCAN + ibDayFrom*bIMPULSE_CAN);
  return( Load(mpdeDayCan, sizeof(impulse)*bCANALS) );
}



bool    SaveDefMon(uchar  ibMonTo)
{
  OpenOut(FLS_DEFMONCAN + ibMonTo*bIMPULSE_CAN);

  if (Save(mpdeMonCan, sizeof(impulse)*bCANALS) == 0)
    return(0);

  return( CloseOut() );
}


bool    LoadDefMon(uchar  ibMonFrom)
{
  OpenIn(FLS_DEFMONCAN + ibMonFrom*bIMPULSE_CAN);
  return( Load(mpdeMonCan, sizeof(impulse)*bCANALS) );
}


/*
void    ResetFlashDef(void)
{
uchar   i;

  memset(&mpdeDayCan, 0, sizeof(mpdeDayCan));
  for (i=0; i<bDAYS; i++)
    SaveDefDay(i);

  memset(&mpdeMonCan, 0, sizeof(mpdeMonCan));
  for (i=0; i<bMONTHS; i++)
    SaveDefMon(i);
}
*/

void    NextDayDef(void) 
{
  memset(&mpdeDayCan, 0, sizeof(mpdeDayCan));
  SaveDefDay(ibHardDay);
}


void    NextMonDef(void) 
{
  memset(&mpdeMonCan, 0, sizeof(mpdeMonCan));
  SaveDefMon(ibHardMon);
}



void    MakeDefSpec(impulse  *mpimT, uchar  ibCan, time  *pti)
{
  uchar i = pti->bHour*2 + pti->bMinute/30;
  uchar t = mpibEngPrevTariff[i];
  ulong dw = mpimT[ibCan].mpdwImp[t];

  if (mpwImpHouCanDef[ibCan] != 0xFFFF)
    dw++;

  mpimT[ibCan].mpdwImp[t] = dw;
}

