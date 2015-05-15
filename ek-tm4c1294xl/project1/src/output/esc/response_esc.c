/*------------------------------------------------------------------------------
RESPONSE_ESC.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_factors.h"
#include "../../memory/mem_ports.h"
#include "../../memory/mem_esc.h"
#include "../../console.h"
#include "../../serial/ports.h"
#include "../../serial/flow.h"
#include "../../hardware/memory.h"
#include "../../digitals/wait_query.h"
#include "../../keyboard/time/key_timedate.h"
#include "../../tariffs/tariffs.h"
#include "../../tariffs/zones.h"
#include "../../tariffs/relaxs.h"
#include "../../time/rtc.h"
#include "../../flash/at45.h"
#include "../../access.h"
#include "../../groups.h"
#include "esc.h"



static void PushFloatBCD(float  fl)
{
  ulong dw = (ulong)fl;

  PushChar( ToBCD(dw % 100)           );
  PushChar( ToBCD((dw % 10000) / 100) );
  PushChar( ToBCD(dw / 10000)         );
}


static void PushZone(void)
{
uchar   i;

  for (i=0; i<GetZoneAltSize(); i++)
  {
    GetZoneAltBreak(i);

    PushChar( ToBCD(brAlt.bMinute) );
    PushChar( ToBCD(brAlt.bHour) | ((brAlt.ibTariff << 6) & 0xC0) );
  }

  for (i=GetZoneAltSize(); i<6; i++)
  {
    PushChar(0xAA);
    PushChar(0xAA);
  }
}



void    Esc(uint  wSize)
{
  InitPush(0);
  uchar bT = 0;

  uint i;
  for (i=0; i<wSize; i++)
  {
    bT += SkipChar();
  }

  PushChar(bT);
  Answer(wSize+1, SER_OUTPUT_SLAVE);
}


void    EscError(uchar  bCode)
{
  InitPush(0);

  PushChar(0x1B);
  PushChar(bQuery);
  PushChar(bCode);

  Esc(3);
}



static void ShowCtrlZ()
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"���� %u: Ctrl Z",ibPort+1);
    Clear();
    HideCurrentTime(0);
  }
}


static void ShowEsc(void)
{
  if (wProgram == bTEST_RESPONSE)
  {
    sprintf(szHi,"���� %u: Esc %c",ibPort+1,bQuery);
    HideCurrentTime(0);
  }
}


void    Esc0(void)
{
  ibActiveEsc = 0xFF;
  mpibActiveEsc[ibPort] = ibActiveEsc;
}


void    EscNumber(void)
{
  uchar i;
  for (i=0; i<bMachinesEsc; i++)
  {
    if ((bQuery - 0x31) == (bLogical + i - 1))
      break;
  }

  if (i != bMachinesEsc)
  {
    ibActiveEsc = (bQuery - 0x31) - (bLogical - 1);
    mpibActiveEsc[ibPort] = ibActiveEsc;

    InitPush(0);
    PushChar(bQuery);
    Esc(1);

    ShowEsc();
  }
  else
  {
    ibActiveEsc = 0xFF;
    mpibActiveEsc[ibPort] = ibActiveEsc;
  }
}


void    Esc_A(void)
{
  Beep();
  ShowEsc();
}


void    Esc_T(void)
{
  InitPush(0);
  PushChar(ToBCD(tiCurr.bSecond));
  PushChar(ToBCD(tiCurr.bMinute));
  PushChar(ToBCD(tiCurr.bHour  ));
  PushChar(ToBCD(tiCurr.bDay   ));
  PushChar(ToBCD(tiCurr.bMonth ));
  PushChar(ToBCD(tiCurr.bYear  ));
  Esc(6);
}


void    Esc_R(void)
{
  InitPush(0);
  Push("C��+2 V.06 10.10.08!",20);
  PushChar(0x31+ibActiveEsc);
  Esc(21);
}


void    Esc_w(void)
{
uchar   i, j;

  InitPush(0);

  // ������ ���� ���������
  i = bOldTrfMode;

  if (GetMode(*GetCurrTimeDate()) != 0)
    i |= 0x04;

  if (enGlobal == GLB_REPROGRAM)
    i |= 0x20;

  PushChar(i);

  // ������ ���� ���������
  if (bOldTrfMode == 4)
    PushChar(4);
  else
    PushChar(0);

  // ����/����� ������� �������
  PushChar( ToBCD(tiStart.bSecond) );
  PushChar( ToBCD(tiStart.bMinute) );
  PushChar( ToBCD(tiStart.bHour  ) );
  PushChar( ToBCD(tiStart.bDay   ) );
  PushChar( ToBCD(tiStart.bMonth ) );
  PushChar( ToBCD(tiStart.bYear  ) );

  // �������� ���� �� ���������
  memset(&zoAlt, 0, sizeof(zoAlt));
  PushZone();
  PushZone();
  PushZone();
  PushZone();

  // �������� ���� �������� ������
  zoAlt = *PGetZonePowMonthMode(tiCurr.bMonth - 1, 0);
  PushZone();

  // ������ ����������
  for (i=0; i<GetRelaxSize(); i++)
  {
    if (i >= 20) break;

    GetRelaxDate(i);
    PushChar( ToBCD(tiRelax.bDay)   );
    PushChar( ToBCD(tiRelax.bMonth) );
  }

  while (i++ < 20)
  {
    PushChar(0x55);
    PushChar(0x55);
  }

  // ��c��� �����: ��� ������
  for (i=bFRAMES*ibActiveEsc; i<bFRAMES*(1+ibActiveEsc); i++)
  {
    uint w = 0;

    for (j=0; j<GetGroupsSize(i); j++)
    {
      if (j > 16) break;
      w |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
    }

    PushChar(w % 0x100);
    PushChar(w / 0x100);
  }

  // ��c��� �����: ������ � ������������� ������
  for (i=bFRAMES*ibActiveEsc; i<bFRAMES*(1+ibActiveEsc); i++)
  {
    uint w = 0;

    for (j=0; j<GetGroupsSize(i); j++)
    {
      if (j > 16) break;
      if (GetGroupsNodeSign(i,j) == 1)
        w |= (uint)(0x01 << GetGroupsNodeCanal(i,j));
    }

    PushChar(w % 0x100);
    PushChar(w / 0x100);
  }

  // ������������ �������������
  for (i=0; i<16; i++)
  {
    PushFloatBCD(mpreTransEng[i+16*ibActiveEsc]);
  }

  // ������������ ��������������
  for (i=0; i<16; i++)
  {
    PushFloatBCD(mprePulseHou[i+16*ibActiveEsc]);
  }

  // ������
  for (i=0; i<18; i++)  PushChar(0);

  // ��������� �����
  PushChar( ToBCD(wPrivate % 100)         );
  PushChar( ToBCD((wPrivate % 10000)/100) );
  PushChar( ToBCD(wPrivate / 10000)       );

  // ��������� �����
  PushChar( ToBCD(wPrivate % 100)         );
  PushChar( ToBCD((wPrivate % 10000)/100) );
  PushChar( ToBCD(wPrivate / 10000)       );

  // ������������ ������
  for (i=0; i<16; i++)
  {
    PushFloatBCD(mpreLosse[i+16*ibActiveEsc] * 1000000);
  }

  Esc(300);
}


void    Esc_W(void)
{
uchar   i;

  InitPush(0);

  if (GetFlashStatus() == 0)
    i = 0x07;                            // �����
  else
    i = 0x01;                            // ������ ����-������

  if (cbPowerOn == 0)
    PushChar(i | 0x08);
  else
  if (cbPowerOn == 1)
    PushChar(i | 0x10);
  else
    PushChar(i);

  PushTime(tiPowerOff);                  // ����� ���������� ���������� �������
  PushTime(tiPowerOn);                   // ����� ���������� ��������� �������
  PushChar(cbPowerOn);                   // ���������� ���������� �������

  PushChar(0);                           // ����� ���������� �� ���������� ����� (����, �����, �����)
  PushChar(0);
  PushChar(0);

  PushChar(0);                           // ����� ���������� �� ������� ����� (����, �����, �����)
  PushChar(0);
  PushChar(0);

  Esc(20);
}


void    EscTariffs(void)
{
  InitPush(0);

  uchar m;
  for (m=0; m<12; m++)
  {
    zoAlt = *PGetZonePowMonthMode(m, 0);
    PushZone();
  }

  for (m=0; m<12; m++)
  {
    zoAlt = *PGetZoneEngMonthMode(m, 0);
    PushZone();
  }

  PushChar(0);
  PushChar(0);
  PushChar(0);
  PushChar(0);

  if (fPublicTariffs == FALSE)
    PushChar(1);
  else
    PushChar(0);

  if (fPublicTariffsPrevMon == FALSE)
    PushChar(1);
  else
    PushChar(0);

  Esc(300);
}


void    EscDisplay(void)
{
  InitPush(0);

  PushChar(0x0D); PushChar(0x0A); Push(&szHi,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A); Push(&szLo,bDISPLAY);
  PushChar(0x0D); PushChar(0x0A);

  Esc(2*bDISPLAY+3*2);
}


void    EscKey(void)
{
  uchar i = bQuery-'�';
  if (ValidKey(i) == true)
  {
    bKey = mpbKeys[i];
    fKey = true;

    EscDisplay();
  }
  else EscError(bESC_BADDATA);
}


void    EscTransit(void)
{
  if (cbWaitQuery != 0)
  {
    InitPush(0);
    Push("Transit error: busy !",21);
    Esc(21);
  }
  else if (ibPort == 0)
  {
    RunFlow0();

    InitPush(0);
    Push("Transit OK: 1 !",15);
    Esc(15);
  }
  else if (ibPort == 1)
  {
    RunFlow1();

    InitPush(0);
    Push("Transit OK: 1 !",15);
    Esc(15);
  }
}


void    EscId(void)
{
  InitPush(0);
  PushInt(GetRomChecksum());
  PushInt(wPrivate);
  PushChar(bLogical);
  Esc(5);
}



void    RunResponseEsc(void)
{
  if (mpSerial[ibPort] == SER_CTRL_Z)
  {
    mpSerial[ibPort] = SER_BEGIN;

    ShowCtrlZ();
  }
  else if (mpSerial[ibPort] == SER_CHAR)
  {
    mpSerial[ibPort] = SER_BEGIN;

    if (enGlobal == GLB_PROGRAM)
      if (!((InBuff(0) >= '�') && (InBuff(0) <= '�')))
        return;

    if (boBlockEsc == (boolean)0x55)
      return;

    bQuery = InBuff(0);

    ibActiveEsc = mpibActiveEsc[ibPort];

    switch (bQuery)
    {
      case 0x30: Esc0(); return;

      case 0x31:
      case 0x32:
      case 0x33:
      case 0x34:
      case 0x35:
      case 0x36:
      case 0x37:
      case 0x38:
      case 0x39:
      case 0x3A:
      case 0x3B:
      case 0x3C:
      case 0x3D:
      case 0x3E:
      case 0x3F:
      case 0x40: EscNumber(); return;

      case 'A': Esc_A(); return;
    }

    if (ibActiveEsc >= bMachinesEsc) return;

    ShowEsc();

    if (boBlockEsc == TRUE)
    {
      if (bQuery != 'R') 
      {
        InitPush(0);
        Push("Disabled !",10);
        Esc(10);
        return;
      } 
    }

    switch (bQuery)
    {
      case 'T': Esc_T(); break;
      case 'R': Esc_R(); break;
      case 'w': Esc_w(); break;
      case 'W': Esc_W(); break;

      case '*': EscTariffs(); break;

      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�':
      case '�': EscKey(); break;

      case '�': EscDisplay(); break;

      case 0x1F: EscTransit(); break;

      case '�': EscId(); break;
    }
  }
}



void    RunResponseEsc_All(void)
{
  ibPort = 0;
  if (IsFlow0() == 0) RunResponseEsc();

  ibPort = 1;
  if (IsFlow1() == 0) RunResponseEsc();

  ibPort = 2;
  RunResponseEsc();

  ibPort = 3;
  RunResponseEsc();
}
