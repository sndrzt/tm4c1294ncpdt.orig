/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ���� ���������� ������ ���������� ����������
boolean                 boEnblAllParams;

// ���� ������� ������ ���������� ���������� (TRUE: ������ 3 ������, FALSE: ������ 30 �����)
boolean                 boMntParams;

// �������
boolean                 boFixParamsBugs;

// ������ ���������� ����������
digital                 mpdiParam[wPARAMS];

// ������ ������������� �������
real                    mpreParamDiv[wPARAMS];

// ������ ���������� ������ �� ����������
boolean                 mpboEnblPar[wPARAMS];

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
