unit View;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, cxStyles, cxCustomData, cxGraphics, cxFilter,
  cxData, cxDataStorage, cxEdit, DB, cxDBData, cxGridLevel, cxClasses,
  cxControls, cxGridCustomView, cxGridCustomTableView, cxGridTableView,
  cxGridDBTableView, cxGrid, cxLookAndFeelPainters, cxButtons, cxImageComboBox,
  cxBlobEdit, DBTables,
  Utils, dxSkinsCore, dxSkinBlack, dxSkinBlue, dxSkinCaramel, dxSkinCoffee,
  dxSkinDarkSide, dxSkinGlassOceans, dxSkiniMaginary, dxSkinLilian,
  dxSkinLiquidSky, dxSkinLondonLiquidSky, dxSkinMcSkin, dxSkinMoneyTwins,
  dxSkinOffice2007Black, dxSkinOffice2007Blue, dxSkinOffice2007Green,
  dxSkinOffice2007Pink, dxSkinOffice2007Silver, dxSkinPumpkin,
  dxSkinSilver, dxSkinStardust, dxSkinSummer2008, dxSkinsDefaultPainters,
  dxSkinValentine, dxSkinXmas2008Blue, dxSkinscxPCPainter, Menus,
  cxContainer, cxGroupBox, cxLabel;

type
  TForm1 = class(TForm)
    cxGrid1DBTableView1: TcxGridDBTableView;
    cxGrid1Level1: TcxGridLevel;
    cxGrid1: TcxGrid;
    ds1: TDataSource;
    tbl1: TTable;
    cxgrdbclmnGrid1DBTableView1SpeciesNo: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1Category: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1Common_Name: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1SpeciesName: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1Lengthcm: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1Length_In: TcxGridDBColumn;
    btn2: TcxButton;
    cxgrpbx1: TcxGroupBox;
    cxgrpbx2: TcxGroupBox;
    cxgrpbx3: TcxGroupBox;
    cxlbl1: TcxLabel;
    cxlbl2: TcxLabel;
    btn1: TcxButton;
    txt1: TStaticText;

    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
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
//  ShowMessageFmt('%s:%x', ['MainThreadID:', MainThreadID]);
//for c := 0 to strngrd1.ColCount - 1 do
//    for r := 0 to strngrd1.RowCount - 1 do
//      strngrd1.Cells[c,r] := Format('%d-%d', [r,c]);
end;

procedure GetTcxGridData(grid: TcxGrid);
var
  FileName: string;
  cxGridDBTableView: TcxGridDBTableView;
  cxView, cxView1: TcxCustomGridView;
  i,j, nRowCount,nColCount: Integer;
  rowInfo: TcxRowInfo;
  s, s1: string;
  p: Pointer ;
  sStr: ShortString;

begin
    if grid.ActiveLevel = nil then
      ShowMessageFmt('%s',['ActiveLevel is nil'])
    else
    begin
       cxView := grid.FocusedView;
       if cxView=cxView1 then
        ShowMessageFmt('%s',['ActiveLevelGridView is FocusedView']);


       if cxView=nil then
         ShowMessageFmt('%s',['cxGridView is nil']);

       if cxView <> nil then
       begin
//         if cxGridView.DataController=nil then
//            ShowMessageFmt('%s',['DataController is nil'])
//         else
//         begin
//           ShowMessageFmt('%s',['DataController is not nil']);
//           nRowCount := cxGridView.DataController.RowCount;
//           ShowMessageFmt('%s%d',['GetRecordCount:', nRowCount]);
//           ItemCount := cxGridView.DataController.ItemCount;
//           ShowMessageFmt('%s%d',['GetItemCount:', nColCount]);
//           for i := 0 to nRowCount-1 do
//           begin
//           if i<>0 then s := Concat(s, Char(13), Chr(10));
//            for j:=0 to ItemCount do
//             begin
//               s1 := Format('%s    ', [cxGridView.DataController.Values[i,j]]);
//               s := Concat(s, s1);
//             end;
//           end;
//         end;
//            SaveData(ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName,
//            s, True);
       p := cxView.ClassInfo();
       sStr := cxView.ClassName();
        if cxView is TcxGridTableView then
          ShowMessageFmt('%s',['cxGridView is TcxGridTableView']);

        if cxView is TcxGridDBTableView then
          ShowMessageFmt('%s',['cxGridView is TcxGridDBTableView']);

       grid.FocusedView :=  TcxGridTableView(grid.FocusedView);

        if grid.FocusedView is TcxGridTableView then
          ShowMessageFmt('%s',['FocusedView is TcxGridTableView']);
          
//       FileName := ExtractFilePath(ParamStr(0))+ Utils.cntSaveGridDataName;
//       cxExportGrid4Link.ExportGrid4ToText(FileName, grid, True, True);
       end;
    end;





//   FileName := ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName;
//   ExportGridToText(FileName, grid, True, True);
end;

procedure DoWindows(h: HWND);
var
  buf: array[0..255] of Char; {这个缓冲区是获取类名用的, 如果不需要可以删除}
  s: AnsiString;
  s1: AnsiString;
  nRet: Integer;
  nRet1: Integer;
  count: Integer;
  Grid, Grid1: TStringGrid;
  tGrid: TcxGrid;
  cxBtn: TcxButton;
  i: Integer;
  tcl: TWinControl;
begin
 GetClassName(h, buf, Length(buf));
  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl=nil then
  MessageBox(0, 'FindControl nil', buf, MB_OK);
  nRet := Pos('TcxGrid', buf);
  nRet1 := Pos('TcxGridSite', buf);
  if (nRet<>0) and (nRet1=0) then
    begin
    tGrid := TcxGrid(Utils.GetInstanceFromhWnd(h));
    ShowMessageFmt('%s:%d', [buf, h]);
    if(tGrid<>nil)  then
      begin
        s1 := Format('tcxgrid  find: %x view count = %d ', [Integer(@tGrid), tGrid.Levels.Count]);
        MessageBox(0, PAnsiChar(AnsiString(s1)), 'tcxgrid', MB_OK);
        GetTcxGridData(tGrid);
      end
  end;
end;


procedure GetChildWindows(h: HWND);
  begin
  DoWindows(h);
  h := GetWindow(h, GW_CHILD); {第一个子窗口}
  while h <> 0 do
  begin
    GetChildWindows(h); {递归}
    h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
  end;
  end;
  

procedure TForm1.btn2Click(Sender: TObject);
 var
   nIndex: Integer;
   nCount: Integer;
  vCol: TcxGridDBColumn;
  vImgCom: TcxImageComboBoxItem;
  i,j: integer;
  FileName: string;
  cxView: TcxCustomGridView;
  sStr: ShortString;
  h: HWND;
begin
//    cxView := cxGrid1.ActiveLevel.GridView;
//    nCount := cxView.DataController.GetRecordCount();
//
//    ShowMessageFmt('%s %d', ['TcxGrid:', nCount]);
//    sStr := cxView.ClassName();
//
//    FileName := ExtractFilePath(ParamStr(0))+'aaa.txt';
//    ExportGrid4ToText(FileName, cxGrid1, True, True);
////  ShowMessageFmt('%s:%x:%d', ['TcxGrid:', Integer(@cxGrid1), i]);
////  ShowMessageFmt('%s:%x', ['TStringGrid:', Integer(@strngrd1)]);
    h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
    ShowMessageFmt('%s:%d', ['window:', h]);
      GetChildWindows(h);
end;

end.









