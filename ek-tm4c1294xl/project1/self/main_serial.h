/*------------------------------------------------------------------------------
MAIN_SERIAL.H


------------------------------------------------------------------------------*/

#include "main_basic.h"



//
typedef enum
{
  AT_BEGIN              =  0,
  AT_TIMEOUT            =  1,
  AT_ANSWER             =  2
} send_at;


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
  uchar         ibBaud;                // ������ ��������
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

  SER_INPUT_SLAVE_UNI      = 62,           // ����
  SER_POSTINPUT_SLAVE_UNI  = 63,           // ���� ��������
} serial;


#define SERIAL_MODEM    0xFF00
#define SERIAL_LOCAL    0xFF01
