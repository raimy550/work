unit WeiXiuWeiTuoInfo;

interface
 uses
  BaseInfo,Windows,Messages,Dialogs,Controls,StdCtrls,Utils,SysUtils,Classes,
  Contnrs,cxCheckBox,StrMap,StrUtils,uLkJSON;
  
const
  cntWeiTuoTxt: string = '维修委托书';
  cntWeiTuoCls: string = 'Tbs';
type
  CWeiTuoInfo = class(CBaseInfo)

  private
    procedure  ParseDataWeiXiu(h: HWND); //本次维修
    procedure  ParseDataWeiXiuImp(h: HWND);
    procedure ParseDataUser(h: HWND);//本次维修 用户数据
    procedure ParseDataWeiXiuEx(h: HWND);//本次维修 扩展数据
    procedure ParseDataYuGu(h: HWND);//本次维修 预估
    
    procedure ParseDataUserBase(h: HWND);
    function  ParseDataUserOthers(h: HWND): Boolean;
    procedure ParseDataUserCar(h: HWND);
    procedure ParseDataUserWeiTuo(h: HWND);
    procedure ParseDataYouHuiSuoPei(h: HWND);

    procedure HandleUserWeiTuo(h: HWND);
    procedure HandleUserCar(h: HWND);
    procedure HandleYuGu(h: HWND);
    procedure HandleYouHuiSuoPei(h: HWND);

  protected
    procedure Init();override;
    function HandleData(h: HWND): Boolean;override;
  public
    procedure SaveJsonData();override;
    procedure SaveShowData();
    function UpdateOp(h: HWND): Boolean;override;
    function GetJsonData():String;

  end;

implementation

