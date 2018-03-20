unit OpSteps;
{操作步骤}

interface

uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils, MyLog, OpBases
,cxCalendar,Contnrs, DataTrans, uLkJSON;

type
{ TOpStepLogin }
  TOpStepLogin = class(TOpStepBase)
protected
  function ActionImp(tOpType: TOpTypeBase): Boolean;override;
end;

{ TOpStepSearchClient 客户筛选设置}
  TOpStepSearchClient = class(TOpStepBase)
protected
  function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
   procedure InitInner();override;
end;

{ TOpStepSearchStateMent 结算单查询}
  TOpStepSearchStateMent = class(TOpStepBase)
  private
    procedure InitInner;override;
  protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
  end;

{ TOpStepSearchCarAndOwerInfo 车主车辆信息查询}

  TOpStepSearchCarAndOwerInfo = class(TOpStepBase)
  private
    procedure InitInner;override;
   protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
  end;

{ TOpStepSearchMembership 会员卡查询}

  TOpStepSearchMembership = class(TOpStepBase)
  private
    procedure InitInner;override;

  protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;override; 
  end;


  
{ TOpStepSaveAndUpLoad 保存下载}

  TOpStepGridSaveAndUpLoad = class(TOpStepBase)
  private
    mPlateName: string;
    mHGridWndParent: HWND;
  protected
    function ActionImp(tOpType: TOpTypeBase): Boolean;override;
    procedure InitInner();override; 
  public
    constructor Create(hTarget:HWND; plateName:string);

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
 hParent, hTarget, hInjet, hTest: HWND;
 cxDataEdit :  TcxDateEdit;
 nRet:Integer;
 bRet: Boolean;
 trans:TDataTrans;
 jsBase: TlkJSONobject;
 fileContent, sRet,urlContent: string; 
begin

  hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
   hTest := Utils.FindeWindowBy(hInjet, '', 'TdxNavBar');
   if hTest<>0 then
   begin
     //CMyLog.DebugMsg('-------Find TdxNavBar');
     Utils.ClickPoint(60, 590);
     Utils.ClickPoint(68, 155);
     Utils.ClickPoint(85, 185);
     Utils.WaitOpTimeOut(Utils.cntInjectExe, Utils.cntWaitWndTime);
     Sleep(10000);
     Windows.SetFocus(hInjet);
     Utils.ClickPoint(183, 170);
     Utils.ClickPoint(560, 170);
   end;


    Result:=False;
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, wndCaption, wndClassName); 
      if hParent<>0 then
        begin
          hTarget :=  Utils.FindeWindowBy(hParent, Integer(26), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateBegin)));
          end;

          hTarget :=  Utils.FindeWindowBy(hParent, Integer(25), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateTo)));
          end;
          
          hTarget := Utils.FindeWindowBy(hParent, '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
            Sleep(10000);

          tOpType.ChangeStep(TOpStepGridSaveAndUpLoad.Create(hParent, wndCaption));
          Result := tOpType.DoStep();
          end;
            
        end;
     end;
    
end;

procedure TOpStepSearchClient.InitInner;
begin
   wndCaption := '客户筛选设置';
   wndClassName := 'TbsCustomFilterSetForm';
   
end;
//==============================================================================
// TOpSearchStateMent
//==============================================================================
function TOpStepSearchStateMent.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget, hInjet, hTest: HWND;
 cxDataEdit :  TcxDateEdit;
 nRet:Integer;
begin
    hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
   hTest := Utils.FindeWindowBy(hInjet, '', 'TdxNavBar');
   if hTest<>0 then
   begin
     Utils.ClickPoint(50, 540);
     Utils.ClickPoint(50, 185);
     Utils.ClickPoint(80, 240);
     Utils.WaitOpTimeOut(Utils.cntInjectExe, Utils.cntWaitWndTime);
     Sleep(10000);
     Windows.SetFocus(hInjet);
   end;
    
    Result:=False;
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, wndCaption, wndClassName); 
      if hParent<>0 then
        begin
          hTarget :=  Utils.FindeWindowBy(hParent, Integer(1), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateBegin)));
          end;

          hTarget :=  Utils.FindeWindowBy(hParent, Integer(2), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateTo)));
          end;
          
          hTarget := Utils.FindeWindowBy(hParent, '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
            Sleep(10000);
            tOpType.ChangeStep(TOpStepGridSaveAndUpLoad.Create(hParent, wndCaption));
            Result := tOpType.DoStep();
          end;
            
        end;
     end;    
end;

procedure TOpStepSearchStateMent.InitInner;
begin
   wndCaption := '结算单查询';
   wndClassName := 'TbsBalanceAccountQueryForm';
   
end;

//==============================================================================
// TOpStepSearchCarAndOwerInfo
//==============================================================================
 function TOpStepSearchCarAndOwerInfo.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget,hInjet,hTest: HWND;
 hTPanels : array of LongWord;
 cxDataEdit :  TcxDateEdit;
 h:HWND;
 nRet, index:Integer;
begin

   hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
   hTest := Utils.FindeWindowBy(hInjet, '', 'TdxNavBar');
   if hTest<>0 then
   begin
     //CMyLog.DebugMsg('-------Find TdxNavBar');
     Utils.ClickPoint(60, 590);
     Utils.ClickPoint(60, 142);
     Utils.ClickPoint(70, 155);
     Utils.WaitOpTimeOut(Utils.cntInjectExe, Utils.cntWaitWndTime);
     Sleep(10000);
     Windows.SetFocus(hInjet);
   end;

    Result:=False;
    index:=0;
    
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, wndCaption, wndClassName);

      if hParent<>0 then
      begin
        h := GetWindow(hParent, GW_CHILD); {第一个子窗口}
        while h <> 0 do
        begin
          SetLength(hTPanels, index+1);
          hTPanels[index] := h;
          index := index+1;
          h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
        end;
      end;

      //CMyLog.DebugMsg(Format('----hTPanels size = %d', [Length(hTPanels)]));
      if (hParent<>0) and (Length(hTPanels)=4) then
        begin
          //车辆信息
