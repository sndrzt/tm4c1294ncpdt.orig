#include        "main_basic.h"



// ��� '�������� ��������'
typedef struct
{
  time          tiNow;                  // �����/����
  real          rePow;                  // �������� ��������� ��������
} maximum;


// ��� '�������� �������� �� �������'
typedef struct
{
  maximum       mpmaMax[bTARIFFS];
} power;


// ��� '���������� ��������� �� �������'
typedef struct
{
  ulong         mpdwImp[bTARIFFS];
} impulse;
