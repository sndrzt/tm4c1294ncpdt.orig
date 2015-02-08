/*------------------------------------------------------------------------------
GAPS.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../engine.h"
#include        "../rtc.h"
#include        "../timedate.h"
#include        "../ports.h"
#include        "../flash/files.h"
#include        "tariffs.h"
#include        "gaps.h"



//                                           0123456789ABCDEF
static char const       szNoGaps[]        = "  ��� ��������  ",
                        szGapError[]      = " ������ !";


static time const       tiGap0 = { 0, 0, 0, 14, 4, 0 };
static time const       tiGap1 = { 1, 0, 0, 14, 10, 0 };

file const              flGapsFlag = {wFLA_GAPS_FLAG, &boGapsFlag, sizeof(boolean)};
file const              flGaps = {wFLA_GAPS, &gaGaps, sizeof(gaps)};




void    InitGaps(void)
{
	LoadFile(&flGapsFlag);
	LoadFile(&flGaps);
}


void    ResetGaps(void)
{
uchar i;

  boGapsFlag = false;
  SaveFile(&flGapsFlag);

  tiGap = tiZero;
  for (i=0; i<bGAPS; i++)
    SetGapDate(i);

  tiGap = tiGap0;
  SetGapDate(0);

  tiGap = tiGap1;
  SetGapDate(1);

  SetGapSize(2);

	SaveFile(&flGaps);
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



uint    GetDayIndex_Alt(void) 
{
uchar   i;
uint    j;

  j = tiAlt.bDay - 1; 

  for (i=1; i<tiAlt.bMonth; i++)
    j += mpbDaysInMonth[i - 1];

  return j;
}


uint    GetDayIndex_Gap(void) 
{
uchar   i;
uint    j;

  j = tiGap.bDay - 1; 

  for (i=1; i<tiGap.bMonth; i++)
    j += mpbDaysInMonth[i - 1];

  return j;
}


uchar   DaysInMonth_Gap(void)
{
  return mpbDaysInMonth[tiAlt.bMonth - 1];
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

      for (j=0; j<=GetDayIndex_Gap(); j++)
        mpbGaps[j] = tiGap.bSecond;
    }
  }
}



void    ShowGapName(uchar  ibMode)
{
  if (ibMode < 12)
    sprintf(szLo+7, "������ %u" , ibMode+1);
  else
    strcpy(szLo+7, szGapError);
}



void    ShowGap(uchar  ibGap)
{
  if (GetGapSize() > 0)
  {
    GetGapDate(ibGap);
   
    sprintf(szLo,"%2u.%02u", tiGap.bDay, tiGap.bMonth);

    ShowGapName(tiGap.bSecond);

    sprintf(szHi+11,"%2u/%-2u", ibGap+1, GetGapSize());
  }
  else ShowLo(szNoGaps);    
}
