/*------------------------------------------------------------------------------
AUTOMATIC_S.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_profile.h"
#include "../memory/mem_factors.h"
#include "../display/display.h"
#include "../keyboard/keyboard.h"
#include "../time/delay.h"
#include "../time/timedate.h"
#include "../hardware/watchdog.h"
#include "../kernel/crc-s.h"
#include "../serial/ports.h"
#include "../serial/ports2.h"
#include "../serial/ports_devices.h"
#include "../devices/devices.h"
#include "../devices/decompress_s.h"
#include "../digitals/digitals.h"
#include "../digitals/wait_answer.h"
#include "automatic1.h"
#include "device_s.h"
#include "automatic_s.h"
//#include        "xdata.h"
//#include        "crc-9.h"
//#include        "sensors.h"
//#include        "watchdog.h"
//#include        "timer0.h"
//#include        "display.h"
//#include        "engine.h"
//#include        "timedate.h"
//#include        "ports.h"
//#include        "ports2.h"
//#include        "delay.h"
//#include        "device_s.h"
//#include        "decompress_s.h"



#ifndef SKIP_S

void    QueryS_IO(uchar  cbIn, uchar  cbOut)
{
uchar	i,j;

  MakeCrcSOutBuff(1, cbOut-3);

  InitPush(0);
  PushChar(0xC0);
  for (i=0; i<cbOut-3; i++) SkipChar();
  PushChar(bCrcS);
  PushChar(0xC0);


  for (i=0; i<=cbOut-1; i++)
    mpbOutBuffSave[i] = GetOutBuff(i); 

  j = 0;
  SetOutBuff(j++, 0xC0);
  for (i=1; i<=cbOut-2; i++)
  {
    if (mpbOutBuffSave[i] == 0xC0) 
    {
      SetOutBuff(j++, 0xDB);
      SetOutBuff(j++, 0xDC);
    }
    else 
    if (mpbOutBuffSave[i] == 0xDB) 
    {
      SetOutBuff(j++, 0xDB);
      SetOutBuff(j++, 0xDD);
    }
    else 
      SetOutBuff(j++, mpbOutBuffSave[i]);
  }
  SetOutBuff(j++, 0xC0);


  Query(cbIn,j,1);
}


serial  InputS(void)
{
  InitWaitAnswer();

  while (1)
  {
    if (fKey == 1) { mpSerial[ibPort] = SER_BADLINK; break; }

    ResetWatchdog();
    ShowWaitAnswer(1);
    if (GetWaitAnswer()) { mpSerial[ibPort] = SER_BADLINK; break; }

    if (mpSerial[ibPort] == SER_INPUT_MASTER)
      DecompressS();

    if (mpSerial[ibPort] == SER_POSTINPUT_MASTER)
    {
      if (ChecksumS() == 0) 
        mpSerial[ibPort] = SER_GOODCHECK; 
      else
        mpSerial[ibPort] = SER_BADCHECK; 

      break;
    }
    else if ((mpSerial[ibPort] == SER_OVERFLOW) || 
             (mpSerial[ibPort] == SER_BADLINK)) break;
  }

  return( mpSerial[ibPort] );
}



bool    QueryConfigS_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryConfigS();

    if (InputS() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadConfigS();
  return(1);
}


time2   QueryTimeS_Full(uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeS();

    if (InputS() == SER_GOODCHECK) break;  
    if (fKey == 1) return GetTime2(tiZero, false);
  }

  if (i == bMINORREPEATS) return GetTime2(tiZero, false);
  ShowPercent(bPercent);

  return GetTime2(ReadTimeS(), true);
}


bool    QueryEngDayS_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngDayS(bTime);

    if (InputS() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyS();
  return(1);
}


bool    QueryEngMonS_Full(uchar  bTime, uchar  bPercent)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEngMonS(bTime);

    if (InputS() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent);

  ReadEnergyS();
  return(1);
}



time2   ReadTimeDateS(void)
{
  Clear();

  time2 ti2 = QueryTimeS_Full(50);
  if (ti2.fValid == false) return GetTime2(tiZero, false);

  tiChannelC = ti2.tiValue;
  mpboChannelsA[0] = true;     

  return GetTime2(ti2.tiValue, true);
}


double2 ReadSensorS(void)
{
  Clear();

  if (QueryConfigS_Full(50) == 0) return GetDouble2(0, false);

  if (QueryEngMonS_Full(0, 75) == 0) return GetDouble2(0, false);

  reBuffA = (float)mpdwChannelsA[0] / wDividerS;
  mpreChannelsB[0] = reBuffA;
  mpboChannelsA[0] = true;

  return(1);
}


double2 ReadCntMonCanS(uchar  ibMonth)
{ 
  Clear();

  if (QueryConfigS_Full(25) == 0) return GetDouble2(0, false);

  time2 ti2 = QueryTimeS_Full(50);
  if (ti2.fValid == false) return GetDouble2(0, false);
  time ti = ti2.tiValue;

  if (ti.bMonth != ibMonth+1)
  {
    if (QueryEngMonS_Full((bMONTHS+ti.bMonth-1-ibMonth) % bMONTHS, 75) == 0) return GetDouble2(0, false);
  }
  else 
  {
    if (QueryEngDayS_Full(1, 75) == 0) return GetDouble2(0, false);
  }

  reBuffA = (float)mpdwChannelsA[0] / wDividerS;
  mpreChannelsB[0] = reBuffA;
  mpboChannelsA[0] = true;

  return(1);
}

#endif
