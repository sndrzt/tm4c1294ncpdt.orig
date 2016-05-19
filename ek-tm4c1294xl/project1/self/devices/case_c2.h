
#ifndef SKIP_C

    case DEV_START_C2:
      cbCorrects = 0;

      cbRepeat = GetMaxRepeats();
      QueryOpenC();
      SetCurr(DEV_OPENCANAL_C2);
      break;

    case DEV_OPENCANAL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK)/* && (ReadResultC() == 1)*/)
      {
        if (fCurrCtrl == true)
          MakePause(DEV_POSTOPENCANAL_C2);
        else
          MakePause(DEV_POSTCORRECT_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenC();
          SetCurr(DEV_OPENCANAL_C2);
        }
      }
      break;

    case DEV_POSTOPENCANAL_C2:
      Clear(); ShowLo(szRepeats);
      sprintf(szLo+8,"%1u",cbCorrects+1); DelayInf();

      cbRepeat = GetMaxRepeats();
      QueryTimeC();
      SetCurr(DEV_TIME_C2);
      break;

    case DEV_TIME_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        MakePause(DEV_POSTTIME_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_TIME_C2);
        }
      }
      break;


    case DEV_POSTTIME_C2:
      {
        ulong dwSecond1 = GetSecondIndex(tiValueC);
        ulong dwSecond2 = GetSecondIndex(tiCurr);

        if (DifferentDay(tiValueC, tiCurr))
        { ShowLo(szBadDates); DelayMsg(); ErrorProfile(); }                       // ���� �� ���������, ��������� ����������
        else
        {
          ShowDigitalDeltaTime(ibDig, dwSecond1, dwSecond2);

          if (AbsLong(dwSecond1 - dwSecond2) < GetCorrectLimit())                 // ��� ���������
          { ShowLo(szCorrectNo); DelayInf(); MakePause(DEV_POSTCORRECT_C2); }
          else if (GetCurrHouIndex() == (tiValueC.bHour*2 + tiValueC.bMinute/30)) // ������� ���������
          { ShowLo(szCorrectYes); DelayInf(); MakePause(DEV_CONTROL_C2);  }
          else
          { ShowLo(szCorrectBig); DelayMsg(); ErrorProfile(); }                   // ������� ������� ������� ������, ��������� ����������
        }
      }
      break;

    case DEV_CONTROL_C2:
      if (++cbCorrects > 3)
        MakePause(DEV_POSTCORRECT_C2);
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryControlC();
        SetCurr(DEV_POSTCONTROL_C2);
      }
      break;

    case DEV_POSTCONTROL_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadResultC() == 1))
        MakePause(DEV_POSTOPENCANAL_C2);
      else
      {
        if (cbRepeat == 0)
          MakePause(DEV_POSTOPENCANAL_C2);   // �� !
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryControlC();
          SetCurr(DEV_POSTCONTROL_C2);
        }
      }
      break;


    case DEV_POSTCORRECT_C2:
      cbRepeat = GetMaxRepeats();
      QueryVersionC();
      SetCurr(DEV_VERSION_C2);
      break;

    case DEV_VERSION_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadVersionC();

        if (boHideMessages == false)
          MakeLongPause(DEV_POSTVERSION_C2, 1);
        else
          MakePause(DEV_POSTVERSION_C2);
      }
      else
      {
        if (cbRepeat == 0) ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryVersionC();
          SetCurr(DEV_VERSION_C2);
        }
      }
      break;

    case DEV_POSTVERSION_C2:
      cbRepeat = GetMaxRepeats();
      QueryTimeC();
      SetCurr(DEV_VALUE_C2);
      break;

    case DEV_VALUE_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        tiValueC = ReadTimeC();
        dwValueC = DateToHouIndex(tiValueC);
        MakePause(DEV_POSTVALUE_C2);
      }
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryTimeC();
          SetCurr(DEV_VALUE_C2);
        }
      }
      break;

    case DEV_POSTVALUE_C2:
