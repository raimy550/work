unit View;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, Grids, cxStyles, cxCustomData, cxGraphics, cxFilter,
  cxData, cxDataStorage, cxEdit, DB, cxDBData, cxGridLevel, cxClasses,
  cxControls, cxGridCustomView, cxGridCustomTableView, cxGridTableView,
  cxGridDBTableView, cxGrid, cxLookAndFeelPainters, cxButtons, cxImageComboBox,
  cxBlobEdit, DBTables,
  Utils,Menus,
  cxContainer, cxGroupBox, cxLabel, cxTextEdit, cxMaskEdit, cxDropDownEdit,
  cxCalendar, cxDBEdit, ExtCtrls, dxNavBar,
  dxNavBarCollns, dxNavBarBase,
  ComCtrls, cxTreeView, dxSkinsCore, dxSkinsDefaultPainters,
  dxSkinscxPCPainter, dxSkinsdxNavBarPainter;

  function setHook:Boolean;stdcall;external 'DphHookDll.dll';

type
  TForm1 = class(TForm)
    cxGrid1DBTableView1: TcxGridDBTableView;
    cxGrid1Level1: TcxGridLevel;
    cxGrid1: TcxGrid;
    ds1: TDataSource;
    btn2: TcxButton;
    cxgrpbx1: TcxGroupBox;
    cxgrpbx2: TcxGroupBox;
    cxgrpbx3: TcxGroupBox;
    cxlbl1: TcxLabel;
    cxlbl2: TcxLabel;
    btn1: TcxButton;
    txt1: TStaticText;
    cxdtdt1: TcxDateEdit;
    cxdbdtdt1: TcxDBDateEdit;
    tbl1: TTable;
    tbl2: TTable;
    ds2: TDataSource;
    btn3: TcxButton;
    cxgrdbclmnGrid1DBTableView1EmpNo: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1LastName: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1FirstName: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1PhoneExt: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1HireDate: TcxGridDBColumn;
    cxgrdbclmnGrid1DBTableView1Salary: TcxGridDBColumn;
    dxnvbr1: TdxNavBar;
    dxnvbrgrpdxnvbr1Group1: TdxNavBarGroup;
    dxnvbrtmdxnvbr1Item1: TdxNavBarItem;
    dxnvbrgrpdxnvbr1Group2: TdxNavBarGroup;
    dxnvbrtmdxnvbr1Item2: TdxNavBarItem;
    dxnvbrtmdxnvbr1Item3: TdxNavBarItem;
    dxnvbrtmdxnvbr1Item4: TdxNavBarItem;
    dxnvbrtmdxnvbr1Item5: TdxNavBarItem;
    dxnvbrtmdxnvbr1Item6: TdxNavBarItem;
    dxnvbrgrpdxnvbr1Group3: TdxNavBarGroup;

    procedure btn1Click(Sender: TObject);
    procedure btn2Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure btn3Click(Sender: TObject);
  private
    { Private declarations }
    procedure InitView();
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}
procedure TForm1.FormCreate(Sender: TObject);
begin
   InitView();
   setHook();
end;

procedure TForm1.InitView();
var
  str: AnsiString;
  group: TdxNavBarGroup;
  bar: TdxNavBarItem;
  rect: TRect;
begin
//  cxdbdtdt1.Properties.DisplayFormat.FormatString = "yyyy-MM-dd HH:mm:ss";
//  cxdbdtdt1.Properties.DisplayFormat.FormatType = DevExpress.Utils.FormatType.DateTime;
//  cxdbdtdt1.Properties.EditFormat.FormatString = "yyyy-MM-dd HH:mm:ss";
//  cxdbdtdt1.Properties.EditFormat.FormatType = DevExpress.Utils.FormatType.DateTime;
//  cxdbdtdt1.Properties.Mask.EditMask = "yyyy-MM-dd HH:mm:ss";
//
//  cxdbdtdt1.Properties.VistaDisplayMode = DevExpress.Utils.DefaultBoolean.True;
//  cxdbdtdt1.Properties.VistaEditTime = DevExpress.Utils.DefaultBoolean.True;

//    cxdbdtdt1.SetTextBuf(PAnsiChar(Format('%s', ['2016-02-15 22:00:00'])));
//    group := dxnvbr1.Groups.Add;
//    group.Caption := 'group1'; 
//    bar := dxnvbr1.Items.Add;
//    bar.Caption := 'item1';
//    group.CreateLink(bar);
//
//    bar := dxnvbr1.Items.Add;
//    bar.Caption := 'item2';
//    group.CreateLink(bar);
     
    
end;

procedure TForm1.btn1Click(Sender: TObject);
var
   c,r, tmp: Integer;
   oldPoint,newPoint: TPoint;
   rect:TRect;
   point: TPoint;
begin
//  ShowMessageFmt('%s:%x', ['MainThreadID:', MainThreadID]);
//for c := 0 to strngrd1.ColCount - 1 do
//    for r := 0 to strngrd1.RowCount - 1 do
//      strngrd1.Cells[c,r] := Format('%d-%d', [r,c]);

//    GetCursorPos(oldPoint);
//    newPoint.X := oldPoint.X+40;
//    newPoint.Y := oldPoint.Y+10;
//  SetCursorPos(newPoint.X, newPoint.Y);  

//   setHook();
//   tmp := 0;
//   while (tmp<10*60) do
//   begin
//    Sleep(1000);
//    tmp := tmp +1;
//   end;

  GetWindowRect(dxnvbr1.Handle, rect);
  //ShowMessage(Format('---dxnv [%d,%d, %d,%d]',[rect.Left, rect.Top, rect.Right, rect.Bottom]));

  GetWindowRect(btn3.Handle, rect);
  point.X := rect.Left+10;
  point.Y := rect.Top+10;

  SetCursorPos(point.X, point.Y);
  mouse_event(MOUSEEVENTF_LEFTDOWN,point.x,point.y,0,0); 
  mouse_event(MOUSEEVENTF_LEFTUP,point.x,point.y,0,0); 
  
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

//    h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//    ShowMessageFmt('%s:%d', ['window:', h]);
//      GetChildWindows(h);

//    InitView();
//    nCount := dxnvbr1.Items.Count;
//    for i:=0 to nCount-1 do
//    begin
//      ShowMessageFmt('%d---%s', [i, dxnvbr1.Items[i].Caption]);
//    end;

    nCount := dxnvbr1.Groups.Count;
    for i:=0 to nCount-1 do
    begin
      ShowMessageFmt('%d---%s', [i, dxnvbr1.Groups[i].Caption]);
    end;
end;

procedure TForm1.btn3Click(Sender: TObject);
var
  time: TDateTime;
begin
//  cxdbdtdt1.SetTextBuf(PAnsiChar(Format('%s', ['2000-02-15 22:00:00'])));

//  cxdbdtdt1.Date := StrToDatetime('2000-02-15 22:00:00');

    cxdtdt1.Date :=  StrToDate('2000-02-15');
    ShowMessage('---------test');
end;

end.









