/*------------------------------------------------------------------------------
OUT_MINUTE3.C
                    

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_ports.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_energy.h"
#include        "../serial/ports.h"
#include        "../realtime/realtime.h"
#include        "../energy.h"
#include        "../energy2.h"



void    OutImpMntCanExt(void)
{
uchar   c, i;
uint    w;

  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    w = 0;

    for (i=0; i<bMINUTES; i++)
    {
    	if (LoadImpMnt((bMINUTES+ibHardMnt-i) % bMINUTES) == FALSE) { Result(bRES_BADFLASH); return; }

      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
        {
          PushInt(mpwImpMntCan1[ PrevSoftMnt() ][ c ]);
          w += sizeof(uint);
        }
      }
    }

    OutptrOutBuff(w);
  }
  else Result(bRES_NEEDWORK);
}


void    OutPowMntCanExt(void)
{
uchar   c, i;
uint    w;
real    re;

  if (enGlobal != GLB_PROGRAM)
  {
    InitPushPtr();
    w = 0;

    for (i=0; i<bMINUTES; i++)
    {
    	if (LoadImpMnt((bMINUTES+ibHardMnt-i) % bMINUTES) == FALSE) { Result(bRES_BADFLASH); return; }

      for (c=0; c<bCANALS; c++)
      {
        if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
        {
          re = GetCanMntInt2Real(mpwImpMntCan1[ PrevSoftMnt() ], c, 20);
          PushReal(re);

          w += sizeof(real);
        }
      }
    }

    OutptrOutBuff(w);
  }
  else Result(bRES_NEEDWORK);
}



void    OutImpCanMntExt(void)
{
  InitPushPtr();

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
  	if (LoadImpMnt((bMINUTES+ibHardMnt-1) % bMINUTES) == FALSE) { Result(bRES_BADFLASH); return; }

    Push( &mpwImpMntCan1[ PrevSoftMnt() ], sizeof(uint)*bCANALS );
    OutptrOutBuff(sizeof(uint)*bCANALS);
  }
}


void    OutPowCanMntExt(void)
{
uchar   c;
uint    w;
real    re;

  InitPushPtr();
  w = 0;

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
  	if (LoadImpMnt((bMINUTES+ibHardMnt-1) % bMINUTES) == FALSE) { Result(bRES_BADFLASH); return; }

    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0)
      {
        re = GetCanMntInt2Real(mpwImpMntCan1[ PrevSoftMnt() ], c, 20);
        PushReal(re);

        w += sizeof(real);
      }
    }

    OutptrOutBuff(w);
  }
}

