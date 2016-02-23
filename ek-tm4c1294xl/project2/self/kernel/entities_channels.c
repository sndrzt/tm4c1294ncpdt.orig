/*------------------------------------------------------------------------------
entities_channels,C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../generated/eeprom.h"
#include "settings.h"
#include "entities_channels.h"



const entity enConnectionTimeout0 = {
  EEPROM_CONNECTION_TIMEOUT_0, &mbConnectionTimeout[0], sizeof(uchar), CHAR, 0,
  0, 255, DEFAULT_CONNECTION_TIMEOUT,
  "CT@0",
  "AI=CT@0;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT@0>255?\"Maximum timeout is 255 minutes\":\"\"",
};

const entity enConnectionTimeout1 = {
  EEPROM_CONNECTION_TIMEOUT_1, &mbConnectionTimeout[1], sizeof(uchar), CHAR, 0,
  0, 255, DEFAULT_CONNECTION_TIMEOUT,
  "CT@1",
  "AI=CT@1;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT@1>255?\"Maximum timeout is 255 minutes\":\"\"",
};

const entity enConnectionTimeout2 = {
  EEPROM_CONNECTION_TIMEOUT_2, &mbConnectionTimeout[2], sizeof(uchar), CHAR, 0,
  0, 255, DEFAULT_CONNECTION_TIMEOUT,
  "CT@2",
  "AI=CT@2;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT@2>255?\"Maximum timeout is 255 minutes\":\"\"",
};

const entity enConnectionTimeout3 = {
  EEPROM_CONNECTION_TIMEOUT_3, &mbConnectionTimeout[3], sizeof(uchar), CHAR, 0,
  0, 255, DEFAULT_CONNECTION_TIMEOUT,
  "CT@3",
  "AI=CT@3;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT@3>255?\"Maximum timeout is 255 minutes\":\"\"",
};

const entity enConnectionTimeout4 = {
  EEPROM_CONNECTION_TIMEOUT_4, &mbConnectionTimeout[4], sizeof(uchar), CHAR, 0,
  0, 255, DEFAULT_CONNECTION_TIMEOUT,
  "CT@4",
  "AI=CT@4;D=Connection timeout (minutes);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT@4>255?\"Maximum timeout is 255 minutes\":\"\"",
};


const entity enRoutingMode0 = {
  EEPROM_ROUTING_MODE_0, &mbRoutingMode[0], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_ROUTING_MODE,
  "RM@0",
  "AI=RM@0;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};

const entity enRoutingMode1 = {
  EEPROM_ROUTING_MODE_1, &mbRoutingMode[1], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_ROUTING_MODE,
  "RM@1",
  "AI=RM@1;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};

const entity enRoutingMode2 = {
  EEPROM_ROUTING_MODE_2, &mbRoutingMode[2], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_ROUTING_MODE,
  "RM@2",
  "AI=RM@2;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};

const entity enRoutingMode3 = {
  EEPROM_ROUTING_MODE_3, &mbRoutingMode[3], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_ROUTING_MODE,
  "RM@3",
  "AI=RM@3;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};

const entity enRoutingMode4 = {
  EEPROM_ROUTING_MODE_4, &mbRoutingMode[4], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_ROUTING_MODE,
  "RM@4",
  "AI=RM@4;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/1-Client (Master)/1",
};


const entity enPort0 = {
  EEPROM_PORT_0, &mwPort[0], sizeof(uint), INT, 0,
  0, 65534, DEFAULT_PORT+0,
  "PN@0",
  "AI=PN@0;E=1;D=Port;T=INT;C=EDIT;V=PN@0>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@0!=1?\"e\":\"i\"",
};

const entity enPort1 = {
  EEPROM_PORT_1, &mwPort[1], sizeof(uint), INT, 0,
  0, 65534, DEFAULT_PORT+1,
  "PN@1",
  "AI=PN@1;E=1;D=Port;T=INT;C=EDIT;V=PN@1>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@1!=1?\"e\":\"i\"",
};

const entity enPort2 = {
  EEPROM_PORT_2, &mwPort[2], sizeof(uint), INT, 0,
  0, 65534, DEFAULT_PORT+2,
  "PN@2",
  "AI=PN@2;E=1;D=Port;T=INT;C=EDIT;V=PN@2>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@2!=1?\"e\":\"i\"",
};

const entity enPort3 = {
  EEPROM_PORT_3, &mwPort[3], sizeof(uint), INT, 0,
  0, 65534, DEFAULT_PORT+3,
  "PN@3",
  "AI=PN@3;E=1;D=Port;T=INT;C=EDIT;V=PN@3>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@3!=1?\"e\":\"i\"",
};

const entity enPort4 = {
  EEPROM_PORT_4, &mwPort[4], sizeof(uint), INT, 0,
  0, 65534, DEFAULT_PORT+4,
  "PN@4",
  "AI=PN@4;E=1;D=Port;T=INT;C=EDIT;V=PN@4>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@4!=1?\"e\":\"i\"",
};


const entity enConnectionMode0 = {
  EEPROM_CONNECTION_MODE_0, &mbConnectionMode[0], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_CONNECTION_MODE,
  "CM@0",
  "AI=CM@0;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM@0!=0?\"e\":\"i\"",
};

const entity enConnectionMode1 = {
  EEPROM_CONNECTION_MODE_1, &mbConnectionMode[1], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_CONNECTION_MODE,
  "CM@1",
  "AI=CM@1;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM@1!=0?\"e\":\"i\"",
};

const entity enConnectionMode2 = {
  EEPROM_CONNECTION_MODE_2, &mbConnectionMode[2], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_CONNECTION_MODE,
  "CM@2",
  "AI=CM@2;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM@2!=0?\"e\":\"i\"",
};

const entity enConnectionMode3 = {
  EEPROM_CONNECTION_MODE_3, &mbConnectionMode[3], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_CONNECTION_MODE,
  "CM@3",
  "AI=CM@3;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM@3!=0?\"e\":\"i\"",
};

const entity enConnectionMode4 = {
  EEPROM_CONNECTION_MODE_4, &mbConnectionMode[4], sizeof(uchar), CHAR, 0,
  0, 1, DEFAULT_CONNECTION_MODE,
  "CM@4",
  "AI=CM@4;E=1;D=Connection mode;T=INT;C=STATIC;O=0-Immediately/0/1-On data/1;S=RM@4!=0?\"e\":\"i\"",
};


const entity enDestinationIP0 = {
  EEPROM_DESTINATION_IP_0, &mdwDestinationIP[0], sizeof(ulong), IP, 0,
  0, MAX_LONG, DEFAULT_DESTINATION_IP,
  "DI@0",
  "AI=DI@0;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM@0==1?\"e\":\"i\"",
};

const entity enDestinationIP1 = {
  EEPROM_DESTINATION_IP_1, &mdwDestinationIP[1], sizeof(ulong), IP, 0,
  0, MAX_LONG, DEFAULT_DESTINATION_IP,
  "DI@1",
  "AI=DI@1;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM@1==1?\"e\":\"i\"",
};

const entity enDestinationIP2 = {
  EEPROM_DESTINATION_IP_2, &mdwDestinationIP[2], sizeof(ulong), IP, 0,
  0, MAX_LONG, DEFAULT_DESTINATION_IP,
  "DI@2",
  "AI=DI@2;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM@2==1?\"e\":\"i\"",
};

const entity enDestinationIP3 = {
  EEPROM_DESTINATION_IP_3, &mdwDestinationIP[3], sizeof(ulong), IP, 0,
  0, MAX_LONG, DEFAULT_DESTINATION_IP,
  "DI@3",
  "AI=DI@3;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM@3==1?\"e\":\"i\"",
};

const entity enDestinationIP4 = {
  EEPROM_DESTINATION_IP_4, &mdwDestinationIP[4], sizeof(ulong), IP, 0,
  0, MAX_LONG, DEFAULT_DESTINATION_IP,
  "DI@4",
  "AI=DI@4;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM@4==1?\"e\":\"i\"",
};


const entity enDestinationPort0 = {
  EEPROM_DESTINATION_PORT_0, &mwDestinationPort[0], sizeof(uint), INT, 0,
  0, MAX_INT, DEFAULT_DESTINATION_PORT+0,
  "DP@0",
  "AI=DP@0;E=1;D=Destination port;T=INT;C=EDIT;S=RM@0!=0?\"e\":\"i\"",
};

const entity enDestinationPort1 = {
  EEPROM_DESTINATION_PORT_1, &mwDestinationPort[1], sizeof(uint), INT, 0,
  0, MAX_INT, DEFAULT_DESTINATION_PORT+1,
  "DP@1",
  "AI=DP@1;E=1;D=Destination port;T=INT;C=EDIT;S=RM@1!=0?\"e\":\"i\"",
};

const entity enDestinationPort2 = {
  EEPROM_DESTINATION_PORT_2, &mwDestinationPort[2], sizeof(uint), INT, 0,
  0, MAX_INT, DEFAULT_DESTINATION_PORT+2,
  "DP@2",
  "AI=DP@2;E=1;D=Destination port;T=INT;C=EDIT;S=RM@2!=0?\"e\":\"i\"",
};

const entity enDestinationPort3 = {
  EEPROM_DESTINATION_PORT_3, &mwDestinationPort[3], sizeof(uint), INT, 0,
  0, MAX_INT, DEFAULT_DESTINATION_PORT+3,
  "DP@3",
  "AI=DP@3;E=1;D=Destination port;T=INT;C=EDIT;S=RM@3!=0?\"e\":\"i\"",
};

const entity enDestinationPort4 = {
  EEPROM_DESTINATION_PORT_4, &mwDestinationPort[4], sizeof(uint), INT, 0,
  0, MAX_INT, DEFAULT_DESTINATION_PORT+4,
  "DP@4",
  "AI=DP@4;E=1;D=Destination port;T=INT;C=EDIT;S=RM@4!=0?\"e\":\"i\"",
};


const entity enBaudRate0 = {
  EEPROM_BAUD_RATE_0, &mibBaudRate[0], sizeof(uchar), CHAR, 0,
  0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
  "BR@0",
  "AI=BR@0;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaudRate1 = {
  EEPROM_BAUD_RATE_1, &mibBaudRate[1], sizeof(uchar), CHAR, 0,
  0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
  "BR@1",
  "AI=BR@1;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaudRate2 = {
  EEPROM_BAUD_RATE_2, &mibBaudRate[2], sizeof(uchar), CHAR, 0,
  0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
  "BR@2",
  "AI=BR@2;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaudRate3 = {
  EEPROM_BAUD_RATE_3, &mibBaudRate[3], sizeof(uchar), CHAR, 0,
  0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
  "BR@3",
  "AI=BR@3;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaudRate4 = {
  EEPROM_BAUD_RATE_4, &mibBaudRate[4], sizeof(uchar), CHAR, 0,
  0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
  "BR@4",
  "AI=BR@4;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};


const entity enParity0 = {
  EEPROM_PARITY_0, &mibParity[0], sizeof(uchar), CHAR, 0,
  0, PARITY_COUNT-1, DEFAULT_PARITY,
  "PR@0",
  "AI=PR@0;D=Parity;T=INT;C=STATIC;O=0-None/0/1-Even/1/2-Odd/2/3-Mark/3/4-Space/4",
};

const entity enParity1 = {
  EEPROM_PARITY_1, &mibParity[1], sizeof(uchar), CHAR, 0,
  0, PARITY_COUNT-1, DEFAULT_PARITY,
  "PR@1",
  "AI=PR@1;D=Parity;T=INT;C=STATIC;O=0-None/0/1-Even/1/2-Odd/2/3-Mark/3/4-Space/4",
};

const entity enParity2 = {
  EEPROM_PARITY_2, &mibParity[2], sizeof(uchar), CHAR, 0,
  0, PARITY_COUNT-1, DEFAULT_PARITY,
  "PR@2",
  "AI=PR@2;D=Parity;T=INT;C=STATIC;O=0-None/0/1-Even/1/2-Odd/2/3-Mark/3/4-Space/4",
};

const entity enParity3 = {
  EEPROM_PARITY_3, &mibParity[3], sizeof(uchar), CHAR, 0,
  0, PARITY_COUNT-1, DEFAULT_PARITY,
  "PR@3",
  "AI=PR@3;D=Parity;T=INT;C=STATIC;O=0-None/0/1-Even/1/2-Odd/2/3-Mark/3/4-Space/4",
};

const entity enParity4 = {
  EEPROM_PARITY_4, &mibParity[4], sizeof(uchar), CHAR, 0,
  0, PARITY_COUNT-1, DEFAULT_PARITY,
  "PR@4",
  "AI=PR@4;D=Parity;T=INT;C=STATIC;O=0-None/0/1-Even/1/2-Odd/2/3-Mark/3/4-Space/4",
};


const entity enDataBits0 = {
  EEPROM_DATA_BITS_0, &mibDataBits[0], sizeof(uchar), CHAR, 0,
  0, DATA_BITS_COUNT-1, DEFAULT_DATA_BITS,
  "DB@0",
  "AI=DB@0;D=Data bits;T=INT;C=STATIC;O=0-7 bits/0/1-8 bits/1",
};

const entity enDataBits1 = {
  EEPROM_DATA_BITS_1, &mibDataBits[1], sizeof(uchar), CHAR, 0,
  0, DATA_BITS_COUNT-1, DEFAULT_DATA_BITS,
  "DB@1",
  "AI=DB@1;D=Data bits;T=INT;C=STATIC;O=0-7 bits/0/1-8 bits/1",
};

const entity enDataBits2 = {
  EEPROM_DATA_BITS_2, &mibDataBits[2], sizeof(uchar), CHAR, 0,
  0, DATA_BITS_COUNT-1, DEFAULT_DATA_BITS,
  "DB@2",
  "AI=DB@2;D=Data bits;T=INT;C=STATIC;O=0-7 bits/0/1-8 bits/1",
};

const entity enDataBits3 = {
  EEPROM_DATA_BITS_3, &mibDataBits[3], sizeof(uchar), CHAR, 0,
  0, DATA_BITS_COUNT-1, DEFAULT_DATA_BITS,
  "DB@3",
  "AI=DB@3;D=Data bits;T=INT;C=STATIC;O=0-7 bits/0/1-8 bits/1",
};

const entity enDataBits4 = {
  EEPROM_DATA_BITS_4, &mibDataBits[4], sizeof(uchar), CHAR, 0,
  0, DATA_BITS_COUNT-1, DEFAULT_DATA_BITS,
  "DB@4",
  "AI=DB@4;D=Data bits;T=INT;C=STATIC;O=0-7 bits/0/1-8 bits/1",
};


const entity enStopBits0 = {
  EEPROM_STOP_BITS_0, &mibStopBits[0], sizeof(uchar), CHAR, 0,
  0, STOP_BITS_COUNT-1, DEFAULT_STOP_BITS,
  "SB@0",
  "AI=SB@0;D=Stop bits;T=INT;C=STATIC;O=0-1 bit/0/1-2 bits/1",
};

const entity enStopBits1 = {
  EEPROM_STOP_BITS_1, &mibStopBits[1], sizeof(uchar), CHAR, 0,
  0, STOP_BITS_COUNT-1, DEFAULT_STOP_BITS,
  "SB@1",
  "AI=SB@1;D=Stop bits;T=INT;C=STATIC;O=0-1 bit/0/1-2 bits/1",
};

const entity enStopBits2 = {
  EEPROM_STOP_BITS_2, &mibStopBits[2], sizeof(uchar), CHAR, 0,
  0, STOP_BITS_COUNT-1, DEFAULT_STOP_BITS,
  "SB@2",
  "AI=SB@2;D=Stop bits;T=INT;C=STATIC;O=0-1 bit/0/1-2 bits/1",
};

const entity enStopBits3 = {
  EEPROM_STOP_BITS_3, &mibStopBits[3], sizeof(uchar), CHAR, 0,
  0, STOP_BITS_COUNT-1, DEFAULT_STOP_BITS,
  "SB@3",
  "AI=SB@3;D=Stop bits;T=INT;C=STATIC;O=0-1 bit/0/1-2 bits/1",
};

const entity enStopBits4 = {
  EEPROM_STOP_BITS_4, &mibStopBits[4], sizeof(uchar), CHAR, 0,
  0, STOP_BITS_COUNT-1, DEFAULT_STOP_BITS,
  "SB@4",
  "AI=SB@4;D=Stop bits;T=INT;C=STATIC;O=0-1 bit/0/1-2 bits/1",
};
