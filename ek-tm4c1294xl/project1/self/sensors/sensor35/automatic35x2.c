/*------------------------------------------------------------------------------
AUTOMATIC35x2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/delay.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "device35.h"
#include "io35.h"
#include "automatic35.h"
#include "automatic35x2.h"



// ReadTariffValue [0x0130]
// ������ �������� ������� �� ������.
// UINT8[1] � ����� ������ (0 � ����� �1, 1 � ����� �2, �, 7 � ����� �8);
// UINT8[2] � ������ ������� ������ (0 � ������� ��������, 1 � �������� �� ����� ���������� ������, 2 � �������� �� ����� ������� ������ �����, �, 13 � �������� �� ����� ������������ ������ �����)
// DATA4[1] - �������� �������.
void    QueryEngMonTariff35(uchar  ibMon, uchar  ibTrf)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x48);

  PushSensorAddress35();

  PushChar(0xD2);
  PushChar(0x01);
  PushChar(0x30);
  PushChar(ibTrf);
  PushChar(ibMon);

  Query35(100+15, 17);
}


bool    QueryEngMonTariff35_Full(uchar  ibMon, uchar  ibTrf, uchar  bPercent)
{
  uchar i;
  for (i=0; i<MaxRepeats(); i++)
  {
    DelayOff();
    QueryEngMonTariff35(ibMon, ibTrf);

    if (Input35() == SER_GOODCHECK) break;
    if (fKey == true) return(0);
  }

  if (i == MaxRepeats()) return(0);
  ShowPercent(bPercent);

  ReadEnergy35();
  return(1);
}


status  ReadCntMonCanTariff35(uchar  ibMonth, uchar  ibTrf) // �� ������ ������
{
  Clear();

  if (QueryConfig35_Full(25) == 0) return ST_BADDIGITAL;


  time2 ti2 = QueryTime35_Full(50);
  if (ti2.fValid == false) return ST_BADDIGITAL;
  time ti = ti2.tiValue;


  uchar ibMon = ((12 + ti.bMonth - 1 - ibMonth) % 12) + 1;
  if (QueryEngMonTariff35_Full(ibMon, ibTrf, 75) == 0) return ST_BADDIGITAL;


  mpdbChannelsC[0] = (double)mpdwChannelsA[0] / GetDivider35();
  mpboChannelsA[0] = true;

  return ST_OK;
}
