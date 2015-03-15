/*------------------------------------------------------------------------------
CURRENT_RUN.C


------------------------------------------------------------------------------*/

#include        "../main.h"



/*
#ifdef  POWER

bit     StartCurrent(uchar  ibCanal)
{
  ibDig = ibCanal;

  while (ibDig < bCANALS)               // ��������� ��� �������� ���������
  {
    LoadCurrDigital(ibDig);

    if ((diCurr.bDevice ==  1) || (diCurr.bDevice == 15) ||
        (diCurr.bDevice ==  2) || (diCurr.bDevice ==  8) || (diCurr.bDevice == 12) ||
        (diCurr.bDevice ==  3) ||
        (diCurr.bDevice ==  4) ||
        (diCurr.bDevice ==  6) ||
        (diCurr.bDevice ==  9) ||
        (diCurr.bDevice == 11) || (diCurr.bDevice == 20) || (diCurr.bDevice == 25) ||
        (diCurr.bDevice == 13) || (diCurr.bDevice == 14) ||
        (diCurr.bDevice == 16) || (diCurr.bDevice == 17) ||
        (diCurr.bDevice == 18) ||
        (diCurr.bDevice == 19) ||
        (diCurr.bDevice == 21) ||
        (diCurr.bDevice == 22) || (diCurr.bDevice == 26) ||
        (diCurr.bDevice == 23) ||
        (diCurr.bDevice == 24))
    {
      if (mpboReadyCan[ibDig] == boFalse)
      {
        if (mpboEnblCan[ibDig] == boFalse)
        {
          sprintf(szHi,"�����: %-2bu       ",ibDig+1);
          ShowLo(szDisabledCan); if (boHideMessages == boFalse) Delay(300);
        }
        else break;
      }
    }

    ibDig++;
  }

  if (ibDig >= bCANALS) return(0);


  NoShowTime(1);
  ShowDigitalHi(); Clear();

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_A
    case 15:
    case 1:  SetNext(DEV_START_A3);  break;
#endif

#ifndef SKIP_B
    case 8:
    case 2:  SetNext(DEV_START_B3);  break;
#endif

#ifndef SKIP_B
    case 12: SetNext(DEV_START_B312);  break;
#endif

#ifndef SKIP_C
    case 3:  SetNext(DEV_START_C3);  break;
#endif

#ifndef SKIP_D
    case 4:  SetNext(DEV_START_D3);  break;
#endif

#ifndef SKIP_F
    case 6:  SetNext(DEV_START_F3);  break;
#endif

#ifndef SKIP_G
    case 9:  SetNext(DEV_START_G3);  break;
#endif

#ifndef SKIP_I
    case 11: SetNext(DEV_START_I3);  break;
#endif

#ifndef SKIP_K
    case 14:
    case 13: SetNext(DEV_START_K3);  break;
#endif

#ifndef SKIP_L
    case 16:
    case 17: SetNext(DEV_START_K3);  break;
#endif

#ifndef SKIP_M
    case 18: SetNext(DEV_START_M3);  break;
#endif

#ifndef SKIP_N
    case 19: SetNext(DEV_START_N3);  break;
#endif

#ifndef SKIP_O
    case 20: SetNext(DEV_START_O3);  break;
#endif

#ifndef SKIP_P
    case 21: SetNext(DEV_START_P3);  break;
#endif

#ifndef SKIP_Q
    case 22: SetNext(DEV_START_Q3);  break;
#endif

#ifndef SKIP_R
    case 23: SetNext(DEV_START_R3);  break;
#endif

#ifndef SKIP_S
    case 24: SetNext(DEV_START_S3);  break;
#endif

#ifndef SKIP_T
    case 25: SetNext(DEV_START_T3);  break;
#endif

#ifndef SKIP_U
    case 26: SetNext(DEV_START_U3);  break;
#endif
  }

  exExtended = EXT_CURRENT_3MIN;
  MakePause(DEV_MODEM_START);
  return(1);
}
*/

void    RunCurrent(void)
{
/*
  if (boLoadMnt == boTrue)
  {
#ifdef  FLOW
    CloseFlow();
#endif

    if (GetCurr() == DEV_PAUSE) return;
    if (fConnect == 1) return;

    enModbusCurrent = MB1_PROGRESS;
    boErrorCurrent = boFalse;

    StartCurrent2();
    memset(&mpboReadyCan, 0, sizeof(mpboReadyCan));
    if (StartCurrent(0) == 0)
    {
      fCurrent = 0;
      Work(); OK();

      bProgram = 0; wProgram = 0;
      cbShowTime = 2;
    }
  }
*/
}

