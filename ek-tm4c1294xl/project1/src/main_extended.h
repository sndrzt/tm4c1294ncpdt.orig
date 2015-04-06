/*------------------------------------------------------------------------------
MAIN_EXTENDED.H


------------------------------------------------------------------------------*/

#ifndef __MAIN_EXTENDED
#define __MAIN_EXTENDED


// ��� '������ ���� 4'
typedef enum
{
  ST4_NONE              = 0,
  ST4_OK                = 1,
  ST4_NOTSUPPORTED      = 2,
  ST4_NOTPRESENTED      = 3,
  ST4_BADDIGITAL        = 0x80,
  ST4_BADFLASH          = 0x81,
  ST4_BADPORT           = 0x82,
  ST4_BADENABLING       = 0x83
} status4;


// ��� '������ ���� 4'
typedef struct
{
  status4       bSelf;
  uint          cwOK,cwError;
  real          reSelf;
  time          tiSelf;
} value4;


// ��� '������ ���� 50'
typedef struct
{
  real          mpreSelf[bTARIFFS];
} value50;


// ��� '������ ���� 51'
typedef struct
{
  value50       vaValue50;
  time          tiSelf;
  boolean       boSelf;
  uint          cwOK,cwError;
} value51;


// ��� '������ ���� 6'
typedef struct
{
  status4       bSelf;
  real          reSelf;
  time          tiSelf;
} value6;


// ��� '������ ���� 6 �� �������'
typedef struct
{
  status4       bSelf;
  real          mpreSelf[bTARIFFS];
  time          tiSelf;
} value6t;


// ��� '������ ���� 7'
typedef struct
{
  uchar         bSelf;
  uint          mpwSelf[4];
  time          tiSelf;
} value7;


// ��� '���������'
typedef struct
{
  real          reSelf;
  time2         tmSelf;
} diagram;


// ���������
#define bVALUE7_BLOCKS      3
#define bVALUE7_USED_SIZE   (bVALUE7_BLOCKS*6) 
#define bVALUE7_REAL_SIZE   ((bVALUE7_BLOCKS+1)*6) 


typedef enum
{
  STA_NONE              = 0,
  STA_DATAON            = 1,
  STA_DATAOFF           = 2,
  STA_USEDAY            = 3,
  STA_USEMON            = 4,
  STA_READY             = 5
} status;


#endif
