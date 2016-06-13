/*------------------------------------------------------------------------------
udp_log,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "lwip/inet.h"
#include "lwip/udp.h"
#include "../kernel/settings.h"
#include "udp_log.h"



static void            *pcb;

static bool             enabled = true;

static uint             errors1, errors2;



void InitUDPLog(void)
{
  if (enabled)
  {
    pcb = udp_new();
  }
}



void UDPLog(uchar *pb, uint wSize)
{
  if (enabled)
  {
    struct pbuf *p = pbuf_alloc(PBUF_TRANSPORT, wSize, PBUF_RAM);
    if (p == NULL)
    {
      errors1++;
    }
    else
    {
      memcpy(p->payload, pb, wSize);

      err_t err = udp_sendto(pcb, p, IP_ADDR_BROADCAST, wUDPDebugPort);
      if (err != 0)
      {
        errors2++;
      }

      pbuf_free(p);
    }
  }
}
