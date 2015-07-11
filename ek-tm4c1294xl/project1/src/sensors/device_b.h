/*------------------------------------------------------------------------------
DEVICE_B.H
              
 
------------------------------------------------------------------------------*/

#ifndef SKIP_B

extern  uchar                   bVersionB1, bVersionB2, bVersionB3;



//bit     ReadAddressB(void);
bool    ReadResultB(void);

void    QueryOpenB(void);

void    QueryVersionB(void);
void    ReadVersionB(void);
bool    TestVersionB710(void);

void    QueryIdB(void);
bool    ReadIdB(void);

void    QueryEnergyB(uchar  bTime);
void    ReadEnergyB(void);

void    QueryControlB(void);
//void    QueryManageB(void);

void    QueryTimeB(void);
time    ReadTimeB(void);

void    QueryTopB(void);
void    ReadTopBOld(void);

void    QueryHeaderB(void);
void    QueryHeaderB_Plus(uchar  bSize);
bool    TestHeaderB(uchar  ibBlock);
bool    ReadHeaderB(uchar  ibBlock, bool  fDelay);

void    ReadCurrentB(void);

#endif
