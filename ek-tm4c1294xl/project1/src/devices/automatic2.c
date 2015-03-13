/*------------------------------------------------------------------------------
AUTOMATIC2.C
              

------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_digitals0.h"
#include        "../display/display.h"
#include        "../time/timedate.h"
#include        "../digitals/digitals.h"
#include        "automatic_b.h"
/*
#include        "xdata.h"
#include        "display.h"
#include        "timedate.h"
#include        "keyboard.h"
#include        "engine.h"
#include        "nexttime.h"
#include        "general.h"
#include        "device_a.h"
#include        "device_b.h"
#include        "device_c.h"
#include        "device_d.h"
#include        "device_e.h"
#include        "device_f.h"
#include        "device_g.h"
#include        "device_g2.h"
#include        "device_h.h"
#include        "device_h2.h"
#include        "device_i.h"
#include        "device_k.h"
#include        "device_m.h"
#include        "device_n.h"
#include        "device_o.h"
#include        "device_p.h"
#include        "device_z.h"
#include        "_automatic1.h"
#include        "automatic_k.h"
#include        "automatic_p.h"
#include        "automatic_q.h"
#include        "automatic_r.h"
#include        "automatic_s.h"
#include        "automatic_t.h"
#include        "automatic_u.h"
#include        "queries.h"
#include        "energy.h"
#include        "delay.h"
#include        "esc.h"
#include        "ports.h"
#include        "sensors.h"



#ifndef SKIP_A

// ������ �������� ��������� ��������� ��� ��������� ���-4��
bit     ReadSensorA(void)                 
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceA() == 0) return(0);


  if (QueryEnergyA_Full(0,100) == 0) return(0);

  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    reBuffA = *PGetCanLong(mpdwChannelsA, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = reBuffB*coEnergy.dwBuff;

  return(1);
}

#endif



#ifndef SKIP_B

// ������ �������� ��������� ��������� ��� ��������� ��������-230
bit     ReadSensorB(void)                 
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return(0);


  if (QueryEnergyB_Full(0,100) == 0) return(0);

  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    reBuffA = *PGetCanLong(mpdwChannelsA, i) * reBuffB * 2;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = reBuffB*coEnergy.dwBuff * 2;

  return(1);
}

#endif



#ifndef SKIP_C

// ������ �������� ��������� ��������� ��� ��������� ��-301
bit     ReadSensorC(void)                 
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceC() == 0) return(0);


  DelayOff();
  QueryEnergyAbsC();

  if (RevInput() != SER_GOODCHECK) return(0);
  ShowPercent(100);

  ReadEnergyC();


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    reBuffA = *PGetCanLong(mpdwChannelsA, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = reBuffB*coEnergy.dwBuff;

  return(1);
}

#endif



#ifndef SKIP_D

// ������ �������� ��������� ��������� ��� ��������� ABB �����
bit     ReadSensorD(void)                 
{
  Clear();
  if (OpenDeviceD() == 0) return(0);

  
  if (ReadAllEnergyD() == 0) return(0);

  QueryCloseD(0);


  MakeEnergyD();

  return(1);
}

#endif



#ifndef SKIP_E

bit     ReadSensorE(uchar  chEsc, bit  fOpen)                
{
uchar   i;

  if (fOpen == 1)
    if (OpenDeviceE() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
    PushChar(0x1B);          
    PushChar(chEsc);            

    Query(64+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(85);


  InitPop(0); 

  for (i=0; i<16; i++)
  {
    coFloat.mpbBuff[0] = PopChar();
    coFloat.mpbBuff[1] = PopChar();
    coFloat.mpbBuff[2] = PopChar();
    coFloat.mpbBuff[3] = PopChar();

    ToReal();
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;                          
  }


  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_F

// ������ �������� ��������� ��������� ��� ��������� ���+2
bit     ReadSensorF(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryRealExtendedF(bEXT_GETSIMPLE_ESC_S);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadRealExtendedF();

  return(1);
}

#endif



#ifndef SKIP_G

// ������ �������� ��������� ��������� ��� ��������� �������-9 a
bit     ReadSensorG(void)                 
{
uchar   i;

  Clear();
  if (OpenDeviceG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyAbsG();                      // ������ ����������� �������

    if (CodInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadEnergyG();

  reBuffB = *PGetCanReal(mpreTransCnt,ibDig);
  reBuffA *= reBuffB;

  return(1);
}

#endif


#ifndef SKIP_H

// ������ �������� ��������� ��������� ��� ��������� �������-9
bit     ReadSensorH(void)                 
{
uchar   i,j;

  Clear();
  if (OpenDeviceH() == 0) return(0);


  for (i=0; i<3; i++) mpreCodEng30[i] = 0;


  for (j=0; j<bTARIFFS; j++)                    // �������� �� ���� ������� (� ��������: 8)
  {
    if (fKey == 1) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsH(j);

      ShowPercent(60+j);

      if (CodInput() != SER_GOODCHECK) continue; else break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      if (ChecksumH(14) == 0) { sprintf(szLo," ������ CRC: H5 "); Delay(1000); return(0); }

      InitPop(3);
      for (i=0; i<3; i++)
      {
        PopLongH();
        reBuffA = (real)dwBuffC/1000;

        mpreCodEng30[i] += reBuffA;
      }
    }
  }

  ShowPercent(100);


  reBuffB = *PGetCanReal(mpreTransCnt,ibDig);

  for (i=0; i<1; i++) 
  {
    reBuffA = mpreCodEng30[0] * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_I

// ������ �������� ��������� ��������� ��� ��������� ���-2�.07
bit     ReadSensorI(void)                 
{
uchar   i,j;

  Clear();

  reBuffB = 0;

  for (j=0; j<bTARIFFS; j++)                    // �������� �� ���� ������� (� ��������: 4)
  {
    if (fKey == 1) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsI(j);

      ShowPercent(60+j);

      if (TxtInput() != SER_GOODCHECK) 
        continue;
      else 
        break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      ReadEnergyI();
      reBuffB += reBuffA;
    }
  }

  ShowPercent(100);


  reBuffA = reBuffB * *PGetCanReal(mpreTransCnt,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;     


  reBuffA = *PGetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_K

// ������ �������� ��������� ��������� ��� ��������� ��6850�
bit     ReadSensorK(uchar  bMaxLines)                 
{
uchar   i,j;

  Clear();

  for (j=0; j<bMaxLines; j++) 
  {
    for (i=0; i<bMINORREPEATS; i++)
    {
      QueryCloseK();
      QueryEnergyAbsK(j);

      if (BccInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (i == bMINORREPEATS) return(0);
    ShowPercent(50+j);

    ReadEnergyK(j);
  }


  QueryCloseK();


  reBuffB = *PGetCanReal(mpreTransCnt,ibDig);

  for (i=0; i<bMaxLines; i++) 
  {
    reBuffA = *PGetCanReal(mpreChannelsB, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_M

// ������ �������� ��������� ��������� ��� ��������� ��������-200
bit     ReadSensorM(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsM();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyM();



  reBuffA = *PGetCanReal(mpreChannelsB, 0) * *PGetCanReal(mpreTransCnt,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;     


  reBuffA = *PGetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_N

// ������ �������� ��������� ��������� ��� ���������������� ��-1.4
bit     ReadSensorN(void)
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyN();


  reBuffA = *PGetCanLong(mpdwChannelsA, 0) * *PGetCanReal(mpreValueCntHou,ibDig);
  reBuffA += *PGetCanReal(mpreCount,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;     


  reBuffA = *PGetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_O

// ������ �������� ��������� ��������� ��� ��������� ���-4��.04
bit     ReadSensorO(void)                 
{
uchar   i,j;

  Clear();

  reBuffB = 0;

  for (j=0; j<bTARIFFS; j++)                    // �������� �� ���� ������� (� ��������: 4)
  {
    if (fKey == 1) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsO(j);

      ShowPercent(60+j);

      if (TxtInput() != SER_GOODCHECK) 
        continue;
      else 
        break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      ReadEnergyO();
      reBuffB += reBuffA;
    }
  }

  ShowPercent(100);


  reBuffA = reBuffB * *PGetCanReal(mpreTransCnt,ibDig);
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;     


  reBuffA = *PGetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_P

bit     ReadSensorP(void)
{
uchar   i;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  if (ReadKoeffDeviceP() == 0) return(0);

  if (QueryEnergyP_Full(0) == 0) return(0);
  if (QueryEnergyP_Full(1) == 0) return(0);

  QueryCloseP();


  reBuffB = mpreTransCnt[ibDig];
  for (i=0; i<16; i++) 
  {
    mpreChannelsB[i] *= reBuffB;
  }

  for (i=0; i<4; i++) 
  {
    if (mpbMappingEls[i] >= 16)
      mpreChannelsEls[i] = 0;
    else
      mpreChannelsEls[i] = mpreChannelsB[mpbMappingEls[i]];
  }

  for (i=0; i<4; i++) 
  {
    mpreChannelsB[i] = mpreChannelsEls[i];
    mpboChannelsA[i] = boTrue;
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];

  return(1);
}

#endif



#ifndef SKIP_A

//  ������ �������� �������/���� ��� ��������� ���-4��
bit     ReadTimeDateA(void)                 
{
uchar   i;

  Clear();

  if (QueryOpenA_Full(25) == 0) return(0);

  if (QueryTimeAltA_Full(75) == 0) return(0);

  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif
*/


