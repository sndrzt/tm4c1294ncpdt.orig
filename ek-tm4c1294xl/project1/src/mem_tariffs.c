#include        "main.h"



// ���� ���� ������� �������
boolean                 boOldTariffs;



// ������ ����������
relaxs                  mpreRelaxs;

// ���������� ����������
time                    tiRelax;

// ������� ������������� ����������
boolean                 boRelaxsFlag;

// ���������� ����������
uchar                   ibRelaxsTariff;



// ������ �������� �������� �������� �� ������� � ������� ������ (��� �������� � �������)
zones                   mpzoPowMonthMode[12+4+1][bMODES],
                        mpzoEngMonthMode[12+4+1][bMODES];

// ������ ������ ������� �������� �������� �������� �� ������� � ������� ������ (��� �������� � �������)
boolean                 mpboPowMonthMode[12+4+1][bMODES],
                        mpboEngMonthMode[12+4+1][bMODES];

// ������ �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
uchar                   mpibPowCurrTariff[48],
                        mpibEngCurrTariff[48];

// ������ �������� ������� ��� ������� �������� ������� �����
uchar                   mpibPowPrevTariff[48],
                        mpibEngPrevTariff[48];

// ������� �����������/���������� �������� �������� �������� �� ������� � ���������� ������
boolean                 boPublicCurr,
                        boPublicPrev;



// ������ �������� ������� �������� ��� �� ����� � ������� (������ �������)
uchar                   mpchPowMonth[12],
                        mpchEngMonth[12];

// ������� ��������� ������� � �������� ��� (������ �������)
uchar                   bOldMode;

// ���������� ����������
uchar                   chOldMode;

// ���������� ����������
uchar                   ibAltMode;



// �������� �������� �������
zones                   zoAlt,zoKey;

// ������ �������� �������� ��������
breaks                  brAlt,brKey;

// ���������� ����������
boolean                 boAlt;



// ���� ������������� �������� ��������
boolean                 boGapsFlag;

// ������ ������� �������� ��������
gaps                    mpgaGaps;

// ����������
time                    tiGap;

// ������ �������� �������� �� ��� �� ������
uchar                   mpbGaps[365];
