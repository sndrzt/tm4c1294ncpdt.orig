program traffic4;

uses
  Forms,
  main in 'main.pas' {frmMain};

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := ' ����i����� ����i�� ';
  Application.CreateForm(TfrmMain, frmMain);
  Application.Run;
end.
