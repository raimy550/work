unit Utils;

interface

uses
Windows,Messages,Dialogs,Grids,cxGrid,Controls,ComCtrls,cxButtons,StdCtrls,
TlHelp32,SysUtils,StrMap,StrUtils,Contnrs,Classes,cxGridLevel,cxGridDBTableView,
cxGridTableView,cxGridCustomView,cxCustomData, ShellAPI;


const
  cnt_WM_WND_VIABLE = WM_USER+123;
//  cntInjectExe: string = 'DphExe.exe';
//  cntInjetWind: AnsiString = 'Form5';

  cntInjectExe: string = 'INFO_DMS.exe';
  
  cntInjetWind: string = '上汽大众经销商智能管理平台';
  cntLoginWind: string = '登录窗口';

  cntInjectDll: string = 'DphHookDll.dll';
  cntOpSaveCls: string ='TcxButton';
  cntOpSave: string ='取消';
  cntOpSure: string ='确定';
  cntDebug: Boolean = True;
  cntDebugModule: Integer = 0;
  cntWaitTime: Integer = 1000*60*5;
  cntWaitWndTime: Integer = 1000*60*3;
  cntTimerIntervalRun: Integer = 1000*6; //监测终端软件运行
  cntTimerIntervalAutoOpsRepeat: Integer = 10*60*1000;//重复执行自动操作
  cntTimerIntervalAutoOp: Integer = 1000*60;
  cntAutoOpTime: Integer=1;


  cntCatchSaveAllDataName: string = 'catdata.txt';
  cntSaveAllDataName: string = 'data.txt';
  cntSaveGridDataName: string = 'grid.txt';
  cntSaveLogName: string = 'log.txt';
  cntUrl: string = 'http://192.168.7.150:8063/api/v1.0.0/createVWMaintainProxyOrder';
  cntUrlUpLoadFile: string = 'http://192.168.7.150:8066/api/v1.0.0/uploadFile';
  cntCfgFileName: string = 'config.ini';
  
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
  procedure DebugShowMsg(str: string);
  procedure LogOut(str: string);
  function HasString(des, sour: string): Boolean;
  function ClassNameContains(h: HWND; cName: string): Boolean;
  function ClassNameEqual(h: HWND; cName: string): Boolean;
  function GetClassNameBy(h: HWND):string;
  function ControlTextContains(h: HWND; cName: string): Boolean;
  function FilterControls(h: HWND): Boolean;
  procedure SortData(dataMap: TStrMap);
  function CreateDirs(dir: string): string;
  function GetSaveDir(): string;
  function GetCurrentDir():string;
  function FindeWindowBy(h: HWND;txt: string; cls: string): HWND;overload;
  function FindeWindowBy(h: HWND;tab: Integer; cls: string): HWND;overload;
  function GetCtlByClassName(h:HWND; cls:string): TWinControl;
  function GetWindowTab(h: HWND): Cardinal;
  procedure ClickWindow(h:HWND);overload;
  function ClickWindow(h:HWND; timeOut:Cardinal): Integer;overload;
  procedure ClickWindow(h:HWND; ClassName, WindowName: PChar);overload;
  procedure ClickPoint(pointX, pointY:Integer);
  procedure SendKeyEventToWindow(h:HWND; key: Integer);
  function WaitOpTimeOut(wndName:string; time:Cardinal): Integer;overload;
  function WaitOpTimeOut(h:HWND; text,className:string;time:Cardinal):Integer;overload;
  function WaitForWindow(wndName:string; uTime, interval:Cardinal):HWND;
  function CheckLogin(time:Cardinal):Boolean;
  function GetDllPath:string;
  procedure RunApp(path: string);
  function KillAppExe(const aPathExe: string): Boolean;

  function SaveGridData(hParent: HWND; saveDir: string; fileName:string):Boolean;
  function ReadFileToHex(FileName: string): string;
  function IsInAutoOpTime():Boolean;

