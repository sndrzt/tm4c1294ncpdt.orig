/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include        "main.h"



// ������ ������
port                    mppoPorts[bPORTS];

// ���� �������� 'AT'
boolean     			boSendAT;

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

// ����������
uchar                   bInBuff0,
                        bInBuff1,
                        bInBuff2,
                        bInBuff3,
                        bInBuff4,
                        bInBuff5,
                        bInBuff6,
                        bInBuff7,
                        bInBuff8,
                        bInBuff9,
                        bInBuffA;

// ������� ������
uchar                   bQuery;

// ������������� ����
uchar                   ibPortActive;
