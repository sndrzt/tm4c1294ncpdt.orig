/*------------------------------------------------------------------------------
MEM_FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



// ���������� �����������/���������� ������
uint                    wByteIn, wByteOut;

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
uint                    mpcwFlashControl[wPAGES];

// �������� ���������� ��������
ulong                   cdwPageErase,
                        cdwPageRead,
                        cdwPageWrite;

// �������� ���������� ������
ulong                   cdwFlashReadBytes,
                        cdwFlashWriteBytes;
