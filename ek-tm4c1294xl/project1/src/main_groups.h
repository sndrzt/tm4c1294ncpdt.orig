#include        "main_basic.h"



// ��� '���� ������'
typedef struct
{
  uchar         ibCanal;                // ������ ������
} nodes;


// ��� '������'
typedef struct
{
  uchar         bSize;                  // ���������� ����� � ������
  nodes         mpnoNodes[bCANALS];     // ���� ������
} groups;
