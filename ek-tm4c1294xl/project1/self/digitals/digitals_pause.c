/*------------------------------------------------------------------------------
DIGITALS_PAUSE!C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../serial/ports.h"
#include "digitals_status.h"
#include "digitals_pause.h"



// ������� ��� �������� �������� ����� ���������
uint                    mpcwPause[bPORTS];



extern  volatile device         deCurr;



// ��������� �������� ����� ��������� � ����������
void    Pause(void)
{
  if (GetStatus() == 1) return;

  if ((GetCurr() == DEV_PAUSE) && (ibPortPause < bPORTS))
  {
    if (mpcwPause[ibPortPause] == 0)
    {
      deCurr = GetPause();
      mpSerial[ibPortPause] = SER_PAUSE;
    }
    else mpcwPause[ibPortPause]--;
  }
}



// ���������� ��������� �������� ����� ���������
void    MakePause(device  de)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*ePAUSE);   

  ibPortPause = ibPort;

  SetPause(de);
  SetCurr(DEV_PAUSE);
}


// ���������� ��������� �������� ����� ���������
void    MakeLongPause(device  de, uchar  bSecond)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*bSecond);   

  ibPortPause = ibPort;

  SetPause(de);
  SetCurr(DEV_PAUSE);
}



// ������ ��������� �������� 
void    NextPause(void)
{
  if (ibPortPause < bPORTS)
  {
    mpcwPause[ibPortPause] = (uint)(wFREQUENCY_T0*ePAUSE);
    SetCurr(DEV_PAUSE);
  }
}
