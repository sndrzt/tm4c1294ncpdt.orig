unit main;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls, OoMisc, AdPort, IniFiles, Buttons;

type
  TfrmMain = class(TForm)
    panClient: TPanel;
    panBottom: TPanel;
    Comm1: TApdComPort;
    Comm2: TApdComPort;
    pgcMain: TPageControl;
    tbsTerminal: TTabSheet;
    memTerminal: TMemo;
    lblComm1: TLabel;
    cmbComm1: TComboBox;
    cmbBaud1: TComboBox;
    cmbComm2: TComboBox;
    cmbBaud2: TComboBox;
    lblComm2: TLabel;
    panRigth2: TPanel;
    btbCrealInfo: TBitBtn;
    btbSaveInfo: TBitBtn;
    sd_RichToFile: TSaveDialog;
    tbsSettings: TTabSheet;
    lblDelay: TLabel;
    edtDelay: TEdit;
    updDelay: TUpDown;
    edtDelayDispersion: TEdit;
    updDelayDispersion: TUpDown;
    lblDelayDispersion: TLabel;
    lblPercent: TLabel;
    tmrDelay: TTimer;
    tmrTimeout1: TTimer;
    tmrTimeout2: TTimer;
    Edit1: TEdit;
    UpDown1: TUpDown;
    procedure FormResize(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure SetBaud1(dwBaud: longint);
    procedure SetComm1(wComNumber: word);
    procedure SetBaud2(dwBaud: longint);
    procedure SetComm2(wComNumber: word);
    procedure Terminal(stT: string);
    procedure ShowComNumber(wComNumber: word);
    procedure ShowData(mbBuff: array of byte; Count: word);
    procedure Comm1TriggerAvail(CP: TObject; Count: Word);
    procedure Comm2TriggerAvail(CP: TObject; Count: Word);
    procedure cmbComm1Change(Sender: TObject);
    procedure cmbComm2Change(Sender: TObject);
    procedure cmbBaud1Change(Sender: TObject);
    procedure cmbBaud2Change(Sender: TObject);
    procedure SaveMemo(Memo: TMemo; stName: string);
    procedure btbSaveInfoClick(Sender: TObject);
    procedure btbCrealInfoClick(Sender: TObject);
    procedure tmrDelayTimer(Sender: TObject);
    procedure Transfer(const CommSrc: TApdComPort; const CommDst: TApdComPort);
    procedure tmrTimeout1Timer(Sender: TObject);
    procedure tmrTimeout2Timer(Sender: TObject);
    procedure UpDown1Changing(Sender: TObject; var AllowChange: Boolean);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frmMain:      TfrmMain;

  FIni:         TIniFile;

  mpbInBuff:            array[0..$FFFF] of byte;

  datStart,
  datStop:              TDateTime;
  wComNumberPrev:       word = 100;

const
  stCOMM1:              string  = '���� �';
  stCOMM2:              string  = '���� �';
  stCOMNUMBER:          string  = '�����';
  stBAUD:               string  = '���������';
  stSETTINGS:           string  = '������';
  sDELAY:               string  = 'Delay';
  sDELAY_DISPERSION:    string  = 'DelayDispersion';

  dwDEFAULT_BAUD:       longint = 9600;

implementation

uses Generics.Collections, support, fifo;

var
  Queue: TObjectQueue<TItem>;

{$R *.DFM}

procedure TfrmMain.FormResize(Sender: TObject);
begin
  if Height < 200 then Height := 200;
  if Width  < 500 then Width  := 500;
end;

procedure TfrmMain.FormShow(Sender: TObject);
var
  stIni: string;
begin
  try
    stIni := ChangeFileExt(ParamStr(0),'.ini');
    FileSetAttr(stIni, FileGetAttr(stIni) and not faReadOnly);
  except
  end;

  try
    FIni := TIniFile.Create(ChangeFileExt(ParamStr(0),'.ini'));

    SetComm1( FIni.ReadInteger(stCOMM1, stCOMNUMBER, 1) );
    SetBaud1( FIni.ReadInteger(stCOMM1, stBAUD,      dwDEFAULT_BAUD) );

    SetComm2( FIni.ReadInteger(stCOMM2, stCOMNUMBER, 2) );
    SetBaud2( FIni.ReadInteger(stCOMM2, stBAUD,      dwDEFAULT_BAUD) );

    updDelay.Position := FIni.ReadInteger(stSETTINGS, sDELAY, 0);
    updDelayDispersion.Position := FIni.ReadInteger(stSETTINGS, sDELAY_DISPERSION, 0);
  except
    ErrBox('������� ��� �������i ���������');
  end;

  with Comm1 do begin
    if (ComNumber < 1) or (ComNumber > 8) then begin
      ErrBox('��������� ����� ����� �: COM' + IntToStr(ComNumber));
      ComNumber := 1;
    end;
    cmbComm1.ItemIndex := ComNumber - 1;

    if cmbBaud1.Items.IndexOf( IntToStr(Baud) ) = -1 then begin
      ErrBox('���������� ��������� ����� �: ' + IntToStr(Baud));
      Baud := dwDEFAULT_BAUD;
    end;
    cmbBaud1.ItemIndex := cmbBaud1.Items.IndexOf( IntToStr(Baud) );
  end;

  with Comm2 do begin
    if (ComNumber < 1) or (ComNumber > 8) then begin
      ErrBox('��������� ����� ����� �: COM' + IntToStr(ComNumber));
      ComNumber := 2;
    end;
    cmbComm2.ItemIndex := ComNumber - 1;

    if cmbBaud2.Items.IndexOf( IntToStr(Baud) ) = -1 then begin
      ErrBox('���������� ��������� ����� �: ' + IntToStr(Baud));
      Baud := dwDEFAULT_BAUD;
    end;
    cmbBaud2.ItemIndex := cmbBaud2.Items.IndexOf( IntToStr(Baud) );
  end;

  Comm1.Open := True;
  Comm2.Open := True;

  datStart := Now;
  datStop  := Now;

  pgcMain.ActivePage := tbsTerminal;

  tmrTimeout1.Interval := UpDown1.Position;
  tmrTimeout2.Interval := UpDown1.Position;

  Queue := TObjectQueue<TItem>.Create;
  Queue.OwnsObjects := true;
end;

procedure TfrmMain.FormClose(Sender: TObject; var Action: TCloseAction);
begin
  try
    with Comm1 do begin
      FIni.WriteInteger(stCOMM1, stCOMNUMBER, ComNumber);
      FIni.WriteInteger(stCOMM1, stBAUD,      Baud);
    end;

    with Comm2 do begin
      FIni.WriteInteger(stCOMM2, stCOMNUMBER, ComNumber);
      FIni.WriteInteger(stCOMM2, stBAUD,      Baud);
    end;

    FIni.WriteInteger(stSETTINGS, sDELAY, updDelay.Position);
    FIni.WriteInteger(stSETTINGS, sDELAY_DISPERSION, updDelayDispersion.Position);
  except
    ErrBox('������� ��� ���i������i ���������');
  end;
end;

procedure TfrmMain.SetComm1(wComNumber: word);
begin
  with Comm1 do begin
    try
      ComNumber := wComNumber;
    except
      ComNumber := 1;
      ErrBox('������� ��� ��������i ������ ����� �: COM' + IntToStr(wComNumber));
    end;
  end;
end;

procedure TfrmMain.SetBaud1(dwBaud: longint);
begin
  with Comm1 do begin
    try
      Baud := dwBaud;
    except
      Baud := dwDEFAULT_BAUD;
      ErrBox('������� ��� ��������i ��������i ����� �: ' + IntToStr(dwBaud));
    end;
  end;
end;

procedure TfrmMain.SetComm2(wComNumber: word);
begin
  with Comm2 do begin
    try
      ComNumber := wComNumber;
    except
      ComNumber := 2;
      ErrBox('������� ��� ��������i ������ ����� �: COM' + IntToStr(wComNumber));
    end;
  end;
end;

procedure TfrmMain.SetBaud2(dwBaud: longint);
begin
  with Comm2 do begin
    try
      Baud := dwBaud;
    except
      Baud := dwDEFAULT_BAUD;
      ErrBox('������� ��� ��������i ��������i ����� �: ' + IntToStr(dwBaud));
    end;
  end;
end;

procedure TfrmMain.Terminal(stT: string);
begin
  memTerminal.Lines.Append(stT);
end;

procedure TfrmMain.ShowComNumber(wComNumber: word);
var
  datNow: TDateTime;
begin
  datNow := Now;

  if (wComNumberPrev <> wComNumber) and (wComNumberPrev <> 100) then begin
    Terminal('');
    Terminal('\\ COM' + IntToStr(wComNumberPrev) + ':  ' + Time2Str(datStop - datStart) +
             '   COM' + IntToStr(wComNumberPrev) +
             '->COM'  + IntToStr(wComNumber) + ':  ' + Time2Str(datNow - datStop));
    datStart := datNow;
  end;

  if (wComNumberPrev <> wComNumber) then begin
    Terminal('');
    Terminal('\\ COM' + IntToStr(wComNumber));
  end;

  datStop := datNow;
  wComNumberPrev := wComNumber;
end;

procedure TfrmMain.ShowData(mbBuff: array of byte; Count: word);
begin
  Terminal(Buff2Str(mbBuff, Count));
end;

procedure ShowDelay;
var
  wDelay: word;
begin
  with frmMain do
  if updDelay.Position > 0 then begin
    wDelay := Round(updDelay.Position*(1 + (Random(updDelayDispersion.Position*2) - updDelayDispersion.Position)/100));
    Terminal('\\ �������� ' + IntToStr(wDelay) + ' ��.');
    Delay(wDelay);
  end;
end;

procedure TfrmMain.Transfer(const CommSrc: TApdComPort; const CommDst: TApdComPort);
var
  Count: word;
begin
  if CommSrc.InBuffUsed > 0 then begin
    Count := CommSrc.InBuffUsed;

    CommSrc.GetBlock(mpbInBuff, Count);
    Terminal('src COM' + IntToStr(CommSrc.ComNumber) + '   ' + Buff2Str(mpbInBuff, Count));

    if updDelay.Position = 0 then begin
      CommDst.PutBlock(mpbInBuff, Count);
      Terminal('dst COM' + IntToStr(CommDst.ComNumber) + '   ' + Buff2Str(mpbInBuff, Count));
    end
    else begin
      Terminal('push size ' + IntToStr(Queue.Count));
      Queue.Enqueue(TItem.Create(CommDst, ToBytes(mpbInBuff,COunt)));
    end;
  end;
end;

procedure TfrmMain.UpDown1Changing(Sender: TObject; var AllowChange: Boolean);
var
  w: word;
begin
  w := Round(UpDown1.Position * (1 + Random(20)/100));
  tmrTimeout1.Interval := w;
  tmrTimeout2.Interval := w;
end;

procedure TfrmMain.Comm1TriggerAvail(CP: TObject; Count: Word);
begin
  if UpDown1.Position = 0 then begin
    Transfer(Comm1, Comm2);
  end
  else begin
    Terminal('\\ restart 1 ' + Time2Str(Now));
    tmrTimeout1.Enabled := False;
    tmrTimeout1.Enabled := True;
  end;
end;

procedure TfrmMain.Comm2TriggerAvail(CP: TObject; Count: Word);
begin
  if UpDown1.Position = 0 then begin
    Transfer(Comm2, Comm1);
  end
  else begin
    Terminal('\\ restart 2 ' + Time2Str(Now));
    tmrTimeout2.Enabled := False;
    tmrTimeout2.Enabled := True;
  end;
end;

procedure TfrmMain.tmrDelayTimer(Sender: TObject);
var
  item: TItem;
  i: word;
begin
  if Queue.Count > 0  then begin
    Terminal('\\ �������� ' + IntToStr(tmrDelay.Interval) + ' ��.');
  end;
  tmrDelay.Interval := Round(updDelay.Position*(1 + (Random(updDelayDispersion.Position*2) - updDelayDispersion.Position)/100));

  if Queue.Count > 0  then begin
    Terminal('pop size ' + IntToStr(Queue.Count));
    item := Queue.Extract;
    Terminal('dst COM' + IntToStr(item.FComPort.ComNumber) + '   ' + Buff2Str(item.FData, Length(item.FData)));

    for i := 0 to Length(item.FData)-1 do begin
      item.FComPort.PutChar(AnsiChar(item.FData[i]));
    end;
  end;

end;

procedure TfrmMain.tmrTimeout1Timer(Sender: TObject);
begin
  Terminal('\\ timeout 1 ' + Time2Str(Now));
  tmrTimeout1.Enabled := False;
  Transfer(Comm1, Comm2);
end;

procedure TfrmMain.tmrTimeout2Timer(Sender: TObject);
begin
  Terminal('\\ timeout 2 ' + Time2Str(Now));
  tmrTimeout2.Enabled := False;
  Transfer(Comm2, Comm1);
end;

procedure TfrmMain.cmbComm1Change(Sender: TObject);
begin
  SetComm1(cmbComm1.ItemIndex + 1);
end;

procedure TfrmMain.cmbComm2Change(Sender: TObject);
begin
  SetComm2(cmbComm2.ItemIndex + 1);
end;

procedure TfrmMain.cmbBaud1Change(Sender: TObject);
begin
  with cmbBaud1 do begin
    try
      SetBaud1( StrToInt(Items.Strings[ItemIndex]) );
    except
      ErrBox('������� ��� �������i ��������i ����� �');
    end;
  end;
end;

procedure TfrmMain.cmbBaud2Change(Sender: TObject);
begin
  with cmbBaud2 do begin
    try
      SetBaud2( StrToInt(Items.Strings[ItemIndex]) );
    except
      ErrBox('������� ��� �������i ��������i ����� �');
    end;
  end;
end;

procedure TfrmMain.SaveMemo(Memo: TMemo; stName: string);
begin
  with sd_RichToFile,Memo do begin
    try
      InitialDir := ExtractFileDir(ParamStr(0));

      ForceDirectories(InitialDir);
      FileName := stName + '.txt';

      if Execute then Memo.Lines.SaveToFile(FileName);
    except
      ErrBox('������ ��� ���������� ������ !')
    end;
  end;
end;

procedure TfrmMain.btbSaveInfoClick(Sender: TObject);
begin
  SaveMemo(memTerminal, '������� ' + DateTime2Str(Now) + ' ');
end;

procedure TfrmMain.btbCrealInfoClick(Sender: TObject);
begin
  memTerminal.Clear;
end;

end.
