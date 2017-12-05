unit OpSteps;
{操作步骤}

interface

uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils, MyLog, OpBases
,cxCalendar,Contnrs;

type
{ TOpStepLogin }
  TOpStepLogin = class(TOpStepBase)
protected
  function ActionImp(tOpType: TOpTypeBase): Boolean;override;
end;

{ TOpStepSearchClient }
  TOpStepSearchClient = class(TOpStepBase)
protected
  function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
end;

{ TOpStepSearchStateMent }
  TOpStepSearchStateMent = class(TOpStepBase)
  protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
  end;

{ TOpStepSearchCarAndOwerInfo }

  TOpStepSearchCarAndOwerInfo = class(TOpStepBase)
   protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
  end;

  
implementation

//==============================================================================
// TOpStepLogin
//==============================================================================

function TOpStepLogin.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget: HWND;
 tcl: TWinControl;
 pswEdit: TcxTextEdit;
begin
   Result:=False;
    hParent := FindWindow(nil,PAnsiChar(Utils.cntLoginWind));
    if hParent<>0 then
    begin
      hTarget := Utils.FindeWindowBy(hParent, Integer(2), 'TcxTextEdit');
      if hTarget<>0 then
      begin
        pswEdit := TcxTextEdit(Utils.GetInstanceFromhWnd(hTarget));
        pswEdit.SetTextBuf('123');
        hTarget := Utils.FindeWindowBy(hParent, '确定', 'TcxButton');
        Utils.ClickWindow(hTarget);
        Result:=True;
      end;
    end;
end;

//==============================================================================
// TOpStepSearchClient
//==============================================================================
function TOpStepSearchClient.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget: HWND;
 cxDataEdit :  TcxDateEdit;
 nRet:Integer;
begin
    Result:=False;
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, '客户筛选设置', 'TbsCustomFilterSetForm'); 
      if hParent<>0 then
        begin
          hTarget :=  Utils.FindeWindowBy(hParent, Integer(26), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetOpDate+1)));
          end;

          hTarget :=  Utils.FindeWindowBy(hParent, Integer(25), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(Date()-1)));
          end;
          
          hTarget := Utils.FindeWindowBy(hParent, '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
            Sleep(5000);
           Utils.SaveGridData(hParent, Utils.GetDllPath, 
           Format('客户筛选设置%s-%s.txt', [DateToStr(tOpType.GetSaveDateBegin), DateToStr(tOpType.GetSaveDateTo)]));
           
           //Utils.SaveGridData(hParent, Utils.GetDllPath, '客户筛选设置.txt');
           Result:=True;
          end;
            
        end;
     end;
    
end;
//==============================================================================
// TOpSearchStateMent
//==============================================================================
function TOpStepSearchStateMent.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget: HWND;
 cxDataEdit :  TcxDateEdit;
 nRet:Integer;
begin
    Result:=False;
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, '结算单查询', 'TbsBalanceAccountQueryForm'); 
      if hParent<>0 then
        begin
          hTarget :=  Utils.FindeWindowBy(hParent, Integer(1), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetOpDate+1)));
          end;

          hTarget :=  Utils.FindeWindowBy(hParent, Integer(2), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(Date())));
          end;
          
          hTarget := Utils.FindeWindowBy(hParent, '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
           Utils.SaveGridData(hParent, Utils.GetDllPath, '结算单查询.txt');
           Result:=True;
          end;
            
        end;
     end;    
end;

//==============================================================================
// TOpStepSearchCarAndOwerInfo
//==============================================================================
 function TOpStepSearchCarAndOwerInfo.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget: HWND;
 hTPanels : array of LongWord;
 cxDataEdit :  TcxDateEdit;
 h:HWND;
 nRet, index:Integer;
begin
    Result:=False;
    index:=0;
    
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, '车主车辆管理', 'TbsCustomerMangageForm');

      if hParent<>0 then
      begin
        h := GetWindow(h, GW_CHILD); {第一个子窗口}
        while h <> 0 do
        begin
          SetLength(hTPanels, index+1);
          hTPanels[index] := h;
          Inc(index);
          h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
        end;
      end;

      if (hParent<>0) and (Length(hTPanels)=4) then
        begin
          //车辆信息
          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[1]), Integer(3), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetOpDate+1)));
          end;
          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[1]), Integer(4), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(Date())));
          end;
          
          hTarget := Utils.FindeWindowBy(HWND(hTPanels[1]), '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
           Utils.SaveGridData(HWND(hTPanels[0]), Utils.GetDllPath, '车辆信息.txt')
          else
          Exit;

          //车主信息
          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[3]), Integer(3), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetOpDate+1)));
          end;
          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[3]), Integer(4), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(Date())));
          end;
          
          hTarget := Utils.FindeWindowBy(HWND(hTPanels[3]), '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
           Utils.SaveGridData(HWND(hTPanels[2]), Utils.GetDllPath, '车主信息.txt');
           Result:=True;
          end;
          
            
        end;
     end;    
end;


end.
