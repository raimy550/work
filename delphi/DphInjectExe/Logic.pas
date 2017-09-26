unit Logic;

interface

uses
SysUtils,
Variants,
TlHelp32,
Windows,
Utils;

//const
//cntInjectDll: string = 'DelphiHookDll.dll';
//cntInjectExe: string = 'vcldelphi.exe';

procedure Init();
procedure DoStart();
function InjectDll(const DllFullPath: string; const dwRemoteProcessId: Cardinal): Boolean;
function GetProcessIDByName(const name: string): DWORD;

implementation
  procedure Init();
  begin

  end;

  procedure DoStart();
  var
  dir, path: string;
  pID: Cardinal;

  begin
     dir := ExtractFileDir(ParamStr(0));
     path := Concat(dir, '\', Utils.cntInjectDll);
     pID := GetProcessIDByName(Utils.cntInjectExe);
     InjectDll(path, pID);
  end;


function GetProcessIDByName(const name: string): DWORD;
var
ProcessName : string; //������
ProcessID : integer; //���̱�ʾ��
i : integer;
ContinueLoop:BOOL;
FSnapshotHandle:THandle; //���̿��վ��
FProcessEntry32:TProcessEntry32; //������ڵĽṹ����Ϣ
  begin
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

function EnableDebugPriv: Boolean;
var
  hToken: THandle;
  tp: TTokenPrivileges;
  rl: Cardinal;
begin
  Result := false;

  // �򿪽������ƻ�
  OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY,
    hToken);

  // ��ý��̱���ΨһID
  if LookupPrivilegeValue(nil, 'SeDebugPrivilege', tp.Privileges[0].Luid) then
  begin
    tp.PrivilegeCount          := 1;
    tp.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED;
    // ����Ȩ��
    Result := AdjustTokenPrivileges(hToken, false, tp, SizeOf(tp), nil, rl);
  end;
end;

function InjectDll(const DllFullPath: string; const dwRemoteProcessId: Cardinal): Boolean;
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
  // ����Ȩ�ޣ�ʹ������Է����������̵��ڴ�ռ�
  if EnableDebugPriv then
  begin
    //��Զ���߳� PROCESS_ALL_ACCESS ������ʾ�����е�Ȩ��
    hRemoteProcess := OpenProcess(PROCESS_ALL_ACCESS, false, dwRemoteProcessId);

    try

      // Ϊע���dll�ļ�·�������ڴ��С,����ΪWideChar,��Ҫ��2
      GetMem(pszLibAFilename, Length(DllFullPath) * 2 + 1);
      // ֮����Ҫת���� WideChar, ����Ϊ��DLLλ���������ַ���·����ʱ�������
      StringToWideChar(DllFullPath, pszLibAFilename, Length(DllFullPath) * 2 + 1);
      // ���� pszLibAFilename �ĳ��ȣ�ע�⣬�����ֽ�Ϊ��Ԫ�ĳ���
      memSize := (1 + lstrlenW(pszLibAFilename)) * SizeOf(WCHAR);

      // ʹ��VirtualAllocEx������Զ�̽��̵��ڴ��ַ�ռ����DLL�ļ����ռ�
      pszLibFileRemote := VirtualAllocEx(hRemoteProcess, nil,
        memSize, MEM_COMMIT, PAGE_READWRITE);

      if Assigned(pszLibFileRemote) then
      begin
        // ʹ��WriteProcessMemory������DLL��·����д�뵽Զ�̽��̵��ڴ�ռ�

        bRet := WriteProcessMemory(hRemoteProcess, pszLibFileRemote, pszLibAFilename, memSize, WriteSize);

        if (bRet = True) and (WriteSize = memSize) then
        begin
          lpThreadId := 0;
          // ����LoadLibraryW����ڵ�ַ
          pfnStartAddr := GetProcAddress(LoadLibrary('Kernel32.dll'),
          'LoadLibraryW');
          // ����Զ���߳�LoadLbraryW,ͨ��Զ���̵߳��ô����µ��߳�
          hRemoteThread := CreateRemoteThread(hRemoteProcess, nil,
          0, pfnStartAddr, pszLibFileRemote, 0, lpThreadId);

          // ���ִ�гɹ����ء�True;
          if (hRemoteThread <> 0) then
          Result := true;

          // �ͷž��
          CloseHandle(hRemoteThread);
        end;
      end;
    finally
      // �ͷž��
      CloseHandle(hRemoteProcess);
    end;
  end;
end;

end.
