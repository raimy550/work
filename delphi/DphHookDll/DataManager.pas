unit DataManager;

interface
uses
  Windows,
  Messages,
  Dialogs,
  Controls,
  StdCtrls,
  Utils,
  SysUtils,
  Classes,
  Contnrs,
  StrMap,
  WeiTuoInfo,
  YuYueInfo,
  LoginInfo,
  DataTrans;

type
  InfoType=(InfoType_None, InfoType_WeiTuo, InfoType_YuYue);

procedure GetWindowsData(h: HWND);
procedure Init();
procedure PostData();
procedure GetLoginData(h: HWND);
procedure CleanData();
//���²�����ť
procedure UpdateOps(h: HWND);
function GetInfoType(h: HWND):InfoType;
procedure UpdateCurInfoType(hContainer: HWND; hInfoOp: HWND);

implementation

var
  mYuYueInfo: CYuYueInfo;
  mCurInfoType: InfoType;

procedure Init();
begin
  WeiTuoInfo.Init();
  LoginInfo.Init();
  mYuYueInfo := CYuYueInfo.Create;
  mCurInfoType := InfoType_None;
end;

procedure CleanData();
begin
  WeiTuoInfo.CleanData;
  mYuYueInfo.CleanData;
end;

function DoWindowsWeiXiu(h: HWND): Boolean;
begin
  //ShowMessageFmt('%s', ['����ά��---��ʼ']);
  WeiTuoInfo.ParseData(h);
  WeiTuoInfo.SaveShowData();
  WeiTuoInfo.SaveJsonData();
  //ShowMessageFmt('%s', ['����ά��---����']);
  Result := True;
end;

function DoWindowsYuYue(h: HWND): Boolean;
begin
  //ShowMessageFmt('%s', ['�ͻ�ԤԼ---��ʼ']);
  mYuYueInfo.ParseData(h);
  mYuYueInfo.SaveShowData();
  mYuYueInfo.SaveJsonData();
  //ShowMessageFmt('%s', ['�ͻ�ԤԼ---����']);
  Result := True;
end;

function DoWindows(h: HWND): Boolean;
var
  buf: array[0..255] of Char; {����������ǻ�ȡ�����õ�, �������Ҫ����ɾ��}
  nRet, nRet1, tab: Integer;
  tcl: TWinControl;
begin
  Result := False;
  if Utils.FilterControls(h) then
  begin
  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl<>nil then
  begin
    begin
      if tcl.Visible then
      begin
        tab := tcl.TabOrder;
        tcl.GetTextBuf(buf, 255);
        nRet :=  Pos('����ά��', buf);
        if (nRet<>0) and (mCurInfoType=InfoType_WeiTuo) then
        begin
          Result := DoWindowsWeiXiu(h);
          Exit;
        end;

        nRet :=  Pos('�ͻ�ԤԼ', buf);
        if (nRet<>0) and (mCurInfoType=InfoType_YuYue) then
        begin
          Result := DoWindowsYuYue(h);
          Exit;
        end;

      end;
    end;
  end;

  end;
end;

function DoLoginWindows(h: HWND): Boolean;
var
  buf: array[0..255] of Char;
  nRet, nRet1, tab: Integer;
begin
    Result := False;
    LoginInfo.ParseData(h);
end;

procedure GetLoginDataImp(h: HWND);
var
  bDone: Boolean;
begin
  if h=0 then
   Exit;
   
  bDone := DoLoginWindows(h);
  if bDone=True then  //�Ѿ��������˳�
    Exit;

  h := GetWindow(h, GW_CHILD); {��һ���Ӵ���}
  while h <> 0 do
  begin
    GetLoginDataImp(h); {�ݹ�}
    h := GetWindow(h, GW_HWNDNEXT); {��һ���Ӵ���}
  end;
end;

procedure GetLoginData(h: HWND);
begin
  //ShowMessageFmt('%s',['��ȡ��¼��Ϣ��ʼ']);
  GetLoginDataImp(h);
  //ShowMessageFmt('%s',['��ȡ��¼��Ϣ����']);
  LoginInfo.SaveJsonData();
end;

procedure GetWindowsDataImp(h: HWND);
var
  bDone: Boolean;
begin
  bDone := DoWindows(h);
  if bDone=True then  //�Ѿ��������˳�
    Exit;

  h := GetWindow(h, GW_CHILD); {��һ���Ӵ���}
  while h <> 0 do
  begin
    GetWindowsDataImp(h); {�ݹ�}
    h := GetWindow(h, GW_HWNDNEXT); {��һ���Ӵ���}
  end;
end;

procedure GetWindowsData(h: HWND);
begin
  GetWindowsDataImp(h);
end;

function AddDataWeiTuo(data: string; tab: Integer): Integer;
begin
  Result :=0;
end;

procedure PostData();
var
  ws: String;
begin
  ws := WeiTuoInfo.GetJsonData();
  DataTrans.HttpPost(Utils.cntUrl, ws);
end;

function DoUpdateOps(h: HWND): Boolean;
var
  tcl: TWinControl;
begin
  Result := False;

  if Utils.FilterControls(h) then
  begin
     if mYuYueInfo.UpdateOp(h) or WeiTuoInfo.UpdateOp(h) then
      begin
          Result := True;
          Exit;
      end;
  end;


end;

function UpdateOpsImp(h: HWND): Boolean;
begin

   if DoUpdateOps(h) then
    Exit;
   
   h := GetWindow(h, GW_CHILD);
   
  while h <> 0 do
  begin
    UpdateOpsImp(h);
    
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure UpdateOps(h: HWND);
begin
    UpdateOpsImp(h);
end;

function GetInfoType(h: HWND):InfoType;
begin
  if h=WeiTuoInfo.GetOp() then
    Result := InfoType_WeiTuo
  else if h=mYuYueInfo.GetOp then
    Result := InfoType_YuYue
  else
    Result := InfoType_None;
end;

procedure UpdateCurInfoType(hContainer: HWND; hInfoOp: HWND);
begin
    UpdateOps(hContainer);
    mCurInfoType := GetInfoType(hInfoOp);
 //   ShowMessageFmt('UpdateCurInfoType---%d', [Integer(mCurInfoType)]);
end;

end.
