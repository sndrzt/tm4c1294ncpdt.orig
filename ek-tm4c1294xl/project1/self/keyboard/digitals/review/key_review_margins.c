/*------------------------------------------------------------------------------
key_review_margins.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char_blocked.h"
#include "key_review_margins.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "  ������������  ",
                        szMessage2[]    = "   ����������   ",
                        szMessage3[]    = "  �������� ���  ",
                        szMessage4[]    = "������ �������� ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewRepeatTotal(void)
{
  key_SetCharBlocked(&chReviewRepeatTotal, pszMessages, REVIEW_MARGINS_MIN, REVIEW_MARGINS_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
