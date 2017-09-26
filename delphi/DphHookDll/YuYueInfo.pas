unit YuYueInfo;

interface
uses
  BaseInfo,
  Windows,
  Messages,
  Dialogs,
  Controls,
  StdCtrls,
  Utils,
  SysUtils,
  Classes,
  Contnrs,
  cxCheckBox,
  StrMap,
  StrUtils,
  uLkJSON;

  const
    cntYuYueTxt: string = '客户预约';
    cntYuYueCls: string = 'Tbs';
type
  CYuYueInfo = class(CBaseInfo)
  private
    procedure HandleDataKehuInfo(h: HWND);
    procedure HandleDataYuYueDanInfo(h: HWND);
    procedure AddDataKehuInfo(h: HWND);
    procedure AddDataYuYueDanInfo(h: HWND);
  protected
    procedure Init();override;
    function HandleData(h: HWND): Boolean;override;
  public
    procedure SaveJsonData();override;
    procedure SaveShowData();
    function UpdateOp(h: HWND): Boolean;override;

  end;

implementation
procedure CYuYueInfo.Init;
   begin
     //客户/车辆信息
     ShowInfo.Put('0', '预约人');
     ShowInfo.Put('1', 'VIN');
     ShowInfo.Put('2', '购车日期');
     ShowInfo.Put('3', '上次进厂日期');
     ShowInfo.Put('6', '车系');
     ShowInfo.Put('7', '车型');
     ShowInfo.Put('8', '车辆性质');
     ShowInfo.Put('9', '预约人手机');
     ShowInfo.Put('10', '车主');
     ShowInfo.Put('12', '预约人电话区号');
     ShowInfo.Put('13', '预约人电话号码');
     ShowInfo.Put('14', '车牌号码');
     ShowInfo.Put('15', '车牌归属地');
     ShowInfo.Put('16', '发动机号码');
     ShowInfo.Put('18', '变速箱代码');
     ShowInfo.Put('19', '专属服务顾问');
     //预约单基本信息 100+
     ShowInfo.Put('100', '预约单号');
     ShowInfo.Put('102', '预约渠道');
     ShowInfo.Put('103', '预约方向');
     ShowInfo.Put('104', '预约业务类型');
     ShowInfo.Put('106', '业务子类型');
     ShowInfo.Put('107', '预约进店时间');
     ShowInfo.Put('108', '服务顾问');
     ShowInfo.Put('109', '预计接待时长');
     ShowInfo.Put('110', '预计上工位时间');
     ShowInfo.Put('111', '预约类别');
     ShowInfo.Put('112', '预约工位');
     ShowInfo.Put('113', '预约施工时间');
     ShowInfo.Put('114', '预计进厂里程');
     ShowInfo.Put('116', '接车地址');
     ShowInfo.Put('117', '故障描述');
     ShowInfo.Put('118', '开单人');
     ShowInfo.Put('119', '预约日期');
     ShowInfo.Put('120', '备注');
     ShowInfo.Put('122', '预约技师');
     ShowInfo.Put('130', '送车地址');
   end;

   function CYuYueInfo.HandleData(h: HWND): Boolean;
   var
    buf: array[0..255] of Char;
    nRet, nRet1: Integer;
    tcl: TWinControl;
   begin
      Result := False;
      if Utils.FilterControls(h)=False then
       Exit;

       Result := True;
       if Utils.ControlTextContains(h, '车辆信息') then
       begin
          //ShowMessageFmt('%s', ['客户车辆信息---开始']);
          HandleDataKehuInfo(h);
          //ShowMessageFmt('%s', ['客户车辆信息---结束']);
       end
       else if Utils.ControlTextContains(h, '预约单基本信息')  then
       begin
         //ShowMessageFmt('%s', ['预约单基本信息---开始']);
         HandleDataYuYueDanInfo(h);
         //ShowMessageFmt('%s', ['预约单基本信息---结束']);
       end
       else
        Result := False;
   end;

   procedure CYuYueInfo.HandleDataKehuInfo(h: HWND);
   begin
    AddDataKehuInfo(h);
    h := GetWindow(h, GW_CHILD);
    while h <> 0 do
    begin
      HandleDataKehuInfo(h);
      h := GetWindow(h, GW_HWNDNEXT);
    end;
   end;

   procedure CYuYueInfo.HandleDataYuYueDanInfo(h: HWND);
   begin
    AddDataYuYueDanInfo(h);
    h := GetWindow(h, GW_CHILD);
    while h <> 0 do
    begin
      HandleDataYuYueDanInfo(h);
      h := GetWindow(h, GW_HWNDNEXT);
    end;
   end;

   procedure CYuYueInfo.AddDataKehuInfo(h: HWND);
   var
    buf: array[0..255] of Char;
    tab: Integer;
    tcl: TWinControl;
   begin
      if Utils.FilterControls(h)=False then
      Exit;

      tcl := Utils.GetInstanceFromhWnd(h);
      if tcl.Visible then
      begin
        tcl.GetTextBuf(buf, 255);
        tab :=  tcl.TabOrder;
        
        if Utils.ControlTextContains(h, '客户/车辆信息') then
         Exit;

        AddData(tab, buf); 
      end;

   end;

   procedure CYuYueInfo.AddDataYuYueDanInfo(h: HWND);
   var
    buf: array[0..255] of Char;
    tab: Integer;
    tcl: TWinControl;
   begin
      if Utils.FilterControls(h)=False then
      Exit;

      tcl := Utils.GetInstanceFromhWnd(h);
      if tcl.Visible then
      begin
        tcl.GetTextBuf(buf, 255);
        tab :=  tcl.TabOrder+100;
        
        if Utils.ControlTextContains(h, '预约单基本信息') then
         Exit;

        AddData(tab, buf); 
      end;

   end;

