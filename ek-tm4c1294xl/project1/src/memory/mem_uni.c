/*------------------------------------------------------------------------------
MEM_UNI.S


------------------------------------------------------------------------------*/

#include        "../main.h"



// ��� �������
uchar                   szObjectName[bNAME];

// ����� �������
uchar                   mpszCanalName[bCANALS][bNAME];

// ����� �����
uchar                   mpszGroupName[bGROUPS][bNAME];

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
