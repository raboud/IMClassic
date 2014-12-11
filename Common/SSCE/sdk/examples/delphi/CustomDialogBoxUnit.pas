unit CustomDialogBoxUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SpellingDialogUnit;

type
  TCustomDialogBoxForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Memo1: TMemo;
    CheckSpellingBtn: TButton;
    CloseBtn: TButton;
    procedure CloseBtnClick(Sender: TObject);
    procedure CheckSpellingBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CustomDialogBoxForm: TCustomDialogBoxForm;

implementation

{$R *.DFM}

procedure TCustomDialogBoxForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

procedure TCustomDialogBoxForm.CheckSpellingBtnClick(Sender: TObject);
var
	dlg: TSpellingDialogForm;
begin
  dlg := TSpellingDialogForm.Create(self);
  if (dlg.Check(Memo1)) then begin
  	dlg.ShowModal;
  end;
  dlg.Free;
end;

end.
