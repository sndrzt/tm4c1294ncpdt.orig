/*------------------------------------------------------------------------------
ENTITY.C


------------------------------------------------------------------------------*/

#include "main.h"
#include "generated/eeprom.h"
#include "settings.h"
#include "entity.h"



const entity enConnectionTimeout = {
        EEPROM_CONNECTION_TIMEOUT, &bConnectionTimeout, sizeof(uchar), CHAR,
        0, 255, DEFAULT_CONNECTION_TIMEOUT,
        "CT",
        "AI=CT;D=Connection timeout (min);T=INT;C=EDIT/SPIN/0/1/1/10;O=0-Disabled/0;V=CT>255?\"Maximum timeout is 255 minutes\":\"\"",
};


const entity enRoutingMode0 = {
        EEPROM_ROUTING_MODE_0, &mbRoutingMode[0], sizeof(uchar), CHAR,
        0, 2, DEFAULT_ROUTING_MODE, // TODO 2-> 1
        "RM",
        "AI=RM;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/2-Client (Master)/2",
};

const entity enRoutingMode1 = {
        EEPROM_ROUTING_MODE_1, &mbRoutingMode[1], sizeof(uchar), CHAR,
        0, 2, DEFAULT_ROUTING_MODE, // TODO 2-> 1
        "RM@2",
        "AI=RM@2;D=Routing mode;T=INT;C=STATIC;O=0-Server (Slave)/0/2-Client (Master)/2",
};


const entity enPort0 = {
        EEPROM_PORT_0, &mwPort[0], sizeof(uint), INT,
        0, 65534, 101,
        "PN",
		"AI=PN;E=1;D=Port;T=INT;C=EDIT;V=PN>65534?\"Port number must be between 0 and 65534\":\"\";S=RM!=2?\"e\":\"i\"",
};

const entity enPort1 = {
        EEPROM_PORT_1, &mwPort[1], sizeof(uint), INT,
        0, 65534, 102,
        "PN@2",
		"AI=PN@2;E=1;D=Port;T=INT;C=EDIT;V=PN@2>65534?\"Port number must be between 0 and 65534\":\"\";S=RM@2!=2?\"e\":\"i\"",
};


const entity enDestIP = {
        EEPROM_DEST_IP, &dwDestIP, sizeof(ulong), LONG,
        0, MAX_LONG, DEFAULT_DEST_IP,
        "DI",
        "AI=DI;E=1;D=Destination IP-address;T=STRING;C=IPCTRL;S=RM==1||RM==2?\"e\":\"i\"", // TODO ||SF==1
};

const entity enDestPort = {
        EEPROM_DEST_PORT, &wDestPort, sizeof(uint), INT,
        0, MAX_INT, DEFAULT_DEST_PORT,
        "DP",
        "AI=DP;E=1;D=Destination port;T=INT;C=EDIT;S=RM!=0?\"e\":\"i\"",
};


const entity enBaudRate0 = {
        EEPROM_BAUD_RATE_0, &mibBaudRate[0], sizeof(uchar), CHAR,
        0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
        "BR",
        "AI=BR;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};

const entity enBaudRate1 = {
        EEPROM_BAUD_RATE_1, &mibBaudRate[1], sizeof(uchar), CHAR,
        0, BAUD_RATE_COUNT-1, DEFAULT_BAUD_RATE,
        "BR@2",
        "AI=BR@2;D=Baud rate;T=INT;C=STATIC;O=0-150bps/0/1-300bps/1/2-600bps/2/3-1200bps/3/4-2400bps/4/5-4800bps/5/6-9600bps/6/7-19200bps/7/8-28800bps/8/9-38400bps/9/10-57600bps/10/11-115200bps/11/12-230400bps/12/13-460800bps/13",
};


const entity enUdpDebugFlag = {
        EEPROM_UDP_DEBUG_FLAG, &fUdpDebugFlag, sizeof(uchar), CHAR,
        0, 1, 0,
        "UDF",
        "AI=UDF;D=UDP debug;T=INT;C=STATIC;O=0-No/0/1-Yes/1",
};

// TODO enUdpDebugIP

const entity enUdpDebugPort = {
        EEPROM_UDP_DEBUG_PORT, &wUdpDebugPort, sizeof(uint), INT,
        0, MAX_INT, 50000,
        "UDP",
        "AI=UDP;E=1;D=UDP debug port;T=INT;C=EDIT;S=UDF!=0?\"e\":\"i\"",
};
