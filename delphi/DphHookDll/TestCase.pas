unit TestCase;

interface
  uses
  Windows,Messages,Dialogs,cxGrid,Controls,SysUtils,Classes,
  cxGridDBTableView,cxGridTableView,cxGridCustomView,cxDBEdit,cxCustomData,
  cxTreeView,cxCheckBox,dxNavBar,dxNavBarCollns,ComCtrls,Utils,
  AutoOps,MyLog,Variants,OpManager,cxCalendar,ConfigManager, DataTrans, uLkJSON;
type
  CTestCase = class(TObject)
  private
    mGridCount : Integer;
    mCOpsManager: COpsManager;
    mTOpManager: TOpManager;
    mTConfigManager: TConfigManager;
    
    strTab: string;
  private
    //测试具体控件
    procedure   TestWindows();
    procedure   TestWindowsImp(h: HWND);
    procedure   DoTestWindows(h: HWND);
    procedure   DoTestDxNavBar(h: HWND);
    procedure   DoTestTreeView(h: HWND);
    procedure   DoTestTcxGridView(h: HWND);
    procedure   DoTestTcxDBDateEdit(h: HWND);
    procedure   DoTestTcxCheckBox(h: HWND);
    
    procedure   GetTcxGridData(grid: TcxGrid);
    //自动操作
    procedure  TestAutoOps();
    //截取窗口数据
    procedure  CatchWindowsData();
    procedure  CatchWindowsDataImp(h: HWND);
    procedure  DoCatchWindows(h: HWND);
    //获取控件坐标
    procedure TestLocation();
    //测试屏幕点击
    procedure TestClickPoint();
    //
    procedure TestFileUpLoad();
    
    
    
  public
    procedure StartTest();
    procedure TestCatchWindowsData();
    
  end;

{ TTestPointClickThread }

  TTestPointClickThread = class(TThread)

   protected
    procedure Execute;override;
   

  end;

implementation

  procedure CTestCase.StartTest;
  var
    i:Integer;
  begin
    mCOpsManager :=COpsManager.Create;
    mTOpManager := TOpManager.Create;
    mTConfigManager := TConfigManager.GetInstance;
  //  测试控件类型
  //TestWindows();
    
  //  测试自动操作
  //TestAutoOps();

  //  抓数据
  //CatchWindowsData();

  //位置点
  //TestLocation();

//  for i:=0 to 20 do
//  begin
//  SaveData(Utils.GetSaveDir()+Format('%s%d', ['grid', mGridCount])+'.txt', '1234567890'+#13#10, True); 
//  end; 

//  mCOpsManager.StartOps(AutoOpType_SearchClient);

// 自动操作测试
//  mTOpManager.StartOps();

//kill
//   CMyLog.DebugMsg(TConfigManager.GetInstance.GetExePath);
//   Utils.KillAppExe(TConfigManager.GetInstance.GetExePath);
//   CMyLog.DebugMsg(TConfigManager.GetInstance.GetExePath);

//测试定点点击
//TestClickPoint;

//测试数据上传
//  TestFileUpLoad();
  end;

  procedure CTestCase.TestCatchWindowsData();
  begin
    CatchWindowsData();
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
  
  procedure CTestCase.DoTestTcxGridView(h: HWND);
   var
    twcl: TWinControl;
    tGrid: TcxGrid;
  begin
      twcl := Utils.GetCtlByClassName(h,'TcxGrid');
      if (twcl<>nil) then
      begin
      tGrid := TcxGrid(twcl);
      if(tGrid<>nil)  then
        begin
  //        s1 := Format('tcxgrid  find: %x view count = %d ', [Integer(@tGrid), tGrid.Levels.Count]);
  //        MessageBox(0, PAnsiChar(AnsiString(s1)), 'tcxgrid', MB_OK);
          GetTcxGridData(tGrid);
        end
      end;
    
  end;
  
  procedure  CTestCase.DoTestTcxDBDateEdit(h: HWND);
   var
    bRet: Boolean;
    twcl: TWinControl;
    tCtl: TcxDBDateEdit;
    cxDataEdit: TcxDateEdit;
  begin
      twcl :=  Utils.GetCtlByClassName(h,'TcxDateEdit');
      if (twcl<>nil) then
      begin
        cxDataEdit := TcxDateEdit(twcl);
        CMyLog.DebugMsg('find-----TcxDateEdit');
  //      tCtl.SetTextBuf(PAnsiChar('2012-07-08 23:12:12'));
  //    cxDataEdit.Date := StrToDateTime('2012-07-08 23:12:12');
        cxDataEdit.SetTextBuf(PAnsiChar('2012-07-08 23:12:12'));
  //    ShowMessageFmt('%s', ['-----------3']);
      end;
      
  end;

  procedure  CTestCase.DoTestTcxCheckBox(h: HWND);
  var
    bRet: Boolean;
    twcl: TWinControl;
    tCtl: TcxCheckBox;
  begin
      twcl :=  Utils.GetCtlByClassName(h,'TcxCheckBox');
      if (twcl<>nil) then
      begin
