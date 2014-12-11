(* SSCE: Sentry Spelling Checker Engine
 * Copyright (c) 1993 Wintertree Software Inc.
 * www.wintertree-software.com
 *
 * Use, duplication, and disclosure of this file is governed by
 * a license agreement between Wintertree Software Inc. and
 * the licensee.
 *
 * $Id: ssce.pas,v 5.14.10 2000/06/28 17:32:17 wsi Exp wsi $
 *)

unit SSCE;

interface

uses
	WinTypes;

const
	SSCE_MAX_WORD_LEN = 63;
	SSCE_MAX_WORD_SZ = 64;
	SSCE_MAX_SUGGEST_DEPTH = 100;

	{ Error codes. Note that these are always negative. }
	SSCE_TOO_MANY_SESSIONS_ERR = -1;
	SSCE_BAD_SESSION_ID_ERR = -2;
	SSCE_WORD_NOT_FOUND_ERR = -3;
	SSCE_FILE_NOT_FOUND_ERR = -4;
	SSCE_TOO_MANY_LEXICONS_ERR = -5;
	SSCE_UNKNOWN_ACTION_ERR = -6;
	SSCE_BAD_LEXICON_ID_ERR = -7;
	SSCE_BUFFER_TOO_SMALL_ERR = -8;
	SSCE_READ_ONLY_LEXICON_ERR = -9;
	SSCE_OUT_OF_MEMORY_ERR = -12;
	SSCE_UNSUPPORTED_ACTION_ERR = -13;
	SSCE_LEXICON_EXISTS_ERR = -14;
	SSCE_TOO_MANY_BLOCKS_ERR = -15;
	SSCE_BAD_BLOCK_ID_ERR = -16;
	SSCE_CANCEL_ERR  = -17;
	SSCE_INVALID_WORD_ERR = -19;
	SSCE_WORD_OUT_OF_SEQUENCE_ERR = -20;
	SSCE_FILE_READ_ERR = -22;
	SSCE_FILE_WRITE_ERR  = -23;
	SSCE_FILE_OPEN_ERR = -24;
	SSCE_BUSY_ERR = -25;
	SSCE_UNKNOWN_LEX_FORMAT_ERR = -26;

	(* Spell-check result masks. Note that these will always result
	 * in a positive value.
	 *)
	SSCE_OK_RSLT = $0;
	SSCE_MISSPELLED_WORD_RSLT = $1;
	SSCE_AUTO_CHANGE_WORD_RSLT = $2;
	SSCE_CONDITIONALLY_CHANGE_WORD_RSLT = $4;
	SSCE_UNCAPPED_WORD_RSLT = $8;
	SSCE_MIXED_CASE_WORD_RSLT = $10;
	SSCE_MIXED_DIGITS_WORD_RSLT = $20;
	SSCE_END_OF_BLOCK_RSLT = $40;
	SSCE_END_OF_TEXT_RSLT = $40;
	SSCE_DOUBLED_WORD_RSLT = $80;

	{ Spell-check option masks. }
	SSCE_IGNORE_CAPPED_WORD_OPT = $1;
	SSCE_IGNORE_MIXED_CASE_OPT = $2;
	SSCE_IGNORE_MIXED_DIGITS_OPT = $4;
	SSCE_IGNORE_ALL_CAPS_WORD_OPT = $8;
	SSCE_REPORT_UNCAPPED_OPT = $10;
	SSCE_REPORT_MIXED_CASE_OPT = $20;
	SSCE_REPORT_MIXED_DIGITS_OPT = $40;
	SSCE_REPORT_SPELLING_OPT = $80;
	SSCE_REPORT_DOUBLED_WORD_OPT = $100;
	SSCE_CASE_SENSITIVE_OPT = $200;
	SSCE_SPLIT_HYPHENATED_WORDS_OPT = $400;
	SSCE_SPLIT_CONTRACTED_WORDS_OPT = $800;
	SSCE_SPLIT_WORDS_OPT = $1000;
	SSCE_SUGGEST_SPLIT_WORDS_OPT = $2000;
	SSCE_SUGGEST_PHONETIC_OPT = $4000;
	SSCE_SUGGEST_TYPOGRAPHICAL_OPT = $8000;
	SSCE_STRIP_POSSESSIVES_OPT = $10000;
	SSCE_IGNORE_NON_ALPHA_WORD_OPT = $20000;
	SSCE_IGNORE_DOMAIN_NAME_OPT = $40000;
	SSCE_ALLOW_ACCENTED_CAPS_OPT = $80000;
    SSCE_IGNORE_HTML_MARKUPS_OPT = $200000;
	SSCE_LANGUAGE_OPT = $80000002;

	{ Lexicon formats: }
	SSCE_COMPRESSED_LEX_FMT = 0;
	SSCE_TEXT_LEX_FMT = 1;

	{ Actions associated with words in text lexicons. }
	SSCE_AUTO_CHANGE_ACTION = 97; {'a'}
	SSCE_AUTO_CHANGE_PRESERVE_CASE_ACTION = 65; {'A'}
	SSCE_CONDITIONAL_CHANGE_ACTION = 99; {'c'}
	SSCE_CONDITIONAL_CHANGE_PRESERVE_CASE_ACTION = 67; {'C'}
	SSCE_EXCLUDE_ACTION = 101; {'e'}
	SSCE_IGNORE_ACTION = 105; {'i'}

	{ Language ids: }
	SSCE_ANY_LANG = 30840;					{ "xx" }
	SSCE_AMER_ENGLISH_LANG = 24941;			{ "am" }
	SSCE_BRIT_ENGLISH_LANG = 25202;			{ "br" }
	SSCE_CANADIAN_ENGLISH_LANG = 25441;			{ "ca" }
	SSCE_CATALAN_LANG = 29539;				{ "sc" }
	SSCE_CZECH_LANG = 25466;				{ "cz" }
	SSCE_DANISH_LANG = 25697;				{ "da" }
	SSCE_DUTCH_LANG = 25717;				{ "du" }
	SSCE_FINNISH_LANG = 26217;				{ "fi" }
	SSCE_FRENCH_LANG = 26226;				{ "fr" }
	SSCE_GERMAN_LANG = 26469;				{ "ge" }
	SSCE_HUNGARIAN_LANG = 26741;			{ "hu" }
	SSCE_ITALIAN_LANG = 26996;				{ "it" }
	SSCE_NORWEGIAN_BOKMAL_LANG = 25442;		{ "cb" }
	SSCE_NORWEGIAN_NYNORSK_LANG = 25444;	{ "cd" }
	SSCE_POLISH_LANG = 28780;				{ "pl" }
	SSCE_PORTUGUESE_BRAZIL_LANG = 28770;	{ "pb" }
	SSCE_PORTUGUESE_IBERIAN_LANG = 28783;	{ "po" }
	SSCE_RUSSIAN_LANG = 29301;				{ "ru" }
	SSCE_SPANISH_LANG = 29552;				{ "sp" }
	SSCE_SWEDISH_LANG = 29559;				{ "sw" }

	{ Character sets. }
	SSCE_LATIN1_CHARSET = 1;
	SSCE_UNICODE_CHARSET = 2;

