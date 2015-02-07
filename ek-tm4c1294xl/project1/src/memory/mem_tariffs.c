/*------------------------------------------------------------------------------
MEM_TARIFFS.S

 TODO add requests for tariffs for all modes
------------------------------------------------------------------------------*/

#include        "../main.h"



// ������ ����������
relaxs                  mpreRelaxs;

// ���������� ����������
time                    tiRelax;

// ������� ������������� ����������
boolean                 boRelaxsFlag;

// ���������� ����������
uchar                   ibRelaxsTariff;



// ������ �������� �������� �������� �� ������� � ������� ������ (��� �������� � �������)
zones                   mpzoPowMonthMode[12][bMODES],
                        mpzoEngMonthMode[12][bMODES];

// ������ �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
uchar                   mpibPowCurrTariff[48],
                        mpibEngCurrTariff[48];

// ������ �������� ������� ��� ������� �������� ������� �����
uchar                   mpibPowPrevTariff[48],
                        mpibEngPrevTariff[48];

// ������� �����������/���������� �������� �������� �������� �� ������� � ���������� ������
boolean                 fPublicTariffsCurr,
                        fPublicTariffsPrev;



// ������ �������� ������� �������� ��� �� ����� � ������� (������ �������)
uchar                   mpcPowMonth[12],
                        mpcEngMonth[12];

// ������� ��������� ������� � �������� ��� (������ �������)
uchar                   bTariffsMode;



// �������� �������� �������
zones                   zoAlt,zoKey;

// ������ �������� �������� ��������
breaks                  brAlt,brKey;



// ���� ������������� �������� ��������
boolean                 boGapsFlag;

// ������ ������� �������� ��������
gaps                    mpgaGaps;

// ����������
time                    tiGap;

// ������ �������� �������� �� ��� �� ������
uchar                   mpbGaps[365];