/*
void    NextCurrent(void)
{
  Clear();

  LoadCurrDigital(ibDig);
  ibPort = diCurr.ibPort;

  switch (diCurr.bDevice)
  {
#ifndef SKIP_D
    case 4:  QueryCloseD(0); break;
#endif
#ifndef SKIP_K
    case 14:
    case 13: QueryCloseK();  break;
#endif
#ifndef SKIP_L
    case 16:
    case 17: QueryCloseK();  break;
#endif
#ifndef SKIP_P
    case 21: QueryCloseP();  break;
#endif
#ifndef SKIP_Q
    case 22: QueryCloseQ();  break;
#endif
#ifndef SKIP_U
    case 26: QueryCloseU();  break;
#endif
  }

  mpSerial[diCurr.ibPort] = SER_BEGIN;

  if (StartCurrent(ibDig+1) == 0)       // ����� ��������
  {
    SetCurr(DEV_BEGIN);

    fCurrent = 0;
    MakeContacts1();
    MakeContacts4();
    StopCurrent2();
    Work(); OK();

    bProgram = 0; wProgram = 0;
    cbShowTime = 2;

    ibPortPause = 0xFF;

    bDelayPhone2 = 3;
    enModbusCurrent = (boErrorCurrent == boFalse) ? MB1_READY : MB1_ERROR;
  }
}



void    MakeCurrent(void)
{
  ShowLo(szPowerOK); Delay(200);

  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      mpbCurrent2Curr[ibCan/8] |= (0x80 >> ibCan%8);

      if (boMntEscS == boTrue)
      {
        mpreEsc_S[ibCan] = mpreValueCntHou[ibCan] * mpdwBase[ibCan];
        mptiEsc_S[ibCan] = *PGetCurrTimeDate();
      }

      mpboReadyCan[ibCan] = boTrue;

      mpwTrue[ibCan]++;
      if (mpboBase[ibCan] == boFalse)
      {
        mpboBase[ibCan] = boTrue;

        mpdwBase[ibCan] = mpdwBaseDig[ diPrev.ibLine ];
        mpreBase[ibCan] = 0;
        mptiBase[ibCan] = *PGetCurrTimeDate();
        mptiOffs[ibCan] = tiOffs;
      }
      else
      {
        tiDig = *PGetCurrTimeDate();
        tiAlt = mptiBase[ibCan];

        if (CompareAltDig(0x07) == 1)           // ����������: ����, �����, ���
          dwBuffC = 0;
        else
          dwBuffC = (ulong)24*3600;

        dwUpdate = mpdwBaseDig[ GetDigitalLine(ibCan) ] - mpdwBase[ibCan];
        mpdwBase[ibCan] = mpdwBaseDig[ GetDigitalLine(ibCan) ];

        tiAlt = tiDig;
        dwBuffC += GetSecondIndex();
        tiAlt = mptiBase[ibCan];
        dwBuffC -= GetSecondIndex();

        mptiBase[ibCan] = tiDig;
        mptiOffs[ibCan] = tiOffs;

        mptiBaseOK[ibCan] = *PGetCurrTimeDate();

        if ((dwBuffC > 0) && (dwBuffC < 1800))
          mpreBase[ibCan] += (real)180*dwUpdate/dwBuffC;

        dwUpdate = mpreBase[ibCan];
        mpreBase[ibCan] -= dwUpdate;

        if (dwUpdate > 100) mpwMore100[ibCan]++;
        if (dwUpdate > 1000) mpwMore1000[ibCan]++;
        if (dwUpdate > 10000) mpwMore10000[ibCan]++;

        if (dwUpdate > 0xFFFF)                  // ������������
          mpwMore[ibCan]++;
        else
        if (dwUpdate < 0)                       // ���
          mpwLess[ibCan]++;
        else
        {
          mpwImpMntCan[ (bMINUTES+ibSoftMnt-1) % bMINUTES ][ibCan] = (uint)dwUpdate;
          MakeSpecCurrent();
        }
      }
    }
  }

  NextCurrent();
}



void    ErrorCurrent(void)
{
  boErrorCurrent = boTrue;
  SaveDisplay();

  ShowHi(szWarning);
  sprintf(szLo,"������� %02bX.%02bX.%02bX",(uchar)(GetCurr() / 0x100),(uchar)(GetCurr() % 0x100),(uchar)mpSerial[ibPort]);
  LongBeep();

  DelayMsg();
  LoadDisplay();

  // ��������� ���������� ������ ������, ������������� �������� ��������
  LoadCurrDigital(ibDig);
  for (ibCan=0; ibCan<bCANALS; ibCan++)
  {
    LoadPrevDigital(ibCan);
    if (CompareCurrPrevLines() == 1)
    {
      mpboReadyCan[ibCan] = boTrue;

      mptiBaseError[ibCan] = *PGetCurrTimeDate();
      mpwFalse[ibCan]++;
    }
  }

  SetCurr(DEV_BEGIN);
  NextCurrent();
}

#endif
 */
