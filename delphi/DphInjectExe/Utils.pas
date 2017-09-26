unit Utils;

interface

uses
Windows,
Messages,
Dialogs,
Grids,
cxGrid,
Controls,
cxButtons,
StdCtrls,
TlHelp32,
SysUtils;

const
//  cntInjectExe: string = 'INFO_DMS.exe';
//  cntInjetWind: AnsiString = '�������ھ��������ܹ���ƽ̨';
//  cntInjetWind: AnsiString = '��¼����';


cntInjectExe: string = 'DphExe.exe';
cntInjetWind: AnsiString = 'Form5';

cntInjectDll: string = 'DphHookDll.dll';
  cntSaveAllDataName: string = 'data.txt';
  cntSaveGridDataName: string = 'grid.txt';


  function GetMainThreadIdFromName(const name: string): DWORD;
  function GetProcessIDByName(const name: string): DWORD;
  procedure GetThreadIdsFromName(const name: string);
  function FindControlFromAllThreads(Handle: HWnd): TWinControl;
  function GetInstanceFromhWnd(const hWnd: Cardinal): TWinControl;
  function cxFindVCLControl(AWnd: HWND): TWinControl;
  function FindControl(Handle: HWnd): TWinControl;
implementation

var
  ControlAtom: TAtom;
  ControlAtomString: string;
  RM_GetObjectInstance: DWORD;  // registered window message
  ThreadIDArr: array of DWORD;
  ThreadID: DWORD;

function GetProcessIDByName(const name: string): DWORD;
var
ProcessName : string; //������
ProcessID : DWORD; //���̱�ʾ��
ContinueLoop:BOOL;
FSnapshotHandle:THandle; //���̿��վ��
FProcessEntry32:TProcessEntry32; //������ڵĽṹ����Ϣ
begin
  Result := 0;
  FSnapshotHandle:=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); //����һ�����̿���
  FProcessEntry32.dwSize:=Sizeof(FProcessEntry32);
  ContinueLoop:=Process32First(FSnapshotHandle,FProcessEntry32); //�õ�ϵͳ�е�һ������
  //ѭ������
  while ContinueLoop do
  begin
    ProcessName := FProcessEntry32.szExeFile;
    ProcessID := FProcessEntry32.th32ProcessID;
    if ProcessName=name then
    begin
      Result := ProcessID;
      Break;
    end;
    ContinueLoop:=Process32Next(FSnapshotHandle,FProcessEntry32);
  end;
end;


function GetMainThreadIdFromName(const name: string): DWORD;
var
  ProcessId: DWORD;
  te: THREADENTRY32;       // �߳���Ϣ
  hSnapshot: THandle;
begin
  Result:=0;
  ProcessId := GetProcessIDByName(name);
   if ProcessId <> 0 then
   begin
       // ��ȡ���̵����߳�ID

    te.dwSize := sizeof(THREADENTRY32);
    hSnapshot := CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if True=Thread32First(hSnapshot, te) then
      begin
        if ProcessId=te.th32OwnerProcessID  then
          Result := te.th32ThreadID
        else
          begin
             while True=Thread32Next(hSnapshot, te) do
              begin
                  if ProcessId=te.th32OwnerProcessID  then
                  begin
                      Result := te.th32ThreadID;
                      Break;
                  end;
              end;
          end;
      end;
    CloseHandle(hSnapshot); // ɾ������
    end;
end;




function cxFindVCLControl(AWnd: HWND): TWinControl;
begin
  Result := nil;
  while (Result = nil) and (AWnd <> 0) do
  begin
    AWnd := GetAncestor(AWnd, GA_PARENT);
    Result := FindControl(AWnd);
  end;
end;


function GetInstanceFromhWnd(const hWnd: Cardinal): TWinControl;
type  
  PObjectInstance = ^TObjectInstance;  
  
  TObjectInstance = packed record  
    Code: Byte;            { ����ת $E8 }  
    Offset: Integer;       { CalcJmpOffset(Instance, @Block^.Code); }  
    Next: PObjectInstance; { MainWndProc ��ַ }  
    Self: Pointer;         { �ؼ������ַ }  
  end;
var
wc: PObjectInstance;

begin  
  Result := nil;  
  wc := Pointer(GetWindowLong(hWnd, GWL_WNDPROC));  
  if wc <> nil then  
  begin  
    Result := wc.Self;  
  end;
