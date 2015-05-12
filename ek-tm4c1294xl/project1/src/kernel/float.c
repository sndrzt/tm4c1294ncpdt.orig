/*------------------------------------------------------------------------------
FLOAT,�


------------------------------------------------------------------------------*/

#include "../main.h"
#include "float.h"



bool    IsNAN(float  fl)
{
  combo32 co;
  co.reBuff = fl;

  return co.dwBuff == 0xFFFFFFFF;
}


bool    ValidFloat(float  fl)
{
  return !IsNAN(fl);
}
