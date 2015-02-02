/*------------------------------------------------------------------------------
TARIFFS.C

 ������������ ���������� ��������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../display.h"
#include        "../delay.h"
#include        "../access.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "zones.h"
#include        "oldtariffs.h"
#include        "relaxs.h"
#include        "gaps.h"



// ������� ������� �� ��������
uchar                   ibMonth,ibMode;



// ���������� ���� ������� ��������� ��������� ������� (��� �������)
void    SetBoolEngMonthMode(void)
{
  mpboEngMonthMode[ibMonth][ibMode] = boAlt;
}

/*
// ������ ���� ������� ��������� ��������� ������� (��� �������)
boolean GetBoolEngMonthMode(void)
{
  return( mpboEngMonthMode[ibMonth][ibMode] );
}
*/

// ���������� ���� ������� ��������� ��������� ������� (��� ��������)
void    SetBoolPowMonthMode(void)
{
  mpboPowMonthMode[ibMonth][ibMode] = boAlt;
}

/*
// ������ ���� ������� ��������� ��������� ������� (��� ��������)
boolean GetBoolPowMonthMode(void)
{
  return( mpboPowMonthMode[ibMonth][ibMode] );
}
*/


// ���������� �������� �������� ������ (��� �������)
void    SetZoneEngMonthMode(void)
{
  mpzoEngMonthMode[ibMonth][ibMode] = zoAlt;
}


// ������ �������� �������� ������ (��� �������)
zones  *PGetZoneEngMonthMode(void)
{
  return( &mpzoEngMonthMode[ibMonth][ibMode] );
}


// ���������� �������� �������� ������ (��� ��������)
void    SetZonePowMonthMode(void)
{
  mpzoPowMonthMode[ibMonth][ibMode] = zoAlt;
}


// ������ �������� �������� ������ (��� ��������)
zones  *PGetZonePowMonthMode(void)
{
  return( &mpzoPowMonthMode[ibMonth][ibMode] );
}



// ���������� �������� �������� ������ �� ��������� ������� (��� �������)
void    SetZonesEngMonthsMode(uchar  ibBeg, uchar  ibEnd)
{
  boAlt = true;
  memcpy(&zoAlt, &zoKey, sizeof(zones));

  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    SetZoneEngMonthMode();
    SetBoolEngMonthMode();
  }
}
// ������� ��������������� ��������� ���������� ibMode,zoKey


// ���������� �������� �������� ������ �� ��������� ������� (��� ��������)
void    SetZonesPowMonthsMode(uchar  ibBeg, uchar  ibEnd)
{
  boAlt = true;
  memcpy(&zoAlt, &zoKey, sizeof(zones));

  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    SetZonePowMonthMode();
    SetBoolPowMonthMode();
  }
}
// ������� ��������������� ��������� ���������� ibMode,zoKey



void    SetTariffsDefault(void)
{
  if (boPublicCurr == true)
  {
    chOldMode = '_';

    SetKeyZonePow();
    SetCharEngMonths(0,11);

    SetKeyZonePow();
    SetCharPowMonths(0,11);
  }
  else
  {
    chOldMode = '_';

    SetKeyZoneEng();
    SetCharEngMonths(0,11);

    SetKeyZonePow();
    SetCharPowMonths(0,11);
  }
}



// ����� �������� �� ���������
void    ResetTariffs(void)
{
  // ����������� �������� ������� ��� ������� � �������
  boPublicCurr = false;

  // ������ ������� ��������� �������
  boOldTariffs = true;

  // ������� ��������� ������� � �������� ��� (������ �������)
  bOldMode = 0;

  boAlt = false;
  for (ibMonth=0; ibMonth<12+4+1; ibMonth++)
  {
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
      SetBoolEngMonthMode(); 
      SetBoolPowMonthMode(); 
    }
  }

  memset(&mpchEngMonth, '\0', sizeof(mpchEngMonth)); 
  memset(&mpchPowMonth, '\0', sizeof(mpchPowMonth)); 

  SetTariffsDefault();
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
uchar  i,j;

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

  zoAlt = *PGetZoneEngMonthMode();
  MakeTariff(mpibEngCurrTariff);

  zoAlt = *PGetZonePowMonthMode();
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
uchar  i,j;

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

  zoAlt = *PGetZoneEngMonthMode();
  MakeTariff(mpibEngPrevTariff);

  zoAlt = *PGetZonePowMonthMode();
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
