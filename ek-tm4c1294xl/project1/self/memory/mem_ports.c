/*------------------------------------------------------------------------------
MEM_PORTS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������ ������
port                    mppoPorts[bPORTS];

// ������� �������� �������� �� ����
uint                    mpwInDelay[bPORTS];

// ��������� �������� �������� �� ���� (���������� � �����������)
uint                    mpwMinorInDelay[bPORTS], mpwMajorInDelay[bPORTS];

// ������ ��������� ����� ������ ������
bool                    mpboLocal[bPORTS];

// ����� ���������� ��������� ����� ������
bool                    mpboLocalDisable[bPORTS];

// ����������� ������ ��������� �������
uchar                   mpbCorrectLimit[bPORTS];

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
                        bInBuffA,
                        bInBuffB,
                        bInBuffC,
                        bInBuffD,
                        bInBuffE,
                        bInBuffF;

// ������� ������
uchar                   bQuery;

// ������������� ����
uchar                   ibPortActive;



// ������ ��� ������� � ������ � ������ �����
uint                    iwPopSave;

// ������ �� ������
uint                    iwInBuffSave;

// ������� �� ������
uint                    cwInBuffSave;

// ������������� �����
uchar                   mpbInBuffSave[wINBUFF_SIZE];



// ������� ��������� ��������
uchar                   cbHeaderBcc;

// ������� �������� ����
uint                    cwInBuffBcc;
