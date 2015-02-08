/*------------------------------------------------------------------------------
RELAXS.C

 ������������ ���������� �����������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../timedate.h"
#include        "../rtc.h"
#include        "../flash/files.h"
#include        "tariffs.h"
#include        "relaxs.h"



//                                           0123456789ABCDEF
static char const       szNoRelaxs[]      = " ��� ���������� ",
                        szRelaxHoliday[]  = " ��������",
                        szRelaxWeekday[]  = " ������� ",
                        szRelaxError[]    = " ������ !";


file const              flRelaxsFlag = {wFLA_RELAXS_FLAG, &boRelaxsFlag, sizeof(boolean)};
file const              flRelaxsTariff = {wFLA_RELAXS_TARIFF, &ibRelaxsTariff, sizeof(uchar)};
file const              flRelaxs = {wFLA_RELAXS_TARIFF, &reRelaxs, sizeof(relaxs)};



void    InitRelaxs(void)
{
	LoadFile(&flRelaxsFlag);
	LoadFile(&flRelaxsTariff);
	LoadFile(&flRelaxs);
}


void    ResetRelaxs(void)
{
  boRelaxsFlag = false;
  SaveFile(&flRelaxsFlag);

  ibRelaxsTariff = 1;
  SaveFile(&flRelaxsTariff);

  memset(&reRelaxs, 0, sizeof(relaxs));
	SaveFile(&flRelaxs);
}


void    DefaultRelaxs(void)
{
static uchar const  mpRelaxs[8*3] = {
	1,  1,  2,
  2,  1,  2,
  7,  1,  2,
  8,  3,  2,
  1,  5,  2,
  9,  5,  2,
  7, 11,  2,
 25, 12,  2
};

uchar  i, j;

  memset(&reRelaxs, 0, sizeof(relaxs));

  SetRelaxSize(0);

  j = 0;
  for (i=0; i<sizeof(mpRelaxs)/3; i++)
  {
    tiRelax.bDay    = mpRelaxs[j++];
    tiRelax.bMonth  = mpRelaxs[j++];
    tiRelax.bSecond = mpRelaxs[j++];  // ��� ���������: �����, �������, �����������

    SetRelaxDate(i);
    SetRelaxSize(GetRelaxSize() + 1);
  }

	SaveFile(&flRelaxs);
}



// ������ ���������� ���� � ������ ����������
uchar   GetRelaxSize(void)
{
  return( reRelaxs.bSize );
}


// ���������� ���������� ���� � ������ ����������
void    SetRelaxSize(uchar  bSize)
{
  reRelaxs.bSize = bSize;
}



// ������ ���� �� ������ ����������
void    GetRelaxDate(uchar  ibRelax)
{
  tiRelax = reRelaxs.mptiDate[ibRelax];
}


// ���������� ���� � ������ ����������
void    SetRelaxDate(uchar  ibRelax)
{
  reRelaxs.mptiDate[ibRelax] = tiRelax;
}



// ���������� ��� ��� ������
uchar   GetModeAlt(void)
{
uchar  i;

  if (bTariffsMode == 0)                    // ��� ����� �������� � ����������� ����
    return(0);                          // �����

  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);

    if ((tiRelax.bDay   == tiAlt.bDay) &&
        (tiRelax.bMonth == tiAlt.bMonth)) 
      return(tiRelax.bSecond);          // ��� �������� ��� ������������ �� ������ ����������
  }

  i = Weekday();                        // ��� �������� ��� ������������ �� ���������

  if (i < 5)  return(0);                // �����
  else 
  if (i == 5) return(1);                // �������
  else        return(2);                // �����������
}
// ������� ��������������� ��������� ���������� tiAlt



// ���������� ��� �������� ������
void    ShowModeName(uchar  ibMode)
{
  switch (ibMode)
  {
    case 1:  strcpy(szLo+7, szRelaxHoliday);  break;
    case 2:  strcpy(szLo+7, szRelaxWeekday);  break;
    default: strcpy(szLo+7, szRelaxError);    break;
  }
}



// ���������� ���� � ��� �������� ���������, ��� ����� � ����� ���������� ����������
void    ShowRelax(uchar  ibRelax)
{
  if (GetRelaxSize() > 0)
  {
    GetRelaxDate(ibRelax);
   
    sprintf(szLo," %2u.%02u",
                 tiRelax.bDay,
                 tiRelax.bMonth);

    ShowModeName(tiRelax.bSecond);

    sprintf(szHi+11,"%2u/%-2u",
                    ibRelax+1,
                    GetRelaxSize());    
  }
  else ShowLo(szNoRelaxs);    
}
