unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids;

type
  TForm1 = class(TForm)
    strngrd1: TStringGrid;
    btn1: TButton;
    procedure btn1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.btn1Click(Sender: TObject);
var
   c,r: Integer;
begin
for c := 0 to strngrd1.ColCount - 1 do
    for r := 0 to strngrd1.RowCount - 1 do
      strngrd1.Cells[c,r] := Format('%d-%d', [r,c]);
end;

end.
