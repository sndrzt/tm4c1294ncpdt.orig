/*------------------------------------------------------------------------------
MEM_RECORDS,C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������� ������
record                  reCurr;

// �������� �������
ulong                   cdwKeyRecord,
                        cdwSysRecord,
                        cdwDigRecord,
                        cdwImpRecord,
                        cdwModRecord,
                        cdwPh2Record,
                        cdwAuxRecord;

// ����� ���������� �������
uchar                   mpfRecordDsbl[256];

// ���������� ���������� - �����
time                    tiRecordTime, tiRecordTime2;

// ���������� ���������� - �����
uchar                   ibRecordCan;

// ���������� ����������
uchar                   bRecord;

// ���������� ����������
uint                    wRecord;

// ���������� ����������
ulong                   dwRecord;
