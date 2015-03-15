/*------------------------------------------------------------------------------
DIGITALS_PAUSE.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "digitals_status.h"



extern  uint                    wCurr;



// ��������� �������� ����� ��������� � ����������
void    Pause(void)
{
  if (GetStatus() == 1) return;

  if ((GetCurr() == DEV_PAUSE) && (ibPortPause < bPORTS))
  {
    if (mpcwPause[ibPortPause] == 0)
    {
      wCurr = GetPause();
      mpSerial[ibPortPause] = SER_PAUSE;
    }
    else mpcwPause[ibPortPause]--;
  }
}



// ���������� ��������� �������� ����� ���������
void    MakePause(uint  w)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*ePAUSE);   

  ibPortPause = ibPort;

  SetPause(w);
  SetCurr(DEV_PAUSE);
}


// ���������� ��������� �������� ����� ���������
void    MakeLongPause(uint  w, uchar  bSecond)
{
  mpcwPause[ibPort] = (uint)(wFREQUENCY_T0*bSecond);   

  ibPortPause = ibPort;

  SetPause(w);
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
