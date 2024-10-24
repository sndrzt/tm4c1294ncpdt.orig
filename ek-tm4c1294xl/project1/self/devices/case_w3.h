
#ifndef SKIP_W

    case DEV_START_W3:
      ShowPercent(50);

      cbRepeat = MaxRepeats();
      QueryOpenW();
      SetCurr(DEV_OPENCANAL_W3);
      break;

    case DEV_OPENCANAL_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_W3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenW();
          SetCurr(DEV_OPENCANAL_W3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_W3:
      ShowPercent(51);

      cbRepeat = MaxRepeats();
      QueryOptionW();
      SetCurr(DEV_OPTION_W3);
      break;

    case DEV_OPTION_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ibLineW = 0;
        MakePause(DEV_POSTOPTION_W3);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionW();
          SetCurr(DEV_OPTION_W3);
        }
      }
      break;

    case DEV_POSTOPTION_W3:
      ShowPercent(52+ibLineW);

      cbRepeat = MaxRepeats();
      QueryEngAbsW_Current(ibLineW);
      SetCurr(DEV_ENERGY_W3);
      break;

    case DEV_ENERGY_W3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTENERGY_W3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngAbsW_Current(ibLineW);
          SetCurr(DEV_ENERGY_W3);
        }
      }
      break;

    case DEV_POSTENERGY_W3:
      ReadEngW(ibLineW);

      if (++ibLineW < MAX_LINE_W)
        MakePause(DEV_POSTOPTION_W3);
      else
        ReadCurrentW();
      break;

#endif
