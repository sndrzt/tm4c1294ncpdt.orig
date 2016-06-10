/*------------------------------------------------------------------------------
settings.h


------------------------------------------------------------------------------*/

#include "entities.h"
#include "entities_default.h"



extern const ulong             mdwBaudRates[BAUD_RATE_COUNT];



extern uchar                   pbMac[6];

extern uint                    wSerialNumber;

extern ulong                   dwIP;
extern ulong                   dwGateway;
extern ulong                   dwNetmask;

extern char                    szOwnerName[NAME_SIZE];
extern char                    szDeviceName[NAME_SIZE];

extern uchar                   mbConnectionTimeout[UART_COUNT];
extern uchar                   mbRoutingMode[UART_COUNT];
extern uint                    mwPort[UART_COUNT];
extern uchar                   mbConnectionMode[UART_COUNT];
extern ulong                   mdwDestinationIP[UART_COUNT];
extern uint                    mwDestinationPort[UART_COUNT];

extern uchar                   mibBaudRate[UART_COUNT];
extern uchar                   mibParity[UART_COUNT];
extern uchar                   mibDataBits[UART_COUNT];
extern uchar                   mibStopBits[UART_COUNT];

extern bool                    fWatchdogFlag;
extern bool                    ibDebugMode;

extern ulong                   dwUdpDebugIP;
extern uint                    wUdpDebugPort;

extern bool                    fLwipDebugFlag;
extern uint                    wLwipDebugTimeout;

extern bool                    fDataDebugFlag;
extern bool                    fIOModeDebugFlag;

extern ledMode                 bLED0Mode;
extern ledMode                 bLED1Mode;

extern uint                    cwErrStorageInit;
extern uint                    cwErrIpLoad;
extern uint                    cwErrEntitySave;



void InitSettings(void);
void ResetSettings(void);
