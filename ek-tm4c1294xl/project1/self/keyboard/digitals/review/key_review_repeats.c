/*------------------------------------------------------------------------------
key_review_repeats.c


------------------------------------------------------------------------------*/

#include "../../../console.h"
#include "../../../digitals/review/review.h"
#include "../../common/key_char.h"
#include "key_review_repeats.h"



//                                         0123456789ABCDEF
static char const       szMessage1[]    = "   ����������   ",
                        szMessage2[]    = "  �������� ���  ",
                        szMessage3[]    = "������ �������� ";

static char const       *pszMessages[]  = { szMessage1, szMessage2, szMessage3, szNumberLimits, "" };



void    key_SetReviewRepeats(void)
{
  key_SetChar(&chReviewRepeats, pszMessages, REVIEW_REPEATS_MIN, REVIEW_REPEATS_MAX);
}
