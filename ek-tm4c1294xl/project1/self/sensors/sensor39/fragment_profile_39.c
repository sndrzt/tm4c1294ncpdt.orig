/*------------------------------------------------------------------------------
fragment_profile_39.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "dlms.h"
#include "error39.h"
#include "caller39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_open_39.h"
#include "hdlc_address.h"
#include "fragment_profile_39.h"



static bool Fault(uchar  bError)
{
  Error39(bError);
  return false;
}



bool    FragmentProfile39(caller39  *pc, time  tm1, time  tm2, bool  fProfile)
{
  InitRecord39(); // step 2


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, tm1, tm2); // step 4
  if (Input39() != SER_GOODCHECK) return Fault(130+0);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+1);

  bool fUseBlocks = UseBlocksDMLS(); // step 5
  bool fLastBlock = LastBlockDMLS();

  AddRecord39(fUseBlocks ? 19 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize()); // step 6

  while (!LastSegmentDMLS()) { // step 7
    (*pc).bNR++;
    RR((*pc).bNR); // step 8
    if (Input39() != SER_GOODCHECK) return Fault(130+2);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+3);

    AddRecord39(6 + GetHdlcAddressesSize()); // step 9
  }

  (*pc).bNR++;
  RR((*pc).bNR); // step 10
  if (Input39() != SER_GOODCHECK) return Fault(130+4);
  if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+5);


  uchar bBlockNumber = 0; // step 11

  while (fUseBlocks && (!fLastBlock)) { // step 12
    bBlockNumber++; // step 13

    (*pc).bNS++;
    QueryNextBlock39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bBlockNumber); // step 14
    if (Input39() != SER_GOODCHECK) return Fault(130+6);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+7);

    fUseBlocks = UseBlocksDMLS(); // step 15
    fLastBlock = LastBlockDMLS();

    AddRecord39(19 + GetHdlcAddressesSize());  // step 16

    while (!LastSegmentDMLS()) { // step 17
      (*pc).bNR++;
      RR((*pc).bNR);
      if (Input39() != SER_GOODCHECK) return Fault(130+8);
      if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+9);

      AddRecord39(6 + GetHdlcAddressesSize());
    }

    (*pc).bNR++;
    RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return Fault(130+10);
    if (ValidateFrame((*pc).bNS, (*pc).bNR) != 0) return Fault(130+11);
  }


  if (fProfile)
    return FinishRecordProfile39();
  else
    return FinishRecord39();
}



#ifdef  MONITOR_39

double2 TestFragmentProfile39(void)
{
  fMonitorLogBasic = false;
  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller39();

  if (FragmentOpen39(&c) != 0) return GetDouble2Error();

  time tm1;
  tm1.bYear = 22;
  tm1.bMonth = 7;
  tm1.bDay = 25;
  tm1.bHour = 0;
  tm1.bMinute = 0;
  tm1.bSecond = 0;

  time tm2;
  tm2.bYear = 22;
  tm2.bMonth = 7;
  tm2.bDay = 26;
  tm2.bHour = 0;
  tm2.bMinute = 0;
  tm2.bSecond = 0;

  bool success = FragmentProfile39(&c, tm1, tm2, false);
  if (!success)  {
    return GetDouble2Error();
  } else {
    return GetDouble0(0);
  }
}

#endif
