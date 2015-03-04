/*------------------------------------------------------------------------------
AT45.H

 AT45DB321B, SPI Mode 0
------------------------------------------------------------------------------*/

#include        "../include/flash.h"



#define NATIVE_FLASH


void    Init_SPIhandAT45DB321(void);
void    InitFlash(void);

boolean SafePageErase(void);
boolean SafePageRead(void);
boolean SafePageWrite(void);

uint    GetFlashStatus(void);
boolean GetFlashChecksum(void);
