/*------------------------------------------------------------------------------
OUT_NVRAM_STACK,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../include/nvram.h"
#include "out_nvram_stack.h"



void    OutNvramStack(void)
{
  InitPushCRC();

  uint i;
  for (i=0; i<3000; i++) PushChar(0);

  InitPushCRC();

  PUSH_ENUM(dwNVRAM_BYTES)

  PushChar(0x0D); PushChar(0x0A);

  #include "../include/out_nvram.txt"

  Output(3000);
}
