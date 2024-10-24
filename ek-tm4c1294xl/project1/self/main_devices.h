/*------------------------------------------------------------------------------
MAIN_DEVICES!H


------------------------------------------------------------------------------*/

#include "main_defines.h"



#ifndef __MAIN_DEVICES
#define __MAIN_DEVICES


// ��� '��������� ������ ��������� ��������'
typedef enum
{
  DEV_BEGIN             =  0,

  DEV_MODEM_MANUAL      =  0x09,

  DEV_MODEM_START       =  0x10,
  DEV_MODEM_POSTSTART   =  0x11,
  DEV_MODEM_BAUD        =  0x12,
  DEV_MODEM_POSTBAUD    =  0x13,
  DEV_MODEM_COMMON      =  0x14,
  DEV_MODEM_POSTCOMMON  =  0x15,
  DEV_MODEM_ONLINE      =  0x16,
  DEV_MODEM_POSTONLINE  =  0x17,
  DEV_MODEM_NORMAL      =  0x18,
  DEV_MODEM_POSTNORMAL  =  0x19,
  DEV_MODEM_CUSTOM      =  0x1A,
  DEV_MODEM_POSTCUSTOM  =  0x1B,
  DEV_MODEM_CONNECT     =  0x1C,
  DEV_MODEM_POSTCONNECT =  0x1D,

  DEV_MODEM_STOP        =  0x20,
  DEV_MODEM_POSTSTOP    =  0x21,
  DEV_MODEM_ESCAPE      =  0x22,
  DEV_MODEM_POSTESCAPE  =  0x23,
  DEV_MODEM_PREVHOOKOFF =  0x24,
  DEV_MODEM_HOOKOFF     =  0x25,
  DEV_MODEM_POSTHOOKOFF =  0x26,
  DEV_MODEM_BREAK       =  0x27,
  DEV_MODEM_POSTBREAK   =  0x28,


#ifndef SKIP_A

  DEV_START_A2          =  0x100,
  DEV_OPENCANAL_A2      =  0x101,
  DEV_POSTOPENCANAL_A2  =  0x102,
  DEV_TIME_A2           =  0x103,
  DEV_POSTTIME_A2       =  0x104,
  DEV_CONTROL_A2        =  0x105,
  DEV_POSTCONTROL_A2    =  0x106,
  DEV_MANAGE_A2         =  0x107,
  DEV_POSTMANAGE_A2     =  0x108,
  DEV_POSTCORECT_A2     =  0x109,
  DEV_TOP_A2            =  0x10A,
  DEV_POSTTOP_A2        =  0x10B,
  DEV_HEADER_A2         =  0x10C,
  DEV_HEADER_A2PLUS     =  0x10D,
  DEV_POSTHEADER_A2     =  0x10E,
  DEV_DATA_A2           =  0x10F,
  DEV_DATA_A2PLUS       =  0x110,
  DEV_POSTDATA_A2       =  0x111,
  DEV_CORRECT_A2        =  0x112,
  DEV_POSTCORRECT_A2    =  0x113,

  DEV_ERROR1_A2         =  0x114,
  DEV_POSTERROR1_A2     =  0x115,
  DEV_ERROR2_A2         =  0x116,
  DEV_POSTERROR2_A2     =  0x117,

  DEV_START_A3          =  0x140,
  DEV_OPENCANAL_A3      =  0x141,
  DEV_POSTOPENCANAL_A3  =  0x142,
  DEV_ENERGY_A3         =  0x143,

#endif


#ifndef SKIP_B

  DEV_START_B2          =  0x200,
  DEV_OPENCANAL_B2      =  0x201,
  DEV_POSTOPENCANAL_B2  =  0x202,
  DEV_TIME_B2           =  0x203,
  DEV_POSTTIME_B2       =  0x204,
  DEV_CONTROL_B2        =  0x205,
  DEV_POSTCONTROL_B2    =  0x206,
  DEV_POSTCORRECT_B2    =  0x207,
  DEV_VERSION_B2        =  0x208,
  DEV_POSTVERSION_B2    =  0x209,

  DEV_PROFILE_B2        =  0x20A,
  DEV_POSTPROFILE_B2    =  0x20B,
  DEV_TOP_B2            =  0x20C,
  DEV_POSTTOP_B2        =  0x20D,
  DEV_HEADER_B2         =  0x20E,
  DEV_POSTHEADER_B2     =  0x20F,

  DEV_HEADER_B2PLUS     =  0x210,
  DEV_POSTHEADER_B2PLUS =  0x211,

  DEV_HEADER_B2NEXT     =  0x212,
  DEV_POSTHEADER_B2NEXT =  0x213,

  DEV_ERROR_B2          =  0x214,
  DEV_POSTERROR_B2      =  0x215,

  DEV_START_B3          =  0x240,
  DEV_OPENCANAL_B3      =  0x241,
  DEV_POSTOPENCANAL_B3  =  0x242,
  DEV_ENERGY_B3         =  0x243,

  DEV_START_B312        =  0x250,
  DEV_OPENCANAL_B312    =  0x251,
  DEV_POSTOPENCANAL_B312=  0x252,
  DEV_ENERGY_B312       =  0x253,

  DEV_START_B4          =  0x260,
  DEV_OPENCANAL_B4      =  0x261,
  DEV_CHECKUP_DAY_B4    =  0x262,
  DEV_ENERGY_DAY_B4     =  0x263,
  DEV_POSTENERGY_DAY_B4 =  0x264,
  DEV_PREVTOP2_B4       =  0x265,
  DEV_TOP2_B4           =  0x266,
  DEV_POSTTOP2_B4       =  0x267,
  DEV_PREVHEADER2_B4    =  0x268,
  DEV_HEADER2_B4        =  0x269,
  DEV_POSTHEADER2_B4    =  0x26A,
  DEV_ERROR1_B4         =  0x26B,
  DEV_POSTERROR1_B4     =  0x26C,
  DEV_CHECKUP_MON_B4    =  0x26D,
  DEV_ENERGY_MON_B4     =  0x26E,
  DEV_POSTENERGY_MON_B4 =  0x26F,
  DEV_ERROR3_B4         =  0x270,
  DEV_POSTERROR3_B4     =  0x271,
  DEV_PREVCORRECT_B4    =  0x272,
  DEV_ERROR2_B4         =  0x273,
  DEV_POSTERROR2_B4     =  0x274,
  DEV_PREVTOP1_B4       =  0x275,
  DEV_TOP1_B4           =  0x276,
  DEV_POSTTOP1_B4       =  0x277,
  DEV_PREVHEADER1_B4    =  0x278,
  DEV_HEADER1_B4        =  0x279,
  DEV_ERROR4_B4         =  0x27A,
  DEV_POSTERROR4_B4     =  0x27B,
  DEV_POSTHEADER1_B4    =  0x27C,

#endif

#ifndef SKIP_C

  DEV_START_C2          =  0x300,
  DEV_OPENCANAL_C2      =  0x301,
  DEV_POSTOPENCANAL_C2  =  0x302,
  DEV_TIME_C2           =  0x303,
  DEV_POSTTIME_C2       =  0x304,
  DEV_CONTROL_C2        =  0x305,
  DEV_POSTCONTROL_C2    =  0x306,
  DEV_POSTCORRECT_C2    =  0x307,
  DEV_VALUE_C2          =  0x308,
  DEV_POSTVALUE_C2      =  0x309,
  DEV_VERSION_C2        =  0x30A,
  DEV_POSTVERSION_C2    =  0x30B,

  DEV_HEADER_6_C2       =  0x30C,
  DEV_POSTHEADER_6_C2   =  0x30D,
  DEV_DATA_6_C2         =  0x30E,
  DEV_ID_6_C2           =  0x30F,
  DEV_POSTID_6_C2       =  0x310,

  DEV_HEADER_1_C2       =  0x311,
  DEV_POSTHEADER_0_C2   =  0x312,
  DEV_POSTHEADER_1_C2   =  0x313,
  DEV_DATA_1_C2         =  0x314,
  DEV_ID_1_C2           =  0x315,
  DEV_POSTID_1_C2       =  0x316,

//  DEV_INIT_61_C2        =  0x312,
//  DEV_DATA_61_C2        =  0x313,
//  DEV_HEADER_61_C2      =  0x314,
//  DEV_POSTHEADER_61_C2  =  0x315,
//  DEV_DATA_62_C2        =  0x316,
//  DEV_HEADER_62_C2      =  0x317,
//  DEV_POSTHEADER_62_C2  =  0x318,

  DEV_ERROR_1_C2        =  0x319,
  DEV_POSTERROR_1_C2    =  0x31A,
  DEV_ERROR_6_C2        =  0x31B,
  DEV_POSTERROR_6_C2    =  0x31C,

  DEV_START_C3          =  0x340,
  DEV_OPENCANAL_C3      =  0x341,
  DEV_POSTOPENCANAL_C3  =  0x342,
  DEV_TIME_C3           =  0x343,
  DEV_POSTTIME_C3       =  0x344,
  DEV_ENERGY_C3         =  0x345,

  DEV_START_C4          =  0x348,
  DEV_OPENCANAL_C4      =  0x349,
  DEV_CHECKUP_DAY_C4    =  0x34A,
  DEV_ENERGY_DAY_C4     =  0x34B,
  DEV_POSTENERGY_DAY_C4 =  0x34C,
  DEV_PREVHEADER_6_C4   =  0x34D,
  DEV_HEADER_6_C4       =  0x34E,
  DEV_POSTHEADER_6_C4   =  0x34F,
  DEV_DATA_6_C4         =  0x350,
  DEV_ERROR1_6_C4       =  0x351,
  DEV_POSTERROR1_6_C4   =  0x352,
  DEV_ERROR2_6_C4       =  0x353,
  DEV_POSTERROR2_6_C4   =  0x354,
  DEV_CHECKUP_MON_C4    =  0x355,
  DEV_ENERGY_MON_C4     =  0x356,
  DEV_POSTENERGY_MON_C4 =  0x357,
  DEV_ERROR3_6_C4       =  0x358,
  DEV_POSTERROR3_6_C4   =  0x359,
  DEV_PREVCORRECT_C4    =  0x35A,

#endif


#ifndef SKIP_D

  DEV_START_D2          =  0x400,
  DEV_OPENCANAL_D2      =  0x401,
  DEV_POSTOPENCANAL_D2  =  0x402,
  DEV_PASSWORD_D2       =  0x403,
  DEV_POSTPASSWORD_D2   =  0x404,
  DEV_PROFILE_D2        =  0x405,
  DEV_POSTPROFILE_D2    =  0x406,
  DEV_PACKETSIZE_D2     =  0x407,
  DEV_POSTPACKETSIZE_D2 =  0x408,
  DEV_DATA1_D2          =  0x409,
  DEV_POSTDATA1_D2      =  0x40A,
  DEV_DATA2_D2          =  0x40B,
  DEV_POSTDATA2_D2      =  0x40C,
  DEV_CORRECT_D2        =  0x40D,
  DEV_POSTCORRECT_D2    =  0x40E,

  DEV_START_D3          =  0x440,
  DEV_OPENCANAL_D3      =  0x441,
  DEV_POSTOPENCANAL_D3  =  0x442,
  DEV_PASSWORD_D3       =  0x443,
  DEV_POSTPASSWORD_D3   =  0x444,
  DEV_ENERGY_D3         =  0x445,
  DEV_POSTENERGY_D3     =  0x446,
  DEV_CONTINUE_D3       =  0x447,
  DEV_POSTCONTINUE_D3   =  0x448,
  DEV_QUADRANTS_D3      =  0x449,

#endif


#ifndef SKIP_E

  DEV_START_E2          =  0x500,
  DEV_OPENCANAL_E2      =  0x501,
  DEV_POSTOPENCANAL_E2  =  0x502,
  DEV_TIME0_E2          =  0x503,
  DEV_POSTTIME0_E2      =  0x504,
  DEV_TIME1LO_E2        =  0x505,
  DEV_TIME2LO_E2        =  0x506,
  DEV_POSTTIME2LO_E2    =  0x507,
  DEV_CORRECT2LO_E2     =  0x508,
  DEV_POSTCORRECT2LO_E2 =  0x509,
  DEV_TIME1HI_E2        =  0x50A,
  DEV_TIME2HI_E2        =  0x50B,
  DEV_POSTTIME2HI_E2    =  0x50C,
  DEV_CORRECT2HI_E2     =  0x50D,
  DEV_POSTCORRECT2HI_E2 =  0x50E,
  DEV_TIME3_E2          =  0x50F,
  DEV_POSTTIME3_E2      =  0x510,
  DEV_CORRECT3_E2       =  0x511,
  DEV_POSTCORRECT3_E2   =  0x512,

  DEV_ENERGY_E2         =  0x540,
  DEV_POSTENERGY_E2     =  0x541,
  DEV_INDEX_E2          =  0x542,
  DEV_POSTINDEX_E2      =  0x543,
  DEV_DEFECT_E2         =  0x544,
  DEV_POSTDEFECT_E2     =  0x545,

#endif


#ifndef SKIP_F

  DEV_START_F2          =  0x600,
  DEV_OPENCANAL_F2      =  0x601,
  DEV_POSTOPENCANAL_F2  =  0x602,
  DEV_TIME_F2           =  0x603,
  DEV_POSTTIME_F2       =  0x604,
  DEV_CONTROL_F2        =  0x605,
  DEV_POSTCONTROL_F2    =  0x606,
  DEV_CORRECT_F2        =  0x607,
  DEV_POSTCORRECT_F2    =  0x608,
  DEV_HEADER_F2         =  0x609,
  DEV_POSTHEADER_F2     =  0x60A,
  DEV_ENERGY_F2         =  0x60B,
  DEV_POSTENERGY_F2     =  0x60C,
  DEV_ERROR_F2          =  0x60D,
  DEV_POSTERROR_F2      =  0x60E,

  DEV_START_F3          =  0x640,
  DEV_POSTOPENCANAL_F3  =  0x641,
  DEV_CURRENT_F3        =  0x642,

#endif

#ifndef SKIP_G

  DEV_START_G2          =  0x900,
  DEV_OPENCANAL_G2      =  0x901,
  DEV_POSTOPENCANAL_G2  =  0x902,
  DEV_TIME_G2           =  0x903,
  DEV_POSTTIME_G2       =  0x904,
  DEV_CONTROL_G2        =  0x905,
  DEV_POSTCONTROL_G2    =  0x906,
  DEV_POSTCORRECT_G2    =  0x907,
  DEV_PROFILE_G2        =  0x908,
  DEV_POSTPROFILE_G2    =  0x909,
  DEV_TOP_G2            =  0x90A,
  DEV_POSTTOP_G2        =  0x90B,
  DEV_HEADER_G2         =  0x90C,
  DEV_POSTHEADER_G2     =  0x90D,

  DEV_START_31C        =  0x940,
  DEV_OPENCANAL_31C    =  0x941,
  DEV_POSTOPENCANAL_31C=  0x942,
  DEV_ENERGY_31C       =  0x943,

#endif

#ifndef SKIP_H

  DEV_START_H2          =  0xA00,
  DEV_OPENCANAL_H2      =  0xA01,
  DEV_POSTOPENCANAL_H2  =  0xA02,
  DEV_TIME_H2           =  0xA03,
  DEV_POSTTIME_H2       =  0xA04,
  DEV_CONTROL_H2        =  0xA05,
  DEV_POSTCONTROL_H2    =  0xA06,
  DEV_POSTCORRECT_H2    =  0xA07,
  DEV_SPECIES_H2        =  0xA08,
  DEV_POSTSPECIES_H2    =  0xA09,
  DEV_PROFILE_H2        =  0xA0A,
  DEV_POSTPROFILE_H2    =  0xA0B,
  DEV_TOP_H2            =  0xA0C,
  DEV_POSTTOP_H2        =  0xA0D,
  DEV_HEADER_H2         =  0xA0E,
  DEV_POSTHEADER_H2     =  0xA0F,

#endif

#ifndef SKIP_I

  DEV_START_I2          =  0xB00,
  DEV_POSTOPENCANAL_I2  =  0xB01,
  DEV_TIME_I2           =  0xB02,
  DEV_POSTTIME_I2       =  0xB03,
  DEV_CONTROL_I2        =  0xB04,
  DEV_POSTCONTROL_I2    =  0xB05,
  DEV_POSTCORRECT_I2    =  0xB06,
  DEV_HEADER_I2         =  0xB07,
  DEV_POSTHEADER_I2     =  0xB08,

  DEV_START_I3          =  0xB40,
  DEV_ENERGY_I3         =  0xB41,

#endif

#ifndef SKIP_K

  DEV_START_K2          =  0xD00,
  DEV_OPENCANAL_K2      =  0xD01,
  DEV_POSTOPENCANAL_K2  =  0xD02,
  DEV_OPTION_K2         =  0xD03,
  DEV_POSTOPTION_K2     =  0xD04,
  DEV_PASSWORD_K2       =  0xD05,
  DEV_POSTPASSWORD_K2   =  0xD06,
  DEV_PREVTIME_K2       =  0xD15,
  DEV_TIME_K2           =  0xD07,
  DEV_POSTTIME_K2       =  0xD08,
  DEV_DATE_K2           =  0xD09,
  DEV_POSTDATE_K2       =  0xD0A,
  DEV_CONTROL_K2        =  0xD0B,
  DEV_POSTCONTROL_K2    =  0xD0C,
  DEV_POSTCORRECT_K2    =  0xD0D,
  DEV_HEADER_K2         =  0xD0E,
  DEV_POSTHEADER_K2     =  0xD0F,
  DEV_DATA_K2           =  0xD10,
  DEV_OPEN_K2           =  0xD11,
  DEV_PREVCORRECT2_K2   =  0xD12,
  DEV_CORRECT2_K2       =  0xD13,
  DEV_POSTCORRECT2_K2   =  0xD14,

  DEV_START_K3          =  0xD40,
  DEV_OPENCANAL_K3      =  0xD41,
  DEV_POSTOPENCANAL_K3  =  0xD42,
  DEV_OPTION_K3         =  0xD43,
  DEV_POSTOPTION_K3     =  0xD44,
  DEV_ENERGY_K3         =  0xD45,
  DEV_POSTENERGY_K3     =  0xD46,

#endif

#ifndef SKIP_M

  DEV_START_M3          =  0x1200,
  DEV_ENERGY_M3         =  0x1201,

#endif

#ifndef SKIP_N

  DEV_START_N3          =  0x1300,
  DEV_ENERGY_N3         =  0x1301,

#endif

#ifndef SKIP_O

  DEV_START_O2          =  0x1400,
  DEV_POSTOPENCANAL_O2  =  0x1401,
  DEV_TIME_O2           =  0x1402,
  DEV_POSTTIME_O2       =  0x1403,
  DEV_CONTROL_O2        =  0x1404,
  DEV_POSTCONTROL_O2    =  0x1405,
  DEV_POSTCORRECT_O2    =  0x1406,
  DEV_HEADER_O2         =  0x1407,
  DEV_POSTHEADER_O2     =  0x1408,

  DEV_START_O3          =  0x1440,
  DEV_ENERGY_O3         =  0x1441,

#endif

#ifndef SKIP_P

  DEV_START_P2          =  0x1500,
  DEV_OPENCANAL_P2      =  0x1501,
  DEV_POSTOPENCANAL_P2  =  0x1502,
  DEV_MODE_P2           =  0x1503,
  DEV_POSTMODE_P2       =  0x1504,
  DEV_PASSWORD_P2       =  0x1505,
  DEV_POSTPASSWORD_P2   =  0x1506,
  DEV_TIME_P2           =  0x1507,
  DEV_POSTTIME_P2       =  0x1508,
  DEV_CORRECT_P2        =  0x1509,
  DEV_POSTCORRECT_P2    =  0x150A,
  DEV_REGISTER_P2       =  0x150B,
  DEV_POSTREGISTER_P2   =  0x150C,
  DEV_SETVALUE_P2       =  0x150D,
  DEV_POSTSETVALUE_P2   =  0x150E,
  DEV_GETVALUE_P2       =  0x150F,
  DEV_POSTGETVALUE_P2   =  0x1510,
  DEV_PROFILE_P2        =  0x1511,
  DEV_POSTPROFILE_P2    =  0x1512,
  DEV_REPASSWORD_P2     =  0x1513,
  DEV_POSTREPASSWORD_P2 =  0x1514,

  DEV_START_P3          =  0x1540,
  DEV_OPENCANAL_P3      =  0x1541,
  DEV_POSTOPENCANAL_P3  =  0x1542,
  DEV_MODE_P3           =  0x1543,
  DEV_POSTMODE_P3       =  0x1544,
  DEV_PASSWORD_P3       =  0x1545,
  DEV_POSTPASSWORD_P3   =  0x1546,
  DEV_REGISTER_P3       =  0x1547,
  DEV_POSTREGISTER_P3   =  0x1548,
  DEV_ENERGY0_P3        =  0x1549,
  DEV_POSTENERGY0_P3    =  0x154B,
  DEV_ENERGY1_P3        =  0x154A,

#endif

#ifndef SKIP_Q

  DEV_START_Q2          =  0x1600,
  DEV_OPEN_Q2           =  0x1601,
  DEV_CORRECT_Q2        =  0x1602,
  DEV_OPENCANAL_Q2      =  0x1603,
  DEV_POSTOPENCANAL_Q2  =  0x1604,
  DEV_OPTION_Q2         =  0x1605,
  DEV_POSTOPTION_Q2     =  0x1606,
  DEV_PASSWORD_Q2       =  0x1607,
  DEV_POSTPASSWORD_Q2   =  0x1608,
  DEV_PREVTIME_Q2       =  0x1613,
  DEV_TIME_Q2           =  0x1609,
  DEV_POSTTIME_Q2       =  0x160A,
  DEV_DATE_Q2           =  0x160B,
  DEV_POSTDATE_Q2       =  0x160C,
  DEV_CONTROL_Q2        =  0x160D,
  DEV_POSTCONTROL_Q2    =  0x160E,
  DEV_POSTCORRECT_Q2    =  0x160F,
  DEV_HEADER_Q2         =  0x1610,
  DEV_POSTHEADER_Q2     =  0x1611,
  DEV_DATA_Q2           =  0x1612,

  DEV_START_Q3          =  0x1640,
  DEV_OPENCANAL_Q3      =  0x1641,
  DEV_POSTOPENCANAL_Q3  =  0x1642,
  DEV_OPTION_Q3         =  0x1643,
  DEV_POSTOPTION_Q3     =  0x1644,
  DEV_ENERGY_Q3         =  0x1645,

#endif

#ifndef SKIP_R

  DEV_START_R2          =  0x1700,

  DEV_START_R3          =  0x1710,
  DEV_DATA_R3           =  0x1711,
  DEV_POSTDATA_R3       =  0x1712,
  DEV_ERROR_R3          =  0x1713,

#endif

#ifndef SKIP_S

  DEV_START_S2          =  0x1800,
  DEV_VERSION_S2        =  0x1801,
  DEV_POSTVERSION_S2    =  0x1802,
  DEV_POSTOPENCANAL_S2  =  0x1803,
  DEV_TIME_S2           =  0x1804,
  DEV_POSTTIME_S2       =  0x1805,
  DEV_CONTROL_S2        =  0x1806,
  DEV_POSTCORRECT_S2    =  0x1807,
  DEV_CONFIG_S2         =  0x1808,
  DEV_POSTCONFIG_S2     =  0x1809,
  DEV_VALUE_S2          =  0x180A,
  DEV_POSTVALUE_S2      =  0x180B,
  DEV_HEADER_S2         =  0x180C,
  DEV_POSTHEADER_S2     =  0x180D,
  DEV_DATA_S2           =  0x180E,

  DEV_START_S3          =  0x1820,
  DEV_CONFIG_S3         =  0x1821,
  DEV_POSTCONFIG_S3     =  0x1822,
  DEV_ENERGY_S3         =  0x1823,

#endif

#ifndef SKIP_T

  DEV_START_T2          =  0x1900,
  DEV_VERSION_T2        =  0x1901,
  DEV_POSTVERSION_T2    =  0x1902,
  DEV_POSTOPENCANAL_T2  =  0x1903,
  DEV_TIME_T2           =  0x1904,
  DEV_POSTTIME_T2       =  0x1905,
  DEV_CONTROL_T2        =  0x1906,
  DEV_POSTCONTROL_T2    =  0x1907,
  DEV_POSTCORRECT_T2    =  0x1908,
  DEV_PREVHEADER_T2     =  0x1909,
  DEV_HEADER_T2         =  0x190A,
  DEV_POSTHEADER_T2     =  0x190B,

  DEV_START_T3          =  0x1940,
  DEV_ENERGY_T3         =  0x1941,

#endif

#ifndef SKIP_U

  DEV_START_U2          =  0x1A00,
  DEV_PREVCORRECT_U2    =  0x1A01,
  DEV_CORRECT_U2        =  0x1A02,
  DEV_OPEN_U2           =  0x1A03,
  DEV_OPENCANAL_U2      =  0x1A04,
  DEV_POSTOPENCANAL_U2  =  0x1A05,
  DEV_OPTION_U2         =  0x1A06,
  DEV_POSTOPTION_U2     =  0x1A07,
  DEV_PASSWORD_U2       =  0x1A08,
  DEV_POSTPASSWORD_U2   =  0x1A09,
  DEV_PREVTIME_U2       =  0x1A15,
  DEV_TIME_U2           =  0x1A0A,
  DEV_POSTTIME_U2       =  0x1A0B,
  DEV_DATE_U2           =  0x1A0C,
  DEV_POSTDATE_U2       =  0x1A0D,
  DEV_CONTROL_U2        =  0x1A0E,
  DEV_POSTCONTROL_U2    =  0x1A0F,
  DEV_POSTCORRECT_U2    =  0x1A10,
  DEV_HEADER_U2         =  0x1A11,
  DEV_POSTHEADER_U2     =  0x1A12,
  DEV_DATA_U2           =  0x1A13,
  DEV_PREVHEADER_U2     =  0x1A14,

  DEV_START_U3          =  0x1A40,
  DEV_OPENCANAL_U3      =  0x1A41,
  DEV_POSTOPENCANAL_U3  =  0x1A42,
  DEV_OPTION_U3         =  0x1A43,
  DEV_POSTOPTION_U3     =  0x1A44,
  DEV_ENERGY_U3         =  0x1A45,

  DEV_PREVHEADER_U4     =  0x1A50,
  DEV_HEADER_U4         =  0x1A51,
  DEV_POSTHEADER_U4     =  0x1A52,
  DEV_DATA_U4           =  0x1A53,

#endif

#ifndef SKIP_V

  DEV_START_V2          =  0x1B00,
  DEV_VERSION_V2        =  0x1B01,
  DEV_POSTVERSION_V2    =  0x1B02,
  DEV_POSTOPENCANAL_V2  =  0x1B03,
  DEV_TIME_V2           =  0x1B04,
  DEV_POSTTIME_V2       =  0x1B05,
  DEV_CONTROL_V2        =  0x1B06,
  DEV_POSTCORRECT_V2    =  0x1B07,
//  DEV_CONFIG_V2         =  0x1B08,
//  DEV_POSTCONFIG_V2     =  0x1B09,
  DEV_VALUE_V2          =  0x1B0A,
  DEV_POSTVALUE_V2      =  0x1B0B,
  DEV_HEADER_V2         =  0x1B0C,
  DEV_POSTHEADER_V2     =  0x1B0D,
  DEV_DATA_V2           =  0x1B0E,

  DEV_START_V3          =  0x1B20,
//  DEV_CONFIG_V3         =  0x1B21,
//  DEV_POSTCONFIG_V3     =  0x1B22,
  DEV_ENERGY_V3         =  0x1B23,

#endif

#ifndef SKIP_W

  DEV_START_W2          =  0x1C00,
  DEV_OPEN_W2           =  0x1C03,
  DEV_OPENCANAL_W2      =  0x1C04,
  DEV_POSTOPENCANAL_W2  =  0x1C05,
  DEV_OPTION_W2         =  0x1C06,
  DEV_POSTOPTION_W2     =  0x1C07,
  DEV_PASSWORD_W2       =  0x1C08,
  DEV_POSTPASSWORD_W2   =  0x1C09,
  DEV_PREVTIME_W2       =  0x1C0A,
  DEV_TIME_W2           =  0x1C0B,
  DEV_POSTTIME_W2       =  0x1C0C,
  DEV_DATE_W2           =  0x1C0D,
  DEV_POSTDATE_W2       =  0x1C0E,
  DEV_GETCORRECT_W2     =  0x1C0F,
  DEV_POSTGETCORRECT_W2 =  0x1C10,
  DEV_SETCORRECT_W2     =  0x1C11,
  DEV_POSTSETCORRECT_W2 =  0x1C12,
  DEV_CORRECT_W2        =  0x1C13,
  DEV_POSTCORRECT_W2    =  0x1C14,
  DEV_CONTROL_W2        =  0x1C15,
  DEV_POSTCONTROL_W2    =  0x1C16,
  DEV_PREVPROFILE_W2    =  0x1C17,
  DEV_PROFILE_W2        =  0x1C18,
  DEV_POSTPROFILE_W2    =  0x1C19,
  DEV_PREVOPENCANAL_W2  =  0x1C1A,

  DEV_START_W3          =  0x1C40,
  DEV_OPENCANAL_W3      =  0x1C41,
  DEV_POSTOPENCANAL_W3  =  0x1C42,
  DEV_OPTION_W3         =  0x1C43,
  DEV_POSTOPTION_W3     =  0x1C44,
  DEV_ENERGY_W3         =  0x1C45,
  DEV_POSTENERGY_W3     =  0x1C46,

#endif

#ifndef SKIP_31

  DEV_START_31P         =  0x1D00,
  DEV_OPENCANAL_31P     =  0x1D01,
  DEV_POSTOPENCANAL_31P =  0x1D02,
  DEV_TIME_31P          =  0x1D03,
  DEV_POSTTIME_31P      =  0x1D04,
  DEV_CONTROL_31P       =  0x1D05,
  DEV_POSTCONTROL_31P   =  0x1D06,
  DEV_POSTCORRECT_31P   =  0x1D07,
  DEV_PROFILE_31P       =  0x1D08,
  DEV_POSTPROFILE_31P   =  0x1D09,
  DEV_TOP_31P           =  0x1D0A,
  DEV_POSTTOP_31P       =  0x1D0B,
  DEV_HEADER_31P        =  0x1D0C,
  DEV_POSTHEADER_31P    =  0x1D0D,

  DEV_START_31C         =  0x1D20,
  DEV_OPENCANAL_31C     =  0x1D21,
  DEV_POSTOPENCANAL_31C =  0x1D22,
  DEV_ENERGY_31C        =  0x1D23,

#endif

#ifndef SKIP_32

  DEV_START_32P         =  0x1E00,
  DEV_OPENCANAL_32P     =  0x1E01,
  DEV_POSTOPENCANAL_32P =  0x1E02,
  DEV_TIME_32P          =  0x1E03,
  DEV_POSTTIME_32P      =  0x1E04,
  DEV_CONTROL_32P       =  0x1E05,
  DEV_POSTCONTROL_32P   =  0x1E06,
  DEV_POSTCORRECT_32P   =  0x1E07,
  DEV_PROFILE_32P       =  0x1E08,
  DEV_POSTPROFILE_32P   =  0x1E09,
  DEV_TOP_32P           =  0x1E0A,
  DEV_POSTTOP_32P       =  0x1E0B,
  DEV_HEADER_32P        =  0x1E0C,
  DEV_POSTHEADER_32P    =  0x1E0D,

#endif

#ifndef SKIP_33

  DEV_START_33P         =  0x1F00,
  DEV_OPENCANAL_33P     =  0x1F01,
  DEV_POSTOPENCANAL_33P =  0x1F02,
  DEV_TIME_33P          =  0x1F03,
  DEV_POSTTIME_33P      =  0x1F04,
  DEV_CONTROL_33P       =  0x1F05,
  DEV_POSTCONTROL_33P   =  0x1F06,
  DEV_POSTCORRECT_33P   =  0x1F07,
  DEV_PROFILE_33P       =  0x1F08,
  DEV_POSTPROFILE_33P   =  0x1F09,
  DEV_TOP_33P           =  0x1F0A,
  DEV_POSTTOP_33P       =  0x1F0B,
  DEV_HEADER_33P        =  0x1F0C,
  DEV_POSTHEADER_33P    =  0x1F0D,

#endif

  DEV_PAUSE             =  1

} device;


#endif
