/*------------------------------------------------------------------------------
SLAVE_MODEM.C


-----------------------------------------------------------------------------*/

#include "../main.h"
#include "../memory/mem_ports.h"
#include "../serial/ports.h"
#include "../display/display.h"
#include "../time/delay.h"
#include "slave_modem.h"



cache const             chSlaveModem = {SLAVE_MODEM, &fSlaveModem, sizeof(bool)};



void    InitSlaveModem(void)
{
  LoadCacheBool(&chSlaveModem, false);
}


void    ResetSlaveModem(void)
{
	fSlaveModem = false;
  SaveCache(&chSlaveModem);
}



static void SendAT(void)
{
  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('\r');
  PushChar('\n');

  Answer(4,SER_OUTPUT_SLAVE);


  DelayMsg();


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


static void SlaveModem(void)
{
  if ((fSlaveModem == true) && (mpanSendAT[ibPort] == ANS_ANSWER))
  {
    mpanSendAT[ibPort] = ANS_BEGIN;

    SaveDisplay();

    ShowHi(szClear); sprintf(szHi,"���� %u: AT",ibPort+1);

    Clear();
    DelayMsg();

    LoadDisplay();

    SendAT();
    fSendAT = 0;
  }
}


void    SlaveModem_All(void)
{
  ibPort = 0;
  SlaveModem();

  ibPort = 1;
  SlaveModem();

  ibPort = 2;
  SlaveModem();

  ibPort = 3;
  SlaveModem();
}

