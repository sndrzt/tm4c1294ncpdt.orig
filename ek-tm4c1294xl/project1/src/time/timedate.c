/*------------------------------------------------------------------------------
TIMEDATE.H


------------------------------------------------------------------------------*/

#include "../main.h"
#include "timedate.h"



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



bool    ValidTimeDate(time  ti)
{
  if (ti.bSecond > 59) return false;
  if (ti.bMinute > 59) return false;
  if (ti.bHour   > 23) return false;

  if ((ti.bDay == 0) ||
  		(ti.bDay > GetDaysInMonthYM(ti.bYear, ti.bMonth)))
    return false;

  if ((ti.bMonth == 0) ||
  		(ti.bMonth > 12 ))
    return false;

  if ((ti.bYear < bMINYEAR) ||
  		(ti.bYear > bMAXYEAR))
    return false;

  return true;
}



// ���������� ������ � ������ ���
ulong   GetSecondIndex(time  ti)
{
  return( (ulong)ti.bHour*3600 + ti.bMinute*60 + ti.bSecond );
}

