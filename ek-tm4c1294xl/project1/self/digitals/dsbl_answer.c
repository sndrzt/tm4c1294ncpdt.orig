/*------------------------------------------------------------------------------
DSBL_ANSWER.C

 '����� �69 �� 11_11_2010'
------------------------------------------------------------------------------*/

#include "../main.h"
#include "../nvram/cache.h"
#include "../nvram/cache2.h"
#include "../serial/ports.h"
#include "dsbl_answer.h"



cache const             chDsblAnswer = {DSBL_ANSWER, &fDsblAnswer, sizeof(bool)};



void    InitDsblAnswer(void)
{
  LoadCacheBool(&chDsblAnswer, false);
}


void    ResetDsblAnswer(void)
{
  SaveCacheBool(&chDsblAnswer, false);
}



void    EnableAnswer(void)
{
//  boAnswerFlag = true;
  cdwAnswerEnabled++; tiAnswerEnabled = tiCurr;
}


void    DisableAnswer(void)
{
//  boAnswerFlag = false;
  cdwAnswerDisabled++; tiAnswerDisabled = tiCurr;
}


bool    IsAnswerDisabled(void)
{
  return 0; // boAnswerFlag != true;
}



void    OutEnableAnswer(void)
{
  EnableAnswer();
  LongResult(bRES_OK);
}


void    OutDsblAnswer(void)
{
  InitPushCRC();
  PushBool(fDsblAnswer);
  PushBool(boAnswerFlag);
  PushLong(cdwAnswerDisabled);
  PushTime(tiAnswerDisabled);
  PushLong(cdwAnswerEnabled);
  PushTime(tiAnswerEnabled);
  Output(1+1+4+6+4+6);
}
