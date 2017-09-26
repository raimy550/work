unit LoginInfo;

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

var
  strCompany: string;
  Info, PtlInfo, DataMap: TStrMap; // key:tab,value:信息

procedure Init();
procedure ParseData(h: HWND);
procedure SaveJsonData();

implementation

procedure AddData(tab: Integer; buf: string);
var
    key, value: string;
begin
  Utils.DebugOut('-----------AddData');
    key := Info.Get(IntToStr(tab));
    if (key<>'') and (buf<>'') then
    begin
      Utils.DebugOut('-----------AddData1');
      //ShowMessageFmt('AddData:%s----%s', [key, buf]);
      Utils.DebugOut('-----------AddData2');
      DataMap.Put(IntToStr(tab), buf);
      Utils.DebugOut('-----------AddData3');
    end;
    Utils.DebugOut('-----------AddData4');

end;

procedure Init();
begin
  Info := TStrMap.Create;
  PtlInfo := TStrMap.Create;
  DataMap := TStrMap.Create;

  Info.Put(IntToStr(0), '公司名称');
  Info.Put(IntToStr(1), '用户代码');
  Info.Put(IntToStr(2), '用户口令');

  PtlInfo.Put(IntToStr(0), 'companyname');
  PtlInfo.Put(IntToStr(1), 'username');
  PtlInfo.Put(IntToStr(2), 'userpwd');
end;

procedure HandleData(h: HWND);
var
   buf: array[0..255] of Char;
   tcl: TWinControl;
   tab: Integer;
begin
    if Utils.FilterControls(h) then
    begin
      tcl := Utils.GetInstanceFromhWnd(h);
      if tcl.Visible then
      begin
        tcl.GetTextBuf(buf, Length(buf));
        tab := tcl.TabOrder;
        if tab=0 then
        begin
          if Utils.ClassNameContains(h, 'TcxLookupComboBox') then
            AddData(tab, buf);
        end
        else
          AddData(tab, buf);
      end;

    end;
end;

procedure ParseData(h: HWND);
begin
    HandleData(h);
end;

procedure SaveJsonData();
var
  i,nCount: Integer;
  s, FileName: string;
  jsBase,js: TlkJSONobject;
begin
   Utils.SortData(DataMap);
   nCount := DataMap.Count;

   jsBase := TlkJSONobject.Create(True);
   js:=TlkJSONobject.Create(True);
   jsBase.Add('LoginInfo', js);
   for i:=0 to nCount-1 do
   begin
      js.Add(PtlInfo.Get(DataMap.FKeyList[i]), DataMap.Get(DataMap.FKeyList[i]));
   end;

   FileName := Utils.GetSaveDir()+Utils.cntSaveLoginFileName;
   TlkJSONstreamed.SaveToFile(jsBase, FileName);
   //ShowMessageFmt('%s%s%s', ['信息获取成功,', '保存路径：', FileName]);
end;

end.
