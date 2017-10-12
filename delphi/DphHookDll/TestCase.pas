unit TestCase;

interface
  uses
  Windows,
  Messages,
  Dialogs,
  Grids,
  cxGrid,
  Controls,
  cxButtons,
  StdCtrls,
  TlHelp32,
  SysUtils,
  cxGridLevel,
  cxGridDBTableView,
  cxGridTableView,
  cxGridCustomView,
  cxDBEdit,
  cxCustomData,
  cxTreeView,
  cxCheckBox,
  dxNavBar,
  dxNavBarCollns,
  ComCtrls,
  Utils,
  DataManager,
  uLkJSON,
  AutoOps,
  MyLog,
  DataTrans;
type
  CTestCase = class(TObject)
  private
    mGridCount : Integer;
    mCOpsManager: COpsManager;
    strTab: string;
  private
    procedure   TestWindows();
    procedure   TestWindowsImp(h: HWND);
    procedure   DoTestWindows(h: HWND);
    procedure   DoTestDxNavBar(h: HWND);
    procedure   DoTestTreeView(h: HWND);
    procedure   GetTcxGridData(grid: TcxGrid);
    
    procedure  TestAutoOps();
    procedure  CatchWindowsData();
    procedure  CatchWindowsDataImp(h: HWND);
    procedure  DoCatchWindows(h: HWND);
    
  public
    procedure StartTest();
    
  end;
