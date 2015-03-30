/*------------------------------------------------------------------------------
CURRENT.C

 ������ ������������ �������� � �������� ���������
------------------------------------------------------------------------------*/

#include        "../../main.h"
#include        "../../memory/mem_realtime.h"
#include        "../../memory/mem_energy.h"
#include        "../../memory/mem_extended1.h"
#include        "../../digitals/digitals.h"
#include        "current.h"



// ��������� ���� ��������� ��� ����������� ��������
bool    IsSpecCurrent(uchar  i)
{
  if ((i == 12) ||
      (i == 16) ||
      (i == 17) ||
      (i == 18) ||
      (i == 19) ||
      (i == 23)) return(1);

  return(0);
}



void    MakeSpecCurrent(void)
{
  if (IsSpecCurrent(GetDigitalDevice(ibCan)) == 1)
  {
    // ��������� ���������� �� ���������
    uint w = (uint)dwUpdate;
    mpwImpHouCan[ibSoftHou][ibCan] += w;

    AddCanImpEng(mpimDayCan[ibSoftDay], ibCan);
    AddCanImpEng(mpimMonCan[ibSoftMon], ibCan);
    AddCanImpEng(mpimAbsCan,            ibCan);


    // ���������� ���������� ��� Esc V
    if (LoadCntMon(tiCurr.bMonth-1) == 0)
      reBuffA = 0;
    else
      reBuffA = *PGetCanReal(mpreCntMonCan[ PrevSoftMon() ], ibCan);

    SetCanReal(&mpreEsc_V, ibCan);

    tiAlt = *GetCurrTimeDate();
    SetCanTime(mptiEsc_V, ibCan);


    // ���������� ���������� ��� Esc S
    reBuffA  = mpdwBase[ibCan] * *PGetCanReal(mpreValueCntHou,ibCan);
    if (GetDigitalDevice(ibCan) == 19) reBuffA += *PGetCanReal(mpreCount,ibCan);
    SetCanReal(&mpreEsc_S, ibCan);

    tiAlt = *GetCurrTimeDate();
    SetCanTime(mptiEsc_S, ibCan);


    // ���������� ���������� ��� Esc U
    moAlt.tiAlfa = tiCurr;

    moAlt.tiBeta = *GetCurrTimeDate();
    SetCanMoment(&mpmoEsc_U, ibCan);
  }
}
