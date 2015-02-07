#include        "main_basic.h"



// ��� '����� ��������� �������'
typedef struct
{
  uchar         bHour;                  // ���
  uchar         bMinute;                // ������
  uchar         ibTariff;               // ������ ������
} breaks;


// ��� '�������� ������ �� �����'
typedef struct
{
  uchar         bSize;                  // ���������� ������� � �������� �������
  breaks        mpbrBreaks[bBREAKS];    // ������ ��������� �������
} zone;


// ��� '��������/�������'
typedef enum
{
  POWER,
  ENERGY
} domain;


// ��� '������ ������� �������'
typedef enum
{
  NONE          = 0,
  MONTH         = 1,
  QUARTER       = '-',
  YEAR          = '_',
} period;


// ��� '������ ����������'
typedef struct
{
  uchar         bSize;                  // ���������� ����������
  time          mptiDate[bRELAXS];      // ���� ����������
} relax;


// ��� '����������� �������� �������'
typedef struct
{
  uchar         bSize;                  // ���������� ��������
  time          mptiDate[bGAPS];        // ���� �������� (������� - ����� ������-������)
} gap;
