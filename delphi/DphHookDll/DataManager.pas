unit DataManager;

interface
uses
  Windows,Messages,Dialogs,Controls,StdCtrls,Utils,SysUtils,Classes,
  Contnrs,StrMap,YuYueInfo,LoginInfo,DataTrans,WeiXiuWeiTuoInfo;

type
  InfoType=(InfoType_None, InfoType_WeiTuo, InfoType_YuYue);

{ TDataManager }

  TDataManager = class(TObject)
  private
      mYuYueInfo: CYuYueInfo;
      mWeiTuoInfo: CWeiTuoInfo;
      mCurInfoType: InfoType;
      mDataTrans: TDataTrans;
  private
    function AddDataWeiTuo(data: string; tab: Integer): Integer;
    function DoLoginWindows(h: HWND): Boolean;
    function DoUpdateOps(h: HWND): Boolean;
    function DoWindows(h: HWND): Boolean;
    function DoWindowsWeiXiu(h: HWND): Boolean;
    function DoWindowsYuYue(h: HWND): Boolean;
    procedure GetLoginDataImp(h: HWND);
    procedure GetWindowsDataImp(h: HWND);
    function UpdateOpsImp(h: HWND): Boolean;

  protected

  public
    constructor Create;
    destructor Destroy; override;

    procedure GetWindowsData(h: HWND);
    procedure Init();
    procedure PostData();
    procedure GetLoginData(h: HWND);
    procedure CleanData();
    //更新操作按钮
    procedure UpdateOps(h: HWND);
    function GetInfoType(h: HWND):InfoType;
    procedure UpdateCurInfoType(hContainer: HWND; hInfoOp: HWND);
  published

  end;


implementation
 

procedure TDataManager.Init();
begin
  //WeiTuoInfo.Init();
  LoginInfo.Init();
  mYuYueInfo := CYuYueInfo.Create;
  mWeiTuoInfo:= CWeiTuoInfo.Create;
  mDataTrans := TDataTrans.Create;
  mCurInfoType := InfoType_None;
  
end;

procedure TDataManager.CleanData();
begin
//  WeiTuoInfo.CleanData;
  mWeiTuoInfo.CleanData;
  mYuYueInfo.CleanData;
end;

function TDataManager.DoWindowsWeiXiu(h: HWND): Boolean;
begin
  //ShowMessageFmt('%s', ['本次维修---开始']);
//  WeiTuoInfo.ParseData(h);
//  WeiTuoInfo.SaveShowData();
//  WeiTuoInfo.SaveJsonData();
    mWeiTuoInfo.ParseData(h);
    mWeiTuoInfo.SaveShowData;
    mWeiTuoInfo.SaveJsonData;
  //ShowMessageFmt('%s', ['本次维修---结束']);
  Result := True;
end;

function TDataManager.DoWindowsYuYue(h: HWND): Boolean;
begin
  //ShowMessageFmt('%s', ['客户预约---开始']);
  mYuYueInfo.ParseData(h);
  mYuYueInfo.SaveShowData();
  mYuYueInfo.SaveJsonData();
  //ShowMessageFmt('%s', ['客户预约---结束']);
  Result := True;
end;

function TDataManager.DoWindows(h: HWND): Boolean;
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
        nRet :=  Pos('维修委托书', buf);
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

function TDataManager.DoLoginWindows(h: HWND): Boolean;
var
  buf: array[0..255] of Char;
  nRet, nRet1, tab: Integer;
begin
    Result := False;
    LoginInfo.ParseData(h);
end;

procedure TDataManager.GetLoginDataImp(h: HWND);
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

procedure TDataManager.GetLoginData(h: HWND);
begin
  //ShowMessageFmt('%s',['获取登录信息开始']);
  GetLoginDataImp(h);
  //ShowMessageFmt('%s',['获取登录信息结束']);
  LoginInfo.SaveJsonData();
end;

procedure TDataManager.GetWindowsDataImp(h: HWND);
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

procedure TDataManager.GetWindowsData(h: HWND);
begin
  GetWindowsDataImp(h);
end;

function TDataManager.AddDataWeiTuo(data: string; tab: Integer): Integer;
begin
  Result :=0;
end;

procedure TDataManager.PostData();
var
  ws: String;
begin
  ws := mWeiTuoInfo.GetJsonData();
  mDataTrans.HttpPost(Utils.cntUrl, ws);
end;


{-------------------------------------------------------------------------------
  过程名:    DoUpdateOps, 更新操作页面的操作按钮，用以判断当前点击操作的页面
  作者:      raimy
  日期:      2017.11.28
  参数:      h: HWND
  返回值:    Boolean
-------------------------------------------------------------------------------}
function TDataManager.DoUpdateOps(h: HWND): Boolean;
var
  tcl: TWinControl;
begin
  Result := False;

  if Utils.FilterControls(h) then
  begin
     if mYuYueInfo.UpdateOp(h) or mWeiTuoInfo.UpdateOp(h) then
      begin
          Result := True;
          Exit;
      end;
  end;


end;

function TDataManager.UpdateOpsImp(h: HWND): Boolean;
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

procedure TDataManager.UpdateOps(h: HWND);
begin
    UpdateOpsImp(h);
end;

function TDataManager.GetInfoType(h: HWND):InfoType;
begin
  if h=mWeiTuoInfo.GetOp() then
    Result := InfoType_WeiTuo
  else if h=mYuYueInfo.GetOp then
    Result := InfoType_YuYue
  else
    Result := InfoType_None;
end;


{-------------------------------------------------------------------------------
  过程名:    UpdateCurInfoType, 更新获取当前页面的类型，以确定当前操作页面
  作者:      raimy
  日期:      2017.11.28
  参数:      hContainer: HWND; hInfoOp: HWND
  返回值:    无
-------------------------------------------------------------------------------}
procedure TDataManager.UpdateCurInfoType(hContainer: HWND; hInfoOp: HWND);
begin
    UpdateOps(hContainer);
    mCurInfoType := GetInfoType(hInfoOp);
 //   ShowMessageFmt('UpdateCurInfoType---%d', [Integer(mCurInfoType)]);
end;

constructor TDataManager.Create;
begin
  Init;
end;

destructor TDataManager.Destroy;
begin

  inherited;
end;

end.
