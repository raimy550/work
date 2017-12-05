unit OpManager;

interface
uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils, 
OpBases, OpSteps, OpTypes, MyLog, ConfigManager, Contnrs, cxDBLookupComboBox;

type

{ Forward declarations }
TOpMonitorThread = class;

{ TOpManager }
   TOpManager = class(TObject)
   public
    procedure StartOp(opSt: TOpStruct);overload;
    procedure StartOps();
    constructor Create();
    function IsLogin():Boolean;
    procedure SetLogin(bLogin:boolean);
   private 
     procedure DoCommLoginOp();
   private
     mOpType: TOpTypeBase;
     mConfigManager: TConfigManager;
     mTOpMonitorThread: TOpMonitorThread;
     mLogin:Boolean;
   end;

{ TOpMonitorThread }

  TOpMonitorThread = class(TThread)
  private
    mOpManager : TOpManager;
  protected
    procedure Execute;override;
  public
    constructor Create(opManager: TOpManager);overload;

  end;


implementation
//==============================================================================
// TOpManager
//==============================================================================

constructor TOpManager.Create;
begin
  mConfigManager := TConfigManager.GetInstance;
  mTOpMonitorThread := TOpMonitorThread.Create(Self);
  mLogin:=False;  
end;

procedure TOpManager.StartOps;
var 
  opList:TObjectList;
  i:Integer;
  stOp: TOpStruct;
begin

  if mLogin=False then
    DoCommLoginOp();

  if mLogin=False then
  begin
    CMyLog.DebugMsg('----Login fail!');
    Exit;
  end ;
//  else
//    CMyLog.DebugMsg('----Login Sucess!');


  opList:=mConfigManager.GetConfigOps();
  for i:=0 to opList.Count-1 do
  begin
     stOp := TOpStruct(opList.Items[i]);
     StartOp(stOp);
  end;
end;

procedure TOpManager.StartOp(opSt: TOpStruct);
var
  bRet: Boolean;
begin
   if opSt.opDate < Date()-1 then
   begin
     //TOpThread.Create(opSt);
     if opSt.opName='SearchClient' then
     mOpType:=TOpTypeSearchClient.Create(TOpStepSearchClient.Create, opSt);
     
     bRet := mOpType.DoStep();
     if bRet then
     begin
        //CMyLog.DebugMsg('--------------Sucess');
        mOpType.UpdateOpDate(mOpType.GetSaveDateTo);
        mConfigManager.UpdateAutoOps;
     end     
     else
     begin
        //CMyLog.DebugMsg('--------------Fail');
        if  OpResultType_Die=mOpType.GetResultType then
        begin
         // Utils.KillAppExe(TConfigManager.GetInstance.GetExePath);
        end;
     end;
       
        
   end;
end;

 function TOpManager.IsLogin: Boolean;
begin
    Result:=mLogin;
end;

procedure TOpManager.SetLogin(bLogin: boolean);
begin
 mLogin:=bLogin;
end;

procedure TOpManager.DoCommLoginOp;
var
  h, hTarget:HWND;
  pswEdit, codeEdit: TcxTextEdit;
  companyEdit: TcxLookupComboBox;
  nRet:Cardinal;
begin
   if mLogin=False then
   begin
     h:=FindWindow(nil, PAnsiChar(Utils.cntInjetWind));
     if h<>0 then
     begin
       mLogin := True;
       Exit;
     end;

     h := Utils.WaitForWindow(Utils.cntLoginWind, Utils.cntWaitWndTime, 1000);
     if h<>0 then
     begin
       hTarget := Utils.FindeWindowBy(h, Integer(0), 'TcxLookupComboBox');
      if hTarget<>0 then
      begin
        companyEdit := TcxLookupComboBox(Utils.GetInstanceFromhWnd(hTarget));
        companyEdit.SetTextBuf(PAnsiChar(TConfigManager.GetInstance.GetLoginCompany));
      end;

       hTarget := Utils.FindeWindowBy(h, Integer(1), 'TcxTextEdit');
      if hTarget<>0 then
      begin
      codeEdit := TcxTextEdit(Utils.GetInstanceFromhWnd(hTarget));
        codeEdit.SetTextBuf(PAnsiChar(TConfigManager.GetInstance.GetLoginUserCode));
      end;

       hTarget := Utils.FindeWindowBy(h, Integer(2), 'TcxTextEdit');
      if hTarget<>0 then
      begin
        pswEdit := TcxTextEdit(Utils.GetInstanceFromhWnd(hTarget));
        pswEdit.SetTextBuf(PAnsiChar(TConfigManager.GetInstance.GetLoginUserPsw));
      end;

      hTarget := Utils.FindeWindowBy(h, 'È·¶¨', 'TcxButton');
      Utils.ClickWindow(hTarget);


      h := Utils.WaitForWindow(Utils.cntInjetWind, Utils.cntWaitWndTime, 1000);
      if h<>0 then
       nRet := WaitOpTimeOut(Utils.cntInjetWind, Utils.cntWaitWndTime);
       if nRet <> 0 then
          mLogin :=  True;
     end;
      
   end;
end;

//==============================================================================
// TOpMonitorThread
//==============================================================================
constructor TOpMonitorThread.Create(opManager : TOpManager);
begin 
  inherited Create(False);
  mOpManager := opManager; 
end;

procedure TOpMonitorThread.Execute;
var
  curTime: TDateTime ;
  Hour, Min, Sec, MSec:Word; 
begin
  FreeOnTerminate := True;
  curTime := Now;
  DecodeTime(curTime, Hour, Min, Sec, MSec); 
 
  while not terminated do
  begin
    if Hour>=Utils.cntAutoOpTime then
    begin
     mOpManager.StartOps;
    end;
    
    Sleep(Utils.cntTimerIntervalAutoOp);  
  end; 
end;

end.
