/*------------------------------------------------------------------------------
profile36!H


------------------------------------------------------------------------------*/

// ������ ����� ��������� �������, ������
#define bMINORCORRECT_36 3



extern  uchar                   ibLine36, bMaxLine36;



bool    HasPassword36(void);
void    QueryPassword36(void);

void    QueryCorrect36(void);
void    QueryControl36(void);

void    QueryTimeSpec36(void);
void    QueryDateSpec36(void);

void    InitHeader36(void);
void    QueryHeader36(void);
void    ReadHeader36(void);
void    ReadHeader36_SkipLine(uchar  ibLine);
void    MakeData36(uchar  ibHou);
bool    ReadData36(void);
