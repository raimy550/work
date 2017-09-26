unit BaseInfo;

interface
uses  
  SysUtils, Classes, StrMap, Windows,Controls,
  StdCtrls;

  type
    CBaseInfo = class(TObject)
    private

    protected
      ShowInfo: TStrMap;        //key:tab,  value:展示信息
      ShowDataMap: TStrMap; //key:tab,  value:展示数据
      PtlInfo: TStrMap;     //key:tab,  value:协议信息
      PtlDataMap: TStrMap;  //key:tab,  value:协议数据
      WndOp: HWND;   // 操作按钮


      
      procedure Init(); virtual;Abstract;
      function HandleData(h: HWND): Boolean;virtual;Abstract;


      procedure AddData(tab: Integer; buf: string);
      function GetKeyByTab(tab: Integer): string;
      function GetPtlInfoByTab(tab: Integer): string;
      procedure SortData(dataMap: TStrMap);


    public
     constructor Create();virtual;
     procedure ParseData(h: HWND); virtual;
     procedure CleanData();virtual;
     procedure SaveJsonData();virtual;
     function GetOp(): HWND; virtual;
     function UpdateOp(h: HWND): Boolean;virtual;
   end;

implementation
  constructor CBaseInfo.Create;
  begin
    ShowInfo := TStrMap.Create;
    ShowDataMap := TStrMap.Create;
    PtlInfo := TStrMap.Create;
    PtlDataMap := TStrMap.Create;
    
    Init();
  end;

  procedure CBaseInfo.CleanData;
  begin
    ShowDataMap.RemoveAll;
    PtlDataMap.RemoveAll;
  end;

   procedure CBaseInfo.SaveJsonData();
   begin
   
   end;

  procedure CBaseInfo.ParseData(h: HWND);
  var
  bDone: Boolean;
  begin

    bDone := HandleData(h);
    if bDone=True then
      Exit;

    h := GetWindow(h, GW_CHILD);
    while h <> 0 do
    begin
      ParseData(h);
      h := GetWindow(h, GW_HWNDNEXT);
    end;
  end;

procedure CBaseInfo.AddData(tab: Integer; buf: string);
var
key, value: string;
begin
    key := GetKeyByTab(tab);
    if (key<>'') and (buf<>'') then
    begin
      value := key+':'+ buf;
      ShowDataMap.Put(IntToStr(tab), value);
      PtlDataMap.Put(IntToStr(tab), buf);
    end;

end;

function CBaseInfo.GetKeyByTab(tab: Integer): string;
begin
 Result := '';
 Result := ShowInfo.Get(IntToStr(tab));
end;

function CBaseInfo.GetPtlInfoByTab(tab: Integer): string;
begin
 Result := '';
 Result := PtlInfo.Get(IntToStr(tab));
end;


procedure CBaseInfo.SortData(dataMap: TStrMap);
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

function CBaseInfo.GetOp(): HWND;
begin
    Result := WndOp;
end;

function CBaseInfo.UpdateOp(h: HWND): Boolean;
begin

end;

end.
