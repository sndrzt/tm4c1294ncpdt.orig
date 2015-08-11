/*------------------------------------------------------------------------------
MAIN_STORAGE,H


------------------------------------------------------------------------------*/

#ifndef __MAIN_STORAGE
#define __MAIN_STORAGE


// ����������� ������ ������ � FLASH
typedef struct
{
  uint          wPage;
  void         *pbBuff;
  uint          wSize;
} file;


// ����������� ������ ������ � NVRAM
typedef struct
{
  ulong         dwAddr;
  void         *pbBuff;
  uint          wSize;
} cache;


#endif
