/*------------------------------------------------------------------------------
MEM_DIRECT.C


------------------------------------------------------------------------------*/

#include        "../main.h"



//
time                    mptiEsc_T[bCANALS];

//
real                    mpreEsc_S[bCANALS];

//
time                    mptiEsc_S[bCANALS];

//
real                    mpreEsc_V[bCANALS];

//
time                    mptiEsc_V[bCANALS];



// ���������� ����������
moment                  moAlt;

// ������ ���������� moment ��� ������������ ������ �������� ���������
moment                  mpmoEsc_U[bCANALS];



// �������� �������
uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                        mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                        mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

// �������� ����� ���������������� ���������
boolean                 mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];

// ����� ������� ������ ���������
boolean                 boDisableEsc1, boDisableEsc2, boDisableEsc3;
