/*------------------------------------------------------------------------------
DEVICE32.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_current.h"
#include "../../memory/mem_factors.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../display/display.h"
#include "../../time/timedate.h"
#include "../../time/delay.h"
#include "../../devices/devices.h"
#include "../../digitals/current/current_run.h"
#include "../../digitals/digitals_messages.h"
//#include "automatic31.h"
#include "device32.h"



#ifndef SKIP_N32

//// �������� ������
//bit     OldVersion31(void)
//{
//  return (bVersionCod == 16) || (bVersionCod == 43);
//}
//
//
//
//// ������ ������ ���� 'long' ��� �������� �������-9
//void    PopLong31(void)
//{
//  if (OldVersion31())
//  {
//    coFloat.mpbBuff[3] = PopChar();
//    coFloat.mpbBuff[2] = PopChar();
//    coFloat.mpbBuff[1] = PopChar();
//    coFloat.mpbBuff[0] = PopChar();
//  }
//  else
//  {
//    coFloat.mpbBuff[0] = PopChar();
//    coFloat.mpbBuff[1] = PopChar();
//    coFloat.mpbBuff[2] = PopChar();
//    coFloat.mpbBuff[3] = PopChar();
//  }
//
//  dwBuffC = coFloat.dwBuff;
//}
//
//
//// ������ ������� �������� ��� �������� �������-9
//void    PopHeader31(void)
//{
//  if (bVersionCod == 43)
//  {
//    coFloat.mpbBuff[3] = PopChar();
//    coFloat.mpbBuff[2] = PopChar();
//    coFloat.mpbBuff[1] = 0;
//    coFloat.mpbBuff[0] = 0;
//  }
//  else if (bSpeciesCod == 0)
//  {
//    coFloat.mpbBuff[0] = 0;
//    coFloat.mpbBuff[1] = PopChar();
//    coFloat.mpbBuff[2] = PopChar();
//    coFloat.mpbBuff[3] = PopChar();
//  }
//  else if (bSpeciesCod == 1)
//  {
//    coFloat.mpbBuff[0] = 0;
//    coFloat.mpbBuff[1] = 0;
//    coFloat.mpbBuff[2] = PopChar();
//    coFloat.mpbBuff[3] = PopChar();
//  }
//  else
//  {
//    coFloat.mpbBuff[3] = PopChar();
//    coFloat.mpbBuff[2] = PopChar();
//    coFloat.mpbBuff[1] = PopChar();
//    coFloat.mpbBuff[0] = PopChar();
//  }
//
//  dwBuffC = coFloat.dwBuff;
//  reBuffA = (real)dwBuffC/1000;
//}
//
//
//
//// ������ ����������� �������/���� ��� �������� �������-9
//void    ReadPackTimeDig31(void)
//{
//uchar   a,b;
//
//  InitPop(3);
//
//  if (OldVersion31())
//  {
//    b = PopChar();
//    a = PopChar();
//  }
//  else
//  {
//    a = PopChar();
//    b = PopChar();
//  }
//
//  tiDig.bMonth  = (a >> 4) & 0x0F;
//  tiDig.bDay    = ((0x100*a+b) >> 7) & 0x1F;
//  tiDig.bHour   = (b >> 2) & 0x1F;
//  tiDig.bMinute = (b & 0x03)*15;
//
//  if (tiDig.bMonth > tiCurr.bMonth)
//    tiDig.bYear = tiCurr.bYear-1;
//  else
//    tiDig.bYear = tiCurr.bYear;
//
//  tiDig.bSecond = 0;
//}
//
//
//
//// ������� ������� �� �������� ������ ����� ��� �������� �������-9
//void    QueryClose31(void)
//{
//  InitPush();
//
//  PushChar(0x7E);
//  PushChar(0x00);
//  PushChar(0x02);
//
//  CodQueryIO(0, 3+1);
//}
//
//
//// ������� ������� �� �������� ������ ����� ��� �������� �������-9
//void    QueryOpen31(void)
//{
//  QueryClose31();
//  DelayOff();
//
//  memset(&mpbCoder, 0, sizeof(mpbCoder));
//  InitPush();
//
//  PushChar(0x7E);
//  PushChar(0x08);
//  PushChar(0x03);
//
//  Push(&mpdwAddress1[diCurr.bAddress-1], sizeof(ulong));
//  Push(&mpdwAddress2[diCurr.bAddress-1], sizeof(ulong));
//
//  CodQueryIO(3+8+1, 3+8+1);
//}
//
//
//// ������ ������ ��� �������� �������-9
//bit     ReadOpen31(void)
//{
//  InitPop(3);
//
//  bVersionCod = PopChar();
//
//  mpbCoder[0] = PopChar();
//  mpbCoder[1] = PopChar();
//  mpbCoder[2] = PopChar();
//  mpbCoder[3] = PopChar();
//
//  sprintf(szLo,"   ������: %2bu   ",bVersionCod);
//  DelayInf(); Clear();
//
//  if ((bVersionCod == 23) || (bVersionCod == 45) ||
//      (bVersionCod == 25) || (bVersionCod == 47) ||
//      (bVersionCod == 16) ||
//      (bVersionCod == 30) ||
//      (bVersionCod == 43)) return(1);
//
//  ShowLo(szNoVersion);
//  DelayInf(); Clear();
//
//  return(0);
//}
//
//
//
//// ������� ������� �� ����� �������/���� ��� �������� �������-9
//void    QueryTime31(void)
//{
//  InitPush();
//
//  PushChar(0x7E);
//  PushChar(0x00);
//  PushChar(0x07);
//
//  CodQueryIO(3+8+1, 3+1);
//}
//
//
//// ������ �������/���� ��� �������� �������-9
//void    ReadTimeAlt31(void)
//{
//  InitPop(3);
//
//  tiAlt.bSecond = PopChar();
//  tiAlt.bMinute = PopChar();
//  tiAlt.bHour   = PopChar();
//                  PopChar();
//  tiAlt.bDay    = PopChar();
//  tiAlt.bMonth  = PopChar();
//  tiAlt.bYear   = PopChar();
//}
//
//
//// ������ �������/���� ��� �������� �������-9
//void    ReadTimeDig31(void)
//{
//  InitPop(3);
//
//  tiDig.bSecond = PopChar();
//  tiDig.bMinute = PopChar();
//  tiDig.bHour   = PopChar();
//                  PopChar();
//  tiDig.bDay    = PopChar();
//  tiDig.bMonth  = PopChar();
//  tiDig.bYear   = PopChar();
//}
//
//
//
//void    QueryControl31(void)
//{
//  InitPushCod();
//
//  PushChar(0x7E);
//  PushChar(0x08);
//  PushChar(0x08);
//
//  PushCharCod( tiCurr.bSecond );
//  PushCharCod( tiCurr.bMinute );
//  PushCharCod( tiCurr.bHour   );
//
//  tiAlt = tiCurr;
//  PushCharCod(Weekday());
//
//  PushCharCod( tiCurr.bDay    );
//  PushCharCod( tiCurr.bMonth  );
//  PushCharCod( tiCurr.bYear   );
//  PushCharCod( 20 );
//
//  CodQueryIO(3+1, 3+8+1);
//}
//
//
//
//// ������� ������� �� ����� ������� ��� �������� �������-9
//void    QueryEnergyAbs31(uchar  ibTariff)
//{
//  InitPushCod();
//
//  PushChar(0x7E);
//  PushChar(0x03);
//  PushChar(0x06);
//
//  PushCharCod((bVersionCod == 43) ? 0x02 : 0x04);
//  PushCharCod(0x00);
//  PushCharCod(ibTariff);
//
//  CodQueryIO(3+14+1, 3+3+1);
//}
//
//
//
//// ������� ������� �� ������ ������ ��� �������� �������-9
//void    QuerySpecies31(void)
//{
//  InitPushCod();
//
//  PushChar(0x7E);
//  PushChar(0x03);
//  PushChar(0x06);
//
//  PushCharCod((bVersionCod == 43) ? 0x09 : 0x0B);
//  PushCharCod(0);
//  PushCharCod(0);
//
//  CodQueryIO(3+8+1, 3+3+1); // �������� ������ ������ 3+6+1, 3+7+1, 3+8+1: �������� ������������
//}
//
//
//// ������ ������ ��� �������� �������-9
//bit     ReadSpecies31(void)
//{
//  if (IndexInBuff() == 3+7+1) { bSpeciesCod = 0; return(1); }
//  if (IndexInBuff() == 3+6+1) { bSpeciesCod = 1; return(1); }
//  if (IndexInBuff() == 3+8+1) { bSpeciesCod = 2; return(1); }
//
//  return(0);
//}
//
//
//
//// ������� �� ���������� ������
//bit     DecIndex31(void)
//{
//  if (wBaseLast == wBaseCurr)
//  {
//    if (wOffsCurr != 0) wOffsCurr--; else return(0);
//  }
//  else
//  {
//    if (wOffsCurr != 0) wOffsCurr--; else wOffsCurr = wBaseLast-1;
//  }
//
//  return(1);
//}
//
//
//
//// ������� ������� �� ������ ������� ������� ��� �������� �������-9
//void    QueryTop31(void)
//{
//  InitPushCod();
//
//  PushChar(0x7E);
//  PushChar(0x03);
//  PushChar(0x06);
//
//  PushCharCod((bVersionCod == 43) ? 0x08 : 0x0A);
//  PushCharCod(0x00);
//  PushCharCod(0x00);
//
//  CodQueryIO(3+8+1, 3+3+1);
//}
//
//
//// ������ ������� ������� ��� �������� �������-9
//bit     ReadTop31(void)
//{
//  InitPop(3);
//
//  iwMajor = 0;
//
//  if (OldVersion31())
//  {
//    wBaseLast = PopIntExtG();                 // ���������� �������
//    wBaseCurr = PopIntExtG();                 // ������ ������� ������
//  }
//  else
//  {
//  	wBaseLast = PopChar()*0x100 + PopChar();  // ���������� �������
//  	wBaseCurr = PopChar()*0x100 + PopChar();  // ������ ������� ������
//  }
//
//  wOffsCurr = wBaseCurr;
//
//  sprintf(szLo,"   %4u:%-4u    ",wBaseLast,wBaseCurr); DelayInf();
//
//  return( DecIndex31() );
//}
//
//
//
//// ������� ������� �� ������ ��������� �������� ����� ��� �������� �������-9
//void    QueryHeader31(void)
//{
//  InitPushCod();
//
//  PushChar(0x7E);
//  PushChar(0x03);
//  PushChar(0x06);
//
//  PushCharCod((bVersionCod == 43) ? 0x09 : 0x0B);
//  PushCharCod(wOffsCurr / 0x100);
//  PushCharCod(wOffsCurr % 0x100);
//
//  CodQueryIO(3+8+1, 3+3+1); // �������� ������ ������ 3+6+1, 3+7+1, 3+8+1: �������� ������������
//}
//
//
//// ������ ��������� �������� ����� ��� �������� �������-9
//bit     ReadHeader31(void)
//{
//  NoShowTime(1);
//
//  if (bVersionCod == 43)
//  {
//    MakeCRC12InBuff(3, 4);
//  	if (wCRC != InBuff(7) + InBuff(8)*0x100) { sprintf(szLo," ���������: %-4u   ",++iwMajor); return(iwMajor < 48); }
//  }
//  else if (bVersionCod == 16)
//  {
//  	MakeCRC12InBuff(3, 6);
//  	if (wCRC != InBuff(9) + InBuff(10)*0x100) { sprintf(szLo," ���������: %-4u   ",++iwMajor); return(iwMajor < 48); }
//  }
//  else
//  {
//    (bSpeciesCod == 0) ? MakeCRC12InBuff(3, 7) : MakeCRC12InBuff(3, 6);
//    if (wCRC != 0) { sprintf(szLo," ���������: %-4u   ",++iwMajor); return(iwMajor < 48); }
//  }
//
//
//  ReadPackTimeDig31();
//  sprintf(szLo," %02bu    %02bu.%02bu.%02bu",
//          tiDig.bHour, tiDig.bDay,tiDig.bMonth,tiDig.bYear);
//
//  if (tiDig.bMinute % 30 != 0) { szLo[4] = '?'; DelayInf(); }
//
//
//  if (SearchDefHouIndex() == 0) return(++iwMajor < 48);
//  iwMajor = 0;
//
//
//  iwDigHou = (wHOURS+iwDigHou-1)%wHOURS;                // ����� ������ ������ �������������� ������ ������������ �����
//
//  tiAlt = tiCurr;
//  dwBuffC = DateToHouIndex();
//
//  dwBuffC -= (wHOURS + iwHardHou - iwDigHou) % wHOURS;
//  HouIndexToDate(dwBuffC);
//
//
//  ShowProgressDigHou();
//  reBuffB = mprePulseHou[ibDig];
//
//  for (ibCan=0; ibCan<1; ibCan++)
//  {
//    PopHeader31();
//    mpreEngFrac[ibDig] += reBuffA;
//
//    if (tiDig.bMinute % 30 == 0)
//    {
//      wBuffD = (uint)(mpreEngFrac[ibDig]*reBuffB);
//      mpwChannels[ibCan] = wBuffD;
//
//      mpreEngFrac[ibDig] -= (real)wBuffD/reBuffB;
//    }
//  }
//
//  MakePrevHou();
//  return(MakeStopHou(0));
//}
//
//
//
//bit     Checksum31(uchar  bSize)
//{
//  if (OldVersion31())
//  {
//    MakeCRC12InBuff(3, bSize-2);
//    if (wCRC != InBuff(3+bSize-2) + InBuff(3+bSize-1)*0x100) return(0);
//  }
//  else
//  {
// 	  MakeCRC12InBuff(3, bSize);
//    if (wCRC != 0) return(0);
//  }
//
//  return(1);
//}

#endif
