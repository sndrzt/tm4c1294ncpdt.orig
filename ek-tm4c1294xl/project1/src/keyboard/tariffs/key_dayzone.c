/*------------------------------------------------------------------------------
KEY_DAYZONE.�

 ������ ��������� ��������� �������
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_tariffs.h"
#include        "../../display/display.h"
#include        "../../keyboard.h"
#include        "../../tariffs/tariffs.h"
#include        "../../tariffs/zones.h"
#include        "../../flash/files.h"



//                                         0123456789ABCDEF
static char const       szMaskBreak[]   = "  __ __   _     ";
                        


// ���������� ������ � ���������� ��������� ��������� �������
bool    AddBreak(void)
{
uchar   i,j;

  // ���������� ����� � ����� ��������� ��������� �������
  SetZoneKeyBreak(ibX);

  // ��������� �� ������� ����� ������ � �������� �������� �������
  for(i=0; i<GetZoneKeySize(); i++)
  {
    // ���� ����� ����� ��� ����
    if (GetBreakKeyIndex(i) == GetBreakKeyIndex(ibX))
    {
      // �������� �����
      GetZoneKeyBreak(ibX);
      SetZoneKeyBreak(i);

      SaveFile(&flZone);
      return(0);
    }
  }

  // ����������      
  for(i=0; i<=GetZoneKeySize(); i++)
  {
    for(j=0; j<=GetZoneKeySize(); j++)
    {
      if (GetBreakKeyIndex(i) < GetBreakKeyIndex(j))
      {
        GetZoneKeyBreak(i);
        brAlt = brKey;

        GetZoneKeyBreak(j);
        SetZoneKeyBreak(i);

        brKey = brAlt;
        SetZoneKeyBreak(j);
      }
    }
  }

  // ����������� ������ ��������� ��������� �������
  SetZoneKeySize(GetZoneKeySize() + 1);

  SaveFile(&flZone);
  return(1);
}



// �������� ������ �� ��������� ��������� �������
void    DelBreak(void)
{
uchar   i;

  // ���� ��� �� ��������� �����
  if (ibX < GetZoneKeySize() - 1)      
  {                                 
    // �������� ����������� ������ ����� 
    for (i=ibX; i<GetZoneKeySize() - 1; i++)
    {
      GetZoneKeyBreak(i + 1);
      SetZoneKeyBreak(i);
    }
  }
  // ����� ��������� ������ ������
  else if (ibX != 0)
    ibX--;            

  // ��������� ���������� ������� 
  if (GetZoneKeySize() != 0)
    SetZoneKeySize(GetZoneKeySize() - 1);

  // �������� �������� ������
  if (GetZoneKeySize() < bBREAKS)
  {
    brKey = brZero;
    SetZoneKeyBreak(GetZoneKeySize());
  }

  SaveFile(&flZone);
}



// ������� ��������� ��������� �������
void    key_SetDayZone(void)
{
  if (bKey == bKEY_ENTER)
  {    
    if (enKeyboard == KBD_ENTER)
    {         
      enKeyboard = KBD_POSTINPUT4;      // �������� �������� ��������� ��������� �������

      ShowHi(szTariffs);
      Clear();
    }    
    else if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      if (enKeyboard == KBD_INPUT2)
      {
        bKey = 0; ShiftLo(5,6);
        bKey = 0; ShiftLo(5,6);
      }

      brKey.bMinute = GetCharLo(5,6);

      if ((brKey.bMinute % 30) == 0)
      {
        enKeyboard = KBD_INPUT3;
        szLo[8] = '-';        
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTINPUT3)
    {
      brKey.ibTariff = GetCharLo(10,10) - 1;

      if (brKey.ibTariff < bTARIFFS)
      {
        enKeyboard = KBD_POSTENTER;     // ��������� � ����� �����
        
        if (AddBreak() == 1)            // ��������� ����� ����� � �������� ������
        {                               
          if (++ibX == bBREAKS)         // ���� �������� ������ ��������
          {                               
            ibX = 0;                    // ��������� �� ������
            enKeyboard = KBD_SHOW;      // ��������� � ����� ���������
          }
        } 
        else Beep();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_SHOW)    // ����� ���������
    {
      ibX++;                            // ��������� �� ��������� �����

      if (ibX == GetZoneKeySize())      // ����� �� ����� ��������� ������� 
      {                                 
        if (ibX == bBREAKS)
          ibX = 0;                      // ���� �������� ������ �������� - ���������� �������� � ������
        else
          enKeyboard = KBD_POSTENTER;   // ���� � �������� ������� ���� ��������� ����� - ��������� � ����� �����
      }
    }


    if ((enKeyboard == KBD_POSTINPUT4) || (enKeyboard == KBD_INPUT1))
    {                                   // �������� ��� ���������� �������� ��������� ��������� �������
      ibX = 0;                          // ������� �� ������

      if (GetZoneKeySize() == 0)
        enKeyboard = KBD_POSTENTER;     // ���� �������� ������ ������ - ��������� � ����� �����
      else
        enKeyboard = KBD_SHOW;          // ���� �������� ������ �� ������ - ��������� � ����� ���������
    }


    if (enKeyboard == KBD_POSTENTER)    // ����� �����            
    { 
      enKeyboard = KBD_INPUT1;          // ���������� � ����� ������
      ShowLo(szMaskBreak);               
    }
    else if (enKeyboard == KBD_SHOW)    // ����� ���������
      ShowZoneKeyBreak(ibX);            // �������� �������� ������
  }



  else if (bKey == bKEY_MINUS)          // � ������ ���������
  {
    if (enKeyboard == KBD_SHOW)
    {                                   
      DelBreak();                       // ������� �����
      LongBeep();

      if (GetZoneKeySize() == 0)
      {                                 
        enKeyboard = KBD_INPUT1;         
        ShowLo(szMaskBreak);
      }
      else ShowZoneKeyBreak(ibX);
    }
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTINPUT1)
    {
      brKey.bHour = GetCharLo(2,3);

      if (brKey.bHour <= 24)
      {
        enKeyboard = KBD_INPUT2;
        szLo[4] = '.';        
      } 
      else Beep();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(2,3);
    }
    else 
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(5,6);
    }
    else 
    if ((enKeyboard == KBD_INPUT3) || (enKeyboard == KBD_POSTINPUT3))
    {
      enKeyboard = KBD_POSTINPUT3;
      ShiftLo(10,10);
    }
    else Beep();
  }
  else Beep();
}
