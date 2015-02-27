/*------------------------------------------------------------------------------
FLASH.H

 ��������� ����-������
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH


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
#define bIMPULSE_CAN    (uchar)(sizeof(impulse) * bCANALS/wFREEPAGE_SIZE + 1)
#define bPOWER_GRP      (uchar)(sizeof(power)   * bGROUPS/wFREEPAGE_SIZE + 1)
#define bREAL_CAN       (uchar)(sizeof(real)    * bCANALS/wFREEPAGE_SIZE + 1)


// ���������� ������� ��� ������� �������� �� ���������
#ifdef  DAYS100

#define IMPHOUCAN_PAGES (uint)(wHOURS/4)

#else

#define IMPHOUCAN_PAGES (uint)(wHOURS/1)
#define UINTCAN_PAGES   (uchar)(sizeof(uint)    * bCANALS/wFREEPAGE_SIZE + 1)

#endif


// ������ ������ ������
typedef enum
{
  FLS_BEGIN             = 0,

  FLS_PRIVATE           = FLS_BEGIN,
  FLS_GLOBAL            = FLS_PRIVATE + 1,
  FLS_LOGICAL           = FLS_GLOBAL + 1,

  FLS_GROUPS            = FLS_LOGICAL + 1,

  FLS_PUBLIC_TARIFFS    = FLS_GROUPS + sizeof(group)*bGROUPS/wFREEPAGE_SIZE + 1,
  FLS_TARIFFS_MODE      = FLS_PUBLIC_TARIFFS + 1,

  FLS_DAY_ZONE          = FLS_TARIFFS_MODE + 1,

  FLS_ZONES_POW         = FLS_DAY_ZONE + 1,
  FLS_ZONES_ENG         = FLS_ZONES_POW + 12*bMODES,

  FLS_PERIOD_POW        = FLS_ZONES_ENG + 12*bMODES,
  FLS_PERIOD_ENG        = FLS_PERIOD_POW + 1,

  FLS_RELAXS_FLAG       = FLS_PERIOD_ENG + 1,
  FLS_RELAXS_TARIFF     = FLS_RELAXS_FLAG + 1,
  FLS_RELAXS            = FLS_RELAXS_TARIFF + 1,

  FLS_GAPS_FLAG         = FLS_RELAXS + sizeof(relaxs)/wFREEPAGE_SIZE + 1,
  FLS_GAPS              = FLS_GAPS_FLAG + 1,

  FLS_TRANS_ENG         = FLS_GAPS + sizeof(gaps)/wFREEPAGE_SIZE + 1,
  FLS_TRANS_CNT         = FLS_TRANS_ENG + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  FLS_PULSE_HOU         = FLS_TRANS_CNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  FLS_PULSE_MNT         = FLS_PULSE_HOU + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,

  FLS_COUNT             = FLS_PULSE_MNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  FLS_LOSSE             = FLS_COUNT + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,
  FLS_LEVEL             = FLS_LOSSE + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,

  FLS_DIGITALS          = FLS_LEVEL + sizeof(real)*bCANALS/wFREEPAGE_SIZE + 1,

  FLS_IMPHOUCAN         = FLS_DIGITALS + sizeof(digital)*bCANALS/wFREEPAGE_SIZE + 1,
  FLS_IMPDAYCAN         = FLS_IMPHOUCAN + IMPHOUCAN_PAGES,
  FLS_IMPMONCAN         = FLS_IMPDAYCAN + bIMPULSE_CAN*bDAYS,
  FLS_POWDAYGRP         = FLS_IMPMONCAN + bIMPULSE_CAN*bMONTHS,
  FLS_POWMONGRP         = FLS_POWDAYGRP + bPOWER_GRP*bDAYS,
  FLS_CNTMONCAN         = FLS_POWMONGRP + bPOWER_GRP*bMONTHS,

  FLS_IMPHOUCAN_BUFF    = FLS_CNTMONCAN + bREAL_CAN*bMONTHS,
  FLS_IMPDAYCAN_BUFF    = FLS_IMPHOUCAN_BUFF + 1,
  FLS_IMPMONCAN_BUFF    = FLS_IMPDAYCAN_BUFF + bIMPULSE_CAN,
  FLS_IMPABSCAN_BUFF    = FLS_IMPMONCAN_BUFF + bIMPULSE_CAN,
  FLS_POWDAYGRP_BUFF    = FLS_IMPABSCAN_BUFF + bIMPULSE_CAN,
  FLS_POWMONGRP_BUFF    = FLS_POWDAYGRP_BUFF + bPOWER_GRP,
  FLS_CNTMONCAN_BUFF    = FLS_POWMONGRP_BUFF + bPOWER_GRP,

  FLS_PTRMNT            = FLS_CNTMONCAN_BUFF + bREAL_CAN,
  FLS_PTRHOU            = FLS_PTRMNT + 1,
  FLS_PTRDAY            = FLS_PTRHOU + 1,
  FLS_PTRMON            = FLS_PTRDAY + 1,
  FLS_TICURR            = FLS_PTRMON + 1,

  FLS_END               = FLS_TICURR + 1
} flash;



#endif
