/*------------------------------------------------------------------------------
MEM_REALTIME.S


------------------------------------------------------------------------------*/

#include "../main.h"
#include "mem_realtime.h"



// ���������� ��� ��������� ��������� �������
time                    tiCurr, tiPrev;

// ������� �� ��������� �������
uchar                   ibSoftMnt,
                        ibSoftHou,
                        ibSoftDay, ibHardDay,
                        ibSoftMon, ibHardMon;

// ������� �� ���������� ������
uint                    iwHardMnt,
                        iwHardHou;

// �������� ��������� ����������� �������� �������
uchar                   cbShowCurrentTime;



// �������� ������������ ��������� ����������
realtime1               Realtime1;



// ����������
uchar                   bHouInc;
