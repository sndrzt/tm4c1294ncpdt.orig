/*------------------------------------------------------------------------------
REFILL!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_profile.h"
#include "../../memory/mem_energy_spec.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../realtime/realtime_spec.h"
#include "../../digitals/digitals.h"
#include "../../devices/devices.h"
#include "../../impulses/energy_spec.h"
#include "../../time/decret.h"
#include "../../flash/records.h"
#include "../../nvram/cache.h"
#include "refill.h"



// ������ ������� ������������������ ����������� ��������
bool                    boDsblRefill;

// ���������� ��� ���������� ����������� ���������
uint                    iwBmin, iwBmax;

// ���������� ��� ��������� �������� �� ������ �����
static uchar            bRefillWinter, mpbRefillWinter[10];


cache const             chDsblRefill = {DSBL_REFILL, &boDsblRefill, sizeof(bool)};



void    InitRefill(void)
{
  LoadCache(&chDsblRefill);
}


void    ResetRefill(void)
{
  boDsblRefill = false;
  SaveCache(&chDsblRefill);
}


void    StartRefill(void)
{
  iwBmin = 0xFFFF;
  memset(&mpbRefillWinter, 0, sizeof(mpbRefillWinter));
}



void    DoRefill(void)
{
  uint iwB = 0;
  uint iwHhr = iwBmin;
  
  while (iwHhr != iwBmax) {
    if (fKey == true) { fKey = 0; Beep(); }
    if ((iwHhr % 0x10) == 0) NexttimeMnt();

    Clear();
    sprintf(szLo,"����������: %u",++iwB);

    LoadImpHouSpec(iwHhr,1);

    uchar ibCan;
    for (ibCan=0; ibCan<bCANALS; ibCan++)
    {
      if (CompareLines(ibDig,ibCan) == 1) 
        mpwImpHouCanSpec[ibCan] = 0; 
    }

    SaveImpHouSpec(1,iwHhr);

    iwHhr = (wHOURS+iwHhr-1)%wHOURS; 
  }
}



void    MakeRefillWinter(time  ti)
{
  if (IsWinter(ti)) {
    bRefillWinter = ++mpbRefillWinter[ti.bHour*2 + ti.bMinute/30];
  }
}



void    MakeRefill(time  ti)
{
  if (IsWinter(ti) && (bRefillWinter > 1)) return;

  if ((iwBmin != 0xFFFF) && (iwBmin != iwDigHou))
  {
    if ((iwDigHou+1)%wHOURS != iwBmin)
    { 
      iwBmin = (wHOURS+iwBmin-1)%wHOURS; 
      iwBmax = iwDigHou; 

      Clear(); AddDigRecord(EVE_REFILL1);
      DoRefill();
      Clear(); AddDigRecord(EVE_REFILL2);
    }
  }

  iwBmin = iwDigHou;
}



// ������: ���� ������� ��������-230 ���������������� ��� �������� �� ������ �����, � �������� (� �.�. ������) � ��������� �� ������ �����,
// �� ��� ��������� ������ ��� ������ ������� �� ������ �������� ��� ������� ��������� �� ������� �������� ����������.
