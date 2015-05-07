/*------------------------------------------------------------------------------
OUT_NAMES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_uni.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../flash/files.h"
#include "unified/uni.h"
#include "out_names.h"



static void OutputName(void  *pbData, uint  wSize)
{
  if (5+wSize < wOUTBUFF_SIZE-bMARGIN)
  {
    InitPushCRC();
    Push(pbData, wSize);
    Output(wSize);
  }
  else Result(bRES_OUTOVERFLOW);
}



void    GetObjectNameExt(void)
{
  OutputName(&szObjectName, bNAME);
}


void    SetObjectNameExt(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    uchar i;
    for (i=0; i<bNAME; i++)
      szObjectName[i] = InBuff(6+i);

    szObjectName[bNAME-1] = 0;

    SaveFile(&flObjectName);

    LongResult(bRES_OK);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    GetCanalsNameExt(void)
{
  if (bInBuff6 < bCANALS)
    OutputName(&mpszCanalsName[ bInBuff6 ], bNAME);
  else
    Result(bRES_BADADDRESS);
}


void    SetCanalsNameExt(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff6 < bCANALS)
    {
      uchar i;
      for (i=0; i<bNAME; i++)
        mpszCanalsName[bInBuff6][i] = InBuff(7+i);

      mpszCanalsName[bInBuff6][bNAME-1] = 0;

      if (bInBuff6 == bCANALS - 1)
        SaveFile(&flCanalsName);

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}



void    GetGroupsNameExt(void)
{
  if (bInBuff6 < bGROUPS)
    OutputName(&mpszGroupsName[ bInBuff6 ], bNAME);
  else
    Result(bRES_BADADDRESS);
}


void    SetGroupsNameExt(void)
{
  if ((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_REPROGRAM))
  {
    if (bInBuff6 < bGROUPS)
    {
      uchar i;
      for (i=0; i<bNAME; i++)
        mpszGroupsName[bInBuff6][i] = InBuff(7+i);

      mpszGroupsName[bInBuff6][bNAME-1] = 0;

      if (bInBuff6 == bGROUPS - 1)
        SaveFile(&flGroupsName);

      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDPROGRAM);
}
