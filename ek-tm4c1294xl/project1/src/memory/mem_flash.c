/*------------------------------------------------------------------------------
MEM_FLASH.C


------------------------------------------------------------------------------*/

#include        "../main.h"
#include        "../include/flash.h"



// ������ ��������/������������ ������� � ���������� �����������/���������� ������
uint                    wPageIn, wPageOut,
                        wByteIn, wByteOut;

// ����� ��������� ����-������
uchar                   bStatusFlash;

// ������ ��������/������������ ������� ����-������
uchar                   mpbPageIn[wPAGE_SIZE],
                        mpbPageOut[wPAGE_SIZE];

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
