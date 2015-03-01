/*------------------------------------------------------------------------------
ENERGY.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "engine.h"
#include        "memory/mem_factors.h"
#include        "memory/mem_energy.h"
#include        "memory/mem_energy_spec.h"
#include        "memory/mem_groups.h"
#include        "memory/mem_tariffs.h"
#include        "memory/mem_realtime.h"
#include        "memory/mem_current.h"
#include        "memory/mem_special.h"
#include        "digitals/digitals.h"
#include        "digitals/sensors.h"
#include        "groups.h"



uint    GetCanInt(uint  *mpwT, uchar  ibCan) {
	ASSERT(ibCan < bCANALS);
  return mpwT[ibCan];
}


void    SetCanInt(uint  *mpwT, uchar  ibCan, uint  wT) {
	ASSERT(ibCan < bCANALS);
  mpwT[ibCan] = wT;
}



ulong   GetCanLong(ulong  *mpdwT, uchar  ibCan) {
	ASSERT(ibCan < bCANALS);
  return mpdwT[ibCan];
}


void    SetCanLong(ulong  *mpdwT, uchar  ibCan, ulong  *pdwT) {
	ASSERT(ibCan < bCANALS);
  mpdwT[ibCan] = *pdwT;
}



real    GetCanReal(real  *mpreT, uchar  ibCan) {
	ASSERT(ibCan < bCANALS);
  return mpreT[ibCan];
}


void    SetCanReal(real  *mpreT, uchar  ibCan, real  *preT) {
	ASSERT(ibCan < bCANALS);
  mpreT[ibCan] = *preT;
}



ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff) {
  return( &mpimT[ibCanal].mpdwImp[ibTariff] );
}



ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal)
{
uchar   i;
static ulong   dw;

  dw = 0;
  for (i=0; i<bTARIFFS; i++)
    dw += *PGetCanImp(mpimT,ibCanal,i);

  return( &dw );
}



// ������������ ��������� �������� �� ������ ���������� ������� uint (����������� ��������)
real    GetGrpMntInt2Real(uint  *mpwT, uchar  ibGrp, uchar  bMul)
{
uchar   i, j;
real    reA, reB;

  reA = 0;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    j = GetGroupsNodeCanal(ibGrp,i);
    reB = GetCanReal(mpreValueEngMnt,j) * GetCanInt(mpwT,j);

    if (GetGroupsNodeSign(ibGrp,i) == 0)
      reA += reB;
    else
      reA -= reB;
  }

  reA *= bMul;
  return reA;
}


// ������������ ��������� �������� �� ������ ���������� ������� uint (����������� ��������)
real    GetCanMntInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMul)
{
real    re;

  re = GetCanReal(mpreValueEngMnt,ibCan) * GetCanInt(mpwT,ibCan);

  re *= bMul;
  return re;
}



// ������������ ��������� �������� �� ������ ���������� ������� uint (����������� ��������)
real     GetGrpHouInt2Real(uint  *mpwT, uchar  ibGroup, uchar  bMul)
{
uchar   i, j;
real    reA, reB;

  reA = 0;
  for (i=0; i<GetGroupsSize(ibGroup); i++)
  {
    j = GetGroupsNodeCanal(ibGroup,i);

    if (GetCanInt(mpwT,j) == 0xFFFF)
      reB = 0;
    else
      reB = GetCanReal(mpreValueEngHou,j) * GetCanInt(mpwT,j);

    if (GetGroupsNodeSign(ibGroup,i) == 0)
      reA += reB;
    else
      reA -= reB;
  }

  reA *= bMul;
  return reA;
}


// ������������ ��������� �������� �� ������ ���������� ������� uint (����������� ��������)
real    GetCanHouInt2Real(uint  *mpwT, uchar  ibCanal, uchar  bMul)
{
real    re;

  if (GetCanInt(mpwT,ibCanal) == 0xFFFF)
    re = 0;
  else
    re = GetCanReal(mpreValueEngHou,ibCanal) * GetCanInt(mpwT,ibCanal);

  re *= bMul;
  return re;
}


real    GetPowGrpHouCurr(uchar  ibGroup, uchar  bMul)
{
uchar   i, j;
real    reA, reB; 

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reB = 0;
  for (i=1; i<=j; i++)
    reB += GetGrpMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], ibGroup, bMul);

  reA = 10*reB/j;

  return reA;
}


real    GetPowCanHouCurr(uchar  ibCan, uchar  bMul)
{
uchar   i,j;
real    reA, reB;

  j = (tiCurr.bMinute % 30) / 3;
  if (j == 0) j = 10;

  reB = 0;
  for (i=1; i<=j; i++)
    reB += GetCanMntInt2Real(mpwImpMntCan[ (bMINUTES+ibSoftMnt-i) % bMINUTES ], ibCan, bMul);

  reA = 10*reB/j;

  return reA;
}



// ������������ ��������� �������� �� ������ ���������� ������� impulse (�������� � �������� �������)
real    GetGrpImp2RealEng(impulse  *mpimT, uchar  ibGrp, uchar  bMask)
{
uchar   i, j;
real    reA, reB;
ulong   dw;

  reA = 0;
  for (i=0; i<GetGroupsSize(ibGrp); i++)
  {
    j = GetGroupsNodeCanal(ibGrp,i);

    dw = 0;

    if ((bMask & 0x01) != 0)
      dw += *PGetCanImp(mpimT,j,0);
    if ((bMask & 0x02) != 0)
      dw += *PGetCanImp(mpimT,j,1);
    if ((bMask & 0x04) != 0)
      dw += *PGetCanImp(mpimT,j,2);
    if ((bMask & 0x08) != 0)
      dw += *PGetCanImp(mpimT,j,3);

    reB = GetCanReal(mpreValueEngHou,j) * dw;

    if (GetGroupsNodeSign(ibGrp,i) == 0)
      reA += reB;
    else
      reA -= reB;
  }

  return reA;
}



// ������������ ��������� �������� �� ������ ���������� ������� impulse (�������� � �������� �������)
real    GetCanImp2RealEng(impulse  *mpimT, uchar  ibCan, uchar  bMask)
{
real    re;
ulong   dw;

  dw = 0;

  if ((bMask & 0x01) != 0)
    dw += *PGetCanImp(mpimT,ibCan,0);
  if ((bMask & 0x02) != 0)
    dw += *PGetCanImp(mpimT,ibCan,1);
  if ((bMask & 0x04) != 0)
    dw += *PGetCanImp(mpimT,ibCan,2);
  if ((bMask & 0x08) != 0)
    dw += *PGetCanImp(mpimT,ibCan,3);

  re = GetCanReal(mpreValueEngHou,ibCan) * dw;

  return re;
}


/*
// ������������ �������� ��� ���������� ���������
void    MakeImpSpec(impulse  *mpimT)
{
uchar   j;

  j = mpibEngPrevTariff[ tiAlt.bHour*2 + tiAlt.bMinute/30 ];

  dwBuffC  = *PGetCanImp(mpimT,ibCan,j);

  if (*PGetCanInt(mpwImpHouCanSpec, ibCan) != 0xFFFF)
    dwBuffC += *PGetCanInt(mpwImpHouCanSpec, ibCan);

  mpimT[ibCan].mpdwImp[j] = dwBuffC;
}
// ������� ��������������� ��������� ���������� tiAlt


// ������������ �������� ��� ���������� ���������: �� ��������� �������� ��������
void    MakeImpSpec_Winter(impulse  *mpimT)
{
uchar   j;

  j = mpibEngPrevTariff[ tiAlt.bHour*2 + tiAlt.bMinute/30 ];

  dwBuffC  = *PGetCanImp(mpimT,ibCan,j);

  dwBuffC -= *PGetCanInt(mpwImpHouCanSpec, ibCan);

  mpimT[ibCan].mpdwImp[j] = dwBuffC;
}
// ������� ��������������� ��������� ���������� tiAlt
*/


