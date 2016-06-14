/*------------------------------------------------------------------------------
watchdog.c


------------------------------------------------------------------------------*/

#include "../main.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "driverlib/watchdog.h"
#include "driverlib/sysctl.h"
#include "../kernel/settings.h"
#include "../kernel/log.h"
#include "watchdog.h"



#define WATCHDOG_VALUE  0x20000000



void EnableWatchdog(void)
{
#ifdef ENABLE_WATCHDOG

  HWREG(SYSCTL_RCGCWD) |= SYSCTL_RCGCWD_R0;

  WatchdogReloadSet(WATCHDOG0_BASE, WATCHDOG_VALUE);

  WatchdogEnable(WATCHDOG0_BASE);
  WatchdogResetEnable(WATCHDOG0_BASE);
  WatchdogStallEnable(WATCHDOG0_BASE);

#endif
}


void DisableWatchdog(void)
{
#ifdef ENABLE_WATCHDOG

  HWREG(SYSCTL_RCGCWD) |= SYSCTL_RCGCWD_R0;

  WatchdogReloadSet(WATCHDOG0_BASE, WATCHDOG_VALUE);
  WatchdogResetDisable(WATCHDOG0_BASE);

#endif
}


void ResetWatchdog(void)
{
#ifdef ENABLE_WATCHDOG

  WatchdogReloadSet(WATCHDOG0_BASE, WATCHDOG_VALUE);

#endif
}



void InitWatchdog(void)
{
  DisableWatchdog();

  if (fWatchdogFlag != false)
    EnableWatchdog();

  fWatchdogReset = IsWatchdogReset();
  if (fWatchdogReset)
  {
    WARNING("watchdog reset\n");
  }
}


bool IsWatchdogReset(void)
{
  bool f = ((SysCtlResetCauseGet() & SYSCTL_CAUSE_WDOG0) != 0);
  SysCtlResetCauseClear(SYSCTL_CAUSE_WDOG0);
  return f;
}

