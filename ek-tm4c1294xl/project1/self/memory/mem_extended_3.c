/*------------------------------------------------------------------------------
MEM_EXTENDED_3,C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������ �������
bool                    fExt3Flag;

// ����� ���������� ������ �������
bool                    mpfEventFirst[bCANALS];

// ���� ���������� ����������� �������
bool                    mpfEventA[32],
                        mpfEventB[32];

// ������� �������
time                    mptiEventAB1[10],
                        mptiEventAB2[10];

// �������� ���� �������
ulong                   mpdwEventDevice[bCANALS],
                        mpdwEventPhase1[bCANALS],
                        mpdwEventPhase2[bCANALS],
                        mpdwEventPhase3[bCANALS];

// ��� ������
uchar                   bEventCode;
