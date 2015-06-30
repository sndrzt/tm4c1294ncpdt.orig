/*------------------------------------------------------------------------------
MEM_FLASH.C


------------------------------------------------------------------------------*/

#include "../main.h"
#include "../include/flash.h"



// ������ ��������/������������ ������� � ���������� �����������/���������� ������
uint                    wPageIn, wPageOut,
                        wByteIn, wByteOut;

// ����� ��������� ����-������
uchar                   bStatusFlash;

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

// �������� ��� �������� ���������� ��������
uint                    cwPageErase,
                        cwPageRead,
                        cwPageWrite;
