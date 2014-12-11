unit PerformanceTestUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, SSCE;

type
  TPerformanceTestForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    RichEdit1: TRichEdit;
    StartBtn: TButton;
    ResultsLbl: TLabel;
    CloseBtn: TButton;
    procedure CloseBtnClick(Sender: TObject);
    procedure StartBtnClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  PerformanceTestForm: TPerformanceTestForm;

implementation

{$R *.DFM}

procedure TPerformanceTestForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

procedure TPerformanceTestForm.StartBtnClick(Sender: TObject);
var
    result: SSCE_S16;
    stringLen: SSCE_S32;
    stringSize: SSCE_S32;
    str: PChar;
    word: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    otherword: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    numMisspelledWords: LongInt;
    totalTime: LongWord;
    startTime: LongWord;
    numWords: SSCE_S32;
    cursor: SSCE_S32;
begin
	(* Allocate a string to check the TRichEdit's contents. The string won't be
     * modified.
     *)
    stringLen := Length(RichEdit1.Text);
    stringSize := stringLen + 1;	{ room for terminating null }
    str := StrAlloc(stringSize);
    StrLCopy(str, PChar(RichEdit1.Text), stringLen);

    ResultsLbl.Caption := '';

    { Keep checking until all the text has been checked. }
    result := 0;
    numMisspelledWords := 0;
    totalTime := 0;
    cursor := 0;
    while ((result >= 0) And (result <> SSCE_END_OF_BLOCK_RSLT)) do begin
    	startTime := GetTickCount;
        result := SSCE_CheckString(SSCE_GetSid, str, cursor, word, SizeOf(word),
          otherWord, SizeOf(otherWord));
        totalTime := totalTime + GetTickCount - startTime;

        if ((result And SSCE_MISSPELLED_WORD_RSLT) <> 0) then begin
        	Inc(numMisspelledWords);
        end;

        (* Advance to the next word. This is necessary or SSCE_CheckString
         * will keep reporting the same word.
         *)
        cursor := cursor + SSCE_S32(StrLen(word));
    end;

    { Count the number of words in the string. }
    cursor := 0;
    numWords := 0;
    while (cursor >= 0) do begin
	    cursor := SSCE_GetStringWord(SSCE_GetSid, str, cursor, word,
          SizeOf(word));
        if (cursor >= 0) then begin
	      	Inc(numWords);
    	    cursor := cursor + SSCE_S32(StrLen(word));
        end;
    end;
    StrDispose(str);

    { Display the results. }
    if (totalTime = 0) then begin
    	totalTime := 1;	{ Don't divide by 0 }
    end;
    ResultsLbl.Caption := IntToStr(numWords) + ' words. ' +
      IntToStr(numMisspelledWords) + ' misspelled words. ' +
      IntToStr(totalTime) + ' ms. ' +
	  IntToStr(LongWord(numWords) * LongWord(1000) div totalTime) +
      ' words/second.';
end;

end.
