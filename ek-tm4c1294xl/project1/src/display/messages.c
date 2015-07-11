/*------------------------------------------------------------------------------
MESSAGES.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "display.h"



//                                         0123456789ABCDEF
char const              szClear[]       = "                ",
                        szWarning[]     = "��������: ������",
                        szError[]       = "    ������ !    ",
                        szOK[]          = "       ��       ",
                        szStop[]        = "     ���� !     ",
                        szWaiting[]     = "   ��������...  ",
                        szCanal[]       = "   ����� ?__    ",
                        szGroup[]       = "  ������ ?__    ",
                        szParam[]       = "�������� ?___   ",
                        szNumber[]      = "   ����� ?__    ",
                        szPort[]        = "    ���� ?__    ",
                        szAddress[]     = "   ����� ?___   ",
                        szHour[]        = " ������� ?__    ",
                        szDay[]         = "   ����� ?__    ",
                        szMonth[]       = "   ����� ?__    ",
                        szQuarter[]     = " ������� ?__    ",
                        szWork[]        = "������          ",
                        szSetting[]     = "���������       ",
                        szRun[]         = "������          ",
                        szAlarm[]       = "������: ������  ",
                        szZones[]       = " �������� ����  ",
                        szTariffs[]     = "�������� ����   ",
                        szEnergy[]      = "    �������     ",
                        szPower[]       = "    ��������    ",
                        szCounters[]    = "��������        ",
                        szImpulseA[]    = "��������        ",
                        szImpulseB[]    = "    ��������    ",
                        szOnCanals[]    = "   �� �������   ",
                        szOnGroups[]    = "   �� �������   ",
                        szForPower[]    = "  ��� ��������  ",
                        szForEnergy[]   = "  ��� ~������   ",
                        szForDigital[]  = "   (��������)   ",
                        szOn12Months[]  = " �� 12 �������  ",
                        szOnMinute[]    = "  �� 3-���      ",
                        szOnHour[]      = " �� 30-���      ",
                        szOnDay[]       = "  �� �����      ",
                        szOnMonth[]     = "  �� �����      ",
                        szMiddle[]      = "    �������     ",
                        szCurrMnt[]     = " 3 ���. ������� ",
                        szCurrHou[]     = "30 ���. ������� ",
                        szPrevHou[]     = "30 ���. ������� ",
                        szDayCurr[]     = "�� ������� �����",
                        szDayPrev[]     = "�� ������� �����",
                        szMonCurr[]     = "�� ������� �����",
                        szMonPrev[]     = "�� ������� �����",
                        szAbsolute[]    = "      �����     ",
                        szMaximum[]     = "  ������������  ",
                        szFull[]        = " �� ���� �����  ",
                        szMorning[]     = " � �������� ��� ",
                        szEvening[]     = " � �������� ��� ",
                        szTops[]        = "� ������� ����� ",
                        szMid[]         = "   � �������    ",
                        szBottom[]      = "� ������ ������ ",
                        szBadFlash[]    = "  ��~�-������ ! ",
                        szBadCODE[]     = "�������� CODE ! ",
                        szBadNVRAM[]    = " ������ NVRAM ! ",
                        szBadRTC1[]     = "������� � RTC ! ",
                        szBadRTC2[]     = "��������� RTC ! ",
                        szIsResetWDT[]  = "  ����� �� WDT  ",
                        szEmpty[]       = "      ���       ",
                        szYes[]         = "�� ",
                        szNo[]          = "���";



void    Work(void)     {  ShowHi(szWork);     }
void    Setting(void)  {  ShowHi(szSetting);  }
void    Clear(void)    {  ShowLo(szClear);    }
void    Error(void)    {  ShowLo(szError);    }
void    OK(void)       {  ShowLo(szOK);       }
void    Stop(void)     {  ShowLo(szStop);     }
void    Waiting(void)  {  ShowLo(szWaiting);  }
void    Canal(void)    {  ShowLo(szCanal);    }
void    Group(void)    {  ShowLo(szGroup);    }
void    Param(void)    {  ShowLo(szParam);    }
void    Number(void)   {  ShowLo(szNumber);   }
void    Port(void)     {  ShowLo(szPort);     }
void    Address(void)  {  ShowLo(szAddress);  }
void    Hour(void )    {  ShowLo(szHour);     }
void    Day(void)      {  ShowLo(szDay);      }
void    Month(void)    {  ShowLo(szMonth);    }
void    Quarter(void)  {  ShowLo(szQuarter);  }
