/*------------------------------------------------------------------------------
DIAGRAM!C

 ������ �������� ��������� �� ��������� �� ����� ('����� �65 �� 03.08.2010')
------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_diagram.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_energy.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_ports.h"
#include "../../hardware/watchdog.h"
#include "../../digitals/digitals.h"
#include "../../realtime/realtime.h"
#include "../../energy.h"
#include "../../flash/flash.h"
#include "../../flash/files.h"
#include "../../time/rtc.h"
#include "../../serial/ports.h"
#include "diagram.h"



bool    SaveDgrHou(uint  iwHouTo)
{
  ASSERT(iwHouTo < wHOURS);
  return SaveBuff(DIAGRAM_HHR_VALUES + iwHouTo*DIAGRAM_CAN_PAGES, mpDiagram, sizeof(mpDiagram));
}


bool    LoadDgrHou(uint  iwHouFrom)
{
  ASSERT(iwHouFrom < wHOURS);
  return LoadBuff(DIAGRAM_HHR_VALUES + iwHouFrom*DIAGRAM_CAN_PAGES, mpDiagram, sizeof(mpDiagram));
}



bool    ClearDiagram(void)
{
  uint wPageOut;
  for (wPageOut=DIAGRAM_HHR_VALUES; wPageOut<DIAGRAM_HHR_VALUES+DIAGRAM_PAGES; wPageOut++)
  {
    if (SafePageErase(wPageOut) == 0) return(0);
    if (GetFlashStatus() != 0) return(0);
    ResetWatchdog();
  }

  return 1;
}



void    NextHouDiagram(void)
{
  LoadDgrHou(iwHardHou);

  memset(&mpDiagram, 0xFF, sizeof(mpDiagram));

  uchar c;
  for (c=0; c<16; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      double db = *PGetCanImpAll(mpimAbsCan,c);
      db *= mpdbValueCntHou[c];
      db += mpdbCount[c];

      diagram vl;
      vl.dbValue = db;

      time ti = *GetCurrTimeDate();
      vl.stValue.bSecond = ti.bSecond;
      vl.stValue.bMinute = ti.bMinute;
      vl.stValue.bHour   = ti.bHour;

      mpDiagram[c] = vl;
    }
  }

  SaveDgrHou(iwHardHou);
}


void    MakeDiagram(uchar  ibCan, double  db)
{
  LoadDgrHou(iwHardHou);

  diagram vl;
  vl.dbValue = db;

  time ti = *GetCurrTimeDate();
  vl.stValue.bSecond = ti.bSecond;
  vl.stValue.bMinute = ti.bMinute;
  vl.stValue.bHour   = ti.bHour;

  mpDiagram[ibCan] = vl;

  SaveDgrHou(iwHardHou);
}



// ������ �� ������ ������� ��������� ����� �����
static uint GetDayHouIndex_Diagram(uchar  ibDay)
{
  // ������ �� ������ ������� ������� �����
  uint w = (wHOURS_DIAGRAM+iwHardHou-GetCurrHouIndex()) % wHOURS_DIAGRAM;

  // ������� �� ������ �������� ����� �����
  uchar i;
  for (i=0; i<ibDay; i++)
  {
    w = (wHOURS_DIAGRAM+w-48) % wHOURS_DIAGRAM;
  }

  // ������ �� ������ ������� ��������� �����
  return w;
}


void    OutDiagram(bool  fDouble)
{
  if (bInBuff6 > wHOURS_DIAGRAM/48) { Result(bRES_BADADDRESS); return; }
  uint iwHhr = GetDayHouIndex_Diagram(bInBuff6);

  InitPushPtr();
  uint wSize = 0;

  uchar h;
  for (h=0; h<48; h++)
  {
    if (LoadDgrHou(iwHhr) == false) { Result(bRES_BADFLASH); return; }

    uchar c;
    for (c=0; c<bCANALS; c++)
    {
      if ((InBuff(7 + c/8) & (0x80 >> c%8)) != 0) 
      {
        if ((bInBuff6 == 0) && (h > GetCurrHouIndex()))
        {
          uchar i;
          for (i=0; i<GetFloatOrDoubleSize(fDouble); i++)
          {
            wSize += PushChar(0xFF);
          }

          wSize += PushChar(0xFF);
          wSize += PushChar(0xFF);
          wSize += PushChar(0xFF);
        }
        else
        {
          diagram vl = mpDiagram[c];

          wSize += PushFloatOrDouble(vl.dbValue, fDouble);

          wSize += PushChar(vl.stValue.bSecond);
          wSize += PushChar(vl.stValue.bMinute);
          wSize += PushChar(vl.stValue.bHour);
        }

        if (wSize >= (wOUTBUFF_SIZE-0x40)) { Result(bRES_OUTOVERFLOW); return; }
      } 
    }
          
    if (++iwHhr >= wHOURS_DIAGRAM) iwHhr = 0;
  }      

  OutptrOutBuff(wSize);
}

