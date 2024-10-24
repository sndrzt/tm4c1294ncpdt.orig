/*------------------------------------------------------------------------------
U_CONFIG!C


------------------------------------------------------------------------------*/


#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_digitals0.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_phones.h"
#include "../../memory/mem_params.h"
#include "../../memory/mem_uni.h"
#include "../../memory/mem_correct1.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../digitals/digitals.h"
#include "../../digitals/devices.h"
#include "../../digitals/serials.h"
#include "../../hardware/memory.h"
#include "../../time/timedate.h"
#include "../../time/rtc.h"
#include "../../time/correct1.h"
#include "../../access.h"
#include "../../groups.h"
#include "response_uni.h"
#include "uni_utils.h"
#include "u_config.h"



static char const       mpbDevicesMask[bMAXDEVICES][8] =
                        {
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 1
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 2
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x70,0xFF}, // 3
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 4
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 5
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 6
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 7
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 8
                          {0x00,0x00,0x00,0x00,0x00,0x3F,0x77,0x77}, // 9
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 10
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 11
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF}, // 12
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 13
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 14
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 15
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 16
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 17
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 18
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 19
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 20
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x0F,0xFF}, // 21
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 22
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 23
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // 24
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0xFF}, // 25
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x07}, // 26
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08}, // 27
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0x00,0x07}, // 28
                          {0x00,0x00,0x00,0x00,0x00,0x40,0x80,0x88}, // 29
                          {0x00,0x00,0x00,0x00,0x00,0x7F,0xF0,0xFF}, // 30
                          {0x00,0x00,0x00,0x00,0x00,0x3F,0x77,0x77}, // 31
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08}, // 32
                          {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08}, // 33
                        };



bool    IsDeviceAdded(uchar  ibDev)
{
  if (GetDigitalDevice(ibDev) == 0) return 1;

  if (cbDevicesUni > 0)
  {
   uchar i;
   for (i=0; i<cbDevicesUni; i++)
    {
      if( (mpdiDevicesUni[i].ibPort   == GetDigitalPort(ibDev)) &&
          (mpdiDevicesUni[i].ibPhone  == GetDigitalPhone(ibDev)) &&
          (mpdiDevicesUni[i].bDevice  == GetDigitalDevice(ibDev)) &&
          (mpdiDevicesUni[i].bAddress == GetDigitalAddress(ibDev)) ) return 1;
    }
  }

  return 0;
}


void    MakeDevicesUni(void)
{
  memset(&mpdiDevicesUni, 0, sizeof(mpdiDevicesUni));
  memset(&mpibFirstCanalsUni, 0, sizeof(mpibFirstCanalsUni));
  cbDevicesUni = 0;

  uchar c;
  for (c=0; c<bCANALS; c++)
  {
    if (IsDeviceAdded(c) == 0)
    {
       mpdiDevicesUni[cbDevicesUni] = mpdiDigital[c];
       mpibFirstCanalsUni[cbDevicesUni] = c;
       cbDevicesUni++;
    }
  }
}


uchar   GetUsedCanals(void)
{
uchar   i=0;

  uchar c;
  for (c=0; c<bCANALS; c++)
    if (GetDigitalDevice(c) != 0)
      i++;

  return i;
}


uchar   GetUsedGroups(void)
{
uchar   i=0;

  uchar g;
  for (g=0; g<bGROUPS; g++)
    if (GetGroupsSize(g) > 0)
      i++;

  return i;
}


uchar   GetCanalsCount(uchar  ibDev)
{
uchar   i,j;

  j = 0;
  for (i=0; i<bCANALS; i++)
  {
    if( (mpdiDevicesUni[ibDev].ibPort   == GetDigitalPort(i)) &&
        (mpdiDevicesUni[ibDev].ibPhone  == GetDigitalPhone(i)) &&
        (mpdiDevicesUni[ibDev].bDevice  == GetDigitalDevice(i)) &&
        (mpdiDevicesUni[ibDev].bAddress == GetDigitalAddress(i)) ) j++;
  }

  return j;
}


uchar   GetFirstCanalsNumber(uchar  ibDev)
{
  uchar i;
  for (i=0; i<bCANALS; i++)
  {
    if( (mpdiDevicesUni[ibDev].ibPort   == GetDigitalPort(i)) &&
        (mpdiDevicesUni[ibDev].ibPhone  == GetDigitalPhone(i)) &&
        (mpdiDevicesUni[ibDev].bDevice  == GetDigitalDevice(i)) &&
        (mpdiDevicesUni[ibDev].bAddress == GetDigitalAddress(i)) ) return i + 1;
  }

  return 0;
}


