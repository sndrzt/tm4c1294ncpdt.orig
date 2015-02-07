#include        "main_basic.h"



// ��� '����� ��������� �������'
typedef struct
{
  uchar         bHour;                  // ���
  uchar         bMinute;                // ������
  uchar         ibTariff;               // ������ ������
} br3ak;


// ��� '�������� ������ �� �����'
typedef struct
{
  uchar         bSize;                  // ���������� ������� � �������� �������
  br3ak         mpbrBreaks[bBREAKS];    // ������ ��������� �������
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
