/*------------------------------------------------------------------------------
MEM_FACTORS,C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������ � ������������� (��� �������/�������� � �������� ���������)
double                  mpdbTransEng[bCANALS],
                        mpdbTransCnt[bCANALS];

// ������ � �������������� (��� ����������� � ����������� ����������)
double                  mpdbPulseHou[bCANALS],
                        mpdbPulseMnt[bCANALS];

// ������ � ������������
double                  mpdbValueEngHou[bCANALS],
                        mpdbValueCntHou[bCANALS],
                        mpdbValueEngMnt[bCANALS],
                        mpdbValueCntMnt[bCANALS];

// ������ ��������� �������� ���������
double                  mpdbCount[bCANALS];

// ������ � ������
double                  mpdbLosse[bCANALS];

// ������ ��������� � ��������������
double                  mpdbLevel[bCANALS];
