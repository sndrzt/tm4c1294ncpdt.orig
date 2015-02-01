#ifndef __MAIN_BASIC
#define __MAIN_BASIC


typedef uint8_t         uchar;
typedef int8_t          schar;

typedef uint16_t        uint;
typedef int16_t         sint;

typedef uint32_t        ulong;
typedef int32_t         slong;

typedef double          real;


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


typedef enum
{
  boFalse               = 0x00,
  boTrue                = 0xFF
} boolean;


//
typedef struct
{
  uint          wPage;
  void          *pbBuff;
  uint          wSize;
} file;


typedef char const      message[bDISPLAY];


#endif
