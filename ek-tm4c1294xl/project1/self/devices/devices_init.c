/*------------------------------------------------------------------------------
DEVICES_INIT.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../console.h"
#include "../memory/mem_digitals.h"
#include "../memory/mem_phones.h"
#include "../keyboard/time/key_timedate.h"
#include "../digitals/digitals.h"
#include "../digitals/digitals_status.h"
#include "../digitals/digitals_pause.h"
#include "../digitals/digitals_messages.h"
#include "../digitals/digitals_display.h"
#include "../digitals/wait_answer.h"
#include "../digitals/wait_query.h"
#include "../digitals/current/current_run.h"
#include "../digitals/profile/profile_run.h"
#include "../digitals/checkup/checkup_run.h"
#include "../digitals/max_repeats.h"
#include "../special/recalc_def.h"
#include "../sensors/device_b.h"
#include "../serial/ports.h"
#include "../serial/ports_modems.h"
#include "../serial/modems.h"
#include "../serial/speeds_display.h"
#include "../digitals/disable_answer.h"
#include "../digitals/profile/refill.h"
#include "../digitals/schedule/schedule.h"
#include "../flash/records.h"
#include "../time/delay.h"
#include "../digitals/extended/extended_0.h"
#include "../digitals/extended/extended_1.h"
#include "../digitals/extended/extended_3.h"
#include "../digitals/extended/extended_4.h"
#include "../digitals/extended/extended_4t.h"
#include "../digitals/extended/extended_5.h"
#include "../digitals/extended/extended_6.h"
#include "../digitals/extended/extended_7.h"
#include "devices_input.h"
#include "devices_postinput.h"
#include "devices_pause.h"
#include "devices.h"
#include "devices_init.h"



cache const             chSeparateCan = {SEPARATE_CAN, &boSeparateCan, sizeof(bool)};
cache const             chShowMessages = {SHOW_MESSAGES, &boShowMessages, sizeof(bool)};
cache const             chHideMessages = {HIDE_MESSAGES, &boHideMessages, sizeof(bool)};
cache const             chControlTime = {CONTROL_TIME, &boControlTime, sizeof(bool)};
cache const             chManageTime = {MANAGE_TIME, &boManageTime, sizeof(bool)};

cache const             chKeysLevelB = {KEYS_LEVEL_B, &bKeysLevelB, sizeof(uchar)};
cache const             chShortProfileC = {SHORT_PROFILE_C, &boShortProfileC, sizeof(bool)};
cache const             chControlQ = {CONTROL_Q, &boControlQ, sizeof(bool)};
cache const             chPlcUFlag = {PLC_U_FLAG, &boPlcUFlag, sizeof(bool)};
cache const             chPlcUSize = {PLC_U_SIZE, &bPlcUSize, sizeof(uchar)};
cache const             chPlcUShutdown = {PLC_U_SHUTDOWN, &wPlcUShutdown, sizeof(uint)};



void    InitDevices1(void)
{
  LoadCache(&chSeparateCan);
  LoadCache(&chShowMessages);
  LoadCache(&chHideMessages);
  LoadCache(&chControlTime);
  LoadCache(&chManageTime);

  LoadCacheChar(&chKeysLevelB, 1, 2, 2);
  LoadCache(&chShortProfileC);
  LoadCache(&chControlQ);
  LoadCacheBool(&chPlcUFlag, false);
  LoadCacheChar(&chPlcUSize, 1, 8, 6);
  LoadCacheInt(&chPlcUShutdown, 10, 500, 100);

  InitMaxRepeats();
  InitDef();
  InitRefill();
  InitSchedule();
  InitExtended0();
  InitExtended1();
  InitExtended3();
  InitExtended4();
  InitExtended4T();
  InitExtended5();
  InitExtended6();
}


void    InitDevices2(void)
{
//uchar   i,j;
//
//  if (GetLabel() == 0)
//  {
//    MakeDigitals();
//
//    for (i=0; i<bCANALS; i++) mpboBase[i] = false;
//
//    for (i=0; i<bCANALS; i++) mpreEngFrac[i] = 0;
//
//    for (i=0; i<bCANALS; i++)
//      for (j=0; j<6; j++) mpreEngFracDigCan[i][j] = 0;
//  }

  SetCurr(DEV_BEGIN);
  SetPause(DEV_BEGIN);

  InitWaitAnswer();
  InitWaitQuery();
  cbWaitOnline = 0;

  fConnect = 0;
  InitConnectKey();

  ibPortPause = 0xFF;

  EnableAnswer();
}


void    ResetDevices(bool  fFull)
{
  boSeparateCan = false;
  SaveCache(&chSeparateCan);

  boShowMessages = false;
  SaveCache(&chShowMessages);

  boHideMessages = false;
  SaveCache(&chHideMessages);

  boControlTime = true;
  SaveCache(&chControlTime);

  boManageTime = true;
  SaveCache(&chManageTime);

  bKeysLevelB = 2;
  SaveCache(&chKeysLevelB);

  boShortProfileC = false;
  SaveCache(&chShortProfileC);

  boControlQ = false;
  SaveCache(&chControlQ);

  boPlcUFlag = false;
  SaveCache(&chPlcUFlag);

  bPlcUSize = 6;
  SaveCache(&chPlcUSize);

  wPlcUShutdown = 100;
  SaveCache(&chPlcUShutdown);

  ResetMaxRepeats();
  ResetDef();
  ResetRefill();
  ResetSchedule();
  ResetExtended0(fFull);
  ResetExtended1();
  ResetExtended3();
  ResetExtended4(fFull);
  ResetExtended4T(fFull);
  ResetExtended5(fFull);
  ResetExtended6(fFull);
  ResetExtended7();
}
