/*------------------------------------------------------------------------------
MEM_PROFILE.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ���� ������ ������ 30-�������� �������� � ������ ������
boolean                 boManualProfile;

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



// ������ ���������� � ������ ������ ������: ������� � ��������� �����������
uint                    wBaseCurr, wOffsCurr,
                        wBaseLast;

// ���������
ulong                   dwBaseCurr;



// ���������� ����������
uchar                   ibMinor, ibMinorMax;

// ���������� ����������
uint                    iwMajor;



// ������� ������� ��������� � ��������
uchar                   bDeltaOld, bDeltaNew;



// �������� �������
uint                    mpcwOutputZ[bCANALS],
                        mpcwOutputC[bCANALS],
                        mpcwOutput0[bCANALS],
                        mpcwOutput1[bCANALS],
                        mpcwOutput2[bCANALS],
                        mpcwOutput3[bCANALS];

