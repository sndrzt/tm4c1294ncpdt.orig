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
time                    tiRecordSetCurrTime;

// ���������� ���������� - �����
uchar                   ibRecordCan;
