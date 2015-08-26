/*------------------------------------------------------------------------------
MEM_GPS.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ����� ����� ����� GPS
uchar                   bPortGps;

// ���������� ����������
uchar                   bStatusGps;

// ���������� ����������
uchar                   bVersionMaxGps, bVersionMinGps;

// ���������� ����������
time                    tiGps;

// ������� ����
uchar                   bGmtGps;

// ������ ��������� �������
bool                    mpboScheduleGps[48];

// �������� �������
uint                    mpcwGpsStatus20[20];

// �������� ������� ��/����� ��������� ���������
time                    tiPrevCorrect, tiPostCorrect;

// ������� ������������� ��������� ������� ��� ������� �������� �������
bool                    boSeasonGps;

// ����� �������� ������
uchar                   bSeasonCurr;
