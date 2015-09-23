/*------------------------------------------------------------------------------
MEM_FLASH!C


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
uint                    cwFlashBusyCnt,
                        cwFlashBusyErr,
                        cwFlashCompareWrn,
                        cwFlashCompareErr,
                        cwFlashEraseWrn,
                        cwFlashEraseErr,
                        cwFlashReadWrn,
                        cwFlashReadErr,
                        cwFlashWriteWrn,
                        cwFlashWriteErr;

// �������� ���������� ������
uint                    cwFlashCompareErr1,
                        cwFlashCompareErr2,
                        cwFlashEraseErr1,
                        cwFlashEraseErr2,
                        cwFlashReadErr1,
                        cwFlashReadErr2,
                        cwFlashWriteErr1,
                        cwFlashWriteErr2;
