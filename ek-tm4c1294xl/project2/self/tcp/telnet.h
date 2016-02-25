/*------------------------------------------------------------------------------
TELNET,H


------------------------------------------------------------------------------*/

#include "telnet_include.h"



tTelnetSession *getTelnetSession(uchar ibUart);

void TelnetFreePbufs(tTelnetSession *pState);

extern void TelnetInit(void);
err_t TelnetConnected(void *arg, struct tcp_pcb *pcb, err_t err);

extern err_t TelnetCloseClient(uint32_t ulSerialPort);
extern err_t TelnetCloseServer(uint32_t ulSerialPort);
extern void TelnetClose(uint32_t ulSerialPort);

extern void TelnetHandler(void);


#if false
extern uint16_t TelnetGetLocalPort(uint32_t ulSerialPort);
extern uint16_t TelnetGetRemotePort(uint32_t ulSerialPort);
#endif
