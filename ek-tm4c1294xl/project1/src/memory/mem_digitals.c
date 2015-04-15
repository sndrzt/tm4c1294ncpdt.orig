/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������� ����� ������������ �������� ���������
uint                    wDigitalsMask;

// ������ ����������� �������
boolean                 mpboEnblCan[bCANALS];



// ���� ������������� ������� ���������
boolean                 boEnblKeys;

// ������ ������� ���������
phone                   mpphKeys[bCANALS];

// �������������� ��������� �������� ���������
ulong                   mpdwAddress1[bCANALS],
                        mpdwAddress2[bCANALS];



// �������� ��������
digital                 diPrev, diCurr, diNext, diLast;



// ���������� ����������
combo32                 coEnergy;

// ������ ��������� ��� ���������� ���������� ������
boolean                 mpboChannelsA[bCHANNELS];

// ������������� �������
ulong                   mpdwChannelsA[bCHANNELS],
                        mpdwChannelsB[bCHANNELS];

// ������������� �������
real                    mpreChannelsA[bCHANNELS],
                        mpreChannelsB[bCHANNELS];

// ������������� ����������
time                    tiChannelC;



// ����� ���������� ������ ������������ � ����������� ��������
boolean                 boEnblCurrent, boEnblProfile;

// �������� ������ ������ ������������ � ����������� ��������
uchar                   bTimeoutCurrent, bTimeoutProfile;

// ���� ����������� ������ ���������� ������� ������ ��������� ��������
boolean                 boSeparateCan;

// ���� ������ ���������� ��� ������������/��������������
boolean                 boShowMessages;

// ���� ������������ ������ ���������
boolean                 boHideMessages;

// ���� ��������� ������� �������� ���������
boolean                 boControlTime;

// ���� ��������� ������� ��������� ���������
boolean                 boManageTime;



// ������ ��������� ��� ���������� ���������� ������ �������, ������������� ������ ��������� ��������
uchar                   mpboReadyCan[bCANALS];



// �������� �������
uint                    mpcwFailure2[bCANALS];



// ������� ������� � �������� ��������-230
uchar                   bKeysLevelB;

// ���� ������ �������� �������� ��-301 (x6 - false, x1 - true)
boolean                 boShortProfileC;

// ����
boolean                 boDirectCntD;
