
#ifndef SKIP_Q

    case DEV_START_Q2:
      if ((boControlQ == false) && (fCurrCtrl == true))
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

      cbRepeat = MaxRepeats();
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

      cbRepeat = MaxRepeats();
      QueryOptionQ();
      SetCurr(DEV_OPTION_Q2);
      break;

    case DEV_OPTION_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (HasPasswordK())
          MakePause(DEV_POSTOPTION_Q2);
        else
          MakePause(DEV_POSTPASSWORD_Q2);
      }
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

      cbRepeat = MaxRepeats();
      QueryPasswordK();
      SetCurr(DEV_PASSWORD_Q2);
      break;

    case DEV_PASSWORD_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTPASSWORD_Q2);
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
      if ((boControlQ != false) && (fCurrCtrl == true))
        MakePause(DEV_PREVTIME_Q2);
      else
        MakePause(DEV_POSTCORRECT_Q2);
      break;

    case DEV_PREVTIME_Q2:
      ShowPercent(53);

      cbRepeat = MaxRepeats();
      QueryTimeSpecK();
      SetCurr(DEV_TIME_Q2);
      break;

    case DEV_TIME_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadTimeK();
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

      cbRepeat = MaxRepeats();
      QueryDateSpecK();
      SetCurr(DEV_DATE_Q2);
      break;

    case DEV_DATE_Q2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiDig = ReadDateK(tiDig);
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
      {
        ulong dwSecond1 = GetSecondIndex(tiDig);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiDig, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_Q2); }
          else if (GetCurrHouIndex() == (tiDig.bHour*2 + tiDig.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_Q2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;


    case DEV_CONTROL_Q2:
      cbRepeat = MaxRepeats();
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
      ibLineQ = 0;

      InitHeaderQ();

      cbRepeat = MaxRepeats();
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
            uchar h;
            for (h=0; h<48; h++)
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
          ReadHeaderQ(ibLineQ);

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
      if (++ibLineQ < MAX_LINE_Q)
      {
        cbRepeat = MaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      else
      {
        ibLineQ = 0;
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
        cbRepeat = MaxRepeats();
        QueryHeaderQ();
        SetCurr(DEV_HEADER_Q2);
      }
      break;

#endif

