unit WeiTuoInfo;

interface
uses
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
    cntWeiTuoTxt: string = 'ά��ί����';
    cntWeiTuoCls: string = 'Tbs';
var
  Info, PtlInfo: TStrMap;   //key:tab,value:��Ϣ
  WeiTuoDataMap: TStrMap;   //key:tab, value: info ,չʾ����
  PtlDataMap: TStrMap;      //key:tab, value: value  ��Э������
  str: TStrings;
  WndOp: HWND;   // ������ť
  
procedure Init();
procedure CleanData();
procedure ParseData(h: HWND);
procedure SaveShowData();
function GetJsonData():String;
procedure SaveJsonData();
function UpdateOp(h: HWND): Boolean;
function GetOp(): HWND;

implementation
procedure Init();
begin
  Info := TStrMap.Create;
  PtlInfo := TStrMap.Create;
  WeiTuoDataMap := TStrMap.Create;
  PtlDataMap:= TStrMap.Create;


  //��������Ϣ 0��ʼ
  Info.Put(IntToStr(1), '��������');
  Info.Put(IntToStr(3), '����');
  Info.Put(IntToStr(5), '�������');
  Info.Put(IntToStr(7), '������');
  Info.Put(IntToStr(8), '�������Ա�');
  Info.Put(IntToStr(10), '�����˵绰');
  Info.Put(IntToStr(12), '�������ֻ�');
  Info.Put(IntToStr(13), '��Ա���');
  Info.Put(IntToStr(15), '��Ա����');
  Info.Put(IntToStr(16), 'ʵ�￨��');
  Info.Put(IntToStr(18), '����һ��');
  //������Ϣ 100��ʼ
  Info.Put(IntToStr(100), '���ƹ�����');
  Info.Put(IntToStr(101), '���ƺ���');
  Info.Put(IntToStr(103), 'VIN');
  Info.Put(IntToStr(105), '��ϵ');
  Info.Put(IntToStr(106), '����');
  Info.Put(IntToStr(107), '����˾����');
  Info.Put(IntToStr(113), '��������');
  Info.Put(IntToStr(114), '�ۼƻ������');
  Info.Put(IntToStr(115), '�����������ֵ');
  Info.Put(IntToStr(116), '�ϴν�������');
  Info.Put(IntToStr(117), 'תΪǱ��');
  Info.Put(IntToStr(118), 'תΪ���ֳ�');
  Info.Put(IntToStr(119), '�����������');
  Info.Put(IntToStr(121), '���Ʊ�����');
  Info.Put(IntToStr(125), '��������');
  Info.Put(IntToStr(126), '��ǰ��ʻ���');
  Info.Put(IntToStr(127), 'ʹ������');
  Info.Put(IntToStr(128), '�´α�������');
  Info.Put(IntToStr(129), 'ת�³��û�');
  Info.Put(IntToStr(132), '��������');
  Info.Put(IntToStr(133), '��������');
  //Info.Put(IntToStr(134), 'SVW');
  Info.Put(IntToStr(135), '����ƾ֤��ʶ');
  Info.Put(IntToStr(136), '�´α������');
  Info.Put(IntToStr(137), 'ϴ��');
  Info.Put(IntToStr(138), '���ڳ�');
  Info.Put(IntToStr(139), '�ڲ�Ա����');
  Info.Put(IntToStr(146), 'ת�ӱ��̻�');

  //ί������Ϣ200��ʼ
  Info.Put(IntToStr(201), 'ί�����');
  Info.Put(IntToStr(202), '�������');
  Info.Put(IntToStr(203), 'ά������');
  Info.Put(IntToStr(204), '����ʱ��');
  Info.Put(IntToStr(210), 'ƾ֤����');
  Info.Put(IntToStr(211), '���Դ');
  Info.Put(IntToStr(212), 'У����');
  Info.Put(IntToStr(213), 'Ԥ��������');
  Info.Put(IntToStr(214), 'Ԥ����ʱ���');
  Info.Put(IntToStr(215), '�ɼ�����');
  Info.Put(IntToStr(216), '���չ�˾');
  Info.Put(IntToStr(217), '������');
  Info.Put(IntToStr(218), '�´α����淶');
  Info.Put(IntToStr(221), '��ע');
  Info.Put(IntToStr(222), '�����ʶ');
  Info.Put(IntToStr(223), '���ذ�ȫ���й���');
  Info.Put(IntToStr(233), 'DISS���');
  Info.Put(IntToStr(250), '��ʱ�ۿ�');
  Info.Put(IntToStr(251), '�����ۿ�');
  Info.Put(IntToStr(252), '�Ż������ۿ�');

  //ί������Ϣ300��ʼ
  Info.Put(IntToStr(301), '�Ż�ģʽ');
  Info.Put(IntToStr(302), '��ʱ��');
  Info.Put(IntToStr(303), 'ά�޲��Ϸ�');
  Info.Put(IntToStr(304), '�ܽ��');
  Info.Put(IntToStr(305), '�Żݽ��');


 //
  //��������Ϣ 0��ʼ
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
  //������Ϣ 100��ʼ
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
  PtlInfo.Put(IntToStr(119), '�����������');
  PtlInfo.Put(IntToStr(121), '���Ʊ�����');
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

  //ί������Ϣ200��ʼ
  PtlInfo.Put(IntToStr(201), 'proxyNumber');
  PtlInfo.Put(IntToStr(202), 'adviser');
  PtlInfo.Put(IntToStr(203), 'maintenanceType');
  PtlInfo.Put(IntToStr(204), 'createdDate');
  PtlInfo.Put(IntToStr(250), '��ʱ�ۿ�');
  PtlInfo.Put(IntToStr(251), '�����ۿ�');
  PtlInfo.Put(IntToStr(252), '�Ż������ۿ�');
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

  //ί������Ϣ300��ʼ
  PtlInfo.Put(IntToStr(301), '�Ż�ģʽ');
  PtlInfo.Put(IntToStr(302), '��ʱ��');
  PtlInfo.Put(IntToStr(303), 'ά�޲��Ϸ�');
  PtlInfo.Put(IntToStr(304), '�ܽ��');
  PtlInfo.Put(IntToStr(305), '�Żݽ��');
