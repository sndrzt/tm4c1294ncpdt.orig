/*------------------------------------------------------------------------------
EXTENDED_4T,C

 �������� ��������� �� ������ ������� �� ������ � ���������� �� ������� (o���� �86� �� 07.04.2013)
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_realtime.h"
#include "../../digitals/digitals.h"
#include "../../digitals/digitals_display.h"
#include "../../digitals/digitals_messages.h"
#include "../../devices/devices.h"
#include "../../sensors/automatic_p.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "automatic_4t.h"
#include "extended_4t.h"



file const              flExt4TFlag = {EXT_4T_FLAG, &fExt4TFlag, sizeof(bool)};
file const              flExt4TMonths = {EXT_4T_MONTHS, &bExt4TMonths, sizeof(uchar)};


//                                         0123456789ABCDEF
static char const       szExtended4T[]  = "����� ������: 6 ";



bool SaveExt4TValues(uchar  ibMon)
{
  return SaveBuff(EXT_4T_MON_VALUES + ibMon*VALUE4T_CAN_PAGES, &mpCntMonCan4T, sizeof(mpCntMonCan4T));
}


bool LoadExt4TValues(uchar  ibMon)
{
  return LoadBuff(EXT_4T_MON_VALUES + ibMon*VALUE4T_CAN_PAGES, &mpCntMonCan4T, sizeof(mpCntMonCan4T));
}



void    InitExtended4T(void) 
{
  LoadFileBoolean(&flExt4TFlag, false);
  LoadFileChar(&flExt4TMonths, 1, 12, 4);
}


void    ResetExtended4T(bool  fFull)
{ 
  if (fFull)
  {
    fExt4TFlag = false;
    SaveFile(&flExt4TFlag);

    bExt4TMonths = 4;
    SaveFile(&flExt4TMonths);
  }


  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4TValues(m);
  }
}



void    ResetExtended4T_Full(void) 
{ 
  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));

  uchar m;
  for (m=0; m<bMONTHS; m++)
  {
    SaveExt4TValues(m);
  }
}


void    ResetExtended4T_Custom(uchar  ibCanMin, uchar  ibCanMax, uchar  ibMonMin, uchar  ibMonMax)
{ 
  uchar m;
  for (m=ibMonMin; m<=ibMonMax; m++)
  {
    LoadExt4TValues(m);

    uchar c;
    for (c=ibCanMin; c<=ibCanMax; c++)
    {
      memset(&mpCntMonCan4T[c], 0, sizeof(value4t));
    }

    SaveExt4TValues(m);
  }
}



void    NextMonExtended4T(void) 
{
  memset(&mpCntMonCan4T, 0, sizeof(mpCntMonCan4T));
  SaveExt4TValues(ibHardMon);
}



static bool MakeDevices(uchar  ibMon, uchar  ibTrf)
{
  memset(&mpboChannelsA, 0, sizeof(mpboChannelsA));  

  status bStatus = ReadCntMonCanTariff(ibMon, ibDig, ibTrf);

  if ((bStatus == ST4_BADDIGITAL) || (bStatus == ST4_NOTSUPPORTED) || (bStatus == ST4_NOTPRESENTED)) 
  { 
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == true)
      {
        value4t vl = mpCntMonCan4T[c];

        vl.bStatus = bStatus;
        vl.mpdbValuesT[ibTrf] = 0;
        vl.tiUpdate = *GetCurrTimeDate();

        mpCntMonCan4T[c] = vl;
      }
    }

    if (bStatus == ST4_BADDIGITAL) { ShowLo(szNoLink); DelayInf(); }
    return false;
  }
  else
  { 
    LoadCurrDigital(ibDig);

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      LoadPrevDigital(c);
      if (CompareCurrPrevLines(ibDig, c) == true)
      {
        if (mpboChannelsA[diPrev.ibLine] == true)
        {
          value4t vl = mpCntMonCan4T[c];

          vl.bStatus = ST4_OK;
          vl.mpdbValuesT[ibTrf] = mpdbChannelsC[diPrev.ibLine];
          vl.tiUpdate = *GetCurrTimeDate();

          mpCntMonCan4T[c] = vl;
        }
      }
    }

    return true;
  }
}



void    MakeExtended4T(void)
{
  if ((fExt4TFlag == true) && (mpfExt4EnblCan[ibDig] == true))
  {
    ShowHi(szExtended4T); 
    Clear(); sprintf(szLo+3,"�������: %u", bExt4TMonths);
    DelayInf();

    ibMonthP = 0xFF;

    uchar m;
    for (m=0; m<bExt4TMonths; m++)
    {
      if (fKey == true) break;

      uchar ibMon = (bMONTHS + ibHardMon - m) % bMONTHS;
      LoadExt4TValues(ibMon);

      status bStatus = mpCntMonCan4T[ibDig].bStatus;
      if ((bStatus == ST4_OK) || (bStatus == ST4_NOTPRESENTED)) continue;

      uchar t;
      for (t=0; t<bTARIFFS; t++)
      {
        Clear(); sprintf(szLo+3,"�����: %-2u",ibMon+1); sprintf(szLo+14,"T%u",t+1); DelayInf();

        if (MakeDevices(ibMon, t) == 0) break;
        ibMonthP = ibMon;
      }

      SaveExt4TValues(ibMon);
    }

    ShowCanalNumber(ibDig);
    Clear();
  }
}