{$IFDEF WIN32}
    SSCE_DLL = 'ssce5332.dll';
{$ELSE}
	SSCE_DLL = 'ssce5316';
{$ENDIF}

type
	S8 = Shortint;
	U8 = Byte;
	SSCE_S16 = Smallint;
	SSCE_U16 = Word;
	SSCE_S32 = Longint;
{$IFDEF WIN32}
	SSCE_U32 = Longword;
{$ELSE}
	SSCE_U32 = Longint;		{ no unsigned 32-bit value in 16-bit Delphi }
{$ENDIF}
	SSCE_CHAR = Char;
	SSCE_PCHAR = PChar;
	SSCE_PS16 = ^SSCE_S16;

	{ Functions available in the basic SSCE API: }
	function SSCE_AddToLex(sid, lexId: SSCE_S16; const word: SSCE_PCHAR;
	  action: SSCE_S16; otherWord: SSCE_PCHAR): SSCE_S16;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CheckBlock(sid, blkId: SSCE_S16;
	  errWord: SSCE_PCHAR; errWordSz: SSCE_S16; otherWord: SSCE_PCHAR;
	  otherWordSz: SSCE_S16): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CheckString(sid: SSCE_S16; const str: SSCE_PCHAR;
	  var cursor: SSCE_S32; errWord: SSCE_PCHAR; errWordSz: SSCE_S16;
	  otherWord: SSCE_PCHAR; otherWordSz: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CheckWord(sid: SSCE_S16; word, replWord: SSCE_PCHAR;
	  replWordSz: SSCE_S16): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_ClearLex(sid, lexId: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CloseBlock(sid, blkId: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CloseLex(sid, lexId: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CloseSession(sid: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_CompressLexAbort(sid: SSCE_S16);
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CompressLexEnd(sid: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CompressLexFile(sid: SSCE_S16; fileName: PChar;
	  var errLine: SSCE_U32): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CompressLexInit(sid: SSCE_S16;
	  lexFileName, suffixFileName: PChar; langId: SSCE_S16;
	  var errLine: SSCE_U32): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CreateLex(sid: SSCE_S16; fileName: PChar;
	  lang: SSCE_S16): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_DelBlockText(sid, blkId: SSCE_S16; numChars: SSCE_S32):
	  SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_DelBlockWord(sid, blkId: SSCE_S16; delText: SSCE_PCHAR;
      delTextSz: SSCE_S16): SSCE_S32; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_DelFromLex(sid, lexId: SSCE_S16; word: SSCE_PCHAR): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_DelStringText(sid: SSCE_S16; str: SSCE_PCHAR;
	  cursor, numChars: SSCE_S32): SSCE_S32; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_DelStringWord(sid: SSCE_S16; str: SSCE_PCHAR;
	  cursor: SSCE_S32; delText: SSCE_PCHAR; delTextSz: SSCE_S32): SSCE_S32;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_FindLexWord(sid, lexId: SSCE_S16; word: SSCE_PCHAR;
	  var otherWord: SSCE_PCHAR; otherWordSz: SSCE_S16): SSCE_S16;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetBlock(sid, blkId: SSCE_S16; block: SSCE_PCHAR;
	  blkSz: SSCE_S32): SSCE_S32; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetBlockInfo(sid, blkId: SSCE_S16; var blkLen, blkSz, cursor,
	  wordCount: SSCE_S32): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetBlockWord(sid, blkId: SSCE_S16; word: SSCE_PCHAR;
	  wordSz: SSCE_S16): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetLex(sid, lexId: SSCE_S16; lexBfr: SSCE_PCHAR;
	  lexBfrSz: SSCE_S32): SSCE_S32; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetLexInfo(sid, lexId: Integer; var size: LongInt;
	  var format, lang: Word): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetOption(sid: SSCE_S16; opt: SSCE_U32): SSCE_U32;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetStringWord(sid: SSCE_S16; const str: SSCE_PCHAR;
	  cursor: SSCE_S32; word: SSCE_PCHAR; wordSz: SSCE_S16): SSCE_S32;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_InsertBlockText(sid, blkId: SSCE_S16; text: SSCE_PCHAR):
	  SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_InsertStringText(sid: SSCE_S16; str: SSCE_PCHAR;
	  strSz, cursor: SSCE_S32; const text: SSCE_PCHAR): SSCE_S32;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_NextBlockWord(sid, blkId: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_OpenBlock(sid: SSCE_S16; block: SSCE_PCHAR;
	  blkLen, blkSz: SSCE_S32; copyBlock: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_OpenLex(sid: SSCE_S16; fileName: PChar;
	  memBudget: SSCE_S32): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_OpenSession: SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_ReplaceBlockWord(sid, blkId: SSCE_S16; word: SSCE_PCHAR):
	  SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_ReplaceStringWord(sid: SSCE_S16; str: SSCE_PCHAR;
	  strSz, cursor: SSCE_S32; const word: SSCE_PCHAR): SSCE_S32;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

    function SSCE_SetBlockCursor(sid, blkId: SSCE_S16; cursor: SSCE_S32): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_SetDebugFile(debugFile: PChar);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetOption(sid: SSCE_S16; opt, val: SSCE_U32): SSCE_U32;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_Suggest(sid: SSCE_S16; word: SSCE_PCHAR;
	  depth: SSCE_S16; suggBfr: SSCE_PCHAR; suggBfrSz: SSCE_S32;
	  scores: SSCE_PS16; scoreSz: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_Version(version: PChar; versionSz: SSCE_S16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	{ Functions in the Sentry Windows API: }

	function SSCE_CheckBlockDlg(parent: HWnd; block: SSCE_PCHAR;
	  blkLen, blkSz: SSCE_S32; showContext: SSCE_S16): SSCE_S32;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CheckBlockDlgTmplt(parent: HWnd; block: SSCE_PCHAR;
	  blkLen, blkSz: SSCE_S32; showContext: SSCE_S16; clientInst: THandle;
	  spellDlgTmpltName, lexDlgTmpltName, optDlgTmpltName, newLexDlgName:
	  PChar): SSCE_S32; {$IFDEF WIN32} stdcall; {$ENDIF}

    function SSCE_CheckCtrlBackground(ctrlWin: HWnd): SSCE_S16;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CheckCtrlDlg(parent, ctrlWin: HWnd; selTextOnly: SSCE_S16):
	  SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_CheckCtrlDlgTmplt(parent, ctrlWin: HWnd;
	  selTextOnly: SSCE_S16; clientInst: THandle;
	  spellDlgTmpltName, lexDlgTmpltName, optDlgTmpltName, newLexDlgName:
	  PChar): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_EditLexDlg(parent: HWnd): SSCE_S16;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_EditLexDlgTmplt(parent: HWnd; clientInst: THandle;
	  lexDlgTmpltName, newLexDlgTmpltName: PChar): SSCE_S16;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetAutoCorrect: SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

    procedure SSCE_GetHelpFile(fileName: PChar; fileNameSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetLexId(lexFileName: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_GetMainLexPath(path: PChar; pathSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_GetMainLexFiles(fileList: PChar; fileListSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetMinSuggestDepth: SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

    procedure SSCE_GetRegTreeName(treeName: PChar; treeNameSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

    procedure SSCE_GetSelUserLexFile(fileName: PChar; fileNameSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_GetSid: SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_GetStatistics(var wordsChecked, wordsChanged,
      errorsDetected: SSCE_U32); {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_GetStringTableName(tableName: PChar;
	  tableNameSz: SSCE_S16); {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_GetUserLexFiles(fileList: PChar; fileListSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_GetUserLexPath(path: PChar; pathSz: SSCE_U16);
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_OptionsDlg(parent: HWnd): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_OptionsDlgTmplt(parent: HWnd; clientInst: THandle;
	  optDlgTmpltName: PChar): SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_ResetLex: SSCE_S16; {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetAutoCorrect(autoCorrect: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	procedure SSCE_SetDialogOrigin(x, y: SSCE_S16); {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetHelpFile(fileName: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetIniFile(iniFile: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

    function SSCE_SetKey(key: SSCE_U32): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetMainLexPath(path: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetMainLexFiles(fileList: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetMinSuggestDepth(depth: SSCE_S16): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

    function SSCE_SetRegTreeName(treeName: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

    function SSCE_SetSelUserLexFile(fileName: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetStringTableName(tableName: PChar): SSCE_S16;
	  {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetUserLexFiles(fileList: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

	function SSCE_SetUserLexPath(path: PChar): SSCE_S16;
      {$IFDEF WIN32} stdcall; {$ENDIF}

implementation

	function SSCE_AddToLex; external SSCE_DLL;

	function SSCE_CheckBlock; external SSCE_DLL;

    function SSCE_CheckString; external SSCE_DLL;

	function SSCE_CheckWord; external SSCE_DLL;

	function SSCE_ClearLex; external SSCE_DLL;

	function SSCE_CloseBlock; external SSCE_DLL;

	function SSCE_CloseLex; external SSCE_DLL;

	function SSCE_CloseSession; external SSCE_DLL;

	procedure SSCE_CompressLexAbort; external SSCE_DLL;

	function SSCE_CompressLexEnd; external SSCE_DLL;

	function SSCE_CompressLexFile; external SSCE_DLL;

	function SSCE_CompressLexInit; external SSCE_DLL;

	function SSCE_CreateLex; external SSCE_DLL;

	function SSCE_DelBlockText; external SSCE_DLL;

	function SSCE_DelBlockWord; external SSCE_DLL;

	function SSCE_DelFromLex; external SSCE_DLL;

	function SSCE_DelStringText; external SSCE_DLL;

	function SSCE_DelStringWord; external SSCE_DLL;

	function SSCE_FindLexWord; external SSCE_DLL;

	function SSCE_GetBlock; external SSCE_DLL;

	function SSCE_GetBlockInfo; external SSCE_DLL;

	function SSCE_GetBlockWord; external SSCE_DLL;

	function SSCE_GetLex; external SSCE_DLL;

	function SSCE_GetLexInfo; external SSCE_DLL;

	function SSCE_GetOption; external SSCE_DLL;

	function SSCE_GetStringWord; external SSCE_DLL;

	function SSCE_InsertBlockText; external SSCE_DLL;

	function SSCE_InsertStringText; external SSCE_DLL;

	function SSCE_NextBlockWord; external SSCE_DLL;

	function SSCE_OpenBlock; external SSCE_DLL;

	function SSCE_OpenLex; external SSCE_DLL;

	function SSCE_OpenSession; external SSCE_DLL;

	function SSCE_ReplaceBlockWord; external SSCE_DLL;

	function SSCE_ReplaceStringWord; external SSCE_DLL;

    function SSCE_SetBlockCursor; external SSCE_DLL;

	procedure SSCE_SetDebugFile; external SSCE_DLL;

	function SSCE_SetOption; external SSCE_DLL;

	function SSCE_Suggest; external SSCE_DLL;

	procedure SSCE_Version; external SSCE_DLL;

	function SSCE_CheckBlockDlg; external SSCE_DLL;

	function SSCE_CheckBlockDlgTmplt; external SSCE_DLL;

    function SSCE_CheckCtrlBackground; external SSCE_DLL;

	function SSCE_CheckCtrlDlg; external SSCE_DLL;

	function SSCE_CheckCtrlDlgTmplt; external SSCE_DLL;

	function SSCE_EditLexDlg; external SSCE_DLL;

	function SSCE_EditLexDlgTmplt; external SSCE_DLL;

	function SSCE_GetAutoCorrect; external SSCE_DLL;

    procedure SSCE_GetHelpFile; external SSCE_DLL;

	function SSCE_GetLexId; external SSCE_DLL;

	procedure SSCE_GetMainLexFiles; external SSCE_DLL;

	procedure SSCE_GetMainLexPath; external SSCE_DLL;

	function SSCE_GetMinSuggestDepth; external SSCE_DLL;

    procedure SSCE_GetRegTreeName; external SSCE_DLL;

    procedure SSCE_GetSelUserLexFile; external SSCE_DLL;

	function SSCE_GetSid; external SSCE_DLL;

	procedure SSCE_GetStatistics; external SSCE_DLL;

	procedure SSCE_GetStringTableName; external SSCE_DLL;

	procedure SSCE_GetUserLexFiles; external SSCE_DLL;

	procedure SSCE_GetUserLexPath; external SSCE_DLL;

	function SSCE_OptionsDlg; external SSCE_DLL;

	function SSCE_OptionsDlgTmplt; external SSCE_DLL;

	function SSCE_ResetLex; external SSCE_DLL;

	function SSCE_SetAutoCorrect; external SSCE_DLL;

	procedure SSCE_SetDialogOrigin; external SSCE_DLL;

    function SSCE_SetHelpFile; external SSCE_DLL;

	function SSCE_SetIniFile; external SSCE_DLL;

    function SSCE_SetKey; external SSCE_DLL;

	function SSCE_SetMainLexFiles; external SSCE_DLL;

	function SSCE_SetMainLexPath; external SSCE_DLL;

	function SSCE_SetMinSuggestDepth; external SSCE_DLL;

    function SSCE_SetRegTreeName; external SSCE_DLL;

    function SSCE_SetSelUserLexFile; external SSCE_DLL;

	function SSCE_SetStringTableName; external SSCE_DLL;

	function SSCE_SetUserLexFiles; external SSCE_DLL;

	function SSCE_SetUserLexPath; external SSCE_DLL;

end.
