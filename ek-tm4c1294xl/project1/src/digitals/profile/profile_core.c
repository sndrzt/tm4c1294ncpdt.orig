/*------------------------------------------------------------------------------
PROFILE_CORE.C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_digitals.h"
#include "../../flash/files.h"
#include "../../nvram/cache.h"
#include "profile_core.h"



cache const             chEnblCan = {ENBL_CAN, &mpboEnblCan, sizeof(mpboEnblCan)};

cache const             chEnblCurrent = {ENBL_CURRENT, &boEnblCurrent, sizeof(bool)};
cache const             chEnblProfile = {ENBL_PROFILE, &boEnblProfile, sizeof(bool)};

cache const             chTimeoutCurrent = {TIMEOUT_CURRENT, &bTimeoutCurrent, sizeof(uchar)};
cache const             chTimeoutProfile = {TIMEOUT_PROFILE, &bTimeoutProfile, sizeof(uchar)};



void    InitProfile(void)
{
	LoadCache(&chEnblCan);

  LoadCache(&chEnblCurrent);
  LoadCache(&chEnblProfile);

  LoadCache(&chTimeoutCurrent);
  LoadCache(&chTimeoutProfile);
}



void    ResetProfile(void)
{
  uchar c;
  for (c=0; c<bCANALS; c++)
    mpboEnblCan[c] = true;

  SaveCache(&chEnblCan);

  boEnblCurrent = false;
  SaveCache(&chEnblCurrent);

  boEnblProfile = true;
  SaveCache(&chEnblProfile);

  bTimeoutCurrent = 2;
  SaveCache(&chTimeoutCurrent);

  bTimeoutProfile = 60;
  SaveCache(&chTimeoutProfile);
}
