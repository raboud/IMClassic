unit Check3rdPartyUnit;

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, SSCE;

type
  TCheck3rdPartyForm = class(TForm)
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    Label4: TLabel;
    RichEdit1: TRichEdit;
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
  Check3rdPartyForm: TCheck3rdPartyForm;

implementation

{$R *.DFM}

procedure TCheck3rdPartyForm.CloseBtnClick(Sender: TObject);
begin
	Close;
end;

procedure TCheck3rdPartyForm.CheckSpellingBtnClick(Sender: TObject);
var
    result: SSCE_S16;
    stringLen: SSCE_S32;
    stringSize: SSCE_S32;
    str: PChar;
    word: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    otherword: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    curWord: Array[0..SSCE_MAX_WORD_SZ] of SSCE_CHAR;
    cursor: SSCE_S32;
begin
    (* Allocate a string buffer that's at least 20% larger than the text
	 * being checked.
     *)
	stringLen := Length(RichEdit1.Text);
	stringSize := stringLen + (stringLen div 5);
	if (stringSize - stringLen < 256) then begin
		stringSize := stringLen + 256;
	end;

	str := StrAlloc(stringSize + 1);
	StrLCopy(str, PChar(RichEdit1.Text), stringLen);

    { Keep checking until all the text has been checked. }
    result := 0;
    cursor := 0;
    while ((result >= 0) And (result <> SSCE_END_OF_BLOCK_RSLT)) do begin
        result := SSCE_CheckString(SSCE_GetSid, str, cursor, word, SizeOf(word),
          otherWord, SizeOf(otherWord));
		if ((result >= 0) And (result <> SSCE_END_OF_BLOCK_RSLT)) then begin
            (* A problem was encountered with a word in the text.
	         * Highlight the misspelled word in the TRichEdit. Use whatever
    	     * properties and methods are appropriate to the 3rd-party control
        	 * you are using.
             *)
	        RichEdit1.SelStart := cursor;
	        RichEdit1.SelLength := StrLen(word);

	        (* Check the current word using CheckBlockDlg. This will give the user
    	     * a chance to correct the misspelling. It may also be corrected
        	 * automatically.
             *)
            StrCopy(curWord, word);
	        result := SSCE_CheckBlockDlg(Handle, curWord, StrLen(curWord),
              SizeOf(curWord), SSCE_S16(False));
	        if (result >= 0) then begin
		        { See if the word was changed. }
		        if (StrComp(curWord, word) <> 0) then begin
		            { The word was changed. Update the text with the new word. }
		            if (SSCE_ReplaceStringWord(SSCE_GetSid, str, stringSize,
                      cursor, curWord) >= 0) then begin
		                (* Update the rich-edit box. The current word is selected,
        		         * so all we have to do is replace the selected text.
                		 * Use whatever properties or methods are appropriate to the
                         * 3rd-party control you are using.
                         *)
		                RichEdit1.SelText := StrPas(curWord);
                    end;
                end;
            end;
        end;

        { Advance to the next word. }
        cursor := cursor + SSCE_S32(StrLen(curWord));
    end;

    StrDispose(str);
end;

end.
