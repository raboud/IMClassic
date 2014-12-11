program DelphiExample;

uses
  Forms,
  MainFormUnit in 'MainFormUnit.pas' {MainForm},
  TextControlUnit in 'TextControlUnit.pas' {TextControlForm},
  CheckBackgroundUnit in 'CheckBackgroundUnit.pas' {CheckBackgroundForm},
  CheckStringUnit in 'CheckStringUnit.pas' {CheckStringForm},
  CheckTextInCodeUnit in 'CheckTextInCodeUnit.pas' {CheckTextInCodeForm},
  PerformanceTestUnit in 'PerformanceTestUnit.pas' {PerformanceTestForm},
  CustomDialogBoxUnit in 'CustomDialogBoxUnit.pas' {CustomDialogBoxForm},
  SpellingDialogUnit in 'SpellingDialogUnit.pas' {SpellingDialogForm},
  Check3rdPartyUnit in 'Check3rdPartyUnit.pas' {Check3rdPartyForm},
  CheckHTMLUnit in 'CheckHTMLUnit.pas' {CheckHTMLForm},
  LicenseKeyUnit in 'LicenseKeyUnit.pas' {LicenseKeyForm},
  SSCE in '..\..\delphi\ssce.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'Sentry Spelling Checker Engine Delphi Example';
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TTextControlForm, TextControlForm);
  Application.CreateForm(TCheckBackgroundForm, CheckBackgroundForm);
  Application.CreateForm(TCheckStringForm, CheckStringForm);
  Application.CreateForm(TCheckTextInCodeForm, CheckTextInCodeForm);
  Application.CreateForm(TPerformanceTestForm, PerformanceTestForm);
  Application.CreateForm(TCustomDialogBoxForm, CustomDialogBoxForm);
  Application.CreateForm(TSpellingDialogForm, SpellingDialogForm);
  Application.CreateForm(TCheck3rdPartyForm, Check3rdPartyForm);
  Application.CreateForm(TCheckHTMLForm, CheckHTMLForm);
  Application.CreateForm(TLicenseKeyForm, LicenseKeyForm);
  Application.Run;
end.
