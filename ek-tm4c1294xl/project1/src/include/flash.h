/*------------------------------------------------------------------------------
FLASH.H

 ��������� ����-������
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH

#include "../memory/mem_digitals.h"
#include "../memory/mem_params0.h"
#include "../memory/mem_params.h"
#include "../memory/mem_phones.h"
#include "../memory/mem_uni.h"
#include "../memory/mem_extended_4.h"
#include "../memory/mem_extended_4t.h"
#include "../memory/mem_extended_5.h"
#include "../memory/mem_extended_6.h"
#include "../memory/mem_correct1.h"



// ������ ��������
#define wPAGE_BYTES     528

// ������ ��������, ��������� ��� ������ ������ ������������
#define wFREE_BYTES     512

// ���������� �������
#define wPAGES          8192


// ���������� �������� ��� ������ �������� ��������� (TODO: use milliseconds)
#define wREAD_STATUS    50000

// ���������� �������� ��� ������/������ ��������
#define bMAXREPEAT      8


// ���������� ������� �� ���� ������ ������������ ���� (TODO rename IMPCAN_PAGES etc.)
#define UINTCAN_PAGES       (uchar)(sizeof(uint)    * bCANALS/wFREE_BYTES + 1)
#define bIMPULSE_CAN        (uchar)(sizeof(impulse) * bCANALS/wFREE_BYTES + 1)
#define bPOWER_GRP          (uchar)(sizeof(power)   * bGROUPS/wFREE_BYTES + 1)
#define FLOAT_CAN_PAGES     (uchar)(sizeof(float)   * bCANALS/wFREE_BYTES + 1)
#define DOUBLE_CAN_PAGES    (uchar)(sizeof(double)  * bCANALS/wFREE_BYTES + 1)
#define PARAMS_PAGES        (uchar)(sizeof(real)    * wPARAMS/wFREE_BYTES + 1)
#define VALUE4_CAN_PAGES    (uchar)(sizeof(mpCntMonCan4)/wFREE_BYTES + 1)
#define VALUE4T_CAN_PAGES   (uchar)(sizeof(mpCntMonCan4T)/wFREE_BYTES + 1)
#define VALUE5_CAN_PAGES    (uchar)(sizeof(mpCntDayCan5)/wFREE_BYTES + 1)
#define VALUE6_CAN_PAGES    (uchar)(sizeof(mpCntMonCan6)/wFREE_BYTES + 1)
#define VALUE7_CAN_PAGES    (uchar)(sizeof(mpCntDayCan7)/wFREE_BYTES + 1)


// ���������� ������� ��� ������� �������� �� ���������
#ifdef  DAYS100

#define IMPHOUCAN_PAGES     (uint)(wHOURS/4)

#else

#define IMPHOUCAN_PAGES     (uint)(wHOURS/1)

#endif


#include "flash_enum.txt"


#endif