//文件类
  function IsFileExist(path :string): Boolean;
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
  if cntDebug then
    OutputDebugString(PAnsiChar(str));
end;

procedure DebugShowMsg(str: string);
begin
  ShowMessageFmt('%s', [str]);
end;

procedure SaveData(path: string; data: string; bAppend: Boolean);
var
  F: TextFile;
begin
  AssignFile(F, path);
  if (bAppend=True) and (FileExists(path)) then
     Append(F)
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
  if cName='' then
  begin
    Result:=True;
    Exit;
  end;
  GetClassName(h, buf, Length(buf));
  Result:=HasString(cName, buf);
end;

function ClassNameEqual(h: HWND; cName: string): Boolean;
var
  buf: array[0..255] of Char;
begin
  GetClassName(h, buf, Length(buf));
  
  Result:= CompareStr(buf, cName)=0;
end;

function GetClassNameBy(h: HWND):string;
var
  buf: array[0..255] of Char;
begin
  GetClassName(h, buf, Length(buf));
  Result:=buf;
end;

function ControlTextContains(h: HWND; cName: string): Boolean;
var
  buf: array[0..255] of Char;
  tcl: TWinControl;
begin

  if cName='' then
  begin
    Result:=True;
    Exit;
  end;

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
    //Pos('TcxGrid', buf)
    nRet := Pos('Show', buf)+Pos('Shell', buf)+Pos('Internet', buf)
    +Pos('Inner', buf)+Pos('CheckBox', buf)+Pos('TcxGridSite', buf);
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

function GetCurrentDir():string;
begin
  Result:=ExtractFilePath(ParamStr(0));
end;

function FindeWindowByImp(h: HWND; txt: string; cls: string): HWND;overload;
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


function FindeWindowByImp(h: HWND;tab: Integer; cls: string): HWND;overload;
var
  wnd: HWND;
  buf: array[0..255] of Char;
begin
  Result :=0;
  if FilterControls(h)=True then
  begin
    GetClassName(h, buf, Length(buf));
    DebugOut(Format('%s---%d', [buf,GetWindowTab(h)]));
    
    if (tab=GetWindowTab(h)) and ClassNameContains(h, cls) then
    begin
       Result := h;
       Exit;
    end;
  end;


  h := GetWindow(h, GW_CHILD); {第一个子窗口}
  while h <> 0 do
  begin
    Result := FindeWindowByImp(h, tab, cls);
    if Result <> 0 then
     Exit;
     
    h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
  end;
end;

function FindeWindowBy(h: HWND;tab: Integer; cls: string): HWND;
begin
  Result := FindeWindowByImp(h, tab, cls);
end;

function GetCtlByClassName(h:HWND; cls:string): TWinControl;
var
  bRet: Boolean;
begin
  Result:=nil;
   bRet := ClassNameEqual(h, cls);
    if bRet then
    begin
      Result := GetInstanceFromhWnd(h);
    end;

end;

function ClickWindow(h:HWND; timeOut:Cardinal): Integer;
var 
  nResult:Cardinal;
begin
 Result := SendMessageTimeout(h, BM_CLICK, 0, 0, SMTO_NORMAL, timeOut, nResult);
end;

procedure ClickWindow(h:HWND);
begin
  if h<> 0 then
    SendMessage(h, BM_CLICK, 0, 0);
end;

procedure ClickWindow(h:HWND; ClassName, WindowName: PChar);
var
  hTarg: HWND;
begin
  hTarg:=FindWindowEx(h, 0, ClassName, WindowName);
  if hTarg<>0 then
    SendMessage(hTarg, BM_CLICK, 0, 0);
    
end;

procedure SendKeyEventToWindow(h:HWND; key: Integer);
begin
  SendMessage(h, WM_KEYDOWN, key, 0);
  SendMessage(h, WM_KEYUP, key, 0);
