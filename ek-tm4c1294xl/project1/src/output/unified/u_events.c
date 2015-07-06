/*------------------------------------------------------------------------------
U_EVENTS.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_records.h"
#include "../../memory/mem_flash.h"
#include "../../include/flash.h"
#include "../../include/queries_uni.h"
#include "../../serial/ports.h"
#include "../../serial/ports2.h"
#include "../../serial/print2.h"
#include "../../flash/records.h"
#include "../../flash/records2.h"
#include "../../time/timedate.h"
#include "../../time/calendar.h"
#include "../../time/rtc.h"
#include "../../hardware/watchdog.h"
#include "response_uni.h"



static time             tiT;



uint    GetPagesCount(uchar  ibClass)
{
  if (ibClass == 1)
    return bRECORD_PAGES;
  else if (ibClass == 2) 
    return wRECORD2_PAGES;
  else
    return bRECORD_PAGES;
}


uint    GetMaxRecordsCount(uchar  ibClass)
{
  if (ibClass == 1)
    return wRECORDS;
  else if (ibClass == 2) 
    return wRECORDS2;
  else
    return wRECORDS;
}


uint    GetRecordsCount(uchar  ibClass)
{
  if (ibClass == 1)
    return (cdwSysRecord < wRECORDS) ? cdwSysRecord : wRECORDS;
  else if (ibClass == 2) 
    return (cdwAuxRecord < wRECORDS2) ? cdwAuxRecord : wRECORDS2;
  else
    return (cdwImpRecord < wRECORDS) ? cdwImpRecord : wRECORDS;
}


void    LoadEventsPage(uchar  ibClass, uint  iwPage)
{
  x_str("\n\n page"); x_intdec(iwPage);
  ResetWDT();

  if (ibClass == 1)
    GetRecordsBlock(CLA_SYSTEM, iwPage);
  else if (ibClass == 2) 
    GetRecordsBlock2(CLA_AUXILIARY, iwPage);
  else
    GetRecordsBlock(CLA_IMPULSE, iwPage);

  x_str("\n");
  uint i;
  for (i=0; i<wLEAF_BYTES; i++)
  {
    if (i % SIZEOF_RECORD == 0) { x_str("\n"); x_bytedec(i / SIZEOF_RECORD); }
    x_bytehex(mpbPageIn[i]);
  }
  x_str("\n");
}


time   ReadEventBlock(uchar  ibBlock) // 1 .. bRECORD_BLOCK
{
  uchar* pBuff = (uchar *) &mpbPageIn + ((ibBlock-1) % bRECORD_BLOCK)*SIZEOF_RECORD;
  BuffToRecord(pBuff);

  x_str("\n block"); x_bytedec(ibBlock-1);
  x_intdec(reCurr.cdwRecord);
  x_bytedec(reCurr.ev);
  if (reCurr.ev != 0xFF) x_time(reCurr.ti);

  return reCurr.ti;
}



void    IncEventsCount(uint  i)
{
uint    j;

  i = 6+1+2+2+i*4;
  j = 0x100*GetOutBuff(i+0)+GetOutBuff(i+1);
  j++;
  SetOutBuff(i+0, j / 0x100);
  SetOutBuff(i+1, j % 0x100);
}


void    PushEventsCounts(void)
{
uint    iwPage;
uchar   ibBlock;

  x_str("\n\n get events table ");
  x_str("\n day index "); x_intdec(0x100*bInBuff8+bInBuff9);
  x_str("\n days count "); x_intdec(0x100*bInBuffA+bInBuffB);

  tiT = *GetCurrTimeDate();
  ulong dw1 = DateToDayIndex(tiT);

  bool f = 0;

  for (iwPage=0; iwPage<GetPagesCount(bInBuff7); iwPage++)
  { 
    LoadEventsPage(bInBuff7, iwPage);

    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--) 
    { 
    	tiT = ReadEventBlock(ibBlock);

      x_str(" countdown "); x_intdec(bRECORD_BLOCK*iwPage + (bRECORD_BLOCK-ibBlock)); x_intdec(GetRecordsCount(bInBuff7) + bRECORD_BLOCK);
      if (bRECORD_BLOCK*iwPage + (bRECORD_BLOCK-ibBlock) > GetRecordsCount(bInBuff7) + bRECORD_BLOCK)
      {
        x_str(" exit ");
        return;
      }
      else
      {
        ulong dw2 = DateToDayIndex(tiT);
        x_str(" delta "); x_longdec(dw1); x_str("-"); x_longdec(dw2); x_str("="); x_longdec(dw1 - dw2);

        if ((f == 0) && (dw1 >= dw2))
        {
          if (dw1 - dw2 >= 0x100*bInBuff8+bInBuff9)
          {
            x_str(" start ");
            f = 1;
          }
        }

        if (f == 1)
        {
          x_str(" add ");
          IncEventsCount(dw1 - dw2);

          if (dw1 - dw2 >= (0x100*bInBuff8+bInBuff9) + (0x100*bInBuffA+bInBuffB))
          {
            x_str(" stop ");
            return;
          }
        }
      }
    }
  }
}


void    GetEventsCountsUni(void)
{
uint    i;

  if (bInBuff6 != 0)
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 3))
    Result2_Info(bUNI_BADDATA,2);
  else if (0x100*bInBuffA+bInBuffB == 0)
    Result2_Info(bUNI_BADDATA,3);
  else
  {
    InitPushUni();

    PushChar(bInBuff7);
    PushInt(GetMaxRecordsCount(bInBuff7));
    PushInt(GetRecordsCount(bInBuff7));
    
    time ti = *GetCurrTimeDate();
    ulong dw = DateToDayIndex(ti);

    for (i=0; i<0x100*bInBuffA+bInBuffB; i++)
    {
      PushInt(0);
      PushChar(ti.bDay);
      PushChar(ti.bMonth);

      ti = DayIndexToDate(--dw);
    }

    x_init();
    PushEventsCounts();
    x_done();

    Output2(1+2+2+(0x100*bInBuffA+bInBuffB)*4);
  }
}



void    PushEventText(uchar  *szT)
{
uchar   i;

  bool f = 1;
  for (i=0; i<63-1; i++)
  {
    if (!*szT) f = 0;
    if (f == 1) PushChar(*szT++); else PushChar(0);
  }

  PushChar(0);
}


void    PushEventsMessage(uchar  bCode)
{
  PushChar(bCode);

  switch (bCode)
  {
    case EVE_PREVNEXTTIME2:   PushEventText("������ ������� ����� ���������� #t4"); break;
    case EVE_POSTNEXTTIME:    PushEventText("�����  �������"); break;
    case EVE_WATCHDOG:        PushEventText("Watchdog reset"); break;
    case EVE_START:           PushEventText("������"); break;
    case EVE_RESTART:         PushEventText("����������"); break;
    case EVE_PASSWORD:        PushEventText("��������������"); break;
    case EVE_DOOROPEN:        PushEventText("������ �������"); break;
    case EVE_DOORCLOSE:       PushEventText("������ �������"); break;

    case EVE_PROGRAM_2:       PushEventText("��������� c ����������: #t4"); break;
    case EVE_EXT_CORRECT2:    PushEventText("��������� - ������ 0xFF 0x0B: #t4"); break;
    case EVE_ESC_K:           PushEventText("��������� - ������ Esc K: #t4"); break;
    case EVE_ESC_k:           PushEventText("��������� - ������ Esc k: #t4"); break;
    case EVE_INQ_CORRECT1:    PushEventText("��������� 1: #t4"); break;
    case EVE_INQ_CORRECT2:    PushEventText("��������� 2: #t4"); break;
    case EVE_INQ_CORRECT4:    PushEventText("��������� 3: #t4"); break;
    case EVE_TIME_OK:         PushEventText("���������: ��"); break;

    case 62: PushEventText("����� �������� !"); break;
    case 63: PushEventText("������� �������� !"); break;
    case 64: PushEventText(" ����� #bd[0], ���������� ����� *"); break;
    case 65: PushEventText(" ����� #bd[0], ������ ����� *"); break;
    case 99: PushEventText("����������: #id[0]-#id[1] ========"); break;
    case 78: PushEventText("����������: ����� ���������"); break;
    case 97: PushEventText("����������: #id[0]-#id[1] *"); break;
    case 81: PushEventText("������ �������"); break;
    case 82: PushEventText("�����  �������"); break;
    case 83: PushEventText("������ �����"); break;
    case 84: PushEventText("�����  �����"); break;
    case 86: PushEventText("����� �������� ! ========"); break;
    case 87: PushEventText("����� ������� ==========="); break;
    case 88: PushEventText("������ ������� 1"); break;
    case 89: PushEventText("�����  ������� 1"); break;
    case 90: PushEventText("��� �������"); break;
    case 91: PushEventText("������ ������� 2"); break;
    case 92: PushEventText("�����  ������� 2"); break;
    case 93: PushEventText("������ #bh[0].#bh[1].#bh[2]"); break;
    case 94: PushEventText("����� �������� �� #id[0] ���."); break;
    case 95: PushEventText("������ ������� ������ �������� *"); break;
    case 96: PushEventText("�����  ������� ������ �������� "); break;
    case 98: PushEventText("����������� �����: 0x#ih[0]"); break;

    default: PushEventText(" ��� �������� ��� �������"); break;
  }
}


void    PushEventParams(void)
{
  switch (reCurr.ev)
  {
    case EVE_PREVNEXTTIME2: 

    case EVE_PROGRAM_2: 
    case EVE_EXT_CORRECT2: 
    case EVE_ESC_K: 
    case EVE_ESC_k: 
    case EVE_INQ_CORRECT1: 
    case EVE_INQ_CORRECT2: 
    case EVE_INQ_CORRECT4: 
      tiT.bSecond = reCurr.mpbBuff[0];
      tiT.bMinute = reCurr.mpbBuff[1];
      tiT.bHour   = reCurr.mpbBuff[2];
      tiT.bDay    = reCurr.mpbBuff[3];
      tiT.bMonth  = reCurr.mpbBuff[4];
      tiT.bYear   = reCurr.mpbBuff[5];

      combo32 co;
      co.dwBuff = DateToSecIndex(tiT);

      PushChar(co.mpbBuff[0]);
      PushChar(co.mpbBuff[1]);
      PushChar(co.mpbBuff[2]);
      PushChar(co.mpbBuff[3]);
      break;

    case 64: 
    case 65: 
      PushChar(reCurr.mpbBuff[0]+1);
      PushChar(0);
      PushChar(0);
      PushChar(0);
      break;

    case 93: 
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      PushChar(0);
      break;

    case 94: 
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(0);
      PushChar(0);
      break;

    case 98: 
      PushChar(reCurr.mpbBuff[0]);
      PushChar(reCurr.mpbBuff[1]);
      PushChar(0);
      PushChar(0);

    case 97: 
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      PushChar(reCurr.mpbBuff[4]);
      PushChar(reCurr.mpbBuff[5]);
      break;

    case 99: 
      PushChar(reCurr.mpbBuff[0]);
      PushChar(reCurr.mpbBuff[1]);
      PushChar(reCurr.mpbBuff[2]);
      PushChar(reCurr.mpbBuff[3]);
      break;

    default: PushChar(0); PushChar(0); PushChar(0); PushChar(0); break;  
  }

  tiT = reCurr.ti;
}



void    PushEvents2(uint  iwPage, uchar  ibBlock, uchar  bTotal)
{
uchar   i,j;

  x_str("\n\n push events \n");
  x_str("\n page "); x_intdec(iwPage); x_str(" block "); x_bytedec(ibBlock-1); x_str(" total "); x_bytedec(bTotal);
  x_str(" index "); x_bytedec(bInBuffA); x_str(" count "); x_bytedec(bInBuffB);

  InitPushUni();

  j = 0;
  LoadEventsPage(bInBuff6, iwPage);

  for (i=0; i<bTotal; i++) 
  {
  	tiT = ReadEventBlock(ibBlock);

    x_str(" index "); x_bytedec(i);
    if (i+1 >= bInBuffA)
    { 
      if ((tiT.bDay == bInBuff7) && (tiT.bMonth == bInBuff8) && (tiT.bYear == bInBuff9))
      {
        x_str(" push ");
        PushChar(reCurr.ev);
        PushEventParams();

        PushChar(tiT.bMinute);
        PushChar(tiT.bHour);
        PushChar(tiT.bDay);
        PushChar(tiT.bMonth);
        PushChar(tiT.bYear);

        if (++j >= bInBuffB)
        {
          x_str("\n success");
          Output2(bInBuffB*10);
          return;
        }
      }
    }

    if (++ibBlock > bRECORD_BLOCK)
    {
      ibBlock = 1;
      if (iwPage > 0) 
      {
        iwPage--;
        LoadEventsPage(bInBuff6, iwPage);
      }
      else
      {
        x_str("\n underflow");
        Result2_Info(bUNI_BADDATA,7);
        return;
      }
    }
  }

  x_str("\n failure");
  Result2_Info(bUNI_BADDATA,8);
}


void    PushEvents1(void)
{
uint    iwPage,i;
uchar   ibBlock,j,bTotal;

  x_str("\n\n get events \n");
  x_bytedec(bInBuff7); x_str("."); x_bytedec(bInBuff8); x_str("."); x_bytedec(bInBuff9);
  x_str(" index "); x_bytedec(bInBuffA); x_str(" count "); x_bytedec(bInBuffB);

  bool f = 0;
  bTotal = 0;
  i = 0;
  j = 0;

  for (iwPage=0; iwPage<GetPagesCount(bInBuff6); iwPage++)
  {
    LoadEventsPage(bInBuff6, iwPage);

    for (ibBlock=bRECORD_BLOCK; ibBlock>0; ibBlock--) 
    { 
    	tiT = ReadEventBlock(ibBlock);

      if ((tiT.bDay == bInBuff7) && (tiT.bMonth == bInBuff8) && (tiT.bYear == bInBuff9))
      { 
        x_str(" calc ");

        f = 1;
        bTotal++;
        i = iwPage;
        j = ibBlock;
      }
      else
      {
        if (f == 1)
        { 
          x_str("\n success");
          PushEvents2(i, j, bTotal);
          return;
        }
      }
    }
  }

  x_str("\n failure");
  Result2_Info(bUNI_BADDATA,6);
}


void    GetEventsUni(void)
{
  if ((bInBuff6 < 1) || (bInBuff6 > 3))
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 31))
    Result2_Info(bUNI_BADDATA,2);
  else if ((bInBuff8 < 1) || (bInBuff8 > 12))
    Result2_Info(bUNI_BADDATA,3);
  else if (bInBuff9 > 99)
    Result2_Info(bUNI_BADDATA,4);
  else if (bInBuffB == 0)
    Result2_Info(bUNI_BADDATA,5);
  else
  {
    x_init();
    SetDelayUni();
    PushEvents1();
    x_done();
  }
}



void    GetEventsMessagesUni(void) 
{
uchar   i;

  if (bInBuff6 != 0)
    Result2_Info(bUNI_BADDATA,1);
  else if ((bInBuff7 < 1) || (bInBuff7 > 3))
    Result2_Info(bUNI_BADDATA,2);
  else if (bInBuff9 == 0)
    Result2_Info(bUNI_BADDATA,3);
  else if ((uint)(bInBuff8 + bInBuff9 - 1) > 255)
    Result2_Info(bUNI_BADDATA,4);
  else
  {
    SetDelayUni();

    InitPushUni();

    PushChar(bInBuff7);
    PushChar(0xFF);

    for (i=0; i<bInBuff9; i++)
      PushEventsMessage(bInBuff8 + i);

    Output2(2+bInBuff9*64);
  }
}
