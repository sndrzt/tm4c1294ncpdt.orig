/*------------------------------------------------------------------------------
MEM_PARAMS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������ ���������� ����������
bool                    boParamsFlag;

// ���� ������� ������ ���������� ���������� (true: ������ 3 ������, false: ������ 30 �����)
bool                    boMntParams;

// ������ ������������� �������
float                   mpreParamsDiv[wPARAMS];

// ������ ���������� ������ �� ����������
bool                    mpboEnblParams[wPARAMS];

// ������������� ������
float                   mpreParamsBuff[2][wPARAMS];

// ������������� ������
time                    mptiParamsBuff[wPARAMS];

// ������������� ������
float                   mpreParam[wPARAMS];

// ������ �� ���������� ������
uchar                   ibSoftTim;

// ������ �� ���������� ������
uint                    iwHardTim;

// ���������� ������� � ������� ���������� ����������
uint                    cwParamTim;

// �������
bool                    boFixParamsBugs;

// �������
bool                    boUseParamsDiv;
