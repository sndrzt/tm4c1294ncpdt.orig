/*------------------------------------------------------------------------------
MEM_FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



// ����� ��������� ����-������
uchar                   bFlashStatus;

// ������ ��������/������������ ������� ����-������
uchar                   mpbPageIn[wPAGE_BYTES],
                        mpbPageOut[wPAGE_BYTES];

// �������� ��� �������� ��������� ����-������
uint                    cwWrnBusy,
                        cwWrnCompare,
                        cwWrnPageErase,
                        cwWrnPageRead,
                        cwWrnPageWrite,
                        cwErrCompare,
                        cwErrPageErase,
                        cwErrPageRead,
                        cwErrPageWrite;

// ������� ���������� ������� ������� ����-������
uint                    mpcwFlashControl[wPAGES_TOTAL];

// �������� ���������� ��������
ulong                   cdwPageErase,
                        cdwPageRead,
                        cdwPageWrite;

// �������� ���������� ������
ulong                   cdwFlashReadBytes,
                        cdwFlashWriteBytes;
