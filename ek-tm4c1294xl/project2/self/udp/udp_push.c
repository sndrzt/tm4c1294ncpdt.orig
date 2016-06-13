/*------------------------------------------------------------------------------
udp_push,c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "udp_push_numbers.h"
#include "udp_push.h"



uchar                   mbUDPPush[UDP_PUSH_SIZE];
uint                    iwUDPPush;


uint                    cwErrUPDPushCharOverflow = 0;



void InitPush(void)
{
  iwUDPPush = 0;
}


void PushChar(const uchar b)
{
  if (iwUDPPush < UDP_PUSH_SIZE)
    mbUDPPush[iwUDPPush++] = b;
  else
    cwErrUPDPushCharOverflow++;
}


void PushString(const char *sz)
{
  while (*sz)
  {
    PushChar(*sz++);
  }
}


void PushBuff(buff bf) // TODO const
{
  while (bf.wSize-- > 0)
  {
    PushChar(*(bf.pbBuff++));
  }
}



void PushIP(const ulong dw)
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


void PushMAC(const uchar *pb, const uchar bSize)
{
  uchar i;
  for (i=0; i<bSize; i++)
  {
    PushCharDec(pb[i]);

    if (i < bSize-1)
      PushChar('.');
  }
}


void PushSuffix(const uint w)
{
  PushChar('|');
  PushIntHex(w);
}
