/*------------------------------------------------------------------------------
MAIN_EXTENDED,H


------------------------------------------------------------------------------*/

#ifndef __MAIN_EXTENDED
#define __MAIN_EXTENDED


// ������ ������ ���������
typedef enum
{
  ST_NONE               = 0,
  ST_OK                 = 1,
  ST_NOTSUPPORTED       = 2,
  ST_NOTPRESENTED       = 3,
  ST_BADDIGITAL         = 0x80, // ������� �� ��������
  ST_BADFLASH           = 0x81, // ���������� ������ ���������
  ST_MODEM_LINK         = 0x82, // �������� �����, ���������� �������� ������
  ST_DISABLED           = 0x83, // ������� ��������
  ST_BAD_VERSION        = 0x84, // ������������ ������ ��������
  ST_BAD_CRC            = 0x85  // ������ ����������� ����� ��������
} status;


// �������� �������� �� �������
typedef struct
{
  double        mpdbValuesT[bTARIFFS];
} value5a;


// �������� �������� �� ������� (������ �����)
typedef struct
{
  value5a       stValue;
  time          tiUpdate;
  bool          boSuccess;
  uint          cwSuccess,cwError;
} value5b;


//
typedef struct
{
  status        bStatus;
  double        dbValue;
  time          tiUpdate;
} value6;


//
typedef struct
{
  status        bStatus;
  double        mpdbValuesT[bTARIFFS];
  time          tiUpdate;
} value4t;


// �����
typedef struct
{
  uchar         bSecond;
  uchar         bMinute;
  uchar         bHour;
} stamp;


// �������� �������� �� ������ �������
typedef struct
{
  double        dbValue;
  stamp         stValue;
} diagram;


#endif