//          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[1]), Integer(3), 'TcxDateEdit');
//          if hTarget<>0 then
//          begin
//           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
//           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetOpDate+1)));
//          end;
//          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[1]), Integer(4), 'TcxDateEdit');
//          if hTarget<>0 then
//          begin
//           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
//           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(Date())));
//          end;
//          
//          hTarget := Utils.FindeWindowBy(HWND(hTPanels[1]), '查询', 'TcxButton');
//          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
//          if nRet<>0 then
//            Result := Utils.SaveGridData(HWND(hTPanels[0]), Utils.GetDllPath, 
//           Format('车辆信息_%s-%s.txt', [DateToStr(tOpType.GetSaveDateBegin), DateToStr(tOpType.GetSaveDateTo)]))
//          else
//          Exit;

          //HWND(hTPanels[3])
          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[3]), Integer(3), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateBegin)));
          end;
          hTarget :=  Utils.FindeWindowBy(HWND(hTPanels[3]), Integer(4), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateTo)));
          end;
          
          hTarget := Utils.FindeWindowBy(HWND(hTPanels[3]), '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
            Sleep(10000);
            tOpType.ChangeStep(TOpStepGridSaveAndUpLoad.Create(HWND(hTPanels[2]), wndCaption));
            Result := tOpType.DoStep();
          end;
          
            
        end;
     end;    
end;

procedure TOpStepSearchCarAndOwerInfo.InitInner;
begin
   wndCaption := '车主车辆管理';
   wndClassName := 'TbsCustomerMangageForm';
   
end;


{ TOpStepGridSaveAndUpLoad }

function TOpStepGridSaveAndUpLoad.ActionImp(tOpType: TOpTypeBase): Boolean;
var
  fileContent, urlContent, sRet: string;
  jsBase:TlkJSONobject;
  trans:TDataTrans;
  bRet:Boolean;
begin 
      Result:= False;
      mSveFileName:=Format('%s_%s-%s.txt', 
     [mPlateName,FormatDateTime('yyyymmdd', tOpType.GetSaveDateBegin), 
     FormatDateTime('yyyymmdd', tOpType.GetSaveDateTo)]);
     bRet := Utils.SaveGridData(mHGridWndParent, Utils.GetDllPath,mSveFileName);
     Result:=bRet; 
      
//     if bRet=True then
//     begin
//        fileContent:=Utils.ReadFileToHex(Utils.GetDllPath+mSveFileName);
//        jsBase := TlkJSONobject.Create(True);
//        jsBase.Add('fileName', mSveFileName);
//        jsBase.Add('fileData', fileContent);
//
//        trans:= TDataTrans.Create;
//        urlContent:=TlkJSON.GenerateText(jsBase);
//        urlContent := StringReplace(urlContent, ' ', '', [rfReplaceAll]);
//        sRet := trans.HttpPost(Utils.cntUrlUpLoadFile, urlContent);
//        if sRet='error'  then
//           Result := False
//        else
//          Result := True;    
//     end;
end;

constructor TOpStepGridSaveAndUpLoad.Create(hTarget: HWND;
  plateName: string);
begin
   mHGridWndParent := hTarget;
   mPlateName :=  plateName;
end;

procedure TOpStepGridSaveAndUpLoad.InitInner;
begin

end;

{ TOpStepSearchMembership }

function TOpStepSearchMembership.ActionImp(tOpType: TOpTypeBase): Boolean;
var
 hParent, hTarget, hInjet, hTest: HWND;
 cxDataEdit :  TcxDateEdit;
 nRet:Integer;
begin
    hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
   hTest := Utils.FindeWindowBy(hInjet, '', 'TdxNavBar');
   if hTest<>0 then
   begin
     Utils.ClickPoint(60, 590);
     Utils.ClickPoint(70, 225);
     Utils.ClickPoint(80, 280);
     Utils.WaitOpTimeOut(Utils.cntInjectExe, Utils.cntWaitWndTime);
     Sleep(10000);
     Windows.SetFocus(hInjet);
   end;
    
    Result:=False;
     hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     if hParent <>0 then
     begin
      hParent := Utils.FindeWindowBy(hParent, wndCaption, wndClassName); 
      if hParent<>0 then
        begin
          hTarget :=  Utils.FindeWindowBy(hParent, Integer(2), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget));
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateBegin)));
          end;

          hTarget :=  Utils.FindeWindowBy(hParent, Integer(3), 'TcxDateEdit');
          if hTarget<>0 then
          begin
           cxDataEdit:=TcxDateEdit(Utils.GetInstanceFromhWnd(hTarget)); 
           cxDataEdit.SetTextBuf(PAnsiChar(DateToStr(tOpType.GetSaveDateTo)));
          end;
          
          hTarget := Utils.FindeWindowBy(hParent, '查询', 'TcxButton');
          nRet := Utils.ClickWindow(hTarget, Utils.cntWaitTime);
          if nRet<>0 then
          begin
            Sleep(10000);
            tOpType.ChangeStep(TOpStepGridSaveAndUpLoad.Create(hParent, wndCaption));
            Result := tOpType.DoStep();
          end;
            
        end;
     end;    
  
end;


procedure TOpStepSearchMembership.InitInner;
begin
   wndCaption := '会员卡查询';
   wndClassName := 'TbsMemberCardInfoQueryForm';
   
end;

end.
