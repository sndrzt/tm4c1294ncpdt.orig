/*------------------------------------------------------------------------------
FLASH.H

 ��������� ����-������
------------------------------------------------------------------------------*/

#ifndef __FLASH
#define __FLASH


// ������ ��������
#define wPAGE_SIZE      528

// ������ ��������, ��������� ��� ������ ������ ������������
#define wFREEPAGE_SIZE  512

// ���������� �������
#define wPAGES          8192


// ���������� �������� ��� ������ �������� ���������
#define wMAXBUSY        1000

// ���������� �������� ��� ������/������ ��������
#define bMAXREPEAT      8


// ������ ������ ������
#define wFLA_BEGIN      0

#define wFLA_PRIVATE    (uint)(wFLA_BEGIN)
#define wFLA_LABEL      (uint)(wFLA_PRIVATE + 1)
#define wFLA_GROUPS     (uint)(wFLA_LABEL + 1)

#define wFLA_END        (uint)(wFLA_GROUPS + 1)


#endif
