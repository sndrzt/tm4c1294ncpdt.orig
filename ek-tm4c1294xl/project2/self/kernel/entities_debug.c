/*------------------------------------------------------------------------------
entities_debug.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
#include "entities_debug.h"



const entity enDebugMode = {
  EEPROM_DEBUG_MODE, &ibDebugMode, sizeof(uchar), CHAR, 0,
  0, 2, 0,
  "DBMD",
  "AI=DBMD;D=Debug mode;T=INT;C=STATIC;O=0-No/0/1-UDP/1/2-UART/2",
};


const entity enUDPDebugIP = {
  EEPROM_UDP_DEBUG_IP, &dwUDPDebugIP, sizeof(ulong), IP, 0,
  0, MAX_LONG, 0xFFFFFFFF,
  "UDPDI",
  "AI=UDPDI;E=1;D=UDP debug IP-address;T=STRING;C=IPCTRL;S=DBMD==1?\"e\":\"i\"",
};

const entity enUDPDebugPort = {
  EEPROM_UDP_DEBUG_PORT, &wUDPDebugPort, sizeof(uint), INT, 0,
  0, MAX_INT, 50000,
  "UDPDP",
  "AI=UDPDP;E=1;D=UDP debug port;T=INT;C=EDIT;S=DBMD==1?\"e\":\"i\"",
};


const entity enLWIPDebugFlag = {
  EEPROM_LWIP_DEBUG_FLAG, &fLWIPDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "LWIPDF",
  "AI=LWIPDF;D=TCP/IP stack debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

const entity enLWIPDebugTimeout = {
  EEPROM_LWIP_DEBUG_TIMEOUT, &wLWIPDebugTimeout, sizeof(uint), INT, 0,
  0, 3600, 300,
  "LWIPDT",
  "AI=LWIPDT;E=1;D=TCP/IP stack debug period (seconds);T=INT;C=EDIT;V=LWIPDT>3600?\"Maximum timeout is 3600 seconds\":\"\";S=LWIPDF!=0?\"e\":\"i\"",
};


const entity enDataDebugFlag = {
  EEPROM_DATA_DEBUG_FLAG, &fDataDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "DTDF",
  "AI=DTDF;D=Bytes debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};


const entity enIOModeDebugFlag = {
  EEPROM_IO_MODE_DEBUG_FLAG, &fIOModeDebugFlag, sizeof(uchar), CHAR, 0,
  0, 1, 0,
  "IOMDF",
  "AI=IOMDF;D=RS-485 I/O debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};


const entity enLED0Mode = {
  EEPROM_LED_MODE_0, &bLED0Mode, sizeof(uchar), CHAR, 0,
  0, 0, 0,
  "LED0MD",
  "AI=LED0MD;D=Ethernet LED0 mode;T=INT;C=STATIC;O=0-Link OK/0",
};

const entity enLED1Mode = {
  EEPROM_LED_MODE_1, &bLED1Mode, sizeof(uchar), CHAR, 0,
  0, 8, 1,
  "LED1MD",
  "AI=LED1MD;D=Ethernet LED1 mode;T=INT;C=STATIC;O=0-Link OK/0/1-RX\\TX activity/1/2-TX activity/2/3-RX activity/3/4-Collision/4/5-100-Base TX speed/5/6-10-Base TX speed/6/7-Full duplex/7/8-Link OK, blink on TX\\RX activity/8",
};
