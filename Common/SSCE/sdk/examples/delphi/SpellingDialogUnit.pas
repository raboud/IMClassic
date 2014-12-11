unit SpellingDialogUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, SSCE;

const
	MAX_SUGGESTIONS = 16;
type
  TSpellingDialogForm = class(TForm)
    ProblemDescLbl: TLabel;
    ProblemWordEdit: TEdit;
    Label1: TLabel;
    ChangeToEdit: TEdit;
    Label2: TLabel;
    SuggestionsList: TListBox;
    IgnoreBtn: TButton;
    IgnoreAllBtn: TButton;
    ChangeBtn: TButton;
    ChangeAllBtn: TButton;
    SuggestBtn: TButton;
    AddBtn: TButton;
    CancelBtn: TButton;
    function runChecker: boolean;
    procedure fillSuggestionsList;
    procedure CancelBtnClick(Sender: TObject);
    procedure IgnoreBtnClick(Sender: TObject);
    procedure AddBtnClick(Sender: TObject);
    procedure ChangeAllBtnClick(Sender: TObject);
    procedure ChangeBtnClick(Sender: TObject);
    procedure IgnoreAllBtnClick(Sender: TObject);
    procedure OnSuggestionsListClick(Sender: TObject);
    procedure SuggestBtnClick(Sender: TObject);
    procedure OnSuggestionsListDblClick(Sender: TObject);
  private
    { Private declarations }
    str: SSCE_PCHAR;
    stringSize: SSCE_S32;
    cursor: SSCE_S32;
    suggestionDepth: SSCE_S16;
    memoControl: TMemo;
  public
    { Public declarations }
    function Check(control: TMemo): Boolean;
  end;

var
  SpellingDialogForm: TSpellingDialogForm;

implementation

{$R *.DFM}

(* Returns True if spelling errors were detected; False otherwise *)
function TSpellingDialogForm.Check(control: TMemo): Boolean;
var
	text: string;
    stringLen: SSCE_S32;
begin
	memoControl := control;
	text := memoControl.Text;

    (* Allocate a string buffer that's at least 20% larger than the text
	 * being checked.
     *)
	stringLen := Length(text);
	stringSize := stringLen + (stringLen div 5);
	if (stringSize - stringLen < 256) then begin
		stringSize := stringLen + 256;
	end;
	str := StrAlloc(stringSize + 1);
	StrLCopy(str, PChar(text), stringLen);

    { Start checking the text. }
    cursor := 0;
    Check := runChecker;
end;

(**fillSuggestionsList:
 * Fill the suggestions list box with suggestions for the current word.
 *)
procedure TSpellingDialogForm.fillSuggestionsList;
var
    suggBfr: Array[0..SSCE_MAX_WORD_LEN * MAX_SUGGESTIONS] of SSCE_CHAR;
    scores: Array[0..MAX_SUGGESTIONS] of SSCE_S16;
    scorePtr: SSCE_PS16;
    i: Cardinal;
    word: string;