//  SendMessage(h, WM_KEYUP, key, 0);
//  keybd_event(key, 0,0,0,);
end;

function GetWindowTab(h: HWND): Cardinal;
var
  tcl: TWinControl;
begin
  Result := 0;
  if FilterControls(h)=False then
      Exit;

  tcl := GetInstanceFromhWnd(h);
  if (tcl<>nil) and tcl.Visible then
   Result := tcl.TabOrder;
end;



{-------------------------------------------------------------------------------
  过程名:    WaitOpTimeOut
  作者:      raimy
  日期:      2017.11.21
  参数:      wndName:string; time:Cardinal
  返回值:    Integer;sucess:not 0 fail: 0
-------------------------------------------------------------------------------}
function WaitOpTimeOut(wndName:string; time:Cardinal):Integer;overload;
var
  nResult: Cardinal;
  h:HWND;
begin
   h := FindWindow(nil,PAnsiChar(wndName));
  Result := SendMessageTimeout(h, Utils.cnt_WM_WND_VIABLE, 0, 0, SMTO_NORMAL, time, nResult);
end;


{-------------------------------------------------------------------------------
  过程名:    WaitOpTimeOut
  作者:      raimy
  日期:      2017.11.21
  参数:      h:HWND父窗口; text,className:string窗口caption，类名; time:Cardinal超时时间
  返回值:    Integer 同上
-------------------------------------------------------------------------------}
function WaitOpTimeOut(h:HWND; text,className:string; time:Cardinal):Integer;overload;
var
  tmp: Cardinal;
  hFind: HWND;
begin
   tmp :=0;
   Result := 0;
   while tmp < time do
   begin
     hFind := FindeWindowBy(h, text, className);
     tmp :=tmp+500;
     if hFind<>0 then
     begin
       Result := WaitOpTimeOut(cntInjetWind, time-tmp);
       Exit;
     end;
     
   end;
end;

function WaitForWindow(wndName:string; uTime, interval:Cardinal):HWND;
var
  sum:Cardinal;
begin
  sum := 0;
  while sum < uTime do
  begin
    sum := sum+ interval;
    Result:=FindWindow(nil, PAnsiChar(wndName));
    if Result<>0 then
     Exit;
     
    Sleep(interval);
  end;
end;

function CheckLogin(time:Cardinal):Boolean;
var
  h: HWND;
begin
   h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
   if h<> 0 then
   Result:=True
   else
   Result:=False;
end;

function IsFileExist(path : string):Boolean;
begin
  Result := FileExists(path);
end;

