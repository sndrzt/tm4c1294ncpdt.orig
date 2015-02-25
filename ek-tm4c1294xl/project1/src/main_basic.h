#ifndef __MAIN_BASIC
#define __MAIN_BASIC


typedef uint8_t         uchar;
typedef int8_t          schar;

typedef uint16_t        uint;
typedef int16_t         sint;

typedef uint32_t        ulong;
typedef int32_t         slong;

typedef float           real;


// ��� '����������'
typedef enum
{
  UNDEFINED           = 0x55,
  FALSE               = 0x00,
  TRUE                = 0xFF
} boolean;


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


// ��� '�����/������'
typedef enum
{
  CANALS,
  GROUPS
} item;


// ��� '��������/�������'
typedef enum
{
  POWER,
  ENERGY
} domain;


//typedef char const      message[bDISPLAY+1];


#endif
