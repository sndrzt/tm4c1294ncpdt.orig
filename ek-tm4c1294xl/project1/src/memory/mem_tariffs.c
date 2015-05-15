/*------------------------------------------------------------------------------
MEM_TARIFFS.S

 TODO add requests for tariffs for all modes
------------------------------------------------------------------------------*/

#include "../main.h"



// ������� ������������� ����������
boolean                 boRelaxsFlag;

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
boolean                 fPublicTariffs;

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
boolean                 boGapsFlag;

// ������ ������� �������� ��������
gaps                    gaGaps;

// ����������
time                    tiGap;

// ������ �������� �������� �� ��� �� ������
uchar                   mpbGaps[365];
