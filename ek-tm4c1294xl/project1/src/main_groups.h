#include        "main_basic.h"



// ��� '���� ������'
typedef struct
{
  uchar         ibCanal;                // ������ ������
} node;


// ��� '������'
typedef struct
{
  uchar         bSize;                  // ���������� ����� � ������
  node          mpnoNodes[bCANALS];     // ���� ������
} group;
