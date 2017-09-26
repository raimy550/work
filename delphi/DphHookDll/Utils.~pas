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
SysUtils,
StrMap,
StrUtils,
Contnrs,
Classes;

const
  cntInjectExe: string = 'INFO_DMS.exe';
  cntInjetWind: AnsiString = '上汽大众经销商智能管理平台';
  cntLoginWind: AnsiString = '登录窗口';
  cntOpSaveCls: string ='TcxButton';
  cntOpSave: string ='取消';
  cntOpSure: string ='确定';


//  cntInjectExe: string = 'DphExe.exe';
//  cntInjetWind: AnsiString = 'Form5';

  cntCatchSaveAllDataName: string = 'catdata.txt';
  cntSaveAllDataName: string = 'data.txt';
  cntSaveGridDataName: string = 'grid.txt';
  cntSaveLogName: string = 'log.txt';
  cntUrl: string = 'http://192.168.7.150:8063/api/v1.0.0/createVWMaintainProxyOrder';
  
  cntDataDir: string = 'HookData\';
  cntSaveWeiXiuName: string = 'WeiXiu.xml';
  cntSaveWeiXiuForShowName: string = 'WeiXiu.txt';
  cntSaveYuYueName: string = 'YuYue.xml';
  cntSaveYuYueForShowName: string = 'YuYue.txt';
  cntSaveLoginFileName: string = 'Login.xml';


  function GetMainThreadIdFromName(const name: string): DWORD;
  function GetProcessIDByName(const name: string): DWORD;
  procedure GetThreadIdsFromName(const name: string);
  function FindControlFromAllThreads(Handle: HWnd): TWinControl;
  function GetInstanceFromhWnd(const hWnd: Cardinal): TWinControl;
  function cxFindVCLControl(AWnd: HWND): TWinControl;
  function FindControl(Handle: HWnd): TWinControl;
  procedure SaveData(path: string; data: string; bAppend: Boolean);
  procedure DebugOut(str: string);
  procedure LogOut(str: string);
  function HasString(des, sour: string): Boolean;
  function ClassNameContains(h: HWND; cName: string): Boolean;
  function ControlTextContains(h: HWND; cName: string): Boolean;
  function FilterControls(h: HWND): Boolean;
  procedure SortData(dataMap: TStrMap);
  function CreateDirs(dir: string): string;
  function GetSaveDir(): string;
  function FindeWindowBy(h: HWND;txt: string; cls: string): HWND;
implementation

var
  ControlAtom: TAtom;
  ControlAtomString: string;
  RM_GetObjectInstance: DWORD;  // registered window message
  ThreadIDArr: array of DWORD;
  ThreadID: DWORD;

function GetProcessIDByName(const name: string): DWORD;
var
ProcessName : string; //进程名
ProcessID : DWORD; //进程表示符
ContinueLoop:BOOL;
FSnapshotHandle:THandle; //进程快照句柄
FProcessEntry32:TProcessEntry32; //进程入口的结构体信息
begin
  Result := 0;
  FSnapshotHandle:=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0); //创建一个进程快照
  FProcessEntry32.dwSize:=Sizeof(FProcessEntry32);
  ContinueLoop:=Process32First(FSnapshotHandle,FProcessEntry32); //得到系统中第一个进程
  //循环例举
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
  te: THREADENTRY32;       // 线程信息
  hSnapshot: THandle;
begin
  Result:=0;
  ProcessId := GetProcessIDByName(name);
   if ProcessId <> 0 then
   begin
       // 获取进程的主线程ID

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
    CloseHandle(hSnapshot); // 删除快照
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
    Code: Byte;            { 短跳转 $E8 }  
    Offset: Integer;       { CalcJmpOffset(Instance, @Block^.Code); }  
    Next: PObjectInstance; { MainWndProc 地址 }  
    Self: Pointer;         { 控件对象地址 }  
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
  te: THREADENTRY32;       // 线程信息
  hSnapshot: THandle;
begin
  ProcessId := GetProcessIDByName(name);
   if ProcessId <> 0 then
   begin
       // 获取进程的主线程ID

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
    CloseHandle(hSnapshot); // 删除快照
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

procedure DebugOut(str: string);
begin
  OutputDebugString(PAnsiChar(str));
