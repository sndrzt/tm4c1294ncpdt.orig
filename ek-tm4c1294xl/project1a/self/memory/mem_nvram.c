/*------------------------------------------------------------------------------
MEM_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"



// �������� ���������� ��������
ulong                   cdwNvramReadBuff,
                        cdwNvramWriteBuff,
                        cdwNvramFreeBuff;

// �������� ���������� ������
ulong                   cdwNvramReadByte,
                        cdwNvramWriteByte;

// �������� ���������� ������
uint                    cwNvramReadWrn,
                        cwNvramReadErr,
                        cwNvramWriteWrn,
                        cwNvramWriteErr,
                        cwNvramFreeWrn,
                        cwNvramFreeErr,
                        cwNvramCompareWrn,
                        cwNvramCompareErr;
