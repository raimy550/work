unit AutoOps;

interface

uses Windows, SysUtils, Classes, Variants, Controls, cxTextEdit, Utils;
// class COpsManager
type
  AutoOpType=(AutoOpType_None, AutoOpType_Export);
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
  procedure DoOpsExport;

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
          DoOpsExport;
         Utils.DebugOut('----------Execute');
        Sleep(500);
     end;
   end;
   
   constructor CThreadOps.Create(autoType: AutoOpType);
   begin
      inherited Create(False);
      mAutoOpType := autoType;
      mCurOpProcess := OpExport_Login;
   end;

   procedure CThreadOps.DoOpsExport;
   var
     hParent, hTarget: HWND;
     tcl: TWinControl;
     pswEdit: TcxTextEdit;
   begin
     if mCurOpProcess=OpExport_Login then
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
            Terminate;
          end;
          Utils.DebugOut('----------DoOpsExport4');

        end;
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