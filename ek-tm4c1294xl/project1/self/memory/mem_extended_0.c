/*------------------------------------------------------------------------------
MEM_EXTENDED_0,C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������
bool                    fExt0Flag;

// ���������� ��������: ��������� � ������������
uchar                   bExt0Limit, bExt0Counter;

// ������ ��������
ulong                   mpdwExt0RepeatsPH[bPORTS][48];

// ������ ������
ulong                   mpdwExt0ErrorsPH[bPORTS][48];
