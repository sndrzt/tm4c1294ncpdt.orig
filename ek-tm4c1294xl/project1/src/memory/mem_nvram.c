/*------------------------------------------------------------------------------
MEM_NVRAM,C


------------------------------------------------------------------------------*/

#include "../main.h"



// �������� ���������� ��������
ulong                   cdwNvramRead,
                        cdwNvramWrite,
                        cdwNvramFree;

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
