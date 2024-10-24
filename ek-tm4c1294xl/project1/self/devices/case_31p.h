#ifndef SKIP_31

    case DEV_START_31P:
      cbCorrects = 0;

      cbRepeat = MaxRepeats();
      QueryOpen31();
      SetCurr(DEV_OPENCANAL_31P);
      break;

    case DEV_OPENCANAL_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadOpen31() == 0)
          ErrorProfile();
        else if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_31P);
        else
          MakePause(DEV_POSTCORRECT_31P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpen31();
          SetCurr(DEV_OPENCANAL_31P);
        }
      }
      break;

    case DEV_POSTOPENCANAL_31P:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = MaxRepeats();
      QueryTime31();
      SetCurr(DEV_TIME_31P);
      break;

    case DEV_TIME_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiProfile31 = ReadTime31();
        MakePause(DEV_POSTTIME_31P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime31();
          SetCurr(DEV_TIME_31P);
        }
      }
      break;


    case DEV_POSTTIME_31P:
      {
        ulong dwSecond1 = GetSecondIndex(tiProfile31);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiProfile31, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_31P); }
          else if (GetCurrHouIndex() == (tiProfile31.bHour*2 + tiProfile31.bMinute/30))       // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_31P);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_31P:
      if (++cbCorrects > bCORRECTS)
        MakePause(DEV_POSTCORRECT_31P);
      else
      {
        cbRepeat = MaxRepeats();
        QueryControl31(tiCurr);
        SetCurr(DEV_POSTCONTROL_31P);
      }
      break;

    case DEV_POSTCONTROL_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_31P);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTCORRECT_31P); // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControl31(tiCurr);
          SetCurr(DEV_POSTCONTROL_31P);
        }
      }
      break;


    case DEV_POSTCORRECT_31P:
      Clear();

      cbRepeat = MaxRepeats();
      QueryTop31();
      SetCurr(DEV_TOP_31P);
      break;

    case DEV_TOP_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTTOP_31P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTop31();
          SetCurr(DEV_TOP_31P);
        }
      }
      break;

    case DEV_POSTTOP_31P:
      if (ReadTop31() == false) DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader31();
        SetCurr(DEV_HEADER_31P);
      }
      break;

    case DEV_HEADER_31P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_31P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryHeader31();
          SetCurr(DEV_HEADER_31P);
        }
      }
      break;

    case DEV_POSTHEADER_31P:
      if (ReadHeader31() == false)
        DoneProfile();
      else if (DecIndex31() == false)
        DoneProfile();
      else
      {
        cbRepeat = MaxRepeats();
        QueryHeader31();
        SetCurr(DEV_HEADER_31P);
      }
      break;

#endif
