unit OpBases;

interface

uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils, MyLog;
const
  cntIdentOpName: string='name';
  cntIdentOpDate: string='date';
  
type
{操作类型}
  TOpType=(OpType_None, OpType_Export, OpType_SearchClient);
 
{步骤确认类型： 搜索， 窗口}
  VerifyType = (VerifyType_Search,VerifyType_Window);
    
{操作错误类型}
  OpResultType = (OpResultType_Sucess,OpResultType_Repeat, OpResultType_Die);
  

{ Forward declarations }
TOpStepBase = class;


{ TOpStruct }

  TOpStruct = class(TObject)
  public
    sectionName: string;
    opName:string;
    opDate:TDateTime;
  end;

  
{TOpTypeBase} 
TOpTypeBase = class(TObject)
  protected
    procedure ChangeStep(opStep: TOpStepBase);
    procedure SetResultType(opResult: OpResultType);
  public
    function DoStep():Boolean;
    function GetOpDate(): TDateTime;
    function GetSaveDateBegin(): TDateTime;
    function GetSaveDateTo(): TDateTime;
    procedure UpdateOpDate(dateTime: TDateTime);
    constructor Create(opStep: TOpStepBase; opSt:TOpStruct);overload;
    function GetResultType(): OpResultType;

  private
    mResult: OpResultType;
    mTOpStruct: TOpStruct;
    mStep: TOpStepBase;
    
end;
  
{TOpStepBase}  
TOpStepBase = class(TObject)
  public
    function DoAction(tOpType: TOpTypeBase): Boolean;
  protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;virtual;abstract;
    
  protected
    stepName : string;
    wndCaption, wndClassName: string;
end;


implementation
uses 
ConfigManager;

//==============================================================================
// TOpTypeBase
//==============================================================================
procedure TOpTypeBase.ChangeStep(opStep: TOpStepBase);
begin
  mStep := opStep;
end;

procedure TOpTypeBase.SetResultType(opResult: OpResultType);
begin
  mResult:=opResult;
end;

function TOpTypeBase.DoStep():Boolean;
begin
  Result := mStep.DoAction(Self);
end;

function TOpTypeBase.GetOpDate(): TDateTime;
begin
  Result := mTOpStruct.opDate;
end;

function TOpTypeBase.GetSaveDateBegin: TDateTime;
begin
  Result := mTOpStruct.opDate+1;
end;

function TOpTypeBase.GetSaveDateTo: TDateTime;
begin
   Result := Date-1;
end;

procedure TOpTypeBase.UpdateOpDate(dateTime: TDateTime);
begin
    TConfigManager.GetInstance.WriteConfig(mTOpStruct.sectionName, cntIdentOpDate, DateToStr(dateTime));
end;

constructor TOpTypeBase.Create(opStep: TOpStepBase; opSt:TOpStruct);
begin
   mStep := opStep;
   mTOpStruct := opSt;
end;

function TOpTypeBase.GetResultType: OpResultType;
begin
   Result:=mResult; 
end;

//==============================================================================
// TOpStepBase
//==============================================================================
function TOpStepBase.DoAction(tOpType: TOpTypeBase): Boolean;
begin
  Result := ActionImp(tOpType);
  if Result=False then
  begin
   tOpType.SetResultType(OpResultType_Die);
  end;
end;



end.
