(* Sentry Spelling Checker Engine
 * SSCE VCL:
 * An interface to the SSCE Windows API using a Delphi Visual Component.
 * Supports Delphi 1 and 2 (16/32 bit).
 *
 * Copyright (c) 1993 Wintertree Software Inc.
 * www.wintertree-software.com
 *
 * Use, duplication, and disclosure of this file is governed by
 * a license agreement between Wintertree Software Inc. and
 * the licensee.
 *
 * $Id: sscevcl.pas,v 5.14 2000/06/28 17:32:17 wsi Exp wsi $
 *)

unit SsceVCL;

{$ifdef win32}
  {$R vcl32.dcr}
{$else}
  {$R vcl16.dcr}
{$endif win32}

interface
uses SysUtils, WinTypes, WinProcs, Classes, Controls, Forms, SSCE;
type
	DocSourceType = (NoDocSource, TextDocSource, ControlDocSource);
	TSsceSpellDlg = class(TComponent)
	private
		DocSource: DocSourceType;
		FCheckSelTextOnly: Boolean;
		FControlHWnd: HWND;
		FDebugFile: String;
		FResult: Integer;
        FShowContext: Boolean;
		FText: PChar;
        function GetAutoCorrect: Boolean;
        function GetErrorsDetected: Integer;
        function GetHelpFile: String;
		function GetMainLexFiles: String;
		function GetMainLexPath: String;
        function GetMinSuggestDepth: Integer;
        {$IFDEF WIN32}
        function GetRegTreeName: String;
        {$ENDIF}
        function GetStringTableName: String;
		function GetText: PChar;
		function GetTextStr: String;
		function GetUserLexFiles: String;
		function GetUserLexPath: String;
		function GetVersion: String;
        function GetWordsChanged: Integer;
        function GetWordsChecked: Integer;
        procedure SetAutoCorrect(ac: Boolean);
		procedure SetControlHWnd(handle: HWND);
		procedure SetDebugFile(debugFile: String);
        procedure SetHelpFile(fileName: String);
        procedure SetKey(key: Longint);
		procedure SetMainLexFiles(fileList: String);
		procedure SetMainLexPath(path: String);
        procedure SetMinSuggestDepth(depth: Integer);
        {$IFDEF WIN32}
        procedure SetRegTreeName(treeName: String);
        {$ENDIF}
        procedure SetStringTableName(tableName: String);
		procedure SetText(aText: PChar);
		procedure SetTextStr(aStr: String);
		procedure SetUserLexFiles(fileList: String);
		procedure SetUserLexPath(path: String);
	public
		constructor Create(aOwner: TComponent); override;
		function Execute: Boolean;
		property ControlHandle: HWND read FControlHWnd write SetControlHWnd
		  stored False;
        property Key: Longint write SetKey stored False;
		procedure ResetTempLexicons;
		property Result: Integer read FResult stored False;
		property Text: PChar read GetText write SetText stored False;
		property TextStr: String read GetTextStr write SetTextStr stored False;
	published
    	property AutoCorrect: Boolean read GetAutoCorrect write SetAutoCorrect
          stored False;
		property CheckSelTextOnly: Boolean read FCheckSelTextOnly
		  write FCheckSelTextOnly;
		property DebugFile: String read FDebugFile write SetDebugFile stored
		  False;
        property ErrorsDetected: Integer read GetErrorsDetected stored False;
        property HelpFile: String read GetHelpFile write SetHelpFile stored
          False;
		property MainLexFiles: String read GetMainLexFiles
		  write SetMainLexFiles stored False;
		property MainLexPath: String read GetMainLexPath write SetMainLexPath
		  stored False;
        property MinSuggestDepth: Integer read GetMinSuggestDepth write
          SetMinSuggestDepth stored False;
        {$IFDEF WIN32}
        property RegTreeName: String read GetRegTreeName write SetRegTreeName
          stored False;
        {$ENDIF}
        property StringTableName: String read GetStringTableName write
          SetStringTableName stored False;
		property ShowContext: Boolean read FShowContext write FShowContext;
		property UserLexFiles: String read GetUserLexFiles write SetUserLexFiles
		  stored False;
		property UserLexPath: String read GetUserLexPath write SetUserLexPath
		  stored False;
		property Version: String read GetVersion stored False;
        property WordsChanged: Integer read GetWordsChanged stored False;
        property WordsChecked: Integer read GetWordsChecked stored False;
	end;

