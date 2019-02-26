/*------------------------------------------------------------------------------
MEM_PROFILE!C


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

// ���������� ���������� ������, �������� � �������� ���������
uchar                   cbDigDay, cbDigMon;



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
time                    tiValueA, tiValueB, tiValueC, tiValueS;

// ���������� ����������
ulong                   dwValueC, dwValueS;



// ������������� ������
double                  mpdbBuffCanHou[4][48];

// ������� �������� 30-���. ��������
double                  mpdbEngFrac[bCANALS];

// ������� �������� 30-���. ��������
double                  mpdbEngFracDigCan[bCANALS][6];

// ������� �������� 30-���. ��������
double                  mpdbEngFracDigCan8[bCANALS][8];

// �������� ������������ ����������� ��������
uint                    mpcwOverflowHhr[bCANALS];

// �������� ������ �����
uint                    mpcwErrorLink[bCANALS];

// �������� ��� ������� �������� ��102
uint                    wDividerS;



// ��������
uint                    mpcwProfileLinkWrn[bPORTS][48],
                        mpcwProfileLinkErr[bPORTS][48];
