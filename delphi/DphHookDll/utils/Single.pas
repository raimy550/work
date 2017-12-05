unit Single;

interface
uses Windows, SysUtils, Classes, Variants, Controls, Utils, MyLog;
 type
   TSingle = class(TObject)
   public
     class function NewInstance: TObject; override;
     procedure FreeInstance;override;
implementation
 var
  sSingle : TSingle;
end.
