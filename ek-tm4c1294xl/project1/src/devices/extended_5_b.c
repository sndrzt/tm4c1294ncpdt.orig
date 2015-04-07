/*------------------------------------------------------------------------------
EXTENDED_5_B.C


------------------------------------------------------------------------------*/
/*
#include        "main.h"
#include        "xdata.h"
#include        "display.h"
#include        "delay.h"
#include        "ports.h"
#include        "engine.h"
#include        "energy.h"
#include        "keyboard.h"
#include        "device_b.h"
#include        "_automatic1.h"



void    QueryEnergyTariffB(uchar  bTime, uchar  bTariff)
{
  InitPush();

  PushChar(diCurr.bAddress);
  PushChar(5);

  PushChar(bTime);
  PushChar(bTariff);

  QueryIO(1+16+2, 2+2+2);
}


bit     QueryEnergyTariffB_Full(uchar  bTime, uchar  bTariff)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyTariffB(bTime,bTariff);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  ReadEnergyB();
  return(1);
}


bit     ReadCntAbsTariffB(uchar  bTariff)                 
{ 
uchar   i;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return(0);


  if (QueryEnergyTariffB_Full(0x40,bTariff) == 0) return(0);  
  ShowPercent(60+bTariff);
  for (i=0; i<4; i++)
  {
    dwBuffC = *PGetCanLong(mpdwChannelsA, i);
    SetCanLong(mpdwChannelsB, i);
  }

  if (QueryEnergyTariffB_Full(0,bTariff) == 0) return(0);             
  ShowPercent(80+bTariff);
  for (i=0; i<4; i++)
  {
    dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
    dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

    SetCanLong(mpdwChannelsB, i);
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000)
      reBuffA = 0;
    else
      reBuffA = *PGetCanLong(mpdwChannelsB, i) * reBuffB * 2;

    SetCanReal(mpreChannelsB, i);
    mpboChannelsA[i] = boTrue;     
  }

  return(1);
}
*/
