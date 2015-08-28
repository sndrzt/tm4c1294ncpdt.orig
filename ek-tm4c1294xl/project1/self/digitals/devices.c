/*------------------------------------------------------------------------------
DEVICES.C
              

------------------------------------------------------------------------------*/

#include "../main.h"
#include "../display/display.h"



//                                         0123456789ABCDEF
message                 mpszDevices[bMAXDEVICES+1] = {
                                          ".�����          ",
                                          ".���-4��        ",
                                          ".��������-230   ",
                                          ".CC-301         ",
                                          ".���������� 4   ",
                                          ".���������� 5   ",
                                          ".���������� 6   ",
                                          ".���������� 7   ",
                                          ".���-M230       ",
                                          ".���������� 9   ",
                                          ".���������� 10  ",
                                          ".���������� 11  ",
                                          ".��������-230 ! ",
                                          ".���������� 13  ",
                                          ".���������� 14  ",
                                          ".���-C4         ",
                                          ".���������� 16  ",
                                          ".���������� 17  ",
                                          ".���������� 18  ",
                                          ".���������� 19  ",
                                          ".���������� 20  ",
                                          ".���������� 21  ",
                                          ".���������� 22  ",
                                          ".���������� 23  ",
                                          ".��102          ",
                                          ".���������� 25  ",
                                          ".��301          "
                                      };

uchar const             mpbMaxLines[bMAXDEVICES+1] =
{ 1, 4, 4, 4, 4, 16, 64, 16, 4, 6, 1, 1, 4, 4, 1, 4, 4, 1, 1, 1, 1, 4, 4, 4, 1, 2, 2 };



bool    IsValidDevice(uchar  bDevice)
{
  ASSERT(bDevice <= bMAXDEVICES);

  switch (bDevice)
  {
    case 0:  return true;

#ifndef SKIP_A
    case 15:
    case 1:  return true;
#endif

#ifndef SKIP_B
    case 12:
    case 8:
    case 2:  return true;
#endif

#ifndef SKIP_C
    case 3:  return true;
#endif

#ifndef SKIP_P
    case 21: return true;
#endif

#ifndef SKIP_S
    case 24: return true;
#endif

#ifndef SKIP_U
    case 26: return true;
#endif

    default: return false;
  }
}



void    ShowDeviceName(uchar  bDevice)
{
  ASSERT(bDevice <= bMAXDEVICES);

  ShowLo( mpszDevices[bDevice] );
  (IsValidDevice(bDevice)) ? (szLo[15] = '+') : (szLo[15] = '-');
}
