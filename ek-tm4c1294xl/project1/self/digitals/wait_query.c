/*------------------------------------------------------------------------------
WAIT_QUERY.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������� ������ ����� ���������� ������� � ��������� ��������
uchar                   cbWaitQuery;



void    InitWaitQuery(void)
{
  cbWaitQuery = 0;
}


void    WaitQuery_1Hz(void)
{
  if (cbWaitQuery > 0) cbWaitQuery--;
}
