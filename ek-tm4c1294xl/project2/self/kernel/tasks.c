/*------------------------------------------------------------------------------
tasks.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "utils/lwiplib_patched.h"
#include "../kernel/log.h"
#include "settings.h"
#include "../tcp/telnet.h"
#include "../tcp/telnet_listen.h"
#include "../tcp/telnet_open.h"
#include "../uart/serial.h"
#include "../uart/serial_receive.h"
#include "entities.h"
#include "version.h"
#include "tasks.h"



static void StartServerConnection(uchar u)
{
  ASSERT(u < UART_COUNT);

  CONSOLE("%u: listen as server on port %u\n", u, mwPort[u]);
  TelnetListen(mwPort[u], u);
}


static void StartClientConnection(uchar u)
{
  ASSERT(u < UART_COUNT);

  ulong dw = mdwDestinationIP[u];
  CONSOLE("%u: connect as client to %u.%u.%u.%u port %u\n",
    u,
    (dw >> 24), (dw >> 16) & 0xFF, (dw >> 8) & 0xFF, dw & 0xFF,
    mwDestinationPort[u]);

  TelnetOpen(mdwDestinationIP[u], mwDestinationPort[u], u);
}



void InitConnection(uchar u)
{
  ASSERT(u < UART_COUNT);

  if (mbRoutingMode[u] == ROUTING_MODE_SERVER)
  {
    StartServerConnection(u);
  }
  else if (mbRoutingMode[u] == ROUTING_MODE_CLIENT)
  {
    if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
    {
      CONSOLE("%u: connect as client immediately\n",u);
      StartClientConnection(u);
    }
  }
  else
  {
    CONSOLE("%u: ERROR routing mode %u", u, mbRoutingMode[u]);
  }
}


void InitConnections(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    InitConnection(u);
  }
}


void TaskConnections(void)
{
  uchar u;
  for(u = 0; u < UART_COUNT; u++)
  {
    if (mbRoutingMode[u] == ROUTING_MODE_CLIENT)
    {
      tTelnetSession *pState = getTelnetSession(u);

      if (mbConnectionMode[u] == CONNECTION_MODE_IMMEDIATELY)
      {
        if (pState->eTCPState == STATE_TCP_IDLE)
        {
          CONSOLE("%u: connect as client immediately after reset\n",u);
          StartClientConnection(u);
        }
      }
      else if (mbConnectionMode[u] == CONNECTION_MODE_ON_DATA)
      {
        if ((pState->eTCPState == STATE_TCP_IDLE) && SerialReceiveAvailable(pState->ulSerialPort))
        {
          CONSOLE("%u: connect as client on data\n",u);
          StartClientConnection(u);
        }
      }
      else
      {
        CONSOLE("%u: ERROR connection mode %u", u, mbConnectionMode[u]);
      }
    }
  }
}



void TaskLwIpDebug(void)
{
static uint wTimeout;

  if ((fLwIpDebugFlag) && (++wTimeout > wLwIpDebugTimeout*10))
  {
    wTimeout = 0;
    stats_display();

    ConsoleVersion();
  }
}
