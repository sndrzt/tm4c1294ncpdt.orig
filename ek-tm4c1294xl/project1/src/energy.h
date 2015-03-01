/*------------------------------------------------------------------------------
ENERGY.H


------------------------------------------------------------------------------*/

uint    GetCanInt(uint  *mpwT, uchar  ibCan);
void    SetCanInt(uint  *mpwT, uchar  ibCan, uint  wT);

ulong   GetCanLong(ulong  *mpdwT, uchar  ibCan);
void    SetCanLong(ulong  *mpdwT, uchar  ibCan, ulong  *pdwT);

real    GetCanReal(real  *mpreT, uchar  ibCan);
void    SetCanReal(real  *mpreT, uchar  ibCan, real  *preT);

ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCan, uchar  ibTariff);
ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCan);

real    GetGrpMntInt2Real(uint  *mpwT, uchar  ibGrp, uchar  bMul);
real    GetCanMntInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMul);

real    GetGrpHouInt2Real(uint  *mpwT, uchar  ibGrp, uchar  bMul);
real    GetCanHouInt2Real(uint  *mpwT, uchar  ibCan, uchar  bMul);

real    GetGrpImp2RealEng(impulse  *mpimT, uchar  ibGrp, uchar  bMask);
real    GetCanImp2RealEng(impulse  *mpimT, uchar  ibCan, uchar  bMask);

void    MakeCntMonCan(void);
real    GetCntCurrImp(uchar  ibCan);

void    MakeImpulse(void);
void    MakeImpulseSpec(void);
