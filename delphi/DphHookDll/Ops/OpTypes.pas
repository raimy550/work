unit OpTypes;

interface

uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils, MyLog,OpBases;

type
  TOpTypeSearchClient = class(TOpTypeBase)
  public
    constructor Create(opStep: TOpStepBase; opSt: TOpStruct);overload;
     
  end;

implementation
//==============================================================================
// TOpTypeSearchClient
//==============================================================================
constructor TOpTypeSearchClient.Create(opStep: TOpStepBase; opSt: TOpStruct);
begin
  inherited Create(opStep, opSt);
  
end;

end.
