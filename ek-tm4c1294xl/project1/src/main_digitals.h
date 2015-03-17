/*------------------------------------------------------------------------------
MAIN_DIGITALS.H


------------------------------------------------------------------------------*/

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



// ��� '����� ��������'
typedef struct
{
  char          szNumber[bPHONENUMBER+1];
} phone;



// ��� '��� ������ ���������'
typedef enum
{
  EXT_PROFILE_30MIN,
  EXT_CURRENT_3MIN,
  EXT_PROFILE_CHECKUP
} extended;
