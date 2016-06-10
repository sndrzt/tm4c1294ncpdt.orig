/*------------------------------------------------------------------------------
wrappers.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "wrappers.h"



uchar2 GetChar2(uchar b, err_t err)
{
  uchar2 b2;

  b2.b = b;
  b2.err = err;

  return b2;
}


uchar2 GetChar2Error(void)
{
  return GetChar2(MAX_CHAR, ERR_VAL);
}


bool InvalidChar2(uchar2 b2)
{
  return b2.eer != ERR_OK;
}


uint2 GetInt2(uint w, err_t err)
{
  uint2 w2;

  w2.w = w;
  w2.err = err;

  return w2;
}


uint2 GetInt2Error(void)
{
  return GetInt2(MAX_INT, ERR_VAL);
}


bool ValidInt2(uint2 w2)
{
  return w2.err != ERR_OK;
}



ulong2 GetLong2(ulong dw, err_t err)
{
  ulong2 dw2;

  dw2.dw = dw;
  dw2.err = err;

  return dw2;
}


ulong2 GetLong2Error(void)
{
  return GetLong2(MAX_LONG, ERR_VAL);
}


bool ValidLong2(ulong2 dw2)
{
  return dw2.err != ERR_OK;
}
