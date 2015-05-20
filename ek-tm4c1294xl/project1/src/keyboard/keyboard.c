/*------------------------------------------------------------------------------
KEYBOARD.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_settings.h"
#include "../memory/mem_program.h"
#include "../memory/mem_realtime.h"
#include "../memory/mem_energy_spec.h"
#include "../display/display.h"
#include "../hardware/beep.h"
#include "../realtime/realtime.h"
#include "../time/delay.h"
#include "../serial/print.h"
#include "../serial/modems.h"
#include "../digitals/answer.h"
#include "../include/programs.h"
#include "../impulses/impulses.h"
#include "../digitals/digitals_status.h"
#include "../devices/devices.h"
#include "../digitals/wait_query.h"
#include "../special/special.h"
#include "../settings.h"
#include "../flash/files.h"
#include "../flash/records.h"
#include "keyboard_auto.h"
#include "keyboard_key.h"
#include "time/key_timedate.h"



//                                         0123456789ABCDEF
char const              szProgram[]     = "��������� ?     ",
                        szMaskKey[]     = " ___            ",
                        szNeed[]        = "����������:     ",
                        szBlock[]       = "���������:      ",
                        szNot[]         = "���:            ",
                        szButtonP[]     = "   ������ 'P'   ",
                        szNoNumber[]    = "����� ��������� ";


// ���� ������� ������: '0'..'9', '-', '.', '���������', '����'
uchar const             mpbKeys[14] = { 0x2B, 0x0E, 0x1E, 0x2E, 0x3E, 0x0D, 0x1D, 0x2D, 0x3D, 0x0B, 0x1B, 0x3B, 0x07, 0x17 };

volatile uchar          bKey;
volatile bool           fKey;

key                     enKeyboard;

uint                    wProgram;

time                    tiKey;

uchar                   ibX, ibY, ibZ;



void    InitKeyboard(void)
{
  enKeyboard = KBD_BEGIN;

  bKey = 0;
  fKey = 0;

  cbShowCurrentTime = 0;
}


// ������� ��������� �� ���������� ���������
void    NoProgram(void)
{
  ShowHi(szNot);
  sprintf(szLo,"  ��������� %u  ",wProgram);
  LongBeep();
}


// ������� ��������� � ������������� ���������� ���������
void    BlockProgram(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," ���������� %u  ",bA);
  LongBeep();
}


void    BlockProgram2(uint  wA, bool fBeep)
{
  ShowHi(szBlock);
  sprintf(szLo," ���������� %u  ",wA);
  if (fBeep == 1) LongBeep();
}


// ������� ��������� � ������������� ���������� ���������
void    BlockProgramExt(uchar  bA)
{
  ShowHi(szBlock);
  sprintf(szLo," ���������� %u  ",bA);
  HideCurrTime(1);
}


// ������� ��������� � ������������� ���������� ���������
void    BlockPrograms(uchar  bA, uchar  bB)
{
  ShowHi(szBlock);
  sprintf(szLo," ��������� %u,%u ",bA,bB);
  LongBeep();
}


// ������� ��������� � ������������� ���������
void    NeedProgram(uchar  bA)
{
  ShowHi(szNeed);
  sprintf(szLo,"  ��������� %u  ",bA);
  LongBeep();
}


// ������� ��������� � ������������� ����������
void    NeedPrograms(uchar  bA, uchar  bB)
{
  ShowHi(szNeed);
  sprintf(szLo," ��������� %u,%u ",bA,bB);
  LongBeep(); 
}



// ������� ��������� � ������������� ����� ������ ���������
void    NeedNumber(void)
{
  ShowHi(szNeed);
  ShowLo(szNoNumber);

  LongBeep();
  DelayInf();

  bKey = bKEY_PROGRAM;
  fKey = true;
}



// ������� ������� ��������� ������� �� ����������
void    RunKeyboard(void)
{
uchar   i;

  // ��������� ����������� ���������
  Keyboard_Auto();

  // ���� ������� �� ����������
  if (fKey == false) return;
  fKey = false;

  for (i=0; i<sizeof(mpbKeys); i++)
    if (bKey == mpbKeys[i]) break;
      
  if (i < sizeof(mpbKeys)) bKey = i; else return;


  // ��������� ��������� �� �������
  fOnImpulse = 1;
  fOnSecond = 1;

  // �������� ������� ������ ��������� �� ���������
  cbShowCurrentTime = 0;

  // ��������� ���������� � ������ connect �� ��������� ����� bMAXWAITONLINE
  cbWaitOnline = 0;

  // ������������� ����� �������� ���������
  if ((fConnect == 1) || (GetCurr() != DEV_BEGIN))
  {
//    if (bKey != bKEY_PROGRAM) return;

    if (((wProgram != bGET_READTIMEDATE1) &&
         (wProgram != bGET_READTIMEDATE2) &&
         (wProgram != wGET_READTRANS)     &&
         (wProgram != wGET_READPULSE)     &&
         (wProgram != bTEST_DIRECT)       &&
         (wProgram != bGET_CNTCANYEAR1)   &&
         (wProgram != bGET_CNTCANYEAR10)  &&
//         (wProgram != bGET_CNTCANYEAR2)   &&
//         (wProgram != bGET_CNTCANYEAR20)  &&
         (wProgram != bGET_CNTCURR_10)    &&
         (wProgram != bGET_CNTCURR_110))  || (bKey == bKEY_PROGRAM))
    {
      SetCurr(DEV_BEGIN);
      SetPause(DEV_BEGIN);

      if (IsOpenSpecial()) { CloseSpecial(); Stop(); }
      CloseSpecialBuff();

      AddDigRecord(EVE_SPECIALCLOSE);

      KeyBreakConnect();
      EnableAnswer();
      return;
    }
  }

  // ������������� ����� �������� ���������
  if (fCurrent == 1)
  {
    SetCurr(DEV_BEGIN);
    if (cbWaitQuery == 0) cbWaitQuery = bMAXWAITQUERY;
  }

  // ����� ������� ��������� ���������� ������ ������ '���������'
  if ((enKeyboard == KBD_BEGIN) && (bKey != bKEY_PROGRAM))
  {
    ShowHi(szNeed);
    ShowLo(szButtonP);
    LongBeep();

    return;     
  }

  // ������ ������ '-' ��� '.'
  if ((bKey == bKEY_MINUS) || (bKey == bKEY_POINT))
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS)) 
    {      
      NeedNumber(); DelayInf();
      bKey = bKEY_PROGRAM;
    }
  }

  // ������ ������ '���������'
  if (bKey == bKEY_PROGRAM)
  {
    enKeyboard = KBD_PROGRAM;
    wProgram = 0;

    fSlide = false;

    ShowHi(szProgram);
    ShowLo(szMaskKey);

    if (enGlobal == GLB_WORK)
      szLo[0] = '>';
    else
    if (enGlobal == GLB_PROGRAM)
      szLo[0] = '-';
    else
    if (enGlobal == GLB_REPROGRAM)
      szLo[0] = '=';

    PrintStop();
    return;
  }

  // ������ �������� ������: ���� ������ ���������
  if (bKey < 10)
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS))
    {
      enKeyboard = KBD_DIGITS;
      ShiftLo(1,3);

      return;
    }
  }

  // ������ ������ '����'
  if (bKey == bKEY_ENTER)
  {
    if ((enKeyboard == KBD_PROGRAM) || (enKeyboard == KBD_DIGITS))
    {      
      enKeyboard = KBD_ENTER;

      wProgram = GetIntLo(1,3);
      if (wProgram == 0)
      { 
        NeedNumber();
        return;
      }
      else
      {
        boFirstReset = TRUE;
        //SaveFile(&flFirstReset);
      }
    }
  }

  Keyboard_Key();
}
