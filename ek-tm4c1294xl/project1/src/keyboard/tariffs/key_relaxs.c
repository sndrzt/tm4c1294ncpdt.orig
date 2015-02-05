/*------------------------------------------------------------------------------
KEY_RELAXS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../memory/mem_settings.h"
#include        "../../memory/mem_realtime.h"
#include        "../../keyboard.h"
#include        "../../display/display.h"
#include        "../../timedate.h"
#include        "../../rtc.h"
#include        "../../tariffs/relaxs.h"



//                                         0123456789ABCDEF
static char const       szRelaxs[]      = "���������       ",
                        szMaskRelax[]   = " __ __          ";



// ���������� ������ ��������� � ������ � ����������
bool    AddRelax(void)
{
uchar   i,j;
uint    k;

  // ��������� �� ������� ����� ��������� � ������
  for (i=0; i<GetRelaxSize(); i++)
  {
    GetRelaxDate(i);
    if ((tiRelax.bMonth == tiKey.bMonth) && (tiRelax.bDay == tiKey.bDay))
    {
      // �������� ��� ���������, �� �������� ��� � ������
      SetRelaxDate(i);
      return(0);
    }
  }


  // ���������� �������� � ����� ������
  tiRelax = tiKey; SetRelaxDate(ibX);

  // ����������      
  for(i=0; i<=GetRelaxSize(); i++)
  {
    for(j=0; j<=GetRelaxSize(); j++)
    {
      GetRelaxDate(i);
      tiAlt = tiRelax; k = GetDayIndex();

      GetRelaxDate(j); 
      tiAlt = tiRelax;

      if (k < GetDayIndex())
      {
        GetRelaxDate(i); tiAlt = tiRelax;

        GetRelaxDate(j);
        SetRelaxDate(i);

        tiRelax = tiAlt; SetRelaxDate(j);
      }
    }
  }

  // ����������� ������ ������
  SetRelaxSize(GetRelaxSize() + 1);             
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
}



// ������� ������ ����������
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
      tiKey.bDay = GetChar(1,2);
      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[3] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_POSTINPUT3)              
    {                                  
      tiKey.bMonth = GetChar(4,5);
      tiKey.bYear  = (*PGetCurrTimeDate()).bYear;

      tiAlt = tiKey;

      if ((tiKey.bMonth == 0) || (tiKey.bMonth > 12))
        Beep();
      else if (tiKey.bDay > DaysInMonth())
      {
        enKeyboard = KBD_INPUT2; 
        LongBeep();

        ShowLo(szMaskRelax); 
      }     
      else
      {
        enKeyboard = KBD_INPUT4;
        tiKey.bSecond = 1;              // ��� ��������� (����� ������)              

        ShowModeName(tiKey.bSecond);
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
      tiKey.bDay = GetChar(1,2);
      if ((tiKey.bDay > 0) && (tiKey.bDay <= 31))
      {
        enKeyboard = KBD_INPUT3;
        szLo[3] = '.';
      }
      else Beep();
    }      
    else if (enKeyboard == KBD_INPUT4)   
    {
      if (++tiKey.bSecond > 2) tiKey.bSecond = 1;

      ShowModeName(tiKey.bSecond);
      szLo[7] = '.';
    }
    else Beep();
  }
  else Beep();
}



// �������� ������ �����������
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


/*
// �������� ���������� ������� �����
void    key_GetWeekday(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;   

      ShowHi(szWeekday); 

      tiAlt = *PGetCurrTimeDate();        
      switch ( GetModeAlt() )
      {
        case 0:  strcpy(szLo, szMode1);  break;
        case 1:  strcpy(szLo, szMode2);  break;
        case 2:  strcpy(szLo, szMode3);  break;
        default: Error();                break;
      }
    }
  }
}
*/

