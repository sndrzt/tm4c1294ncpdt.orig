/*------------------------------------------------------------------------------
UDP_OUTPUT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/udp.h"
#include "lwip/ip_addr.h"
#include "../settings.h"
#include "mac.h"
#include "udp_output.h"



static uchar            *pbOut;
static uchar            ibOut;
static uint             wCode;



static err_t CheckSize(struct pbuf *p, uchar bSize)
{
  return (p->len < bSize) ? ERR_SIZE : ERR_OK;
}



static uchar PopChar(struct pbuf *p, uchar i)
{
  uchar *pb = p->payload;
  return pb[i];
}


static uchar PopIntLtl(struct pbuf *p, uchar i)
{
  return PopChar(p, i) + PopChar(p, i+1)*0x100;
}


static uchar PopLongLtl(struct pbuf *p, uchar i)
{
  return PopIntLtl(p, i) + PopIntLtl(p, i+2)*0x10000;
}



static err_t PopCode(struct pbuf *p)
{
  uchar *pb = p->payload;

  if (pb[p->len-3] != '|') return ERR_CODE;
  wCode = PopIntLtl(p, p->len-2);

  return ERR_OK;
}


static err_t InitPush(struct pbuf *p, uchar bSize)
{
  p = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (p == NULL) return ERR_MEM;

  pbOut = p->payload;
  ibOut = 0;

  return ERR_OK;
}


static void PushChar(uchar b)
{
  pbOut[ibOut++] = b;
}


static void PushIntLtl(uint w)
{
  PushChar(w % 0x100);
  PushChar(w / 0x100);
}


static void PushLongLtl(ulong dw)
{
  PushIntLtl(dw % 0x10000);
  PushIntLtl(dw / 0x10000);
}


//static void PushCharDec(uchar b)
//{
//  PushChar('0' + b / 100);
//  PushChar('0' + (b % 100) / 10);
//  PushChar('0' + b % 10);
//}


static void PushMAC(uchar *pbMAC)
{
//  PushCharDec(pbMAC[0]); PushChar('.');
//  PushCharDec(pbMAC[1]); PushChar('.');
//  PushCharDec(pbMAC[2]); PushChar('.');
//  PushCharDec(pbMAC[3]); PushChar('.');
//  PushCharDec(pbMAC[4]); PushChar('.');
//  PushCharDec(pbMAC[5]);

  PushChar(pbMAC[0]);
  PushChar(pbMAC[1]);
  PushChar(pbMAC[2]);
  PushChar(pbMAC[3]);
  PushChar(pbMAC[4]);
  PushChar(pbMAC[5]);
}


static void UDPOutput(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  if (addr->addr == IPADDR_BROADCAST)
    udp_sendto(pcb, p, IP_ADDR_BROADCAST, port);
  else
    udp_sendto(pcb, p, addr, port);

  pbuf_free(p);
}


static err_t UDPOutput_Error(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, uchar bError)
{
  err_t err = InitPush(p, 1+1);
  if (err != ERR_OK) return err;

  PushChar('?');
  PushChar(bError);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOutputX(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port)
{
  err_t err = InitPush(p, 1+6);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushMAC(pbMAC);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOutput_GetLong(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong dw)
{
  err_t err = CheckSize(p,6);
  if (err != ERR_OK) { UDPOutput_Error(pcb, p, addr, port, err); return err; }

  err = PopCode(p);
  if (err != ERR_OK) { UDPOutput_Error(pcb, p, addr, port, err); return err; }

  err = InitPush(p, 1+4+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushLongLtl(dw);
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}


err_t UDPOutput_SetLong(struct udp_pcb *pcb, struct pbuf *p, struct ip_addr *addr, uint port, ulong *pdw)
{
  err_t err = CheckSize(p,10);
  if (err != ERR_OK) { UDPOutput_Error(pcb, p, addr, port, err); return err; }

  err = PopCode(p);
  if (err != ERR_OK) { UDPOutput_Error(pcb, p, addr, port, err); return err; }

  *pdw = PopLongLtl(p, 3);

  err = InitPush(p, 1+3);
  if (err != ERR_OK) return err;

  PushChar('A');
  PushChar('|');
  PushIntLtl(wCode);

  UDPOutput(pcb, p, addr, port);
  return ERR_OK;
}
