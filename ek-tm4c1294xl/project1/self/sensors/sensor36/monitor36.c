/*------------------------------------------------------------------------------
monitor36.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "../../serial/monitor.h"
#include "monitor36.h"



static void MonitorControl(uchar  bControl) {
  MonitorString(" Control="); MonitorCharHex(bControl);

  if ((bControl & 0x01) == 0x00) {
    MonitorString("I-frame");
    MonitorString(" N(R)=");  MonitorCharDec((bControl & 0xE0) >> 5);
    MonitorString(" N(S)=");  MonitorCharDec((bControl & 0x0E) >> 1);
  } else if ((bControl & 0x03) == 0x01) {
    MonitorString("S-frame");
    MonitorString(" N(R)=");  MonitorCharDec((bControl & 0xE0) >> 5);
  } else if ((bControl & 0x03) == 0x03) {
    MonitorString("U-frame");
  }

  if ((bControl & 0x10) == 0x00) {
    MonitorString(" F=0");
  } else {
    MonitorString(" F=1");
  }
}



void    MonitorOutput36(void)
{
  MonitorString("\n Output:");

  MonitorString(" Format="); MonitorCharHex(OutBuff(1)); MonitorCharHex(OutBuff(2));
  MonitorControl(OutBuff(5));
}



void    MonitorInput36(void)
{
  MonitorString("\n Input:");
  InitPop(1);

  uint wFormat = PopIntLtl();
  MonitorString(" Format="); MonitorIntHex(wFormat);

  PopChar();
  PopChar();

  MonitorControl(PopChar());
}
