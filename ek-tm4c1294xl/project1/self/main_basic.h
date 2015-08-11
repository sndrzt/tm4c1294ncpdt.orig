/*------------------------------------------------------------------------------
MAIN_BASIC.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_BASIC
#define __MAIN_BASIC


typedef uint8_t         uchar;
typedef int8_t          schar;

typedef uint16_t        uint;
typedef int16_t         sint;

typedef uint32_t        ulong;
typedef int32_t         slong;

typedef float           real;


// ��� '����� � ����'
typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
  uchar         bDay;
  uchar         bMonth;
  uchar         bYear;
} time;


// ��� '��������������� 32 ����'
typedef union
{
  uchar         mpbBuff[4];
  ulong         dwBuff;
  float         flBuff;
} combo32;


// ��� '��������������� 64 ����'
typedef union
{
  uchar         mpbBuff[8];
  uint64_t      qwBuff;
  double        dbBuff;
} combo64;


// ��� '��������/�������'
typedef enum
{
  POWER,
  ENERGY
} domain;


typedef char const      message[bDISPLAY+1];


//
typedef struct
{
  uint          w1;
  uint          w2;
} tuple2uint;


//
typedef struct
{
  time          ti1;
  time          ti2;
} tuple2time;


#endif