#ifndef SKIP_B

//  ������ �������� �������/���� ��� ��������� ��������-230
bool    ReadTimeDateB(void)
{
uchar   i;

  Clear();

  if (QueryOpenB_Full(25) == 0) return(0);

  if (QueryTimeAltB_Full(75) == 0) return(0);

  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif


/*
#ifndef SKIP_C

//  ������ �������� �������/���� ��� ��������� CC-301
bit     ReadTimeDateC(void)                 
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeC();

    if (RevInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeAltC();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_D

// ������ �������� �������/���� ��� ��������� ABB �����
bit     ReadTimeDateD(void)                 
{
uchar   i;

  Clear();
  if (OpenDeviceD() == 0) return(0);

  
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeD();

  QueryCloseD(0);


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;       

  return(1);
}

#endif



#ifndef SKIP_E

// ������ �������� �������/���� ��� ��������� ���-2
bit     ReadTimeDateE(void)                
{
uchar   i;

  if (OpenDeviceE() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush();
    PushChar(0x1B);          
    PushChar('T');            

    Query(6+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);


  ReadTimeAltE();


  tiChannelC = tiAlt;
  for (i=0; i<16; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_F

// ������ �������� �������/���� ��� ��������� ���+2
bit     ReadTimeDateF(void)                
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryTimeF();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadTimeAltF();


  tiChannelC = tiAlt;
  for (i=0; i<bCANALS; i++) mpboChannelsA[i] = boTrue;       

  return(1);
}

#endif



#ifndef SKIP_G

//  ������ �������� �������/���� ��� ��������� �������-9 a
bit     ReadTimeDateG(void)                 
{
uchar   i;

  Clear();
  if (OpenDeviceG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeG();

    if (CodInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadTimeAltG();


  tiChannelC = tiAlt;
  for (i=0; i<6; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_H

//  ������ �������� �������/���� ��� ��������� �������-9
bit     ReadTimeDateH(void)                 
{
uchar   i;

  Clear();
  if (OpenDeviceH() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeH();

    if (CodInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadTimeAltH();


  tiChannelC = tiAlt;
  for (i=0; i<6; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_I

//  ������ �������� �������/���� ��� ��������� ���-2�.07
bit     ReadTimeDateI(void)                 
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeI();

    if (TxtInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeAltI();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_K

//  ������ �������� �������/���� ��� ��������� ��6850�
bit     ReadTimeDateK(void)                 
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryTimeK();

    if (BccInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(25);

  ReadTimeAltK();


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryDateK();

    if (BccInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadDateAltK();


  QueryCloseK();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_O

//  ������ �������� �������/���� ��� ��������� ���-4��.04
bit     ReadTimeDateO(void)                 
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeO();

    if (TxtInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ReadTimeAltO();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_P

bit     ReadTimeDateP(void)
{
uchar   i;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadTimeAltP();
  QueryCloseP();


  tiChannelC = tiAlt;
  for (i=0; i<4; i++) mpboChannelsA[i] = boTrue;       

  return(1);
}

#endif



#ifndef SKIP_Z

//  ������ �������� �������/����
bit     ReadTimeDateZ(void)                 
{
uchar   i;

  Clear();

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTimeZ();

    if (ZetInput() != SER_GOODCHECK) 
      continue;
    else 
      break;
  }

  if (i == bMINORREPEATS) return(0);


  ReadTimeAltZ();

  tiChannelC = tiAlt;
  mpboChannelsA[0] = boTrue;     

  return(1);
}

#endif



#ifndef SKIP_A

// ������ �������� ��������� ��������� �� ������� ��� �������� ���-4��
bit     ReadCntMonCanA(uchar  ibMonth)                 
{ 
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceA() == 0) return(0);


  if (QueryTimeAltA_Full(76) == 0) return(0);

  if (tiAlt.bMonth == ibMonth+1)        // ��������� ��������� �� ������ �������� ������
  {
    if (QueryEnergyA_Full2(0x40,98) == 0) return(0);
    for (i=0; i<4; i++)
    {
      dwBuffC = *PGetCanLong(mpdwChannelsA, i);
      SetCanLong(mpdwChannelsB, i);
    }

    if (QueryEnergyA_Full2(0,99) == 0) return(0);             
    for (i=0; i<4; i++)
    {
      dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
      dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

      SetCanLong(mpdwChannelsB, i);
    }
  }
  else
  {
    dwBuffC = 0;
    for (i=0; i<4; i++) SetCanLong(mpdwChannelsB, i);

    j = ibMonth + 2;
    do
    {
      if (QueryEnergyA_Full2( 0x30 | ((j - 1) % 12 + 1), 76 + j ) == 0) return(0);             
      for (i=0; i<4; i++)
      {
        dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
        dwBuffC += *PGetCanLong(mpdwChannelsB, i);

        SetCanLong(mpdwChannelsB, i);
      }
    }
    while ((bMONTHS + tiAlt.bMonth - j++) % bMONTHS != 0 );

    if (QueryEnergyA_Full2(0,99) == 0) return(0);             
    for (i=0; i<4; i++)
    {
      dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
      dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

      SetCanLong(mpdwChannelsB, i);
    }
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000) mpdwChannelsB[i] = 0;

    reBuffA = *PGetCanLong(mpdwChannelsB, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = *PGetCanLong(mpdwChannelsB, diCurr.ibLine) * reBuffB;

  return(1);
}

#endif



#ifndef SKIP_B

// ������ �������� ��������� ��������� �� ������� ��� �������� ��������-230
bit     ReadCntMonCanB(uchar  ibMonth)                 
{ 
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceB_Special() == 0) return(0);


  if (QueryTimeAltB_Full(76) == 0) return(0);

  if (tiAlt.bMonth == ibMonth+1)        // ��������� ��������� �� ������ �������� ������
  {
    if (QueryEnergyB_Full2(0x40,98) == 0) return(0);                   
    for (i=0; i<4; i++)
    {
      dwBuffC = *PGetCanLong(mpdwChannelsA, i);
      SetCanLong(mpdwChannelsB, i);
    }

    if (QueryEnergyB_Full2(0,99) == 0) return(0);             
    for (i=0; i<4; i++)
    {
      dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
      dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

      SetCanLong(mpdwChannelsB, i);
    }
  }
  else
  {
    dwBuffC = 0;
    for (i=0; i<4; i++) SetCanLong(mpdwChannelsB, i);

    j = ibMonth + 2;
    do
    {
      if (QueryEnergyB_Full2( 0x30 | ((j - 1) % 12 + 1), 76 + j ) == 0) return(0);
      for (i=0; i<4; i++)
      {
        dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
        dwBuffC += *PGetCanLong(mpdwChannelsB, i);

        SetCanLong(mpdwChannelsB, i);
      }
    }
    while ((bMONTHS + tiAlt.bMonth - j++) % bMONTHS != 0 );

    if (QueryEnergyB_Full2(0,99) == 0) return(0);             
    for (i=0; i<4; i++)
    {
      dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
      dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

      SetCanLong(mpdwChannelsB, i);
    }
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    if (mpdwChannelsB[i] > 0xF0000000) mpdwChannelsB[i] = 0;

    reBuffA = *PGetCanLong(mpdwChannelsB, i) * reBuffB * 2;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = *PGetCanLong(mpdwChannelsB, diCurr.ibLine) * reBuffB * 2;

  return(1);
}

#endif



#ifndef SKIP_C

bit     ReadCntMonCanC(uchar  ibMonth)                 
{ 
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceC() == 0) return(0);


  DelayOff();
  QueryTimeC();                   

  if (RevInput() != SER_GOODCHECK) return(0);  if (fKey == 1) return(0);
  ShowPercent(76);

  ReadTimeAltC();                        

  if (tiAlt.bMonth == ibMonth+1)        // ��������� ��������� �� ������ �������� ������
  {
    if (QueryEnergyDayC_Full2(0, 98) == 0) return(0);
    for (i=0; i<4; i++)
    {
      dwBuffC = *PGetCanLong(mpdwChannelsA, i);
      SetCanLong(mpdwChannelsB, i);
    }


    if (QueryEnergyAbsC_Full2(99) == 0) return(0);
    for (i=0; i<4; i++)
    {
      dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
      dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

      SetCanLong(mpdwChannelsB, i);
    }
  }
  else
  {
    dwBuffC = 0;
    for (i=0; i<4; i++) SetCanLong(mpdwChannelsB, i);

    j = (ibMonth + 1)%12;
    do
    {
      if (QueryEnergyMonC_Full2(-((12-1+tiAlt.bMonth-j)%12), 76+j) == 0) return(0);
      for (i=0; i<4; i++)
      {
        dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
        dwBuffC += *PGetCanLong(mpdwChannelsB, i);

        SetCanLong(mpdwChannelsB, i);
      }
    }
    while ((bMONTHS + tiAlt.bMonth - ++j) % bMONTHS != 0 );


    if (QueryEnergyAbsC_Full2(99) == 0) return(0);             
    for (i=0; i<4; i++)
    {
      dwBuffC  = *PGetCanLong(mpdwChannelsA, i);
      dwBuffC -= *PGetCanLong(mpdwChannelsB, i);

      SetCanLong(mpdwChannelsB, i);
    }
  }


  reBuffB = reBuffB/reBuffA;

  for (i=0; i<4; i++) 
  {
    reBuffA = *PGetCanLong(mpdwChannelsB, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = *PGetCanLong(mpdwChannelsB, diCurr.ibLine) * reBuffB;

  return(1);
}

#endif



#ifndef SKIP_D

bit     ReadCntMonCanD(uchar  ibMonth)                 
{ 
uchar	i,j;

  Clear();
  if (OpenDeviceD() == 0) return(0);

  
  DelayOff();
  QueryTimeD();                   

  if (ExtInput() != SER_GOODCHECK) return(0);
  ShowPercent(50);

  ReadTimeD();                        


  if (tiAlt.bMonth == ibMonth+1) 
  {  
    if (ReadAllEnergyD() == 0) return(0);

    QueryCloseD(0);
    MakeEnergyD();
  
    if (LoadImpDay( ibHardDay ) == 0) return(0);

    for (i=0; i<4; i++) {
      for (ibCan=0; ibCan<bCANALS; ibCan++) {
        if ((GetDigitalPort(ibCan)    == GetDigitalPort(ibDig))    &&
            (GetDigitalPhone(ibCan)   == GetDigitalPhone(ibDig))   &&
            (GetDigitalDevice(ibCan)  == GetDigitalDevice(ibDig))  &&
            (GetDigitalAddress(ibCan) == GetDigitalAddress(ibDig)) &&
            (GetDigitalLine(ibCan)    == i)) {

          reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibCan,0x0F);
          reBuffA /= mpreTransEng[ibCan];

          mpreChannelsB[i] -= reBuffA;
        }
      }
    }
  }
  else
  { 
    if (ReadAllEnergyD() == 0) return(0);

    QueryCloseD(0);
    MakeEnergyD();

    j = ibHardMon;
    do
    {
      if (LoadImpMon(j) == 0) return(0);

      for (i=0; i<4; i++) {
        for (ibCan=0; ibCan<bCANALS; ibCan++) {
          if ((GetDigitalPort(ibCan)    == GetDigitalPort(ibDig))    &&
              (GetDigitalPhone(ibCan)   == GetDigitalPhone(ibDig))   &&
              (GetDigitalDevice(ibCan)  == GetDigitalDevice(ibDig))  &&
              (GetDigitalAddress(ibCan) == GetDigitalAddress(ibDig)) &&
              (GetDigitalLine(ibCan)    == i)) {

            reBuffA = *PGetCanImp2RealEng(mpimMonCan[ PrevSoftMon() ],ibCan,0x0F);
            reBuffA /= mpreTransEng[ibCan];

            mpreChannelsB[i] -= reBuffA;
          }
        }
      }  

      j = (bMONTHS + j - 1) % bMONTHS;
    }
    while (j != ibMonth);
  }

  reBuffA = mpreChannelsB[diCurr.ibLine];
  return(1);
}

#endif



#ifndef SKIP_E

// ������ �������� ��������� ��������� �� ������� ��� ��������� ���-2
bit     ReadCntMonCanE(uchar  ibMonth)                 
{
  Clear();
  if (ReadTimeDateE() == 0) return(0);


  ibMonth = (bMONTHS+tiAlt.bMonth-1-ibMonth) % bMONTHS;

  if (ibMonth > 6-1) 
  { 
    reBuffA = 0; 
    return(1); 
  }


  if (ReadAllIndexesE('v',ibMonth) == 0) return(0);


  Clear();
  //ShowPercent(80);

  if (ReadSensorE('V',0) == 0) return(0);


  return(1);
}

#endif



#ifndef SKIP_F

//  ������ �������� ��������� ��������� ��� ���������� ���+2
bit     ReadCntMonCanF(uchar  ibMonth)                 
{
uchar   i;

  Clear(); 

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryTimeF();                   

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  ReadTimeAltF();                        
  if (tiAlt.bMonth != ibMonth+1) return(0);     // ��������� ��������� �� ������ �������� ������


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryRealExtendedF(bINQ_GETCNTCANMONCURR_ALL);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  ReadRealExtendedF();

  return(1);
}

#endif



#ifndef SKIP_G

//  ������ �������� ��������� ��������� ��� ��������� �������-9
bit     ReadCntMonCanG(uchar  ibMonth)                 
{
uchar   i;

  Clear();
  if (ReadKoeffDeviceG() == 0) return(0);
  reBuffX = reBuffB;


  DelayOff();
  QueryTimeG();                   

  if (CodInput() != SER_GOODCHECK) return(0);  if (fKey == 1) return(0);
  ShowPercent(55);

  ReadTimeAltG();                        


  for (i=0; i<30; i++) mpreCodEng30[i] = 0;

  if (ExtVersionCod()) 
  {
    if (tiAlt.bMonth != ibMonth+1) 
    {
      if (bVersionCod == 49) 
        return ReadCntMonCanExt_G(ibMonth); 
      else
        { sprintf(szLo,"   ����������   "); Delay(1000); sprintf(szLo,"   ������ 49    "); Delay(1000); return(0); }
    }                                           
    else                                        // ��������� ��������� �� ������ �������� ������
    {
      if (ReadEnergyExt_G() == 0) return(0); 
    } 
  }
  else
  {
    if (tiAlt.bMonth != ibMonth+1) 
    {
      { sprintf(szLo,"   ����������   "); Delay(1000); sprintf(szLo,"   ������ 49    "); Delay(1000); return(0); }
    }                                           
    else                                        // ��������� ��������� �� ������ �������� ������
    {
      if (ReadEnergyBCD_G() == 0) return(0); 
    }
  }

  ShowPercent(100);


  for (i=0; i<6; i++) 
  {
    mpreChannelsB[i] = mpreCodEng30[i*5+0] - mpreCodEng30[i*5+3];

    reBuffA = *PGetCanReal(mpreChannelsB, i) * reBuffB;
    SetCanReal(mpreChannelsB, i);

    mpboChannelsA[i] = boTrue;     
  }

  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_H

//  ������ �������� ��������� ��������� ��� ��������� �������-9
bit     ReadCntMonCanH(uchar  ibMonth)                 
{
uchar   i,j;

  Clear();
  if (ReadKoeffDeviceH() == 0) return(0);
  reBuffX = reBuffB;


  DelayOff();
  QueryTimeH();                   

  if (CodInput() != SER_GOODCHECK) return(0);  if (fKey == 1) return(0);
  ShowPercent(55);

  ReadTimeAltH();                        

  if (tiAlt.bMonth != ibMonth+1) 
  {
    if ((bVersionCod == 43) || (bVersionCod == 45) || (bVersionCod == 47))
      return ReadCntMonCanExt_H(ibMonth); 
    else
      { sprintf(szLo,"   ����������   "); Delay(1000); sprintf(szLo,"������ 43,45,47 "); Delay(1000); return(0); }
  }                                           
                                                // ��������� ��������� �� ������ �������� ������

  for (i=0; i<3; i++) mpreCodEng30[i] = 0;


  for (j=0; j<bTARIFFS; j++)                    // �������� �� ���� ������� (� ��������: 8)
  {
    if (fKey == 1) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsH(j);

      ShowPercent(60+j);

      if (CodInput() != SER_GOODCHECK) continue; else break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      if (ChecksumH(14) == 0) { sprintf(szLo," ������ CRC: H7 "); Delay(1000); return(0); }

      InitPop(3);
      for (i=0; i<3; i++)
      {
        PopLongH();
        reBuffA = (real)dwBuffC/1000;

        mpreCodEng30[i] += reBuffA;
      }
    }
  }

  ShowPercent(100);


  // ������� �� ������� ����� ��������������, � �� ������������� �� �������� (��� ������ ����) !
  if (LoadImpDay( ibHardDay ) == 0) return(0);

  reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,0x0F);
  reBuffA = reBuffA / *PGetCanReal(mpreTransEng,ibDig);

  reBuffA = mpreCodEng30[0] * *PGetCanReal(mpreTransCnt,ibDig) - reBuffA;
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;     


  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_I

bit     ReadCntMonCanI(uchar  ibMonth)                 
{ 
uchar   i,j;

  Clear();

  DelayOff();
  QueryTimeI();                   

  if (TxtInput() != SER_GOODCHECK) return(0);
  ShowPercent(50);

  ReadTimeAltI();                        

  if (tiAlt.bMonth != ibMonth+1) return(0);     // ��������� ��������� �� ������ �������� ������


  reBuffB = 0;

  for (j=0; j<bTARIFFS; j++)                    // �������� �� ���� ������� (� ��������: 4)
  {
    if (fKey == 1) return(0);

    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryEnergyAbsI(j);

      ShowPercent(60+j);

      if (TxtInput() != SER_GOODCHECK) 
        continue;
      else 
        break;
    }

    if (i == bMINORREPEATS) return(0);
    else 
    {
      ReadEnergyI();
      reBuffB += reBuffA;
    }
  }

  ShowPercent(100);


  // ������� �� ������� ����� ��������������, � �� ������������� �� �������� (��� ������ ����) !
  if (LoadImpDay( ibHardDay ) == 0) return(0);

  reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,0x0F);
  reBuffA = reBuffA / *PGetCanReal(mpreTransEng,ibDig);

  reBuffA = reBuffB * *PGetCanReal(mpreTransCnt,ibDig) - reBuffA;
  SetCanReal(mpreChannelsB, 0);

  mpboChannelsA[0] = boTrue;     


  reBuffA = *PGetCanReal(mpreChannelsB, 0);

  return(1);
}

#endif



#ifndef SKIP_K

// ������ �������� ��������� ��������� ��� ��������� ��6850�
bit     ReadCntMonCanK(void)                 
{
  if (ReadTimeDateK() == 0) return(0);
  if (tiAlt.bMonth != ibMon+1) return(0);     // ��������� ��������� �� ������ �������� ������


  if (ReadSensorK(4) == 0) return(0);

  // ������� �� ������� ����� ��������������, � �� ������������� �� �������� (��� ������ ����) !
  if (LoadImpDay( ibHardDay ) == 0) return(0);

  for (ibMinor=0; ibMinor<ibMinorMax; ibMinor++) 
  {
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
       if (GetDigitalLine(ibCan) == ibMinor)
       {
         reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibCan,0x0F);
         reBuffA = reBuffA / *PGetCanReal(mpreTransEng,ibCan);

         reBuffB = *PGetCanReal(mpreChannelsB, ibMinor);
         reBuffA = reBuffB * *PGetCanReal(mpreTransCnt,ibCan) - reBuffA;
         SetCanReal(mpreChannelsB, ibMinor);
       }  
    }
  }

  reBuffA = *PGetCanReal(mpreChannelsB, diCurr.ibLine);

  return(1);
}

#endif



#ifndef SKIP_O

bit     ReadCntMonCanO(uchar  ibMonth)                 
{ 
uchar   i,j;

  Clear();

  DelayOff();
  QueryTimeO();                   

  if (TxtInput() != SER_GOODCHECK) return(0);
  ShowPercent(50);

  ReadTimeAltO();                        

  if (tiAlt.bMonth != ibMonth+1) 
  {
    reBuffB = 0;
    for (j=0; j<bTARIFFS; j++) 
    {
      if (fKey == 1) return(0);
      for (i=0; i<bMINORREPEATS; i++)
      {
        DelayOff();
        QueryEnergyAbsMonO(j, (ibMonth+1)%12+1);

        ShowPercent(60+j);
        if (TxtInput() != SER_GOODCHECK) continue; else break;
      }

      if (i == bMINORREPEATS) return(0);
      else 
      {
        ReadEnergyO();
        reBuffB += reBuffA;
      }
    }

    reBuffA = reBuffB * *PGetCanReal(mpreTransCnt,ibDig);
    SetCanReal(mpreChannelsB, 0);
 
    mpboChannelsA[0] = boTrue;     
    reBuffA = *PGetCanReal(mpreChannelsB, 0);
  }
  else 
  {
    reBuffB = 0;
    for (j=0; j<bTARIFFS; j++) 
    {
      if (fKey == 1) return(0);
      for (i=0; i<bMINORREPEATS; i++)
      {
        DelayOff();
        QueryEnergyAbsO(j);

        ShowPercent(60+j);
        if (TxtInput() != SER_GOODCHECK) continue; else break;
      }

      if (i == bMINORREPEATS) return(0);
      else 
      {
        ReadEnergyO();
        reBuffB += reBuffA;
      }
    }

    // ������� �� ������� ����� ��������������, � �� ������������� �� �������� (��� ������ ����) !
    if (LoadImpDay( ibHardDay ) == 0) return(0);

    reBuffA = *PGetCanImp2RealEng(mpimDayCan[ PrevSoftDay() ],ibDig,0x0F);
    reBuffA = reBuffA / *PGetCanReal(mpreTransEng,ibDig);

    reBuffA = reBuffB * *PGetCanReal(mpreTransCnt,ibDig) - reBuffA;
    SetCanReal(mpreChannelsB, 0);
 
    mpboChannelsA[0] = boTrue;     
    reBuffA = *PGetCanReal(mpreChannelsB, 0);
  }

  ShowPercent(100);

  return(1);
}

#endif



// ��������� ��������� ��������� � �������� ���������
bit     ReadSensors(uchar  ibCanal)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 0:  reBuffA = *PGetCounterOld(ibCanal);
             return(1);                break;

#ifndef SKIP_A
    case 15:
    case 1:  return( ReadSensorA() );  break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadSensorB() );  break;

    case 12: reBuffA = mpdwBase[ibCanal] * *PGetCanReal(mpreValueCntHou,ibCanal);
             return(1);                break;
#endif

#ifndef SKIP_C
    case 3:  return( ReadSensorC() );  break;
#endif

#ifndef SKIP_D
    case 4:  return( ReadSensorD() );  break;
#endif

#ifndef SKIP_E
    case 7:  
    case 5:  return( ReadSensorE('S',1) );  break;
#endif

#ifndef SKIP_F
    case 6:  return( ReadSensorF() );  break;
#endif

#ifndef SKIP_G
    case 9:  return( ReadSensorG() );  break;
#endif

#ifndef SKIP_H
    case 10: return( ReadSensorH() );  break;
#endif

#ifndef SKIP_I
    case 11: return( ReadSensorI() );  break;
#endif

#ifndef SKIP_K
    case 13: return( ReadSensorK(4) ); break;
    case 14: return( ReadSensorK(1) ); break;
#endif

#ifndef SKIP_L
    case 17:
    case 16: reBuffA = mpdwBase[ibCanal] * *PGetCanReal(mpreValueCntHou,ibCanal);
             return(1);                break;
#endif

#ifndef SKIP_M
    case 18: return( ReadSensorM() );  break;
#endif

#ifndef SKIP_N
    case 19: reBuffA = mpdwBase[ibCanal] * *PGetCanReal(mpreValueCntHou,ibCanal);
             reBuffA += *PGetCanReal(mpreCount,ibCanal);
             return(1);                break;
#endif

#ifndef SKIP_O
    case 20: return( ReadSensorO() );  break;
#endif

#ifndef SKIP_P
    case 21: return( ReadSensorP() );  break;
#endif

#ifndef SKIP_Q
    case 22: return( ReadSensorQ() );  break;
#endif

#ifndef SKIP_R
    case 23: return( ReadSensorR() );  break;
#endif

#ifndef SKIP_S
    case 24: return( ReadSensorS() );  break;
#endif

#ifndef SKIP_T
    case 25: return( ReadSensorT() );  break;
#endif

#ifndef SKIP_U
    case 26: return( ReadSensorU() );  break;
#endif

#ifndef SKIP_Z
    case 99: reBuffA = 0; return(1);   break;
#endif

    default: reBuffA = 0; return(0);   break;
  }
}
*/


// ��������� �������� �������/���� � �������� ���������
bool    ReadTimeDate(uchar  ibCan)
{
  Clear();

  LoadCurrDigital(ibCan);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  return( ReadTimeDateA() );
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadTimeDateB() );

    case 12: tiAlt = tiCurr; return(1);
#endif

#ifndef SKIP_C
    case 3:  return( ReadTimeDateC() );
#endif

    default: tiAlt = tiZero; return(0);
  }
}


