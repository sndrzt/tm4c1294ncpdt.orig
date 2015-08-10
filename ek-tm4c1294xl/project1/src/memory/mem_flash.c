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

// ������� ���������� ������� ������� ����-������
uint                    mpcwFlashControl[wPAGES_TOTAL];

// �������� ���������� ��������
ulong                   cdwFlashErasePage,
                        cdwFlashReadPage,
                        cdwFlashWritePage;

// �������� ���������� ������
ulong                   cdwFlashReadByte,
                        cdwFlashWriteByte;

// �������� ���������� ������
uint                    cwFlashBusyWrn,
                        cwFlashCompareWrn,
                        cwFlashEraseWrn,
                        cwFlashReadWrn,
                        cwFlashWriteWrn,
                        cwFlashCompareErr,
                        cwFlashEraseErr,
                        cwFlashReadErr,
                        cwFlashWriteErr;
