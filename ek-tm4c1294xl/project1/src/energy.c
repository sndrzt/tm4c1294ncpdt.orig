/*------------------------------------------------------------------------------
ENERGY.C


------------------------------------------------------------------------------*/

#include        "main.h"
#include        "engine.h"



// ��������� �� ���������� ������� unsigned int
uint    *PGetCanInt(uint  *mpwT, uchar  ibCanal)
{
  return( &mpwT[ibCanal] );
}


// �������� � ��������� ������ unsigned int
void    SetCanInt(uint  *mpwT, uchar  ibCanal, uint  wT)
{
  mpwT[ibCanal] = wT;
}



// ��������� �� ���������� ������� unsigned int
ulong   *PGetCanLong(ulong  *mpdwT, uchar  ibCanal)
{
  return( &mpdwT[ibCanal] );
}


// �������� � ��������� ������ unsigned int �� dwBuffC
void    SetCanLong(ulong  *mpdwT, uchar  ibCanal)
{
  mpdwT[ibCanal] = dwBuffC;
}



// ��������� �� ���������� ������� real
real    *PGetCanReal(real  *mpreT, uchar  ibCanal)
{
  return( &mpreT[ibCanal] );
}


// �������� � ��������� ������ real �� reBuffA
void    SetCanReal(real  *mpreT, uchar  ibCanal)
{
  mpreT[ibCanal] = reBuffA;
}



// ��������� �� ���������� ������� impulse (�� ��������� ������)
ulong   *PGetCanImp(impulse  *mpimT, uchar  ibCanal, uchar  ibTariff)
{
  return( &mpimT[ibCanal].mpdwImp[ibTariff] );
}


// ��������� �� ���������� ������� impulse (�� ���� �������)
ulong   *PGetCanImpAll(impulse  *mpimT, uchar  ibCanal)
{
uchar   i;

  dwBuffC = 0;
  for (i=0; i<bTARIFFS; i++)
    dwBuffC += *PGetCanImp(mpimT,ibCanal,i);

  return( &dwBuffC );
}