procedure CWeiTuoInfo.Init;
begin
      //送修人信息 0起始
  ShowInfo.Put(IntToStr(1), '车主名称');
  ShowInfo.Put(IntToStr(3), '个人');
  ShowInfo.Put(IntToStr(5), '车主编号');
  ShowInfo.Put(IntToStr(7), '送修人');
  ShowInfo.Put(IntToStr(8), '送修人性别');
  ShowInfo.Put(IntToStr(10), '送修人电话');
  ShowInfo.Put(IntToStr(12), '送修人手机');
  ShowInfo.Put(IntToStr(13), '会员编号');
  ShowInfo.Put(IntToStr(15), '会员积分');
  ShowInfo.Put(IntToStr(16), '实物卡号');
  ShowInfo.Put(IntToStr(18), '大众一家');
  //车辆信息 100起始
  ShowInfo.Put(IntToStr(100), '车牌归属地');
  ShowInfo.Put(IntToStr(101), '车牌号码');
  ShowInfo.Put(IntToStr(103), 'VIN');
  ShowInfo.Put(IntToStr(105), '车系');
  ShowInfo.Put(IntToStr(106), '车型');
  ShowInfo.Put(IntToStr(107), '本公司购车');
  ShowInfo.Put(IntToStr(113), '车辆性质');
  ShowInfo.Put(IntToStr(114), '累计换表里程');
  ShowInfo.Put(IntToStr(115), '换表区间里程值');
  ShowInfo.Put(IntToStr(116), '上次进厂日期');
  ShowInfo.Put(IntToStr(117), '转为潜客');
  ShowInfo.Put(IntToStr(118), '转为二手车');
  ShowInfo.Put(IntToStr(119), '换表区间里程');
  ShowInfo.Put(IntToStr(121), '潘云宝或马骏');
  ShowInfo.Put(IntToStr(125), '销售日期');
  ShowInfo.Put(IntToStr(126), '当前行驶里程');
  ShowInfo.Put(IntToStr(127), '使用性质');
  ShowInfo.Put(IntToStr(128), '下次保养日期');
  ShowInfo.Put(IntToStr(129), '转新车置换');
  ShowInfo.Put(IntToStr(132), '发动机号');
  ShowInfo.Put(IntToStr(133), '生命周期');
  //Info.Put(IntToStr(134), 'SVW');
  ShowInfo.Put(IntToStr(135), '三包凭证标识');
  ShowInfo.Put(IntToStr(136), '下次保养里程');
  ShowInfo.Put(IntToStr(137), '洗车');
  ShowInfo.Put(IntToStr(138), '进口车');
  ShowInfo.Put(IntToStr(139), '内部员工车');
  ShowInfo.Put(IntToStr(146), '转延保商机');

  //委托书信息200起始
  ShowInfo.Put(IntToStr(201), '委托书号');
  ShowInfo.Put(IntToStr(202), '服务顾问');
  ShowInfo.Put(IntToStr(203), '维修类型');
  ShowInfo.Put(IntToStr(204), '开单时间');
  ShowInfo.Put(IntToStr(210), '凭证类型');
  ShowInfo.Put(IntToStr(211), '活动来源');
  ShowInfo.Put(IntToStr(212), '校验码');
  ShowInfo.Put(IntToStr(213), '预交车日期');
  ShowInfo.Put(IntToStr(214), '预交车时间点');
  ShowInfo.Put(IntToStr(215), '旧件处理');
  ShowInfo.Put(IntToStr(216), '保险公司');
  ShowInfo.Put(IntToStr(217), '报案号');
  ShowInfo.Put(IntToStr(218), '下次保养规范');
  ShowInfo.Put(IntToStr(221), '备注');
  ShowInfo.Put(IntToStr(222), '车间标识');
  ShowInfo.Put(IntToStr(223), '严重安全进行故障');
  ShowInfo.Put(IntToStr(233), 'DISS编号');
  ShowInfo.Put(IntToStr(250), '工时折扣');
  ShowInfo.Put(IntToStr(251), '材料折扣');
  ShowInfo.Put(IntToStr(252), '优惠索赔折扣');

  //委托书信息300起始
  ShowInfo.Put(IntToStr(301), '优惠模式');
  ShowInfo.Put(IntToStr(302), '工时费');
  ShowInfo.Put(IntToStr(303), '维修材料费');
  ShowInfo.Put(IntToStr(304), '总金额');
  ShowInfo.Put(IntToStr(305), '优惠金额');


 //
  //送修人信息 0起始
  PtlInfo.Put(IntToStr(1), 'carOwnerName');
  PtlInfo.Put(IntToStr(3), 'carOwnerQuality');
  PtlInfo.Put(IntToStr(5), 'carOwnerNumber');
  PtlInfo.Put(IntToStr(7), 'songCarRen');
  PtlInfo.Put(IntToStr(8), 'songCarRenSex');
  PtlInfo.Put(IntToStr(10), 'songCarRenTelephone');
  PtlInfo.Put(IntToStr(12), 'songCarRenMobile');
  PtlInfo.Put(IntToStr(13), 'associatorNumber');
  PtlInfo.Put(IntToStr(15), 'associatorScore');
  PtlInfo.Put(IntToStr(16), 'cardNumber');
  PtlInfo.Put(IntToStr(18), 'VolkswagenFamily');
  //车辆信息 100起始
  PtlInfo.Put(IntToStr(100), 'plateNumber');
  PtlInfo.Put(IntToStr(101), 'plateNumber');
  PtlInfo.Put(IntToStr(103), 'vin');
  PtlInfo.Put(IntToStr(105), 'carSeries');
  PtlInfo.Put(IntToStr(106), 'carModel');
  PtlInfo.Put(IntToStr(107), 'inOwnCompanyPurchased');
  PtlInfo.Put(IntToStr(113), 'carQuality');
  PtlInfo.Put(IntToStr(114), 'totalMileage');
  PtlInfo.Put(IntToStr(115), 'regionMileage');
  PtlInfo.Put(IntToStr(116), 'lastEnteringPlantDate');
  PtlInfo.Put(IntToStr(117), 'potentialCustomer');
  PtlInfo.Put(IntToStr(118), 'secondHandCar');
  PtlInfo.Put(IntToStr(119), '换表区间里程');
  PtlInfo.Put(IntToStr(121), '潘云宝或马骏');
  PtlInfo.Put(IntToStr(125), 'saleDate');
  PtlInfo.Put(IntToStr(126), 'mileage');
  PtlInfo.Put(IntToStr(127), 'useQuality');
  PtlInfo.Put(IntToStr(128), 'nextMaintainDate');
  PtlInfo.Put(IntToStr(129), 'newCarReplacement');
  PtlInfo.Put(IntToStr(132), 'engineNumber');
  PtlInfo.Put(IntToStr(133), 'lifecycle');
  //Info.Put(IntToStr(134), 'SVW');
  PtlInfo.Put(IntToStr(135), 'guaranteeCardId');
  PtlInfo.Put(IntToStr(136), 'nextMaintainMileage');
  PtlInfo.Put(IntToStr(137), 'carWash');
  PtlInfo.Put(IntToStr(138), 'importedCar');
  PtlInfo.Put(IntToStr(139), 'employeeCar');
  PtlInfo.Put(IntToStr(146), 'extendGuarantee');

  //委托书信息200起始
  PtlInfo.Put(IntToStr(201), 'proxyNumber');
  PtlInfo.Put(IntToStr(202), 'adviser');
  PtlInfo.Put(IntToStr(203), 'maintenanceType');
  PtlInfo.Put(IntToStr(204), 'createdDate');
  PtlInfo.Put(IntToStr(250), '工时折扣');
  PtlInfo.Put(IntToStr(251), '材料折扣');
  PtlInfo.Put(IntToStr(252), '优惠索赔折扣');
  PtlInfo.Put(IntToStr(210), 'certificateType');
  PtlInfo.Put(IntToStr(211), 'activitySource');
  PtlInfo.Put(IntToStr(212), 'checkCode');
  PtlInfo.Put(IntToStr(213), 'expectDeliverDate');
  PtlInfo.Put(IntToStr(214), 'expectDeliverDate');
  PtlInfo.Put(IntToStr(215), 'oldDeviceProcess');
  PtlInfo.Put(IntToStr(216), 'insuranceCompany');
  PtlInfo.Put(IntToStr(217), 'reportNumber');
  PtlInfo.Put(IntToStr(218), 'nextMaintainSpecification');
  PtlInfo.Put(IntToStr(221), 'remark');
  PtlInfo.Put(IntToStr(222), 'workshopId');
  PtlInfo.Put(IntToStr(223), 'safetyFault');
  PtlInfo.Put(IntToStr(233), 'dissNumber');

  //委托书信息300起始
  PtlInfo.Put(IntToStr(301), '优惠模式');
  PtlInfo.Put(IntToStr(302), '工时费');
  PtlInfo.Put(IntToStr(303), '维修材料费');
  PtlInfo.Put(IntToStr(304), '总金额');
  PtlInfo.Put(IntToStr(305), '优惠金额');
