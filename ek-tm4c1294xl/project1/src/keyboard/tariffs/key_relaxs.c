/*------------------------------------------------------------------------------
KEY_RELAXS.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../keyboard.h"
#include "../../display/display.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../tariffs/relaxs.h"
#include "../../nvram/cache.h"



//                                         0123456789ABCDEF
static char const       szRelaxs[]      = "���������       ",
                        szMaskRelax[]   = " __ __          ",
                        szNoRelaxs[]    = " ��� ���������� ",
                        szHoliday[]     = " ��������",
                        szWeekday[]     = " ������� ",
                        szError[]       = " ������ !";


static time             tiT;



void    ShowRelaxName(uchar  i)
{
  switch (i)
  {
    case 1:  strcpy(szLo+7, szHoliday);  break;
    case 2:  strcpy(szLo+7, szWeekday);  break;
    default: strcpy(szLo+7, szError);    break;
  }
}


void    ShowRelax(uchar  ibRelax)
{
  if (GetRelaxSize() > 0)
  {
    GetRelaxDate(ibRelax);

    sprintf(szLo," %2u.%02u", tiRelax.bDay, tiRelax.bMonth);
    ShowRelaxName(tiRelax.bSecond);
    sprintf(szHi+11,"%2u/%-2u", ibRelax+1, GetRelaxSize());
  }
  else ShowLo(szNoRelaxs);
}



// ���������� ������ ��������� � ������ � ����������
bool    AddRelax(void)
{
uchar   i,j;
uint    k;

  // ��������� �� ������� ����� ��������� � ������
  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bMonth == tiT.bMonth) && (tiRelax.bDay == tiT.bDay))
    {
      // �������� ��� ���������, �� �������� ��� � ������
      SetRelaxDate(i);

    	SaveCache(&chRelaxs);
      return(0);
    }
  }


  // ���������� �������� � ����� ������
  tiRelax = tiT; SetRelaxDate(ibX);

  // ����������
  for(i=0; i<=GetRelaxSize(); i++)
  {
    for(j=0; j<=GetRelaxSize(); j++)
    {
      GetRelaxDate(i);
      k = GetDayIndexMD(tiRelax.bMonth, tiRelax.bDay);

      GetRelaxDate(j);
      if (k < GetDayIndexMD(tiRelax.bMonth, tiRelax.bDay))
      {
        GetRelaxDate(i);
        time ti = tiRelax;

        GetRelaxDate(j);
        SetRelaxDate(i);

        tiRelax = ti;
        SetRelaxDate(j);
      }
    }
  }

  // ����������� ������ ������
  SetRelaxSize(GetRelaxSize() + 1);

	SaveCache(&chRelaxs);
  return(1);
}



// �������� ��������� �� ������
void    DelRelax(void)
{
uchar  i;

  // ���� ������� �� ��������� ��������
  if (ibX < GetRelaxSize() - 1)
  {
    // �������� ����������� ��������� �����
    for (i=ibX; i<GetRelaxSize() - 1; i++)
    {
      GetRelaxDate(i + 1);
      SetRelaxDate(i);
    }
  }
  // ����� ��������� ������ �������� ���������
  else if (ibX != 0) 
    ibX--;        

  // ��������� ���������� ����������
  if (GetRelaxSize() != 0)
    SetRelaxSize(GetRelaxSize() - 1);

	SaveCache(&chRelaxs);
}



void    key_SetRelaxs(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {                                  
      if (boRelaxsFlag == false)
      { BlockProgram(bSET_RELAXS_FLAG); return; }
      else
      {
        enKeyboard = KBD_POSTINPUT1;    // �������� �������� ������ ����������
        ShowHi(szRelaxs);       
      }
    }     
    else if (enKeyboard == KBD_POSTINPUT2)              
    {                                   
      tiT.bDay = GetCharLo(1,2);
      if ((tiT.bDay > 0) && (tiT.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[3] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_POSTINPUT3)              
    {                                  
      tiT.bMonth = GetCharLo(4,5);
      tiT.bYear  = GetCurrTimeDate()->bYear;

      if ((tiT.bMonth == 0) || (tiT.bMonth > 12))
        Beep();
      else if (tiT.bDay > GetDaysInMonthYM(tiT.bYear, tiT.bMonth))
      {
        enKeyboard = KBD_INPUT2; 
        LongBeep();

        ShowLo(szMaskRelax); 
      }     
      else
      {
        enKeyboard = KBD_INPUT4;
        tiT.bSecond = 1;              // ��� ��������� (����� ������)

        ShowRelaxName(tiT.bSecond);
        szLo[7] = '.';
      }
    }
    else if (enKeyboard == KBD_INPUT4)              
    {
      enKeyboard = KBD_POSTENTER;       // ��������� � ����� �����

      if (AddRelax() == 1)              // ��������� ����� ��������� � ������
      {
        if (++ibX == bRELAXS)           // ���� ������ ��������
        {
          ibX = 0;                      // ��������� �� ������
          enKeyboard = KBD_SHOW;        // ��������� � ����� ���������
        }
      }
      else Beep();                      // ����� �������� ���� � ������
    }                                                            
    else if (enKeyboard == KBD_SHOW)    // ����� ���c�����
    {                                   
      ibX++;                            // ��������� �� ��������� ��������
      if (ibX == GetRelaxSize())        // ����� �� ����� ������
      {                                 
        if (GetRelaxSize() == bRELAXS) 
          ibX = 0;                      // ���� ������ �������� - ���������� �������� � ������
        else 
          enKeyboard = KBD_POSTENTER;   // ���� � ������ ���� ��������� ����� - ��������� � ����� �����
      }
    }


    if ((enKeyboard == KBD_POSTINPUT1) || (enKeyboard == KBD_INPUT2))
    {                                   // �������� ��� ���������� �������� ������ ����������
      ibX = 0;                          // ��������� �� ������
      if (GetRelaxSize() == 0) 
        enKeyboard = KBD_POSTENTER;     // ���� ������ ������ - ��������� � ����� �����
      else                  
        enKeyboard = KBD_SHOW;          // ���� ������ �� ������ - ��������� � ����� ���������
    }


    if (enKeyboard == KBD_POSTENTER)    // ����� �����
    {
      enKeyboard = KBD_INPUT2;          // ���������� � ����� ���������
      ShowLo(szMaskRelax);
    }
    else if (enKeyboard == KBD_SHOW)    // ����� ���������
      ShowRelax(ibX);                   // �������� �������� ���������
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(1,2);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(4,5);
    }
  }


  else if (bKey == bKEY_MINUS)
  {    
    if (enKeyboard == KBD_SHOW)         // � ������ ���������
    {
      DelRelax();                       // ������� �������� �� ������
      LongBeep();

      if (GetRelaxSize() == 0)
      {
        enKeyboard = KBD_INPUT2; 

        ShowHi(szRelaxs); 
        ShowLo(szMaskRelax);
      }
      else ShowRelax(ibX);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {    
    if (enKeyboard == KBD_POSTINPUT2)              
    {                                   
      tiT.bDay = GetCharLo(1,2);
      if ((tiT.bDay > 0) && (tiT.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[3] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_INPUT4)   
    {
      if (++tiT.bSecond > 2) tiT.bSecond = 1;

      ShowRelaxName(tiT.bSecond);
      szLo[7] = '.';
    }
    else Beep();
  }
  else Beep();
}



void    key_GetRelaxs(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      if (boRelaxsFlag == false)
      { BlockProgram(bSET_RELAXS_FLAG); return; }
      else
      {
        enKeyboard = KBD_POSTENTER;   
        ShowHi(szRelaxs); 
        
        ibX = 0;                
        ShowRelax(ibX);
      }
    }
    else if (enKeyboard == KBD_POSTENTER)
    {  
      if (++ibX >= GetRelaxSize()) ibX = 0;
      ShowRelax(ibX);
    }
  }
}
