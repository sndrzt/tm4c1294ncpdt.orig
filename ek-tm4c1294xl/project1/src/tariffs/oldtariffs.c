/*------------------------------------------------------------------------------
OLDTARIFFS.�

 ���������� �������� (������ �������)
------------------------------------------------------------------------------*/

#include        <string.h>
#include        <stdio.h>
#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../access.h"
#include        "../flash/files.h"
#include        "tariffs.h"
#include        "zones.h"



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
void    ReplaceMode(uchar  ibMonth, uchar  ibMode, domain  doT, uchar  ibTariffOld, uchar  ibTariffNew)
{
  if (doT == DOM_POWER)
  {
    // ������ �������� �������� ������ �� ������ 0 (�����)
    zoAlt = *PGetZonePowMonthMode(ibMonth, 0);

    // �������� ���� ����� �� ������
    ReplaceZone(ibTariffOld,ibTariffNew);

    // ���������� ��������� �������� �������� ������
    SetZonePowMonthMode(ibMonth, ibMode, &zoAlt);
  }
  else
  {
    // ������ �������� �������� ������ �� ������ 0 (�����)
    zoAlt = *PGetZoneEngMonthMode(ibMonth, 0);

    // �������� ���� ����� �� ������
    ReplaceZone(ibTariffOld,ibTariffNew);

    // ���������� ��������� �������� �������� ������
    SetZoneEngMonthMode(ibMonth, ibMode, &zoAlt);
  }
}



// ��������� ������� �������� ��������� ������� � ��������� ���
void    MakeTariffsModeMonth(uchar  ibMonth, domain  doT)
{
uchar  ibMode;

  switch (bTariffsMode)
  {     
    case 0:         
    	ibMode = 1;                          // ��� ������
      ReplaceMode(ibMonth,ibMode,doT,0,0); // ���������� ������ � ������� � ��������� ���
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,2);
      ReplaceMode(ibMonth,ibMode,doT,3,3);

      ibMode = 2;                          // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,doT,0,0); // ���������� ������ � ������� � ��������� ���
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,2);
      ReplaceMode(ibMonth,ibMode,doT,3,3);
      break;
    
    case 1:
    case 3:          
    	ibMode = 1;                          // ��� ������
      ReplaceMode(ibMonth,ibMode,doT,0,1); // � �������� � �������� ��� �� �������� ������
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1);
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                          // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,doT,0,1); // � �������� � �������� ��� �� �������� ������
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1);
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;
    
    case 2:          
    	ibMode = 1;                          // ��� ������
      ReplaceMode(ibMonth,ibMode,doT,0,0); // � �������� � �������� ��� �� ������� ������
      ReplaceMode(ibMonth,ibMode,doT,1,0);
      ReplaceMode(ibMonth,ibMode,doT,2,0);
      ReplaceMode(ibMonth,ibMode,doT,3,0);

      ibMode = 2;                          // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,doT,0,0); // � �������� � �������� ��� �� ������� ������
      ReplaceMode(ibMonth,ibMode,doT,1,0);
      ReplaceMode(ibMonth,ibMode,doT,2,0);
      ReplaceMode(ibMonth,ibMode,doT,3,0);
      break;

    case 4:          
    	ibMode = 1;                          // ��� ������
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(ibMonth,ibMode,doT,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                          // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(ibMonth,ibMode,doT,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;

    case 5:          
    	ibMode = 1;                          // ��� ������
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,1);
      ReplaceMode(ibMonth,ibMode,doT,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,doT,3,1);

      ibMode = 2;                          // ��� �������� ����
      ReplaceMode(ibMonth,ibMode,doT,0,0);
      ReplaceMode(ibMonth,ibMode,doT,1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(ibMonth,ibMode,doT,2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(ibMonth,ibMode,doT,3,1);
      break;
  }
}



// ��������� ������� �������� ��������� ������� � ��������� ���
void    MakeTariffsMode(void)
{
uchar  ibMonth;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
  	MakeTariffsModeMonth(ibMonth, DOM_ENERGY);
  	MakeTariffsModeMonth(ibMonth, DOM_POWER);
  }
}



// ������ ��������� ��������� ������� �� ��������� ������� (��� �������)
void    SetPeriodTariffsEng(uchar  ibMonthBeg, uchar  ibMonthEnd, zones  *pzo, period  pe)
{
uchar  ibMonth;

  SetZonesEngMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzo);

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
  	MakeTariffsModeMonth(ibMonth, DOM_ENERGY);
  	SaveZonesEng(ibMonth, 1);
  	SaveZonesEng(ibMonth, 2);

  	mpeTariffEng[ibMonth] = pe;
  }

  SaveFile(&flPeriodTariffEng);
}


// ������ ��������� ��������� ������� �� ��������� ������� (��� ��������)
void    SetPeriodTariffsPow(uchar  ibMonthBeg, uchar  ibMonthEnd, zones  *pzo, period  pe)
{
uchar  ibMonth;

  SetZonesPowMonthsMode(ibMonthBeg, ibMonthEnd, 0, pzo);

  for (ibMonth=ibMonthBeg; ibMonth<=ibMonthEnd; ibMonth++)
  {
  	MakeTariffsModeMonth(ibMonth, DOM_POWER);
  	SaveZonesPow(ibMonth, 1);
  	SaveZonesPow(ibMonth, 2);

  	mpeTariffPow[ibMonth] = pe;
  }

  SaveFile(&flPeriodTariffPow);
}
