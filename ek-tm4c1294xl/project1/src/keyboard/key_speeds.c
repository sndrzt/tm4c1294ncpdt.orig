/*------------------------------------------------------------------------------
KEY_SPEEDS.C

 ������� � �������� ��������� ������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_ports.h"
#include        "keyboard.h"
#include        "../display/display.h"
#include        "../serial/speeds.h"
#include        "../serial/speeds_display.h"



//                                         0123456789ABCDEF
static char const       szPorts[]       = "�����           ";



static void ShowPort(void)
{ 
  sprintf(szLo+15,"%u",ibX+1);
}



void    key_SetSpeeds(void)
{
  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ShowHi(szPorts);

      Waiting(); DelayInf();

      ibX = 0;                    
      ShowSpeeds(ibX,1);
      ShowPort();
    }
    else if (enKeyboard == KBD_POSTENTER)
    {                                   
      if (++ibX >= bPORTS) 
        ibX = 0;

      ShowSpeeds(ibX,1);      
      ShowPort();
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {                                   
      ((ibX == 0) || (ibX == 1)) ? (ibY = bSPEEDS) : (ibY = 7);

      if (++mppoPorts[ibX].ibSpeed >= ibY) 
        mppoPorts[ibX].ibSpeed = 0;

      SetSpeeds(ibX);
      if (IsSlave(ibX) == 1) SetDelay(ibX);

      ShowSpeeds(ibX,1);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {                                   
      if (++mppoPorts[ibX].enStream >= bSTREAMS) 
        mppoPorts[ibX].enStream = STR_SLAVEESC;

      SetSpeeds(ibX);
      SetCorrectLimit(ibX);
      if (IsSlave(ibX) == 1) SetDelay(ibX);

      ShowSpeeds(ibX,1);
    }
    else Beep();
  }


  else if (bKey == 0)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      if (++mppoPorts[ibX].ibParity >= bPARITYS) 
        mppoPorts[ibX].ibParity = 0; 

      SetSpeeds(ibX);
      if (IsSlave(ibX) == 1) SetDelay(ibX);

      ShowSpeeds(ibX,1);
    }
    else Beep();
  }


  else if (bKey == 1)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      if (IsMaster(ibX) == 1) 
      {
        if (mpboLocalDisable[ibX] == TRUE)
          mpboLocalDisable[ibX] = FALSE;
        else 
        { 
          mpboLocalDisable[ibX] = TRUE;
          mpboLocal[ibX] = FALSE;
        }

        ShowSpeeds(ibX,1);
      }  
      else Beep();
    }
    else Beep();
  }
  else Beep();
}

