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
  Utils in 'Utils.pas',
  StrMap in 'StrMap.pas',
  DataTrans in 'DataTrans.pas',
  YuYueInfo in 'YuYueInfo.pas';

{$R *.res}
var
  hHook1:HHOOK;

function DllInit():Integer; stdcall;
begin
  Init();
  Result := 0;
end;

function hookProc(nCode,wParam,lParam: DWORD):DWORD;stdcall;
begin
  DoProc(nCode, wParam, lParam);
  Result:=CallNextHookEx(hHook1,nCode,wParam,lParam);

end;

function mouseProc(nCode: Integer; wParam: WPARAM;lParam: LPARAM):DWORD;stdcall;
begin
  DoProcMouse(nCode, wParam, lParam);
  Result:=CallNextHookEx(hHook1,nCode,wParam,lParam);

end;

function setHook():Boolean;stdcall;
begin
//  hHook1:=SetWindowsHookEx(WH_CALLWNDPROC,@hookProc,HInstance,0);
  hHook1:=SetWindowsHookEx(WH_MOUSE,@mouseProc,HInstance,0);
  Result:=hHook1<>0;
end;

//É¾³ýÊó±ê¹³×Ó
function delHook:Boolean;stdcall;
begin
  Result:=UnhookWindowsHookEx(hHook1);
end;




procedure DLLEntryPoint(Reason:Integer);

  begin
    case Reason of
      DLL_PROCESS_ATTACH:
      begin
      Init();
      OutputDebugString('---------DLL_PROCESS_ATTACH');
      //ShowMessageFmt('%s%s', ['----', 'DLL_PROCESS_ATTACH']);
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
    hookProc;
begin
    DllProc := @DLLEntryPoint;
    DLLEntryPoint(DLL_PROCESS_ATTACH);
end.
