/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������ ���������� ����������
boolean                 boParamsFlag;

// ���� ������� ������ ���������� ���������� (TRUE: ������ 3 ������, FALSE: ������ 30 �����)
boolean                 boMntParams;

// ������ ������������� �������
real                    mpreParamsDiv[wPARAMS];

// ������ ���������� ������ �� ����������
boolean                 mpboEnblParams[wPARAMS];

// ������������� ������
real                    mpreParamsBuff[2][wPARAMS];

// ������������� ������
time                    mptiParamsBuff[wPARAMS];

// ������ �� ���������� ������
uchar                   ibSoftTim;

// ������ �� ���������� ������
uint                    iwHardTim;

// ���������� ������� � ������� ���������� ����������
uint                    cwParamTim;

// �������
boolean                 boFixParamsBugs;

// �������
boolean                 boUseParamsDiv;
