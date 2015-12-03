/*------------------------------------------------------------------------------
UDP_PUSH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_push.h"

extern int usprintf(char * restrict s, const char * restrict format, ...);



static uchar            *pbPush;
static uchar            ibPush;



err_t InitPush2(struct pbuf **pp, uchar bSize)
{
  //
  // The incoming pbuf is no longer needed, so free it.
  //
  pbuf_free(*pp);

  *pp = pbuf_alloc(PBUF_TRANSPORT, bSize, PBUF_RAM);
  if (pp == NULL) return ERR_MEM;

  pbPush = (*pp)->payload;
  ibPush = 0;

  return ERR_OK;
}



void PushChar(uchar b)
{
  pbPush[ibPush++] = b;
}


void PushIntLtl(uint w)
{
  PushChar(w % 0x100);
  PushChar(w / 0x100);
}


void PushLongLtl(ulong dw)
{
  PushIntLtl(dw % 0x10000);
  PushIntLtl(dw / 0x10000);
}


void PushString(const char *sz)
{
  while (*sz)
  {
    PushChar(*sz++);
  }
}


uchar   PushIntHex(uint w)
{
static char mb[6*2];

  memset(&mb, 0, sizeof(mb));
  uchar n = usprintf(mb, "%X" ,w);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mb[i]);
  }

  return n;
}


uchar   PushCharDec(uchar b)
{
static char mb[4*2];

  memset(&mb, 0, sizeof(mb));
  uchar n = usprintf(mb, "%u" ,b);

  uchar i;
  for (i=0; i<n; i++)
  {
    PushChar(mb[i]);
  }

  return n;
}


void PushIP(ulong dw)
{
  combo32 cb;
  cb.dwBuff = dw;

  PushCharDec(cb.mpbBuff[3]);
  PushChar('.');
  PushCharDec(cb.mpbBuff[2]);
  PushChar('.');
  PushCharDec(cb.mpbBuff[1]);
  PushChar('.');
  PushCharDec(cb.mpbBuff[0]);
}


void PushSfx(uint w)
{
  PushChar('|');
  PushIntHex(w);
}


void PushArray(uchar *pb, uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushChar(pb[i]);
  }
}


void PushArrayString(uchar *pb, uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushCharDec(pb[i]);
    if (i < bSize-1) PushChar('.');
  }
}


uchar GetPushSize(void)
{
  return ibPush;
}


// TODO test overflow
