unit CheckBackgroundUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, SSCE;

type
  TCheckBackgroundForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    RichEdit1: TRichEdit;
    RichEdit2: TRichEdit;
    CloseBtn: TButton;
    procedure OnEnterRichEdit1(Sender: TObject);
    procedure OnEnterRichEdit2(Sender: TObject);
    procedure CloseBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CheckBackgroundForm: TCheckBackgroundForm;

implementation

{$R *.DFM}

procedure TCheckBackgroundForm.OnEnterRichEdit1(Sender: TObject);
begin
	SSCE_CheckCtrlBackground(RichEdit1.Handle);
end;

procedure TCheckBackgroundForm.OnEnterRichEdit2(Sender: TObject);
begin
	SSCE_CheckCtrlBackground(RichEdit2.Handle);
end;

procedure TCheckBackgroundForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

end.
