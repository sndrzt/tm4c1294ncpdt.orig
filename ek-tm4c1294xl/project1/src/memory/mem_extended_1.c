/*------------------------------------------------------------------------------
MEM_EXTENDED_1,C


------------------------------------------------------------------------------*/

#include "../main.h"



// �������� ��������� ������� (�� ������ ���������� ������������ ������)
double                  mpdbEsc_S[bCANALS];

// ����� ���������� �������� mpdbEsc_S
time                    mptiEsc_S[bCANALS];

// �������� ��������� �� ������ ������� ����� (�� ������ ���������� ������������ ������)
double                  mpdbEsc_V[bCANALS];

// ����� ���������� �������� mpdbEsc_V
time                    mptiEsc_V[bCANALS];

// ����� �������� ��������� (�� ������ ���������� ������������ ������)
time                    mptiEsc_U1[bCANALS];

// ����� ���������� �������� mpdbEsc_U1
time                    mptiEsc_U2[bCANALS];



// �������� �������� �������
uint                    mpcwEscV_OK[bCANALS],
                        mpcwEscS_OK[bCANALS],
                        mpcwEscU_OK[bCANALS];

// �������� ��������� �������
uint                    mpcwEscV_Error[bCANALS],
                        mpcwEscS_Error[bCANALS],
                        mpcwEscU_Error[bCANALS];



// ����� ������� �������
bool                    boDsblEscU, boDsblEscV, boDsblEscS;

//
bool                    boMntEscS;

//
bool                    boExtendedEscU, boExtendedEscV, boExtendedEscS;