// ��������� � ���������� ������� impulse (�� �������� ������ ��� �������)
void    AddCanImpEng(impulse  *mpimT, uchar  ibCanal, uchar  wImp)
{
uchar   i;

  i = tiPrev.bHour*2 + tiPrev.bMinute/30;
  mpimT[ibCanal].mpdwImp[ mpibEngCurrTariff[i] ] += wImp;
}



// ����������� �������� ��������� ��� �������� ������
void    MakeCntMonCan(void)
{
uchar  c;
real   re;

  for (c=0; c<bCANALS; c++)
  {
    if (GetDigitalDevice(c) == 0)
    {
      re  = *PGetCanImpAll(mpimAbsCan,c);
      re *= GetCanReal(mpreValueCntHou,c);
      re += GetCanReal(mpreCount,c);
    }
    else
    {
      re = mpdwBase[c] * GetCanReal(mpreValueCntHou,c);
      if (GetDigitalDevice(c) == 19) re += GetCanReal(mpreCount,c);
    }

    SetCanReal(mpreCntMonCan[ ibSoftMon ],c, &re);
  }
}


// ������������ ��������� ��������� �� ���������� ���������
real    GetCntCurrImp(uchar  ibCan)
{
real    re;

  if (GetDigitalDevice(ibCan) == 19)
  {
    re = mpdwBase[ibCan] * GetCanReal(mpreValueCntHou,ibCan);
    re += GetCanReal(mpreCount,ibCan);
  }
  else
  {
    re  = GetCanInt(mpwImpMntCan1[ibSoftMnt],ibCan) * GetCanReal(mpreValueCntMnt,ibCan);
    re += *PGetCanImpAll(mpimAbsCan,ibCan)         * GetCanReal(mpreValueCntHou,ibCan);
    re += GetCanReal(mpreCount,ibCan);
  }

  return re;
}



void    MakeImpulse(void)
{
uchar  ibCan;
uint   w;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (mpboUsedNodes[ibCan] == false) continue;

    if (GetDigitalDevice(ibCan) == 0)
    {
      w = GetCanInt(mpwImpMntCanCurr,ibCan);
      mpwImpHouCan[ibSoftHou][ibCan] += w;

      AddCanImpEng(mpimDayCan[ibSoftDay], ibCan, w);
      AddCanImpEng(mpimMonCan[ibSoftMon], ibCan, w);
      AddCanImpEng(mpimAbsCan,            ibCan, w);
    }
  }
}


void    MakeImpulseSpec(void)
{
uchar  ibCan;
uint   w;

  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    if (mpboUsedNodes[ibCan] == false) continue;

    if (GetDigitalDevice(ibCan) == 0)
    {
      w = GetCanInt(mpwImpMntCanCurr,ibCan);
      mpwImpHouCan[ibSoftHou][ibCan] += w;

      AddCanImpEng(mpimDayCan[ibSoftDay], ibCan, w);
      AddCanImpEng(mpimMonCan[ibSoftMon], ibCan, w);
      AddCanImpEng(mpimAbsCan,            ibCan, w);

      if ((tiOldDay.bYear  == tiCurr.bYear)  &&
          (tiOldDay.bMonth == tiCurr.bMonth) &&
          (tiOldDay.bDay   == tiCurr.bDay))
        AddCanImpEng(mpimDayCanSpec, ibCan, w);

      if ((tiOldMon.bYear  == tiCurr.bYear)  &&
          (tiOldMon.bMonth == tiCurr.bMonth))
        AddCanImpEng(mpimMonCanSpec, ibCan, w);
    }
  }
}
