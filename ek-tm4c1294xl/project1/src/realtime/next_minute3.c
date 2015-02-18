/*------------------------------------------------------------------------------
NEXT_MINUTE3.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../energy.h"
#include        "../impulses/impulses.h"



void    NextMinute3(void)
{
  cdwMinutes3++;

  memset(&mpwImpMntCan[(ibSoftMnt+1) % bMINUTES], 0, sizeof(uint)*bCANALS); // TODO Init/Reset mpwImpMntCan

  DisableImpulses();
  memcpy(&mpwImpCurrMntCan, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
  if (++ibSoftMnt >= bMINUTES) ibSoftMnt = 0;
  EnableImpulses();

  MakeImpulse();

}


void    NextMinute3Spec(void)
{
  cdwMinutes3++;

  memset(&mpwImpMntCan[(ibSoftMnt+1) % bMINUTES], 0, sizeof(uint)*bCANALS); // TODO Init/Reset mpwImpMntCan

  DisableImpulses();
  memcpy(&mpwImpCurrMntCan, &mpwImpMntCan[ibSoftMnt], sizeof(uint)*bCANALS);
  if (++ibSoftMnt >= bMINUTES) ibSoftMnt = 0;
  EnableImpulses();

  MakeImpulseSpec();
}
