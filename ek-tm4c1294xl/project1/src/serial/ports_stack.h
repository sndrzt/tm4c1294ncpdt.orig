/*------------------------------------------------------------------------------
PORTS_STACK.H


------------------------------------------------------------------------------*/

void    InitPush(uchar  ibPush);
void    InitPushCRC(void);
void    InitPushPtr(void);
void    InitPushUni(void);
void    InitPushPck(void);

void    Push(void  *pbData, uint  wSize);
uchar   PushChar(uchar  bT);
void    PushBool(bool  bo);
uchar   PushInt(uint  w);
uchar   PushLong(ulong  dw);
void    PushFloat(float  fl);
void    PushDouble(double  db);
uchar   PushFloatOrDouble(double  db, bool  fDouble);
uchar   PushTime(time  ti);
void    PushString(char  *psz);
void    PushIntAsString(uint  wT);
void    PushBuffInt(uint  *pwData, uint  wSize);
void    PushBuffLong(ulong  *pdwData, uint  wSize);
void    PushCharHex2Txt(uchar  bT);
void    PushCharDec2Txt(uchar  bT);

uchar   SkipChar(void);
void    Skip(uint  wSize);

void    InitPop(uint  i);

void    Pop(void  *pbData, uint  wSize);
uchar   PopChar(void);
ulong   PopLong(void);
float   PopFloat(void);
