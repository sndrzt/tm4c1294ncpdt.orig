/*------------------------------------------------------------------------------
MEM_EXTENDED_4.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ���� ���������� ������
bool                    fExt4Flag;

// ������� ������ � �������
uchar                   bExt4Months;

// ������ ����������� �������
bool                    mpfExt4EnblCan[bCANALS];

// ����� �������� ��������� �� ������ 12 �������
value6                  mpCntMonCan4[bCANALS];

// ������� ��������� ����� ����� � �����
uint                    cwDayCan4, cwMonCan4;