implementation

  procedure CTestCase.StartTest;
  begin
    mCOpsManager :=COpsManager.Create;
  //  测试控件类型
  //TestWindows();
    
  //  测试自动操作
  TestAutoOps();

  //  抓数据
  //CatchWindowsData();
   
  end;

  procedure CTestCase.DoTestTreeView(h: HWND);
  var
    bRet: Boolean;
    cxTreeView: TcxTreeView;
    treeNode: TTreeNode;
    twcl: TWinControl;
    tcl: TControl;
    i: Integer;
  begin
    bRet := Utils.ClassNameEqual(h, 'TcxTreeView');
    if bRet then
    begin
      CMyLog.DebugMsg('-----------TcxTreeView find');
      twcl := Utils.GetInstanceFromhWnd(h);
      CMyLog.DebugMsg('-----------TcxTreeView find1');
      if (twcl<>nil) then
      begin
        CMyLog.DebugMsg('-----------TcxTreeView find2');
        cxTreeView := TcxTreeView(twcl);

         if (cxTreeView=nil) or (cxTreeView.Items=nil) then
         begin
         CMyLog.DebugMsg('-----------TcxTreeView nil');
         Exit;
         end;
       
        CMyLog.DebugMsg('-----------TcxTreeView find3');
     
        CMyLog.DebugMsg(Format('%s---%d', ['TcxTreeView-items',cxTreeView.Items.Count]));
        if cxTreeView.Items.Count=0 then
        Exit;
      
        for i:=0 to cxTreeView.Items.Count-1 do
        begin
           treeNode:= cxTreeView.Items[i];
           CMyLog.DebugMsg(Format('index:%d---%s', [i,treeNode.Text]));
         
        end;
      end;
    end;
  end;
  
  procedure CTestCase.DoTestDxNavBar(h: HWND);
  var
    bRet: Boolean;
    dxNavBar: TdxNavBar;
    dxNavBarItem: TdxNavBarItem;
    dxNavBarGroup: TdxNavBarGroup;
    twcl: TWinControl;
    tcl: TControl;
    i: Integer;
  begin
    bRet := Utils.ClassNameEqual(h, 'TdxNavBar');
    if bRet then
    begin
      CMyLog.DebugMsg(Format(('%s--%s'),['TdxNavBar find', Utils.GetClassNameBy(h)]));
      twcl := Utils.GetInstanceFromhWnd(h);
      CMyLog.DebugMsg('-----------TdxNavBar find1');
      if (twcl<>nil) then
      begin
        CMyLog.DebugMsg('-----------TdxNavBar find2');
        dxNavBar := TdxNavBar(twcl);
  //      tcl := dxNavBar.FindChildControl('维修管理');
  //      if tcl <> nil then
  //       begin
  //         CMyLog.DebugMsg('-----------维修管理 find');
  //         Utils.ClickWindow(h);
  //       end;

         if dxNavBar=nil then
         begin
         CMyLog.DebugMsg('-----------dxNavBar nil');
         Exit;
         end;
       
        CMyLog.DebugMsg('-----------TdxNavBar find3');

        CMyLog.DebugMsg(Format('%s---%d', ['dxNavBar-items',dxNavBar.Items.Count]));
        CMyLog.DebugMsg(Format('%s---%d', ['dxNavBar-groups',dxNavBar.Groups.Count]));
        if dxNavBar.Groups.Count=0 then
        Exit;
      
        for i:=0 to dxNavBar.Groups.Count-1 do
        begin
           CMyLog.DebugMsg(Format('index:%d---%s', [i,dxNavBar.Groups.Items[i].Caption]));
         
        end;
      end;
    end;
  end;
  
  procedure CTestCase.DoTestWindows(h: HWND);
  var
    buf: array[0..255] of Char; {这个缓冲区是获取类名用的, 如果不需要可以删除}
    s: AnsiString;
    s1: AnsiString;
    nRet: Integer;
    bRet, bRet1: Boolean;
    nRet1: Integer;
    count: Integer;
    Grid, Grid1: TStringGrid;
    tGrid: TcxGrid;
    cxBtn: TcxButton;
    cxDBDateEdit: TcxDBDateEdit;
    dxNavBar: TdxNavBar;
  
    i: Integer;
    tcl: TWinControl;
    cxCheckBox: TcxCheckBox ;
  begin
    if Utils.FilterControls(h)=False then
      Exit;

     //DoTestTreeView(h);
     DoTestDxNavBar(h);
    
    tcl := Utils.GetInstanceFromhWnd(h);
    if tcl<>nil then
  //  bRet := Utils.ClassNameContains(h, 'TcxDBDateEdit');
  //    bRet := Utils.ClassNameContains(h, 'TcxGrid');
  //  bRet := Utils.ClassNameContains(h, 'TcxCheckBox');
    if bRet then
      begin
  //    cxCheckBox := TcxCheckBox(tcl);
  //    ShowMessageFmt('%s',['TcxCheckBox-----start1']);
  //    if cxCheckBox.Checked then
  //    ShowMessageFmt('%s--%s',['TcxCheckBox','是'])
  //    else
  //    ShowMessageFmt('%s--%s',['TcxCheckBox','否']);
  //    ShowMessageFmt('%s',['TcxCheckBox-----end']);


  //    cxDBDateEdit := TcxDBDateEdit(tcl);
  //    cxDBDateEdit.SetTextBuf(PAnsiChar('2012-07-08 23:12:12'));
  ////    cxDBDateEdit.Date := StrToDateTime('2012-07-08 23:12:12');
  ////    ShowMessageFmt('%s', ['-----------3']);

  //    tGrid := TcxGrid(Utils.GetInstanceFromhWnd(h));
  //    if(tGrid<>nil)  then
  //      begin
  ////        s1 := Format('tcxgrid  find: %x view count = %d ', [Integer(@tGrid), tGrid.Levels.Count]);
  ////        MessageBox(0, PAnsiChar(AnsiString(s1)), 'tcxgrid', MB_OK);
  //        GetTcxGridData(tGrid);
  //      end

  ////    Grid := TStringGrid(Utils.GetInstanceFromhWnd(h));
  //    Grid := TStringGrid(FindControl(h));
  //    Grid1 := TStringGrid(Utils.GetInstanceFromhWnd(h));
  //    if(Grid<>nil)  then
  //      begin
  //        s1 := Format('TStringGrid  find: %x , %x', [Integer(@Grid), Integer(@Grid1)]);
  //        MessageBox(0, PAnsiChar(AnsiString(s1)), 'TStringGrid', MB_OK);
  //        GetGridData(Grid);
  //      end

  // TcxButton
  //    cxBtn := TcxButton(Utils.GetInstanceFromhWnd(h));
  //    if(cxBtn<>nil)  then
  //      begin
  //       i := cxBtn.GetTextLen();
  //       cxBtn.GetTextBuf(buf, 255);
  //       MessageBox(0, buf,'Button', MB_OK);
  //       ShowMessageFmt('%s---%d', ['TcxButton Text len=', i]);
  //      end
    end;
  end;

  procedure CTestCase.GetTcxGridData(grid: TcxGrid);
  var
    FileName: string;
    cxGridDBTableView: TcxGridDBTableView;
    cxView, cxView1: TcxCustomGridView;
    i,j, nRowCount,nColCount: Integer;
    rowInfo: TcxRowInfo;
    s, s1: string;
    p: Pointer ;
    sStr: ShortString;

  begin
      if grid.ActiveLevel = nil then
        ShowMessageFmt('%s',['ActiveLevel is nil'])
      else
      begin
         cxView := grid.FocusedView;
   
         if cxView=cxView1 then
          ShowMessageFmt('%s',['ActiveLevelGridView is FocusedView']);


         if cxView=nil then
           ShowMessageFmt('%s',['cxGridView is nil']);

         if cxView <> nil then
         begin
           if cxView.DataController=nil then
              ShowMessageFmt('%s',['DataController is nil'])
           else
           begin
             //ShowMessageFmt('%s',['DataController is not nil']);
             nRowCount := cxView.DataController.GetRowCount();
             //ShowMessageFmt('%s%d',['GetRecordCount:', nRowCount]);
             nColCount := cxView.DataController.GetItemCount();
             //ShowMessageFmt('%s%d',['GetItemCount:', nColCount]);
             for i := 0 to nRowCount-1 do
             begin
             if i<>0 then s := Concat(s, Char(13), Chr(10));
              for j:=0 to nColCount-1 do
               begin
                 s1 := Format('%s    ', [cxView.DataController.Values[i,j]]);
                 s := Concat(s, s1);
               end;
             end;
           end;

           if nRowCount>0 then
           begin
              SaveData(Utils.GetSaveDir()+Format('%s%d', ['grid', mGridCount])+'.txt',s, False);
              mGridCount := mGridCount+1;
           end;

            
  //       p := cxView.ClassInfo();
  //       sStr := cxView.ClassName();
  //        if cxView is TcxGridTableView then
  //          ShowMessageFmt('%s',['cxGridView is TcxGridTableView']);
  //
  //        if cxView is TcxGridDBTableView then
  //          ShowMessageFmt('%s',['cxGridView is TcxGridDBTableView']);
  //
  //       grid.FocusedView :=  TcxGridTableView(grid.FocusedView);
  //
  //        if grid.FocusedView is TcxGridTableView then
  //          ShowMessageFmt('%s',['FocusedView is TcxGridTableView']);
  //          
  ////       FileName := ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName;
  ////       cxExportGrid4Link.ExportGrid4ToText(FileName, grid, True, True);
         end;
      end;
  //   FileName := ExtractFilePath(ParamStr(0))+Utils.cntSaveGridDataName;
  //   ExportGridToText(FileName, grid, True, True);
  end;
  
  procedure CTestCase.TestWindowsImp(h: HWND);
  begin
    DoTestWindows(h);
    h := GetWindow(h, GW_CHILD); {第一个子窗口}
    while h <> 0 do
    begin
      TestWindowsImp(h); {递归}
      h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
    end;
  end;
  
  procedure CTestCase.TestWindows;
  var
    h : HWND;
  begin
     h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     TestWindowsImp(h);
  end;

  procedure CTestCase.TestAutoOps;
  begin
     CMyLog.DebugMsg('--------TestAutoOps');
      mCOpsManager.StartOps(AutoOpType_Export);
  end;
  
  procedure CTestCase.DoCatchWindows(h: HWND);
  var
    buf: array[0..255] of Char; {这个缓冲区是获取类名用的, 如果不需要可以删除}
    nRet, nRet1, tab: Integer;
    tcl: TWinControl;
    s, s1: string;
  begin
   // ShowMessageFmt('GetClassName-----%s', [buf]);
    if Utils.FilterControls(h) then
    begin
      tcl := Utils.GetInstanceFromhWnd(h);
      if tcl<>nil then
        begin
          if tcl.Visible then
          begin
            tab := tcl.TabOrder;
            tcl.GetTextBuf(buf, 255);
            //ShowMessageFmt('%s----%d ', [buf, tab]);
            s1 := Format('%s----%d ', [buf, tab]);
            s := Concat(s, Char(13), Char(10));
            strTab := Concat(strTab, s);
            strTab := Concat(strTab, s1);
          end;
        end;
    end;
  end;
  
  procedure CTestCase.CatchWindowsDataImp(h: HWND);
  begin
    DoCatchWindows(h);
    h := GetWindow(h, GW_CHILD); {第一个子窗口}
    while h <> 0 do
    begin
      CatchWindowsDataImp(h); {递归}
      h := GetWindow(h, GW_HWNDNEXT); {下一个子窗口}
    end;
  end;
  
  procedure CTestCase.CatchWindowsData;
  var
    h:HWND;
  begin
      h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
      CatchWindowsDataImp(h);
     ShowMessageFmt('%s', [strTab]);
     Utils.SaveData(Utils.GetSaveDir+Utils.cntCatchSaveAllDataName,
                strTab, False);
  end;
end.
