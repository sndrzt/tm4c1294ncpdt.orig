/*------------------------------------------------------------------------------
input_wrapper.c

����� ��� ��������� ������ �� ���������������� ������
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../digitals/skip_failure.h"
#include "input_wrapper.h"



void    InputStart(void)
{
  SkipFailure_InputStart();
}


void    InputGoodCheck(void)
{
  SkipFailure_InputGoodCheck();
}
