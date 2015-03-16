/*------------------------------------------------------------------------------
MODEMS.C


------------------------------------------------------------------------------*/

#include    "../main.h"
#include    "../display/display.h"
#include    "../time/delay.h"
#include    "../serial/ports_stack.h"
#include    "../serial/ports_common.h"
#include    "../serial/ports_devices.h"
#include    "../serial/ports_modems.h"



//                                         0123456789ABCDEF
static char const       szBaud[]        = "   ����� ...    ",
                        szCommon[]      = " ��������� 1 ...",
                        szCustom[]      = " ��������� 2 ...",
                        szRing[]        = "      ring      ",
                        szNoCarrier[]   = "   no carrier   ",
                        szModemError[]  = "      error     ",
                        szNoDialtone[]  = "  no dialtone   ",
                        szBusy[]        = "    ������ !    ",
                        szNoAnswer[]    = "    no answer   ",
                        szEscape[]      = "     +++ ...    ",
                        szHookOff[]     = " ���������� ... ",
                        szDTROff[]      = "     ����� !    ",
                        szBreakConnect[]= " �������������� ",
                        szBlockingAll[] = " ��� ���������� ",
                        szConnect[]     = "   ����������   ",
                        szDisconnect[]  = "  ������������  ",
                        szNoConnect[]   = " ��� ���������� ",
                        szNoDisconnect[]= "��� ������������";



uchar   GetModemAnswer(void)
{
uchar   i,j;
       
  if ((IndexInBuff() >= 2) && (IndexInBuff() <= 4))
  {
    wBuffD = 0;
    for (i=0; i<IndexInBuff()-1; i++)
    {
      j = InBuff(i);
      if ((j >= '0') && (j <= '9'))
        wBuffD = wBuffD*10 + ToChar(j);
      else
      {
        wBuffD = 0xFF;
        break;
      }
    }
  }
  else wBuffD = 0xFE;

  if (wBuffD < 0x100)
    return(wBuffD);
  else
    return(0xFD);  
}



void    QueryModemBaud(bool fShow)
{
  if (fShow == 1) ShowLo(szBaud); 

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 2+2, 1);
}


void    QueryModemCommon(bool fShow)
{
  if (fShow == 1) ShowLo(szCommon); 

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('E');                        // E0 - ��������� ��� ���������
  PushChar('0');

  PushChar('V');                        // V0 - ����� ��������� � �������� �������
  PushChar('0');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 6+2, 1);
}


void    QueryModemCustom(void)
{
  ShowLo(szCustom); //DelayInf();

  InitPush(0);

  PushChar('A');
  PushChar('T');

  PushChar('Q');                        // Q0 - ���������� ������ ��� ����������� �������
  PushChar('0');

  PushChar('X');
  PushChar('4');

  PushChar('&');                        // &D3 - ������ ����� � ���������� ������ ��������� ������� DTR
  PushChar('D');
  PushChar('2');

  PushChar(0x5C);                       // \Q0 - ���������� ������� ���������
  PushChar('Q');
  PushChar('0');

  PushChar('S');                        // S0=2 - ������ ���������� ������ �� ������ �����
  PushChar('0');
  PushChar('=');
  PushChar('2');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 16+2, 1);
}



void    QueryModemConnect(void)
{
uchar   i;

  NoShowTime(0);

  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('D');
  PushChar('P');

  phT = mpphPhones[diCurr.ibPhone - 1];

  Clear();
  strcpy(szLo, phT.szNumber);

  for (i=0; i<bPHONENUMBER; i++)
  {
    if ( phT.szNumber[i] == 0 ) break;
    PushChar( phT.szNumber[i] );
  }

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 4+i+2, 1);
}



bool    ShowModemConnect(void)
{
  fAlt = 0;

  switch ( GetModemAnswer() ) 
  {
    case 2:  ShowLo(szRing);        break;
    case 3:  ShowLo(szNoCarrier);   break;
    case 4:  ShowLo(szModemError);  break;
    case 6:  ShowLo(szNoDialtone);  break;
    case 7:  ShowLo(szBusy);        break;
    case 8:  ShowLo(szNoAnswer);    break;

    case 0xFF: 
    case 0xFE: 
    case 0xFD: sprintf(szLo,"   ������: %bu   ", GetModemAnswer()); 
                                    break;

    default:   sprintf(szLo," ����������: %bu ", GetModemAnswer());
               fAlt = 1;            break;
  }

  DelayInf();
  return(fAlt);
}


