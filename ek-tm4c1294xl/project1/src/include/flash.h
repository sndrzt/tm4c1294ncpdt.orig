/*------------------------------------------------------------------------------
FLASH.H

 ��������� ����-������
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH

#include        "../memory/mem_digitals0.h"
#include        "../memory/mem_digitals.h"
#include        "../memory/mem_params.h"
#include        "../memory/mem_phones.h"
#include        "../memory/mem_uni.h"
#include        "../memory/mem_extended_4.h"
#include        "../memory/mem_extended_4t.h"
#include        "../memory/mem_extended_5.h"
#include        "../memory/mem_extended_6.h"
#include        "../memory/mem_extended_7.h"



// ������ ��������
#define wPAGE_SIZE      528

// ������ ��������, ��������� ��� ������ ������ ������������
#define wFREEPAGE_SIZE  512

// ���������� �������
#define wPAGES          8192


// ���������� �������� ��� ������ �������� ��������� (TODO: use milliseconds)
#define wREAD_STATUS    50000

// ���������� �������� ��� ������/������ ��������
#define bMAXREPEAT      8


// ���������� ������� �� ���� ������ ������������ ���� (TODO rename IMPCAN_PAGES etc.)
#define bIMPULSE_CAN        (uchar)(sizeof(impulse) * bCANALS/wFREEPAGE_SIZE + 1)
#define bPOWER_GRP          (uchar)(sizeof(power)   * bGROUPS/wFREEPAGE_SIZE + 1)
#define REALCAN_PAGES       (uchar)(sizeof(real)    * bCANALS/wFREEPAGE_SIZE + 1)
#define PARAMS_PAGES        (uchar)(sizeof(real)    * wPARAMS/wFREEPAGE_SIZE + 1)
#define VALUE5_CAN_PAGES    (uchar)(sizeof(mpvaValue5)/wFREEPAGE_SIZE + 1)
#define VALUE6_CAN_PAGES    (uchar)(sizeof(mpCntMonCan4)/wFREEPAGE_SIZE + 1)
#define VALUE6T_CAN_PAGES   (uchar)(sizeof(mpCntMonCan4T)/wFREEPAGE_SIZE + 1)
#define VALUE7_CAN_PAGES    (uchar)(sizeof(mpCntDayCan7)/wFREEPAGE_SIZE + 1)


// ���������� ������� ��� ������� �������� �� ���������
#ifdef  DAYS100

#define IMPHOUCAN_PAGES     (uint)(wHOURS/4)

#else

#define IMPHOUCAN_PAGES     (uint)(wHOURS/1)
#define UINTCAN_PAGES       (uchar)(sizeof(uint)    * bCANALS/wFREEPAGE_SIZE + 1)

#endif


#include        "flash_enum.txt"


#endif
