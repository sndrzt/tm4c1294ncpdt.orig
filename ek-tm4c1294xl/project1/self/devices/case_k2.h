#ifndef SKIP_K

    case DEV_START_K2:
      if ((boControlK == boFalse) && (fCurrCtrlHou == 1))
        MakePause(DEV_PREVCORRECT2_K2);
      else
        MakePause(DEV_OPEN_K2);
      break;

    case DEV_PREVCORRECT2_K2:
      if (tiCurr.bSecond < bMINORCORRECT_K) {
        MakePause(DEV_CORRECT2_K2);
      } else {
        ShowTimeOneE();
        MakePause(DEV_PREVCORRECT2_K2);
      }
      break;

    case DEV_CORRECT2_K2:
      ShowLo(szCorrectQ1);
      QueryCorrectK();
      SetCurr(DEV_POSTCORRECT2_K2);
      break;

    case DEV_POSTCORRECT2_K2:
      //ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_K2);
      break;

    case DEV_OPEN_K2:
      Clear(); ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_K2);
      break;

    case DEV_OPENCANAL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_K2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_K2:
      Clear(); ShowPercent(51);

      cbRepeat = bMINORREPEATS;
      QueryOptionK();
      SetCurr(DEV_OPTION_K2);
      break;

    case DEV_OPTION_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_K2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_K2);
        }
      }
      break;

    case DEV_POSTOPTION_K2:
      ShowPercent(52);

      cbRepeat = bMINORREPEATS;
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_K2);
      break;

    case DEV_PASSWORD_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if ((boControlK != boFalse) && (fCurrCtrlHou == 1))
          MakePause(DEV_POSTPASSWORD_K2);
        else
          MakePause(DEV_POSTCORRECT_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_K2);
        }
      }
      break;

    case DEV_POSTPASSWORD_K2:
      ShowPercent(53);

      cbRepeat = bMINORREPEATS;
      QueryTimeSpecK();
      SetCurr(DEV_TIME_K2);
      break;

    case DEV_TIME_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltK();
        tiDig = tiAlt;
        MakePause(DEV_POSTTIME_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_K2);
        }
      }
      break;

    case DEV_POSTTIME_K2:
      ShowPercent(54);

      cbRepeat = bMINORREPEATS;
      QueryDateSpecK();
      SetCurr(DEV_DATE_K2);
      break;

    case DEV_DATE_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadDateAltK();
        tiDig = tiAlt;
        MakePause(DEV_POSTDATE_K2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_K2);
        }
      }
      break;


    case DEV_POSTDATE_K2:
      wBuffD  = GetDayIndex();              // ���������� ���� � ������ ���� �������� ��������
      dwBuffC = GetSecondIndex();           // ���������� ������ �������� ��������

      tiAlt = tiCurr;                       // ������� �����/���� ���������

      if (wBuffD != GetDayIndex())
      { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
      else
      {
        if (dwBuffC > GetSecondIndex())                                         // ���������� ��������� ������� �������� �������� �����
          ShowDeltaNeg();
        else
          ShowDeltaPos();

        if (dwBuffC < bMINORCORRECT_K)                                          // ��� ���������
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_K2); }
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // ������� ���������
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_K2); }
        else
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
      }
      break;


    case DEV_CONTROL_K2:
      cbRepeat = bMINORREPEATS;
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_K2);
      break;

    case DEV_POSTCONTROL_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_K2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_K2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_K2);
        }
      }
      break;


    case DEV_POSTCORRECT_K2:
      iwMajor = 0;
      ibMinor = 0;

      wBaseCurr = 0;
      tiDigPrev = tiCurr;

      cbRepeat = bMINORREPEATS;
      QueryHeaderK();
      SetCurr(DEV_HEADER_K2);
      break;

    case DEV_HEADER_K2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (IndexInBuff() == 10)                        // ���� ��� ��������� ������
        {
          if (iwMajor >= 480)                           // ���� ������� ���� ��������� ������� �����
            DoneProfile();
          else
          {
            for (i=0; i<48; i++)
            {
              wBaseCurr++;

              sprintf(szLo," ���������: %-4u   ",++iwMajor);

              iwDigHou = (wHOURS+iwHardHou-wBaseCurr)%wHOURS;
              ShowProgressDigHou();
            }

            if (MakeStopHou(0) == 0)
              DoneProfile();
            else
              MakePause(DEV_DATA_K2);
          }
        }
        else
        {
          ReadHeaderK();

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_K2);
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

          QueryHeaderK();
          SetCurr(DEV_HEADER_K2);
        }
      }
      break;

    case DEV_POSTHEADER_K2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataK() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_K2);
      }
      break;

    case DEV_DATA_K2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderK();
        SetCurr(DEV_HEADER_K2);
      }
      break;

#endif
