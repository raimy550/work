unit view;

interface
uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Logic, Utils, dxCntner, dxEditor, dxEdLib, Menus,
  cxLookAndFeelPainters, cxButtons;

   function setHook:Boolean;stdcall;external 'DphHookDll.dll';

type
  TForm1 = class(TForm)
    btn1: TButton;
    btn2: TButton;
    dxdt1: TdxEdit;
    txt1: TStaticText;
    btn3: TcxButton;
    btn4: TcxButton;
    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
    procedure btn3Click(Sender: TObject);
    procedure btn4Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;
  exeName: String;

implementation

{$R *.dfm}

procedure TForm1.FormCreate(Sender: TObject);
begin
  Application.ShowMainForm := False;
  setHook();
end;

procedure TForm1.btn1Click(Sender: TObject);
begin
  Logic.DoStart();
end;

procedure TForm1.btn2Click(Sender: TObject);
var
  bRet:  Boolean;
begin
  bRet := setHook();

end;

procedure TForm1.btn3Click(Sender: TObject);
var
  openDlg: TOpenDialog;
  str: String;
begin
  openDlg := TOpenDialog.Create(Self);
  if openDlg.Execute then
  begin
    dxdt1.Text := openDlg.FileName;
    exeName := ExtractFileName(openDlg.FileName);
  end;
end;

procedure TForm1.btn4Click(Sender: TObject);
var
  bRet:  Boolean;
begin
  bRet := setHook();
end;

end.
