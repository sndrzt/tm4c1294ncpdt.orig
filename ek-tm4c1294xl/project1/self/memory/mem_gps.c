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
bool                    mpboGpsSchedule[48];

// �������� �������
uint                    mpcwGpsSchedule[20];

// �������� ������� ��/����� ��������� ���������
time                    tiPrevCorrect, tiPostCorrect;

// ������� ������������� ��������� ������� ��� ������� �������� �������
bool                    boSeasonGps;

// ����� �������� ������
uchar                   bSeasonCurr;
