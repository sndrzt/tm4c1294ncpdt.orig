/*------------------------------------------------------------------------------
RELAXS.C

 ������������ ���������� �����������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../memory/mem_program.h"
#include        "../keyboard.h"
#include        "../display.h"
#include        "../timedate.h"
#include        "../rtc.h"
#include        "tariffs.h"



//                                           0123456789ABCDEF
static char const       szNoRelaxs[]      = " ��� ���������� ",
                        szRelaxHoliday[]  = " ��������",
                        szRelaxWeekday[]  = " ������� ",
                        szRelaxError[]    = " ������ !";



// ������ ���������� ���� � ������ ����������
uchar   GetRelaxSize(void)
{
  return( mpreRelaxs.bSize );
}


// ���������� ���������� ���� � ������ ����������
void    SetRelaxSize(uchar  bSize)
{
  mpreRelaxs.bSize = bSize;
}



// ������ ���� �� ������ ����������
void    GetRelaxDate(uchar  ibRelax)
{
  tiRelax = mpreRelaxs.mptiDate[ibRelax];
}


// ���������� ���� � ������ ����������
void    SetRelaxDate(uchar  ibRelax)
{
  mpreRelaxs.mptiDate[ibRelax] = tiRelax;
}



// ��������� ������ ���������� �� ���������
void    DefaultRelaxs(void)
{
static uchar const  mpRelaxs[8*3] =
{ 1,  1,  2,
  2,  1,  2,
  7,  1,  2,
  8,  3,  2,
  1,  5,  2,
  9,  5,  2,
  7, 11,  2,
 25, 12,  2 };

  SetRelaxSize(0);

  ibZ = 0;
  for (ibX=0; ibX<sizeof(mpRelaxs)/3; ibX++)
  {
    tiRelax.bDay    = mpRelaxs[ibZ++];
    tiRelax.bMonth  = mpRelaxs[ibZ++];
    tiRelax.bSecond = mpRelaxs[ibZ++];  // ��� ���������: �����, �������, �����������

    SetRelaxDate(ibX);
    SetRelaxSize(GetRelaxSize() + 1);
  }

  boSetRelaxs = true; //false;
}



// ����� ������ ����������
void    ResetRelaxs(void)
{
  SetRelaxSize(0);
  boSetRelaxs = true; //false;

  boRelaxsFlag = false;
  ibRelaxsTariff = 1;
}



// ���������� ��� ��� ������
uchar   GetModeAlt(void)
{
uchar  i;

  if (bOldTariffsMode == 0)                    // ��� ����� �������� � ����������� ����
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
