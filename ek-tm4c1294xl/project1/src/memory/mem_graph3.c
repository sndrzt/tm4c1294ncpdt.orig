/*------------------------------------------------------------------------------
MEM_GRAPH3.C


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

// ������� ��������������� ����������
uint                    mpwTrue[bCANALS],
                        mpwFalse[bCANALS],
                        mpwMore[bCANALS],
                        mpwLess[bCANALS],
                        mpwRepeat[bCANALS];
