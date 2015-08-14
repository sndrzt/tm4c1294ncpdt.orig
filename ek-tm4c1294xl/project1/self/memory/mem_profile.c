/*------------------------------------------------------------------------------
MEM_PROFILE.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ������ ������ 30-�������� �������� � ������ ������
bool                    boManualProfile;

// ������� �������� ���������
uint                    cwHouRead;

// ������������ ������������ ������
uint                    cwHouLength;

// �������� �������
uint                    mpcwProfile_OK[bCANALS],
                        mpcwProfile_Error[bCANALS],
                        mpcwDigital_OK[bCANALS],
                        mpcwCalcDig[bCANALS];

// ������� ��������� ������� ��� ������ �������� ���������
bool                    fCurrCtrl;



// ������ �� ������� �������� ������, �������� � �������� ���������
uint                    iwDigHou;

// ���������� ���������� ������, �������� � �������� ���������
uint                    cwDigHou;



// ������ ���������� � ������ ������ ������: ������� � ��������� �����������
uint                    wBaseCurr, wOffsCurr,
                        wBaseLast;

// ���������
ulong                   dwBaseCurr;

// ������ �������� ������� ������
uchar                   bCurrHouIndex;



// ���������� ����������
uchar                   ibMinor, ibMinorMax;

// ���������� ����������
uint                    iwMajor;



// ������� ������� ��������� � ��������
uchar                   bDeltaOld, bDeltaNew;



// ����� � ������� ������������� �������
uchar                   bOutputC0, bOutputC1, bOutputC2;

// �������� �������
uint                    mpcwOutputZ[bCANALS],
                        mpcwOutputC[bCANALS],
                        mpcwOutput0[bCANALS],
                        mpcwOutput1[bCANALS],
                        mpcwOutput2[bCANALS],
                        mpcwOutput3[bCANALS];

// ���������� ����������
time                    tiValueA, tiValueB, tiValueC;

// ���������� ����������
ulong                   dwValueC;



// ������������� ������
float                   mpreBuffCanHou[4][48];

// ������������� ������
float                   mpreEngFracDigCan[bCANALS][6];
