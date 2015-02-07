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
} zones;


// ��� '��������/�������'
typedef enum
{
  DOM_POWER,
  DOM_ENERGY
} domain;


// ��� '������ ������� �������'
typedef enum
{
  PER_INIT              = 0,
  PER_MONTH             = 1,
  PER_QUARTER           = '-',
  PER_YEAR              = '_',
} period;


// ��� '������ ����������'
typedef struct
{
  uchar         bSize;                  // ���������� ����������
  time          mptiDate[bRELAXS];      // ���� ����������
} relaxs;


// ��� '����� ��������� �������'
typedef struct
{
  uchar         bSize;                  // ���������� �������
  time          mptiDate[bGAPS]  ;      // ���� ������� (������� - ����� ������-������)
} gaps;
