/*------------------------------------------------------------------------------
AUTOMATIC1.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_factors.h"
#include        "../memory/mem_digitals.h"
#include        "../keyboard/keyboard.h"
#include        "../display/display.h"
#include        "../serial/ports_stack.h"
#include        "../serial/ports_devices.h"
#include        "../serial/ports_common.h"
#include        "../digitals/digitals_run.h"
#include        "../engine.h"
#include        "../energy.h"
#include        "automatic_b.h"



#ifndef SKIP_A

// ������ ������������� ��� �������� ���-4��
bool    ReadKoeffDeviceA(void)
{
uchar   i;

  if (QueryOpenA_Full(25) == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(2);                        // ������ �������������

    DelayOff();
    QueryIO(1+10+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  // K �������������
  reBuffB = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));  


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(0x12);                     // ������ ���������� ��������

    DelayOff();
    QueryIO(1+3+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);


  switch (InBuff(2) & 0x0F)             // K ��������������
  {
    case 0:  reBuffA = 10000;  break;
    case 1:  reBuffA = 50000;  break;
    case 2:  reBuffA =  2500;  break;
    case 3:  reBuffA =  1000;  break;   // 12500
    case 4:  reBuffA =  2000;  break;   // ?
    case 5:  reBuffA =   500;  break;   // ?

    default: return(0);  
  }

  return(1);
}

#endif



#ifndef SKIP_B

// ������ ������������� ��� �������� ��������-230
bool    ReadKoeffDeviceB(void)
{
uchar   i;

  if (QueryOpenB_Full(25) == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(2);                        // ������ �������������

    DelayOff();
    QueryIO(1+4+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  // K �������������
  reBuffB = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));  


  for (i=0; i<bMINORREPEATS; i++)
  {
    // ������ �������: ����� 3 �����
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(0x12);                     // ������ ���������� ��������

    DelayOff();
    QueryIO(1+3+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
                                        
    // ������ �������: ����� 6 ����
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(0x12);                     // ������ ���������� ��������

    DelayOff();
    QueryIO(1+6+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  switch (InBuff(3) & 0x0F)             // K ��������������
  {
    case 1:  reBuffA = 10000;  break;
    case 2:  reBuffA =  2000;  break;
    case 3:  reBuffA =  1000;  break;
    case 4:  reBuffA =  2000;  break;

    default: return(0);  
  }

  mpreLevelDiv[ibDig] = reBuffA / 1000;

  return(1);
}


// ������ ������������� ��� �������� ��������-230
bool    ReadKoeffDeviceB_Special(void)
{
uchar   i;

  if (QueryOpenB_Full(25) == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(8);           
    PushChar(2);                        // ������ �������������

    DelayOff();
    QueryIO(1+4+2, 2+1+2);

    if (Input() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  // K �������������
  reBuffB = (InBuff(1)*0x100 + InBuff(2)) * (InBuff(3)*0x100 + InBuff(4));  

  // K ��������������
  reBuffA = 2000;

  return(1);
}

#endif



#ifndef SKIP_C

// ������ ������������� ��� �������� ��-301
bool    ReadKoeffDeviceC(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryOpenC();                       // �������� ������ �����

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(25);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();

    InitPush(0);
    PushChar(diCurr.bAddress);           
    PushChar(3);
    PushChar(34);

    PushChar(0);
    PushChar(0);
    PushChar(0);

    RevQueryIO(4+18+2, 3+3+2);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  coTrue.mpbBuff[3] = InBuff(4);
  coTrue.mpbBuff[2] = InBuff(5);
  coTrue.mpbBuff[1] = InBuff(6);
  coTrue.mpbBuff[0] = InBuff(7);

  reBuffB = coTrue.dwBuff; 

  coTrue.mpbBuff[3] = InBuff(8);
  coTrue.mpbBuff[2] = InBuff(9);
  coTrue.mpbBuff[1] = InBuff(10);
  coTrue.mpbBuff[0] = InBuff(11);

  reBuffB *= coTrue.dwBuff;             // K �������������


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();

    InitPush(0);
    PushChar(diCurr.bAddress);
    PushChar(3);
    PushChar(24);

    PushChar(0);
    PushChar(0);
    PushChar(0);

    RevQueryIO(4+8+2, 3+3+2);

    if (RevInput() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(60);


  reBuffA = InBuff(8) + InBuff(9)*0x100;
  reBuffA = 1000000/reBuffA;            // K ��������������

  return(1);
}

#endif



#ifndef SKIP_G

bool    ReadKoeffDeviceG(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  if (ReadOpenG() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    InitPushCod();

    PushChar(0x7E);
    PushChar(0x03);
    PushChar(0x06);

    PushCharCod(0x03);
    PushCharCod(0x00);
    PushCharCod(0x00);

    CodQueryIO(3+25+1, 3+3+1);

    if (CodInput() == SER_GOODCHECK) break; 
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);


  InitPop(3);
  for (i=0; i<9; i++) PopChar();

  if (ExtVersionCod()) PopRealExt_G(); else PopRealBCD_G();
  reBuffB = reBuffA;

  if (ExtVersionCod()) PopRealExt_G(); else PopRealBCD_G();  
  reBuffB *= reBuffA;                   // K �������������
  
  reBuffA = 10000;                      // K ��������������

  return(1);
}

#endif



#ifndef SKIP_H

bool    ReadKoeffDeviceH(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  if (ReadOpenH() == 0) return(0);


  reBuffB = 1;                          // K �������������

  if (bVersionCod == 43)
    reBuffA = 1000;                     // K ��������������
  else
    reBuffA = 10000;

  return(1);
}

#endif



#ifndef SKIP_P

bool    ReadKoeffDeviceP(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryRegisterP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(60);

  ReadRegisterP();

  return(1);
}

#endif



#if (defined SKIP_A && defined SKIP_B && defined SKIP_C && defined SKIP_E)
#else

// ���������� � �������������� � � ������������
void    SetCanalsAll(void)
{
  SetCanReal(mprePulseHou,ibDig,&reBuffA);
  SetCanReal(mprePulseMnt,ibDig,&reBuffA);
  reBuffA = reBuffB;

  SetCanReal(mpreTransEng,ibDig,&reBuffA);
  SetCanReal(mpreTransCnt,ibDig,&reBuffA);
}

#endif


/*
#if (defined SKIP_A && defined SKIP_B && defined SKIP_C)
#else

// ���������� ��������� ���������
void    SetEnergyAll(void)
{
  reBuffA  = *PGetCanReal(mpreTransCnt,ibDig) / *PGetCanReal(mprePulseHou,ibDig);
  reBuffA *= coEnergy.dwBuff;

  SetCanReal(mpreCount,ibDig);    
}

#endif
*/