begin
	scorePtr := @scores[0];
    word := ProblemWordEdit.Text;
    SSCE_Suggest(SSCE_GetSid, PChar(word), SSCE_GetMinSuggestDepth,
      suggBfr, SizeOf(suggBfr), scorePtr, MAX_SUGGESTIONS);

	i := 0;
    SuggestionsList.Clear;
    while (suggBfr[i] <> #0) do begin
        SuggestionsList.Items.Add(StrPas(@suggBfr[i]));
       	i := i + StrLen(@suggBfr[i]) + 1;
    end;

    { Copy the first suggestion to the change-to field. }
    if (i > 0) then begin
    	ChangeToEdit.Text := SuggestionsList.Items.Strings[0];
    end
    else begin
    	ChangeToEdit.Text := '';
    end;
end;

(* Returns True if spelling errors were detected; False otherwise *)
function TSpellingDialogForm.runChecker: boolean;
var
	word: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    otherWord: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    spellingResult: SSCE_S16;
    problem: string;
begin
    { Process auto-corrections }
    repeat
    	{ Get the next misspelled word. }
        spellingResult := SSCE_CheckString(SSCE_GetSid, str, cursor, word,
          SizeOf(word), otherWord, SizeOf(otherWord));
        if (spellingResult = SSCE_AUTO_CHANGE_WORD_RSLT) then begin
            { Replace the word in the text. }
            if (SSCE_ReplaceStringWord(SSCE_GetSid, str, stringSize, cursor,
              otherWord) >= 0) then begin
                { Replace the word in the TMemo. }
                memoControl.SelStart := cursor;
                memoControl.SelLength := StrLen(word);
                memoControl.SelText := StrPas(otherWord);
            end;

            (* Skip over the replaced word to avoid problems caused by
             * recursive replacements.
             *)
            cursor := cursor + SSCE_S32(StrLen(otherWord));
        end;
    until (spellingResult <> SSCE_AUTO_CHANGE_WORD_RSLT);

    if (spellingResult = SSCE_END_OF_BLOCK_RSLT) then begin
        { End of text reached. }
        CancelBtnClick(self);
        runChecker := False;
    end
    Else begin
        { A problem was detected. }
        runChecker := True;
        if (spellingResult = (SSCE_MISSPELLED_WORD_RSLT Or
          SSCE_UNCAPPED_WORD_RSLT)) then begin
            problem := 'Capitalization:';
        end
        else if ((spellingResult And SSCE_MISSPELLED_WORD_RSLT) <> 0) then begin
            problem := 'Not in dictionary:'
        end
        else if (spellingResult = SSCE_CONDITIONALLY_CHANGE_WORD_RSLT) then
          begin
            problem := 'Consider changing:'
        end
        else if (spellingResult = SSCE_DOUBLED_WORD_RSLT) then begin
            problem := 'Doubled word:'
        end;
        ProblemDescLbl.Caption := problem;
        ProblemWordEdit.Text := StrPas(word);

        if ((spellingResult And SSCE_MISSPELLED_WORD_RSLT) <> 0) then begin
            { Fill the suggestions list with suggestions. }
            suggestionDepth := SSCE_GetMinSuggestDepth;
            fillSuggestionsList;
        end
        else if (spellingResult = SSCE_CONDITIONALLY_CHANGE_WORD_RSLT) then
          begin
            { Add the replacement word to the suggestions list. }
            suggestionsList.Clear;
            suggestionsList.Items.Add(StrPas(otherWord));
            suggestionsList.ItemIndex := 0;
        end
        else if (spellingResult = SSCE_DOUBLED_WORD_RSLT) then begin
            { Clear the suggestions list. }
            suggestionsList.Clear;
            ChangeToEdit.Text := '';
        end;

        { Highlight the problem word in the TMemo. }
        memoControl.SelStart := cursor;
        memoControl.SelLength := StrLen(word);
    end;
end;

procedure TSpellingDialogForm.CancelBtnClick(Sender: TObject);
begin
	if (str <> nil) then begin
    	StrDispose(str);
    end;
    Close;
end;

procedure TSpellingDialogForm.IgnoreBtnClick(Sender: TObject);
begin
	{ Skip this word. }
    cursor := cursor + SSCE_S32(Length(ProblemWordEdit.Text));

    { Keep checking. }
    runChecker;
end;

procedure TSpellingDialogForm.AddBtnClick(Sender: TObject);
var
	userDictFile: Array[0..256] of char;
    lexId: SSCE_S16;
begin
    (* Add the current word to the selected user dictionary.
     * A different (slightly more complicated method) would involve
     * displaying a dropdown-list of user dictionary files (call
     * SSCEVB_GetUserLexFiles) and letting the user pick the user
     * dictionary file to add the word to.
     *)
    SSCE_GetSelUserLexFile(userDictFile, SizeOf(userDictFile));
    if (StrLen(userDictFile) > 0) then begin
        lexId := SSCE_GetLexId(userDictFile);
        if (lexId >= 0) then begin
            SSCE_AddToLex(SSCE_GetSid, lexId, PChar(ProblemWordEdit.Text),
              SSCE_IGNORE_ACTION, PChar(''));
        end;
    end;

    { Keep checking. The word will be automatically skipped. }
    runChecker;
end;

procedure TSpellingDialogForm.ChangeAllBtnClick(Sender: TObject);
var
	lexId: SSCE_S16;
begin
    if (Length(ChangeToEdit.Text) > 0) then begin
        { Add the word and replacement to the temporary dictionary. }
        lexId := SSCE_GetLexId(PChar(0));
        if (lexId >= 0) then begin
            SSCE_AddToLex(SSCE_GetSid, lexId, PChar(ProblemWordEdit.Text),
              SSCE_AUTO_CHANGE_PRESERVE_CASE_ACTION, PChar(ChangeToEdit.Text));
        end;
    end;

    (* Keep checking. This and all further occurrences of the word will
     * be automatically replaced.
     *)
    runChecker;
end;

procedure TSpellingDialogForm.ChangeBtnClick(Sender: TObject);
var
    delText: Array[0..SSCE_MAX_WORD_SZ * 2] of SSCE_CHAR;
begin
    if (Length(ChangeToEdit.Text) > 0) then begin
        { Replace the current word with the word in the Change To field. }
        if (SSCE_ReplaceStringWord(SSCE_GetSid, str, stringSize, cursor,
          PChar(ChangeToEdit.Text)) >= 0) then begin
            { Change the word in the TMemo. }
            memoControl.SelStart := cursor;
            memoControl.SelLength := Length(ProblemWordEdit.Text);
            memoControl.SelText := ChangeToEdit.Text;
        end;
    end
    else begin
        { Delete the current word and any leading whitespace. }
        cursor := SSCE_DelStringWord(SSCE_GetSid, str, cursor,
          delText, SizeOf(delText));
        if (cursor >= 0) then begin
            { Delete the word in the TMemo. }
            memoControl.SelStart := cursor;
            memoControl.SelLength := StrLen(delText);
            memoControl.SelText := '';
        end;
    end;

    { Keep checking. }
    runChecker;
end;

procedure TSpellingDialogForm.IgnoreAllBtnClick(Sender: TObject);
var
	lexId: SSCE_S16;
begin
    { Add the word to the temporary dictionary. }
    lexId := SSCE_GetLexId(PChar(0));
    if (lexId >= 0) then begin
        SSCE_AddToLex(SSCE_GetSid, lexId, PChar(ProblemWordEdit.Text),
          SSCE_IGNORE_ACTION, PChar(0));
    end;

    (* Keep checking. This and all further occurrences of the word will
     * be automatically skipped.
     *)
    runChecker;
end;

procedure TSpellingDialogForm.OnSuggestionsListClick(Sender: TObject);
begin
    { Copy the selected suggestion to the Change To field. }
    ChangeToEdit.Text :=
      SuggestionsList.Items.Strings[SuggestionsList.ItemIndex];
end;

procedure TSpellingDialogForm.SuggestBtnClick(Sender: TObject);
begin
    { Locate better suggestions by increasing the suggestion depth. }
    suggestionDepth := suggestionDepth + 10;
    fillSuggestionsList;
end;

procedure TSpellingDialogForm.OnSuggestionsListDblClick(Sender: TObject);
begin
	{ Automatically replace the current word with the selected word. }
    OnSuggestionsListClick(Sender);
    ChangeBtnClick(Sender);
end;

end.
