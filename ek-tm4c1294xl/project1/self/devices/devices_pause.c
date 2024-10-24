/*------------------------------------------------------------------------------
DEVICES_PAUSE,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_flow.h"
#include "../serial/ports.h"
#include "../serial/monitor.h"
#include "../serial/input_wrapper.h"
#include "../sensors/unpack_w.h"
#include "../sensors/sensor31/unpack31.h"
#include "../digitals/digitals_status.h"
#include "devices_pause.h"



void    DevicesPause(void)
{
#ifndef SKIP_31
    if ((diCurr.bDevice == 9)  || (diCurr.bDevice == 10) ||
        (diCurr.bDevice == 31) || (diCurr.bDevice == 32) || (diCurr.bDevice == 33))
    {
      if (mpSerial[ibPort] == SER_BADLINK)
      {
        uchar bCrc = MakeCrc8Bit31InBuff(1, IndexInBuff()-1);
        if (bCrc == 0)
        {
          Unpack31();
          InputGoodCheck();
          mpSerial[ibPort] = SER_GOODCHECK;
        }
        else
          mpSerial[ibPort] = SER_BADCHECK;
      }
    }
#endif

#ifndef SKIP_K
    if ((diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
        (diCurr.bDevice == 16) || (diCurr.bDevice == 17))
    {
      if (mpSerial[ibPort] == SER_BADLINK)
      {
        if ((GetCurr() == DEV_OPENCANAL_K2) || (GetCurr() == DEV_OPENCANAL_K3))
        {
          MonitorIn();
          uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((b == '\r') || (b == '\n'))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_K2)
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_K2)
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_HEADER_K2)
        {
          MonitorIn();
          if (IndexInBuff() == 10)
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_Q
    else if (diCurr.bDevice == 22)
    {
      if (mpSerial[ibPort] == SER_BADLINK)
      {
        if ((GetCurr() == DEV_OPENCANAL_Q2) || (GetCurr() == DEV_OPENCANAL_Q3))
        {
          MonitorIn();
          uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((b == '\r') || (b == '\n'))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_Q2)
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_Q2)
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_HEADER_Q2)
        {
          MonitorIn();
          if (IndexInBuff() == 10)
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_U
    else if ((diCurr.bDevice == 26) || (diCurr.bDevice == 28))
    {
      if (mpSerial[ibPort] == SER_BADLINK)
      {
        if ((GetCurr() == DEV_OPENCANAL_U2) || (GetCurr() == DEV_OPENCANAL_U3))
        {
          MonitorIn();
          uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((b == '\r') || (b == '\n'))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PASSWORD_U2)
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_POSTCONTROL_U2)
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if ((GetCurr() == DEV_HEADER_U2) || (GetCurr() == DEV_HEADER_U4))
        {
          MonitorIn();
          if (IndexInBuff() == 3)
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif

#ifndef SKIP_W
    else if ((diCurr.bDevice == 29) || (diCurr.bDevice == 30))
    {
      if (mpSerial[ibPort] == SER_BADLINK)
      {
        if ((GetCurr() == DEV_OPENCANAL_W2) || (GetCurr() == DEV_OPENCANAL_W3))
        {
          MonitorIn();
          uchar b = InBuff(IndexInBuff() - 1) & 0x7F;
          if ((b == '\r') || (b == '\n'))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if ((GetCurr() == DEV_PASSWORD_W2) ||
                 (GetCurr() == DEV_POSTCONTROL_W2) ||
                 (GetCurr() == DEV_POSTSETCORRECT_W2))
        {
          MonitorIn();
          if ((IndexInBuff() == 1) && ((InBuff(0) & 0x7F) == 0x06))
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }

        else if (GetCurr() == DEV_PROFILE_W2)
        {
          if (DoneProfileW())
          {
            InputGoodCheck();
            mpSerial[ibPort] = SER_GOODCHECK;
          }
          else
            mpSerial[ibPort] = SER_BADCHECK;
        }
      }
    }
#endif
}
