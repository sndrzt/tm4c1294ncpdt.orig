/*------------------------------------------------------------------------------
review_core.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../display/display.h"
#include "../../time/delay.h"
#include "../../serial/monitor.h"
#include "../../devices/devices.h"
#include "review.h"
#include "review_buff.h"
#include "review_core.h"
#include "review_can.h"
#include "review_warning.h"



static uchar            cbRepeatCurr, cbRepeatTotal;

uchar                   bReviewRepeatMax;
bool                    fReviewIdRepeat;



// ���������� ����� ���������� ����� ��������
void StartReview(void)
{
  StartReviewBuff();
  StartReviewCan(ibDig);
}

// ���������� ����� ���������� ����� ���������� �1 ��� �6 ����� ��������
void RestartReview(void)
{
  RestartReviewBuff();

  cbRepeatCurr = 0;
  cbRepeatTotal = 0;

  bReviewRepeatMax = bReviewRepeatBasic;
  fReviewIdRepeat = false;
}



static bool UseReview(void)
{
  return (fReviewFlag == true);
}

static void Show(void)
{
  sprintf(szHi+10, "%2u", cbRepeatTotal);
}



static review_code ReadReview2(uchar  ibMin, uchar  ibMax, uchar  bSize)
{
  if (!UseReview()) {
    return REVIEW_SUCCESS;
  } else if (cbRepeatTotal == 0) {
    cbRepeatTotal++;
    Show();

    cbRepeatCurr++;
    SaveReviewBuff(ibMin,ibMax);

    WarningReviewBuff(bSize);
    return REVIEW_REPEAT;
  } else {
    cbRepeatTotal++;
    Show();

    if (cbRepeatTotal >= bReviewRepeatTotal) {
      Clear(); strcpy(szLo+0, "������ ��������"); DelayMsg(); Clear();
      return REVIEW_ERROR;
    } else {
      if (TestReviewBuff(ibMin,ibMax)) {
        if (++cbRepeatCurr >= bReviewRepeatMax) {
          NextReviewBuff();
          return REVIEW_SUCCESS;
        } else {
          return REVIEW_REPEAT;
        }
      } else {
        cbRepeatCurr = 0;
        SaveReviewBuff(ibMin,ibMax);

        if (!WarningReviewBuff(bSize)) {
          Clear(); strcpy(szLo+3, "�������� !"); DelayInf(); Clear();
        }
        return REVIEW_REPEAT;
      }
    }
  }
}

static review_code ReadReview(uchar  ibMin, uchar  ibMax, uchar  bSize)
{
  review_code rc = ReadReview2(ibMin, ibMax, bSize);

  if ((rc == REVIEW_REPEAT) && (fReviewIdRepeat == true)) {
    rc = REVIEW_ID_REPEAT;
    MonitorString("\n REVIEW_ID_REPEAT");
  }

  if (rc == REVIEW_REPEAT) {
    MonitorString("\n REVIEW_REPEAT");
  }

  mcwReviewEvents[rc]++;

  return rc;
}



review_code ReadReviewC1(void)
{
  return ReadReview(0, 13, 1);
}

review_code ReadReviewC1_Shutdown(void)
{
  return ReadReview(0, 5, 0);
}

review_code ReadReviewC6(void)
{
  return ReadReview(0, 53, 6);
}
