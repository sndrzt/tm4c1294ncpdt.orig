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

// ������� ��������������� ����������
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwMore[bCANALS],
                        mpwLess[bCANALS],
                        mpwRepeat[bCANALS];



// ������� ��������������� ����������
uint                    mpwMore100[bCANALS],
                        mpwMore1000[bCANALS],
                        mpwMore10000[bCANALS];

// ������� ��������������� ����������
time                    mptiBaseOK[bCANALS],
                        mptiBaseError[bCANALS];
