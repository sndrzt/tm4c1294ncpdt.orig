/*------------------------------------------------------------------------------
MAIN_ENERGY.H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// ��� '�����/���� + ��������'
typedef struct
{
  time          tiSelf;                 // �����/����
  real          reSelf;                 // ��������
} value;


// ��� '�������� �������� �� �������'
typedef struct
{
  value         mpmaMax[bTARIFFS];
} power;


// ��� '���������� ��������� �� �������'
typedef struct
{
  ulong         mpdwImp[bTARIFFS];
} impulse;
