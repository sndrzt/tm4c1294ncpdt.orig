/*------------------------------------------------------------------------------
OLDTARIFFS.�

 ������������ ���������� �������� (������ �������)
------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../access.h"
#include        "tariffs.h"
#include        "zones.h"



bool                    fEnergy;



// �������� �� ���� ������� ���������� zoAlt ���� ����� �� ������
void    ReplaceZone(uchar  ibTariffOld, uchar  ibTariffNew)
{
uchar  i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);
    if (brAlt.ibTariff = ibTariffOld)
    {
      brAlt.ibTariff = ibTariffNew;
      SetZoneAltBreak(i);
    }
  }
}



// ���������� � ����� ibAltMode ��������� �������� �������� ������ �� ������ 0 (�����)
void    ReplaceMode(uchar  ibMonth, uchar  ibMode, uchar  ibTariffOld, uchar  ibTariffNew)
{
  if (fEnergy == 0)
  {
    // ������ �������� �������� ������ �� ������ 0 (�����)
    zoAlt = *PGetZonePowMonthMode(ibMonth, 0);

    // �������� ���� ����� �� ������
    ReplaceZone(ibTariffOld,ibTariffNew);

    // ���������� ��������� �������� �������� ������
    SetZonePowMonthMode(ibMonth, ibMode, &zoAlt);
    SetBoolPowMonthMode(ibMonth, ibMode, true);
  }
  else
  {
    // ������ �������� �������� ������ �� ������ 0 (�����)
    zoAlt = *PGetZoneEngMonthMode(ibMonth, 0);

    // �������� ���� ����� �� ������
    ReplaceZone(ibTariffOld,ibTariffNew);

    // ���������� ��������� �������� �������� ������
    SetZoneEngMonthMode(ibMonth, ibMode, &zoAlt);
    SetBoolEngMonthMode(ibMonth, ibMode, true);
  }
}



// ��������� ������� �������� ��������� ������� � ��������� ���
void    MakeOldMode(uchar  ibMonth)
{
uchar  ibMode;

  switch (bOldMode)
  {     
    case 0:         
    	ibMode = 1;                      // ��� ������
      ReplaceMode(ibMonth,ibMode,0,0); // ���������� ������ � ������� � ��������� ���
      ReplaceMode(ibMonth,ibMode,1,1);
      ReplaceMode(ibMonth,ibMode,2,2);
      ReplaceMode(ibMonth,ibMode,3,3);

      ibMode = 2;                      // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,0,0); // ���������� ������ � ������� � ��������� ���
      ReplaceMode(ibMonth,ibMode,1,1);
      ReplaceMode(ibMonth,ibMode,2,2);
      ReplaceMode(ibMonth,ibMode,3,3);
      break;
    
    case 1:
    case 3:          
    	ibMode = 1;                      // ��� ������
      ReplaceMode(ibMonth,ibMode,0,1); // � �������� � �������� ��� �� �������� ������
      ReplaceMode(ibMonth,ibMode,1,1);
      ReplaceMode(ibMonth,ibMode,2,1);
      ReplaceMode(ibMonth,ibMode,3,1);

      ibMode = 2;                      // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,0,1); // � �������� � �������� ��� �� �������� ������
      ReplaceMode(ibMonth,ibMode,1,1);
      ReplaceMode(ibMonth,ibMode,2,1);
      ReplaceMode(ibMonth,ibMode,3,1);
      break;
    
    case 2:          
    	ibMode = 1;                      // ��� ������
      ReplaceMode(ibMonth,ibMode,0,0); // � �������� � �������� ��� �� ������� ������
      ReplaceMode(ibMonth,ibMode,1,0);
      ReplaceMode(ibMonth,ibMode,2,0);
      ReplaceMode(ibMonth,ibMode,3,0);

      ibMode = 2;                      // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,0,0); // � �������� � �������� ��� �� ������� ������
      ReplaceMode(ibMonth,ibMode,1,0);
      ReplaceMode(ibMonth,ibMode,2,0);
      ReplaceMode(ibMonth,ibMode,3,0);
      break;

    case 4:          
    	ibMode = 1;                      // ��� ������
      ReplaceMode(ibMonth,ibMode,0,0);
      ReplaceMode(ibMonth,ibMode,1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(ibMonth,ibMode,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,3,1);

      ibMode = 2;                      // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,0,0);
      ReplaceMode(ibMonth,ibMode,1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(ibMonth,ibMode,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,3,1);
      break;

    case 5:          
    	ibMode = 1;                      // ��� ������
      ReplaceMode(ibMonth,ibMode,0,0);
      ReplaceMode(ibMonth,ibMode,1,1);
      ReplaceMode(ibMonth,ibMode,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,3,1);

      ibMode = 2;                      // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,0,0);
      ReplaceMode(ibMonth,ibMode,1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(ibMonth,ibMode,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,3,1);
      break;
  }
}
// ������� ��������������� ��������� ���������� ibMonth,fEnergy



// ��������� ������� �������� ��������� ������� � ��������� ���
void    MakeAllOldModes(uchar  bT)
{
uchar  ibMonth;

  bOldMode = bT;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    fEnergy = 1; MakeOldMode(ibMonth);
    fEnergy = 0; MakeOldMode(ibMonth);
  }
}



// ������ ��������� ��������� ������� �� ��������� ������� (��� �������)
void    SetCharEngMonths(uchar  ibMonthBeg, uchar  ibMonthEnd, zones *pzoT)
{
uchar  ibMonth;

  SetZonesEngMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzoT);

  fEnergy = 1;
  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    MakeOldMode(ibMonth);
    mpchEngMonth[ibMonth] = chOldMode;
  }
}
// ������� ��������������� ��������� ���������� zoKey,chOldMode


// ������ ��������� ��������� ������� �� ��������� ������� (��� ��������)
void    SetCharPowMonths(uchar  ibMonthBeg, uchar  ibMonthEnd, zones *pzoT)
{
uchar  ibMonth;

  SetZonesPowMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzoT);

  fEnergy = 0;
  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
    MakeOldMode(ibMonth);
    mpchPowMonth[ibMonth] = chOldMode;
  }
}
// ������� ��������������� ��������� ���������� zoKey,chOldMode
