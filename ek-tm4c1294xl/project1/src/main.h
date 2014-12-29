#ifndef __MAIN
#define __MAIN


#include        <stdint.h>
#include        <stdbool.h>
#include        "system.h"
#include        "main_keyboard.h"


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


// ��� '����� ������ �����'
typedef enum 
{ 
  STR_SLAVEESC          = 0,
  STR_SLAVECRC          = 1,
  STR_MASTERDIRECT      = 2,
  STR_MASTERMODEM       = 3,
  STR_SLAVEUNI          = 4
} stream;


// ��� '��������� �����'
typedef struct
{
  uchar         ibSpeed;                // ������ ��������
  uchar         ibParity;               // ������ �������� ��������
  stream        enStream;               // ����� ������ �����
} port;



// ��� '��������� �����'
typedef enum 
{ 
  SER_BEGIN             = 0,            // ��������� ���������

  SER_OUTPUT_SLAVE      = 1,            // ��������
  SER_INPUT_SLAVE       = 2,            // ����
  SER_POSTINPUT_SLAVE   = 3,            // ���� ��������

  SER_HEADER            = 4,            // �������� ���������
  SER_POINTER           = 5,            // �������� ������ �� ���������
  SER_CRCLO             = 6,            // �������� �������� ����� CRC
  SER_CRCHI             = 7,            // �������� �������� ����� CRC
  SER_CLOSE             = 8,            // �������� ���������

  SER_ESC               = 9,            // ���� Esc
  SER_CTRL_Z            = 10,           // ���� Ctrl Z
  SER_CHAR              = 11,           // ���� �������

  SER_OUTPUT_MASTER     = 20,           // ��������
  SER_INPUT_MASTER      = 21,           // ����
  SER_POSTINPUT_MASTER  = 22,           // ���� ��������

  SER_ANSWER_MODEM      = 23,           // ���� �� ������
  SER_POSTANSWER_MODEM  = 24,           // ���� �� ������ ��������

  SER_GOODCHECK         = 30,           // ����������� ����� ���������
  SER_BADCHECK          = 31,           // ������: ������ ����������� �����
  SER_BADLINK           = 32,           // ������: ��� ������
  SER_OVERFLOW          = 33,           // ������: ������������ �������� ������

  SER_PAUSE             = 40,           // ����� ����������

  SER_PACKET_HEADER     = 50,
  SER_PACKET_BODY       = 51,

  SER_LOCAL             = 60,
  SER_BULK              = 61,

  SER_INPUT_SLAVE2      = 62,           // ����
  SER_POSTINPUT_SLAVE2  = 63,           // ���� ��������
} serial;        


#define SERIAL_MODEM    0xFF00
#define SERIAL_LOCAL    0xFF01


#endif






