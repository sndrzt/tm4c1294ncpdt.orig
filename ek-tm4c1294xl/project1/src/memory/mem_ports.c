/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������ ������
port                    mppoPorts[bPORTS];

// ������� �������� �������� �� ����
uint                    mpwInDelay[bPORTS];

// ��������� �������� �������� �� ���� (���������� � �����������)
uint                    mpwMinorInDelay[bPORTS], mpwMajorInDelay[bPORTS];

// ������ ��������� ����� ������ ������
boolean                 mpboLocal[bPORTS];

// ����� ���������� ��������� ����� ������
boolean                 mpboLocalDisable[bPORTS];

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
                        bInBuffA
                        bInBuffB,
                        bInBuffC,
                        bInBuffD,
                        bInBuffE,
                        bInBuffF;

// ������� ������
uchar                   bQuery;

// ������������� ����
uchar                   ibPortActive;
