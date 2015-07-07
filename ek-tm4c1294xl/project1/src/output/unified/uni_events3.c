/*------------------------------------------------------------------------------
UNI_EVENTS3.C


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
#include "uni_events0.h"
#include "uni_events3.h"



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


time    PushEventParams(void)
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
      {
        time  ti;
        ti.bSecond = reCurr.mpbBuff[0];
        ti.bMinute = reCurr.mpbBuff[1];
        ti.bHour   = reCurr.mpbBuff[2];
        ti.bDay    = reCurr.mpbBuff[3];
        ti.bMonth  = reCurr.mpbBuff[4];
        ti.bYear   = reCurr.mpbBuff[5];

        combo32 co;
        co.dwBuff = DateToSecIndex(ti);

        PushChar(co.mpbBuff[0]);
        PushChar(co.mpbBuff[1]);
        PushChar(co.mpbBuff[2]);
        PushChar(co.mpbBuff[3]);
      }
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

  return reCurr.ti;
}



void    GetEventsMessagesUni(void) 
{
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

    uchar i;
    for (i=0; i<bInBuff9; i++)
    {
      PushEventsMessage(bInBuff8 + i);
    }

    Output2(2+bInBuff9*64);
  }
}