procedure CYuYueInfo.SaveShowData();
var
  i,nCount, tmp, tmp1: Integer;
  s,  FileName: string;
begin
   SortData(ShowDataMap);
   nCount := ShowDataMap.Count;
   s := Concat(s,  Char(13), Char(10), '《客户或车辆信息》', Char(13), Char(10));
   for i:=0 to nCount-1 do
   begin
     if i>0 then
     begin
       tmp := StrToInt(ShowDataMap.FKeyList[i]);
       tmp1 := StrToInt(ShowDataMap.FKeyList[i-1]);
       if ((tmp1<100) and (tmp>=100)) then
        s := Concat(s, Char(13), Char(10),'《预约单基本信息》', Char(13), Char(10));
     end;

   s := Concat(s, ShowDataMap.FStrList[i], Char(13), Char(10));
   end;

   FileName := Utils.GetSaveDir()+Utils.cntSaveYuYueForShowName;
   Utils.SaveData(FileName, s, False);
   //ShowMessageFmt('%s%s%s', ['信息获取成功,', '保存路径：', FileName]);
end;

procedure CYuYueInfo.SaveJsonData();
var
  i,nCount, cur, pre: Integer;
  s, FileName: string;
  jsBase,js: TlkJSONobject;
begin
   SortData(ShowDataMap);
   nCount := ShowDataMap.Count;

   jsBase := TlkJSONobject.Create(True);
   js:=TlkJSONobject.Create(True);
   jsBase.Add('客户或车辆信息', js);
   for i:=0 to nCount-1 do
   begin
     cur := i;
     if i>0 then
     begin
       cur := StrToInt(ShowDataMap.FKeyList[i]);
       pre := StrToInt(ShowDataMap.FKeyList[i-1]);
       if ((pre<100) and (cur>=100)) then
       begin
           js:=TlkJSONobject.Create(True);
           jsBase.Add('预约单基本信息', js);
       end;
     end;

     js.Add(GetKeyByTab(cur), PtlDataMap.Get(IntToStr(cur)));
   end;

   FileName := Utils.GetSaveDir()+Utils.cntSaveYuYueName;
   TlkJSONstreamed.SaveToFile(jsBase, FileName);
   //ShowMessageFmt('%s%s%s', ['信息获取成功,', '保存路径：', FileName]);
end;

function CYuYueInfo.UpdateOp(h: HWND): Boolean;
begin
  //WndOp := Utils.FindeWindowBy(h, cntYuYueTxt, cntYuYueCls);
  Result := False;
  if Utils.ClassNameContains(h, cntYuYueCls) and Utils.ControlTextContains(h, cntYuYueTxt) then
  begin
       WndOp := Utils.FindeWindowBy(h, Utils.cntOpSave, cntOpSaveCls);
       Result := True;
  end;
end;

end.
