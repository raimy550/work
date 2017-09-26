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
    //�ǵ�����֮��MyMap.Free;  
    destructor Destroy; override;  
    //�����ܸ���  
    function GetCount: Integer;
    //���ؼ���Ӧ��ֵ��û�з��ؿ��ַ���  
    function Get(Key: string): string;  
    //���ԣ�Ԫ��  
    //ͨ��MyMap['key']���������  
    property Items[Key: string]: string read Get ; default;
    //���ԣ�����  
    property Count: Integer read GetCount;  
    //����  
    procedure Put(Key, Str: string);
    //�Ƴ�  
    procedure Remove(Key: string);  
    //�Ƴ�ȫ��  
    procedure RemoveAll();
  end;  
  
implementation  
  
{ TStringHashedTable }  
  
procedure TStrMap.Put(Key, Str: string);  
var KeyIndex:Integer;  
begin  
  KeyIndex := FKeyList.IndexOf(Key);  
  if KeyIndex <> -1 then  //����ҵ�����ͬKEY����ֵ��  
  begin  
    FStrList[KeyIndex] := Str;  
    Exit;
  end;  
  //���û�ҵ�����ͬKEY�����  
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
