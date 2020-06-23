/*------------------------------------------------------------------------------
time39_test.c

------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "device39.h"
#include "time39.h"
#include "io39.h"
#include "fragment_open_time_39.h"
#include "time39.h"
#include "time39_test.h"



#ifdef  MONITOR_39

double2 TestTimeCorrect39(void)
{
//  fMonitorLogBasic = false;
//  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller();

  time2 tmA = FragmentOpenTime39(&c);
  if (!tmA.fValid) return GetDouble2Error1(1);


  time tmSensor1 = tmA.tiValue;
  time tmMaster1 = *GetCurrTimeDate();
  slong wDeltaSeconds1 = GetSecondIndex(tmMaster1) - GetSecondIndex(tmSensor1);
  MonitorString("\n before correction ");
  MonitorString("\n sensor: "); MonitorTime(tmSensor1);
  MonitorString("\n master: "); MonitorTime(tmMaster1);
  MonitorString("\n delta:  "); MonitorSignedLongDec(wDeltaSeconds1);


//  c.bNS++;
  c.bInvokeId++;
  QueryCorrectTime39(c.bNS, c.bNR, c.bInvokeId, wDeltaSeconds1);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(2);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return GetDouble2Error1(3);


  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c.bNS, c.bNR, c.bInvokeId);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(4);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return GetDouble2Error1(5);
  time tmSensor2 = ReadTime39();

  c.bNR++;
  Query39_RR(c.bNR);
  if (Input39() != SER_GOODCHECK) return GetDouble2Error1(6);
  if (ValidateFrame(c.bNS, c.bNR) != 0) return GetDouble2Error1(7);


  time tmMaster2 = *GetCurrTimeDate();
  slong wDeltaSeconds2 = GetSecondIndex(tmMaster2) - GetSecondIndex(tmSensor2);
  MonitorString("\n after correction ");
  MonitorString("\n sensor: "); MonitorTime(tmSensor2);
  MonitorString("\n master: "); MonitorTime(tmMaster2);
  MonitorString("\n delta:  "); MonitorSignedLongDec(wDeltaSeconds2);


  return GetDouble2(0, true);
}

#endif

