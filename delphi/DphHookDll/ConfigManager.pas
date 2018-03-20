unit ConfigManager;

interface
uses Windows, SysUtils, Classes, Variants, Utils, MyLog, IniFiles,Contnrs;

type
{ TConfigManager }

  TConfigManager = class(TObject)
  private
  private
    mInitFile: TIniFile;

    mExePath: string;

    mOpList: TObjectList;

    mLoginCompany, mLoginUserCode, mLoginUserPsw: string;
    
  protected
    
  public
    class function GetInstance: TConfigManager;
    class function NewInstance:TObject;override;
    procedure FreeInstance;override;
    
    constructor Create;
    function GetExePath():string;
    function GetLoginCompany():string;
    function GetLoginUserCode():string;
    function GetLoginUserPsw():string;
    function GetConfigOps():TObjectList;
    procedure WriteConfig(setion,ident,value:string);
    procedure UpdateAutoOps();
    procedure UpdateLoginInfo();
    function  IsAllOpsOperatedAccordDate(date:TDateTime): Boolean;
  private
    procedure Init;
    procedure InitAutoOps();
    procedure InitLoginInfo();
    
    
  published
  end;



implementation
uses
  OpBases;

var
  gConfigManager: TConfigManager=nil;
  
  constructor TConfigManager.Create;
  begin
    Init;  
  end;

  class function TConfigManager.GetInstance:TConfigManager;
  begin
      if not Assigned(gConfigManager) then 
        gConfigManager:=TConfigManager.Create;
        Result := gConfigManager;
  end;

  class function TConfigManager.NewInstance:TObject;
  begin
    if not Assigned(gConfigManager) then
       gConfigManager:=TConfigManager(inherited NewInstance);
    Result:= gConfigManager;
  end;

  procedure TConfigManager.FreeInstance;
  begin
    inherited;
    gConfigManager:=nil;
  end;
  
  function TConfigManager.GetExePath: string;
begin
  Result:=mExePath;
end;

procedure TConfigManager.Init;
  var
    path, tmp:string;
    bRet:Boolean;
    stOp: TOpStruct;
  begin
    mOpList:=TObjectList.Create;
    path := Utils.GetDllPath();
    mInitFile := TIniFile.Create(path+Utils.cntCfgFileName);
    mExePath := mInitFile.ReadString('ExePath', 'path', '');

    InitLoginInfo(); 
    InitAutoOps();
  end;


procedure TConfigManager.InitAutoOps;
var
  stOp: TOpStruct;
  strRet, tmp: string;
  i:Integer;
begin
    mOpList.Clear;
    i:=0;
    strRet := mInitFile.ReadString(Format('AutoOp%d', [i]), cntIdentOpName, '');
 //   stOp := TOpStruct.Create;
    
    while strRet <> '' do
    begin
      stOp := TOpStruct.Create;
      stOp.opName := strRet;
      stOp.sectionName := Format('AutoOp%d', [i]);
      tmp:=mInitFile.ReadString(Format('AutoOp%d', [i]), cntIdentOpDate, '');
      stOp.opDate := StrToDate(tmp);
      
      mOpList.Add(stOp);
     // CMyLog.DebugMsg(Format('TConfigManager--add %d, opName=%s', [i, stOp.opName]));
      Inc(i); 
      strRet:= mInitFile.ReadString(Format('AutoOp%d', [i]), cntIdentOpName, '');
    end;
    
end;

function TConfigManager.GetConfigOps: TObjectList;
begin
  Result := mOpList;
end;

procedure TConfigManager.WriteConfig(setion, ident, value: string);
begin
  mInitFile.WriteString(setion, ident, value);
end;

procedure TConfigManager.UpdateAutoOps;
begin
  InitAutoOps;
end;

procedure TConfigManager.InitLoginInfo;
begin
    mLoginCompany :=mInitFile.ReadString('LoginInfo', 'companyName', ''); 
    mLoginUserCode :=mInitFile.ReadString('LoginInfo', 'userCode', ''); 
    mLoginUserPsw :=mInitFile.ReadString('LoginInfo', 'userPsw', ''); 
end;

procedure TConfigManager.UpdateLoginInfo;
begin
   InitLoginInfo();
end;

function TConfigManager.GetLoginCompany: string;
begin
  Result := mLoginCompany;
end;

function TConfigManager.GetLoginUserCode: string;
begin
  Result:=mLoginUserCode
end;

function TConfigManager.GetLoginUserPsw: string;
begin
   result:=mLoginUserPsw;
end;

function TConfigManager.IsAllOpsOperatedAccordDate(
  date: TDateTime): Boolean;
var
  nCount,i :Integer;
  stOp: TOpStruct;
begin
  UpdateAutoOps();
  nCount := mOpList.Count;
  Result := True;
  for i:=0 to nCount-1 do 
  begin
    stOp := TOpStruct(mOpList.Items[i]);
    if stOp.opDate<>(date-1) then
    begin
      Result:=False;
      Exit;
    end;
  end;
  
end;

end.
