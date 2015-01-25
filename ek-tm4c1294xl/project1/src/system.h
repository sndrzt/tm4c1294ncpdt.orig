/*------------------------------------------------------------------------------
SYSTEM.H


------------------------------------------------------------------------------*/

#ifndef __SYSTEM
#define __SYSTEM


// ������� ���������� Timer0, ��
#define wFREQUENCY_T0   350

// ������� ���������� Timer1, ��
#define wFREQUENCY_T1   1


// ����� ��������� ������
#define bPACKET_HEADER  8
// ����� ��������� ������ ��� �������� ������ �� ���������
#define bHEADER         15


// ������ ��������� � �������� ������� ������
#define wOUTBUFF_SIZE   0x100
#define wINBUFF_SIZE    0x100


// ������� ���������� Timer0, ��
#define wFREQUENCY_T0   350


// ������������ ����� ����� ��������� �������� �������� � ������� ������� 'AT'
#define bANSWER_AT      10


// ���������� ������
#define bPORTS          4

// ���������� ���������
#define bSPEEDS         9

// ���������� ����� ��������
#define bPARITYS        5

// ���������� ������� ������
#define bSTREAMS        5


// ������ ������ ����������
#define bDISPLAY        16

// ������ ������ ��� ������ ������� �� ������������
#define bMARGIN         32


// ���������� �������
#define bTARIFFS        4

// ���������� ������� ��������� ��������� �������
#define bBREAKS         6

// ���������� ����� ������� � ����������� �� ��� ������ (����� ������� ������� �������)
#define bMODES          3

// ���������� ���������� �� ���
#define bRELAXS         40

// ���������� ������� ��� ������� �������� ��������
#define bGAPS           11


// �������� ������ �������
#define bMAXVERSION     4

// �������� ������ �������
#define bMINVERSION     18


// ���������� �������
#define bCANALS         64

// ���������� �����
#define bGROUPS         32

// ���������� ����� �������� ���������
#define bDEVICES        0


// ������ ����������� ��������
#define bMINUTES        40

// ������ ����������� ��������
#define wHOURS          (uint)(10*48)

// ������ �������� ��������
#define bDAYS           14

// ������ �������� �������� (����������� 12 !)
#define bMONTHS         12


#endif
