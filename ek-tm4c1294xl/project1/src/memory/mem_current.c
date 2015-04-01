/*------------------------------------------------------------------------------
MEM_CURRENT.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������ ������� ������� (� ���������)
ulong                   mpdwBase[bCANALS];

// ������ ������� ������� (� ��������� �������)
real                    mpreBase[bCANALS];

// ������ �������/���� ���������� ������� �������
time                    mptiBase[bCANALS];

// ������ ������ ��������� ������� �������
boolean                 mpboBase[bCANALS];

// ������ ��� �������� ������� �������� ���� ������� ������ ��������
ulong                   mpdwBaseDig[bCHANNELS];

// ������ �������/���� ���������
time                    mptiOffs[bCANALS];

// ���������� ����������
time                    tiOffs;

// ������� ��������������� ����������
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwOverflow[bCANALS],
                        mpwUnderflow[bCANALS],
                        mpwRepeat[bCANALS];



// ������� ��������������� ����������
uint                    mpwMore100[bCANALS],
                        mpwMore1000[bCANALS],
                        mpwMore10000[bCANALS];

// ������� ��������������� ����������
time                    mptiBaseOK[bCANALS],
                        mptiBaseError[bCANALS];



// ���� ������� �������
boolean                 boCurrent2;

// ������� ����� �������
uchar                   mpbCurrent2Curr[8],
                        mpbCurrent2Prev[8],
                        mpbCurrent2Buff[8];

// ���������� �����������
boolean                 boEnblCurrent2;

// �������� ���������� �����������
uint                    mpwCurrent2Mnt[bCANALS];

// �������� ������������
uint                    mpwCurrent2Overflow[bCANALS];