uchar   GetDeviceNumber(uchar  ibCan)
{
  if (cbDevicesUni > 0)
  {
    uchar i;
    for (i=0; i<cbDevicesUni; i++)
    {
      if( (mpdiDevicesUni[i].ibPort   == GetDigitalPort(ibCan)) &&
          (mpdiDevicesUni[i].ibPhone  == GetDigitalPhone(ibCan)) &&
          (mpdiDevicesUni[i].bDevice  == GetDigitalDevice(ibCan)) &&
          (mpdiDevicesUni[i].bAddress == GetDigitalAddress(ibCan)) ) return i + 1;
    }
  }

  return 0;
}



void    GetCorrectUni(void)
{
  InitPop(6);

  time ti;
  Pop(&ti, sizeof(time));

  if (ValidTimeDate(ti) == true)
  {
    if ((tiCurr.bDay   != ti.bDay)   ||
        (tiCurr.bMonth != ti.bMonth) ||
        (tiCurr.bYear  != ti.bYear))
      Result2(bUNI_BADTIME);
    else
    if ((tiCurr.bHour*2 + tiCurr.bMinute/30) != (ti.bHour*2 + ti.bMinute/30))
      Result2(bUNI_BADTIME);
    else
    {
      SetCurrTime_Full(ti, EVE_UNI_CORRECT);
      Result2(bUNI_OK);
    }
  }
  else Result2(bUNI_BADDATA);
}



void    GetCorrectionsUni(void)
{
  InitPushUni();

  uchar c;
  for (c=bInBuff6; c<bInBuff6+bInBuff7; c++)
  {
    if (c == 0)
      PushIntBig((sint)(Correct1.mpwPosValueCurr[0] - Correct1.mpwNegValueCurr[0]));
    else if (c == 1)
      PushIntBig((sint)(Correct1.mpwPosValuePrev[0] - Correct1.mpwNegValuePrev[0]));
    else
      PushIntBig(0);
  }

  Output2(2*(bInBuff7-bInBuff6));
}



void    GetOpenUni(void)
{
uchar   i;

  memset(&mpbPassTwo, 0, sizeof(mpbPassTwo));

  for (i=0; i<8; i++)
    mpbPassTwo[i] = InBuff(6+i) - 0x30;

  if ((memcmp(mpbPassOne, mpbPassTwo, 8) == 0) || SuperUser())
  {
    SetDelayUni();
    Result2(bUNI_GOODPASSWORD);
  }
  else
  {
    Result2(bUNI_BADPASSWORD);
  }
}



void    GetConfigUni(void)
{
  MakeDevicesUni();

  InitPushUni();

  Push("���+2 ", 6);
  PushCharDec2Txt(GetBuildDate_Day());
  PushChar('.');
  PushCharDec2Txt(GetBuildDate_Month());
  PushChar('.');
  PushCharDec2Txt(GetBuildDate_Year());
  PushChar(' ');

  PushCharDec2Txt(bMAXVERSION);
  PushChar('.');
  PushCharDec2Txt(bMINVERSION);
  PushChar('.');
  PushCharDec2Txt(GetBuildNumber() / 100);
  PushCharDec2Txt(GetBuildNumber() % 100);
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');
  PushChar(' ');

  Push(szObjectName, 32);

  PushIntBig(wPrivate / 0x10000);
  PushIntBig(wPrivate % 0x10000);

  PushIntBig(GetRomChecksum());
  PushIntBig(GetUsedCanals());
  PushIntBig(GetUsedGroups());
  PushIntBig(bTARIFFS);
  PushIntBig(bMAXDEVICES);
  PushIntBig(cbDevicesUni);
  PushIntBig(wOUTBUFF_SIZE);

  Output2(32+32+4+2+2+2+2+2+2+2);
}



void    GetSensorsUni(void)
{
  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bMAXDEVICES)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > bMAXDEVICES + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      PushIntBig(c);

      uchar i;
      for (i=1; i<16; i++)
        PushChar(mpszDevices[c][i]);

      PushChar(0);
    }
    Output2((uint)(2+16)*bInBuff9);
  }
}



