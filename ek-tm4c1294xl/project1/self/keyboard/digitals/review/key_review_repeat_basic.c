/*------------------------------------------------------------------------------
key_review_repeat_basic.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char_blocked.h"
#include "key_review_repeat_basic.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "    �������     ",
                        szMessage2[]    = "   ����������   ",
                        szMessage3[]    = "  �������� ���  ",
                        szMessage4[]    = "������ �������� ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szMessage4, szNumberLimits, "" };



void    key_SetReviewRepeatBasic(void)
{
  key_SetCharBlocked(&chReviewRepeatBasic, pszMessages, REVIEW_REPEAT_BASIC_MIN, REVIEW_REPEAT_BASIC_MAX, fReviewFlag, wSET_REVIEW_FLAG);
}
