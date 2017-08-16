/*------------------------------------------------------------------------------
KEY_SPEEDS!C

 ������� � �������� ��������� ������
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "keyboard.h"
#include "../display/display.h"
#include "../serial/speeds.h"
#include "../serial/speeds_display.h"
#include "../serial/speeds_storage.h"
#include "../digitals/correct_limit.h"



//                                         0123456789ABCDEF
static char const       szPorts[]       = "�����           ";



static void ShowPort(uchar  ibPrt)
{
  sprintf(szLo+15,"%u",ibPrt+1);
}



void    key_SetSpeeds(void)
{
static uchar ibPrt;

  if (bKey == bKEY_ENTER)
  {
    if (enKeyboard == KBD_ENTER)
    {
      enKeyboard = KBD_POSTENTER;
      ShowHi(szPorts);

      Waiting(); DelayInf();

      ibPrt = 0;
      ShowSpeeds(ibPrt,1);
      ShowPort(ibPrt);
    }
    else if (enKeyboard == KBD_POSTENTER)
    {
      if (++ibPrt >= bPORTS)
        ibPrt = 0;

      ShowSpeeds(ibPrt,1);
      ShowPort(ibPrt);
    }
  }


  else if (bKey == bKEY_POINT)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      ((ibPrt == 0) || (ibPrt == 1)) ? (ibY = bBAUDS) : (ibY = 7);

      if (++mppoPorts[ibPrt].ibBaud >= ibY)
        mppoPorts[ibPrt].ibBaud = 0;

      SetSpeed(ibPrt);
      if (IsSlave(ibPrt) == 1) SetDefaultDelay(ibPrt);

      ShowSpeeds(ibPrt,1);
    }
    else Beep();
  }


  else if (bKey == bKEY_MINUS)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      if (++mppoPorts[ibPrt].enStream >= bSTREAMS)
        mppoPorts[ibPrt].enStream = STR_SLAVEESC;

      SetSpeed(ibPrt);
      SetCorrectLimit(ibPrt);
      if (IsSlave(ibPrt) == 1) SetDefaultDelay(ibPrt);

      ShowSpeeds(ibPrt,1);
    }
    else Beep();
  }


  else if (bKey == 0)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      if (++mppoPorts[ibPrt].ibParity >= bPARITYS)
        mppoPorts[ibPrt].ibParity = 0;

      SetSpeed(ibPrt);
      if (IsSlave(ibPrt) == 1) SetDefaultDelay(ibPrt);

      ShowSpeeds(ibPrt,1);
    }
    else Beep();
  }


  else if (bKey == 1)
  {
    if ((enGlobal != GLB_WORK) && (enKeyboard == KBD_POSTENTER))
    {
      if (IsMaster(ibPrt) == 1)
      {
        if (mpboLocalDisable[ibPrt] == true)
          mpboLocalDisable[ibPrt] = false;
        else
        {
          mpboLocalDisable[ibPrt] = true;
          mpboLocal[ibPrt] = false;
        }
        SaveLocalDisable();

        ShowSpeeds(ibPrt,1);
      }
      else Beep();
    }
    else Beep();
  }
  else Beep();
}

