/*------------------------------------------------------------------------------
MEM_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ���� ������ ������ 30-�������� �������� � ������ ������
boolean                 boManualProfile;



// �������� �������
uint                    mpcwEscV_OK[bCANALS], mpcwEscV_Error[bCANALS],
                        mpcwEscS_OK[bCANALS], mpcwEscS_Error[bCANALS],
                        mpcwEscU_OK[bCANALS], mpcwEscU_Error[bCANALS];

// �������� �������
uint                    mpcwProfile_OK[bCANALS],
                        mpcwProfile_Error[bCANALS];

// �������� ����� ���������������� ���������
boolean                 mpboDefEscV[bCANALS],
                        mpboDefEscS[bCANALS],
                        mpboDefEscU[bCANALS];
