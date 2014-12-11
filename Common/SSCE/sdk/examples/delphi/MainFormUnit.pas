unit MainFormUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SSCE, TextControlUnit, CheckBackgroundUnit, CheckStringUnit,
  CheckTextInCodeUnit, PerformanceTestUnit, CustomDialogBoxUnit,
  Check3rdPartyUnit, CheckHTMLUnit, LicenseKeyUnit;

const
	{ Set this constant to the license key provided by Wintertree Software. }
	SentryLicenseKey = 0;
type
  TMainForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    VersionLbl: TLabel;
    CheckTextBoxBtn: TButton;
    CheckBackgroundBtn: TButton;
    CheckStringBtn: TButton;
    CheckTextInCodeBtn: TButton;
    TestPerformanceBtn: TButton;
    CustomDialogBoxBtn: TButton;
    Check3rdPartyBtn: TButton;
    CheckHTMLBtn: TButton;
    procedure CheckTextBoxBtnClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure CheckBackgroundBtnClick(Sender: TObject);
    procedure CheckStringBtnClick(Sender: TObject);
    procedure CheckTextInCodeBtnClick(Sender: TObject);
    procedure TestPerformanceBtnClick(Sender: TObject);
    procedure CustomDialogBoxBtnClick(Sender: TObject);
    procedure Check3rdPartyBtnClick(Sender: TObject);
    procedure CheckHTMLBtnClick(Sender: TObject);
    procedure getLicenseKey;
  private
    { Private declarations }
    licenseKey: SSCE_U32;
  public
    { Public declarations }
  end;

var
  MainForm: TMainForm;

implementation

{$R *.DFM}

procedure TMainForm.FormCreate(Sender: TObject);
var
	version: Array[0..20] of char;
begin
	licenseKey := SentryLicenseKey;
    if (licenseKey <> 0) then begin
    	SSCE_SetKey(licenseKey);
    end;
    SSCE_Version(version, SizeOf(version));
    VersionLbl.Caption := 'Version ' + StrPas(version);
end;

procedure TMainForm.CheckTextBoxBtnClick(Sender: TObject);
var
	dlg: TTextControlForm;
begin
  getLicenseKey;
  dlg := TTextControlForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.CheckBackgroundBtnClick(Sender: TObject);
var
	dlg: TCheckBackgroundForm;
begin
  getLicenseKey;
  dlg := TCheckBackgroundForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.CheckStringBtnClick(Sender: TObject);
var
	dlg: TCheckStringForm;
begin
  getLicenseKey;
  dlg := TCheckStringForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.CheckTextInCodeBtnClick(Sender: TObject);
var
	dlg: TCheckTextInCodeForm;
begin
  getLicenseKey;
  dlg := TCheckTextInCodeForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.TestPerformanceBtnClick(Sender: TObject);
var
	dlg: TPerformanceTestForm;
begin
  getLicenseKey;
  dlg := TPerformanceTestForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.CustomDialogBoxBtnClick(Sender: TObject);
var
	dlg: TCustomDialogBoxForm;
begin
  getLicenseKey;
  dlg := TCustomDialogBoxForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.Check3rdPartyBtnClick(Sender: TObject);
var
	dlg: TCheck3rdPartyForm;
begin
  getLicenseKey;
  dlg := TCheck3rdPartyForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

procedure TMainForm.CheckHTMLBtnClick(Sender: TObject);
var
	dlg: TCheckHTMLForm;
begin
  getLicenseKey;
  dlg := TCheckHTMLForm.Create(self);
  dlg.ShowModal;
  dlg.Free;
end;

{ Make sure we have a valid license key. The examples won't work without one. }
procedure TMainForm.getLicenseKey;
var
	dlg: TLicenseKeyForm;
begin
    if (licenseKey = 0) then begin
    	dlg := TLicenseKeyForm.Create(self);
		dlg.ShowModal;
        licenseKey := dlg.LicenseKey;
		dlg.Free;
        SSCE_SetKey(licenseKey);
    end;
end;

end.
