/*------------------------------------------------------------------------------
GAPS!C

 �������� �������: ('����� �66 �� 17.08.2010')
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_tariffs.h"
#include "../nvram/cache.h"
#include "../time/timedate.h"
#include "tariffs.h"
#include "gaps.h"



static time const       tiGap0 = { 0, 0, 0, 14,  4, 0 };
static time const       tiGap1 = { 1, 0, 0, 14, 10, 0 };

cache const             chGapsFlag = {GAPS_FLAG, &boGapsFlag, sizeof(bool)};
cache const             chGaps = {GAPS, &gaGaps, sizeof(gaGaps)};



void    InitGaps(void)
{
  LoadCache(&chGapsFlag);
  LoadCache(&chGaps);
}


void    ResetGaps(void)
{
  boGapsFlag = false;
  SaveCache(&chGapsFlag);


  memset(&gaGaps, 0, sizeof(gaGaps));

  tiGap = tiGap0;
  SetGapDate(0);

  tiGap = tiGap1;
  SetGapDate(1);

  SetGapSize(2);
  SaveCache(&chGaps);
}



uchar   GetGapSize(void) 
{
  return( gaGaps.bSize );
}


void    SetGapSize(uchar  bSize) 
{
  gaGaps.bSize = bSize;
}



void    GetGapDate(uchar  ibGap) 
{
  tiGap = gaGaps.mptiDate[ibGap];
}


void    SetGapDate(uchar  ibGap) 
{
  gaGaps.mptiDate[ibGap] = tiGap;
}



void    MakeGaps(void)
{
uchar   i;
uint    j;

  if (GetGapSize() == 0)
  {
    for (j=0; j<sizeof(mpbGaps); j++)
      mpbGaps[j] = 0;
  }
  else
  { 
    GetGapDate(0);
    for (j=0; j<365; j++) 
      mpbGaps[j] = tiGap.bSecond;

    for (i=0; i<GetGapSize(); i++) 
    {
      GetGapDate(GetGapSize()-1-i);

      for (j=0; j<=GetDayIndexMD(tiGap.bMonth, tiGap.bDay); j++)
        mpbGaps[j] = tiGap.bSecond;
    }
  }
}
