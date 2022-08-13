/*------------------------------------------------------------------------------
correct39_wrapper.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "correct39_wrapper.h"



static uchar            cbCorrects;
static uint             wDeltaOld;
static uint             wDeltaNew;



void    Init_Current39(void)
{
  cbCorrects = 0;
  wDeltaOld = 0;
  wDeltaNew = 0;
}



uchar   GetCounter_Correct39(void)
{
  return cbCorrects;
}



void    Write_Current39(uint  wDelta)
{
  cbCorrects++;
  wDeltaOld = wDelta;
}



bool    Read2_Current39(uint  wDelta)
{
  wDeltaNew = wDelta;
  return (wDeltaNew < wDeltaOld) && (cbCorrects < 100);
}


void    Read3_Current39(void)
{
  cbCorrects++;
  wDeltaOld = wDeltaNew;
}
