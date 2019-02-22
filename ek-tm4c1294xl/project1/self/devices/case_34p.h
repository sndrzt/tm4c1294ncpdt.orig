#ifndef SKIP_34

    case DEV_START_34P:
      MakePause(DEV_PREVTIME_34P);
      break;


    case DEV_PREVTIME_34P:
      cbRepeat = MaxRepeats();
      QueryTime34();
      SetCurr(DEV_TIME_34P);
      break;

    case DEV_TIME_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        SetTimeCurr34(ReadTime34());
        MakePause(DEV_POSTTIME_34P);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTime34();
          SetCurr(DEV_TIME_34P);
        }
      }
      break;

    case DEV_POSTTIME_34P:
      {
        ulong dwSecond1 = GetSecondIndex(GetTimeCurr34());
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(GetTimeCurr34(), tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); } // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);
          //dwCorrectW = dwSecond2 - dwSecond1;

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit()) // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_34); }
          else if (AbsLong(dwSecond1 - dwSecond2) < 10) // ������� ���������
          {
            ShowLo(szCorrectYes); DelayInf();
            MakePause(DEV_POSTCORRECT_34);
          }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); } // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_POSTCORRECT_34:
      MakePause(DEV_PREVOPEN_34P);
      break;


    case DEV_PREVOPEN_34P:
      InitProfileOpen34();

      cbRepeat = MaxRepeats();
      QueryProfileOpen34();
      SetCurr(DEV_OPEN_34P);
      break;

    case DEV_OPEN_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_PREVREAD_34P);
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileOpen34();
          SetCurr(DEV_OPEN_34P);
        }
      }
      break;

    case DEV_PREVREAD_34P:
      InitProfileRead34();

      cbRepeat = MaxRepeats();
      QueryProfileRead34();
      SetCurr(DEV_READ_34P);
      break;

    case DEV_READ_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        if (ReadProfileRead34()) {
          cbRepeat = MaxRepeats();
          QueryProfileRead34();
          SetCurr(DEV_READ_34P);
        } else {
          MakePause(DEV_PREVCLOSE_34P);
        }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileRead34();
          SetCurr(DEV_READ_34P);
        }
      }
      break;

    case DEV_PREVCLOSE_34P:
      cbRepeat = MaxRepeats();
      QueryProfileClose34();
      SetCurr(DEV_CLOSE_34P);
      break;

    case DEV_CLOSE_34P:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        if (ReadProfileClose34()) {
          cbRepeat = MaxRepeats();
          QueryProfileOpen34();
          SetCurr(DEV_OPEN_34P);
        } else {
          DoneProfile();
        }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryProfileClose34();
          SetCurr(DEV_CLOSE_34P);
        }
      }
      break;

#endif
