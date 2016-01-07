/*------------------------------------------------------------------------------
DEVICE_W.H


------------------------------------------------------------------------------*/

#define MAX_LINE_W      4



extern  uchar                   ibLineW;

extern  time                    tiProfileW;



double  PopDoubleW(void);

void    QueryCloseW(void);
void    QueryOpenW(void);

void    QueryTypeW(void);
void    ReadTypeW(void);

void    QueryTimeW_Profile(void);
void    QueryTimeW(void);
time    ReadTimeW(void);

void    QueryControlW(time  ti);
void    QueryGetCorrectW(void);
uint    ReadGetCorrectW(void);
void    QuerySetCorrectW(sint  wSecond);

void    QueryOptionW(void);
void    QueryPasswordW(void);

void    QueryKtransW(uchar  ibKtrans);

void    QueryEngAbsW_Current(uchar  ibLine);
void    QueryEngAbsW(uchar  ibLine);
void    QueryEngMonW(uchar  ibLine, uchar  bTime);
void    QueryEngDayW(uchar  ibLine, uchar  bTime);

void    ReadEngW(uchar  ibLine);

//void    InitHeaderV(void);
//void    QueryHeaderV(void);
//bool    ReadHeaderV(void);

void    ReadCurrentW(void);
