/*------------------------------------------------------------------------------
SLAVE_MODEM!C

 '���������������� ���+2, ������ 177'
-----------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../serial/ports_devices.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "slave_modem.h"



cache const             chSlaveModem = {SLAVE_MODEM, &fSlaveModem, sizeof(bool)};



void    InitSlaveModem(void)
{
  LoadCacheBool(&chSlaveModem, false);

  ResetSendAT_All();
}


void    ResetSlaveModem(void)
{
	fSlaveModem = false;
  SaveCache(&chSlaveModem);
}



static void SendAT1(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('\r');
  PushChar('\n');

  Answer(4,SER_OUTPUT_SLAVE);
}


static void SendAT2(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('&'); // &D0 - ������������ ������ DTR
  PushChar('D');
  PushChar('0');

  PushChar('&'); // &K0 - ���������� ������� ���������
  PushChar('K');
  PushChar('0');

  PushChar('S'); // S0=2 - ������ ���������� ������ �� ������ �����
  PushChar('0');
  PushChar('=');
  PushChar('2');

  PushChar('\r');
  PushChar('\n');

  Answer(8,SER_OUTPUT_SLAVE);
}


static void SendAT(void)
{
  SendAT1();

  DelayMsg();

  SendAT2();
}



static void RunSlaveModem(void)
{
  if ((fSlaveModem == true) && (mpstSendAT[ibPort] == AT_ANSWER))
  {
    mpstSendAT[ibPort] = AT_BEGIN;

    SaveDisplay();

    ShowHi(szClear); sprintf(szHi,"���� %u: AT",ibPort+1);

    Clear();
    DelayMsg();

    LoadDisplay();

    SendAT();
    fSendAT = 0;
  }
}


void    RunSlaveModem_All(void)
{
  ibPort = 0;
  RunSlaveModem();

  ibPort = 1;
  RunSlaveModem();

  ibPort = 2;
  RunSlaveModem();

  ibPort = 3;
  RunSlaveModem();
}



void    ResetSendAT(uchar  ibPrt)
{
  mpcbSendAT[ibPrt] = bSEND_AT_TIMEOUT;
  mpstSendAT[ibPrt] = AT_TIMEOUT;
}


void    ResetSendAT_All(void)
{
  uchar p;
  for (p=0; p<bPORTS; p++)
  {
    ResetSendAT(p);
  }
}



void    SlaveModem_1Hz(void)
{
  uchar p;
  for (p=0; p<bPORTS; p++)
  {
    if (mpstSendAT[p] == AT_TIMEOUT)
    {
      (mpcbSendAT[p] == 0) ? (mpstSendAT[p] = AT_ANSWER) : (mpcbSendAT[p]--);
    }
  }
}



void    OutSlaveModem(void)
{
  InitPushCRC();

  PushBool(fSlaveModem);
  PushChar(fSendAT);
  Push(&mpcbSendAT, sizeof(mpcbSendAT));
  Push(&mpstSendAT, sizeof(mpstSendAT));

  Output(1+1+4+4);
}



/*
��� ���������� ������� ������� ������������ ��������� 198. ��� ���������� ����� ����� �������� � 10 ������ ����� ��������� ���� ������� ����� ���������� ������� at \r \n ��� ��������� ������, ������������ � ������ ��������������� ����������� �������� (auto baud) � ����� 1 ������� ����� �� ������� ATS0=2 \r \n ��� ��������� ����-������� ������ ��� ������ ������ �� ������ �����. � ��������� �������� ���������:
1. ��������� ���������
2. ����������� ������ �� ������, ���������� � ������� �������
3. ��������� �������� ������ �� ������, ���������� � ������� �������
4. ��������� ������ ����� ���������� 198
5. ������� �� ��������� �����
*/
