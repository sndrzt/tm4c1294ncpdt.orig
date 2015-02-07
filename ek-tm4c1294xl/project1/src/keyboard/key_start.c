/*------------------------------------------------------------------------------
KEY_START.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_settings.h"
#include        "../memory/mem_program.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display/display.h"
#include        "../tariffs/tariffs.h"
#include        "../access.h"
#include        "../settings.h"
#include        "../groups.h"
#include        "../rtc.h"
#include        "../factors.h"



//                                         0123456789ABCDEF
static message          szStart         = "�����           ",
                        szRestart       = "�������         ",
                        szDebug         = "�������         ",
                        szNoOldTariff   = "��� �������     ",
                        szBadRTC        = "��������� RTC ! ";


void    ShowNoOldTariff(uchar  ibMonth)
{
  ShowHi(szNoOldTariff);
  Clear();

  sprintf(szLo,"��� ������: %-2u ",ibMonth+1);
  DelayMsg();
}


bool    TestOldTariffs(void)
{
uchar  ibMonth;

  for (ibMonth=0; ibMonth<12; ibMonth++)
  {
    // �������� ������� ����������� ��� ���������� ��� ��������
    if (mpcPowMonth[ibMonth] == 0)
    {
    	ShowNoOldTariff(ibMonth);
      NeedPrograms(bSET_PROGRAM10, bSET_PROGRAM17);
      return(0);
    }

    // �������� ������� ���������� ��� �������
    if (mpcEngMonth[ibMonth] == 0)
    {
    	ShowNoOldTariff(ibMonth);
      NeedPrograms(bSET_PROGRAM20, bSET_PROGRAM27);
      return(0);
    }
  }

  return(1);
}



void    key_Start(void)
{
  if (enKeyboard == KBD_ENTER)
  {  
    enKeyboard = KBD_BEGIN; 

    ShowHi(szStart);     
    Clear();


    if (boSetTime == false)
    {
      NeedProgram(bSET_CURRTIME);
      return;
    }
    else if (boSetDate == false)
    {
      NeedProgram(bSET_CURRDATE);
      return;
    }
    else if (boSetGroups == false)
    {
      NeedProgram(bSET_GROUPS);
      return;
    }
    else if (boSetPassword == false)
    {
      NeedProgram(bSET_PASSWORD);
      return;
    }

    if (TestOldTariffs() == 0)
      return;

    PGetCurrTimeDate();
    if (TrueCurrTimeDate() == 0)
    {
      ShowHi(szAlarm);
      ShowLo(szBadRTC); LongBeep(); DelayMsg();
      return;
    }

// TODO key_Start

    // ������������ ������� �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
    MakeAllCurrTariffs();

    // ������������ ������ � ������������
    MakeFactors();

    // ������������� �������� ������������ ������� � �����
    MakeUsedNodes();
    
    // ���������� �����/���� ������� �������
    tiStart = *PGetCurrTimeDate();

    DelayMsg();
    Work(); OK(); 

    LongBeep();

    enGlobal = GLB_WORK;  
    SaveGlobal();

//    AddSysRecord(EVE_START);
  }
  else Beep();
}



// ��������� ������ ����� ��������������������
void    key_Restart(void)
{
  if (enKeyboard == KBD_ENTER)
  {  
    enKeyboard = KBD_BEGIN; 

    ShowHi(szRestart);     
    Clear();    

    if (boSetPassword == false)
    {
      NeedProgram(bSET_PASSWORD);
      return;
    }

// TODO key_Restart

    // ������������ ������� �������� ������� ��� ������� �������� ������� ����� (��� �������� � �������)
    MakeAllCurrTariffs();

    // ������������ ������ � ������������
    MakeFactors();

    // ������������� �������� ������������ ������� � �����
    MakeUsedNodes();

    DelayMsg();
    Work(); OK(); 

    LongBeep();
    enGlobal = GLB_WORK;  

//    AddSysRecord(EVE_RESTART);

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}



// ������������� ��������� �� ���������
void    key_Debug(void)
{
  if (enKeyboard == KBD_ENTER)
  {  
    enKeyboard = KBD_BEGIN; 

    ShowHi(szDebug);     
    Clear();

    boSetTime = true;
    boSetDate = true;

    ClearPassOne();
    boSetPassword = true;

    boSetGroups = true;

// TODO key_Debug
/*
    // ���������� ��������� �� ��������� ��� ���������� zoAlt,zoKey
    ResetZones();

    // ���������� ��������� �� ��������� ��� ���������� bOldMode
    ResetTariffs();

    // ����� ������� ������� �������
    for (ibMode=0; ibMode<bMODES; ibMode++)
    {
      // ��� ������� �������� �������� ������������ ���������� zoKey
      SetZonesEngMonthsMode(0,11);
      SetZonesPowMonthsMode(0,11);
    }

    // ������ ������� ������� �������
    chOldMode = '_';

    SetCharEngMonths(0,11);
    SetCharPowMonths(0,11);
*/
    // ������������� �������� ������������ ������� � �����
    MakeUsedNodes();

    OK();

//    if (boDTREnable == true) DTROff_All();
  }
  else Beep();
}
