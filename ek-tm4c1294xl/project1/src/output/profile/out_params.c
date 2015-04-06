/*------------------------------------------------------------------------------
OUT_PARAMS.C


------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_ports.h"
#include        "../../memory/mem_digitals0.h"
#include        "../../memory/mem_realtime.h"
#include        "../../serial/ports.h"
#include        "../../realtime/realtime.h"
#include        "../../digitals/digitals.h"
#include        "../../digitals/digitals_pause.h"
#include        "../../digitals/digitals_messages.h"
#include        "../../digitals/params/params.h"
#include        "../../digitals/params/params2.h"
#include        "../../engine.h"
#include        "../../console.h"



void    OutGetParams100(void)
{
  if ((uint)100*bInBuff5 < wPARAMS)
  {
    InitPushCRC();
    Push(&mpdiParam[ (uint)100*bInBuff5 ],(uint)100*sizeof(digital));
    Output((uint)100*sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutGetParams(void)
{
  if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
  {
    InitPushCRC();
    Push(&mpdiParam[ bInBuff5*0x100 + bInBuff6 ],sizeof(digital));
    Output(sizeof(digital));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetParam(void)
{
  if (enGlobal != GLB_WORK)
  {
    if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
    {
      digital di;

      di.ibPort   = InBuff(7);
      di.ibPhone  = InBuff(8);
      di.bDevice  = InBuff(9);
      di.bAddress = InBuff(10);
      di.ibLine   = InBuff(11);

      if (TrueParam(&di) == 1)
      {
        mpdiParam[ bInBuff5*0x100 + bInBuff6 ] = di;
        LongResult(bRES_OK);
      }
      else Result(bRES_BADDATA);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}



void    OutGetParamDiv(void)
{
  if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
  {
    InitPushCRC();
    Push(&mpreParamDiv[bInBuff5*0x100 + bInBuff6], sizeof(real));
    Output(sizeof(real));
  }
  else Result(bRES_BADADDRESS);
}


void    OutSetParamDiv(void)
{
  if (enGlobal != GLB_WORK)
  {
    if (bInBuff5*0x100 + bInBuff6 < wPARAMS)
    {
      InitPop(7);
      mpreParamDiv[bInBuff5*0x100 + bInBuff6] = PopReal();
      LongResult(bRES_OK);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDREPROGRAM);
}


//      case bINQ_GETPARAMCURR:
void    OutGetParamCurr(void)
{
  if ((uint)10*bInBuff5 < wPARAMS)
  {
    SaveDisplay();
    ShowHi(szDirectParam); Clear();

    InitPushCRC();
    Push(&tiCurr, sizeof(time));

    boBeginParam = FALSE;

    bool fAlt = 1;
    uchar ibCan;
    for (ibCan=0; ibCan<10; ibCan++)
    {
      sprintf(szHi+13,"%03u",(uint)10*bInBuff5+ibCan+1);

      if (fAlt == 1)
      {
        if (mpboEnblPar[(uint)10*bInBuff5+ibCan] != TRUE)
          reBuffA = 0;
        else
        {
          uchar i = ibPort;
          fAlt = ReadParam((uint)10*bInBuff5+ibCan);
          ibPort = i;
        }
      }

      if (fAlt == 1)
        Push(&reBuffA, sizeof(real));
      else
      {
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
    }

    Output(sizeof(time)+(uint)10*sizeof(real));
    NextPause();                                      // внимание !

    LoadDisplay();
  }
  else Result(bRES_BADADDRESS);
}


//      case bINQ_GETPARAMBUFF:
void    OutGetParamBuff(void)
{
  if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
  {
    InitPushCRC();

    Push(&mptiParBuff[ (uint)10*bInBuff5 ],              (uint)10*bInBuff6*sizeof(time));
    Push(&mpreParBuff[ ibSoftTim ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(real));

    Output((uint)10*bInBuff6*(sizeof(time)+sizeof(real)));
  }
  else Result(bRES_BADADDRESS);
}


//      case bINQ_GETPARAMFULL:
void    OutGetParamFull(void)
{
  if (enGlobal != GLB_PROGRAM)
  {
    if (((uint)10*bInBuff5 < wPARAMS) && ((uint)10*bInBuff6 <= wPARAMS))
    {
      if (bInBuff7*0x100+bInBuff8 < wTIMES)
      {
        if (LoadParTim((wTIMES + iwHardTim - (bInBuff7*0x100+bInBuff8)) % wTIMES) == 1)
        {
          InitPushCRC();

          PushInt(iwHardTim);
          PushInt(wTIMES);
          PushChar(boMntParams);
          Push(&tiCurr, sizeof(time));

          Push(&mpreParBuff[ PrevSoftTim() ][ (uint)10*bInBuff5 ], (uint)10*bInBuff6*sizeof(real));

          Output(5+sizeof(time)+(uint)10*bInBuff6*sizeof(real));
        }
        else Result(bRES_BADFLASH);
      }
      else Result(bRES_BADADDRESS);
    }
    else Result(bRES_BADADDRESS);
  }
  else Result(bRES_NEEDWORK);
}



//      case bINQ_RESETDIVIDERS:
void    OutGetParamDivs(void)
{
  if (enGlobal != GLB_WORK)
  {
    MakeAllDividers();
    Result(bRES_OK);
  }
  else Result(bRES_NEEDREPROGRAM);
}


//      case bINQ_GETPARAMDIG:
void    OutGetParamDig(void)
{
  if (bInBuff5 >= bCANALS)
    Result(bRES_BADADDRESS);
  else if ((GetDigitalPhone(bInBuff5) != 0) || (GetDigitalDevice(bInBuff5) == 0))
    Result(bRES_BADDIGITAL);
  else
  {
    SaveDisplay();
    ShowHi(szDirectParam); Clear();

    InitPushCRC();
    Push(&tiCurr, sizeof(time));

    boBeginParam = FALSE;

    bool fAlt = 1;
    uchar ibCan;
    for (ibCan=0; ibCan<bPARAM_BLOCK; ibCan++)
    {
      sprintf(szHi+14,"%2u",ibCan+1);

      if (fAlt == 1)
      {
        digital diT;
        diT.ibPort   = mpdiDigital[bInBuff5].ibPort;
        diT.ibPhone  = mpdiDigital[bInBuff5].ibPhone;
        diT.bDevice  = mpdiDigital[bInBuff5].bDevice;
        diT.bAddress = mpdiDigital[bInBuff5].bAddress;
        diT.ibLine   = mppaParamMap[ibCan];

        mpdiParam[wPARAMS-1] = diT;

        mpboEnblPar[wPARAMS-1] = TRUE;
        MakeDividers(wPARAMS-1);

        if (boParamDivider == TRUE)
        {
          wBuffD = GetParamIndex();
          if (wBuffD != 0xFFFF)
            mpreParamDiv[wPARAMS-1] = mpreParamDiv[wBuffD];
        }

        if (mpboEnblPar[wPARAMS-1] != TRUE)
          reBuffA = 0;
        else
        {
          ibDig = bInBuff5;

          uchar i = ibPort;
          fAlt = ReadParam(wPARAMS-1);
          ibPort = i;
        }
      }

      if (fAlt == 1)
        Push(&reBuffA, sizeof(real));
      else
      {
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
        PushChar(0xFF);
      }
    }

    Output(sizeof(time)+bPARAM_BLOCK*sizeof(real));
    NextPause();                                      // внимание !

    LoadDisplay();
  }
}
