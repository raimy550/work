unit DataTrans;

interface
uses
  IdHTTP, SysUtils, Classes,Contnrs;
  function  HttpPost(postUrl:string;data:String):string;

implementation
var
  idhtp1: TIdHTTP;
  PostData : TStringStream;

function  HttpPost(postUrl:string;data:String):string;
begin
  idhtp1:=   TidHTTp.create(nil);
  idhtp1.AllowCookies:=True;
  idhtp1.HTTPOptions:=[hoForceEncodeParams];
  idhtp1.ProtocolVersion:= pv1_1;
  idhtp1.Request.ContentType:= 'application/json';//'application/x-www-form-urlencoded';
  idhtp1.Request.CacheControl:='no-cache';
  idhtp1.Request.UserAgent:= 'User-Agent=Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.0.1) Gecko/2008070208 Firefox/3.0.1';
  idhtp1.Request.Accept:= 'Accept=text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8';
  idhtp1.Request.AcceptEncoding:= 'Accept-Encoding=gzip,deflate';
  idhtp1.Request.AcceptCharSet:= 'Accept-Charset=gb2312,utf-8;q=0.7,*;q=0.7';
  idhtp1.Request.Connection:= 'Connection=keep-alive';
  try
    PostData := TStringStream.Create(data);  
    result := idhtp1.Post(postUrl,PostData);
  except
    Result := 'error';
  end;
end;

end.
