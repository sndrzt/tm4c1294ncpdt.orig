/*------------------------------------------------------------------------------
key_review_wrn_trend.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_int_blocked.h"
#include "key_review_wrn_trend.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  ������������  ",
                        szMessage2[]    = "  % ����������  ",
                        szMessage3[]    = "    ��������    ",
                        szMessage4[]    = " ��������� ���  ",
                        szMessage5[]    = "������ �������� ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szMessage5, szNumberLimits, "" };



void    key_SetReviewWrnTrend(void)
{
	key_SetIntBlocked(&chReviewWrnTrend, pszMessages, REVIEW_WRN_TREND_MIN, REVIEW_WRN_TREND_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
