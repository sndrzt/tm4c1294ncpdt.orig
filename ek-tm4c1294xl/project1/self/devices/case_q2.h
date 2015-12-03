#ifndef SKIP_Q

    case DEV_START_Q3:
      ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q3);
      break;

    case DEV_OPENCANAL_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q3:
      Clear(); ShowPercent(51);

      cbRepeat = bMINORREPEATS;
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q3);
      break;

    case DEV_OPTION_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_Q3);
        }
      }
      break;

    case DEV_POSTOPTION_Q3:
      ShowPercent(52);

      cbRepeat = bMINORREPEATS;
      QueryEnergySpecQ();
      SetCurr(DEV_ENERGY_Q3);
      break;

    case DEV_ENERGY_Q3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyQ();
        ReadCurrentQ();
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEnergySpecQ();
          SetCurr(DEV_ENERGY_Q3);
        }
      }
      break;


    case DEV_START_Q2:
      if ((boControlQ == boFalse) && (fCurrCtrlHou == 1))
      {
        ShowLo(szCorrectQ1);
        QueryCorrectQ();
        SetCurr(DEV_CORRECT_Q2);
      }
      else MakePause(DEV_OPEN_Q2);
      break;

    case DEV_CORRECT_Q2:
      ShowLo(szCorrectQ2);
      MakePause(DEV_OPEN_Q2);
      break;

    case DEV_OPEN_Q2:
      Clear(); ShowPercent(50);

      cbRepeat = bMINORREPEATS;
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_Q2);
      break;

    case DEV_OPENCANAL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadOpenK();
        MakeLongPause(DEV_POSTOPENCANAL_Q2, 1);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_Q2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_Q2:
      Clear(); ShowPercent(51);

      cbRepeat = bMINORREPEATS;
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q2);
      break;

    case DEV_OPTION_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_Q2);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionQ();
          SetCurr(DEV_OPTION_Q2);
        }
      }
      break;

    case DEV_POSTOPTION_Q2:
      ShowPercent(52);

      cbRepeat = bMINORREPEATS;
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_Q2);
      break;

    case DEV_PASSWORD_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if ((boControlQ != boFalse) && (fCurrCtrlHou == 1))
          MakePause(DEV_POSTPASSWORD_Q2);
        else
          MakePause(DEV_POSTCORRECT_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryPasswordK();
          SetCurr(DEV_PASSWORD_Q2);
        }
      }
      break;

    case DEV_POSTPASSWORD_Q2:
      ShowPercent(53);

      cbRepeat = bMINORREPEATS;
      QueryTimeSpecK();
      SetCurr(DEV_TIME_Q2);
      break;

    case DEV_TIME_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadTimeAltK();
        tiDig = tiAlt;
        MakePause(DEV_POSTTIME_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeSpecK();
          SetCurr(DEV_TIME_Q2);
        }
      }
      break;

    case DEV_POSTTIME_Q2:
      ShowPercent(54);

      cbRepeat = bMINORREPEATS;
      QueryDateSpecK();
      SetCurr(DEV_DATE_Q2);
      break;

    case DEV_DATE_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadDateAltK();
        tiDig = tiAlt;
        MakePause(DEV_POSTDATE_Q2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryDateSpecK();
          SetCurr(DEV_DATE_Q2);
        }
      }
      break;


    case DEV_POSTDATE_Q2:
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
        { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_Q2); }
        else if (GetHouIndex() == (tiAlt.bHour*2 + tiAlt.bMinute/30))           // ������� ���������
        { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_Q2); }
        else
        { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
      }
      break;


    case DEV_CONTROL_Q2:
      cbRepeat = bMINORREPEATS;
      QueryControlK();
      SetCurr(DEV_POSTCONTROL_Q2);
      break;

    case DEV_POSTCONTROL_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTCORRECT_Q2);
      else
      {
        if (cbRepeat == 0) MakePause(DEV_POSTCORRECT_Q2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlK();
          SetCurr(DEV_POSTCONTROL_Q2);
        }
      }
      break;


    case DEV_POSTCORRECT_Q2:
      iwMajor = 0;
      ibMinor = 0;

      InitHeaderQ();

      cbRepeat = bMINORREPEATS;
      QueryHeaderQ();
      SetCurr(DEV_HEADER_Q2);
      break;

    case DEV_HEADER_Q2:
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
              MakePause(DEV_DATA_Q2);
          }
        }
        else
        {
          ReadHeaderQ();

          iwMajor = 0;                                  // ���� ���� ��������� ������
          MakePause(DEV_POSTHEADER_Q2);
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

          QueryHeaderQ();
          SetCurr(DEV_HEADER_Q2);
        }
      }
      break;

    case DEV_POSTHEADER_Q2:
      if (++ibMinor < ibMinorMax)
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      else
      {
        ibMinor = 0;
        if (ReadDataQ() == 0)
          DoneProfile();
        else
          MakePause(DEV_DATA_Q2);
      }
      break;

    case DEV_DATA_Q2:
      if (wBaseCurr > wHOURS)
        DoneProfile();
      else
      {
        cbRepeat = bMINORREPEATS;
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      break;

#endif

