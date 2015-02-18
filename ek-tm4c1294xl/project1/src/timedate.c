/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "display/display.h"
#include        "engine.h"



time                    tiAlt;

time const              tiZero = { 0, 0, 0, 0, 0, 0 };

static uchar const      mpbDaysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };



// ���������� ���� � ������
uchar   GetDaysInMonthM(uchar  bMonth)
{
	ASSERT((bMonth >= 1) && (bMonth <= 12));

  return mpbDaysInMonth[bMonth-1];
}


// ���������� ���� � ������
uchar   GetDaysInMonthYM(uchar  bYear, uchar  bMonth)
{
  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
  ASSERT((bMonth >= 1) && (bMonth <= 12));

  if ((bYear % 4 == 0) && (bMonth == 2))
    return 29;
  else
    return GetDaysInMonthM(bMonth);
}


// ���������� ���� � ����
uint    GetDaysInYearY(uchar  bYear)
{
  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));

  if (bYear % 4 == 0)
    return 366;
  else
    return 365;
}


// ���� ������: 0 - �����������, ..., 6 - ����������� (1 ������ 2000 ����: 5 - �������)
uchar   GetWeekdayYMD(uchar  bYear, uchar  bMonth, uchar  bDay)
{
uchar   i;
uint    j;

  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
  ASSERT((bMonth >= 1) && (bMonth <= 12));
  ASSERT((bDay >= 1) && (bDay <= 31));

  j = 5 + bDay - 1;

  for (i=1; i<bMonth; i++)
  	j += GetDaysInMonthYM(bYear, i);

  for (i=0; i<bYear; i++)
  	j += GetDaysInYearY(i);

  return j % 7;
}


// ��������� ����������� ������
time   *GetDecretDateYM(uchar  bYear, uchar  bMonth)
{
static time ti;

  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
  ASSERT((bMonth >= 1) && (bMonth <= 12));

  ti = tiZero;

  ti.bYear  = bYear;
  ti.bMonth = bMonth;

  for (ti.bDay=GetDaysInMonthYM(ti.bYear, ti.bMonth); ti.bDay>0; ti.bDay--)
    if (GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) == 6) break;

  return &ti;
}


// ���������� ���� � ������ ����
uint    GetDayIndexYMD(uchar  bYear, uchar  bMonth, uchar  bDay)
{
uchar   i;
uint    j;

  ASSERT((bYear >= bMINYEAR) && (bYear <= bMAXYEAR));
	ASSERT((bMonth >= 1) && (bMonth <= 12));
	ASSERT((bDay >= 1) && (bDay <= 31));

  j = bDay - 1;

  for (i=1; i<bMonth; i++)
  	 j += GetDaysInMonthYM(bYear, i);

  return j;
}


// ���������� ���� � ������ ����
uint    GetDayIndexMD(uchar  bMonth, uchar  bDay)
{
uchar   i;
uint    j;

  ASSERT((bMonth >= 1) && (bMonth <= 12));
	ASSERT((bDay >= 1) && (bDay <= 31));

  j = bDay - 1;

  for (i=1; i<bMonth; i++)
    j += GetDaysInMonthM(i);

  return j;
}



bool     TrueTimeDate(void)
{
  if (tiAlt.bSecond > 59) return false;
  if (tiAlt.bMinute > 59) return false;
  if (tiAlt.bHour   > 23) return false;

  if ((tiAlt.bDay == 0) ||
  		(tiAlt.bDay > GetDaysInMonthYM(tiAlt.bYear, tiAlt.bMonth)))
    return false;

  if ((tiAlt.bMonth == 0) ||
  		(tiAlt.bMonth > 12 ))
    return false;

  if ((tiAlt.bYear < bMINYEAR) ||
  		(tiAlt.bYear > bMAXYEAR))
    return false;

  return true;
}



ulong   DateToSecIndex(time  ti)
{
uchar   i;
ulong   dw;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += GetDaysInYearY(i);

  for (i=1; i<ti.bMonth; i++)
    dw += GetDaysInMonthYM(ti.bYear, i);

  dw += ti.bDay-1;
  dw *= 1440;
  dw += ti.bHour*60 + ti.bMinute;
  dw *= 60;
  dw += ti.bSecond;

  return(dw);
}


