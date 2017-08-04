/*------------------------------------------------------------------------------
MONITOR.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/uartstdio.h"
#include "../time/rtc.h"
#include "ports_common.h"
#include "monitor_settings.h"
#include "monitor.h"



void    MonitorString(const char  *psz)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz);
  }
}


void    MonitorChar(const char  *psz, uchar  b)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz, b);
  }
}


void    MonitorCharChar(uchar  b)
{
  MonitorChar("%c", (b < ' ' ? '_' : b));
}


void    MonitorCharDec(uchar  b)
{
  MonitorChar("%u", b);
}


void    MonitorCharDec3(uchar  b)
{
  MonitorChar("%3u ", b);
}


void    MonitorCharHex(uchar  b)
{
  MonitorChar("%02X ", b);
}


void    MonitorInt(const char  *psz, uint  w)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz, w);
  }
}


void    MonitorIntDec(uint  w)
{
  MonitorInt("%u", w);
}


void    MonitorIntDec5(uint  w)
{
  MonitorInt("%5u ", w);
}


void    MonitorIntHex(uint  w)
{
  MonitorInt("%04X", w);
}


void    MonitorLong(const char  *psz, ulong  dw)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf(psz, dw);
  }
}


void    MonitorLongDec(ulong  dw)
{
  MonitorLong("%u", dw);
}


void    MonitorTime(time  ti)
{
  if (UseMonitor())
  {
    MonitorRepeat();
    UARTprintf("%02u:%02u:%02u %02u.%02u.%02u ",
               ti.bHour,
               ti.bMinute,
               ti.bSecond,
               ti.bDay,
               ti.bMonth,
               ti.bYear);
  }
}



static void MonitorOutHex(uint  cwOut)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwOut; i++)
  {
    MonitorCharHex(OutBuff(i));
  }
}


static void MonitorOutChar7(uint  cwOut)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwOut; i++)
  {
    MonitorCharChar(OutBuff(i) & 0x7F);
  }
}


static void MonitorOutChar8(uint  cwOut)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwOut; i++)
  {
    MonitorCharChar(OutBuff(i));
  }
}


void    MonitorOut(uint  cwIn, uint  cwOut)
{
  if (UseMonitor())
  {
    if (fMonitorLogBasic)
    {
      MonitorString("\n\n Output: out="); MonitorIntDec(cwOut);
      MonitorString(" in="); MonitorIntDec(cwIn);
      MonitorString(" "); MonitorTime(*GetCurrTimeDate());
    }

    if (fMonitorLogHex) MonitorOutHex(cwOut);
    if (fMonitorLogChar7) MonitorOutChar7(cwOut);
    if (fMonitorLogChar8) MonitorOutChar8(cwOut);
  }
}



static void MonitorInHex(uint  cwIn)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwIn; i++)
  {
    MonitorCharHex(InBuff(i));
  }
}


static void MonitorInChar7(uint  cwIn)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwIn; i++)
  {
    MonitorCharChar(InBuff(i) & 0x7F);
  }
}


static void MonitorInChar8(uint  cwIn)
{
  MonitorString("\n ");

  uint i;
  for (i=0; i<cwIn; i++)
  {
    MonitorCharChar(InBuff(i));
  }
}


void    MonitorIn(void)
{
  if (UseMonitor())
  {
    if (fMonitorLogBasic)
    {
      MonitorString("\n Input: in="); MonitorIntDec(IndexInBuff());
      MonitorString(" "); MonitorTime(*GetCurrTimeDate());
    }

    if (fMonitorLogHex) MonitorInHex(IndexInBuff());
    if (fMonitorLogChar7) MonitorInChar7(IndexInBuff());
    if (fMonitorLogChar8) MonitorInChar8(IndexInBuff());
  }
}