end;

function CWeiTuoInfo.HandleData(h: HWND): Boolean;
begin
    if Utils.ControlTextContains(h, '本次维修') then
    begin
      ParseDataWeiXiu(h);
      Result := True;
    end;

end;

procedure CWeiTuoInfo.ParseDataUser(h: HWND);
var
  bDone: Boolean;
begin

  bDone := ParseDataUserOthers(h);
  if bDone=True then
    Exit;

  ParseDataUserBase(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseDataUser(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure CWeiTuoInfo.ParseDataUserBase(h: HWND);
var
  buf: array[0..255] of Char;
  tab : Integer;
  tcl: TWinControl;
begin
  if Utils.FilterControls(h)=False then
  Exit;

  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl.Visible then
  begin
    tcl.GetTextBuf(buf, 255);
    tab :=  tcl.TabOrder;
    AddData(tab, buf);
  end;
end;

function CWeiTuoInfo.ParseDataUserOthers(h: HWND): Boolean;
begin
  Result := False;
  if Utils.FilterControls(h)=False then
    Exit;

  if Utils.ControlTextContains(h, '车辆信息') then
  begin
    ParseDataUserCar(h);
    Result := True;
  end;

  if Utils.ControlTextContains(h, '委托书信息') then
  begin
    ParseDataUserWeiTuo(h);
    Result := True;
  end;
end;

procedure CWeiTuoInfo.ParseDataUserCar(h: HWND);
begin
  HandleUserCar(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseDataUserCar(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure CWeiTuoInfo.ParseDataUserWeiTuo(h: HWND);
begin
  HandleUserWeiTuo(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseDataUserWeiTuo(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure CWeiTuoInfo.ParseDataYuGu(h: HWND);
begin
  HandleYuGu(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseDataYuGu(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure CWeiTuoInfo.SaveJsonData;
var
  i,nCount, cur, pre: Integer;
  s, FileName: string;
  jsBase,js: TlkJSONobject;
begin
   SortData(ShowDataMap);
   nCount := ShowDataMap.Count;

   jsBase := TlkJSONobject.Create(True);
   js:=TlkJSONobject.Create(True);
   jsBase.Add('carOwnerInfo', js);
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
           jsBase.Add('carInfo', js);
       end;

       if ((pre<200) and (cur>=200)) then
       begin
          js:=TlkJSONobject.Create(True);
          jsBase.Add('proxyInfo', js);
       end;
     end;

     js.Add(GetPtlInfoByTab(cur), PtlDataMap.Get(IntToStr(cur)));
   end;

   FileName := Utils.GetSaveDir()+Utils.cntSaveWeiXiuName;
   TlkJSONstreamed.SaveToFile(jsBase, FileName);
end;

procedure CWeiTuoInfo.SaveShowData;
var
  i,nCount, tmp, tmp1: Integer;
  s,  FileName: string;
begin
   SortData(ShowDataMap);
   nCount := ShowDataMap.Count;
   ShowMessageFmt('%s--%d', ['WeiTuoDataMap', nCount]);
   s := Concat(s,  Char(13), Char(10), '《客户信息》', Char(13), Char(10));
   for i:=0 to nCount-1 do
   begin
     if i>0 then
     begin
       tmp := StrToInt(ShowDataMap.FKeyList[i]);
       tmp1 := StrToInt(ShowDataMap.FKeyList[i-1]);
       if ((tmp1<100) and (tmp>=100)) then
        s := Concat(s, Char(13), Char(10),'《车辆信息》', Char(13), Char(10));

       if ((tmp1<200) and (tmp>=200)) then
        s := Concat(s, Char(13), Char(10),'《委托书信息》', Char(13), Char(10));

        if ((tmp1<300) and (tmp>=300)) then
        s := Concat(s, Char(13), Char(10),'《预估费用》', Char(13), Char(10));
     end;

   s := Concat(s, ShowDataMap.FStrList[i], Char(13), Char(10));
   end;

   FileName := Utils.GetSaveDir()+Utils.cntSaveWeiXiuForShowName;
   Utils.SaveData(FileName, s, False);
end;

procedure CWeiTuoInfo.ParseDataWeiXiu(h: HWND);
var
  hChild: HWND;
begin
  hChild := GetWindow(h, GW_CHILD);

  while hChild <> 0 do
  begin
    ParseDataWeiXiuImp(hChild);
    hChild := GetWindow(hChild, GW_HWNDNEXT);
  end;
end;

procedure CWeiTuoInfo.ParseDataWeiXiuImp(h: HWND);
begin
  if Utils.ClassNameContains(h, 'TPanel') then
      begin
        //ShowMessageFmt('%s', ['用户基础数据---开始']);
        ParseDataUser(h);
        //ShowMessageFmt('%s', ['用户基础数据---结束']);
      end

    else if Utils.ClassNameContains(h, 'TcxGroupBox') then
    begin
      //ShowMessageFmt('%s', ['预估费用---开始']);
        ParseDataYuGu(h);
      //ShowMessageFmt('%s', ['预估费用---结束']);
    end

    else if Utils.ClassNameContains(h, 'TcxPageControl') then
    begin
    //ShowMessageFmt('%s', ['扩展数据---开始']);
        ParseDataWeiXiuEx(h);
     // ShowMessageFmt('%s', ['扩展数据---结束']);
    end;

    
end;

procedure CWeiTuoInfo.ParseDataWeiXiuEx(h: HWND);
begin

end;

procedure CWeiTuoInfo.HandleYuGu(h: HWND);
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
        tab :=  tcl.TabOrder+300;
        
        if Utils.ControlTextContains(h, '预估费用') then
         Exit;

        AddData(tab, buf); 
      end;
end;

procedure CWeiTuoInfo.HandleUserCar(h: HWND);
var
  buf: array[0..255] of Char;
  tab : Integer;
  tcl: TWinControl;
begin
  if Utils.FilterControls(h)=False then
  Exit;

  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl.Visible then
  begin
    if Utils.ControlTextContains(h, '车辆信息') then    //过滤掉
      Exit;
      
    tcl.GetTextBuf(buf, 255);
    tab :=  tcl.TabOrder+100;
    AddData(tab, buf);
    
//    nRet := Pos('CheckBox', buf);
//    if nRet<>0 then
//    begin
//      Exit;
//      checkBox := TcxCheckBox(tcl);
//      ShowMessageFmt('%s: %s',['TcxCheckBox', buf1]);
//
//      nCheck := SendMessage(h, BM_GETCHECK, 0, 0);
//      ShowMessageFmt('%s: %d',['nCheck', nCheck]);
//      if nCheck=BST_CHECKED then
//      begin
//          value := '是';
//          ShowMessageFmt('%s: %s--%s',['TcxCheckBox', key,'是']);
//      end
//      else
//      begin
//          value := '否';
//          ShowMessageFmt('%s: %s--%s',['TcxCheckBox', key,'否']);
//      end;
//    end
//    else
//       value := StrPas(@buf1[0]);
  end;

end;

procedure CWeiTuoInfo.HandleUserWeiTuo(h: HWND);
var
  buf: array[0..255] of Char;
  tab : Integer;
  tcl: TWinControl;
begin
  if Utils.FilterControls(h)=False then
  Exit;

  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl.Visible then
  begin    
    if Utils.ControlTextContains(h, '委托书信息') then    //过滤掉
      Exit
    else if Utils.ControlTextContains(h, '优惠索赔') then
    begin
      ParseDataYouHuiSuoPei(h);
      Exit;
    end;
      
    tcl.GetTextBuf(buf, 255);
    tab :=  tcl.TabOrder+200;
    AddData(tab, buf);
  end;
end;

procedure CWeiTuoInfo.ParseDataYouHuiSuoPei(h: HWND);
begin
  HandleYouHuiSuoPei(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseDataYouHuiSuoPei(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure CWeiTuoInfo.HandleYouHuiSuoPei(h: HWND);
  var
  buf: array[0..255] of Char;
  tab : Integer;
  tcl: TWinControl;
begin
  if Utils.FilterControls(h)=False then
  Exit;

  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl.Visible then
  begin
    if Utils.ControlTextContains(h, '优惠索赔') then    //过滤掉
      Exit;
      
    tcl.GetTextBuf(buf, 255);
    tab :=  tcl.TabOrder+250;
    AddData(tab, buf);
  end;
end;

function CWeiTuoInfo.UpdateOp(h: HWND): Boolean;
begin
  Result := False;
  if Utils.ClassNameContains(h, cntWeiTuoCls) and Utils.ControlTextContains(h, cntWeiTuoTxt) then
  begin
       WndOp := Utils.FindeWindowBy(h, Utils.cntOpSave, cntOpSaveCls);
       Result := True;
  end;
end;

function CWeiTuoInfo.GetJsonData():String;
var
  i,nCount, cur, pre: Integer;
  s, FileName: string;
  jsBase,js: TlkJSONobject;
begin
   SortData(ShowDataMap);
   nCount := ShowDataMap.Count;

   jsBase := TlkJSONobject.Create(True);
   js:=TlkJSONobject.Create(True);
   jsBase.Add('carOwnerInfo', js);
   for i:=0 to nCount-1 do
   begin
     if i>0 then
     begin
       cur := StrToInt(ShowDataMap.FKeyList[i]);
       pre := StrToInt(ShowDataMap.FKeyList[i-1]);
       if ((pre<100) and (cur>=100)) then
       begin
           js:=TlkJSONobject.Create(True);
           jsBase.Add('carInfo', js);
       end;

       if ((pre<200) and (cur>=200)) then
       begin
           js:=TlkJSONobject.Create(True);
           jsBase.Add('proxyInfo', js);
       end;
     end;

     js.Add(GetPtlInfoByTab(cur), PtlDataMap.Get(IntToStr(cur)));
   end;
   
   Result := TlkJSON.GenerateText(jsBase);
end;

end.