end;

procedure CleanData();
begin
   WeiTuoDataMap.RemoveAll();
   PtlDataMap.RemoveAll();
end;


function GetKeyByTab(tab: Integer): string;
begin
 Result := '';
 Result := Info.Get(IntToStr(tab));
end;

function GetPtlInfoByTab(tab: Integer): string;
begin
 Result := '';
 Result := PtlInfo.Get(IntToStr(tab));
end;

procedure AddData(tab: Integer; buf: string);
var
    key, value: string;
begin
    key := GetKeyByTab(tab);
    if (key<>'') and (buf<>'') then
    begin
      value := key+':'+ buf;
      WeiTuoDataMap.Put(IntToStr(tab), value);
      PtlDataMap.Put(IntToStr(tab), buf);
    end;

end;



procedure HandleWeiXiuCarInfo(h: HWND);
var
  buf, buf1: array[0..255] of Char;
  nRet, nRet1, tab,nCheck: Integer;
  tcl: TWinControl;
  key,value: string;
  checkBox: TcxCheckBox;
  lpResult: Cardinal;
begin
  GetClassName(h, buf, Length(buf));
  
  nRet := Pos('Inner', buf);
  nRet1 := Pos('CheckBox', buf);

  if (nRet<>0) or (nRet1<>0) then
    Exit;

  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl.Visible then
  begin
    tcl.GetTextBuf(buf1, 255);
    tab :=  tcl.TabOrder+100;

    nRet := Pos('������Ϣ', buf1);
    if nRet<>0 then
      Exit;

    AddData(tab, buf1);
    
    nRet := Pos('CheckBox', buf);
    if nRet<>0 then
    begin
      Exit;
      checkBox := TcxCheckBox(tcl);
      ShowMessageFmt('%s: %s',['TcxCheckBox', buf1]);

      nCheck := SendMessage(h, BM_GETCHECK, 0, 0);
      ShowMessageFmt('%s: %d',['nCheck', nCheck]);
      if nCheck=BST_CHECKED then
      begin
          value := '��';
          ShowMessageFmt('%s: %s--%s',['TcxCheckBox', key,'��']);
      end
      else
      begin
          value := '��';
          ShowMessageFmt('%s: %s--%s',['TcxCheckBox', key,'��']);
      end;
    end
    else
       value := StrPas(@buf1[0]);
    //ShowMessageFmt('%s--%s',[key,value]);
  end;


