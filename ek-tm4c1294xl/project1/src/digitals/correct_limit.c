/*------------------------------------------------------------------------------
CORRECT_LIMIT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "correct_limit.h"



cache const             chCorrectLimit = {CORRECT_LIMIT, &mpbCorrectLimit, sizeof(mpbCorrectLimit)};



void    InitCorrectLimit(void)
{
}


void    ResetCorrectLimit(void)
{
}



void    SetCorrectLimit(uchar  ibPrt)
{
//  mpbCorrectLimit[ibPrt] = (mppoPorts[ibPrt].enStream == STR_MASTERMODEM) ? bCORRECT_MODEM : bCORRECT_DIRECT;
}


void    CheckCorrectLimit(uchar  ibPrt)
{
//  if (mpbCorrectLimit[ibPrt] < bCORRECT_MINIMUM) SetCorrectLimit(ibPrt);
//  if (mpbCorrectLimit[ibPrt] > bCORRECT_MAXIMUM) mpbCorrectLimit[ibPrt] = bCORRECT_MAXIMUM;
}


void    MakeCorrectLimit(void)
{
//  if (diT.bDevice == 24) mpbCorrectLimit[diT.ibPort] = bCORRECT_DEVICE_S;
}


uchar   MinorCorrect(void)
{
  return 5; //mpbCorrectLimit[diCurr.ibPort];
}
