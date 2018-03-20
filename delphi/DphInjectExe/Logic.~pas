unit Logic;

interface

uses
SysUtils,
Variants,
TlHelp32,
Windows,
Utils,
IniFiles,
MyLog,
ExtCtrls,
ConfigManager;

//const
//cntInjectDll: string = 'DelphiHookDll.dll';
//cntInjectExe: string = 'vcldelphi.exe';

 type TLogic = class(TObject)
 private
   mInitFile: TIniFile;
   mExePath: string;
   mLargerTimer: Boolean;
   mConfigManager: TConfigManager;
  public
    constructor Create;
    procedure DoStart(path:string);
    procedure DoRemoteInject();
    procedure DoTimerMonitor(ctlTimer: TTimer);
    function IsExeFileExist: Boolean;
    
  private
    procedure Init();
    procedure InitExeFilePath();
    function InjectDll(const DllFullPath: string; const dwRemoteProcessId: Cardinal): Boolean;
    function GetProcessIDByName(const name: string): DWORD;
    function EnableDebugPriv: Boolean;
    procedure ReStart();
    end;

implementation
  procedure TLogic.Init();
  var
    cRet: Cardinal;
  begin
    InitExeFilePath;
    mConfigManager := TConfigManager.GetInstance;
    
//    if mExePath<>'' then
//    begin
//      cRet := Utils.GetProcessIDByName(Utils.cntInjectExe);
//      if cRet=0 then
//      begin
//        Utils.RunApp(mExePath);
//        DoRemoteInject();
//      end;
//    end;
  end;

  procedure TLogic.DoStart(path:string);
  var
    bRet:Boolean;
    iniPath: string;
  begin
    iniPath := ExtractFilePath(ParamStr(0))+Utils.cntCfgFileName;
    mInitFile := TIniFile.Create(iniPath);
    mInitFile.WriteString('ExePath', 'path', path);

    RunApp(Utils.cntInjectExe);
    DoRemoteInject();
  end;


function TLogic.GetProcessIDByName(const name: string): DWORD;
var
ProcessName : string; //进程名
ProcessID : integer; //进程表示符
i : integer;
ContinueLoop:BOOL;
FSnapshotHandle:THandle; //进程快照句柄
FProcessEntry32:TProcessEntry32; //进程入口的结构体信息
  begin
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

function TLogic.EnableDebugPriv: Boolean;
var
  hToken: THandle;
  tp: TTokenPrivileges;
  rl: Cardinal;
begin
  Result := false;

  // 打开进程令牌环
  OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY,
    hToken);

  // 获得进程本地唯一ID
  if LookupPrivilegeValue(nil, 'SeDebugPrivilege', tp.Privileges[0].Luid) then
  begin
    tp.PrivilegeCount          := 1;
    tp.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED;
  // 调整权限
    Result := AdjustTokenPrivileges(hToken, false, tp, SizeOf(tp), nil, rl);
  end;
end;

function TLogic.InjectDll(const DllFullPath: string; const dwRemoteProcessId: Cardinal): Boolean;
var
  hRemoteProcess, hRemoteThread: THandle;
  pszLibFileRemote: Pointer;
  pszLibAFilename: PwideChar;
  pfnStartAddr: TFNThreadStartRoutine;
  memSize, WriteSize: Cardinal;
  lpThreadId: DWORD;

  bRet: Boolean;
begin
  Result := false;
  // 调整权限，使程序可以访问其他进程的内存空间
  if EnableDebugPriv then
  begin
    //打开远程线程 PROCESS_ALL_ACCESS 参数表示打开所有的权限
    hRemoteProcess := OpenProcess(PROCESS_ALL_ACCESS, false, dwRemoteProcessId);

    try

      // 为注入的dll文件路径分配内存大小,由于为WideChar,故要乘2
      GetMem(pszLibAFilename, Length(DllFullPath) * 2 + 1);
      // 之所以要转换成 WideChar, 是因为当DLL位于有中文字符的路径下时不会出错
      StringToWideChar(DllFullPath, pszLibAFilename, Length(DllFullPath) * 2 + 1);
      // 计算 pszLibAFilename 的长度，注意，是以字节为单元的长度
      memSize := (1 + lstrlenW(pszLibAFilename)) * SizeOf(WCHAR);

      // 使用VirtualAllocEx函数在远程进程的内存地址空间分配DLL文件名空间
      pszLibFileRemote := VirtualAllocEx(hRemoteProcess, nil,
        memSize, MEM_COMMIT, PAGE_READWRITE);

      if Assigned(pszLibFileRemote) then
      begin
        // 使用WriteProcessMemory函数将DLL的路径名写入到远程进程的内存空间

        bRet := WriteProcessMemory(hRemoteProcess, pszLibFileRemote, pszLibAFilename, memSize, WriteSize);

        if (bRet = True) and (WriteSize = memSize) then
        begin
          lpThreadId := 0;
          // 计算LoadLibraryW的入口地址
          pfnStartAddr := GetProcAddress(LoadLibrary('Kernel32.dll'),
          'LoadLibraryW');
          // 启动远程线程LoadLbraryW,通过远程线程调用创建新的线程
          hRemoteThread := CreateRemoteThread(hRemoteProcess, nil,
          0, pfnStartAddr, pszLibFileRemote, 0, lpThreadId);

          // 如果执行成功返回　True;
          if (hRemoteThread <> 0) then
          Result := true;

          // 释放句柄
          CloseHandle(hRemoteThread);
        end;
      end;
    finally
      // 释放句柄
      CloseHandle(hRemoteProcess);
    end;
  end;
end;

constructor TLogic.Create;
begin
  Init;
end;

procedure TLogic.DoRemoteInject;
  var
  dir, path: string;
  pID: Cardinal;

  begin
     dir := ExtractFileDir(ParamStr(0));
     path := Concat(dir, '\', Utils.cntInjectDll);
     pID := GetProcessIDByName(Utils.cntInjectExe);
     InjectDll(path, pID);
  end;

procedure  TLogic.InitExeFilePath();
var
    iniPath: string;
begin
    iniPath := ExtractFilePath(ParamStr(0))+Utils.cntCfgFileName;
    mInitFile := TIniFile.Create(iniPath);
    mExePath := mInitFile.ReadString('ExePath', 'path', '');
end;

procedure TLogic.DoTimerMonitor(ctlTimer: TTimer);
var
  nRet: Cardinal;
  bDone : Boolean;
begin
//    nRet := Utils.GetProcessIDByName(Utils.cntInjectExe);
//   if Utils.IsInAutoOpTime=True then
//   begin
//     //ctlTimer.Enabled :=False;
//      bDone := mConfigManager.IsAllOpsOperatedAccordDate(Date);
//      
//      if bDone=False then
//      begin
//       ctlTimer.Interval := Utils.cntTimerIntervalAutoOpsRepeat;
//       if nRet<>0 then
//        Utils.KillAppExe(mExePath);
//        Sleep(1000);  
//        ReStart();
//        Exit;
//      end;
//   end
//   else
//    ctlTimer.Interval := Utils.cntTimerIntervalRun;
//
//   if nRet=0 then
//    ReStart();
end;

function TLogic.IsExeFileExist: Boolean;
begin
  Result := mExePath<>'';
end;

procedure TLogic.ReStart;
begin
    Utils.RunApp(mExePath);
    DoRemoteInject();
end;

end.
