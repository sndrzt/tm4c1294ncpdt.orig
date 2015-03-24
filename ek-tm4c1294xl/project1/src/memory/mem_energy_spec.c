/*------------------------------------------------------------------------------
MEM_ENERGY_SPEC.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������ �� ������� �������� ������, �������� � �������� ���������
uint                    iwDigHou;

// ������� ����������� ��������� (�� ���������)
uint                    mpwImpHouCanSpec[bCANALS];

// ������� ����������� ��������� �� ������� (�� ������ � �������)
impulse                 mpimDayCanSpec[bCANALS],
                        mpimMonCanSpec[bCANALS];

// ������� ���������� �������� �� ������� (�� ������ � �������)
power                   mppoDayGrpSpec[bGROUPS],
                        mppoMonGrpSpec[bGROUPS];



// �����/���� ������ � ����������� �������
time                    tiOldDay, tiOldMon;

// ������� ������ � ����������� �������
uchar                   ibOldDay, ibOldMon;



// ������ ��������� ��� ��������� �������� �� ������ �����
uchar                   mpbWinterCan[bCANALS];



// ���������� ������� � �������� ��������
uchar                   cbChannels;

// ������ ������� � �������� ��������
uint                    mpwChannels[bCHANNELS];



// ���� ������� �������� �������
uchar                   boOpenCalc;



// �������������
impulse                 mpdeDayCan[bCANALS],
                        mpdeMonCan[bCANALS];

// �������������
uint                    mpwImpHouCanDef[bCANALS];



// ������ ����� �� ���� � �������
time                    mpdeDay[bDAYS],
                        mpdeMon[bMONTHS];
