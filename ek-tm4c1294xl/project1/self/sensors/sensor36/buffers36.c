/*------------------------------------------------------------------------------
buffers36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/monitor.h"
#include "buffer_x.h"
#include "buffers36.h"



void    StartBuffer1(void) {
  InitPushX();
}


void    AddBuffer1(uint  iwStart, uint  cwSize) {
  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    PushCharX(PopChar());
  }
}


uint    FinishBuffer1(void) {
  if (GetPopCapacity() < 2)
    return 1;

  if (PopCharX() != 1) // array
    return 2;

  uchar bCount = PopCharX();

  uchar i;
  for (i=0; i<bCount; i++)
  {
    if (GetPopCapacity() < 2 + 2+12 + 1+8)
      return 3;

    if (PopCharX() != 0x02) // structure
      return 4;

    if (PopCharX() != 2) // structure size
      return 5;

    if (PopCharX() != 0x09) // string
      return 6;

    if (PopCharX() != 12) // string size
      return 7;

    time ti = PopTimeDateX();

    if (PopCharX() != 0x15) // unsigned long 64
      return 8;

    uint64_t ddw = PopLong64X();

    MonitorString("\n");
    MonitorTime(ti);
    MonitorLongDec(ddw / 1000000);
    MonitorLongDec(ddw % 1000000);
  }

  return 0;
}



/*
void    PrintInBuff(uint  iwStart, uint  cwSize) {
  MonitorString("\n buffer size "); MonitorIntDec(cwSize);
  MonitorString("\n ");

  if (cwSize > 5000) return;

  InitPop(iwStart);

  uint i;
  for (i=0; i<cwSize; i++) {
    MonitorCharHex(PopChar());
  }
}
*/
