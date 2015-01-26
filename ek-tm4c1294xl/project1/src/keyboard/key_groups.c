/*------------------------------------------------------------------------------
KEY_GROUPS.C

 ������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../mem_groups.h"
#include        "../mem_program.h"
#include        "../display.h"
#include        "../beep.h"
#include        "../keyboard.h"
#include        "../groups.h"



//                                         0123456789ABCDEF
static char const       szMaskGroups[]  = "    + ___       ",
                        szGroups[]      = "������          ",
                        szNoNodes[]     = "  ��� �������   ";

static nodes            noT;



// ���������� ���� � ������
bool    AddNode(void)
{
uchar   i,j;

  // ��������� �� ��������� ����� ���� � ������
  for (i=0; i<GetGroupsSize(ibX); i++)
  {
    if (GetGroupsNodeCanal(ibX,i) == (noT.ibCanal & 0x7F))
    {           
      // �������� ���� ����
      SetGroupsNode(ibX,i,noT);
      SaveGroups();

      return(0);
    }
  }

  // ��������� ���� � ����� ������
  SetGroupsNode(ibX,ibY, noT);

  // ���������� �����     
  for(i=0; i<=GetGroupsSize(ibX); i++)
  {
    for(j=0; j<=GetGroupsSize(ibX); j++)
    {
      if (GetGroupsNodeCanal(ibX,i) < GetGroupsNodeCanal(ibX,j))
      {
        noT = GetGroupsNode(ibX,i);
        SetGroupsNode(ibX,i, GetGroupsNode(ibX,j));
        SetGroupsNode(ibX,j, noT);
      }
    }
  }

  // ����������� ������ ������
  SetGroupsSize(ibX, GetGroupsSize(ibX)+1);
  SaveGroups();

  return(1);
}



// �������� ���� �� ������
void    DelNode(void)
{
uchar   i;

  // ���� ��� �� ��������� ���� � ������
  if (ibY+1 < GetGroupsSize(ibX))
  {
    // �������� ��������� ���� �����
    for (i=ibY; i<GetGroupsSize(ibX)-1; i++)
    {
      noT = GetGroupsNode(ibX,i+1);
      SetGroupsNode(ibX,i, noT);
    }
  }
  // ����� ��������� ������ ����
  else if (ibY != 0) 
    ibY--;

  // ��������� ���������� ����� � ������
  if (GetGroupsSize(ibX) != 0)
    SetGroupsSize(ibX, GetGroupsSize(ibX)-1);
}



// ���������� ����� �������� ���� � ����� ���������� ����� � ������� ������
void    ShowNodes(void)
{
  sprintf(szLo+11,"%2u/%-2u",
          ibY+1,
          GetGroupsSize(ibX));
}



// ���������� ������� ����
void    ShowGroup(void)
{ 
  if (GetGroupsSize(ibX) > 0)
  {
    sprintf(szLo,"      %-3u  ",
            GetGroupsNodeCanal(ibX,ibY)+1);

    if (GetGroupsNodeSign(ibX,ibY) == 0)
      szLo[4] = '+';
    else
      szLo[4] = '-';

    ShowNodes();
  }
  else ShowLo(szNoNodes);
}



// ���������� ����� ������
void    ShowGroupNumber(void)
{ 
  sprintf(szHi,"������: %u",ibX+1);
}



void    key_SetGroups(void)
{
  if (bKey == bKEY_ENTER)
  {    
    if (enKeyboard == KBD_ENTER)        
    {                                   // ������ ������� ������ '����'
      enKeyboard = KBD_INPUT2;          // ���������� � ����� ������ ������
      ShowHi(szGroups); 
      Group();

      boSetGroups = boTrue; 
    }
    else if (enKeyboard == KBD_INPUT2)  // ����� ������ �� �����
    {                                   // �������� � ������ ������
      enKeyboard = KBD_POSTINPUT3;      
      ibX = 0;                          // ������ ������
      ShowGroupNumber();  
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {                                   
      if ((ibX = GetChar(10,11)-1) < bGROUPS)
      {                                 // �������� ������ ������
        enKeyboard = KBD_POSTINPUT3;
        ShowGroupNumber();
      } 
      else Beep();
    }    
    else if (enKeyboard == KBD_POSTINPUT1)              
    {                                   // ������ ������ ����� �����
      if ((noT.ibCanal = GetChar(6,8)-1) < bCANALS)
      {
        enKeyboard = KBD_POSTENTER;     

        if (szLo[4] == '-')
          noT.ibCanal |= 0x80;

        if (AddNode() == 1)             // ���������� ���� � ������
        {                               // ��� ������ ����                                        
          if (++ibY == bCANALS)      // ���� ������ ��������� ���������
          {
            enKeyboard = KBD_SHOW;      // ��������� � ����� ���������
            ibY = 0;
          }
        }
        else Beep();                    // ���� ����� ����
      }
      else Beep();
    }                                                                
    else if (enKeyboard == KBD_SHOW)
    {                                   // ���������� ��������
      ibY++;                            // ��������� �� ��������� ����
      if (ibY == GetGroupsSize(ibX))    // ����� �� ���������� ����     
      {                                 
        if (GetGroupsSize(ibX) == bCANALS) 
          ibY = 0;                      // ���� ������ ������ - ���������� �������� � ������
        else 
          enKeyboard = KBD_POSTENTER;   // ����� ���� ������ ����        
      }
    }


    if (enKeyboard == KBD_POSTINPUT3)
    {
      // ��� �������������������� ����������� ������������� ���������� ������
      if ((enGlobal == GLB_REPROGRAM) && (mpboUsedGroups[ibX] == boTrue))
      {
        Error();
        LongBeep();
        return;
      }
    }


    if ((enKeyboard == KBD_POSTINPUT3) || (enKeyboard == KBD_INPUT1))
    {                                   // �������� �������� ������ � ������
      ibY = 0;                          // ������� �� ������ ����
      if (GetGroupsSize(ibX) == 0) 
        enKeyboard = KBD_POSTENTER;     // ���� ������ ������ - ����� �����
      else                  
        enKeyboard = KBD_SHOW;          // ���� ������ �� ������ - ����� ���������
    }


    if (enKeyboard == KBD_POSTENTER)    // ��������������� ���������� �����  
    {
      enKeyboard = KBD_INPUT1; 
      ShowLo(szMaskGroups);
    }
    else if (enKeyboard == KBD_SHOW)    // ��������������� ��������
      ShowGroup();     
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
    else 
    if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1))
    {
      enKeyboard = KBD_POSTINPUT1;
      ShiftLo(6,8);
    }
  }


  else if (bKey == bKEY_MINUS)
  {    
    if (enKeyboard == KBD_SHOW)         
    {                                   // � ������ ���������
      DelNode();                        // ������� ���� �� ������
      LongBeep();

      if (GetGroupsSize(ibX) == 0)
      {
        enKeyboard = KBD_INPUT1; 
        ShowLo(szMaskGroups);
      }
      else ShowGroup();
    }
 

    else if ((enKeyboard == KBD_INPUT1) || (enKeyboard == KBD_POSTINPUT1)) 
    {                                   // � ������ �����
      if (szLo[4] == '-')               // �������� ���� ���� �� ��������������� 
        szLo[4] = '+';
      else
        szLo[4] = '-';
    } 
    else Beep();
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enKeyboard == KBD_POSTENTER) || 
        (enKeyboard == KBD_INPUT1)    || (enKeyboard == KBD_SHOW))
    {
      if (++ibX >= bGROUPS)
        ibX = 0;

      ShowGroupNumber();
      ibY = 0;                

      if (GetGroupsSize(ibX) == 0) 
      {
        enKeyboard = KBD_INPUT1;        // ���� ������ ������ - ����� �����
        ShowLo(szMaskGroups);
      }
      else                  
      {
        enKeyboard = KBD_SHOW;          // ���� ������ �� ������ - ����� ���������
        ShowGroup();
      }
    }
    else Beep();
  }
}



void    key_GetGroups(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_INPUT2;

      ShowHi(szGroups); 
      Group();
    }

    else if (enKeyboard == KBD_INPUT2)
    {
      enKeyboard = KBD_POSTENTER;   
        
      ibX = 0;
      ShowGroupNumber();

      ibY = 0;                
      ShowGroup();
    }
    else if (enKeyboard == KBD_POSTINPUT2)
    {
      if ((ibX = GetChar(10,11)-1) < bGROUPS)
      {
        enKeyboard = KBD_POSTENTER;   
        ShowGroupNumber();

        ibY = 0;                
        ShowGroup();
      }
      else Beep();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {  
      if (++ibY >= GetGroupsSize(ibX))
        ibY = 0;
      ShowGroup();
    }
  }


  else if (bKey < 10)
  {
    if ((enKeyboard == KBD_INPUT2) || (enKeyboard == KBD_POSTINPUT2))
    {
      enKeyboard = KBD_POSTINPUT2;
      ShiftLo(10,11);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if (enKeyboard == KBD_POSTENTER)  
    {
      if (++ibX >= bGROUPS)
        ibX = 0;

      ShowGroupNumber();

      ibY = 0;                
      ShowGroup();
    }
    else Beep();
  }
}

