/*------------------------------------------------------------------------------
automatic38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../sensors/automatic1.h"
#include "automatic38.h"



bool    Automatic38(void)
{
  Clear();

  dbKpulse = 10000         ;            // K ��������������
  dbKtrans = 1;                         // K �������������
  SetAllFactors(dbKpulse,dbKtrans);     // ���������� � �������������� � � �������������

  return true;
}