//      if (mpbHouCheck[ibDig] != 0)
//      {
//        Clear(); sprintf(szLo+2,"��������: %bu",mpbHouCheck[ibDig]);
//        MakeLongPause(DEV_INIT_61_C2, 1);
//      }
//      else
      cbIteration = 0;
      if (boShortProfileC == false)
      {
        InitHeaderC6();

        StartReview();
        MakePause(DEV_DATA_6_C2);
      }
      else
      {
        InitHeaderC1();

        StartReview();
        MakePause(DEV_DATA_1_C2);
      }
      break;


    case DEV_DATA_6_C2:
      cbRepeat = GetMaxRepeats();
      QueryHeaderC6();
      SetCurr(DEV_HEADER_6_C2);
      break;

    case DEV_HEADER_6_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTHEADER_6_C2);
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_6_C2);
      }
      break;

    case DEV_ERROR_6_C2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryIdC();
        SetCurr(DEV_POSTERROR_6_C2);
      }
      break;

    case DEV_POSTERROR_6_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC6();
          SetCurr(DEV_HEADER_6_C2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_6_C2);
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

          QueryIdC();
          SetCurr(DEV_POSTERROR_6_C2);
        }
      }
      break;

    case DEV_POSTHEADER_6_C2:
      switch (ReadReviewC6()) {
        case REVIEW_REPEAT: {
          MakePause(DEV_DATA_6_C2);
          break;
        }
        case REVIEW_SUCCESS: {
          cbIteration = 0;
          if (ReadHeaderC6() == 0)
            DoneProfile();
          else {
            StartReview();
            if (fReviewReadId == true)
              MakePause(DEV_ID_6_C2);
            else
              MakePause(DEV_DATA_6_C2);
          }
          break;
        }
        case REVIEW_ERROR: {
          ErrorProfile();
          break;
        }
        default: ASSERT(false);
      }
      break;

    case DEV_ID_6_C2:
      cbRepeat = GetMaxRepeats();
      QueryIdC();
      SetCurr(DEV_POSTID_6_C2);
      break;

    case DEV_POSTID_6_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadIdC() == 1))
        MakePause(DEV_DATA_6_C2);
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTID_6_C2);
        }
      }
      break;


    case DEV_DATA_1_C2:
      cbRepeat = GetMaxRepeats();
      QueryHeaderC1();
      SetCurr(DEV_HEADER_1_C2);
      break;

    case DEV_HEADER_1_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        cbIteration = 0;
        if ((IndexInBuff() == 6) && (InBuff(1) == 0x83) && (InBuff(2) == 0x24) && (InBuff(3) == 0x05)) // ��� ��������� ������
        {
          if (ReadHeaderC1_Shutdown() == 0)
            DoneProfile();
          else
            MakePause(DEV_DATA_1_C2);
        }
        else // ���� ��������� ������
        {
          MakePause(DEV_POSTHEADER_1_C2);
        }
      }
      else
      {
        ShowLo(szFailure1);
        MakePause(DEV_ERROR_1_C2);
      }
      break;

    case DEV_ERROR_1_C2:
      mpcwOutput1[ibDig]++; //Beep();

      if (++cbIteration > bMINORREPEATS) ErrorProfile();
      else
      {
        cbRepeat = GetMaxRepeats();
        QueryIdC();
        SetCurr(DEV_POSTERROR_1_C2);
      }
      break;

    case DEV_POSTERROR_1_C2:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        if (ReadIdC() == 1)
        {
          QueryHeaderC1();
          SetCurr(DEV_HEADER_1_C2);
        }
        else
        {
          ShowLo(szFailure2);
          MakePause(DEV_ERROR_1_C2);
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

          QueryIdC();
          SetCurr(DEV_POSTERROR_1_C2);
        }
      }
      break;

    case DEV_POSTHEADER_1_C2:
      switch (ReadReviewC1()) {
        case REVIEW_REPEAT: {
          MakePause(DEV_DATA_1_C2);
          break;
        }
        case REVIEW_SUCCESS: {
          if (ReadHeaderC1() == 0)
            DoneProfile();
          else {
            StartReview();
            if (fReviewReadId == true)
              MakePause(DEV_ID_1_C2);
            else
              MakePause(DEV_DATA_1_C2);
          }
          break;
        }
        case REVIEW_ERROR: {
          ErrorProfile();
          break;
        }
        default: ASSERT(false);
      }
      break;

    case DEV_ID_1_C2:
      cbRepeat = GetMaxRepeats();
      QueryIdC();
      SetCurr(DEV_POSTID_1_C2);
      break;

    case DEV_POSTID_1_C2:
      if ((mpSerial[ibPort] == SER_GOODCHECK) && (ReadIdC() == 1))
        MakePause(DEV_DATA_1_C2);
      else
      {
        if (cbRepeat == 0)
          ErrorProfile();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryIdC();
          SetCurr(DEV_POSTID_1_C2);
        }
      }
      break;

#endif
