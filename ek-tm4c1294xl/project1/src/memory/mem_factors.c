/*------------------------------------------------------------------------------
MEM_FACTORS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������ � ������������� (��� �������/�������� � ��������� ���������)
real                    mpreTransEng[bCANALS],
                        mpreTransCnt[bCANALS];

// ������ � �������������� (��� ����������� � ����������� ����������)
real                    mprePulseHou[bCANALS],
                        mprePulseMnt[bCANALS];

// ������ � ������������
double                  mpdbValueEngHou[bCANALS],
                        mpdbValueCntHou[bCANALS],
                        mpdbValueEngMnt[bCANALS],
                        mpdbValueCntMnt[bCANALS];

// ������ ��������� ���������
real                    mpreCount[bCANALS];

// ������ � ������
real                    mpreLosse[bCANALS];

// ������ ��������� � ��������������
real                    mpreLevel[bCANALS];
