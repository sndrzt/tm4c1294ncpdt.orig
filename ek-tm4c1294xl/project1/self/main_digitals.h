/*------------------------------------------------------------------------------
MAIN_DIGITALS,H


------------------------------------------------------------------------------*/

#include "main_basic.h"



// �������� �������
typedef struct
{
  uchar         ibPort;                 // ������ �����
  uchar         ibPhone;                // ������ ��������
  uchar         bDevice;                // ��� ������������ ��������
  uchar         bAddress;               // ���������� �����
  uchar         ibLine;                 // ��� �������
} digital;



// ������ ������
typedef struct
{
  char          szLine[bLINE_SIZE+1];
} line;



// ��� ������ ���������
typedef enum
{
  EXT_PROFILE_30MIN,
  EXT_CURRENT_3MIN,
  EXT_PROFILE_CHECKUP
} extended;



// ����� ������ �������� �������� ��������-230
typedef enum
{
  P2M_AUTOMATIC     = 0,
  P2M_SIZE_1        = 1,
  P2M_SIZE_16       = 2,
  P2M_SIZE_17       = 3,
  P2M_BY_DIGITAL    = 4
} profile2mode;
