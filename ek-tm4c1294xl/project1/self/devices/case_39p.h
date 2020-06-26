
#ifndef SKIP_39

    case DEV_START_39P:
      MakePause(DEV_DISC_O_39P);
      break;


    case DEV_DISC_O_39P:
      Clear(); ShowPercent(50);

      cbRepeat = MaxRepeats();
      Query39_DISC_Profile();
      SetCurr(DEV_DISC_I_39P);
      break;

    case DEV_DISC_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_SNRM_O_39P);
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_SNRM_O_39P:
      Clear(); ShowPercent(51);

      cbRepeat = MaxRepeats();
      Query39_SNRM();
      SetCurr(DEV_SNRM_I_39P);
      break;

    case DEV_SNRM_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        MakePause(DEV_AARQ_O_39P);
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_AARQ_O_39P:
      Clear(); ShowPercent(52);

      cbRepeat = MaxRepeats();
      Query39_AARQ_Profile();
      SetCurr(DEV_AARQ_I_39P);
      break;

    case DEV_AARQ_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateFrame_Profile()) {}
          Error39(220+0);
          ErrorProfile();
        } else {
          MakePause(DEV_RR_AARQ_O_39P);
        }  
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_RR_AARQ_O_39P:
      Clear(); ShowPercent(53);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_RR_AARQ_I_39P);
      break;

    case DEV_RR_AARQ_I_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Error39(220+0);
          MakePause(DEV_9_39P);
        }  
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_9_39P:
      Clear(); ShowPercent(54);

      cbRepeat = MaxRepeats();
      QueryTime39_Profile();
      SetCurr(DEV_10_39P);
      break;

    case DEV_10_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateIframe_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          ReadTime39_Profile();
          MakePause(DEV_11_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_11_39P:
      Clear(); ShowPercent(55);

      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_12_39P);
      break;

    case DEV_12_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (!ValidateSframe_Profile()) {
          Error39(220+0);
          ErrorProfile();
        } else {
          MakePause(DEV_13_39P);
        }  
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_13_39P:
      InitProfile39_Profile();
      MakePause(DEV_13a_39P);
      break;


    case DEV_13a_39P:
      cbRepeat = MaxRepeats();
      QueryProfile39_Profile();
      SetCurr(DEV_14_39P);
      break;

    case DEV_14_39P:
      Read1_Profile();
      MakePause(DEV_15_39P);
      break;

    case DEV_15_39P:
        if (!LastSegmentDMLS()) {
          MakePause(DEV_16_39P);
        } else {          
          MakePause(DEV_18_39P);
        }
      break;


    case DEV_16_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_17_39P);
      break;

    case DEV_17_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Read2_Profile();
          MakePause(DEV_15_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_18_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_19_39P);
      break;

    case DEV_19_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Read3_Profile();
          if (UseBlocks_Profile()) {
            QueryNextBlock39_Profile();
            MakePause(DEV_19a_39P);
          } else {
            MakePause(DEV_27_39P);
          }
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_19a_39P:
      Read4_Profile();
      MakePause(DEV_20_39P);
      break;

    case DEV_20_39P:
        if (!LastSegmentDMLS()) {
          MakePause(DEV_21_39P);
        } else {          
          MakePause(DEV_25_39P);
        }
      break;


    case DEV_21_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_22_39P);
      break;

    case DEV_22_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          Error39(220+0);
          ErrorProfile();
        } else {
          Read5_Profile();
          MakePause(DEV_20_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_25_39P:
      cbRepeat = MaxRepeats();
      Query39_RR_Profile();
      SetCurr(DEV_26_39P);
      break;

    case DEV_26_39P:
      if (mpSerial[ibPort] == SER_GOODCHECK) {
        if (false/*!ValidateSframe_Profile()*/) {
          Error39(220+0);
          ErrorProfile();
        } else {
          MakePause(DEV_27_39P);
        }
      } else {
        Error39(220+0);
        ErrorProfile();
      }
      break;


    case DEV_27_39P:
      if (FinishProfile39_Profile())
        MakePause(DEV_13a_39P);
      else
        DoneProfile();
      break;

#endif
