/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������ ���������� ����������
boolean                 boParamsFlag;

// ���� ������� ������ ���������� ���������� (TRUE: ������ 3 ������, FALSE: ������ 30 �����)
boolean                 boMntParams;

// ������ ���������� ����������
digital                 mpdiParam[wPARAMS];

// ������ ������������� �������
real                    mpreParamDiv[wPARAMS];

// ������ ���������� ������ �� ����������
boolean                 mpboEnblParams[wPARAMS];

// ������������� ������
real                    mpreParBuff[2][wPARAMS];

// ������������� ������
time                    mptiParBuff[wPARAMS];

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
