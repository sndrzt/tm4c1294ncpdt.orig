
#ifndef SKIP_U

    case DEV_START_36P:
      if ((boControlQ == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT_36P);
      else
        MakePause(DEV_OPEN_36P);
      break;

    case DEV_PREVCORRECT_36P:
      if (tiCurr.bSecond < bMINORCORRECT_U) {
        MakePause(DEV_CORRECT_36P);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_36P);
      }
      break;

    case DEV_CORRECT_36P:
      ShowLo(szCorrectQ1);
      QueryCorrectU();
      SetCurr35(DEV_OPEN_36P);
      break;

    case DEV_OPEN_36P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenK();
      SetCurr35(DEV_OPENCANAL_36P);
      break;

    case DEV_OPENCANAL_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_36P, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr35(DEV_OPENCANAL_36P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_36P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionU();
      SetCurr35(DEV_OPTION_36P);
      break;

    case DEV_OPTION_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_36P);
        else
          MakePause(DEV_POSTPASSWORD_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionU();
          SetCurr35(DEV_OPTION_36P);
        }
      }
      break;

    case DEV_POSTOPTION_36P:
      ShowPercent(52);

      cbRepeat = MaxRepeats();
      QueryPasswordK();
      SetCurr35(DEV_PASSWORD_36P);
      break;

    case DEV_PASSWORD_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_36P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr35(DEV_PASSWORD_36P);
        }
      }
      break;

    case DEV_POSTPASSWORD_36P:
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_36P);
      else
        MakePause(DEV_POSTCORRECT_36P);
      break;

    case DEV_PREVTIME_36P:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpecK();
      SetCurr35(DEV_TIME_36P);
      break;

    case DEV_TIME_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr35(DEV_TIME_36P);
        }
      }
      break;

    case DEV_POSTTIME_36P:
      ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryDateSpecK();
      SetCurr35(DEV_DATE_36P);
      break;

    case DEV_DATE_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_36P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr35(DEV_DATE_36P);
        }
      }
      break;


    case DEV_POSTDATE_36P:
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_36P); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_36P); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_36P:
      cbRepeat = MaxRepeats();
      QueryControlK();
      SetCurr35(DEV_POSTCONTROL_36P);
      break;

    case DEV_POSTCONTROL_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_36P);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_36P);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr35(DEV_POSTCONTROL_36P);
        }
      }
      break;


    case DEV_POSTCORRECT_36P:
      if (boPlcUFlag == false)
        MakePause(DEV_PREVHEADER_36P);
      else
      {
        Clear();
        sprintf(szLo+4, "����: %u", bPlcUSize);
        MakeLongPause(DEV_PREVHEADER_U4, 1);
      }
      break;

    case DEV_PREVHEADER_36P:
      iwMajor = 0;
      InitHeaderU();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == 1)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = MaxRepeats();
      QueryHeaderU();
      SetCurr35(DEV_HEADER_36P);
      break;

    case DEV_HEADER_36P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 3)                        // ���� ��� ��������� ������
        {
          if (iwMajor >= 31)                           // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            sprintf(szLo," ���������: %-4u   ",++iwMajor);

            iwDigHou = (wHOURS+iwHardHou-wBaseCurr*48)%wHOURS;
            ShowProgressDigHou();

            NewBoundsAbs16(++wBaseCurr);

            if (wBaseCurr >= wHOURS/48)
              DoneProfile();
            else if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_36P);
          }
        }
        else
        {
          ReadHeaderU();

          if (SkipLine(ibDig, ibLineU+1) == 1)
          {
            ReadHeaderU_SkipLine(ibLineU+1);
            ibLineU++;
          }

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_36P);
        }
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeaderU();
          SetCurr35(DEV_HEADER_36P);
        }
      }
      break;

    case DEV_POSTHEADER_36P:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderU();
        SetCurr35(DEV_HEADER_36P);
      }
      else
      {
        if (ReadDataU() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_36P);
      }
      break;

    case DEV_DATA_36P:
      if (wBaseCurr > wHOURS/48)
        DoneProfile();
      else
      {
        ibLineU = 0;

        if (SkipLine(ibDig, ibLineU) == 1)
        {
          ReadHeaderU_SkipLine(ibLineU);
          ibLineU++;
        }

        cbRepeat = MaxRepeats();
        QueryHeaderU();
        SetCurr35(DEV_HEADER_36P);
      }
      break;

#endif