/*
// ��������� ��������� ��������� �� ������� � �������� ���������
bit     ReadCntMonCan(uchar  ibMonth, uchar  ibCanal)
{
  Clear();

  LoadCurrDigital(ibCanal);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
    case 0:  if (LoadCntMon(ibMonth) == 0) return(0);
             reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
             return(1); break;

#ifndef SKIP_A
    case 15:
    case 1:  return( ReadCntMonCanA(ibMonth) ); break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  return( ReadCntMonCanB(ibMonth) ); break;

    case 12: if (LoadCntMon(ibMonth) == 0) return(0);
             reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
             return(1); break;
#endif

#ifndef SKIP_C
    case 3:  return( ReadCntMonCanC(ibMonth) ); break;
#endif

#ifndef SKIP_D
    case 4:  return( ReadCntMonCanD(ibMonth) ); break;
#endif

#ifndef SKIP_E
    case 7:  
    case 5:  return( ReadCntMonCanE(ibMonth) ); break;
#endif

#ifndef SKIP_F
    case 6:  return( ReadCntMonCanF(ibMonth) ); break;
#endif

#ifndef SKIP_G
    case 9:  return( ReadCntMonCanG(ibMonth) ); break;
#endif

#ifndef SKIP_H
    case 10: return( ReadCntMonCanH(ibMonth) ); break;
#endif

#ifndef SKIP_I
    case 11: return( ReadCntMonCanI(ibMonth) ); break;
#endif

#ifndef SKIP_K
    case 13: return( ReadCntMonCanK2(ibMonth) ); break;

    case 14: ibMon = ibMonth; ibMinorMax = 1;
             return( ReadCntMonCanK() ); break;
#endif

#ifndef SKIP_L
    case 17:
    case 16: if (LoadCntMon(ibMonth) == 0) return(0);
             reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
             return(1); break;
#endif

#ifndef SKIP_M
    case 18: if (LoadCntMon(ibMonth) == 0) return(0);
             reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
             return(1); break;
#endif

#ifndef SKIP_N
    case 19: if (LoadCntMon(ibMonth) == 0) return(0);
             reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
             return(1); break;
#endif

#ifndef SKIP_O
    case 20: return( ReadCntMonCanO(ibMonth) ); break;
#endif

#ifndef SKIP_P
    case 21: return( ReadCntMonCanP(ibMonth) ); break;
#endif

#ifndef SKIP_Q
    case 22: return( ReadCntMonCanQ(ibMonth) ); break;
#endif

#ifndef SKIP_R
    case 23: if (LoadCntMon(ibMonth) == 0) return(0);
             reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCanal);
             return(1); break;
#endif

#ifndef SKIP_S
    case 24: return( ReadCntMonCanS(ibMonth) ); break;
#endif

#ifndef SKIP_T
    case 25: return( ReadCntMonCanT(ibMonth) ); break;
#endif

#ifndef SKIP_U
    case 26: return( ReadCntMonCanU(ibMonth) ); break;
#endif

#ifndef SKIP_Z
    case 99: reBuffA = 0; return(1);            break;
#endif

    default: reBuffA = 0; return(0);            break;
  }
}
*/