time    SecIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= (ulong)24*60*60*GetDaysInYearY(ti.bYear))
  {
    dw -= (ulong)24*60*60*GetDaysInYearY(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= (ulong)24*60*60*GetDaysInMonthYM(ti.bYear,ti.bMonth))
  {
    dw -= (ulong)24*60*60*GetDaysInMonthYM(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw/((ulong)24*60*60); dw -= (ulong)24*60*60*ti.bDay;
  ti.bDay++;

  ti.bHour = dw/((uint)60*60); dw -= (ulong)60*60*ti.bHour;

  ti.bMinute = dw/60;  dw -= (ulong)60*ti.bMinute;
  ti.bSecond = dw;

  return ti;
}


/*
ulong   DateToMntIndex(void)
{
uchar   i;
time    ti;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += DaysInYearSpec(i);

  for (i=1; i<ti.bMonth; i++)
    dw += DaysInMonthSpec(ti.bYear,i);

  dw += ti.bDay-1;
  dw *= 480;
  dw += ti.bHour*20 + ti.bMinute/3;

  return(dw);
}


void    MntIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= (ulong)480*DaysInYearSpec(ti.bYear))
  {
    dw -= (ulong)480*DaysInYearSpec(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= (ulong)480*DaysInMonthSpec(ti.bYear,ti.bMonth))
  {
    dw -= (ulong)480*DaysInMonthSpec(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw/480; dw -= ti.bDay*480;
  ti.bDay++;

  ti.bHour = dw/20; dw -= ti.bHour*20;

  ti.bMinute = dw*3;
  ti.bSecond = 0;
}
*/


ulong   DateToHouIndex(time  ti)
{
uchar   i;
ulong   dw;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += GetDaysInYearY(i);

  for (i=1; i<ti.bMonth; i++)
    dw += GetDaysInMonthYM(ti.bYear,i);

  dw += ti.bDay-1;
  dw *= 48;
  dw += ti.bHour*2 + ti.bMinute/30;

  return(dw);
}


time    HouIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= (uint)48*GetDaysInYearY(ti.bYear))
  {
    dw -= (uint)48*GetDaysInYearY(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= (uint)48*GetDaysInMonthYM(ti.bYear,ti.bMonth))
  {
    dw -= (uint)48*GetDaysInMonthYM(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw/48; dw -= ti.bDay*48;
  ti.bDay++;

  ti.bHour = dw/2; dw -= ti.bHour*2;

  ti.bMinute = dw*30;
  ti.bSecond = 0;

  return ti;
}


/*
ulong   DateToDayIndex(void)
{
uchar   i;
time    ti;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += DaysInYearSpec(i);

  for (i=1; i<ti.bMonth; i++)
    dw += DaysInMonthSpec(ti.bYear,i);

  dw += ti.bDay-1;

  return(dw);
}


void    DayIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= DaysInYearSpec(ti.bYear))
  {
    dw -= DaysInYearSpec(ti.bYear);
    ti.bYear++;
  }

  ti.bMonth = 1;
  while (dw >= DaysInMonthSpec(ti.bYear,ti.bMonth))
  {
    dw -= DaysInMonthSpec(ti.bYear,ti.bMonth);
    ti.bMonth++;
  }

  ti.bDay = dw;
  ti.bDay++;

  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;
}



ulong   DateToMonIndex(void)
{
uchar   i;
time    ti;

  dw = 0;

  for (i=0; i<ti.bYear; i++)
    dw += 12;

  dw += ti.bMonth-1;

  return(dw);
}


void    MonIndexToDate(ulong  dw)
{
time    ti;

  ti.bYear = 0;
  while (dw >= 12)
  {
    dw -= 12;
    ti.bYear++;
  }

  ti.bMonth = dw+1;
  ti.bDay = 1;

  ti.bHour   = 0;
  ti.bMinute = 0;
  ti.bSecond = 0;
}
*/


void    ShowTime(time  ti)
{
  sprintf(szLo+4,"%02u:%02u:%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bSecond);
}


void    ShowDate(time  ti)
{
  sprintf(szLo+4,"%02u.%02u.%02u",
                 ti.bDay,
                 ti.bMonth,
                 ti.bYear);

  szLo[14] = szDigits[GetWeekdayYMD(ti.bYear, ti.bMonth, ti.bDay) + 1];
}


void    ShowTimeDate(time  ti)
{
  sprintf(szLo+1,"%02u:%02u %02u.%02u.%02u",
                 ti.bHour,
                 ti.bMinute,
                 ti.bDay,
                 ti.bMonth,
                 ti.bYear);
}



void    LoadBetaMonth(uchar  ibMonth)
{
  strcpy(szBeta,szOnMonth);
  sprintf(szBeta+11, "%-2u", ibMonth + 1);
}

