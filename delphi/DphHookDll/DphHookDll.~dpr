library DphHookDll;

{ Important note about DLL memory management: ShareMem must be the
  first unit in your library's USES clause AND your project's (select
  Project-View Source) USES clause if your DLL exports any procedures or
  functions that pass strings as parameters or function results. This
  applies to all strings passed to and from your DLL--even those that
  are nested in records and classes. ShareMem is the interface unit to
  the BORLNDMM.DLL shared memory manager, which must be deployed along
  with your DLL. To avoid using BORLNDMM.DLL, pass string information
  using PChar or ShortString parameters. }

uses
  Windows,
  Dialogs,
  SysUtils,
  Messages,
  Classes,
  Logic in 'Logic.pas',
  Utils in 'utils\Utils.pas',
  StrMap in 'utils\StrMap.pas',
  MyLog in 'utils\MyLog.pas',
  DataTrans in 'DataTrans.pas',
  YuYueInfo in 'YuYueInfo.pas',
  WeiTuoInfo in 'WeiTuoInfo.pas',
  LoginInfo in 'LoginInfo.pas',
  AutoOps in 'AutoOps.pas',
  TestCase in 'TestCase.pas',
  ConfigManager in 'ConfigManager.pas',
  OpBases in 'Ops\OpBases.pas',
  OpManager in 'Ops\OpManager.pas',
  OpSteps in 'Ops\OpSteps.pas',
  OpTypes in 'Ops\OpTypes.pas',
  uLkJSON in 'utils\uLkJSON.pas',
  BaseInfo in 'BaseInfo.pas',
  DataManager in 'DataManager.pas';

{$R *.res}
var
  hHookMouse, hHookKey, hHookWndProc:HHOOK;

function DllInit():Integer; stdcall;
begin
  Init();
  Result := 0;
end;

function hookProc(nCode,wParam,lParam: DWORD):DWORD;stdcall;
begin
  DoProc(nCode, wParam, lParam);
  Result:=CallNextHookEx(hHookWndProc,nCode,wParam,lParam);

end;

function mouseProc(nCode: Integer; wParam: WPARAM;lParam: LPARAM):DWORD;stdcall;
begin
  DoProcMouse(nCode, wParam, lParam);
  Result:=CallNextHookEx(hHookMouse,nCode,wParam,lParam);

end;
           
function keyProc(nCode: Integer; wParam: WPARAM;lParam: LPARAM):DWORD;stdcall;
begin

  DoProcKey(nCode, wParam, lParam);
  Result:=CallNextHookEx(hHookKey,nCode,wParam,lParam);

end;

function setHook():Boolean;stdcall;
begin
  //hHookWndProc:=SetWindowsHookEx(WH_CALLWNDPROC,@hookProc,HInstance,0);
  hHookMouse:=SetWindowsHookEx(WH_MOUSE,@mouseProc,HInstance,0);
  hHookKey := SetWindowsHookEx(WH_KEYBOARD,@keyProc,HInstance,0);
  Result:= (hHookMouse<>0) and (hHookKey<>0) and (hHookWndProc<>0);
end;

//É¾³ý¹³×Ó
function delHook:Boolean;stdcall;
begin
  Result:=UnhookWindowsHookEx(hHookMouse) and UnhookWindowsHookEx(hHookKey) and UnhookWindowsHookEx(hHookWndProc);
end;


procedure catchWindowData();
begin
  DoCatchWindowData();
end;


procedure DLLEntryPoint(Reason:Integer);

  begin
    case Reason of
      DLL_PROCESS_ATTACH:
      begin
      Logic.Init();
      //OutputDebugString('---------DLL_PROCESS_ATTACH');
      //ShowMessageFmt('-----------%s', ['DLL_PROCESS_ATTACH']);
      end;

      DLL_PROCESS_DETACH:
      delHook();

      DLL_THREAD_ATTACH:;
      DLL_THREAD_DETACH:;
    end;
  end;

  exports
    DllInit,
    setHook,
    hookProc,
    catchWindowData;
begin
    DllProc := @DLLEntryPoint;
    DLLEntryPoint(DLL_PROCESS_ATTACH);
end.
