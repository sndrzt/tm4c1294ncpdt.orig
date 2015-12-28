
#ifndef SKIP_U

    case DEV_START_U3:
      Clear(); ShowPercent(50);

      cbRepeat = GetMaxRepeats();
      QueryOpenK();
      SetCurr(DEV_OPENCANAL_U3);
      break;

    case DEV_OPENCANAL_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPENCANAL_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOpenK();
          SetCurr(DEV_OPENCANAL_U3);
        }
      }
      break;

    case DEV_POSTOPENCANAL_U3:
      Clear(); ShowPercent(51);

      cbRepeat = GetMaxRepeats();
      QueryOptionU();
      SetCurr(DEV_OPTION_U3);
      break;

    case DEV_OPTION_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
        MakePause(DEV_POSTOPTION_U3);
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryOptionK();
          SetCurr(DEV_OPTION_U3);
        }
      }
      break;

    case DEV_POSTOPTION_U3:
      Clear(); ShowPercent(52);

      ibLineU = 0;
      if (SkipLine(ibDig, ibLineU) == true)
      {
        ReadEnergyU_SkipLine(ibLineU);
        ibLineU++;
      }

      cbRepeat = GetMaxRepeats();
      QueryEngSpecU(ibLineU);
      SetCurr(DEV_ENERGY_U3);
      break;

    case DEV_ENERGY_U3:
      if (mpSerial[ibPort] == SER_GOODCHECK)
      {
        ReadEnergyU(ibLineU);

        if (SkipLine(ibDig, ibLineU+1) == true)
        {
          ReadEnergyU_SkipLine(ibLineU+1);
          ibLineU++;
        }

        uchar bMaxLine = GetMaxLine(ibDig);
        if (++ibLineU < bMaxLine)
        {
          Clear(); ShowPercent(52+ibLineU);
          QueryEngSpecU(ibLineU);
          SetCurr(DEV_ENERGY_U3);
        }
        else
          ReadCurrentU(bMaxLine);
      }
      else
      {
        if (cbRepeat == 0) ErrorCurrent();
        else
        {
          ErrorLink();
          cbRepeat--;

          QueryEngSpecU(ibLineU);
          SetCurr(DEV_ENERGY_U3);
        }
      }
      break;

#endif
