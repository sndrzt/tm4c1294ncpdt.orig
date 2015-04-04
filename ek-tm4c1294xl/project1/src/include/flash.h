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
#define REALCAN_PAGES   (uchar)(sizeof(real)    * bCANALS/wFREEPAGE_SIZE + 1)


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

  FLS_DECRET            = FLS_GAPS + sizeof(gaps)/wFREEPAGE_SIZE + 1,

  FLS_TRANS_ENG         = FLS_DECRET + 1,
  FLS_TRANS_CNT         = FLS_TRANS_ENG + REALCAN_PAGES,
  FLS_PULSE_HOU         = FLS_TRANS_CNT + REALCAN_PAGES,
  FLS_PULSE_MNT         = FLS_PULSE_HOU + REALCAN_PAGES,

  FLS_COUNT             = FLS_PULSE_MNT + REALCAN_PAGES,
  FLS_LOSSE             = FLS_COUNT + REALCAN_PAGES,
  FLS_LEVEL             = FLS_LOSSE + REALCAN_PAGES,

  FLS_IMPMNTCAN         = FLS_LEVEL + REALCAN_PAGES,
  FLS_IMPHOUCAN         = FLS_IMPMNTCAN + bMINUTES,

  FLS_IMPDAYCAN         = FLS_IMPHOUCAN + IMPHOUCAN_PAGES,
  FLS_IMPMONCAN         = FLS_IMPDAYCAN + bIMPULSE_CAN*bDAYS,
  FLS_POWDAYGRP         = FLS_IMPMONCAN + bIMPULSE_CAN*bMONTHS,
  FLS_POWMONGRP         = FLS_POWDAYGRP + bPOWER_GRP*bDAYS,
  FLS_CNTMONCAN         = FLS_POWMONGRP + bPOWER_GRP*bMONTHS,

  FLS_DEFDAYCAN         = FLS_CNTMONCAN + REALCAN_PAGES*bMONTHS,
  FLS_DEFMONCAN         = FLS_DEFDAYCAN + bIMPULSE_CAN*bDAYS,

  FLS_IMPHOUCAN_BUFF    = FLS_DEFMONCAN + bIMPULSE_CAN*bMONTHS,
  FLS_IMPDAYCAN_BUFF    = FLS_IMPHOUCAN_BUFF + 1,
  FLS_IMPMONCAN_BUFF    = FLS_IMPDAYCAN_BUFF + bIMPULSE_CAN,
  FLS_IMPABSCAN_BUFF    = FLS_IMPMONCAN_BUFF + bIMPULSE_CAN,
  FLS_POWDAYGRP_BUFF    = FLS_IMPABSCAN_BUFF + bIMPULSE_CAN,
  FLS_POWMONGRP_BUFF    = FLS_POWDAYGRP_BUFF + bPOWER_GRP,
  FLS_CNTMONCAN_BUFF    = FLS_POWMONGRP_BUFF + bPOWER_GRP,

  FLS_PTRMNT            = FLS_CNTMONCAN_BUFF + REALCAN_PAGES,
  FLS_PTRHOU            = FLS_PTRMNT + 1,
  FLS_PTRDAY            = FLS_PTRHOU + 1,
  FLS_PTRMON            = FLS_PTRDAY + 1,

  FLS_REALTIME          = FLS_PTRMON + 1,

  FLS_SEPARATE_CAN      = FLS_REALTIME + 1,
  FLS_SHOW_MESSAGES     = FLS_SEPARATE_CAN + 1,
  FLS_HIDE_MESSAGES     = FLS_SHOW_MESSAGES + 1,
  FLS_CONTROL_TIME      = FLS_HIDE_MESSAGES + 1,
  FLS_MANAGE_TIME       = FLS_CONTROL_TIME + 1,
  FLS_FIRST_RESET       = FLS_MANAGE_TIME + 1,

  FLS_PORTS             = FLS_FIRST_RESET + 1,
  FLS_LOCAL_DISABLE     = FLS_PORTS + 1,

  FLS_MAJOR_IN_DELAY    = FLS_LOCAL_DISABLE + 1,
  FLS_MINOR_IN_DELAY    = FLS_MAJOR_IN_DELAY + 1,

  FLS_DIGITALS          = FLS_MINOR_IN_DELAY + 1,

  FLS_ENBL_CAN          = FLS_DIGITALS + sizeof(mpdiDigital)/wFREEPAGE_SIZE + 1,

  FLS_ENBL_PRT_HOU      = FLS_ENBL_CAN + 1,
  FLS_CTRL_HOU          = FLS_ENBL_PRT_HOU + 1,
  FLS_RECALC_HOU        = FLS_CTRL_HOU + 1,
  FLS_RECALC_ALWAYS     = FLS_RECALC_HOU + 1,

  FLS_ENBL_CURRENT      = FLS_RECALC_ALWAYS + 1,
  FLS_ENBL_PROFILE      = FLS_ENBL_CURRENT + 1,
  FLS_TIMEOUT_CURRENT   = FLS_ENBL_PROFILE + 1,
  FLS_TIMEOUT_PROFILE   = FLS_TIMEOUT_CURRENT + 1,

  FLS_PHONES            = FLS_TIMEOUT_PROFILE + 1,
  FLS_MAX_CONNECT       = FLS_PHONES + sizeof(mpphPhones)/wFREEPAGE_SIZE + 1,
  FLS_CUSTOM_MODEM      = FLS_MAX_CONNECT + 1,

  FLS_ENBL_KEYS         = FLS_CUSTOM_MODEM + 1,
  FLS_KEYS              = FLS_ENBL_KEYS + 1,

  FLS_ADDRESS1          = FLS_KEYS + sizeof(mpphKeys)/wFREEPAGE_SIZE + 1,
  FLS_ADDRESS2          = FLS_ADDRESS1 + sizeof(mpdwAddress1)/wFREEPAGE_SIZE + 1,

  FLS_MAX_REPEATS       = FLS_ADDRESS2 + sizeof(mpdwAddress2)/wFREEPAGE_SIZE + 1,

  FLS_OBJECT_NAME       = FLS_MAX_REPEATS + 1,
  FLS_CANALS_NAME       = FLS_OBJECT_NAME + 1,
  FLS_GROUPS_NAME       = FLS_CANALS_NAME + sizeof(mpszCanalsName)/wFREEPAGE_SIZE + 1,

  FLS_STRICT_UNI        = FLS_GROUPS_NAME + sizeof(mpszGroupsName)/wFREEPAGE_SIZE + 1,
  FLS_MAX_DELAY_UNI     = FLS_STRICT_UNI + 1,
  FLS_REPEAT_FLOW_INI   = FLS_MAX_DELAY_UNI + 1,
  FLS_DSBL_PASSWORD_INI = FLS_REPEAT_FLOW_INI + 1,

  FLS_USE_BOUNDS        = FLS_DSBL_PASSWORD_INI + 1,
  FLS_START_REL_CAN     = FLS_USE_BOUNDS + 1,
  FLS_START_ABS16_CAN   = FLS_START_REL_CAN + 1,
  FLS_START_ABS32_CAN   = FLS_START_ABS16_CAN + 1,
  FLS_START_CAN         = FLS_START_ABS32_CAN + 1,
  FLS_STOP_CAN          = FLS_START_CAN + 1,
  FLS_STOP_AUX_CAN      = FLS_STOP_CAN + 1,

  FLS_DSBL_REFILL       = FLS_STOP_AUX_CAN + 1,
  FLS_ENBL_CURRENT2     = FLS_DSBL_REFILL + 1,

  FLS_DSBL_ESC_U        = FLS_ENBL_CURRENT2 + 1,
  FLS_DSBL_ESC_V        = FLS_DSBL_ESC_U + 1,
  FLS_DSBL_ESC_S        = FLS_DSBL_ESC_V + 1,
  FLS_MNT_ESC_S         = FLS_DSBL_ESC_S + 1,
  FLS_EXTENDED_ESC_U    = FLS_MNT_ESC_S + 1,
  FLS_EXTENDED_ESC_V    = FLS_EXTENDED_ESC_U + 1,
  FLS_EXTENDED_ESC_S    = FLS_EXTENDED_ESC_V + 1,

  FLS_FLOW_PORT_FROM    = FLS_EXTENDED_ESC_S + 1,
  FLS_MAX_FLOW_DELAY    = FLS_FLOW_PORT_FROM + 1,
  FLS_FLOW_PORT_TO      = FLS_MAX_FLOW_DELAY + 1,

  FLS_ENBL_PARAMS       = FLS_FLOW_PORT_TO + 1,
  FLS_MNT_PARAMS        = FLS_ENBL_PARAMS + 1,
  FLS_PARAMS            = FLS_MNT_PARAMS + 1,

  FLS_END               = FLS_PARAMS + sizeof(mpdiParam)/wFREEPAGE_SIZE + 1
} flash;



#endif
