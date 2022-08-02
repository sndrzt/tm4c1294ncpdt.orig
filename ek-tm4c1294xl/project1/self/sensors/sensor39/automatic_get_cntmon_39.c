/*------------------------------------------------------------------------------
automatic_get_cntmon_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "dlms.h"
#include "error39.h"
#include "time39.h"
#include "io39.h"
#include "hdlc_address.h"
#include "query_billing_period_39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "read_engmon_39.h"
#include "dlms_read_register.h"
#include "buffer_record_39.h"
#include "fragment_open_time_39.h"
#include "fragment_cntmon_39.h"
#include "fragment_profile_39.h"
#include "automatic_get_cntmon_39.h"



static double2 Fault(uchar  bError)
{
  return GetDouble2Error1(Error39(bError));
}



double2 ReadCntMonCan38_Internal(uchar  ibMon)
{
  caller39 c = InitCaller39();

  time2 tm2 = FragmentOpenTime39(&c);
  if (!tm2.fValid) return Fault(70+0);
  time tm = tm2.tiValue;


  if (tm.bMonth != ibMon+1)
  {
    uchar bMonth = (ibMon+1) % 12 + 1;
    uchar bYear = (bMonth > tm.bMonth) ? tm.bYear-1 : tm.bYear;

    double2 db2 = FragmentCntMonCan(obisEngAbs[0], &c, bMonth, bYear); // TODO

    if (db2.bError == ERROR_NOT_PRESENTED) {
      Clear();
      sprintf(szLo+1, "����� %02u.%02u ?", bMonth, bYear);
      Delay(1000);
      return Fault(70+1);
    }

    DISC();
    if (Input39() != SER_GOODCHECK) return Fault(70+2);

    return db2;
  }
  else
  {
    time tm1;
    tm1.bYear = tm.bYear;
    tm1.bMonth = tm.bMonth;
    tm1.bDay = tm.bDay;
    tm1.bHour = 0;
    tm1.bMinute = 0;
    tm1.bSecond = 0;

    time tm2;
    tm2.bYear = tm.bYear;
    tm2.bMonth = tm.bMonth;
    tm2.bDay = tm.bDay;
    tm2.bHour = 23;
    tm2.bMinute = 59;
    tm2.bSecond = 59;

    InitRecord39_FragmentProfile39();

    record39 r = FragmentProfile39(&c, tm1, tm2, false);

    if (r.bError != 0)
    {
      return Fault(70+3);
    }
    if (r.fFirst == false)
    {
      Clear();
      sprintf(szLo+0, "����� %02u.%02u.%02u ?", tm.bDay, tm.bMonth, tm.bYear);
      Delay(1000);
      return Fault(70+4);
    }

    double2 scaler = ReadRegisterScaler39(obisEngAbs[0], &c);  // TODO
    if (!scaler.fValid) return Fault(70+5);

    DISC();
    if (Input39() != SER_GOODCHECK) return Fault(70+6);

    //return GetDouble0((double)r.ddwValue * scaler.dbValue);
    return GetDouble0(-1); // TODO
  }
}



double2 ReadCntMonCan39(uchar  ibMon)
{
  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    double2 db2 = ReadCntMonCan38_Internal(ibMon);
    if (fKey == true) break;
    if (db2.fValid)
    {
      mpdbChannelsC[0] = db2.dbValue / 1000;
      mpboChannelsA[0] = true;

      return GetDouble0(mpdbChannelsC[0]);
    }
  }

  DISC();
  if (Input39() != SER_GOODCHECK) return Fault(70+7);

  return Fault(70+8);
}