procedure Register;

implementation

constructor TSsceSpellDlg.Create(aOwner: TComponent);
begin
	inherited Create(aOwner);
	DocSource := NoDocSource;
	FCheckSelTextOnly := False;
	FDebugFile := '';
	FResult := 0;
    FShowContext := True;
	FText := nil;
end;

(**Execute
 * Interactively check spelling of the text or control.
 * @return True if the spelling check succeeded; False if the user canceled.
 *)
function TSsceSpellDlg.Execute: Boolean;
var
	block: PChar;
	blockLen: LongInt;
	blockSize: LongInt;
	parentHandle: HWND;
	retVal: LongInt;
begin
	{ Get the parent form's handle. }
	parentHandle := 0;
	if (Owner is TForm) then begin
		parentHandle := (Owner as TForm).Handle;
	end;

	{ Use CheckBlockDlg or CheckCtrlDlg, depending on the thing being checked. }
	if (DocSource = TextDocSource) then begin
	   (* Allocate a string buffer that's at least 10% larger than the text
		* being checked.
		*)
		blockLen := StrLen(FText);
		blockSize := blockLen + (blockLen div 10);
		if (blockSize < 100) then begin
			blockSize := 100;
		end;

		block := StrAlloc(blockSize + 1);
		StrLCopy(block, FText, blockLen);

		{ Check the block. }
		retVal := SSCE_CheckBlockDlg(parentHandle, block, blockLen, blockSize,
		  SSCE_S16(FShowContext));
		if (retVal >= 0) then begin
			{ Get the corrected block. }
			if (blockLen < retVal) then begin
				{ The block grew. Allocate more space. }
				StrDispose(FText);
				FText := StrAlloc(retVal + 1);
			end;
			StrLCopy(FText, block, retVal);
			Execute := True;
			FResult := 0;
		end
		else begin
			Execute := False;
			FResult := Integer(retVal);
		end;
		StrDispose(block);
	end
	else if (DocSource = ControlDocSource) then begin
		retVal := SSCE_CheckCtrlDlg(parentHandle, FControlHWnd,
		  Integer(FCheckSelTextOnly));
		Execute := (retVal >= 0);
       FResult := Integer(retVal);
	end
	else begin
		Execute := False;
	end;
end;

(**GetAutoCorrect
 * Return the current value of the AutoCorrect property.
 * @return True if auto-correct enabled; False otherwise
 *)
function TSsceSpellDlg.GetAutoCorrect: Boolean;
begin
    GetAutoCorrect := Boolean(SSCE_GetAutoCorrect);
end;

(**GetErrorsDetected
 * Obtain the number of misspelled words detected in the last text checked.
 * @return Number of misspelled words
 *)
function TSsceSpellDlg.GetErrorsDetected: Integer;
var
	wordsChecked, wordsChanged, errors: SSCE_U32;
begin
    SSCE_GetStatistics(wordsChecked, wordsChanged, errors);
    GetErrorsDetected := errors;
end;

(**GetHelpFile
 * Obtain the name of the help file invoked when the Help button is pressed
 * on a dialog.
 * @return help file name
 *)
function TSsceSpellDlg.GetHelpFile: String;
var
	fileName: array[0..255] of Char;
begin
	SSCE_GetHelpFile(fileName, SizeOf(fileName));
	GetHelpFile := StrPas(fileName);
end;

(**GetMainLexFiles
 * Obtain the list of files forming the main lexicon
 * @return Lexicon file list
 *)
function TSsceSpellDlg.GetMainLexFiles: String;
var
	fileList: array[0..255] of Char;
begin
	SSCE_GetMainLexFiles(fileList, SizeOf(fileList));
	GetMainLexFiles := StrPas(fileList);
end;

(**GetMainLexPath
 * Obtain the path to the directory containing the main lexicon files.
 * @return Lexicon path
 *)
function TSsceSpellDlg.GetMainLexPath: String;
var
	path: array[0..255] of Char;
begin
	SSCE_GetMainLexPath(path, SizeOf(path));
	GetMainLexPath := StrPas(path);
end;

(**GetMinSuggestDepth
 * Return the current value of the MinSuggestDetph property.
 * @return Minimum suggestion depth
 *)
function TSsceSpellDlg.GetMinSuggestDepth: Integer;
begin
    GetMinSuggestDepth := SSCE_GetMinSuggestDepth;
end;

{$IFDEF WIN32}

(**GetRegTreeName
 * Obtain the name of the registry tree used to read and save property values.
 * @return Registry tree name
 *)
function TSsceSpellDlg.GetRegTreeName: String;
var
	treeName: array[0..255] of Char;
begin
	SSCE_GetRegTreeName(treeName, SizeOf(treeName));
	GetRegTreeName := StrPas(treeName);
end;

{$ENDIF}

(**GetStringTableName
 * Obtain the name of the string table used to read strings displayed by SSCE.
 * @return String table name
 *)
function TSsceSpellDlg.GetStringTableName: String;
var
	tableName: array[0..255] of Char;
begin
	SSCE_GetStringTableName(tableName, SizeOf(tableName));
	GetStringTableName := StrPas(tableName);
end;

(**GetText
 * Retrieve the text property as a PChar value.
 * @return Text property value
 *)
function TSsceSpellDlg.GetText: PChar;
begin
	if (FText <> nil) then begin
		FText := StrAlloc(1 + 1);
		StrPCopy(FText, '');
	end;
	GetText := FText;
end;

(**GetTextStr
 * Retrieve the Text property as a Pascal string. Only the 1st 255 characters
 * are retrieved.
 * @return Text property string
 *)
function TSsceSpellDlg.GetTextStr: String;
begin
	if (FText <> nil) then begin
		GetTextStr := StrPas(FText);
	end
	else begin
		GetTextStr := '';
	end;
end;

(**GetUserLexFiles
 * Obtain the list of user lexicon files.
 * @return User lexicon file list
 *)
function TSsceSpellDlg.GetUserLexFiles: String;
var
	fileList: array[0..255] of Char;
begin
	SSCE_GetUserLexFiles(fileList, SizeOf(fileList));
	GetUserLexFiles := StrPas(fileList);
end;

(**GetUserLexPath
 * Obtain the path to the directory containing the user lexicon files.
 * @return User lexicon path
 *)
function TSsceSpellDlg.GetUserLexPath: String;
var
	path: array[0..255] of Char;
begin
	SSCE_GetUserLexPath(path, SizeOf(path));
	GetUserLexPath := StrPas(path);
end;

(**GetVersion
 * Obtain the Sentry Spelling Checker Engine version.
 * @return Version id
 *)
function TSsceSpellDlg.GetVersion: String;
var
	version: array[0..255] of Char;
begin
	SSCE_Version(version, SizeOf(version));
	GetVersion := StrPas(version);
end;

(**GetWordsChanged
 * Obtain the number of words changed in the last text checked.
 * @return Number of changed words
 *)
function TSsceSpellDlg.GetWordsChanged: Integer;
var
	wordsChecked, wordsChanged, errors: SSCE_U32;
begin
    SSCE_GetStatistics(wordsChecked, wordsChanged, errors);
    GetWordsChanged := wordsChanged;
end;

(**GetWordsChecked:
 * Obtain the number of words checked in the last text.
 * @return Number of checked words
 *)
function TSsceSpellDlg.GetWordsChecked: Integer;
var
	wordsChecked, wordsChanged, errors: SSCE_U32;
begin
    SSCE_GetStatistics(wordsChecked, wordsChanged, errors);
    GetWordsChecked := wordsChecked;
end;

(**ResetTempLexicons:
 * Clear the contents of temporary lexicons used by the dialog.
 * The temporary lexicons are used to hold ignore-all and change-all words.
 *)
procedure TSsceSpellDlg.ResetTempLexicons;
begin
	SSCE_ResetLex;
end;

(**SetAutoCorrect:
 * Change the value of the AutoCorrect property.
 *)
procedure TSsceSpellDlg.SetAutoCorrect(ac: Boolean);
begin
	SSCE_SetAutoCorrect(SSCE_S16(ac));
end;

(**SetControlHWnd:
 * Set the handle of a control to be checked.
 *)
procedure TSsceSpellDlg.SetControlHWnd(handle: HWND);
begin
	FControlHWnd := handle;
	DocSource := ControlDocSource;
end;

(**SetDebugFile:
 * Set the name of a log file used to record diagnostic information.
 *)
procedure TSsceSpellDlg.SetDebugFile(debugFile: String);
var
	cStr: array[0..255] of Char;
begin
	FDebugFile := debugFile;
	StrPCopy(cStr, debugFile);
	SSCE_SetDebugFile(cStr);
end;

(**SetHelpFile:
 * Set the name of the help file invoked when the Help button is pressed.
 *)
procedure TSsceSpellDlg.SetHelpFile(fileName: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, fileName);
	SSCE_SetHelpFile(cStr);
end;

(**SetKey:
 * Set the license key used to unlock the Sentry DLL.
 *)
procedure TSsceSpellDlg.SetKey(key: Longint);
begin
	SSCE_SetKey(key);
end;

(**SetMainLexFiles:
 * Set the list of files forming the main lexicon.
 *)
procedure TSsceSpellDlg.SetMainLexFiles(fileList: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, fileList);
	SSCE_SetMainLexFiles(cStr);
end;

(**SetMainLexPath:
 * Set the path to the directory containing the main lexicon files.
 *)
procedure TSsceSpellDlg.SetMainLexPath(path: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, path);
	SSCE_SetMainLexPath(cStr);
end;

(**SetMinSuggestDepth:
 * Change the value of the MinSuggestDepth property.
 *)
procedure TSsceSpellDlg.SetMinSuggestDepth(depth: Integer);
begin
	SSCE_SetMinSuggestDepth(depth);
end;

{$IFDEF WIN32}

(**SetRegTreeName:
 * Set the name of the registry tree used to read and save property values.
 *)
procedure TSsceSpellDlg.SetRegTreeName(treeName: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, treeName);
	SSCE_SetRegTreeName(cStr);
end;

{$ENDIF}

(**SetStringTableName:
 * Set the name of the string table used to read strings displayed by the
 * Sentry built-in dialog boxes.
 *)
procedure TSsceSpellDlg.SetStringTableName(tableName: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, tableName);
	SSCE_SetStringTableName(cStr);
end;

(**SetText:
 * Set the Text property via a PChar.
 *)
procedure TSsceSpellDlg.SetText(aText: PChar);
begin
	if (FText <> nil) then begin
		StrDispose(FText);
	end;
	FText := StrNew(aText);
   DocSource := TextDocSource;
end;

(**SetTextStr:
 * Set the Text property using a Pascal string.
 *)
procedure TSsceSpellDlg.SetTextStr(aStr: String);
begin
	if (FText <> nil) then begin
		StrDispose(FText);
	end;
	FText := StrAlloc(Length(aStr) + 1);
	StrPCopy(FText, aStr);
	DocSource := TextDocSource;
end;

(**SetUserLexFiles:
 * Set the list of user-lexicon files.
 *)
procedure TSsceSpellDlg.SetUserLexFiles(fileList: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, fileList);
	SSCE_SetUserLexFiles(cStr);
end;

(**SetUserLexPath:
 * Set the path to the directory containing user lexicon files.
 *)
procedure TSsceSpellDlg.SetUserLexPath(path: String);
var
	cStr: array[0..255] of Char;
begin
	StrPCopy(cStr, path);
	SSCE_SetUserLexPath(cStr);
end;

procedure Register;
begin
	RegisterComponents('Dialogs', [TSsceSpellDlg]);
end;

end.
