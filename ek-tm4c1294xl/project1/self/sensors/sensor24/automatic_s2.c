/*------------------------------------------------------------------------------
AUTOMATIC_S2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_factors.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../time/timedate.h"
#include "../../hardware/watchdog.h"
#include "../../kernel/crc_s.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../sensors/sensor24/unpack_s.h"
#include "../../digitals/digitals.h"
#include "../../digitals/wait_answer.h"
#include "../automatic1.h"
#include "device_s.h"
#include "automatic_s.h"
#include "automatic_s2.h"



#ifndef SKIP_S

// ReadTariffValue [0x0130]
// ������ �������� ������� �� ������.
// UINT8[1] � ����� ������ (0 � ����� �1, 1 � ����� �2, �, 7 � ����� �8);
// UINT8[2] � ������ ������� ������ (0 � ������� ��������, 1 � �������� �� ����� ���������� ������, 2 � �������� �� ����� ������� ������ �����, �, 13 � �������� �� ����� ������������ ������ �����)
// DATA4[1] - �������� �������.
void    QueryEngMonTariffS(uchar  ibMon, uchar  ibTrf)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushAddressS();

  PushChar(0xD2);
  PushChar(0x01);
  PushChar(0x30);
  PushChar(ibTrf);
  PushChar(ibMon);

  QueryS(100+15, 17);
}


bool    QueryEngMonTariffS_Full(uchar  ibMon, uchar  ibTrf, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngMonTariffS(ibMon, ibTrf);

    if (InputS() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergyS();
  return(1);
}


status  ReadCntMonCanTariffS(uchar  ibMonth, uchar  ibTrf) // �� ������ ������
{
  Clear();

  if (QueryConfigS_Full(25) == 0) return ST_BADDIGITAL;


  time2 ti2 = QueryTimeS_Full(50);
  if (ti2.fValid == false) return ST_BADDIGITAL;
  time ti = ti2.tiValue;


  uchar ibMon = ((12 + ti.bMonth - 1 - ibMonth) % 12) + 1;
  if (QueryEngMonTariffS_Full(ibMon, ibTrf, 75) == 0) return ST_BADDIGITAL;


  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / wDividerS;
  mpboChannelsA[0] = true;

  return ST_OK;
}

#endif