#ifndef SKIP_A

// ������� ���������� ��� ��������� ���-4��
bool    AutomaticA(void)
{
  if (ReadKoeffDeviceA() == 0) return(0);


  SetCanalsAll();                        // ���������� � �������������� � � ������������

  if (QueryEnergyA_Full(0,100) == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_B

// ������� ���������� ��� ��������� ��������-230
bool    AutomaticB(void)
{
  if (ReadKoeffDeviceB() == 0) return(0);


  SetCanalsAll();                        // ���������� � �������������� � � ������������

  if (QueryEnergyB_Full(0,100) == 0) return(0);

  return(1);
}


// ������� ���������� ��� ��������� ��������-230
bool    AutomaticJ(void)
{
  if (ReadKoeffDeviceB_Special() == 0) return(0);
  mpreLevelDiv[ibDig] = reBuffA / 1000;


  SetCanalsAll();                        // ���������� � �������������� � � ������������

  if (QueryEnergyB_Full(0,100) == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_C

// ������� ���������� ��� ��������� ��-301
bool    AutomaticC(void)
{
  if (ReadKoeffDeviceC() == 0) return(0);


  SetCanalsAll();                       // ���������� � �������������� � � ������������

  DelayOff();
  QueryEnergyAbsC();                    // ������ ����������� �������

  if (RevInput() != SER_GOODCHECK) return(0);
  ShowPercent(100);
/*
  ReadEnergyC();
  SetEnergyAll();                       // ���������� ��������� ���������
*/
  return(1);
}

#endif



#ifndef SKIP_D

// �������� ������ ��� ��������� ABB �����
bool    OpenDeviceD(void)
{
uchar   i;

  for (i=0; i<bMAJORREPEATS; i++)
  {
    ShowPercent(i);

    DelayOff();
    QueryOpenD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMAJORREPEATS) return(0);
  ShowPercent(48);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryPasswordD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(49);

  if (InBuff(2) != 0) return(0);
  ShowPercent(50);


  return(1);
}

#endif



#ifndef SKIP_E

// �������� ������ ��� ���������� ���-2
bool    OpenDeviceE(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    if (diCurr.bAddress <= 16)
    {   
      QueryBreakE();

      InitPush(0);
      PushChar(0x1B);          
      PushChar('0'+diCurr.bAddress);            

      Query(1+1, 2, 1);

      if (EscInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }
    else return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  return(1);
}

#endif



#ifndef SKIP_G

// �������� ������ ��� ��������� �������-9 a
bool    OpenDeviceG(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenG();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  if (ReadOpenG() == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_H

// �������� ������ ��� ��������� �������-9 a
bool    OpenDeviceH(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenH();

    if (CodInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  if (ReadOpenH() == 0) return(0);

  return(1);
}

#endif



#ifndef SKIP_D

// ������ ���� ����������� ������� ��� ��������� ABB �����
bool    ReadAllEnergyD(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEnergyD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);

  ibMinor = 0;
  ReadEnergyD();


  while (ibMinor < GetEnergyBlocksD())
  {
    for (i=0; i<bMINORREPEATS; i++)
    {
      DelayOff();
      QueryContinueD();

      if (ExtInput() == SER_GOODCHECK) break;
      if (fKey == 1) return(0);
    }

    if (i == bMINORREPEATS) return(0);
    ShowPercent(76 + ibMinor);

    ReadEnergyD();
  }


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryStopD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadQuadrantsD();


  return(1);
}

#endif



#ifndef SKIP_P

// �������� ������ ��� ��������� Elster A1140
bool    OpenDeviceP(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenP();

    if (ElsInput(1) == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(20);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryModeP();

    if (ElsInput(0) == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(30);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryPasswordP();

    if (ElsInput(2) == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(40);


  return(1);
}

#endif



#ifndef SKIP_D

// ������� ���������� ��� ��������� ABB �����
bool    AutomaticD(void)
{
uchar   i;

  if (OpenDeviceD() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryConfigD();

    if (ExtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(51);

  if (InBuff(2) != 0) return(0);
  ShowPercent(52);
  
  ReadConfigD();


  if (ReadAllEnergyD() == 0) return(0);

  QueryCloseD(0);


  MakeEnergyD();

  SetCanReal(mpreCount,ibDig);    

  return(1);
}

#endif



#ifndef SKIP_E

// ������� ���������� ��� ��������� ���-2
bool    AutomaticE(void)
{
uchar   i;

  if (OpenDeviceE() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(0x1B);          
    PushChar('w');            

    Query(300+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(75);


  InitPop((uint)132 + diCurr.ibLine*3); // K �������������
  PopRealBCD();

  reBuffB = reBuffA;                    


  InitPop((uint)180 + diCurr.ibLine*3); // K ��������������
  PopRealBCD();

  SetCanalsAll();                        // ���������� � �������������� � � ������������


  DelayOff();

  for (i=0; i<bMINORREPEATS; i++)       // ������ ����������� �������
  {
    InitPush(0);
    PushChar(0x1B);          
    PushChar('S');            

    Query(64+1, 2, 1);  

    if (EscInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);


  InitPop(diCurr.ibLine*4); 

  coFloat.mpbBuff[0] = PopChar();
  coFloat.mpbBuff[1] = PopChar();
  coFloat.mpbBuff[2] = PopChar();
  coFloat.mpbBuff[3] = PopChar();

  ToReal();
  SetCanReal(mpreCount,ibDig);            // ���������� ��������� ���������


  return(1);
}

#endif



#ifndef SKIP_F

// ������� ���������� ��� ��������� ���+2
bool    AutomaticF(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryBreakF();
    QueryKoeffF();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadKoeffF();


  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryRealExtendedF(bEXT_GETSIMPLE_ESC_S);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(100);

  ReadRealExtendedF();

  SetCanReal(mpreCount,ibDig);  


  return(1);
}

#endif



#ifndef SKIP_G

bool    AutomaticG(void)
{
  if (ReadKoeffDeviceG() == 0) return(0);
  ShowPercent(100);

  SetCanalsAll();                       // ���������� � �������������� � � ������������

  return(1);
}

#endif



#ifndef SKIP_H

bool    AutomaticH(void)
{
  if (ReadKoeffDeviceH() == 0) return(0);
  ShowPercent(100);

  SetCanalsAll();                       // ���������� � �������������� � � ������������

  return(1);
}

#endif



#ifndef SKIP_I

bool    AutomaticI(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenI();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ReadOpenI();

  reBuffB = 1;                          // K �������������
  reBuffA = 5000;                       // K ��������������

  ShowPercent(100);

  SetCanalsAll();                       // ���������� � �������������� � � ������������

  return(1);
}

#endif



#ifndef SKIP_K

bool    AutomaticK(void)
{
uchar   i,bT;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryCloseK();
    QueryOpenK();

    if (BccInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);

    bT = InBuff(IndexInBuff() - 1) & 0x7F;
    if ((bT == '\r') || (bT == '\n')) 
      break;
  }

  if (i == bMINORREPEATS) return(0);
  ReadOpenK();

  QueryCloseK();


  reBuffB = 1;                          // K �������������
  reBuffA = 5000;                       // K ��������������

  Delay(1000);

  SetCanalsAll();                       // ���������� � �������������� � � ������������

  return(1);
}

#endif



#ifndef SKIP_M

bool    AutomaticM(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsM();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  reBuffB = 1;                          // K �������������
  reBuffA = 100;                        // K ��������������

  ShowPercent(100);

  SetCanalsAll();                       // ���������� � �������������� � � ������������

  return(1);
}

#endif



#ifndef SKIP_N

bool    AutomaticN(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    InitPush(0);
    PushChar(0);   
    PushChar(diCurr.bAddress);

    PushChar(8);

    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);
    PushChar(0);

    QueryIO(5+8, 5+8);

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);

  sprintf(szLo+1,"������:");
  szLo[ 9] = InBuff(3); 
  szLo[10] = InBuff(4); 
  szLo[11] = InBuff(5); 
  szLo[12] = InBuff(6); 
  szLo[13] = InBuff(7); 

  DelayInf(); Clear();
  

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryEnergyAbsN();

    if (Input() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadEnergyN();

  mpdwBase[ibDig] = *PGetCanLong(mpdwChannelsA, 0);

  return(1);
}

#endif



#ifndef SKIP_O

bool    AutomaticO(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryOpenO();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ReadOpenO();

  reBuffB = 1;                          // K �������������
  reBuffA = 5000;                       // K ��������������

  ShowPercent(100);

  SetCanalsAll();                       // ���������� � �������������� � � ������������

  return(1);
}

#endif



#ifndef SKIP_T

bool    AutomaticT(void)
{
uchar   i;

  for (i=0; i<bMINORREPEATS; i++)
  {
    QueryVersionT();

    if (TxtInput() == SER_GOODCHECK) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ReadVersionT();

  Delay(1000); Clear();

  reBuffB = 1;                          // K �������������
  reBuffA = 5000;                       // K ��������������

  ShowPercent(100);

  SetCanalsAll();

  return(1);
}

#endif



#ifndef SKIP_P

bool    AutomaticP(void)
{
uchar   i;

  Clear();
  if (OpenDeviceP() == 0) return(0);


  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryTransP();

    if (ElsInput(0) != SER_GOODCHECK) continue; else break;
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(50);

  ReadTransP();                         // K �������������
  QueryCloseP();


  reBuffA = 5000;                       // K ��������������
  SetCanalsAll();                       // ���������� � �������������� � � �������������

  return(1);
}

#endif



#ifndef SKIP_R

bool    AutomaticR(void)
{
  Clear();

  if (ReadSensorR() == 0) return(0);

  reBuffA = 1;                          // K ��������������
  reBuffB = 1;                          // K �������������
  SetCanalsAll();                       // ���������� � �������������� � � �������������

  return(1);
}

#endif



#ifndef SKIP_S

bool    AutomaticS(void)
{
  Clear();

  if (QueryConfigS_Full(50) == 0) return(0);

  reBuffA = wDividerS;                  // K ��������������
  reBuffB = 1;                          // K �������������
  SetCanalsAll();                       // ���������� � �������������� � � �������������

  return(1);
}

#endif
