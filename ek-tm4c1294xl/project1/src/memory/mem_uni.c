/*------------------------------------------------------------------------------
MEM_UNI.S


------------------------------------------------------------------------------*/

#include        "../main.h"



// ��� �������
char                    szObjectName[bNAME];

// ����� �������
char                    mpszCanalsName[bCANALS][bNAME];

// ����� �����
char                    mpszGroupsName[bGROUPS][bNAME];

// ����������
digital                 mpdiDevicesUni[bCANALS];

// ���������� ���������
uchar                   cbDevicesUni;

// ������� ������� � ������
uchar                   mpbDelayUni[bPORTS], mpbMaxDelayUni[bPORTS];

// ����� �����
uchar                   mpbGroupMaskUni[16];

// ����� �����
uchar                   mpbDefUni[64];

// ������� �������� ���������� ���������
boolean                 boStrictUni;

// ������������ �������
uchar                   bMaxDelayUni;

// ����
boolean                 boRepeatFlowUni;
