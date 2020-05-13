/*------------------------------------------------------------------------------
read_profile_36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../devices/devices.h"
//#include "../../sensors/automatic1.h"
#include "../../serial/monitor.h" //
#include "../../digitals/digitals.h"
#include "device36.h"
#include "device36_2.h"
#include "io36.h"
#include "monitor36.h"
#include "buffers36.h"
#include "read_profile_36.h"




schar   y(void)
{
  StartBuffer1();

  Query36_DISC();
  if (Input36() != SER_GOODCHECK) return -15;//GetDouble2Error();
  DelayOff();

  Query36_SNRM();
  if (Input36() != SER_GOODCHECK) return -16;//GetDouble2Error();
  DelayOff();

  uchar bNS = 0;
  uchar bNR = 0;
  uchar bInvokeId = 0;

  Query36_Open2(bNS, bNR);
  if (Input36() != SER_GOODCHECK) return -17;//GetDouble2Error();
//  if (!ValidateIframe(bNS, bNR)) return GetDouble2Error();
  DelayOff();

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -18;//GetDouble2Error();
//  if (!ValidateSframe(bNR)) return GetDouble2Error();
  DelayOff();



  bNS++;
  bInvokeId++;
  QueryEngCurrDay36(bNS, bNR, bInvokeId);
  if (Input36() != SER_GOODCHECK) return -19;
  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  while (!LastSegmentDMLS()) {
    bNR++;
    Query36_RR(bNR);
    if (Input36() != SER_GOODCHECK) return -20;
    AddBuffer1(8, IndexInBuff()-8-3);
    DelayOff();
  }

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -21;
  DelayOff();



  bNS++;
  uchar bBlockNumber = 1;
  QueryNextBlock36(bNS, bNR, bInvokeId, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return -22;
  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  while (!LastSegmentDMLS()) {
    bNR++;
    Query36_RR(bNR);
    if (Input36() != SER_GOODCHECK) return -23;
    AddBuffer1(8, IndexInBuff()-8-3);
    DelayOff();
  }

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -24;
  DelayOff();



  bNS++;
  bBlockNumber = 2;
  QueryNextBlock36(bNS, bNR, bInvokeId, bBlockNumber);
  if (Input36() != SER_GOODCHECK) return -25;
  AddBuffer1(22, IndexInBuff()-22-3);
  DelayOff();

  while (!LastSegmentDMLS()) {
    bNR++;
    Query36_RR(bNR);
    if (Input36() != SER_GOODCHECK) return -26;
    AddBuffer1(8, IndexInBuff()-8-3);
    DelayOff();
  }

  bNR++;
  Query36_RR(bNR);
  if (Input36() != SER_GOODCHECK) return -27;
  DelayOff();





  FinishBuffer1();
  return 0;
}


double2 ReadProfile36(void)
{
  return GetDouble2(y(), true);
}
