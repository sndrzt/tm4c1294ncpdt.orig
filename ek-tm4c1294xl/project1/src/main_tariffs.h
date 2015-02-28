/*------------------------------------------------------------------------------
MAIN_TARIFFS.H


------------------------------------------------------------------------------*/

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
} relaxs;


// ��� '����������� �������� �������'
typedef struct
{
  uchar         bSize;                  // ���������� ��������
  time          mptiDate[bGAPS];        // ���� �������� (������� - ����� ������-������)
} gaps;
