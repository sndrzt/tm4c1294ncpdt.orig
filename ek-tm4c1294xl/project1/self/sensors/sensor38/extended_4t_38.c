/*------------------------------------------------------------------------------
extended_4t_38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals.h"
#include "device38.h"
#include "io38.h"
#include "dff.h"
#include "automatic_get_time_38.h"
#include "extended_4t_38.h"



void    QueryEngAbsTariff38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A); // GET_DATA_SINGLE_EX
  PushChar(0x00);

  PushChar(0x01); // A+
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x02); // A-
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x03); // R+
  PushChar(0x02);
  PushChar(0x00);

  PushChar(0x04); // R-
  PushChar(0x02);
  PushChar(0x00);

  Query38(250, 25);
}


status   ReadEngMonTariff38_Full(time  ti, uchar  ibTariff)
{
  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    if (SkipLine(ibDig, i) == true) { mpdbChannelsC[i] = 0; continue; }

    uchar r;
    for (r=0; r<MaxRepeats(); r++)
    {
      QueryEngMon38(i,ti);

      if ((Input38() == SER_GOODCHECK) && (!NoData38())) break;
      if (NoData38()) return ST_NOTPRESENTED;
      if (fKey == true) return ST_BADDIGITAL;
    }

    if (r == MaxRepeats()) return ST_BADDIGITAL;
    ShowPercent(70+i);

    ReadEngTariff38(i,ibTariff);
  }

  return ST_OK;
}



status  ReadCntMonCanTariff38(uchar  ibMonth, uchar  ibTariff, uchar  bMaxLines) // �� ������ ������
{
  time2 ti2 = ReadTimeCan38();
  if (ti2.fValid == 0) return ST_BADDIGITAL;

  time ti = ti2.tiValue;
  if (ibMonth == 0)
  {
    ti.bMonth = 12;
    ti.bYear--;
  }
  else
  {
    if (ibMonth+1 > ti.bMonth) ti.bYear--;
    ti.bMonth = ibMonth;
  }

  status st = ReadEngMonTariff38_Full(ti,ibTariff,bMaxLines);

  if (st == ST_NOTPRESENTED)
  {
    Clear();
    sprintf(szLo+1, "����� %02u.%02u ?",ti.bMonth,ti.bYear);
    Delay(1000);
    return(ST_NOTPRESENTED);
  }

  if (st != ST_OK) return st;


  QueryClose38();


  double dbTrans = mpdbTransCnt[ibDig];

  uchar i;
  for (i=0; i<bMaxLines; i++)
  {
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return ST_OK;
}

