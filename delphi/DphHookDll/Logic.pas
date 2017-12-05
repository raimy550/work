unit Logic;

interface
uses
Windows,
Messages,
Dialogs,

cxGrid,Controls,SysUtils,cxGridDBTableView,cxGridTableView,cxGridCustomView,
cxCheckBox,dxNavBar,dxNavBarCollns,Utils,DataManager,uLkJSON,AutoOps,MyLog,
DataTrans,TestCase, OpManager;

procedure Init();
procedure DoProc(nCode,wParam,lParam: DWORD);
procedure DoProcMouse(nCode: Integer; wParam:Integer; lParam: LongInt);
procedure DoProcKey(nCode: Integer; wParam:Integer; lParam: LongInt);
procedure GetData(hOp: HWND);
procedure PostData();

procedure DoCatchWindowData();

implementation

var
  roopCount: Integer;
  strTab: string;
  curProcessID,injectProcessID: Cardinal;
  mCOpsManager: COpsManager;
  mTOpManager: TOpManager;
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
  mTestCase := CTestCase.Create;
  curProcessID:=GetCurrentProcessId();
  injectProcessID:=Utils.GetProcessIDByName(Utils.cntInjectExe);
  
  if curProcessID<>injectProcessID then
  Exit;

  DataManager.Init();
  mCOpsManager := COpsManager.Create;
  mTOpManager:= TOpManager.Create;
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

procedure DoProcKey(nCode: Integer; wParam:Integer; lParam: LongInt);
var
  pEvt: PEventMsg;
  vKey:Cardinal;
begin
   if curProcessID=injectProcessID  then
   begin
    //pEvt := Pointer(DWord(lParam));
      
     CMyLog.DebugI(Format('wParam = %x, lparaj=%x', [wParam, lParam]));
     if (wParam=VK_RETURN) and (lParam=$1c0001) then
     begin
       CMyLog.DebugI('-----------------VK_RETURN');
     end;
//    if wParam=WM_KEYUP  then
//    begin
//      CMyLog.DebugI('--------------WM_KEYUP');
//      pEvt := PEventMsg(lParam);
//      vKey := LOBYTE(pEvt.message);
//      CMyLog.DebugI(Format('---vkey = %x', [vKey]));
//      if vKey=VK_RETURN then
//      begin
//         CMyLog.DebugI('-----------------VK_RETURN');
//      end;
//    end;

    
    //CMyLog.DebugI(Format('keyProc--msg:%x',[pEvt.message]));
  
//    if pEvt.message = WM_KEYDOWN then
//    begin
//       vKey := LOBYTE(pEvt.paramL);
//       CMyLog.DebugI(Format('WM_KEYDOWN--value:%x',[vKey]));
//    end;
   end;
end;

procedure DoProcMouse(nCode: Integer;wParam:WPARAM; lParam: LPARAM);
var
  p: PMouseHookStruct;
  bRet, bRet1: Boolean;
begin
   if curProcessID=injectProcessID  then
   begin
      p := PMouseHookStruct(lParam);
      //DebugOut(Format('code=%x, wParam=%x, lParam(hWnd=%x, x=%d, y=%d)', [nCode, wParam, p.hwnd, p.pt.X, p.pt.Y]));
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
 //      Utils.DebugOut(Format('-------WndProc: ncode:%x, wparam=%x, lparam=%x', [nCode, wParam, lParam]));
     if (nCode = HC_ACTION) then
    begin
      pcwp := PCWPStruct(lParam);
//      if (pcwp.message<>132) then
//      begin
////        Utils.LogOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
////        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
//        Utils.DebugOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
//        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
//      end;

      Utils.DebugOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
//      if (pcwp.message=$287) and (pcwp.wParam=$17) then
//      begin
////        Utils.LogOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
////        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
////        ShowMessageFmt('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
////        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]);
////        ShowMessageFmt('%s---%d', ['WM_COMMAND', HWND(pcwp.lParam)]);
////       DebugOut(Format('%s---%d', ['WM_COMMAND', HWND(pcwp.lParam)]));
//         Utils.DebugOut(Format('hWnd=%x, wParam=%x, lParam(Msg=%x, Wparam=%x, Lparam=%x)',
//        [pcwp.hwnd,  wParam, pcwp.message, pcwp.wParam, pcwp.lParam]));
//         bRet:=ClassNameContains(HWND(pcwp.lParam), Utils.cntOpSaveCls);
//         bRet1:=ControlTextContains(HWND(pcwp.lParam), Utils.cntOpSave);
//         if bRet and bRet1 then
//         begin
//          ShowMessageFmt('%s', ['-------click save']);
//          GetData(HWND(pcwp.lParam));                                         
//         // PostData();
//         end;
//
//         bRet1:=ControlTextContains(HWND(pcwp.lParam), Utils.cntOpSure);
//         if bRet and bRet1 then
//         begin
//         GetLoginData();
//         end;
//      end;
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

procedure DoCatchWindowData();
begin
  mTestCase.TestCatchWindowsData();  
end;

end.
