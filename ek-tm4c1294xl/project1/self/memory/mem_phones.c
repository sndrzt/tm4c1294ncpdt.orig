/*------------------------------------------------------------------------------
MEM_PHONES.C


------------------------------------------------------------------------------*/

#include "../main.h"



// ������ ������� ���������
line                    mpphPhones[bCANALS];

// ������������ ����� �������� ������� Connect
uchar                   bMaxConnect;

// ���� ���������� �������: ��������� 2
bool                    boCustomModem;

// �������� ��� �������� ������ �������� �����
uint                    mpcwBaud[bPORTS],
                        mpcwCommon[bPORTS],
                        mpcwCustom[bPORTS],
                        mpcwConnect[bPORTS],
                        mpcwEscape[bPORTS],
                        mpcwHookOff[bPORTS],
                        mpcwDTROff[bPORTS];
