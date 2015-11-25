
#ifndef SKIP_U

    case DEV_START_U2:
      if ((boControlQ == false) && (fCurrCtrl == true))
        MakePause(DEV_PREVCORRECT_U2);
      else
        MakePause(DEV_OPEN_U2);
      break;

    case DEV_PREVCORRECT_U2:
      if (tiCurr.bSecond < bMINORCORRECT_U) {
        MakePause(DEV_CORRECT_U2);
      } else {
        ShowTimeOneE(ibDig);
        MakePause(DEV_PREVCORRECT_U2);
      }
      break;

    case DEV_CORRECT_U2:
      ShowLo(szCorrectQ1);
      QueryCorrectU();
      SetCurr(DEV_OPEN_U2);
      break;

    case DEV_OPEN_U2:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U2);
      break;

    case DEV_OPENCANAL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_U2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U2:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U2);
      break;

    case DEV_OPTION_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_U2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionU();
          SetCurr(DEV_OPTION_U2);
        }
      }
      break;

    case DEV_POSTOPTION_U2:
      ShowPercent(52);

      cbRepeat = GetMaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_U2);
      break;

    case DEV_PASSWORD_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if ((boControlQ != false) && (fCurrCtrl == true))
          MakePause(DEV_POSTPASSWORD_U2);
        else
          MakePause(DEV_POSTCORRECT_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_U2);
        }
      }
      break;

    case DEV_POSTPASSWORD_U2:
      ShowPercent(53);

      cbRepeat = GetMaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_U2);
      break;

    case DEV_TIME_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
        MakePause(DEV_POSTTIME_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_U2);
        }
      }
      break;

    case DEV_POSTTIME_U2:
      ShowPercent(54);

      cbRepeat = GetMaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_U2);
      break;

    case DEV_DATE_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
        MakePause(DEV_POSTDATE_U2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_U2);
        }
      }
      break;


    case DEV_POSTDATE_U2:
      {
        uint iwDay1 = GetDayIndexMD(tiDig.bMonth, tiDig.bDay);
        ulong dwSecond1 = GetSecondIndex(tiDig);

        uint iwDay2 = GetDayIndexMD(tiCurr.bMonth, tiCurr.bDay);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (iwDay1 != iwDay2)
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_U2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_U2); }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_U2:
      cbRepeat = GetMaxRepeats();
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_U2);
      break;

    case DEV_POSTCONTROL_U2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_U2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_U2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_U2);
        }
      }
      break;


    case DEV_POSTCORRECT_U2:
      if (boPlcUFlag == false)
        MakePause(DEV_PREVHEADER_U2);
      else
      {
        Clear();
        sprintf(szLo+4, "����: %u", bPlcUSize);
        MakeLongPause(DEV_PREVHEADER_U4, 1);
      }
      break;

    case DEV_PREVHEADER_U2:
      iwMajor = 0;
      InitHeaderU();

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == 1)
      {
        ReadHeaderU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = GetMaxRepeats();
      QueryHeaderU();
      SetCurr(DEV_HEADER_U2);
      break;

    case DEV_HEADER_U2:
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
              MakePause(DEV_DATA_U2);
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
          MakePause(DEV_POSTHEADER_U2);
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
          SetCurr(DEV_HEADER_U2);
        }
      }
      break;

    case DEV_POSTHEADER_U2:
      if (++ibLineU < bMaxLineU)
      {
        cbRepeat = GetMaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      else
      {
        if (ReadDataU() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_U2);
      }
      break;

    case DEV_DATA_U2:
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

        cbRepeat = GetMaxRepeats();
        QueryHeaderU();
        SetCurr(DEV_HEADER_U2);
      }
      break;

#endif
