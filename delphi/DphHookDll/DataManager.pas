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
//更新操作按钮
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
  //ShowMessageFmt('%s', ['本次维修---开始']);
  WeiTuoInfo.ParseData(h);
  WeiTuoInfo.SaveShowData();
  WeiTuoInfo.SaveJsonData();
  //ShowMessageFmt('%s', ['本次维修---结束']);
  Result := True;
end;

function DoWindowsYuYue(h: HWND): Boolean;
begin
  //ShowMessageFmt('%s', ['客户预约---开始']);
  mYuYueInfo.ParseData(h);
  mYuYueInfo.SaveShowData();
  mYuYueInfo.SaveJsonData();
  //ShowMessageFmt('%s', ['客户预约---结束']);
  Result := True;
end;

function DoWindows(h: HWND): Boolean;
var
  buf: array[0..255] of Char; {这个缓冲区是获取类名用的, 如果不需要可以删除}
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
        nRet :=  Pos('本次维修', buf);
        if (nRet<>0) and (mCurInfoType=InfoType_WeiTuo) then
        begin
          Result := DoWindowsWeiXiu(h);
          Exit;
        end;

        nRet :=  Pos('客户预约', buf);
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
  if bDone=True then  //已经处理则退出
    Exit;

  h := GetWindow(h, GW_CHILD); {第一个子窗口}
  while h <> 0 do
  begin
    GetLoginDataImp(h); {递归}
    h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
  end;
end;

procedure GetLoginData(h: HWND);
begin
  //ShowMessageFmt('%s',['获取登录信息开始']);
  GetLoginDataImp(h);
  //ShowMessageFmt('%s',['获取登录信息结束']);
  LoginInfo.SaveJsonData();
end;

procedure GetWindowsDataImp(h: HWND);
var
  bDone: Boolean;
begin
  bDone := DoWindows(h);
  if bDone=True then  //已经处理则退出
    Exit;

  h := GetWindow(h, GW_CHILD); {第一个子窗口}
  while h <> 0 do
  begin
    GetWindowsDataImp(h); {递归}
    h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
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
