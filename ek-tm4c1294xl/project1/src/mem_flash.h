/*------------------------------------------------------------------------------
MEM_FLASH.H


------------------------------------------------------------------------------*/

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
