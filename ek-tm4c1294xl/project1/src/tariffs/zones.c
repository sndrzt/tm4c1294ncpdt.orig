/*------------------------------------------------------------------------------
ZONES.C

 ������������ ���������� ��������� ��������� ���������
------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../memory/mem_tariffs.h"
#include        "../keyboard.h"
#include        "../display/display.h"



//                                       0123456789ABCDEF  
static char const       szNoZones[]   = " ���� �� ������ ";


breaks const            brZero = { 0, 0, 0 };



// ������ ���������� ������� � �������� ������� zoAlt
uchar   GetZoneAltSize(void)
{
  return( zoAlt.bSize );
}


// ���������� ���������� ������� � �������� ������� zoAlt
void    SetZoneAltSize(uchar  bSize)
{
  zoAlt.bSize = bSize;
}



// ������ ����� brAlt �� ��������� ������� zoAlt
void    GetZoneAltBreak(uchar  ibBreak)
{
  brAlt = zoAlt.mpbrBreaks[ibBreak];
}


// ���������� ����� brAlt � �������� ������ zoAlt
void    SetZoneAltBreak(uchar  ibBreak)
{
  zoAlt.mpbrBreaks[ibBreak] = brAlt;
}



// ������ ���������� ������� � �������� ������� zoKey
uchar   GetZoneKeySize(void)
{
  return( zoKey.bSize );
}


// ���������� ���������� ������� � �������� ������� zoKey
void    SetZoneKeySize(uchar  bSize)
{
  zoKey.bSize = bSize;
}



// ������ ����� brKey �� ��������� ������� zoKey
void    GetZoneKeyBreak(uchar  ibBreak)
{
  brKey = zoKey.mpbrBreaks[ibBreak];
}


// ���������� ����� brKey � �������� ������ zoKey
void    SetZoneKeyBreak(uchar  ibBreak)
{
  zoKey.mpbrBreaks[ibBreak] = brKey;
}



// ��������� ������ �������� ��� ������ ��������� ������� zoAlt
uchar   GetBreakAltIndex(uchar  ibBreak)
{
  GetZoneAltBreak(ibBreak);
  return( brAlt.bHour*2 + brAlt.bMinute/30 );
}


// ��������� ������ �������� ��� ������ ��������� ������� zoKey
uchar   GetBreakKeyIndex(uchar  ibBreak)
{
  GetZoneKeyBreak(ibBreak);
  return( brKey.bHour*2 + brKey.bMinute/30 );
}



// ���������� ��������� �� ��������� ��� ���������� zoAlt,zoKey
void    ResetZones(void)
{
static uchar const  mpbZone[3*bBREAKS] =
{  6,  0,  0,
   8,  0,  1,
  10,  0,  2,
  18,  0,  1,
  20,  0,  3,
  21, 30,  1 };

  ibY = 0;
  for (ibX=0; ibX<bBREAKS; ibX++)
  {    
    brAlt.bHour    = mpbZone[ibY++];
    brAlt.bMinute  = mpbZone[ibY++];
    brAlt.ibTariff = mpbZone[ibY++];

    SetZoneAltBreak(ibX);
  }

  SetZoneAltSize(bBREAKS);

  memcpy(&zoKey, &zoAlt, sizeof(zones));
}



// ���������� ����� ��������� ������� zoAlt
void    ShowZoneAltBreak(uchar  ibBreak)
{
  if (GetZoneAltSize() > 0)
  {
    GetZoneAltBreak(ibBreak);

    sprintf(szLo,"  %2u.%02u - %1u  %1u/%1u",
                 brAlt.bHour, 
                 brAlt.bMinute,
                 brAlt.ibTariff+1,
                 ibBreak+1, 
                 GetZoneAltSize());
  }
  else ShowLo(szNoZones);
}


// ���������� ����� ��������� ������� zoKey
void    ShowZoneKeyBreak(uchar  ibBreak)
{
  if (GetZoneKeySize() > 0)
  {
    GetZoneKeyBreak(ibBreak);

    sprintf(szLo,"  %2u.%02u - %1u  %1u/%1u",
                 brKey.bHour, 
                 brKey.bMinute,
                 brKey.ibTariff+1,
                 ibBreak+1, 
                 GetZoneKeySize());
  }
  else ShowLo(szNoZones);
}



#ifndef MODBUS

// ��������� ������������ ��������� ��������� �������
bool    TrueZone(void)
{
  return true;
}

#endif



zones   *PGetDefaultZonePow(void) {
static uchar const  mpbZone[3*bBREAKS] = {
 	 6,  0,  0,
   8,  0,  1,
  11,  0,  2,
  17,  0,  1,
  20,  0,  3,
  23,  0,  1
};

static zones  zo;
breaks  br;
uchar  i, j;

  i = 0;
  for (j=0; j<bBREAKS; j++)
  {    
  	br.bHour    = mpbZone[i++];
  	br.bMinute  = mpbZone[i++];
  	br.ibTariff = mpbZone[i++];

  	zo.mpbrBreaks[j] = br;
  }

  zo.bSize = 6;

  return &zo;
}


zones   *PGetDefaultZoneEng(void) {
static uchar const  mpbZone[3*bBREAKS] = {
   6,  0,  0,
   8,  0,  1,
  11,  0,  2,
  23,  0,  1,
  24,  0,  0,
   0,  0,  0
};

static zones  zo;
breaks  br;
uchar  i, j;

  i = 0;
  for (j=0; j<bBREAKS; j++)
  {    
  	br.bHour    = mpbZone[i++];
  	br.bMinute  = mpbZone[i++];
  	br.ibTariff = mpbZone[i++];

  	zo.mpbrBreaks[j] = br;
  }

  zo.bSize = 5;

  return &zo;
}
