/*------------------------------------------------------------------------------
PHONES2!C


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../memory/mem_settings.h"
#include "../../memory/mem_digitals.h"
#include "../../memory/mem_tariffs.h"
#include "../../memory/mem_realtime.h"
#include "../../memory/mem_phones2.h"
#include "../../display/display.h"
#include "../../keyboard/keyboard.h"
#include "../../time/rtc.h"
#include "../../time/timedate.h"
#include "../../realtime/realtime.h"
#include "../../energy4.h"
#include "../../serial/ports.h"
#include "../../serial/ports_push.h"
#include "../../serial/ports_devices.h"
#include "../../serial/ports_modems.h"
#include "../../serial/modems.h"
#include "../../flash/records.h"
#include "../../nvram/cache.h"
#include "../../nvram/cache2.h"
#include "phones2_modem.h"
#include "phones2.h"



// �������������� ��������
float                  reCurrPhones2;

// ������
uchar                  mpbAnswer1Phones2[PHONE2_ANSWER], mpbAnswer2Phones2[PHONE2_ANSWER];

// �����
stamp2                 mpstPhones2[PHONE2_CODES];

// �����
uchar                  mpbBuffPhones2[PHONE2_RECORD];

// ��������
ulong                  cdwPhones20, cdwPhones21, cdwPhones22, cdwPhones23, cdwPhones24, cdwPhones25;

// ������������� �����
char                   mpbInBuffSave2[100];



cache const             chPortPhones2 = {PORT_PHONES2, &bPortPhones2, sizeof(uchar)};
cache const             chPhones2 = {PHONES2, &mpphPhones2, sizeof(mpphPhones2)};
cache const             chMaxxPhones2 = {PORT_PHONES2, &reMaxxPhones2, sizeof(float)};


//                                         0123456789ABCDEF
static char const       szPhonesRun2[]    = "���-��������    ",
                        szPhonesMode21[]  = " ��������� 1... ",
                        szPhonesMode22[]  = " ��������� 2... ",
                        szPhonesMode23[]  = " ��������� 3... ";



void    ResetPhones2(void) {
uchar   i;

  bPortPhones2 = 0;
  reCurrPhones2 = 0;
  reMaxxPhones2 = 1000;

  uchar c;
  for (c=0; c<bPHONES2; c++)
  {
    mpphPhones2[c].szLine[0] = '0';
  }

  memset(&mpbAnswer1Phones2, 0, sizeof(mpbAnswer1Phones2));
  memset(&mpbAnswer2Phones2, 0, sizeof(mpbAnswer2Phones2));

  for (i=0; i<PHONE2_CODES; i++) {
    mpstPhones2[i].cwSelf = 0;
    mpstPhones2[i].tiSelf = tiZero;
  }

  memset(&mpbBuffPhones2, 0, sizeof(mpbBuffPhones2));

  cdwPhones20 = 0;
  cdwPhones21 = 0;
  cdwPhones22 = 0;
  cdwPhones23 = 0;
  cdwPhones24 = 0;
  cdwPhones25 = 0;
}



bool    UsePhones2(void) {
  return ((bPortPhones2 > 0) && (bPortPhones2 <= bPORTS));
}






phones2 SafeWritePhones2(uchar  ibPrt, bool  fDebug) {
stream  s;
uint    w;
phones2 f;

  if (mppoPorts[ibPrt].enStream == STR_MASTERDIRECT) {
    w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2(fDebug);
    mpwMinorInDelay[ibPrt] = w;
  }
  else {
    s = mppoPorts[ibPrt].enStream;
    mppoPorts[ibPrt].enStream = STR_MASTERDIRECT;
    w = mpwMinorInDelay[ibPrt];
    mpwMinorInDelay[ibPrt] = 5*wFREQUENCY_T0;
    f = WritePhones2(fDebug);
    mppoPorts[ibPrt].enStream = s;
    mpwMinorInDelay[ibPrt] = w;
  }

  mpbBuffPhones2[PHONE2_RECORD-1] = f;

  if (f < PHONE2_CODES-1) {
    mpstPhones2[f].cwSelf++;
    mpstPhones2[f].tiSelf = *GetCurrTimeDate();
  }
  else {
    mpstPhones2[PHONE2_CODES-1].cwSelf++;
    mpstPhones2[PHONE2_CODES-1].tiSelf = *GetCurrTimeDate();
  }

  return f;
}


void    RunPhones2(bool  fDebug) {
  if (UsePhones2()) {
    Clear();

    ibPort = bPortPhones2-1;
    diCurr.ibPort = bPortPhones2-1;

    if (SafeWritePhones2(bPortPhones2-1, fDebug) == PH2_OK) {
      if (fDebug == false) cdwPhones25++;
    }
    else
      Error();

    mpSerial[ibPort] = SER_BEGIN;

    Work();
  }
}
