/*------------------------------------------------------------------------------
MEM_PHONES.C


------------------------------------------------------------------------------*/

#include        "../main.h"



// ������ ������� ���������
phone                   mpphPhones[bCANALS];

// ������������ ����� �������� ������� Connect
uchar                   bMaxConnect;

// ���� ���������� �������: ��������� 2
boolean                 boCustomModem;

// �������� ��� �������� ������ �������� �����
uint                    mpcwBaud[bPORTS],
                        mpcwCommon[bPORTS],
                        mpcwCustom[bPORTS],
                        mpcwConnect[bPORTS],
                        mpcwEscape[bPORTS],
                        mpcwHookOff[bPORTS],
                        mpcwDTROff[bPORTS];
