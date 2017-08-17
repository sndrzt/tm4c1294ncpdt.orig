/*------------------------------------------------------------------------------
skip_failure.h


------------------------------------------------------------------------------*/

void    InitSkipFailure(void);
void    ResetSkipFailure(void);

void   SkipFailure_Start(void);
void   SkipFailure_Success(void);
void   SkipFailure_Failure(void);
bool   SkipFailure_IsFailure(void);
