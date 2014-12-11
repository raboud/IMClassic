unit CheckTextInCodeUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SSCE;

const
	MAX_SUGGESTIONS = 16;
type
  TCheckTextInCodeForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Memo1: TMemo;
    CheckSpellingBtn: TButton;
    Label4: TLabel;
    Memo2: TMemo;
    CloseBtn: TButton;
    procedure CloseBtnClick(Sender: TObject);
    procedure CheckSpellingBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  CheckTextInCodeForm: TCheckTextInCodeForm;

implementation

{$R *.DFM}

procedure TCheckTextInCodeForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

procedure TCheckTextInCodeForm.CheckSpellingBtnClick(Sender: TObject);
var
    result: SSCE_S16;
    str: PChar;
    stringSize: Integer;
    word: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    otherword: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    suggBfr: Array[0..SSCE_MAX_WORD_LEN * MAX_SUGGESTIONS] of SSCE_CHAR;
    scores: Array[0..MAX_SUGGESTIONS] of SSCE_S16;
    scorePtr: SSCE_PS16;
    i: Cardinal;
    line: string;
    cursor: SSCE_S32;
begin
	{ Copy the TMemo's contents to a string. The string won't be modified. }
    stringSize := Length(Memo1.Text) + 1;	{ room for terminating null }
    str := StrAlloc(stringSize);
    StrLCopy(str, PChar(Memo1.Text), Length(Memo1.Text));

    Memo2.Lines.Clear;

    { Keep checking until all the text has been checked. }
    result := 0;
    cursor := 0;
    while ((result >= 0) And (result <> SSCE_END_OF_BLOCK_RSLT)) do begin
        result := SSCE_CheckString(SSCE_GetSid, str, cursor, word, SizeOf(word),
          otherWord, SizeOf(otherWord));

        if ((result And SSCE_MISSPELLED_WORD_RSLT) <> 0) then begin
            { We found a misspelled word. Get some suggestions for it. }
            scorePtr := @scores[0];
            SSCE_Suggest(SSCE_GetSid, word, SSCE_GetMinSuggestDepth,
              suggBfr, SizeOf(suggBfr), scorePtr, MAX_SUGGESTIONS);

            i := 0;
            line := '';
            while (suggBfr[i] <> #0) do begin
            	if (Length(line) > 0) then begin
                	line := line + ', ';
                end;
				line := line + StrPas(@suggBfr[i]);
       	        i := i + StrLen(@suggBfr[i]) + 1;
            end;

            (* Add the misspelled word and suggestions to the
             * "Misspelled words" box.
             *)
            Memo2.Lines.Add(StrPas(word) + ': ' + line);
            Memo2.Lines.Add('');
        end;

        (* Advance to the next word. This is necessary or SSCE_CheckString
         * will keep reporting the same word.
         *)
        cursor := cursor + SSCE_S32(StrLen(word));
    end;

    StrDispose(str);
end;

end.
