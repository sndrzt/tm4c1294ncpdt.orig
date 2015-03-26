/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������� ����� ������������ �������� ���������
uint                    wDigitalsMask;

// ������ ����������� �������
boolean                 mpboEnblCan[bCANALS];

//  ������ ������ �������� ��������� �� ������ � ���������
boolean                 mpboEnblPrtHou[bPORTS][48];

//  ������ ��������� ������� �������� ��������� �� ���������
boolean                 mpboCtrlHou[48];



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
combo                   coEnergy;

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



// ������ ��������� ��� ���������� ���������� ������ �������, ������������� ������ ��������� ��������
uchar                   mpboReadyCan[bCANALS];



// �������� �������
uint                    mpcwFailure2[bCANALS];
