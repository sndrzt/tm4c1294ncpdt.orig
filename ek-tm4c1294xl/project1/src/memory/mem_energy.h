/*------------------------------------------------------------------------------
MEM_ENERGY.H


------------------------------------------------------------------------------*/

extern  uint                    mpwImpMntCanCurr[bCANALS];

extern  uint                    mpwImpMntCan1[2][bCANALS];

extern  uint                    mpwImpHouCan[2][bCANALS];

extern  impulse                 mpimDayCan[2][bCANALS],
                                mpimMonCan[2][bCANALS],
                                mpimAbsCan[bCANALS];

extern  impulse                 imAlt;

extern  real                    mpreCntMonCan[2][bCANALS];

extern  power                   mppoDayGrp[2][bGROUPS],
                                mppoMonGrp[2][bGROUPS];
