unit CheckHTMLUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SSCE;

type
  TCheckHTMLForm = class(TForm)
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
  CheckHTMLForm: TCheckHTMLForm;

implementation

{$R *.DFM}

procedure TCheckHTMLForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

procedure TCheckHTMLForm.CheckSpellingBtnClick(Sender: TObject);
begin
    { Make sure the ignore HTML option is set. }
    SSCE_SetOption(SSCE_GetSid, SSCE_IGNORE_HTML_MARKUPS_OPT, 1);

    SSCE_CheckCtrlDlg(Handle, Memo1.Handle, SSCE_S16(False));
end;

end.
