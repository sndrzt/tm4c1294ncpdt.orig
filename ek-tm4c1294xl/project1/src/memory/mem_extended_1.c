/*------------------------------------------------------------------------------
MEM_EXTENDED_1.C


------------------------------------------------------------------------------*/

#include        "../main.h"



//
real                    mpreEsc_S[bCANALS];

//
time                    mptiEsc_S[bCANALS];

//
real                    mpreEsc_V[bCANALS];

//
time                    mptiEsc_V[bCANALS];

//
time                    mptiEsc_U1[bCANALS];

//
time                    mptiEsc_U2[bCANALS];



// �������� �������
uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                        mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                        mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

// �������� ����� ���������������� ���������
boolean                 mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];



// ����� ������� ������ ���������
boolean                 boDsblEscU, boDsblEscV, boDsblEscS;

// ����
boolean                 boMntEscS;

// ���� ����������� ���������� ������ ��� Esc-��������
boolean                 boExtendedEscU, boExtendedEscV, boExtendedEscS;
