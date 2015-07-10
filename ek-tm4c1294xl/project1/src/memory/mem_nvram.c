/*------------------------------------------------------------------------------
MEM_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"



// �������� ���������� ��������
ulong                   cdwNvramReadBuffs,
                        cdwNvramWriteBuffs,
                        cdwNvramFreeBuffs;

// �������� ���������� ������
ulong                   cdwNvramReadBytes,
                        cdwNvramWriteBytes;

// �������� ���������� ������
uint                    cwWrnNvramRead,
                        cwErrNvramRead,
                        cwWrnNvramWrite,
                        cwErrNvramWrite,
                        cwWrnNvramFree,
                        cwErrNvramFree,
                        cwWrnNvramCompare,
                        cwErrNvramCompare;