end;

procedure GetThreadIdsFromName(const name: string);
var
  ProcessId: DWORD;
  te: THREADENTRY32;       // �߳���Ϣ
  hSnapshot: THandle;
begin
  ProcessId := GetProcessIDByName(name);
   if ProcessId <> 0 then
   begin
       // ��ȡ���̵����߳�ID

    te.dwSize := sizeof(THREADENTRY32);
    hSnapshot := CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if True=Thread32First(hSnapshot, te) then
      begin
        if ProcessId=te.th32OwnerProcessID  then
        begin
          SetLength(ThreadIDArr, Length(ThreadIDArr)+1);
          ThreadIDArr[Length(ThreadIDArr)] := te.th32ThreadID;
          ShowMessageFmt('%s--%x--ThreadID:%d', ['push', Length(ThreadIDArr), te.th32ThreadID]);
        end;

         while True=Thread32Next(hSnapshot, te) do
          begin
              if ProcessId=te.th32OwnerProcessID  then
              begin
                  SetLength(ThreadIDArr, Length(ThreadIDArr)+1);
                  ThreadIDArr[Length(ThreadIDArr)-1] := te.th32ThreadID;
                  ShowMessageFmt('%s--%d--ThreadID:%x', ['push', Length(ThreadIDArr)-1, te.th32ThreadID]);
              end;
          end;
      end;
    CloseHandle(hSnapshot); // ɾ������
    end;
end;


function FindControlFromAllThreads(Handle: HWnd): TWinControl;
var
  OwningProcess: DWORD;
  i: Integer;
  AtomString: string;
  Atom: TAtom;
  p: Pointer;

begin
  Result := nil;
  if (Handle <> 0) and (GetWindowThreadProcessID(Handle, OwningProcess) <> 0) and
     (OwningProcess = GetCurrentProcessId) then
  begin
    for i := 0 to Length(ThreadIDArr)-1 do
    begin
      AtomString := Format('ControlOfs%.8X%.8X', [GetModuleHandle(nil), ThreadIDArr[i]]);
      ShowMessageFmt('----------%s', [AtomString]);
      Atom := GlobalAddAtom(PChar(AtomString));
      p := Pointer(GetProp(Handle, MakeIntAtom(Atom)));

      if (p <> nil) then
      begin
        Result:= p;
        ShowMessageFmt('find control from %s', [AtomString]);
        Break;
      end;

    end;
  end;
end;


function FindControl(Handle: HWnd): TWinControl;
var
  OwningProcess: DWORD;
begin
  Result := nil;
  if (Handle <> 0) and (GetWindowThreadProcessID(Handle, OwningProcess) <> 0) and
     (OwningProcess = GetCurrentProcessId) then
  begin
//   ShowMessageFmt('%s:%x, %s:%x, %s:%s', ['MainThread', MainThreadID, 'CurThread', GetCurrentProcessId, 'ControlAtomString:',ControlAtomString]);
    if GlobalFindAtom(PChar(ControlAtomString)) = ControlAtom then
      Result:= Pointer(GetProp(Handle, MakeIntAtom(ControlAtom)))
//       Result := Pointer(SendMessage(Handle, RM_GetObjectInstance, GetCurrentProcessId, 0))
    else
       Result := Pointer(SendMessage(Handle, RM_GetObjectInstance, GetCurrentProcessId, 0));
  end;
end;

initialization
  ThreadID := GetMainThreadIdFromName(Utils.cntInjectExe);

//  GetThreadIdsFromName(cntInjectExe);
//  ShowMessageFmt('%s:thread id count = %d', [cntInjectExe, Length(ThreadIDArr)]);
//  ShowMessageFmt('%s:thread id = %d', [cntInjectExe, ThreadID]);
  ControlAtomString := Format('ControlOfs%.8X%.8X', [GetModuleHandle(nil), ThreadID]);
  ControlAtom := GlobalAddAtom(PChar(ControlAtomString));
  RM_GetObjectInstance := RegisterWindowMessage('DelphiRM_GetObjectInstance');
// RM_GetObjectInstance := RegisterWindowMessage(PChar(ControlAtomString));
finalization
  GlobalDeleteAtom(ControlAtom);
  ControlAtomString := '';
  
end.