//        tCtl := TcxCheckBox(twcl);
//        ShowMessageFmt('%s',['TcxCheckBox-----start']);
//        if tCtl.Checked then
//        begin
//           ShowMessageFmt('%s--%s',['TcxCheckBox','是']);
//           tCtl.Checked := False;
//        end
//        else
//        begin
//          ShowMessageFmt('%s--%s',['TcxCheckBox','否']);
//          tCtl.Checked := True;
//        end;
//          
//        ShowMessageFmt('%s',['TcxCheckBox-----end']);
        Utils.SendKeyEventToWindow(h, VK_SPACE);
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
  begin
    if Utils.FilterControls(h)=False then
      Exit;

     //DoTestTreeView(h);
     //DoTestDxNavBar(h);
     //DoTestTcxGridView(h);
     //DoTestTcxCheckBox(h);
     DoTestTcxDBDateEdit(h);

  end;

  procedure CTestCase.GetTcxGridData(grid: TcxGrid);
  var
    FileName: string;
    cxGridDBTableView: TcxGridDBTableView;
    cxView, cxView1: TcxCustomGridView;
    i,j, nRowCount,nColCount: Integer;
    rowInfo: TcxRowInfo;
    s, s1, tmp: string;
    p: Pointer ;
    sStr: ShortString;
    vari: Variant;

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
             nRowCount := cxView.DataController.GetRowCount();
             nColCount := cxView.DataController.GetItemCount();

             s := '';
             s1 := '';
             if nRowCount>0 then
             begin
               //字段值
               for j:=0 to nColCount-1 do
               begin
                 cxGridDBTableView := TcxGridDBTableView(cxView); 
                 s1 := Format('%s', [cxGridDBTableView.Columns[j].Caption]);
                 if j<>0 then
                  s1 := #9+s1;
                  s := Concat(s, s1);
               end;
               s := Concat(s, Char(13), Chr(10));
               SaveData(Utils.GetSaveDir()+Format('%s%d', ['grid', mGridCount])+'.txt',s, True);

//               字段类型
//                s := '';
//                s1 := '';
//               for j:=0 to nColCount-1 do
//               begin
//                 vari := cxView.DataController.Values[0,j];
//                 s1 := Format('%s', [VarTypeAsText(VarType(vari))]);
//                 if j<>0 then
//                  s1 := #9+s1;
//                  s := Concat(s, s1);
//               end;
//               s := Concat(s, Char(13), Chr(10));
//               SaveData(Utils.GetSaveDir()+Format('%s%d', ['grid', mGridCount])+'.txt',s, True);
             end;

               
             s := '';
             s1 := '';
             for i := 0 to nRowCount-1 do
             begin
             if i<>0 then s := Concat(s, Char(13), Chr(10));
              for j:=0 to nColCount-1 do
               begin
                 s1 := Format('%s', [cxView.DataController.GetDisplayText(i,j)]);
                 
                 if j<>0 then
                  s1 := #9+s1;
                  
                 s := Concat(s, s1);
               end;
               
               if ((0=(i mod 100)) and (i>99)) or (i=nRowCount-1)then
                 begin
                    SaveData(Utils.GetSaveDir()+Format('%s%d', ['grid', mGridCount])+'.txt',s, True);
                    s := '';
                 end;
             end;
           end;

           if nRowCount>0 then
           begin
              //SaveData(Utils.GetSaveDir()+Format('%s%d', ['grid', mGridCount])+'.txt',s, True);
              mGridCount := mGridCount+1;
           end;
         end;
      end;
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
    h, h1 : HWND;
  begin
     h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
     //h1 := Utils.FindeWindowBy(h, '车主车辆管理', 'TbsCustomerMangageForm');
     //h1 := Utils.FindeWindowBy(h, '结算单查询', 'TbsBalanceAccountQueryForm');
     //h1 := Utils.FindeWindowBy(h, '客户筛选设置', 'TbsCustomFilterSetForm');
     
     h1 := h;
     if h1<>0 then
     begin
      CMyLog.DebugMsg('-------------找到根窗口');
      TestWindowsImp(h1);
     end;
