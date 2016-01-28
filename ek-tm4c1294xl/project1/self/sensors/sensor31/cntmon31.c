/*------------------------------------------------------------------------------
CNTMON31.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../serial/monitor.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/digitals_messages.h"
#include "automatic31.h"
#include "device31.h"
#include "cntmon31.h"



#ifndef SKIP_N31

// ������� �� �������
static double           mpdbChannelsMon[6];

// ������� �����
static double           mpdbChannelsAbs[6];

// ������ �������
static uchar            mpbChannelsMon[13];

// �������
static double           mpdbEng30[30];



static void QueryData4(uchar  ibTrf) // ������� �� �������/���������� ����� � �������/���������� �����
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x04); // "����������� ������� (�� �������)"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query31(3+4+8*24+2+1, 3+3+1);
}


static void QueryData5(uchar  ibTrf) // ������� �����
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(0x05); // "����������� ������� ����� (�� �������)"
  PushCharCod(0x00);
  PushCharCod(ibTrf);

  Query31(3+4+8*6+2+1, 3+3+1);
}


static void QueryData26(uchar  ibMon, uchar  ibTrf) // ������� �� �������
{
  InitPushCod();

  PushChar(0x7E);
  PushChar(0x03);
  PushChar(0x06);

  PushCharCod(26); // "���� �������"

  uint w = ibMon * 72 + ibTrf;
  PushCharCod(w / 0x100);
  PushCharCod(w % 0x100);

  Query31(3+102+1, 3+3+1);
}



static bool ValidPackTime(void)
{
  time ti = ReadPackTime31();

  if ((ti.bSecond == 0) &&
      (ti.bMinute == 0) &&
      (ti.bHour   == 0) &&
      (ti.bDay    == 0) &&
      (ti.bMonth  == 0) &&
      (ti.bYear   == 0)) return false;

  return true;
}


static bool ReadCntCurrMonCan(void)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // � �������� 72 ������
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryData5(t);

      ShowPercent(60+t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break;         // ����� �� ������������
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 52);
        if (wCRC != InBuff(55) + InBuff(56)*0x100) { sprintf(szLo," ������ CRC: G0 "); Delay(1000); return(0); }

        uchar i;
        for (i=0; i<6; i++)
        {
          mpdbEng30[i*5] += PopDouble31()/1000; // ������� �����
        }
      }
    }
  }

  for (t=0; t<bTARIFFS; t++) // � �������� 72 ������
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryData4(t);

      ShowPercent(70+t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break; // ����� �� ������������
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 196);
        if (wCRC != InBuff(199) + InBuff(200)*0x100) { sprintf(szLo," ������ CRC: G1 "); Delay(1000); return(0); }

        uchar i;
        for (i=0; i<24; i++)
        {
          mpdbEng30[1 + (i/4)*5 + i%4] += PopDouble31()/1000; // ������� �� �������/���������� ����� � �������/���������� �����
        }
      }
    }
  }

  return(1);
}


bool    ReadMonIndexExt31(void)
{
  uchar m;
  for (m=0; m<=12; m++)
  {
    MonitorString("\n month "); MonitorCharDec(m);

    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryData26(m, 0);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return 0xEE;
    else
    {
      uint wCRC = MakeCrc16Bit31InBuff(3, 100);
      if (wCRC != InBuff(103) + InBuff(104)*0x100) { sprintf(szLo," ������ CRC: G2 "); Delay(1000); return(0); }

      time ti = ReadPackTime31();
      MonitorString("\n time "); MonitorTime(ti);

      if (ti.bMonth == 0)
        mpbChannelsMon[m] = 0;
      else
        mpbChannelsMon[m] = (10 + ti.bMonth)%12 + 1;

      if (ti.bMonth != 0)
        { Clear(); sprintf(szLo+2,"�������: %-2u", mpbChannelsMon[m]); Delay(200); }
      else
        { Clear(); sprintf(szLo+1,"�����: %2u-%-2u",m,12); }
    }
  }

  return(1);
}


uchar   SearchMonIndexExt31(uchar  bMon)
{
  sprintf(szLo," ���������: %-2u  ", bMon); DelayInf();

  uchar m;
  for (m=0; m<=12; m++)
    if (mpbChannelsMon[m] == bMon)
      return m;

  return 0xFF;
}


bool  ReadEngMonExt31(uchar  ibMon)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // � �������� 72 ������
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryData26(ibMon, t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      uint wCRC = MakeCrc16Bit31InBuff(3, 100);
      if (wCRC != InBuff(103) + InBuff(104)*0x100) { sprintf(szLo," ������ CRC: G3 "); Delay(1000); return(0); }

      InitPop(3+4); // ���������� ����/�����

      uchar i;
      for (i=0; i<6; i++)
      {
        mpdbChannelsMon[i] += PopDouble31()/1000;
      }
    }
  }

  return(1);
}


bool  ReadEngMonCurrExt31(void)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // � �������� 72 ������
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryData4(t);

      ShowPercent(80+t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break; // ����� �� ������������
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 196);
        if (wCRC != InBuff(199) + InBuff(200)*0x100) { sprintf(szLo," ������ CRC: G4 "); Delay(1000); return(0); }

        uchar i;
        for (i=0; i<24; i++)
        {
          mpdbEng30[1 + (i/4)*5 + i%4] += PopDouble31()/1000; // ������� �� �������/���������� ����� � �������/���������� �����
        }
      }
    }
  }

  uchar i;
  for (i=0; i<6; i++)
  {
    mpdbChannelsMon[i] += mpdbEng30[i*5+1]; // ������� �� ������� �����
  }

  return(1);
}


bool    ReadEngAbsExt31(void)
{
  uchar t;
  for (t=0; t<bTARIFFS; t++) // � �������� 72 ������
  {
    uchar r;
    for (r=0; r<bMINORREPEATS; r++)
    {
      DelayOff();
      QueryData5(t);

      ShowPercent(90+t);

      if (Input31() == SER_GOODCHECK) break;
      if (fKey == true) return false;
    }

    if (r == bMINORREPEATS) return(0);
    else
    {
      if (ValidPackTime() == 0) break; // ����� �� ������������
      else
      {
        uint wCRC = MakeCrc16Bit31InBuff(3, 52);
        if (wCRC != InBuff(55) + InBuff(56)*0x100) { sprintf(szLo," ������ CRC: G5 "); Delay(1000); return(0); }

        uchar i;
        for (i=0; i<6; i++)
        {
          mpdbChannelsAbs[i] += PopDouble31()/1000;
        }
      }
    }
  }

  return(1);
}


double2 ReadCntMonCanExt31(uchar  ibMon, time  ti)
{
  if (ReadMonIndexExt31() == 0) return GetDouble2Error();
  Clear();


  uchar i;
  for (i=0; i<6; i++) mpdbChannelsMon[i] = 0;

  uchar m = ibMon+1;
  uchar ibDay = 0;
  do
  {
    if ((m%12 + 1) == ti.bMonth)
    {
      if (ReadEngMonCurrExt31() == 0) return GetDouble2Error();
    }
    else
    {
      uchar ibGrp = SearchMonIndexExt31(m%12 + 1);
      if (ibGrp == 0xFF) { sprintf(szLo,"  ����������� ! "); Delay(1000); return GetDouble2Error(); }
      Clear();
      if (ReadEngMonExt31(ibGrp) == 0) return GetDouble2Error();
    }
    ShowPercent(80 + ibDay++);
  }
  while ((bMONTHS + ti.bMonth - ++m) % bMONTHS != 0 );


  for (i=0; i<6; i++) mpdbChannelsAbs[i] = 0;

  if (ReadEngAbsExt31() == 0) return GetDouble2Error();
  ShowPercent(99);


  double dbTrans = mpdbTransCnt[ibDig];

  for (i=0; i<6; i++)
  {
    mpdbChannelsC[i] = mpdbChannelsAbs[i] - mpdbChannelsMon[i];
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}



double2 ReadCntMonCan31(uchar  ibMon)
{
  time2 ti2 = QueryTime31_Full(50);
  if (ti2.fValid == false) return GetDouble2Error();
  time ti = ti2.tiValue;


  uchar i;
  for (i=0; i<30; i++) mpdbEng30[i] = 0;

  if (NewVersion31())
  {
    if (ti.bMonth != ibMon+1) // �������� ��������� ��� ���� �������, ����� ��������
    {
      if (GetVersion31() == 49)
        return ReadCntMonCanExt31(ibMon, ti);
      else
      {
        Clear(); sprintf(szLo+3,"����������"); Delay(1000);
        Clear(); sprintf(szLo+3,"������ 49"); Delay(1000);
        return GetDouble2Error();
      }
    }
    else // �������� ��������� ��� �������� ������ (������� �� ������ ������� �����)
    {
      if (ReadCntCurrMonCan() == 0) return GetDouble2Error();
    }
  }
  else
  {
    ShowLo(szNoVersion); Delay(1000); return GetDouble2Error();
  }

  ShowPercent(100);


  double dbTrans = mpdbTransCnt[ibDig];

  for (i=0; i<6; i++)
  {
    mpdbChannelsC[i] = mpdbEng30[i*5+0] - mpdbEng30[i*5+3]; // ������� ����� ����� ������� �� ������� ����� ����� ������� �� ������ ������� �����
    mpdbChannelsC[i] *= dbTrans;
    mpboChannelsA[i] = true;
  }

  return GetDouble2(mpdbChannelsC[diCurr.ibLine], true);
}

#endif
