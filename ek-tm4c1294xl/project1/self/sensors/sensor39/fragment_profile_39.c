/*------------------------------------------------------------------------------
fragment_profile_39*c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "../../serial/monitor_settings.h"
#include "device39.h"
#include "caller39.h"
#include "query_profile_39.h"
#include "query_next_block_39.h"
#include "io39.h"
#include "buffer_record_39.h"
#include "fragment_open_39.h"
#include "hdlc_address.h"
#include "fragment_profile_39.h"



record39 FragmentProfile39(caller39  *pc, time  ti1, time  ti2)
{
  InitBuffRecord39();


  (*pc).bNS++;
  (*pc).bInvokeId++;
  QueryProfile39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, ti1, ti2);
  if (Input39() != SER_GOODCHECK) return GetBuffRecordError(1);
  ValidateFrame((*pc).bNS, (*pc).bNR);

  bool fUseBlocks = UseBlocksDMLS();
  bool fLastBlock = LastBlockDMLS();

  AddBuffRecord39(fUseBlocks ? 20 + GetHdlcAddressesSize() : 13 + GetHdlcAddressesSize());

  while (!LastSegmentDMLS()) {
    (*pc).bNR++;
    Query39_RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return GetBuffRecordError(2);
    ValidateFrame((*pc).bNS, (*pc).bNR);

    AddBuffRecord39(6 + GetHdlcAddressesSize());
  }

  (*pc).bNR++;
  Query39_RR((*pc).bNR);
  if (Input39() != SER_GOODCHECK) return GetBuffRecordError(3);
  ValidateFrame((*pc).bNS, (*pc).bNR);


  uchar bBlockNumber = 0;

  while (fUseBlocks && (!fLastBlock)) {
    bBlockNumber++;

    (*pc).bNS++;
    QueryNextBlock39((*pc).bNS, (*pc).bNR, (*pc).bInvokeId, bBlockNumber);
    if (Input39() != SER_GOODCHECK) return GetBuffRecordError(4);
    ValidateFrame((*pc).bNS, (*pc).bNR);

    fUseBlocks = UseBlocksDMLS();
    fLastBlock = LastBlockDMLS();

    AddBuffRecord39(20 + GetHdlcAddressesSize());

    while (!LastSegmentDMLS()) {
      (*pc).bNR++;
      Query39_RR((*pc).bNR);
      if (Input39() != SER_GOODCHECK) return GetBuffRecordError(5);
      ValidateFrame((*pc).bNS, (*pc).bNR);

      AddBuffRecord39(6 + GetHdlcAddressesSize());
    }

    (*pc).bNR++;
    Query39_RR((*pc).bNR);
    if (Input39() != SER_GOODCHECK) return GetBuffRecordError(6);
    ValidateFrame((*pc).bNS, (*pc).bNR);
  }


  return FinishBuffRecord39();
}



#ifdef  MONITOR_39

double2 TestFragmentProfile39(void)
{
//  fMonitorLogBasic = false;
//  fMonitorLogHex = false;

  MonitorOpen(0);

  caller39 c = InitCaller39();

  if (FragmentOpen39(&c) != 0) return GetDouble2Error();

  time ti1;
  ti1.bYear = 20;
  ti1.bMonth = 6;
  ti1.bDay = 1;
  ti1.bHour = 0;
  ti1.bMinute = 0;
  ti1.bSecond = 0;

  time ti2;
  ti2.bYear = 20;
  ti2.bMonth = 6;
  ti2.bDay = 14;
  ti2.bHour = 0;
  ti2.bMinute = 0;
  ti2.bSecond = 0;

  InitBuffRecord39_All();

  uchar bError = FragmentProfile39(&c, ti1, ti2).bError;
  if (bError != 0)  {
    MonitorString("\n error "); MonitorCharDec(bError);
    return GetDouble2Error();
  }

  return GetDouble2(0, true);
}

#endif
