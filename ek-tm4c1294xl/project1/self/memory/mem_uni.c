/*------------------------------------------------------------------------------
MEM_UNI,S


------------------------------------------------------------------------------*/

#include "../main.h"



// �������� �������
char                    szObjectName[bNAME_SIZE];

// �������� �������
char                    mpszCanalsName[bCANALS][bNAME_SIZE];

// �������� �����
char                    mpszGroupsName[bGROUPS][bNAME_SIZE];

// ������ ���������
digital                 mpdiDevicesUni[bCANALS];

// ������ �������� ������ ������� ���������
uchar                   mpibFirstCanalsUni[bCANALS];

// ���������� ���������
uchar                   cbDevicesUni;

// �������� ������� � ������
uchar                   mpbDelayUni[bPORTS];

// ������������ ������� ������� � ������
uchar                   bMaxDelayUni;

// ����� �����
uchar                   mpbGroupMaskUni[16];

// ����� �����
uchar                   mpbDefUni[64];

// ������� �������� ���������� ���������
bool                    boStrictUni;

// ������� ������������� �������� �������� ����� ������ ������� �����
bool                    boRepeatFlowUni;

// ������� ������������� ������������� ������
bool                    boEnblPassUni;
