/*------------------------------------------------------------------------------
udp_push.h


------------------------------------------------------------------------------*/

#include "lwip/udp.h"



void InitPush(void);
void PushChar(uchar b);
void PushString(const char *sz);
void PushArrayString(uchar *pb, uchar bSize);
void PushBuff(buff bf);
uchar PushCharDec(uchar b);
uchar PushIntDec(uint w);
uchar PushIntHex(uint w);
void PushIP(ulong dw);
void PushSuffix(uint w);

err_t UDPPush(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar broadcast);
