/*------------------------------------------------------------------------------
review.h


------------------------------------------------------------------------------*/

#ifndef __REVIEW
#define __REVIEW

#define REVIEW_REPEATS_MIN    2
#define REVIEW_REPEATS_MAX    5
#define REVIEW_REPEATS_DEF    2

#define REVIEW_BORDERS_MIN    2
#define REVIEW_BORDERS_MAX    5
#define REVIEW_BORDERS_DEF    4

#define REVIEW_MARGINS_MIN    10
#define REVIEW_MARGINS_MAX    50
#define REVIEW_MARGINS_DEF    20

#define REVIEW_WRN_TREND_MIN  100
#define REVIEW_WRN_TREND_MAX  50000
#define REVIEW_WRN_TREND_DEF  200

#define REVIEW_WRN_TOP_MIN    1
#define REVIEW_WRN_TOP_MAX    0xFFFF
#define REVIEW_WRN_TOP_DEF    0x7FFF



#define REVIEW_EVENTS_SIZE    16



extern bool                    fReviewFlag;
extern bool                    mfReviewCan[bCANALS];
extern bool                    fReviewReadId;
extern uchar                   bReviewRepeats;
extern uchar                   bReviewBorders;
extern uchar                   bReviewMargins;
extern uint                    wReviewWrnTrend;
extern uint                    wReviewWrnTop;

extern uint                    mcwReviewEvents[REVIEW_EVENTS_SIZE];
extern uint                    mcwReviewWarnings[REVIEW_EVENTS_SIZE];

extern cache const             chReviewFlag;
extern cache const             chReviewCan;
extern cache const             chReviewReadId;
extern cache const             chReviewRepeats;
extern cache const             chReviewBorders;
extern cache const             chReviewMargins;
extern cache const             chReviewWrnTrend;
extern cache const             chReviewWrnTop;



void InitReview(void);
void ResetReview(bool  fFull);

#endif
