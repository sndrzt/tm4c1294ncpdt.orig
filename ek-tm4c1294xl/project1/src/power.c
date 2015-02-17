/*------------------------------------------------------------------------------
POWER.C

 ��������� ��������
------------------------------------------------------------------------------*/

#include        "main.h"
#include        "memory/mem_realtime.h"
#include        "memory/mem_tariffs.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_energy_spec.h"
#include        "realtime/realtime.h"
#include        "engine.h"
#include        "energy.h"



void    SetGrpMaxPow(power  *mppoT, uchar  ibGrp, uchar  ibTar, value  *pvaT)
{  
	ASSERT(ibGrp < bGROUPS);
	ASSERT(ibTar < bTARIFFS);
  mppoT[ibGrp].mpmaMax[ibTar] = *pvaT;
}


real    GetGrpMaxPowReal(power  *mppoT, uchar  ibGrp, uchar  ibTar)
{  
	ASSERT(ibGrp < bGROUPS);
	ASSERT(ibTar < bTARIFFS);
  return mppoT[ibGrp].mpmaMax[ibTar].reSelf;
}


time    GetGrpMaxPowTime(power  *mppoT, uchar  ibGrp, uchar  ibTar)
{
	ASSERT(ibGrp < bGROUPS);
	ASSERT(ibTar < bTARIFFS);
  return mppoT[ibGrp].mpmaMax[ibTar].tiSelf;
}



// ������� ������ ������ � ���������� ��������� value �� ���� �������
uchar   GetGrpMaxPowIndex(power  *mppoT, uchar  ibGrp)
{
uchar  i,j;

  j = 0;
  for (i=0; i<bTARIFFS; i++)
  {
    if (GetGrpMaxPowReal(mppoT,ibGrp,i) >=
        GetGrpMaxPowReal(mppoT,ibGrp,j))
      j = i;
  }

  return(j);
}



void    MakeMaxPow(power  *mppoT)
{
uchar   g,t;
real   	re;
static value va;

  t = mpibPowCurrTariff[tiPrev.bHour*2 + tiPrev.bMinute/30];

  for (g=0; g<bGROUPS; g++)
  {
    re = GetGrpHouInt2Real(mpwImpHouCan[ ibSoftHou ],g,2);
    if (re >= GetGrpMaxPowReal(mppoT,g,t))
    {
      va.reSelf = re;
      va.tiSelf = tiPrev;
      SetGrpMaxPow(mppoT,g,t,&va);
    }
  }
}


void    MakeMaxPowSpec(power  *mppoT, uchar  ibGrp, time  *ptiT)
{
uchar		t;
real   	re;
static value va;

  t = mpibPowPrevTariff[ ptiT->bHour*2 + ptiT->bMinute/30 ];

  re = GetGrpHouInt2Real(mpwImpHouCanSpec,ibGrp,2);
  if (re >= GetGrpMaxPowReal(mppoT,ibGrp,t))
  {
    va.reSelf = re;
    va.tiSelf = *ptiT;
    SetGrpMaxPow(mppoT,ibGrp,t,&va);
  }
}


// ������ ���������� �������� �� ������� ����� � �����
void    MakeMaxPowAll(void)
{       
  MakeMaxPow( mppoDayGrp[ibSoftDay] );
  MakeMaxPow( mppoMonGrp[ibSoftMon] );
}
