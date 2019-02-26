/*------------------------------------------------------------------------------
MEM_DIGITALS!C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������� ����� ������������ �������� ���������
volatile uint           wDigitalsMask;

// ������ ����������� �������
bool                    mpboEnblCan[bCANALS];



// ���� ������������� ������� ���������
bool                    boEnblKeys;

// ������ ������� ���������
line                    mpphKeys[bCANALS];

// �������������� ��������� �������� ���������
ulong                   mpdwAddress1[bCANALS],
                        mpdwAddress2[bCANALS];



// �������� ��������
digital                 diPrev, diCurr, diNext, diLast;



// ���������� ����������
combo32                 coEnergy;

// ������ ��������� ��� ���������� ���������� ������
bool                    mpboChannelsA[bCHANNELS];

// ������������� �������
ulong                   mpdwChannelsA[bCHANNELS],
                        mpdwChannelsB[bCHANNELS];

// ������������� ������
double                  mpdbChannelsC[bCHANNELS];

// ������������� ����������
time                    tiChannelC;



// ����� ���������� ������ ������������ � ����������� ��������
bool                    boEnblCurrent, boEnblProfile;

// �������� ������ ������ ������������ � ����������� ��������
uchar                   bTimeoutCurrent, bTimeoutProfile;

// ���� ����������� ������ ���������� ������� ������ ��������� ��������
bool                    boSeparateCan;

// ���� ������ ���������� ��� ������������/��������������
bool                    boShowMessages;

// ���� ������������ ������ ���������
bool                    boHideMessages;

// ���� ��������� ������� �������� ���������
bool                    boControlTime;

// ���� ��������� ������� ��������� ���������
bool                    boManageTime;



// ������ ��������� ��� ���������� ���������� ������ �������, ������������� ������ ��������� ��������
uchar                   mpboReadyCan[bCANALS];



// �������� �������
uint                    mpcwFailure2[bCANALS];



// ������� ������� � �������� ��������-230
uchar                   bKeysLevelB;

// ���� ������ �������� �������� ��-301 (x6 - false, x1 - true)
bool                    boShortProfileC;

// ���� ��������� ������� ��������� ���������� CE304
bool                    boControlQ;

// ���� ��������� ������� ��������� ���������� ��3850�
bool                    boControlK;

// �������
bool                    boPlcUFlag;

// ������
uchar                   bPlcUSize;

// ������
uint                    wPlcUShutdown;

// ���� ��������� ������� ��������� Rovalant ���-3
bool                    boControlW;



// ������ ������ �� ������� �� ����� ������ �������� ���������
bool                    fDsblAnswer;

// �������
bool                    fEnblAnswerCurr;

// �������
ulong                   cdwAnswerDisabled, cdwAnswerEnabled;

// �����/����
time                    tiAnswerDisabled, tiAnswerEnabled;

