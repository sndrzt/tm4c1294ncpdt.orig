/*------------------------------------------------------------------------------
current39.c


------------------------------------------------------------------------------*/

#include <math.h>
#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "../../digitals/current/current_run.h"
#include "io39.h"
#include "dlms.h"
#include "caller39.h"
#include "dlms_obis.h"
#include "dlms_read_data.h"
#include "dlms_read_register.h"
#include "query_register_39.h"
#include "current39_wrapper.h"



static uchar            bLine39;



static caller39         c;

static ulong64_         counter[4];
static double2          scaler;



void    ClearLine39(void)
{
  bLine39 = 0;
}


uchar   IncLine39(void)
{
  return ++bLine39;
}


uchar   GetLine39(void)
{
  return bLine39;
}



void    DISC_Current39(void)
{
  c = InitCaller39();
  DISC();
}


void    SNRM_Current39(void)
{
  SNRM();
}


void    AARQ_Current39(void)
{
  AARQ(c.bNS, c.bNR);
}


void    RR_Current39(void)
{
  c.bNR++;
  RR(c.bNR);
}



bool    ValidateFrame_Current39(void)
{
  return ValidateFrame(c.bNS, c.bNR) == 0;
};



void    QueryValue_Current39(void)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryValue_Current39 ");  MonitorCharDec(ibLine39);
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterValueDLMS(obisEngAbs[ibLine39], c);
}


bool    ReadValue_Current39(void)
{
  counter[ibLine39] = ReadUnsignedValueDLSM();
  return counter[ibLine39].fValid;
}



void    QueryScaler_Current39(void)
{
#ifdef MONITOR_39_NAMES
  MonitorString("\n\n QueryScaler_Current39 ");
#endif

  c.bNS++;
  c.bInvokeId++;
  QueryGetRegisterScalerDLMS(obisEngAbs[0], c);
}


bool    ReadScaler_Current39(void)
{
  scaler = ReadRegisterScalerDLMS();
  return scaler.fValid;
}



void    ReadCurrent39(void)
{
  double dbScaler = scaler.dbValue;

  uchar i;
  for (i=0; i<4; i++)
  {
    uint64_t ddwCounter = counter[i].ddwValue;
    mpdwBaseDig[i] = ((double)ddwCounter * dbScaler / 1000) * mpdbPulseMnt[ibDig];
  }

  MakeCurrent();
}
