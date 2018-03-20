unit Logic;

interface
uses
Windows,Messages,Dialogs,
cxGrid,Controls,SysUtils,cxGridDBTableView,cxGridTableView,cxGridCustomView,
cxCheckBox,dxNavBar,dxNavBarCollns,Utils,DataManager,uLkJSON,AutoOps,MyLog,
DataTrans,TestCase, OpManager;
type
{ TLogic }

  TLogic = class(TObject)
  private
    roopCount: Integer;
    strTab: string;
    curProcessID,injectProcessID: Cardinal;
    mCOpsManager: COpsManager;
    mTOpManager: TOpManager;
    mGridCount: Integer;
    mTestCase: CTestCase;
    mDataManager: TDataManager;
  public
    procedure GetLoginData;
    procedure Init();
    procedure DoProc(nCode,wParam,lParam: DWORD);
    procedure DoProcMouse(nCode: Integer; wParam:Integer; lParam: LongInt);
    procedure DoProcKey(nCode: Integer; wParam:Integer; lParam: LongInt);
    procedure GetData(hOp: HWND);
    procedure PostData();
    procedure DoCatchWindowData();

  end;

implementation
  


procedure TLogic.GetLoginData();
var
  h:HWND;
begin
  h := FindWindow(nil,PAnsiChar(Utils.cntLoginWind));
  mDataManager.GetLoginData(h);
end;

procedure TLogic.Init();
var
  h: HWND;
  i: Integer;
begin
  mTestCase := CTestCase.Create;
  curProcessID:=GetCurrentProcessId();
  injectProcessID:=Utils.GetProcessIDByName(Utils.cntInjectExe);
  
  if curProcessID<>injectProcessID then
  Exit;

  mDataManager:=TDataManager.Create;
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

procedure TLogic.DoProcKey(nCode: Integer; wParam:Integer; lParam: LongInt);
var
  pEvt: PEventMsg;
  vKey:Cardinal;
begin
   if curProcessID=injectProcessID  then
   begin
     CMyLog.DebugI(Format('wParam = %x, lparaj=%x', [wParam, lParam]));
     if (wParam=VK_RETURN) and (lParam=$1c0001) then
     begin
       CMyLog.DebugI('-----------------VK_RETURN');
     end;
   end;
end;

procedure TLogic.DoProcMouse(nCode: Integer;wParam:WPARAM; lParam: LPARAM);
var
  p: PMouseHookStruct;
  bRet, bRet1: Boolean;
begin
   if curProcessID=injectProcessID  then
   begin
      p := PMouseHookStruct(lParam);
      if wParam=WM_LBUTTONUP then
      begin
       bRet:=ClassNameContains(p.hwnd, Utils.cntOpSaveCls);
       bRet1:=ControlTextContains(p.hwnd, Utils.cntOpSave);
       if bRet and bRet1 then
       begin
        //ShowMessageFmt('%s', ['-------click save']);
        GetData(p.hwnd);
       end;

       bRet1:=ControlTextContains(p.hwnd, Utils.cntOpSure);
       if bRet and bRet1 then
       begin
         GetLoginData();
       end;
      end;
   end;

end;

procedure TLogic.DoProc(nCode,wParam,lParam: DWORD);
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

procedure TLogic.GetData(hOp: HWND);
var
  h:HWND;
begin
  h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
  mDataManager.UpdateCurInfoType(h, hOp);
  mDataManager.CleanData();
  mDataManager.GetWindowsData(h);
end;

procedure TLogic.PostData();
begin
  mDataManager.PostData();
end;

procedure TLogic.DoCatchWindowData();
begin
  mTestCase.TestCatchWindowsData();  
end;

end.

