/*------------------------------------------------------------------------------
time34.h


------------------------------------------------------------------------------*/

// ����� ��������� �������, ������
#define CORRECT_LIMIT_34    10



void    SetTimeCurr34(time  tm);
time    GetTimeCurr34(void);

void    QueryTime34(void);
time    ReadTime34(void);

void    SetCorrectSecond34(int32_t dw);
void    QueryCorrect34(void);
bool    ReadCorrect34(void);
