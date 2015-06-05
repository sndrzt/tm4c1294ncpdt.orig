/*------------------------------------------------------------------------------
OUT_FLASH_STACK,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../include/flash.h"
#include "out_flash_stack.h"



#define PUSH_ENUM(value) PushString(#value); PushString("="); PushIntAsString(value); PushChar(0x0D); PushChar(0x0A);



void    OutFlashStack(void)
{
  InitPushCRC();

  uint i;
  for (i=0; i<3000; i++) PushChar(0);

  InitPushCRC();

  PUSH_ENUM(UINTCAN_PAGES)
  PUSH_ENUM(IMPHOUCAN_PAGES)
  PUSH_ENUM(bIMPULSE_CAN)
  PUSH_ENUM(bPOWER_GRP)
  PUSH_ENUM(FLOAT_CAN_PAGES)
  PUSH_ENUM(DOUBLE_CAN_PAGES)
  PUSH_ENUM(PARAMS_PAGES)
  PUSH_ENUM(VALUE4_CAN_PAGES)
  PUSH_ENUM(VALUE4T_CAN_PAGES)
  PUSH_ENUM(VALUE5_CAN_PAGES)
  PUSH_ENUM(VALUE6_CAN_PAGES)
  PUSH_ENUM(VALUE7_CAN_PAGES)

  PushChar(0x0D); PushChar(0x0A);

  #include "../include/out_flash.txt"

  Output(3000);
}
