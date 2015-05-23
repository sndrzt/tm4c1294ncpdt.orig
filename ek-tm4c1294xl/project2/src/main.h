/*------------------------------------------------------------------------------
MAIN,H


------------------------------------------------------------------------------*/

#ifndef __MAIN
#define __MAIN


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "driverlib/debug.h"
#include "system.h"
#include "main_keyboard.h"
#include "kernel/boolean.h"
#include "kernel/float.h"


// ��� '������� �������� �� �������� �����'
typedef enum
{
  DEC_NONE              = 0,
  DEC_AUTO              = 1,
  DEC_CUSTOM            = 2
} decret;


// ��� '����� ������ �������'
typedef enum
{
  GLB_PROGRAM           = 0,
  GLB_WORK              = 1,
  GLB_REPROGRAM         = 2
} global;


#endif






