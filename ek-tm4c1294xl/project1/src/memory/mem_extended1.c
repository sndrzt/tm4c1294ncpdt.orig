/*------------------------------------------------------------------------------
MEM_DIRECT.C


------------------------------------------------------------------------------*/

#include        "../main.h"



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
