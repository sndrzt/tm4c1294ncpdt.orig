/*------------------------------------------------------------------------------
input.c

����� ��� ��������� ������ �� ���������������� ������
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/skip_failure.h"
#include "input.h"



void    InputStart(void)
{
  SkipFailure_Failure();
}


void    InputGoodCheck(void)
{
  SkipFailure_Success();
}