//      h := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//      TestWindowsImp(h);
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
            s1 := Format('%s----%s----%d ', [Utils.GetClassNameBy(h), buf, tab]);
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

  procedure CTestCase.TestLocation;
  var
    hInjet, hTest: HWND;
    rect: TRect;
  begin
      CMyLog.DebugMsg('--------TestLocation');
      hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
      hTest := Utils.FindeWindowBy(hInjet, '取消', 'TcxButton');
      GetWindowRect(hTest, rect);
      CMyLog.DebugMsg(Format('(%d,%d, %d,%d)', [rect.Left, rect.Top, rect.Right, rect.Bottom]));
  end;
  
procedure CTestCase.TestClickPoint;
var
   hInjet, hTest: HWND;
   rect: TRect;
   point:TPoint;
begin
//   hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
//   hTest := Utils.FindeWindowBy(hInjet, '', 'TdxNavBar');
//   if hTest<>0 then
//   begin
//     CMyLog.DebugMsg('-------Find TdxNavBar');
////     GetWindowRect(hTest, rect);
////    CMyLog.DebugMsg(Format('(%d,%d, %d,%d)', [rect.Left, rect.Top, rect.Right, rect.Bottom]));
//   Utils.ClickPoint(60, 590);
//   Utils.ClickPoint(68, 155);
//   Utils.ClickPoint(85, 185);
//   Utils.WaitOpTimeOut(hInjet, '客户筛选设置', 'TbsCustomFilterSetForm', Utils.cntWaitWndTime);
//   Sleep(5000);
//   Utils.ClickPoint(183, 170);
//   Utils.ClickPoint(560, 170);
//   TTestPointClickThread.Create(False);
  
end;

{ TTestPointClickThread }

procedure TTestPointClickThread.Execute;
var
   hInjet, hTest: HWND;
   rect: TRect;
   point:TPoint;
begin
   inherited;
   
   hInjet := FindWindow(nil,PAnsiChar(Utils.cntInjetWind));
   hTest := Utils.FindeWindowBy(hInjet, '', 'TdxNavBar');
   if hTest<>0 then
   begin
     CMyLog.DebugMsg('-------Find TdxNavBar');
//     GetWindowRect(hTest, rect);
//    CMyLog.DebugMsg(Format('(%d,%d, %d,%d)', [rect.Left, rect.Top, rect.Right, rect.Bottom]));
   Utils.ClickPoint(60, 590);
   Utils.ClickPoint(68, 155);
   Utils.ClickPoint(85, 185);
   Utils.WaitOpTimeOut(Utils.cntInjectExe, Utils.cntWaitWndTime);
   //Utils.WaitOpTimeOut(hInjet, '客户筛选设置', 'TbsCustomFilterSetForm', Utils.cntWaitWndTime);
   Sleep(5000);
   Utils.ClickPoint(183, 170);
   Utils.ClickPoint(560, 170);
   end;
  
end;

procedure CTestCase.TestFileUpLoad;
var
  trans:TDataTrans;
 jsBase: TlkJSONobject;
 fileContent,urlContent, sRet, fileName: string;
begin
  fileName := '客户筛选设置_20171129-20171203.txt';
  fileContent:=Utils.ReadFileToHex(Utils.GetDllPath+fileName);
  jsBase := TlkJSONobject.Create(True);
  jsBase.Add('fileName', fileName);
  jsBase.Add('fileData', fileContent);

  trans:= TDataTrans.Create;
  urlContent:=TlkJSON.GenerateText(jsBase);
  urlContent := StringReplace(urlContent, ' ', '', [rfReplaceAll]);
 // Utils.SaveData(Utils.GetDllPath+'111.txt', urlContent, False );
  sRet := trans.HttpPost(Utils.cntUrlUpLoadFile, urlContent);
  
  CMyLog.DebugMsg(sRet);
end;

end.
