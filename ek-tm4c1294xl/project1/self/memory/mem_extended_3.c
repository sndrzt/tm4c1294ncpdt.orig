/*------------------------------------------------------------------------------
MEM_EXTENDED_3,C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������ �������
bool                    fExt3Flag;

// ����� ���������� ������ �������
bool                    mpboEventFirst[bCANALS];

// ���� ���������� ����������� �������
bool                    mpboEventA[32],
                        mpboEventB[32];

// ������� �������
time                    mptiEventAB1[10],
                        mptiEventAB2[10];

// �������� ���� �������
ulong                   mpdwEventDevice[bCANALS],
                        mpdwEventPhase1[bCANALS],
                        mpdwEventPhase2[bCANALS],
                        mpdwEventPhase3[bCANALS];

// ������� ���� �������
ulong                   dwEventIndexCurr, dwEventIndexPrev;

// ��� ������
uchar                   bEventCode;
