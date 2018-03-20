unit DataTrans;

interface
uses
  IdHTTP, SysUtils, Classes,Contnrs;
type
{ TDataTrans }

  TDataTrans = class(TObject)
  private
    mIdhttp: TIdHTTP;
    mPostData : TStringStream;
  public
    constructor Create();
    function  HttpPost(postUrl:string;data:String):string;

  end;


implementation


constructor TDataTrans.Create;
begin
  inherited;
  mIdhttp := TidHTTp.create(nil);
end;

function  TDataTrans.HttpPost(postUrl:string;data:String):string;
begin
  mIdhttp.AllowCookies:=True;
  mIdhttp.HTTPOptions:=[hoForceEncodeParams];
  mIdhttp.ProtocolVersion:= pv1_1;
  mIdhttp.Request.ContentType:= 'application/json';//'application/x-www-form-urlencoded';
  mIdhttp.Request.CacheControl:='no-cache';
  mIdhttp.Request.UserAgent:= 'User-Agent=Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.0.1) Gecko/2008070208 Firefox/3.0.1';
  mIdhttp.Request.Accept:= 'Accept=text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8';
  mIdhttp.Request.AcceptEncoding:= 'Accept-Encoding=gzip,deflate';
  mIdhttp.Request.AcceptCharSet:= 'Accept-Charset=gb2312,utf-8;q=0.7,*;q=0.7';
  mIdhttp.Request.Connection:= 'Connection=keep-alive';
  try
    mPostData := TStringStream.Create(data);
    result := mIdhttp.Post(postUrl,mPostData);
  except
    Result := 'error';
  end;
end;

end.
