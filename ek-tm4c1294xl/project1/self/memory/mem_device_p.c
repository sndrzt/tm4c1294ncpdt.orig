/*------------------------------------------------------------------------------
MEM_DEVICE_P.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������ ��� ����������� ������
uchar                   mpbPasswordEls[8], mpbRandomEls[16], mpbResultEls[16];

// ������
uchar                   mpbEls1[8], mpbEls2[16];

// ����� ��������
uchar                   mpbBuffEls[128];

// ����������
uchar                   pbPutEls, pbGetEls, cbSizeEls;

// ����������
uchar                   bFlagElsCurr, bFlagElsPrev;

// ����������
uchar                   bCodeElsCurr, bCodeElsPrev;

// ����������
ulong                   dwStampElsCurr, dwStampElsPrev;

// ����������
uchar                   bBreakEls, bFirstEls;

// ����������
uchar                   mpbMappingEls[4];

// ����������
float                   mpreChannelsEls[4];

// ������� �������� �������� �������
bool                    boTimeChangeP;

// ������ �������� �������� � ������ �������� �������� �������
ulong                   dwHouIndexP1, dwHouIndexP2;
