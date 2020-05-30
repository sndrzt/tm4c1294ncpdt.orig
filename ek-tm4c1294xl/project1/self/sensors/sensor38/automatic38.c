/*------------------------------------------------------------------------------
automatic38.c


------------------------------------------------------------------------------*/

#include "../../main.h"
//#include "../../memory/mem_factors.h"
#include "../../display/display.h"
//#include "../../keyboard/keyboard.h"
//#include "../../time/timedate.h"
//#include "../../serial/ports.h"
//#include "../../devices/devices.h"
#include "../../sensors/automatic1.h"
//#include "../../digitals/digitals.h"
//#include "device38.h"
//#include "io38.h"
#include "automatic38.h"



bool    Automatic38(void)
{
  Clear();

  dbKpulse = 10000         ;            // K ��������������
  dbKtrans = 1;                         // K �������������
  SetAllFactors(dbKpulse,dbKtrans);     // ���������� � �������������� � � �������������

  return true;
}
