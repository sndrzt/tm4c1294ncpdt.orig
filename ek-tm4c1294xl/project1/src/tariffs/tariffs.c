/*------------------------------------------------------------------------------
TARIFFS.C

 ����� ������� ������� �������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_program.h"
#include        "../display/display.h"
#include        "../delay.h"
#include        "../flash/files.h"
#include        "../access.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "zones.h"
#include        "oldtariffs.h"
#include        "relaxs.h"
#include        "gaps.h"
#include        "tariffs.h"



file const              flPublicTariffs = {wFLA_PUBLIC_TARIFFS, &fPublicTariffsCurr, sizeof(boolean)};
file const              flOldTariffsMode = {wFLA_OLD_TARIFFS_MODE, &bOldTariffsMode, sizeof(uchar)};



void    InitTariffs(void)
{
  LoadFile(&flPublicTariffs);

  LoadFile(&flOldTariffsMode);
}


void    ResetTariffs(void)
{
  // ����������� �������� ������� ��� ������� � �������
  fPublicTariffsCurr = false;
  SaveFile(&flPublicTariffs);

  // ������� ��������� ������� � �������� ��� (������ �������)
  bOldTariffsMode = 0;
  SaveFile(&flOldTariffsMode);

//  memset(&mpchEngMonth, '\0', sizeof(mpchEngMonth));
//  memset(&mpchPowMonth, '\0', sizeof(mpchPowMonth));
//
//  SetTariffsDefault();
}



void    SetZoneEngMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  mpzoEngMonthMode[ibMonth][ibMode] = *pzoT;
}


zones  *PGetZoneEngMonthMode(uchar ibMonth, uchar ibMode) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  return( &mpzoEngMonthMode[ibMonth][ibMode] );
}


void    SetZonePowMonthMode(uchar ibMonth, uchar ibMode, zones *pzoT) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  mpzoPowMonthMode[ibMonth][ibMode] = *pzoT;
}


zones  *PGetZonePowMonthMode(uchar ibMonth, uchar ibMode) {
	ASSERT(ibMonth < 12);
	ASSERT(ibMode < bMODES);
  return( &mpzoPowMonthMode[ibMonth][ibMode] );
}



// ���������� �������� �������� ������ �� ��������� ������� (��� �������)
void    SetZonesEngMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT)
{
uchar  ibMonth;

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    SetZoneEngMonthMode(ibMonth, ibMode, pzoT);
  }
}


// ���������� �������� �������� ������ �� ��������� ������� (��� ��������)
void    SetZonesPowMonthsMode(uchar  ibMonthBeg, uchar  ibMonthEnd, uchar  ibMode, zones *pzoT)
{
uchar  ibMonth;

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    SetZonePowMonthMode(ibMonth, ibMode, pzoT);
  }
}



void    SetTariffsDefault(void)
{
uchar  chOldMode;

  if (fPublicTariffsCurr == true)
  {
    chOldMode = '_';

    SetKeyZonePow();
    SetCharEngMonths(0,11,&zoKey,chOldMode);

    SetKeyZonePow();
    SetCharPowMonths(0,11,&zoKey,chOldMode);
  }
  else
  {
    chOldMode = '_';

    SetKeyZoneEng();
    SetCharEngMonths(0,11,&zoKey,chOldMode);

    SetKeyZonePow();
    SetCharPowMonths(0,11,&zoKey,chOldMode);
  }
}



// ������������ ������ �������� ������� ��� ������� �������� ������� �����
void    MakeTariff(uchar  mpTariff[48])
{
uchar   i,j;

  GetZoneAltBreak(0);
  for (j=0; j<48; j++)
    mpTariff[j] = brAlt.ibTariff;

  j = 0;
  for (i=0; i<bBREAKS; i++)
  {
    while (j < GetBreakAltIndex(i))
    {
      GetZoneAltBreak(i);
      mpTariff[j++] = brAlt.ibTariff;
    }
  }
}
// ������� ��������������� ��������� ���������� zoAlt



// ���������� ��� ������� ����� ������������� ������ ����������
uchar   RelaxIndex(void)
{
uchar i;

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return tiRelax.bSecond;   
  }

  return 0;
}
// ������� ��������������� ��������� ���������� tiAlt



// ������������ ������ �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
void    MakeAllCurrTariffs(void)
{
uchar  i, j;
uchar  ibMonth, ibMode;

  tiAlt = *PGetCurrTimeDate();

  if (boGapsFlag == false) 
  {
    ibMonth = tiAlt.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndex_Alt()];
  } 

  ibMode  = GetModeAlt();               

  zoAlt = *PGetZoneEngMonthMode(ibMonth,ibMode);
  MakeTariff(mpibEngCurrTariff);

  zoAlt = *PGetZonePowMonthMode(ibMonth,ibMode);
  MakeTariff(mpibPowCurrTariff);

  if (boRelaxsFlag == true)
  {
    j = RelaxIndex();
    i = Weekday();
    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff; 
      if (i >= bTARIFFS) i = 0;
      // memset(&mpibEngCurrTariff, i, sizeof(mpibEngCurrTariff));
      memset(&mpibPowCurrTariff, i, sizeof(mpibPowCurrTariff));
    }
  }
}


void    MakeAllPrevTariffs(void)
{
uchar  i, j;
uchar  ibMonth, ibMode;

  ibMonth = tiAlt.bMonth - 1;                   

  if (boGapsFlag == false) 
  {
    ibMonth = tiAlt.bMonth - 1;
  }
  else
  {
    MakeGaps();
    ibMonth = mpbGaps[GetDayIndex_Alt()];
  } 

  ibMode  = GetModeAlt();               

  zoAlt = *PGetZoneEngMonthMode(ibMonth,ibMode);
  MakeTariff(mpibEngPrevTariff);

  zoAlt = *PGetZonePowMonthMode(ibMonth,ibMode);
  MakeTariff(mpibPowPrevTariff);

  if (boRelaxsFlag == true)
  {
    j = RelaxIndex();
    i = Weekday();
    if ((j != 2) && ((i == 5) || (i == 6) || (j == 1)))
    {
      i = ibRelaxsTariff; 
      if (i >= bTARIFFS) i = 0;
      // memset(&mpibEngPrevTariff, i, sizeof(mpibEngPrevTariff));
      memset(&mpibPowPrevTariff, i, sizeof(mpibPowPrevTariff));
    }
  }
}
// ������� ��������������� ��������� ���������� tiAlt
