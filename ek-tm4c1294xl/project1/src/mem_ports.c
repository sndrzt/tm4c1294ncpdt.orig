/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include        "main.h"



// ������ ������
port                    mppoPorts[bPORTS];

// ������ ��������� �������� 'AT'
uchar                   mpcbSendAT[bPORTS];

// ������ ��������� �������� 'AT'
answer                  mpanSendAT[bPORTS];

// ������� �������� �������� �� ����
uint                    mpwInDelay[bPORTS];

// ��������� �������� �������� �� ���� (���������� � �����������)
uint                    mpwMinInDelay[bPORTS], mpwMajInDelay[bPORTS];

// ������ ��������� ����� ������ ������
boolean                 mpboLocal[bPORTS];
