/*------------------------------------------------------------------------------
MEM_FLASH.H


------------------------------------------------------------------------------*/

#include "../include/flash.h"



extern  uint                    wPageIn, wPageOut,
                                wByteIn, wByteOut;

extern  uchar                   bStatusFlash;

extern  uchar                   mpbPageIn[wPAGE_SIZE],
                                mpbPageOut[wPAGE_SIZE];

extern  uint                    cwWrnBusy,
                                cwWrnCompare,
                                cwWrnPageErase,
                                cwWrnPageRead,
                                cwWrnPageWrite,
                                cwErrCompare,
                                cwErrPageErase,
                                cwErrPageRead,
                                cwErrPageWrite;

extern  uint                    mpcwFlashControl[wPAGES];

extern  uint                    cwPageErase,
                                cwPageRead,
                                cwPageWrite;