void    QueryModemEscape(void)
{
  ShowLo(szEscape); //DelayInf();

  Delay(1500);

  InitPush(0);

  PushChar('+');
  PushChar('+');
  PushChar('+');

  Query(SERIAL_MODEM, 3, 1);

  Delay(1500);
}


void    QueryModemHookOff(void)
{
  ShowLo(szHookOff); //DelayInf();

  InitPush(0);

  PushChar('A');
  PushChar('T');
  PushChar('H');
  PushChar('0');

  PushChar('\r');
  PushChar('\n');

  Query(SERIAL_MODEM, 4+2, 1);
}



void    ModemDTROff(void)
{
  ShowLo(szDTROff); //DelayInf();

  DTROff();
}



void    Local(void)
{
  if (mpSerial[ibPort] == SER_LOCAL)
  {
    if (mpboLocalDisable[ibPort] == boTrue)
      mpSerial[ibPort] = SER_BEGIN;
    else
    {
      InitPush(0);

      PushChar('O');
      PushChar('K');
      PushChar('\r');
      PushChar('\n');

      Query(SERIAL_LOCAL, 2+2, 1); 
    }
  }
}



// ���������� � ������� (������� ��������� diCurr)
bool    Connect(void)
{
uchar   i;

  fConnect = 0;

  ibPort = diCurr.ibPort;

  if (StreamPort(diCurr.ibPort) == 0) return(0);
  if (diCurr.ibPhone == 0) return(1); 

  if (mpboEnblCan[ibDig] == boFalse) { ShowLo(szBlockingAll); DelayInf(); return(1); }

  ShowPort(diCurr.ibPort);
  ShowLo(szConnect); DelayInf();

  for (i=0; i<bMINORREPEATS; i++)
  {
//    QueResult(bRES_MODEMBAUD, i);

    DelayOff();
    QueryModemBaud(1);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) ;
  else
    { ShowLo(szBaudOK); DelayInf(); mpcwBaud[diCurr.ibPort]++; }


  for (i=0; i<bMINORREPEATS; i++)
  {
//    QueResult(bRES_MODEMCOMMON, i);

    DelayOff();
    QueryModemCommon(1);

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return(0);

    if (i > 0)                          // ������� �� ��������� hook on
    {
      DelayOff();
      QueryModemEscape();

      if (ModInputOK(3) == 1) ;
      if (fKey == 1) return(0);

      DelayOff();
      QueryModemHookOff();

      if (ModInputOK(1) == 1) ;
      if (fKey == 1) return(0);
    }
  }

  if (i == bMINORREPEATS) return(0);
  ShowLo(szCommonOK); DelayInf(); mpcwCommon[diCurr.ibPort]++;


  if (boCustomModem == boTrue)
  {
    for (i=0; i<bMINORREPEATS; i++)
    {
//      QueResult(bRES_MODEMCUSTOM, i);

      DelayOff();
      QueryModemCustom();

      if (ModInputOK(1) == 1) break;
      if (fKey == 1) return(0);
    }

    if (i == bMINORREPEATS) return(0);
    ShowLo(szCustomOK); DelayInf(); mpcwCustom[diCurr.ibPort]++;
  }


  for (i=0; i<bMINORREPEATS; i++)
  {
//    QueResult(bRES_MODEMCONNECT, i);

    DelayOff();

    fConnect = 1;
    QueryModemConnect();

    if ((ModInput(bConnect,1) == SER_POSTANSWER_MODEM) && (ShowModemConnect() == 1)) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) return(0);


  cbWaitOnline = 0;

  mpcwConnect[diCurr.ibPort]++;
  return(1);
}


// ������� ��������� diCurr
bool    SafeConnect(void)
{
#ifdef  FLOW
  CloseFlow();
#endif

  SaveDisplay();
  fAlt = Connect();
  LoadDisplay();

//  QueResult(bRES_CONNECT, (uchar)fAlt);
//  ResetAllSerial();

  return(fAlt);
}



