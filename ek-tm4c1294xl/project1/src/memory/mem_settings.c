/*------------------------------------------------------------------------------
MEM_SETTINGS.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ���������� ����� �������
uchar                   bLogical;

// ���������� ����� �������
uint                    wPrivate;

// ����� ������ �������
global                  enGlobal;



// ������� �������� �� �������� �����
decret                  deDecret;

// ���� �������� �� �������� �����
time                    tiSummer, tiWinter;

// �������� ��������� ��������� �� �������� ����� TODO persist cbSummer, cbWinter
uchar                   cbSummer, cbWinter;



// �����/���� ��������� ��������� � ���������� �������
time                    tiPowerOn, tiPowerOff;

// ������� ���������� �������
uchar                   cbPowerOn;

// �����/���� �������
time                    tiStart;



// ���������� � ����������� ������
uchar                   mpbPassOne[10],
                        mpbPassTwo[10];
