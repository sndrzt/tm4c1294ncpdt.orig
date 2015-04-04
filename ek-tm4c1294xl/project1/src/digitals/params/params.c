/*------------------------------------------------------------------------------
PARAMS.C

 ���������� ���������
------------------------------------------------------------------------------*/

#include    "../../main.h"
#include    "../../flash/files.h"
#include    "params.h"



file const              flEnblParams = {FLS_ENBL_PARAMS, &boEnblParams, sizeof(boolean)};
file const              flMntParams = {FLS_MNT_PARAMS, &boMntParams, sizeof(boolean)};



void    InitParams(void)
{
  LoadFile(&flEnblParams);
  LoadFile(&flMntParams);
}


void    ResetParams(void)
{
  boEnblParams = FALSE;
  SaveFile(&flEnblParams);

  boMntParams = FALSE;
  SaveFile(&flMntParams);
}

/*
#include        "main.h"
#include        "xdata.h"
#include        "x_params.h"
#include        "display.h"



param           code    mppaParamMap[bPARAM_BLOCK] =
{
  PAR_P , PAR_P1 , PAR_P2 , PAR_P3 ,
  PAR_Q , PAR_Q1 , PAR_Q2 , PAR_Q3 ,
  PAR_S , PAR_S1 , PAR_S2 , PAR_S3 ,
  PAR_U , PAR_U1 , PAR_U2 , PAR_U3 ,
  PAR_I , PAR_I1 , PAR_I2 , PAR_I3 ,
  PAR_C , PAR_C1 , PAR_C2 , PAR_C3 ,
  PAR_F , PAR_F1 , PAR_F2 , PAR_F3 ,
  0
};



void    ResetParams(void)
{
uint    i;

  for (i=0; i<wPARAMS; i++) 
  {
    mpreParamDiv[i] = 1;
    mpboEnblPar[i] = boTrue;
  }
}



void    LoadCurrParam(uint  iwPar)
{
  diCurr = mpdiParam[ iwPar ];
}



#ifndef MODBUS
bit     TrueParam(void)
{
  return(1);
}
#endif



bit     TrueParamLine(uchar  ibLine)
{
  switch (ibLine)
  {
    case PAR_P  :
    case PAR_P1 :
    case PAR_P2 :
    case PAR_P3 :

    case PAR_Q  :
    case PAR_Q1 :
    case PAR_Q2 :
    case PAR_Q3 :

    case PAR_S  :
    case PAR_S1 :
    case PAR_S2 :
    case PAR_S3 :

    case PAR_U  :
    case PAR_U1 :
    case PAR_U2 :
    case PAR_U3 :

    case PAR_I  :
    case PAR_I1 :
    case PAR_I2 :
    case PAR_I3 :

    case PAR_C  :
    case PAR_C1 :
    case PAR_C2 :
    case PAR_C3 :

    case PAR_F  :
    case PAR_F1 :
    case PAR_F2 :
    case PAR_F3 : return(1); 

    default:      return(0);
   }
}



void    SetParam(uint  iwPar)
{
  mpdiParam[iwPar] = diT;
}



uchar   GetParamPort(uint  iwPar)
{
  return( mpdiParam[iwPar].ibPort );
}


uchar   GetParamPhone(uint  iwPar)
{
  return( mpdiParam[iwPar].ibPhone );
}


uchar   GetParamDevice(uint  iwPar)
{
  return( mpdiParam[iwPar].bDevice );
}


uchar   GetParamAddress(uint  iwPar)
{
  return( mpdiParam[iwPar].bAddress );
}


uchar   GetParamLine(uint  iwPar)
{
  return( mpdiParam[iwPar].ibLine );
}



void    ShowParam(uint  iwPar)
{
  sprintf(szLo,"%1bu.%02bu.%02bu.%03bu.%02bu  ",
               GetParamPort(iwPar)+1,
               GetParamPhone(iwPar),
               GetParamDevice(iwPar),
               GetParamAddress(iwPar),
               GetParamLine(iwPar));

  sprintf(szHi+13,"%03u",iwPar+1);
  (mpboEnblPar[iwPar] == boTrue) ? (szHi[12] = '+') : (szHi[12] = '-');
}
*/
