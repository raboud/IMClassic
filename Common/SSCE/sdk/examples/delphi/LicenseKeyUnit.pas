unit LicenseKeyUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SSCE;

type
  TLicenseKeyForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    KeyEdit: TEdit;
    OKBtn: TButton;
    CancelBtn: TButton;
    procedure OKBtnClick(Sender: TObject);
    procedure CancelBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
    LicenseKey: SSCE_S32;
  end;

var
  LicenseKeyForm: TLicenseKeyForm;

implementation

{$R *.DFM}

procedure TLicenseKeyForm.OKBtnClick(Sender: TObject);
begin
	LicenseKey := StrToInt('$' + KeyEdit.Text);
    Close;
end;

procedure TLicenseKeyForm.CancelBtnClick(Sender: TObject);
begin
	LicenseKey := 0;
    Close;
end;

procedure TLicenseKeyForm.FormCreate(Sender: TObject);
begin
	KeyEdit.Text := IntToStr(LicenseKey);
end;

end.
