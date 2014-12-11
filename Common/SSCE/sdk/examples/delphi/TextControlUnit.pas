unit TextControlUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, Ssce;

type
  TTextControlForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Edit1: TEdit;
    Label3: TLabel;
    Label4: TLabel;
    CheckTEditBtn: TButton;
    Memo1: TMemo;
    Label5: TLabel;
    CheckTMemoBtn: TButton;
    RichEdit1: TRichEdit;
    Label6: TLabel;
    CheckTRichEditBtn: TButton;
    CloseBtn: TButton;
    procedure CheckTEditBtnClick(Sender: TObject);
    procedure CloseBtnClick(Sender: TObject);
    procedure CheckTMemoBtnClick(Sender: TObject);
    procedure CheckTRichEditBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  TextControlForm: TTextControlForm;

implementation

{$R *.DFM}

procedure TTextControlForm.CheckTEditBtnClick(Sender: TObject);
begin
	SSCE_CheckCtrlDlg(Handle, Edit1.Handle, SSCE_S16(False));
end;

procedure TTextControlForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

procedure TTextControlForm.CheckTMemoBtnClick(Sender: TObject);
begin
	SSCE_CheckCtrlDlg(Handle, Memo1.Handle, SSCE_S16(False));
end;

procedure TTextControlForm.CheckTRichEditBtnClick(Sender: TObject);
begin
	SSCE_CheckCtrlDlg(Handle, RichEdit1.Handle, SSCE_S16(False));
end;

end.
