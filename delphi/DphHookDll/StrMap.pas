unit StrMap;

interface  
uses  
  SysUtils, Classes,Contnrs;  
  
type  
  TStrMap = class(TPersistent)  
    FKeyList: TStrings;
    FStrList: TStrings;
  private  
    //procedure SetItems(Key: string; const Value: string);  
  public  
    constructor Create;  
    //记得用完之后，MyMap.Free;  
    destructor Destroy; override;  
    //返回总个数  
    function GetCount: Integer;
    //返回键对应的值，没有返回空字符串  
    function Get(Key: string): string;  
    //属性，元素  
    //通过MyMap['key']这个方法用  
    property Items[Key: string]: string read Get ; default;
    //属性，总数  
    property Count: Integer read GetCount;  
    //放入  
    procedure Put(Key, Str: string);
    //移除  
    procedure Remove(Key: string);  
    //移除全部  
    procedure RemoveAll();
  end;  
  
implementation  
  
{ TStringHashedTable }  
  
procedure TStrMap.Put(Key, Str: string);  
var KeyIndex:Integer;  
begin  
  KeyIndex := FKeyList.IndexOf(Key);  
  if KeyIndex <> -1 then  //如果找到了相同KEY，设值。  
  begin  
    FStrList[KeyIndex] := Str;  
    Exit;
  end;  
  //如果没找到了相同KEY，添加  
  FKeyList.Add(Key);  
  FStrList.Add(Str);  
end;  
  
constructor TStrMap.Create;  
begin  
  
  FKeyList := TStringList.Create;  
  FStrList := TStringList.Create;  
end;  
  
procedure TStrMap.Remove(Key: string);  
var  
  KeyIndex: Integer;  
begin  
  KeyIndex := FKeyList.IndexOf(Key);  
  FKeyList.Delete(KeyIndex);  
  FStrList.Delete(KeyIndex);  
end;  
  
procedure TStrMap.RemoveAll;  
begin  
  FKeyList.Clear;  
  FStrList.Clear;  
end;  
  
destructor TStrMap.Destroy;  
begin  
  FStrList.Free;  
  FKeyList.Free;  
  inherited Destroy;  
end;  
  
function TStrMap.GetCount: Integer;  
begin  
  Result := FKeyList.Count;  
end;  
  
function TStrMap.Get(Key: string): string;
var  
  KeyIndex: Integer;  
begin  
  KeyIndex := FKeyList.IndexOf(Key);
  if KeyIndex = -1 then
    Result := ''
  else
    Result := FStrList[KeyIndex];
end; 


end.  
