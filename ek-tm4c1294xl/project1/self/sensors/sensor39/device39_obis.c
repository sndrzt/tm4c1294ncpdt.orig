/*------------------------------------------------------------------------------
device39_obis.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "device39_obis.h"



const obis_t        obisId      = {0, 0, 96, 1, 4, 255}; // Ch. 0; Device ID; #5

const obis_t        obisTime    = {0, 0, 1, 0, 0, 255}; // Ch. 0; Clock object; #1

const obis_t        obisEngAbs  = {1, 0, 15, 8, 0, 255}; // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 0 (0 is total); Unspecified number of most recent billing periods

const obis_t        obisEngAbsTariff[4] = {
  {1, 0, 15, 8, 1, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 1 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 15, 8, 2, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 2 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 15, 8, 3, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 3 (0 is total); Unspecified number of most recent billing periods
  {1, 0, 15, 8, 4, 255}, // Ch. 0; Sum Li Active power (abs(QI+QIV)+abs(QII+QIII)); Time integral 1; Rate 4 (0 is total); Unspecified number of most recent billing periods
};

const obis_t        obisBillingPeriod = {0, 0, 98, 1, 0, 255}; // Ch. 0; Data of billing period; Scheme 1; #1; Unspecified number of most recent billing periods

const obis_t        obisProfile  = {1, 0, 99, 1, 0, 255}; // Ch. 0; Load profile with recording period 1; #1

// Blue Book: 7.5.1 Value group C codes � Electricity
const obis_t        obisU1      = {1, 0, 32, 7, 0, 255},
                    obisU2      = {1, 0, 52, 7, 0, 255},
                    obisU3      = {1, 0, 72, 7, 0, 255},

                    obisI1      = {1, 0, 31, 7, 0, 255},
                    obisI2      = {1, 0, 51, 7, 0, 255},
                    obisI3      = {1, 0, 71, 7, 0, 255},

                    obisPplus   = {1, 0,  1, 7, 0, 255},
                    obisPminus  = {1, 0,  2, 7, 0, 255},

                    obisQplus   = {1, 0,  3, 7, 0, 255},
                    obisQminus  = {1, 0,  4, 7, 0, 255};
