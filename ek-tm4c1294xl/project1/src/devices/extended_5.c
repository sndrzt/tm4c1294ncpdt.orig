/*------------------------------------------------------------------------------
EXTENDED_5.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_realtime.h"
#include        "../memory/mem_profile.h"
#include        "../memory/mem_extended_5.h"
#include        "../digitals/digitals.h"
#include        "../digitals/digitals_display.h"
#include        "../devices/devices.h"
#include        "../serial/ports.h"
#include        "../time/rtc.h"
#include        "../console.h"
#include        "extended_5_b.h"
#include        "extended_5_c.h"
#include        "extended_5.h"



//                                         0123456789ABCDEF
static char const       szExtended5[]   = "����� ������: 5 ";



bool    ReadCntAbsTariff(uchar  ibCanal, uchar  bTariff)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return( ReadCntAbsTariffA(bTariff) );
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadCntAbsTariffB(bTariff) );
#endif

#ifndef SKIP_C
    case 3:  return( ReadCntAbsTariffC(bTariff) );
#endif

#ifndef SKIP_H
    case 10: return( ReadCntAbsTariffH(bTariff) );
#endif

    default: return 0;
  }
}


bool    CoreExtended5(void)
{
  memset(&mpvaValue50, 0, sizeof(mpvaValue50));  

  uchar t;
  for (t=0; t<bTARIFFS; t++)
  {
    if (fKey == 1) return (0);
    Clear();

    memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  
    if (ReadCntAbsTariff(ibDig,t+1) == 0) return (0);

    uchar i;
    for (i=0; i<4; i++)
    {
      mpvaValue50[i].mpreSelf[t] = mpreChannelsB[i];
    }
  }

  return (1);
}


void    MakeExtended5(void)
{ 
  if ((boExt5Flag == TRUE) && ((mpvaValue51[ibDig].boSelf == FALSE) || (boManualProfile == TRUE)))
  {
    ShowHi(szExtended5); Clear();
   
    if (CoreExtended5() == 1)
    {
      LoadCurrDigital(ibDig);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        LoadPrevDigital(c);
        if (CompareCurrPrevLines(ibDig, c) == 1)
        {
          mpvaValue51[c].cwOK++;
          mpvaValue51[c].tiSelf = *GetCurrTimeDate();
          mpvaValue51[c].vaValue50 = mpvaValue50[diPrev.ibLine];
          mpvaValue51[c].boSelf = TRUE;
        }
      }
    }
    else
    {
      LoadCurrDigital(ibDig);

      uchar c;
      for (c=0; c<bCANALS; c++)
      {
        LoadPrevDigital(c);
        if (CompareCurrPrevLines(ibDig, c) == 1)
        {
          mpvaValue51[c].cwError++;
        }
      }

      Error();
      DelayInf();
    }  

    ShowCanalNumber(ibDig);
    Clear();
  }
}


void    NextDayExtended5(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    mpvaValue51[c].boSelf = FALSE;
  }
}


#ifndef MODBUS

void    OutExtended50(void)
{
  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    uint wSize = 1;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        Push(&mpvaValue51[c], sizeof(value51));
        wSize += sizeof(value51);
      }
    }

    OutptrOutBuff(wSize);
  }
}


void    OutExtended51(void)
{

  if (enGlobal == GLB_PROGRAM)
    Result(bRES_NEEDWORK);
  else
  {
    InitPushPtr();            
    PushChar(boExt5Flag);
    uint wSize = 1;

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(6 + c/8) & (0x80 >> c%8)) != 0) 
      {
        Push(&mpvaValue51[c].vaValue50, sizeof(value50));
        wSize += sizeof(value50);
        Push(&mpvaValue51[c].tiSelf, sizeof(time));
        wSize += sizeof(time);
      }
    }

    OutptrOutBuff(wSize);
  }
}

#endif
