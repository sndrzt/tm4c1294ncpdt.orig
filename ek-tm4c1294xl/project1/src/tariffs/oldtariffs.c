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
void    ReplaceZone(uchar  ibOld, uchar  ibNew)
{
uchar  i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);
    if (brAlt.ibTariff = ibOld)
    {
      brAlt.ibTariff = ibNew;
      SetZoneAltBreak(i);
    }
  }
}



// ���������� � ����� ibAltMode ��������� �������� �������� ������ �� ������ 0 (�����)
void    ReplaceMode(uchar  ibOld, uchar  ibNew)
{
  if (fEnergy == 0)
  {
    // ������ �������� �������� ������ �� ������ 0 (�����)
    ibMode = 0;
    zoAlt = *PGetZonePowMonthMode();

    // �������� ���� ����� �� ������
    ReplaceZone(ibOld,ibNew);                      

    // �������������� ������ � ����� ibAltMode
    ibMode = ibAltMode;
    boAlt = true;

    // ���������� ��������� �������� �������� ������
    SetZonePowMonthMode();     
    SetBoolPowMonthMode();
  }
  else
  {
    // ������ �������� �������� ������ �� ������ 0 (�����)
    ibMode = 0;
    zoAlt = *PGetZoneEngMonthMode();

    // �������� ���� ����� �� ������
    ReplaceZone(ibOld,ibNew);

    // �������������� ������ � ����� ibAltMode
    ibMode = ibAltMode;
    boAlt = true;

    // ���������� ��������� �������� �������� ������
    SetZoneEngMonthMode();
    SetBoolEngMonthMode();
  }
}
// ������� ��������������� ��������� ���������� ibMonth,ibAltMode



// ��������� ������� �������� ��������� ������� � ��������� ���
void    MakeOldMode(void)
{
  switch (bOldMode)
  {     
    case 0:         
      ibAltMode = 1;    // ��� ������
      ReplaceMode(0,0); // ���������� ������ � ������� � ��������� ���
      ReplaceMode(1,1);
      ReplaceMode(2,2);
      ReplaceMode(3,3);

      ibAltMode = 2;    // ��� �������� ����
      ReplaceMode(0,0); // ���������� ������ � ������� � ��������� ���
      ReplaceMode(1,1);
      ReplaceMode(2,2);
      ReplaceMode(3,3);
      break;
    
    case 1:
    case 3:          
      ibAltMode = 1;    // ��� ������
      ReplaceMode(0,1); // � �������� � �������� ��� �� �������� ������
      ReplaceMode(1,1);
      ReplaceMode(2,1);
      ReplaceMode(3,1);

      ibAltMode = 2;    // ��� �������� ����
      ReplaceMode(0,1); // � �������� � �������� ��� �� �������� ������
      ReplaceMode(1,1);
      ReplaceMode(2,1);
      ReplaceMode(3,1);
      break;
    
    case 2:          
      ibAltMode = 1;    // ��� ������
      ReplaceMode(0,0); // � �������� � �������� ��� �� ������� ������
      ReplaceMode(1,0);
      ReplaceMode(2,0);
      ReplaceMode(3,0);

      ibAltMode = 2;    // ��� �������� ����
      ReplaceMode(0,0); // � �������� � �������� ��� �� ������� ������
      ReplaceMode(1,0);
      ReplaceMode(2,0);
      ReplaceMode(3,0);
      break;

    case 4:          
      ibAltMode = 1;    // ��� ������
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(3,1);

      ibAltMode = 2;    // ��� �������� ����
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(3,1);
      break;

    case 5:          
      ibAltMode = 1;    // ��� ������
      ReplaceMode(0,0);       
      ReplaceMode(1,1);       
      ReplaceMode(2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(3,1);

      ibAltMode = 2;    // ��� �������� ����
      ReplaceMode(0,0);       
      ReplaceMode(1,0); // ������� ����� ���������� �� ������ �����
      ReplaceMode(2,1); // �������� � �������� ������ ���������� �� ������� �����
      ReplaceMode(3,1);
      break;
  }
}
// ������� ��������������� ��������� ���������� ibMonth,fEnergy



// ��������� ������� �������� ��������� ������� � ��������� ���
void    MakeAllOldModes(uchar  bT)
{
  bOldMode = bT;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    fEnergy = 1; MakeOldMode();
    fEnergy = 0; MakeOldMode();
  }
}



// ������ ��������� ��������� ������� �� ��������� ������� (��� �������)
void    SetCharEngMonths(uchar  ibBeg, uchar  ibEnd)
{
  ibMode = 0;
  SetZonesEngMonthsMode(ibBeg,ibEnd);

  fEnergy = 1;
  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    MakeOldMode();
    mpchEngMonth[ibMonth] = chOldMode;
  }
}
// ������� ��������������� ��������� ���������� zoKey,chOldMode


// ������ ��������� ��������� ������� �� ��������� ������� (��� ��������)
void    SetCharPowMonths(uchar  ibBeg, uchar  ibEnd)
{
  ibMode = 0;
  SetZonesPowMonthsMode(ibBeg,ibEnd);

  fEnergy = 0;
  for (ibMonth=ibBeg; ibMonth<=ibEnd; ibMonth++)
  {
    MakeOldMode();
    mpchPowMonth[ibMonth] = chOldMode;
  }
}
// ������� ��������������� ��������� ���������� zoKey,chOldMode
