/*------------------------------------------------------------------------------
device38.c

���������� CE318
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "io38.h"
#include "device38.h"



#include "../../time/calendar.h"
#include "../../serial/monitor.h"
#include "../../memory/mem_serial3.h"
uint DFF_Decoder(uchar  *pbData, uchar bS);



void    PushAddress38(void)
{
  PushChar(0xE8);
  PushChar(0xB7);
  PushChar(0xC4);
  PushChar(0x04);

//  PushLongLtl(80001000); // TODO
}


void    QueryTime38(void)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x04);
  PushChar(0x00);
  PushChar(0x01);

  Query38(100+18, 14);
}


time    ReadTime38(void)
{
  uint w = DFF_Decoder(&mpbInBuff3[11], 0);

  MonitorIn();
  InitPop(11);
  ulong dw = PopLongLtl();

  time ti = SecIndexToDate(dw);
  ti.bYear += 12;

  return ti;
}



void    QueryEngAbs38(uchar  ibLine)
{
  InitPush(0);

  PushChar(0xC0);
  PushChar(0x06);

  PushAddress38();

  PushChar(0x00);
  PushChar(0x06);

  PushChar(0x0A);
  PushChar(0x00);
  PushChar(0x01 + ibLine);

  PushChar(0x02);
  PushChar(0x00);

  Query38(100+17, 16);
}


ulong   ReadEngAbs38(void)
{
  uint w = DFF_Decoder(&mpbInBuff3[11], 0);

  MonitorIn();
  InitPop(11);
  ulong dw = PopChar() + PopChar()*0x100 + PopChar()*0x10000;

  MonitorLongDec(dw);

  return dw;
}
