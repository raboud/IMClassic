unit CheckStringUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SSCE;

type
  TCheckStringForm = class(TForm)
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
  CheckStringForm: TCheckStringForm;

implementation

{$R *.DFM}

procedure TCheckStringForm.CloseBtnClick(Sender: TObject);
begin
Close
end;

procedure TCheckStringForm.CheckSpellingBtnClick(Sender: TObject);
var
	text: string;
    stringLen: SSCE_S32;
    stringSize: SSCE_S32;
    theString: PChar;
    rv: SSCE_S32;
begin
	text := Memo1.Text;

    (* Allocate a string buffer that's at least 20% larger than the text
	 * being checked.
     *)
	stringLen := Length(text);
	stringSize := stringLen + (stringLen div 5);
	if (stringSize - stringLen < 256) then begin
		stringSize := stringLen + 256;
	end;

	theString := StrAlloc(stringSize + 1);
	StrLCopy(theString, PChar(text), stringLen);

	(* Check the string. The "showContext" parameter is set to True
     * so the user can see the misspelled words in context.
     *)
	rv := SSCE_CheckBlockDlg(Handle, theString, stringLen, stringSize,
      SSCE_S16(True));
    if (rv >= 0) then begin
    	(* The string is updated in place if the user makes corrections.
         * Replace the contents of the TMemo with the corrected text.
         *)
        Memo1.Text := theString;
    end;
    StrDispose(theString);
end;

end.