// ������������ � ������� (������� ��������� diCurr)
bool    Disconnect(void)
{
uchar   i;
bool    fResult;

  fResult = 0;

  ibPort = diCurr.ibPort;

  ShowPort(diCurr.ibPort);
  ShowLo(szDisconnect); DelayInf();

  for (i=0; i<bMINORREPEATS; i++)
  {
    // ������� �� ��������� hook on
//    QueResult(bRES_MODEMESCAPE, i);

    DelayOff();
    QueryModemEscape();

    if (ModInputOK(3) == 1) break;
    if (fKey == 1) return(0);

    // ������� �� ��������� hook off
//    QueResult(bRES_MODEMHOOKOFF, i);

    DelayOff();
    QueryModemHookOff();

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) ;
  else
    { ShowLo(szEscapeOK); DelayInf(); mpcwEscape[diCurr.ibPort]++; }


  for (i=0; i<bMINORREPEATS; i++)
  {
//    QueResult(bRES_MODEMHOOKOFF, i);

    DelayOff();
    QueryModemHookOff();

    if (ModInputOK(1) == 1) break;
    if (fKey == 1) return(0);
  }

  if (i == bMINORREPEATS) ;
  else
  { 
    fResult = 1;
    ShowLo(szHookOffOK); DelayInf(); mpcwHookOff[diCurr.ibPort]++;
  }
 

  ModemDTROff();
  mpcwDTROff[diCurr.ibPort]++;

  fConnect = 0;

  return(fResult);
}


// ������� ��������� diCurr
bool    SafeDisconnect(void)
{
#ifdef  FLOW
  CloseFlow();
#endif

  SaveDisplay();
  fAlt = Disconnect();
  LoadDisplay();

//  QueResult(bRES_DISCONNECT, (uchar)fAlt);
//  ResetAllSerial();

  return(fAlt);
}



void    InitConnect(void)
{
  diLast.ibPort  = 0xFF;
  diLast.ibPhone = 0xFF;

//  ResetAllSerial();
}


void    InitConnectKey(void)
{
  InitConnect(); //fQuery = 0;
}

/*
void    InitConnectQue(void)
{
  InitConnect(); fQuery = 1;
  ibPortQue = ibPort;
}


void    DoneConnectQue(void)
{
  ibPort = ibPortQue;
  DelayMsg();
}
*/


// ������� ��������� diCurr
bool    BreakConnect(void)
{
  fAlt = ((diLast.ibPort != diCurr.ibPort) || (diLast.ibPhone != diCurr.ibPhone)); 

  if (fAlt == 1)
  {
    SaveDisplay();

    ShowPort(diCurr.ibPort);
    ShowLo(szBreakConnect); DelayInf();

    LoadDisplay();
  }

//  QueResult(bRES_BREAKCONNECT, (uchar)fAlt);
  return(fAlt);
}


// ������� ������������� ������������ � ������� (������� ��������� diCurr)
bool    NeedDisconnect(void)
{
  if (diCurr.ibPhone == 0)
    return(diCurr.bDevice != 0);
  else
    return(1);
}



// ������� ��������� diCurr
bool    LoadConnect(uchar  ibCanal)
{
  if (fConnect == 1)
  {
    if ((diLast.ibPort == 0xFF) || (diLast.ibPhone == 0xFF))
    { 
      KeyBreakConnect();
      return(0);
    }
    else if (BreakConnect() == 1)
    { 
      if (NeedDisconnect() == 1)
      {
        diNext = diCurr; diCurr = diLast;
        fAlt = SafeDisconnect();
        diCurr = diNext;

        if (fAlt == 0) { ShowLo(szNoDisconnect); InitConnect(); return(0); }
      }

      ibDig = ibCanal;
      if (SafeConnect() == 0) { ShowLo(szNoConnect);  InitConnect(); return(0); }
    }
    else ibDig = ibCanal;
  }
  else 
  {
    ibDig = ibCanal;
    if (SafeConnect() == 0) { ShowLo(szNoConnect);  InitConnect(); return(0); }
  }

  return(1);
}


// ������� ��������� diCurr
void    SaveConnect(void)
{
  diLast = diCurr;
}

