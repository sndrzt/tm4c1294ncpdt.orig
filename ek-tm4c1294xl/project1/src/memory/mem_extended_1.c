/*------------------------------------------------------------------------------
MEM_EXTENDED_1.C


------------------------------------------------------------------------------*/

#include "../main.h"



//
double                  mpdbEsc_S[bCANALS];

//
time                    mptiEsc_S[bCANALS];

//
double                  mpdbEsc_V[bCANALS];

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
bool                    mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];



// ����� ������� ������ ���������
bool                    boDsblEscU, boDsblEscV, boDsblEscS;

// ����
bool                    boMntEscS;

// ���� ����������� ���������� ������ ��� Esc-��������
bool                    boExtendedEscU, boExtendedEscV, boExtendedEscS;
