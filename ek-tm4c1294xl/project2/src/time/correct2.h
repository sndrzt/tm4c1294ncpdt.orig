/*------------------------------------------------------------------------------
CORRECT2.H


------------------------------------------------------------------------------*/

extern  file const              flCorrect2Flag;



void    InitCorrect2(void);
void    ResetCorrect2(void);

bool    Correct2Disabled(void);
bool    Correct2Allowed(void);
void    Correct2(event  ev);
void    OutCorrect21(void);
