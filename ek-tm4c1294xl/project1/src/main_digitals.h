#include        "main_basic.h"



// ��� '�������� �������'
typedef struct
{
  uchar         ibPort;                 // ������ �����
  uchar         ibPhone;                // ������ ��������
  uchar         bDevice;                // ��� ������������ ��������
  uchar         bAddress;               // ���������� �����
  uchar         ibLine;                 // ��� �������
} digital;



// ��� '��������'
typedef struct
{
  uchar         szNumber[bPHONENUMBER+1];
} phone;
