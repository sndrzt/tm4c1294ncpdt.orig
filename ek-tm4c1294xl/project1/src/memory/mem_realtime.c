/*------------------------------------------------------------------------------
MEM_REALTIME.S


------------------------------------------------------------------------------*/

#include "../main.h"



// ���������� ��� ��������� ��������� �������
time                    tiCurr, tiPrev;

// ������� �� ��������� �������
uchar                   ibSoftMnt, ibHardMnt,
                        ibSoftHou,
                        ibSoftDay, ibHardDay,
                        ibSoftMon, ibHardMon;

// ������� �� ���������� ������
uint                    iwHardHou;

// �������� ��������� ����������� �������� �������
uchar                   cbShowCurrentTime;



// �������� ������������� �������
ulong                   cdwSeconds, cdwMinutes1, cdwMinutes3, cdwMinutes30;

// �������� ������������� �������
uint                    cwDays, cwMonths, cwYears;



// ����������
uchar                   bHouInc;