function GetDllPath:string;
var
ModuleName:string;
i:Integer;
begin
  SetLength(ModuleName, 255);
  //取得Dll自身路径
  GetModuleFileName(HInstance, PChar(ModuleName), Length(ModuleName));
  i := LastDelimiter('\', ModuleName);
  Result := Copy(ModuleName, 1, i);
end;

function SaveGridData(hParent: HWND; saveDir: string; fileName:string):Boolean;
var
    cxGridDBTableView: TcxGridDBTableView;
    cxView, cxView1: TcxCustomGridView;
    i,j, nRowCount,nColCount: Integer;
    rowInfo: TcxRowInfo;
    s, s1, tmp: string;
    p: Pointer ;
    sStr: ShortString;
    vari: Variant;
    grid: TcxGrid;
    twcl: TWinControl;
    hFind: HWND;

  begin
      Result:=False;
      hFind:=FindeWindowBy(hParent, '', 'TcxGrid');
      if (hFind<>0) then
      begin
      twcl := GetCtlByClassName(hFind, 'TcxGrid');
      grid := TcxGrid(twcl);
      if(grid=nil)  then
      Exit;
      end;
      
      
      if grid.ActiveLevel = nil then
        Exit
      else
      begin
         cxView := grid.FocusedView;

         if cxView=nil then
           Exit;

         if cxView <> nil then
         begin
           if cxView.DataController=nil then
              Exit
           else
           begin
             nRowCount := cxView.DataController.GetRowCount();
             nColCount := cxView.DataController.GetItemCount();
             if nRowCount=0 then
             Exit;

             s := '';
             s1 := '';
             if nRowCount>0 then
             begin
               //字段值
               for j:=0 to nColCount-1 do
               begin
                 cxGridDBTableView := TcxGridDBTableView(cxView); 
                 s1 := Format('%s', [cxGridDBTableView.Columns[j].Caption]);
                 if j<>0 then
                  s1 := #9+s1;
                  s := Concat(s, s1);
               end;
               s := Concat(s, Char(13), Chr(10));
               SaveData(saveDir+fileName,s, True);
             end;

               
             s := '';
             s1 := '';
             for i := 0 to nRowCount-1 do
             begin
             if i<>0 then s := Concat(s, Char(13), Chr(10));
              for j:=0 to nColCount-1 do
               begin
                 s1 := Format('%s', [cxView.DataController.GetDisplayText(i,j)]);
                 
                 if j<>0 then
                  s1 := #9+s1;
                  
                 s := Concat(s, s1);
               end;
               
               if ((0=(i mod 100)) and (i>99)) or (i=nRowCount-1)then
                 begin
                    SaveData(saveDir+fileName,s, True);
                    s := '';
                 end;
             end;
           end;
         end;
      end;

      Result:=True;
  end;

procedure RunApp(path: string);
begin
  ShellExecute(0,'open',Pchar(path),nil,nil,SW_SHOWNORMAL); 
end;

function KillAppExe(const aPathExe: string): Boolean;
const
PROCESS_TERMINATE = $0001;
var
_vHandle : THandle;
_vProEntry : TProcessEntry32;
_vIsFound : Boolean;
_vTempStr : string;
begin
  Result := False;
  _vHandle := CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  try
  _vProEntry.dwSize := SizeOf(_vProEntry);
  _vIsFound := Process32First(_vHandle, _vProEntry);
  while _vIsFound do
  begin
  _vTempStr := _vProEntry.szExeFile;
  if (UpperCase(_vTempStr) = UpperCase(ExtractFileName(aPathExe))) or
  (UpperCase(_vTempStr) = UpperCase(aPathExe)) then
  begin
  Result := TerminateProcess(OpenProcess(PROCESS_TERMINATE,
  Boolean(0), _vProEntry.th32ProcessID), 0);
  end;
  _vIsFound := Process32Next(_vHandle, _vProEntry);
  end;
  finally
  CloseHandle(_vHandle);
  end;
end;

procedure ClickPoint(pointX, pointY:Integer);
begin
  //Windows.ClientToScreen(h, point);
  SetCursorPos(pointX, pointY);
  mouse_event(MOUSEEVENTF_LEFTDOWN,pointX,pointY,0,0); 
  Sleep(300);
  mouse_event(MOUSEEVENTF_LEFTUP,pointX,pointY,0,0); 
  Sleep(3000);
end;

function ReadFileToHex(FileName: string): string;
var
  b: Byte;
begin
  Result := '';
  if not FileExists(FileName) then Exit;
  with TMemoryStream.Create do begin
    LoadFromFile(FileName);
    Position := 0;
    while Position < Size do
    begin
      ReadBuffer(b, 1);
      Result := Result + Format('%.2x ', [b]) ;
    end;
    Trim(Result);
    Free;
  end;
end;

function IsInAutoOpTime():Boolean;
var
  Year, Month, Day, Hour, Min, Sec, MSec:Word;
  curTime: TDateTime ;
begin
  Result:=False;
  curTime := Now;
  DecodeDate(curTime, Year, Month, Day);
  DecodeTime(curTime, Hour, Min, Sec, MSec); 
  if (Hour>=cntAutoOpTime) and (Hour-cntAutoOpTime <= 2) then
    Result:=True;
  
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
