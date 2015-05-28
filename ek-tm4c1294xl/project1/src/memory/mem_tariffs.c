/*------------------------------------------------------------------------------
MEM_TARIFFS.S

 TODO add requests for tariffs for all modes
------------------------------------------------------------------------------*/

#include "../main.h"



// ������� ������������� ����������
bool                 boRelaxsFlag;

// ����� ��� ������������� ����������
uchar                   ibRelaxsTariff;

// ������ ����������
relaxs                  reRelaxs;

// ���������� ����������
time                    tiRelax;



// ������ �������� �������� �������� �� ������� � ������� ������ (��� �������� � �������)
zone                    mpzoPowMonthMode[12][bMODES],
                        mpzoEngMonthMode[12][bMODES];

// ������ �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
uchar                   mpibPowCurrTariff[48],
                        mpibEngCurrTariff[48];

// ������ �������� ������� ��� ������� �������� ������� �����
uchar                   mpibPowPrevTariff[48],
                        mpibEngPrevTariff[48];

// ������� �����������/���������� �������� �������� �������� �� ������� � ���������� ������
bool                 fPublicTariffs, fPublicTariffsPrevMon;

// ������ �������� ������� �������� ��� �� ����� � ������� (������ �������)
period                  mpeTariffPow[12],
                        mpeTariffEng[12];

// ������� ��������� ������� � �������� ��� (������ �������)
uchar                   bOldTrfMode;



// �������� �������� �������
zone                    zoAlt, zoKey;

// ������ �������� �������� ��������
br3ak                   brAlt, brKey;



// ���� ������������� �������� ��������
bool                 boGapsFlag;

// ������ ������� �������� ��������
gaps                    gaGaps;

// ����������
time                    tiGap;

// ������ �������� �������� �� ��� �� ������
uchar                   mpbGaps[365];
