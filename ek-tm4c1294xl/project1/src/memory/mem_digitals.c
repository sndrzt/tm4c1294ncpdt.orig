/*------------------------------------------------------------------------------
MEM_DIGITALS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������� ����� ������������ �������� ���������
uint                    wDigitalsMask;

// ������ ����������� �������
boolean                 mpboEnblCan[bCANALS];



// ���� ������������� ������� ���������
boolean                 boEnableKeys;

// ������ ������� ���������
phone                   mpphKeys[bCANALS];



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

// ���� ������������ ������ ���������
boolean                 boHideMessages;



// ������ ��������� ��� ���������� ���������� ������ �������, ������������� ������ ��������� ��������
uchar                   mpboReadyCan[bCANALS];



// ������ ������� ���������
phone                   mpphPhones[bCANALS];

// ������������ ����� �������� ������� Connect
uchar                   bMaxConnect;

// �������� ��� �������� ������ �������� �����
uint                    mpcwBaud[bPORTS],
                        mpcwCommon[bPORTS],
                        mpcwCustom[bPORTS],
                        mpcwConnect[bPORTS],
                        mpcwEscape[bPORTS],
                        mpcwHookOff[bPORTS],
                        mpcwDTROff[bPORTS];