end;

procedure DoWeiXiuCarInfo(h: HWND);
begin
  HandleWeiXiuCarInfo(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    DoWeiXiuCarInfo(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;


procedure HandleYouHuiSuoPei(h: HWND);
var
  buf, buf1: array[0..255] of Char;
  nRet, nRet1, tab: Integer;
  tcl: TWinControl;
  key, value: string;
begin
  GetClassName(h, buf1, Length(buf1));
  nRet := Pos('Inner', buf1);
  if nRet<>0 then
    Exit;

   tcl := Utils.GetInstanceFromhWnd(h);
   if tcl.Visible then
  begin
    tcl.GetTextBuf(buf, 255);
    tab :=  tcl.TabOrder+250;
    key := GetKeyByTab(tab);
    AddData(tab, buf);
   // ShowMessageFmt('%s--%s',[key,buf]);
  end;
end;

procedure DoYouHuiSuoPei(h: HWND);
begin
  HandleYouHuiSuoPei(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    DoYouHuiSuoPei(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

function HandleWeiXiuWeiTuoInfo(h: HWND): Boolean;
var
  buf, buf1: array[0..255] of Char;
  nRet, nRet1, tab, nCheck: Integer;
  tcl: TWinControl;
  key, value: string;
  checkBox: TcxCheckBox;
  lpResult: Cardinal;
begin
  Result := False;
  GetClassName(h, buf1, Length(buf1));
  nRet := Pos('Inner', buf1);
  if nRet<>0 then
    Exit;

   tcl := Utils.GetInstanceFromhWnd(h);
   if tcl.Visible then
  begin
    tcl.GetTextBuf(buf, 255);
     nRet := Pos('ί������Ϣ', buf);
    if nRet<>0 then
      Exit;
    nRet := Pos('�Ż�����', buf);
    if nRet<>0 then
    begin
       DoYouHuiSuoPei(h);
       Result := True;
       Exit;
    end;


    tab :=  tcl.TabOrder+200;
    key := GetKeyByTab(tab);
    AddData(tab, buf);


    nRet := Pos('cxCheckBox', buf1);
    if nRet<>0 then
    begin
      Exit;
      checkBox := TcxCheckBox(tcl);
      nCheck := SendMessageTimeout(h, BM_GETCHECK, 0, 0, SMTO_ABORTIFHUNG, 100, lpResult);

      value := StrUtils.IfThen(nCheck=BST_CHECKED, '��', '��');
    end
    else
      value := StrPas(@buf[0]);
    //ShowMessageFmt('%s--%s',[key,value]);
  end;

end;

procedure DoWeiXiuWeiTuoInfo(h: HWND);
var
  bDone: Boolean;
begin
  bDone := HandleWeiXiuWeiTuoInfo(h);
  if bDone=True then
    Exit;
    
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    DoWeiXiuWeiTuoInfo(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure HandleWeiXiuBaseInfo(h: HWND);
var
  buf: array[0..255] of Char;
  nRet, nRet1, tab: Integer;
  tcl: TWinControl;
  key: string;
begin
  GetClassName(h, buf, Length(buf));
  nRet := Pos('Inner', buf);
  if nRet<>0 then
  begin
    Exit;
  end;
  
  tcl := Utils.GetInstanceFromhWnd(h);
  if tcl.Visible then
  begin
    tcl.GetTextBuf(buf, 255);
    tab := tcl.TabOrder;
    key := GetKeyByTab(tab);
  //  ShowMessageFmt('%s--%s',[key,buf]);
    AddData(tab, buf);
  end;
end;

function DoWeiXiuData(h: HWND): Boolean;
var
  buf: array[0..255] of Char;
  nRet, nRet1: Integer;
  tcl: TWinControl;
begin
  Result := False;
  GetClassName(h, buf, Length(buf));
  nRet := Pos('Inner', buf);
  if nRet<>0 then
  begin
    Exit;
  end;

  tcl := Utils.GetInstanceFromhWnd(h);
  tcl.GetTextBuf(buf, 255);
  nRet :=  Pos('������Ϣ', buf);
  nRet1 :=  Pos('ί������Ϣ', buf);
  if nRet<>0 then
  begin
     //ShowMessageFmt('%s', ['������Ϣ---��ʼ']);
     DoWeiXiuCarInfo(h);
     //ShowMessageFmt('%s', ['������Ϣ---����']);
     Result := True;
  end;
  if nRet1<>0 then
  begin
     //ShowMessageFmt('%s', ['ί������Ϣ---��ʼ']);
     DoWeiXiuWeiTuoInfo(h);
     //ShowMessageFmt('%s', ['ί������Ϣ---����']);
     Result := True;
  end;
end;

procedure ParseWeiXiuUserData(h: HWND);
var
  bDone: Boolean;
begin

  bDone := DoWeiXiuData(h);
  if bDone=True then
    Exit;

  HandleWeiXiuBaseInfo(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseWeiXiuUserData(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure HandleWeiXiuYuGuInfo(h: HWND);
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
        
        if Utils.ControlTextContains(h, 'Ԥ������') then
         Exit;

        AddData(tab, buf); 
      end;
end;

procedure ParseWeiXiuYuGuData(h: HWND);
var
  bDone: Boolean;
begin

  HandleWeiXiuYuGuInfo(h);
  h := GetWindow(h, GW_CHILD);
  while h <> 0 do
  begin
    ParseWeiXiuYuGuData(h);
    h := GetWindow(h, GW_HWNDNEXT);
  end;
end;

procedure ParseData(h: HWND);
var
  buf: array[0..255] of Char;
  nRet, nRet1: Integer;
  tcl: TWinControl;
  hChild: HWND;
begin
  hChild := GetWindow(h, GW_CHILD);
  while hChild <> 0 do
  begin
     GetClassName(hChild, buf, Length(buf));
      nRet := Pos('TPanel', buf);
    if nRet<>0 then
      begin
        //ShowMessageFmt('%s', ['�û���������---��ʼ']);
        ParseWeiXiuUserData(hChild);
        //ShowMessageFmt('%s', ['�û���������---����']);
      end;


    nRet := Pos('TcxGroupBox', buf);
    if nRet<>0 then
    begin
      //ShowMessageFmt('%s', ['Ԥ������---��ʼ']);
        ParseWeiXiuYuGuData(hChild);
      //ShowMessageFmt('%s', ['Ԥ������---����']);
    end;


    hChild := GetWindow(hChild, GW_HWNDNEXT);
  end;
end;

procedure Save(path: string; data: string; bAppend: Boolean);
var
  F: TextFile;
begin
  AssignFile(F, path);
  if bAppend=True then
  begin
    if FileExists(path) then
     Append(F);
  end
  else
  Rewrite(F);

  
  try
    Write(F, data);
  finally
     CloseFile(F);
  end;
end;

procedure SortWeiTuoData(dataMap: TStrMap);
var
  i,j,tmp, nCount: Integer;
  strTmp, str1, str2: string;
  strKeys, strValues: TStrings;
begin
   nCount := dataMap.Count;
   strKeys := dataMap.FKeyList;
   strValues := dataMap.FStrList;

   for i:=0 to nCount-1 do
   begin
      for j:=0 to nCount-2 do
      begin
        str1 := strKeys[j] ;
        str2 := strKeys[j+1];
        if StrToInt(str1)>StrToInt(str2) then
        begin
           strTmp := strKeys[j];
           strKeys[j] := strKeys[j+1];
           strKeys[j+1] := strTmp;

           strTmp := strValues[j];
           strValues[j] := strValues[j+1];
           strValues[j+1] := strTmp;
        end;
      end;
   end;
end;

procedure SaveShowData();
var
  i,nCount, tmp, tmp1: Integer;
  s,  FileName: string;
begin
   SortWeiTuoData(WeiTuoDataMap);
   nCount := WeiTuoDataMap.Count;
   //ShowMessageFmt('%s--%d', ['WeiTuoDataMap', nCount]);
   s := Concat(s,  Char(13), Char(10), '���ͻ���Ϣ��', Char(13), Char(10));
   for i:=0 to nCount-1 do
   begin
     if i>0 then
     begin
       tmp := StrToInt(WeiTuoDataMap.FKeyList[i]);
       tmp1 := StrToInt(WeiTuoDataMap.FKeyList[i-1]);
       if ((tmp1<100) and (tmp>=100)) then
        s := Concat(s, Char(13), Char(10),'��������Ϣ��', Char(13), Char(10));

       if ((tmp1<200) and (tmp>=200)) then
        s := Concat(s, Char(13), Char(10),'��ί������Ϣ��', Char(13), Char(10));

        if ((tmp1<300) and (tmp>=300)) then
        s := Concat(s, Char(13), Char(10),'��Ԥ�����á�', Char(13), Char(10));
     end;

   s := Concat(s, WeiTuoDataMap.FStrList[i], Char(13), Char(10));
   end;

   FileName := Utils.GetSaveDir()+Utils.cntSaveWeiXiuForShowName;
   Save(FileName, s, False);
   //ShowMessageFmt('%s%s%s', ['��Ϣ��ȡ�ɹ�,', '����·����', FileName]);
end;

function GetJsonData():String;
var
  i,nCount, cur, pre: Integer;
  s, FileName: string;
  jsBase,js: TlkJSONobject;
begin
   SortWeiTuoData(WeiTuoDataMap);
   nCount := WeiTuoDataMap.Count;

   jsBase := TlkJSONobject.Create(True);
   js:=TlkJSONobject.Create(True);
   jsBase.Add('carOwnerInfo', js);
   for i:=0 to nCount-1 do
   begin
     if i>0 then
     begin
       cur := StrToInt(WeiTuoDataMap.FKeyList[i]);
       pre := StrToInt(WeiTuoDataMap.FKeyList[i-1]);
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

//   FileName := ExtractFilePath(ParamStr(0))+Utils.cntSaveJsonName;
//   TlkJSONstreamed.SaveToFile(jsBase, FileName);
//   ShowMessageFmt('%s%s%s', ['��Ϣ��ȡ�ɹ�,', '����·����', FileName]);
end;

procedure SaveJsonData();
var
  i,nCount, cur, pre: Integer;
  s, FileName: string;
  jsBase,js: TlkJSONobject;
begin
   SortWeiTuoData(WeiTuoDataMap);
   nCount := WeiTuoDataMap.Count;

   jsBase := TlkJSONobject.Create(True);
   js:=TlkJSONobject.Create(True);
   jsBase.Add('carOwnerInfo', js);
   for i:=0 to nCount-1 do
   begin
     cur := i;
     if i>0 then
     begin
       cur := StrToInt(WeiTuoDataMap.FKeyList[i]);
       pre := StrToInt(WeiTuoDataMap.FKeyList[i-1]);
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
   //ShowMessageFmt('%s%s%s', ['��Ϣ��ȡ�ɹ�,', '����·����', FileName]);
end;

function UpdateOp(h: HWND): Boolean;
begin
  Result := False;
  if Utils.ClassNameContains(h, cntWeiTuoCls) and Utils.ControlTextContains(h, cntWeiTuoTxt) then
  begin
       WndOp := Utils.FindeWindowBy(h, Utils.cntOpSave, cntOpSaveCls);
       Result := True;
  end;
end;

 function GetOp(): HWND;
 begin
   Result := WndOp;
 end;

end.
