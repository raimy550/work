unit AutoOps;

interface

uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils;
// class COpsManager
type
  AutoOpType=(AutoOpType_None, AutoOpType_Export, AutoOpType_SearchClient);
  OpProcess=(OpExport_Login, OpExport_Select, OpExport_Export, OpExport_Sucess);
type
  COpsManager = class(TObject)
  private
    mOpType: AutoOpType;
    mCurOpProcess: OpProcess;
  public
    constructor Create();
    procedure StartOps(opType: AutoOpType);

end;

// class CThreadOps
type
  CThreadOps = class(TThread)
  private
    mAutoOpType: AutoOpType;
    mCurOpProcess: OpProcess;

  protected
  procedure Execute;override;
  procedure DoOpsTypeExport;
  procedure DoOpsTypeSearchClient;
  procedure DoProcessLogin;
  procedure DoProcessSelect;

  public
    constructor Create(autoType: AutoOpType);overload;
end;

implementation
// class CThreadOps
   procedure CThreadOps.Execute;
   begin
     while not Terminated do
     begin
        if mAutoOpType=AutoOpType_Export then
          DoOpsTypeExport
        else if mAutoOpType=AutoOpType_SearchClient then
          DoOpsTypeSearchClient;
        
         Utils.DebugOut('---------- Thread Execute');
        Sleep(500);
     end;
   end;
   
   constructor CThreadOps.Create(autoType: AutoOpType);
   begin
      inherited Create(False);
      mAutoOpType := autoType;
      mCurOpProcess := OpExport_Login;
   end;
   
   procedure CThreadOps.DoOpsTypeExport;
   begin
     if mCurOpProcess=OpExport_Login then
     begin
       DoProcessLogin;
     end
     else if mCurOpProcess=OpExport_Select then
     begin
       DoProcessSelect;
     end;
   end;

   procedure CThreadOps.DoOpsTypeSearchClient;
   var 
     nRet: Integer;
   begin
     if mCurOpProcess=OpExport_Login then
     begin
       nRet := Utils.WaitOpTimeOut(Utils.cntInjetWind, 1000*60*3);
      if nRet=0 then
        ExitThread(0);

     end
   end;
   
   procedure  CThreadOps.DoProcessLogin;
   var
     hParent, hTarget: HWND;
     tcl: TWinControl;
     pswEdit: TcxTextEdit;
   begin
      Utils.DebugOut('----------DoOpsExport');
        hParent := FindWindow(nil,PAnsiChar(Utils.cntLoginWind));
        Utils.DebugOut('----------DoOpsExport1');
        if hParent<>0 then
        begin
          Utils.DebugOut('----------DoOpsExport2');
          hTarget := Utils.FindeWindowBy(hParent, Integer(2), 'TcxTextEdit');
          if hTarget<>0 then
          begin
            Utils.DebugOut('----------DoOpsExport3');
            pswEdit := TcxTextEdit(Utils.GetInstanceFromhWnd(hTarget));
            pswEdit.SetTextBuf('123');
            hTarget := Utils.FindeWindowBy(hParent, 'ȷ��', 'TcxButton');
            Utils.ClickWindow(hTarget);
            mCurOpProcess := OpExport_Select;
          end;
          Utils.DebugOut('----------DoOpsExport4');

        end;
   end;

   procedure CThreadOps.DoProcessSelect;
   var
     hParent, hTarget: HWND;
   begin
      hParent := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
       if hParent<>0 then
       begin
       
       end;
   end;
   
// class COpsManager
   constructor COpsManager.Create;
   begin
     
   end;

   procedure COpsManager.StartOps(opType: AutoOpType);
   var
     opThread: CThreadOps;
   begin
      opThread := CThreadOps.Create(opType);
   end;

end.
