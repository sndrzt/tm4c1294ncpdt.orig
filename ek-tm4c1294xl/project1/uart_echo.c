/*------------------------------------------------------------------------------
TODO .C


------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "src/hardware/watchdog.h"
#include "src/hardware/system_clock.h"
#include "src/hardware/beep.h"
#include "src/display/lcd.h"
#include "src/time/rtc.h"
#include "src/keyboard/infrared.h"
#include "src/keyboard/key.h"
#include "src/keyboard/keyboard.h"
#include "src/nvram/23x1024.h"
#include "src/flash/at45.h"
#include "src/display/display.h"
#include "src/isr/timer0.h"
#include "src/isr/timer1.h"
#include "src/isr/timer2.h"
#include "src/isr/serial0.h"
#include "src/isr/serial1.h"
#include "src/isr/serial2.h"
#include "src/isr/serial3.h"
#include "src/hardware/memory.h"
#include "src/hardware/power_off.h"
#include "src/uarts.h"
#include "src/serial/modems.h"
#include "src/serial/print.h"
#include "src/flash/storage.h"
#include "src/flash/records.h"
#include "src/settings.h"
#include "src/impulses/impulses.h"
#include "src/impulses/factors.h"
#include "src/groups.h"
#include "src/tariffs/zones.h"
#include "src/tariffs/tariffs.h"
#include "src/tariffs/relaxs.h"
#include "src/tariffs/gaps.h"
#include "src/digitals/digitals.h"
#include "src/digitals/limits.h"
#include "src/digitals/params/params.h"
#include "src/digitals/profile/profile_core.h"
#include "src/devices/devices_init.h"
#include "src/devices/devices.h"
#include "src/digitals/phones.h"
#include "src/special/defects.h"
#include "src/serial/speeds.h"
#include "src/serial/flow.h"
#include "src/output/esc/esc.h"
#include "src/output/esc/response_esc.h"
#include "src/output/unified/uni.h"
#include "src/output/unified/response_uni.h"
#include "src/time/decret.h"
#include "src/time/correct1.h"
#include "src/time/correct2.h"
#include "src/special/recalc.h"
#include "src/realtime/realtime.h"
#include "src/realtime/realtime_init.h"
#include "src/output/response_crc.h"



int main(void) {
  ui32SysClock = GetSystemClockFrequency();

  InitUart0(ui32SysClock);
  InitUart2(ui32SysClock);
  InitUart3(ui32SysClock);
  InitUart4(ui32SysClock);

  DisableWDT();

	InitBeep();
	InitLCD();
	InitNvram();
	InitFlash();            //Delay(100); TestOK();
	InitRTC();
	InitCODE();

	InitRecords();
	InitSettings();         //Delay(100); TestOK();
	InitInfrared();
	InitKey();
	InitKeyboard();         //Delay(100); TestOK();
	InitImpulses();
	InitFactors();
	InitGroups();           //Delay(100); TestOK();
	InitZones();
	InitTariffs();          //Delay(100); TestOK();
	InitRelaxs();
	InitGaps();             //Delay(100); TestOK();
	InitDecret();
	InitCorrect1();
	InitCorrect2();
	InitDigitals();         //Delay(100); TestOK();
	InitLimits();
  InitDevices1();
	InitParams();
	InitPhones();
	InitProfile();
	InitSpeeds();
	InitEsc();
	InitUni();
	InitFlow();             //Delay(100); TestOK();
	InitPowerOff();

	InitSlide();

  PrintStart();
	InitStorage();
  InitDefects();
	InitRealtime();
  PrintStop();

	InitDisplay();

//    InitCurrent();
//    InitProfiles();
    InitDevices2();

    InitSerial0();
    InitSerial1();
    InitSerial2();
    InitSerial3();

    InitTimer0(ui32SysClock);
    InitTimer1(ui32SysClock);
    InitTimer2(ui32SysClock);

    IntMasterEnable();

    InitRecalc();
    LongBeep();

    InitWDT();

    while (1) {
    	ASSERT((enGlobal == GLB_PROGRAM) || (enGlobal == GLB_WORK) || (enGlobal == GLB_REPROGRAM));

    	ResetWDT();

    	RunRealtime();
    	RunDevices();
    	RunInfrared();
    	RunKeyboard();
    	RunLocal();

    	RunResponseCRC_All();
    	RunResponseEsc_All();
    	RunResponseUni_All();
    	RunResponseFlow_All();
    }
}
