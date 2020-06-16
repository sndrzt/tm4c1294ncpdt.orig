/*------------------------------------------------------------------------------
profile39_caller.c


------------------------------------------------------------------------------*/

#include "../../main.h"
// #include "../../memory/mem_digitals.h"
// #include "../../memory/mem_Profile.h"
// #include "../../memory/mem_factors.h"
// #include "../../serial/ports.h"
// #include "../../devices/devices.h"
// #include "../../digitals/digitals.h"
#include "../../kernel/tuples.h"
// #include "io39.h"
#include "device39.h"
#include "hdlc_monitor.h"
#include "profile39_caller.h"



static caller39         c;



void    InitRunner39_Profile(void) { 
  caller39 c = InitCaller();
}



void    Query39_DISC_Profile(void) {
  InitRunner39_Profile();

  Query39_DISC();
}


void    Query39_AARQ_Profile(void) {
  Query39_AARQ(c.bNS, c.bNR);
}


void    Query39_RR_Profile(void) {
  c.bNR++;
  Query39_RR(c.bNR);
}


void    QueryTime39_Profile(void) {
  c.bNS++;
  c.bInvokeId++;
  QueryTime39(c.bNS, c.bNR, c.bInvokeId);
}



bool    ValidateSframe_Profile(void) {
  return ValidateSframe(c.bNR);
}


bool    ValidateIframe_Profile(void) {
  return ValidateIframe(c.bNS, c.bNR);
};



void    InitProfile39_Profile(void) {
  InitHeader39();
  InitBuffRecord39();
}


void    QueryProfile39_Profile(void) {
  t2time t2 = QueryHeader39(&c);

  c.bNS++;
  c.bInvokeId++;
  QueryProfile39(c.bNS, c.bNR, c.bInvokeId, t2.ti1, t2.ti2);
}