void    GetDigitalsUni(void)
{
  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > cbDevicesUni)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > cbDevicesUni + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();
    uint wSize = 0;

    uchar d;
    for (d=bInBuff7; d<bInBuff7+bInBuff9; d++)
    {
      wSize += PushIntBig(d);

      wSize += PushIntBig(mpdiDevicesUni[d-1].bDevice);

      uchar c = mpibFirstCanalsUni[d-1];
      wSize += PushLongBig(mdwSerialValues[c]);

      wSize += PushIntBig(mpdiDevicesUni[d-1].bAddress);
      wSize += PushIntBig(GetCanalsCount(d-1));
      wSize += PushIntBig(wHOURS);
      wSize += PushIntBig(GetFirstCanalsNumber(d-1));

      wSize += PushChar(0);
      wSize += PushChar(0);
      wSize += PushChar(0);
      wSize += PushChar(0);
      wSize += PushChar(0);
      wSize += PushChar(0);

      wSize += PushChar(0);

      uchar i = 0;
      if (boEnblCurrent == true) i |= 0x01;
      i |= 0x02;
      if (boEnblProfile == true) i |= 0x04;
      if (boParamsFlag == true) i |= 0x08;
      wSize += PushChar(i);

      uchar j = mpdiDevicesUni[d-1].bDevice - 1;
      for (i=0; i<8; i++)
      {
        wSize += PushChar(mpbDevicesMask[j][i]);
      }

      if (mpdiDevicesUni[d-1].ibPhone == 0)
      {
        for (i=0; i<32; i++)
        {
          wSize += PushChar(0);
        }
      }
      else
      {
        wSize += Push(&mpphPhones[ mpdiDevicesUni[d-1].ibPhone - 1 ].szLine, 13);
        for (i=0; i<32-13; i++)
        {
          wSize += PushChar(0);
        }
      }
    }

    Output2(wSize);
  }
}



void    GetSerialsUni(void)
{
  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > cbDevicesUni)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > cbDevicesUni + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();
    uint wSize = 0;

    uchar d;
    for (d=bInBuff7; d<bInBuff7+bInBuff9; d++)
    {
      uchar c = mpibFirstCanalsUni[d-1];
      wSize += PushLongBig(mdwSerialValues[c]);

      ulong dw;
      if (mfSerialFlags[c] == false)
        dw = 0xFFFFFFFF;
      else if (mpboEnblCan[c] == false)
        dw = 0xFFFFFFFE;
      else
        dw = DateToLongUni(&mtiSerialTimes[c]);

      wSize += PushLongBig(dw);
    }

    Output2(wSize);
  }
}



void    GetCanalsUni(void)
{
  MakeDevicesUni();

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bCANALS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > bCANALS + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();

    uchar c;
    for (c=bInBuff7; c<bInBuff7+bInBuff9; c++)
    {
      PushIntBig(c);

      PushIntBig(GetDeviceNumber(c-1));
      PushIntBig(GetDigitalLine(c-1)+1);

      PushFloat(mpdbTransEng[c-1]);
      PushFloat(mpdbPulseHou[c-1]);
      PushFloat(mpdbLosse[c-1]);

      PushChar(GetDigitalLine(c-1));

      uchar g = 0;
      if (mpboEnblCan[c-1] != true) g |= 0x01;
      PushChar(g);

      Push(mpszCanalsName[c-1], 32);
    }
    Output2((uint)(2+2+2+4+4+4+1+1+32)*bInBuff9);
  }
}



void    GetGroupsUni(void)
{
uchar   i;

  if ((bInBuff6 != 0) || (bInBuff8 != 0))
    Result2(bUNI_BADDATA);
  else if (bInBuff7 > bGROUPS)
    Result2(bUNI_BADDATA);
  else if (bInBuff7+bInBuff9 > bGROUPS + 1)
    Result2(bUNI_BADDATA);
  else
  {
    InitPushUni();

    uchar g;
    for (g=bInBuff7-1; g<bInBuff7+bInBuff9-1; g++)
    {
      PushIntBig(g+1);

      uchar c;
      for (c=0; c<128-16; c++)
        PushChar(0);

      memset(&mpbGroupMaskUni, 0, sizeof(mpbGroupMaskUni));
      if (GetGroupsSize(g) > 0)
      {
        for (c=0; c<GetGroupsSize(g); c++)
        {
          i = GetGroupsNodeCanal(g, c);
          mpbGroupMaskUni[16-1 - (i / 4)] |= (0x01 << ((i % 4) * 2));

          if (GetGroupsNodeSign(g, c) == 1)
            mpbGroupMaskUni[16-1 - (i / 4)] |= (0x02 << ((i % 4) * 2));
        }
      }
      Push(mpbGroupMaskUni, sizeof(mpbGroupMaskUni));

      Push(mpszGroupsName[g], bNAME_SIZE);
    }

    Output2((uint)(2+128+32)*bInBuff9);
  }
}
