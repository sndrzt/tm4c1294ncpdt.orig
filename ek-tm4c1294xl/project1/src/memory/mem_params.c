/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������ ���������� ����������
bool                 boParamsFlag;

// ���� ������� ������ ���������� ���������� (true: ������ 3 ������, false: ������ 30 �����)
bool                 boMntParams;

// ������ ������������� �������
real                    mpreParamsDiv[wPARAMS];

// ������ ���������� ������ �� ����������
bool                 mpboEnblParams[wPARAMS];

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
bool                 boFixParamsBugs;

// �������
bool                 boUseParamsDiv;
