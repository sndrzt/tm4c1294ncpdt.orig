/*------------------------------------------------------------------------------
automatic_get_cntcur_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "automatic_get_cntcur_38.h"



//#include "../../memory/mem_serial3.h"
#include "../../serial/monitor.h"
#include "../../time/calendar.h"
#include "dff.h"
#include "profile38.h"
uint64_t DffDecodePositive_(uchar  *pb);
void    MonitorOpen(uchar  ibPrt);



double2 ReadCntCurr38(void)
{
    ulong out;
    int64_t ddw;
    uchar n;

    ddw = 1;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n 1 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -1;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n -1 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 127;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n 127 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -127;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n -127 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 128;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n 128 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -128;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n -128 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);


    ddw = -1;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -10;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -100;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -1000;
    memset(&out, 0, sizeof(out));
    n = EncodeInt(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);



    ddw = 1;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n 1 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -1;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n -1 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = 127;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n 127 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -127;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n -127 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);


    ddw = 128;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n 128 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -128;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n -128 "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -100;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);

    ddw = -1000;
    memset(&out, 0, sizeof(out));
    n = DffEncode(ddw, (uint8_t *)&out);
    MonitorString("\n "); MonitorCharDec(n); MonitorString(" "); MonitorLongHex(out);


  if (1+1 == 2) return GetDouble2(0, true);

  Clear();

  uchar r;
  for (r=0; r<MaxRepeats(); r++)
  {
    QueryEngAbs38();

    if (Input38() == SER_GOODCHECK) break;
    if (fKey == true) return GetDouble2Error();
  }

  if (r == MaxRepeats()) return GetDouble2Error();

  uchar ibIn = 10;

  uchar i;
  for (i=0; i<4; i++)
  {
    ibIn++;

    uint64_t ddw = 0;
    uchar delta = pucDecodeBitArr((uchar *) &ddw, InBuffPtr(ibIn));
    if (delta == 0xFF) return GetDouble2Error();
    ibIn += delta;

    mpdwChannelsA[i] = ddw % 0x100000000;
    mpdbChannelsC[i] = (double)mpdwChannelsA[i] / 10000;
  }


  for (i=0; i<4; i++)
  {
    mpdbChannelsC[i] *= mpdbTransCnt[ibDig];
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}
