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
cxDBEdit,
cxCustomData,
cxTreeView,
cxCheckBox,
dxNavBar,
dxNavBarCollns,
ComCtrls,
Utils,
DataManager,
uLkJSON,
AutoOps,
MyLog,
DataTrans,
TestCase;

procedure Init();
procedure DoProc(nCode,wParam,lParam: DWORD);
procedure DoProcMouse(nCode: Integer; wParam:Integer; lParam: LongInt);
procedure GetData(hOp: HWND);
procedure PostData();

implementation

var
  roopCount: Integer;
  strTab: string;
  curProcessID,injectProcessID: Cardinal;
  mCOpsManager: COpsManager;
  mGridCount: Integer;
  mTestCase: CTestCase;


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
  if curProcessID<>injectProcessID then
  Exit;

  DataManager.Init();
  mCOpsManager := COpsManager.Create;
  mTestCase := CTestCase.Create;
  mGridCount :=0;
//  GetLoginData();
//  TestJson();

//h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//DataManager.GetWindowsData(h);


//  ≤‚ ‘øÿº˛¿‡–Õ
//  h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//  TestWindows(h);
    mTestCase.StartTest();


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
       bRet:=ClassNameContains(p.hwnd, Utils.cntOpSaveCls);
       bRet1:=ControlTextContains(p.hwnd, Utils.cntOpSave);
       if bRet and bRet1 then
       begin
        ShowMessageFmt('%s', ['-------click save']);
        GetData(p.hwnd);
       // PostData();
       end;

       bRet1:=ControlTextContains(p.hwnd, Utils.cntOpSure);
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
         bRet:=ClassNameContains(HWND(pcwp.lParam), Utils.cntOpSaveCls);
         bRet1:=ControlTextContains(HWND(pcwp.lParam), Utils.cntOpSave);
         if bRet and bRet1 then
         begin
          ShowMessageFmt('%s', ['-------click save']);
          GetData(HWND(pcwp.lParam));                                         
         // PostData();
         end;

         bRet1:=ControlTextContains(HWND(pcwp.lParam), Utils.cntOpSure);
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
  DataManager.GetWindowsData(h);
end;

procedure PostData();
begin
  DataManager.PostData();
end;

end.
