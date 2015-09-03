/*------------------------------------------------------------------------------
EXTENDED_3_B.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../console.h"
#include "../../memory/mem_extended_3.h"
#include "../../memory/mem_digitals.h"
#include "../../serial/ports.h"
#include "../../serial/ports_devices.h"
#include "../../devices/devices.h"
#include "../../sensors/automatic_b.h"
#include "../../flash/records.h"
#include "extended_3.h"
#include "extended_3_b.h"



void    ShowEventsB(uchar  ibEvent)
{
  ShowHi(szClear); ShowHi("�������:");
  Clear();
  switch (ibEvent) 
  {
    case 1: sprintf(szHi+9,"������"); break;
    case 3: sprintf(szHi+9,"���� 1"); break;
    case 4: sprintf(szHi+9,"���� 2"); break;
    case 5: sprintf(szHi+9,"���� 3"); break;
    default: Error(); break;
  }
}


void    QueryEventB(uchar  ibEvent, uchar  j)
{
  InitPush(0);

  PushChar(diCurr.bAddress);           
  PushChar(4);                       

  PushChar(ibEvent);
  PushChar(j);

  QueryIO(1+12+2, 2+2+2);
}


bool    QueryEventB_Full(uchar  ibEvent, uchar  j, uchar  bPercent)
{
  uchar i;
  for (i=0; i<bMINORREPEATS; i++)
  {
    DelayOff();
    QueryEventB(ibEvent,j);

    if (Input() == SER_GOODCHECK) break;  
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);
  ShowPercent(bPercent+j);

  return(1);
}


time    ReadEventB(void)
{
  time ti;
  ti.bSecond = FromBCD( PopChar() );
  ti.bMinute = FromBCD( PopChar() );
  ti.bHour   = FromBCD( PopChar() );
  ti.bDay    = FromBCD( PopChar() );
  ti.bMonth  = FromBCD( PopChar() );
  ti.bYear   = FromBCD( PopChar() );

  return ti;
}


uchar   GetEventCodeB(uchar  ibEvent)
{
  switch (ibEvent)
  {
    case 1: return INC_DEVICE;
    case 3: return INC_PHASE1;
    case 4: return INC_PHASE2;
    case 5: return INC_PHASE3;
    default: return INC_ERROR;
  }
}


void    ReadEventsB(uchar  ibEvent)
{
uchar j;
 
  ShowEventsB(ibEvent);

  if (QueryOpenB_Full(25) == 0) { bEventCode = 0; AddImpRecord(EVE_EVENTS_BADLINK); return; }

  uchar i;
  for (i=0; i<10; i++)
  {
    if (QueryEventB_Full(ibEvent,i,50) == 0) {  bEventCode = i+1; AddImpRecord(EVE_EVENTS_BADLINK); return; }

    InitPop(1);
    mptiEventAB1[i] = ReadEventB();
    mptiEventAB2[i] = ReadEventB();
  } 

  switch (ibEvent) {
    case 1: dwEventIndexPrev = mpdwEventDevice[ibDig]; break;
    case 3: dwEventIndexPrev = mpdwEventPhase1[ibDig]; break;
    case 4: dwEventIndexPrev = mpdwEventPhase2[ibDig]; break;
    case 5: dwEventIndexPrev = mpdwEventPhase3[ibDig]; break;
  }

  dwEventIndexCurr = 0;
  bool f = false;

  for (i=0; i<10; i++)
  {
    time ti = mptiEventAB1[i];
    if (dwEventIndexPrev == DateToEventIndex(ti)) f = true;
    if (dwEventIndexCurr < DateToEventIndex(ti))
    {
      dwEventIndexCurr = DateToEventIndex(ti);
      j = i;
    }

    ti = mptiEventAB2[i];
    if (dwEventIndexPrev == DateToEventIndex(ti)) f = true;
    if (dwEventIndexCurr < DateToEventIndex(ti))
    {
      dwEventIndexCurr = DateToEventIndex(ti);
      j = i;
    }
  }

  if (dwEventIndexCurr == 0) AddImpRecord(EVE_EVENTS_BADDATA);
  if ((f == false) && (mpboEventFirst[ibDig] == true)) { bEventCode = GetEventCodeB(ibEvent); AddImpRecord(EVE_EVENTS_OMISSION); }

  for (i=0; i<10; i++)
  {
    uchar k = (10 + j + i + 1) % 10;

    time ti = mptiEventAB1[k];
    if (dwEventIndexPrev < DateToEventIndex(ti))
    {
      bEventCode = GetEventCodeB(ibEvent);
      AddImpRecord(EVE_EVENTS_B);
    }

    ti = mptiEventAB2[k];
    if (dwEventIndexPrev < DateToEventIndex(ti))
    {
      bEventCode = GetEventCodeB(ibEvent) | 0x80; // �������� !
      AddImpRecord(EVE_EVENTS_B);
    }
  }   

  switch (ibEvent) {
    case 1: mpdwEventDevice[ibDig] = dwEventIndexCurr; break;
    case 3: mpdwEventPhase1[ibDig] = dwEventIndexCurr; break;
    case 4: mpdwEventPhase2[ibDig] = dwEventIndexCurr; break;
    case 5: mpdwEventPhase3[ibDig] = dwEventIndexCurr; break;
  }
}


void    ReadEventsAllB(void)
{
  if (mpboEventB[0] == true) {
    ReadEventsB(1);
  }
  if (mpboEventB[1] == true) {
    ReadEventsB(3);
  }
  if (mpboEventB[2] == true) {
    ReadEventsB(4);
  }
  if (mpboEventB[3] == true) {
    ReadEventsB(5);
  }
}
