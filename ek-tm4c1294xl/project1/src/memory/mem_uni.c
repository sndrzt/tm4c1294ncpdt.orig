/*------------------------------------------------------------------------------
MEM_UNI.S


------------------------------------------------------------------------------*/

#include "../main.h"



// ��� �������
char                    szObjectName[bNAME_SIZE];

// ����� �������
char                    mpszCanalsName[bCANALS][bNAME_SIZE];

// ����� �����
char                    mpszGroupsName[bGROUPS][bNAME_SIZE];

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
bool                    boStrictUni;

// ������������ �������
uchar                   bMaxDelayUni;

// ����
bool                    boRepeatFlowUni;

// ����
bool                    boEnblPassUni;
