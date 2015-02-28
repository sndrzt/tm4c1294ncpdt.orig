/*------------------------------------------------------------------------------
MAIN_STORAGE.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_STORAGE
#define __MAIN_STORAGE


// ��� '������ ������ � ������'
typedef enum
{
  FRM_DEFAULT           = 0,
  FRM_UINT              = 1,
  FRM_REAL              = 2,
  FRM_IMPULSE           = 3,
  FRM_MAX_POWER         = 4,
} format;


// ��� '����������� ������ ������"
typedef struct
{
  uint          wPage;
  void         *pbBuff;
  uint          wSize;
  format        foSelf;
} file;


#endif
