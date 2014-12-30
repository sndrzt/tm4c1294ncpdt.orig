#ifndef __MAIN
#define __MAIN


#include        <stdint.h>
#include        <stdbool.h>
#include        "system.h"
#include        "main_keyboard.h"
#include        "main_serial.h"


typedef unsigned char   uchar;
typedef signed char     schar;

typedef unsigned int    uint;
typedef signed int      sint;

typedef unsigned long   ulong;
typedef signed long     slong;


// ��� '������ ���������'
typedef uchar           message[bDISPLAY+1];


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


typedef enum 
{ 
  ANS_BEGIN             =  0,           // ��������� ���������
  ANS_TIMEOUT           =  1,           // ��������� ��������
  ANS_ANSWER            =  2            // �������� �������
} answer;


// ��� '������� �������� �� �������� �����'
typedef enum
{
  DEC_NONE              = 0,
  DEC_AUTO              = 1,
  DEC_CUSTOM            = 2
} decret;


// ��� '��������� ������ �������'
typedef enum
{
  GLB_PROGRAM           = 0,
  GLB_WORK              = 1,
  GLB_REPROGRAM         = 2
} global;


// ��� '��������� �����'
typedef struct
{
  uchar         ibSpeed;                // ������ ��������
  uchar         ibParity;               // ������ �������� ��������
  stream        enStream;               // ����� ������ �����
} port;


#endif






