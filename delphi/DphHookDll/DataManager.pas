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
    //���²�����ť
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
  //ShowMessageFmt('%s', ['����ά��---��ʼ']);
//  WeiTuoInfo.ParseData(h);
//  WeiTuoInfo.SaveShowData();
//  WeiTuoInfo.SaveJsonData();
    mWeiTuoInfo.ParseData(h);
    mWeiTuoInfo.SaveShowData;
    mWeiTuoInfo.SaveJsonData;
  //ShowMessageFmt('%s', ['����ά��---����']);
  Result := True;
end;

function TDataManager.DoWindowsYuYue(h: HWND): Boolean;
begin
  //ShowMessageFmt('%s', ['�ͻ�ԤԼ---��ʼ']);
  mYuYueInfo.ParseData(h);
  mYuYueInfo.SaveShowData();
  mYuYueInfo.SaveJsonData();
  //ShowMessageFmt('%s', ['�ͻ�ԤԼ---����']);
  Result := True;
end;

function TDataManager.DoWindows(h: HWND): Boolean;
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
        nRet :=  Pos('ά��ί����', buf);
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
  if bDone=True then  //�Ѿ��������˳�
    Exit;

  h := GetWindow(h, GW_CHILD); {��һ���Ӵ���}
  while h <> 0 do
  begin
    GetLoginDataImp(h); {�ݹ�}
    h := GetWindow(h, GW_HWNDNEXT); {��һ���Ӵ���}
  end;
end;

procedure TDataManager.GetLoginData(h: HWND);
begin
  //ShowMessageFmt('%s',['��ȡ��¼��Ϣ��ʼ']);
  GetLoginDataImp(h);
  //ShowMessageFmt('%s',['��ȡ��¼��Ϣ����']);
  LoginInfo.SaveJsonData();
end;

procedure TDataManager.GetWindowsDataImp(h: HWND);
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
  ������:    DoUpdateOps, ���²���ҳ��Ĳ�����ť�������жϵ�ǰ���������ҳ��
  ����:      raimy
  ����:      2017.11.28
  ����:      h: HWND
  ����ֵ:    Boolean
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
  ������:    UpdateCurInfoType, ���»�ȡ��ǰҳ������ͣ���ȷ����ǰ����ҳ��
  ����:      raimy
  ����:      2017.11.28
  ����:      hContainer: HWND; hInfoOp: HWND
  ����ֵ:    ��
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