end;

procedure SaveData(path: string; data: string; bAppend: Boolean);
var
  F: TextFile;
begin
  AssignFile(F, path);
  if bAppend=True then
  begin
    if FileExists(path) then
     Append(F);
  end
  else
  Rewrite(F);

  
  try
    Write(F, data);
  finally
     CloseFile(F);
  end;
end;

procedure LogOut(str: string);
begin
   str := Concat(str, Char(13), Chr(10));
   SaveData(ExtractFilePath(ParamStr(0))+Utils.cntSaveLogName, str, True);
end;

function HasString(des, sour: string): Boolean;
var
  nRet: Integer;
begin
    Result := False;
    nRet := Pos(des, sour);
    if nRet<>0 then
     Result := True;
end;

function ClassNameContains(h: HWND; cName: string): Boolean;
var
  buf: array[0..255] of Char;
begin
  GetClassName(h, buf, Length(buf));
  Result:=HasString(cName, buf);
end;

function ControlTextContains(h: HWND; cName: string): Boolean;
var
  buf: array[0..255] of Char;
  tcl: TWinControl;
begin
  Result := False;
  tcl := GetInstanceFromhWnd(h);
  if tcl<>nil then
  begin
     tcl.GetTextBuf(buf, 255);
     Result:=HasString(cName, buf);
  end;
end;

function FilterControls(h: HWND): Boolean;
var
  buf: array[0..255] of Char;
  nRet: Integer;
begin
    GetClassName(h, buf, Length(buf));
    nRet := Pos('TcxGrid', buf)+ Pos('Show', buf)+Pos('Shell', buf)+Pos('Internet', buf)
    +Pos('Inner', buf)+Pos('CheckBox', buf);
    Result := nRet=0;
end;

procedure SortData(dataMap: TStrMap);
var
  i,j,tmp, nCount: Integer;
  strTmp, str1, str2: string;
  strKeys, strValues: TStrings;
begin
   nCount := dataMap.Count;
   strKeys := dataMap.FKeyList;
   strValues := dataMap.FStrList;

   for i:=0 to nCount-1 do
   begin
      for j:=0 to nCount-2 do
      begin
        str1 := strKeys[j] ;
        str2 := strKeys[j+1];
        if StrToInt(str1)>StrToInt(str2) then
        begin
           strTmp := strKeys[j];
           strKeys[j] := strKeys[j+1];
           strKeys[j+1] := strTmp;

           strTmp := strValues[j];
           strValues[j] := strValues[j+1];
           strValues[j+1] := strTmp;
        end;
      end;
   end;
end;

function CreateDirs(dir: string): string;
begin
  Result := dir;
  if DirectoryExists(dir)=False then
  begin
     ForceDirectories(dir);
  end;
end;

function GetSaveDir(): string;
begin
  Result := CreateDirs(ExtractFilePath(ParamStr(0))+Utils.cntDataDir);
end;

function FindeWindowByImp(h: HWND; txt: string; cls: string): HWND;
var
  wnd: HWND;
begin
  Result :=0;
  if FilterControls(h)=True then
  begin
    if ControlTextContains(h, txt) and ClassNameContains(h, cls) then
    begin
       Result := h;
       Exit;
    end;
  end;


  h := GetWindow(h, GW_CHILD); {第一个子窗口}
  while h <> 0 do
  begin
    Result := FindeWindowByImp(h, txt, cls);
    if Result <> 0 then
     Exit;
     
    h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
  end;
end;

function FindeWindowBy(h: HWND; txt: string; cls: string): HWND;
begin
    Result := FindeWindowByImp(h, txt, cls);
end;


initialization
  ThreadID := GetMainThreadIdFromName(Utils.cntInjectExe);
  ControlAtomString := Format('ControlOfs%.8X%.8X', [GetModuleHandle(nil), ThreadID]);
  ControlAtom := GlobalAddAtom(PChar(ControlAtomString));
  RM_GetObjectInstance := RegisterWindowMessage('DelphiRM_GetObjectInstance');
// RM_GetObjectInstance := RegisterWindowMessage(PChar(ControlAtomString));
finalization
  GlobalDeleteAtom(ControlAtom);
  ControlAtomString := '';
  
end.
