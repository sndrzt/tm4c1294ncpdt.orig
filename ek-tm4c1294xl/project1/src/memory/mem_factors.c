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
real                    mpreValueEngHou[bCANALS],
                        mpreValueCntHou[bCANALS],
                        mpreValueEngMnt[bCANALS],
                        mpreValueCntMnt[bCANALS];

// ������ ��������� ���������
real                    mpreCount[bCANALS];

// ������ � ������
real                    mpreLosse[bCANALS];

// ������ ��������� � ��������������
real                    mpreLevel[bCANALS];
