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



// ���� ������� �������� �������
uchar                   boOpenCalc;



// �������������
impulse                 mpdeDayCan[bCANALS],
                        mpdeMonCan[bCANALS];

// �������������
uint                    mpwImpHouCanDef[bCANALS];
