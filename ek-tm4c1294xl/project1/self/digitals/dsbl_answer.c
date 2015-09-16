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
	fDsblAnswer = false;
  SaveCache(&chDsblAnswer);
}



void    EnableAnswer(void)
{
//  boAnswerFlag = true;
  cdwAnswerEnable++; tiAnswerEnable = tiCurr;
}


void    DisableAnswer(void)
{
//  boAnswerFlag = false;
  cdwAnswerDisable++; tiAnswerDisable = tiCurr;
}


bool   AnswerDisabled(void)
{
  return 0; // boAnswerFlag != true;
}



void    OutDsblAnswer(void)
{
  InitPushCRC();
  PushBool(fDsblAnswer);
  PushBool(boAnswerFlag);
  PushLong(cdwAnswerDisable);
  PushTime(tiAnswerDisable);
  PushLong(cdwAnswerEnabled);
  PushTime(tiAnswerEnable);
  Output(1+1+4+6+4+6);
}
