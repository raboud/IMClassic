Attribute VB_Name = "SSCE"
' SSCE: Sentry Spelling Checker Engine
' Copyright (c) 1994 Wintertree Software Inc.
' www.wintertree-software.com
'
' Use, duplication, and disclosure of this file is governed by
' a license agreement between Wintertree Software Inc. and
' the licensee.
'
' $Id: ssce.bas,v 5.14.10 2000/06/28 17:33:00 wsi Exp wsi $

Global Const SSCE_MAX_WORD_LEN = 63
Global Const SSCE_MAX_WORD_SZ = (SSCE_MAX_WORD_LEN + 1)
Global Const SSCE_MAX_SUGGEST_DEPTH = 100

' Error codes. Note that these are always negative.
Global Const SSCE_TOO_MANY_SESSIONS_ERR = (-1)
Global Const SSCE_BAD_SESSION_ID_ERR = (-2)
Global Const SSCE_WORD_NOT_FOUND_ERR = (-3)
Global Const SSCE_FILE_NOT_FOUND_ERR = (-4)
Global Const SSCE_TOO_MANY_LEXICONS_ERR = (-5)
Global Const SSCE_UNKNOWN_ACTION_ERR = (-6)
Global Const SSCE_BAD_LEXICON_ID_ERR = (-7)
Global Const SSCE_BUFFER_TOO_SMALL_ERR = (-8)
Global Const SSCE_READ_ONLY_LEXICON_ERR = (-9)
Global Const SSCE_OUT_OF_MEMORY_ERR = (-12)
Global Const SSCE_UNSUPPORTED_ACTION_ERR = (-13)
Global Const SSCE_LEXICON_EXISTS_ERR = (-14)
Global Const SSCE_TOO_MANY_BLOCKS_ERR = (-15)
Global Const SSCE_BAD_BLOCK_ID_ERR = (-16)
Global Const SSCE_CANCEL_ERR = (-17)
Global Const SSCE_INVALID_WORD_ERR = (-19)
Global Const SSCE_WORD_OUT_OF_SEQUENCE_ERR = (-20)
Global Const SSCE_FILE_READ_ERR = (-22)
Global Const SSCE_FILE_WRITE_ERR = (-23)
Global Const SSCE_FILE_OPEN_ERR = (-24)
Global Const SSCE_BUSY_ERR = (-25)
Global Const SSCE_UNKNOWN_LEX_FORMAT_ERR = (-26)

' Spell-check result masks. Note that these will always result in a
' positive value.
Global Const SSCE_OK_RSLT = &H0
Global Const SSCE_MISSPELLED_WORD_RSLT = &H1
Global Const SSCE_AUTO_CHANGE_WORD_RSLT = &H2
Global Const SSCE_CONDITIONALLY_CHANGE_WORD_RSLT = &H4
Global Const SSCE_UNCAPPED_WORD_RSLT = &H8
Global Const SSCE_MIXED_CASE_WORD_RSLT = &H10
Global Const SSCE_MIXED_DIGITS_WORD_RSLT = &H20
Global Const SSCE_END_OF_BLOCK_RSLT = &H40
Global Const SSCE_END_OF_TEXT_RSLT = SSCE_END_OF_BLOCK_RSLT
Global Const SSCE_DOUBLED_WORD_RSLT = &H80

' Options.
Global Const SSCE_IGNORE_CAPPED_WORD_OPT = &H1&
Global Const SSCE_IGNORE_MIXED_CASE_OPT = &H2&
Global Const SSCE_IGNORE_MIXED_DIGITS_OPT = &H4&
Global Const SSCE_IGNORE_ALL_CAPS_WORD_OPT = &H8&
Global Const SSCE_REPORT_UNCAPPED_OPT = &H10&
Global Const SSCE_REPORT_MIXED_CASE_OPT = &H20&
Global Const SSCE_REPORT_MIXED_DIGITS_OPT = &H40&
Global Const SSCE_REPORT_SPELLING_OPT = &H80&
Global Const SSCE_REPORT_DOUBLED_WORD_OPT = &H100&
Global Const SSCE_CASE_SENSITIVE_OPT = &H200&
Global Const SSCE_SPLIT_HYPHENATED_WORDS_OPT = &H400&
Global Const SSCE_SPLIT_CONTRACTED_WORDS_OPT = &H800&
Global Const SSCE_SPLIT_WORDS_OPT = &H1000&
Global Const SSCE_SUGGEST_SPLIT_WORDS_OPT = &H2000&
Global Const SSCE_SUGGEST_PHONETIC_OPT = &H4000&
Global Const SSCE_SUGGEST_TYPOGRAPHICAL_OPT = &H8000&
Global Const SSCE_STRIP_POSSESSIVES_OPT = &H10000
Global Const SSCE_IGNORE_NON_ALPHA_WORD_OPT = &H20000
Global Const SSCE_IGNORE_DOMAIN_NAME_OPT = &H40000
Global Const SSCE_ALLOW_ACCENTED_CAPS_OPT = &H80000
Global Const SSCE_IGNORE_HTML_MARKUPS_OPT = &H200000
Global Const SSCE_LANGUAGE_OPT = &H80000002

' Lexicon formats:
Global Const SSCE_COMPRESSED_LEX_FMT = 0
Global Const SSCE_TEXT_LEX_FMT = 1

' Actions associated with words in text lexicons.
Global Const SSCE_AUTO_CHANGE_ACTION = 97               ' "a"
Global Const SSCE_AUTO_CHANGE_PRESERVE_CASE_ACTION = 65 ' "A"
Global Const SSCE_CONDITIONAL_CHANGE_ACTION = 99        ' "c"
Global Const SSCE_CONDITIONAL_CHANGE_PRESERVE_CASE_ACTION = 67 ' "C"
Global Const SSCE_EXCLUDE_ACTION = 101                  ' "e"
Global Const SSCE_IGNORE_ACTION = 105                   ' "i"

' Language ids:
Global Const SSCE_ANY_LANG = 30840                      ' "xx"
Global Const SSCE_AMER_ENGLISH_LANG = 24941             ' "am"
Global Const SSCE_BRIT_ENGLISH_LANG = 25202             ' "br"
Global Const SSCE_CANADIAN_ENGLISH_LANG = 25441         ' "ca"
Global Const SSCE_CATALAN_LANG = 29539                  ' "sc"
Global Const SSCE_CZECH_LANG = 25466                    ' "cz"
Global Const SSCE_DANISH_LANG = 25697                   ' "da"
Global Const SSCE_DUTCH_LANG = 25717                    ' "du"
Global Const SSCE_FINNISH_LANG = 26217                  ' "fi"
Global Const SSCE_FRENCH_LANG = 26226                   ' "fr"
Global Const SSCE_GERMAN_LANG = 26469                   ' "ge"
Global Const SSCE_HUNGARIAN_LANG = 26741                ' "hu"
Global Const SSCE_ITALIAN_LANG = 26996                  ' "it"
Global Const SSCE_NORWEGIAN_BOKMAL_LANG = 25442         ' "cb"
Global Const SSCE_NORWEGIAN_NYNORSK_LANG = 25444        ' "cd"
Global Const SSCE_POLISH_LANG = 28780                   ' "pl"
Global Const SSCE_PORTUGUESE_BRAZIL_LANG = 28770        ' "pb"
Global Const SSCE_PORTUGUESE_IBERIAN_LANG = 28783       ' "po"
Global Const SSCE_RUSSIAN_LANG = 29301                  ' "ru"
Global Const SSCE_SPANISH_LANG = 29552                  ' "sp"
Global Const SSCE_SWEDISH_LANG = 29559                  ' "sw"

' Character sets.
Global Const SSCE_LATIN1_CHARSET = 1
Global Const SSCE_UNICODE_CHARSET = 2

' Functions in the basic SSCE API

#If Win32 Then

Declare Function SSCE_AddToLex Lib "ssce5332.dll" (ByVal sid%, ByVal lexId%, _
  ByVal word$, ByVal action%, ByVal otherWord$) As Integer

Declare Function SSCE_CheckBlock Lib "ssce5332.dll" (ByVal sid%, _
  ByVal blkId%, ByVal errWord$, ByVal errWordSz%, ByVal otherWord$, _
  ByVal otherWordSz%) As Integer

Declare Function SSCE_CheckString Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$, cursor&, ByVal errWord$, ByVal errWordSz%, _
  ByVal otherWord$, ByVal otherWordSz%) As Integer

Declare Function SSCE_CheckWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal word$, ByVal otherWord$, ByVal otherWordSz%) As Integer

Declare Function SSCE_ClearLex Lib "ssce5332.dll" (ByVal sid%, ByVal lexId%) _
  As Integer

Declare Function SSCE_CloseBlock Lib "ssce5332.dll" (ByVal sid%, ByVal blkId%) _
  As Integer

Declare Function SSCE_CloseLex Lib "ssce5332.dll" (ByVal sid%, ByVal lexId%) _
  As Integer

Declare Function SSCE_CloseSession Lib "ssce5332.dll" (ByVal sid%) As Integer

Declare Sub SSCE_CompressLexAbort Lib "ssce5332.dll" (ByVal sid%)

Declare Function SSCE_CompressLexEnd Lib "ssce5332.dll" (ByVal sid%) As Integer

Declare Function SSCE_CompressLexFile Lib "ssce5332.dll" (ByVal sid%, _
  ByVal fileName$, errLine&) As Integer
  
Declare Function SSCE_CompressLexInit Lib "ssce5332.dll" (ByVal sid%, _
  ByVal lexFileName$, ByVal suffixFileName, ByVal langId%, errLine&) As Integer
  
Declare Function SSCE_CountStringWords Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$) As Long

Declare Function SSCE_CreateLex Lib "ssce5332.dll" (ByVal sid%, _
  ByVal fileName$, ByVal lang%) As Integer

Declare Function SSCE_DelBlockText Lib "ssce5332.dll" (ByVal sid%, _
  ByVal blkId%, ByVal numChars&) As Integer

Declare Function SSCE_DelBlockWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal blkId%, ByVal delText$, ByVal delTextSz%) As Long

Declare Function SSCE_DelFromLex Lib "ssce5332.dll" (ByVal sid%, ByVal lexId%, _
  ByVal word$) As Integer

Declare Function SSCE_DelStringText Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$, ByVal cursor&, ByVal numChars&) As Long

Declare Function SSCE_DelStringWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$, ByVal cursor&, ByVal delText$, ByVal delTextSz&) As Long

Declare Function SSCE_FindLexWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal lexId%, ByVal word$, ByVal otherWord$, ByVal otherWordSz%) As Integer

Declare Function SSCE_GetBlock Lib "ssce5332.dll" (ByVal sid%, ByVal blkId%, _
  ByVal block$, ByVal blkSz&) As Long

Declare Function SSCE_GetBlockInfo Lib "ssce5332.dll" (ByVal sid%, ByVal blkId%, _
  blkLen&, blkSz&, curPos&, wordCount&) As Integer

Declare Function SSCE_GetBlockWord Lib "ssce5332.dll" (ByVal sid%, ByVal blkId%, _
  ByVal word$, ByVal wordSz%) As Integer

Declare Function SSCE_GetLex Lib "ssce5332.dll" (ByVal sid%, ByVal lexId%, _
  ByVal lexBfr$, ByVal lexBfrSz&) As Long

Declare Function SSCE_GetLexInfo Lib "ssce5332.dll" (ByVal sid%, ByVal lexId%, _
  lexSz&, lexFormat%, lang%) As Integer

Declare Function SSCE_GetOption Lib "ssce5332.dll" (ByVal sid%, ByVal opt&) As Long

Declare Function SSCE_GetStringWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$, ByVal cursor&, ByVal word$, ByVal wordSz%) As Long

Declare Function SSCE_InsertBlockText Lib "ssce5332.dll" (ByVal sid%, ByVal blkId%, _
  ByVal text$) As Integer

Declare Function SSCE_InsertStringText Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$, ByVal strSz&, ByVal cursor&, ByVal text$) As Long

Declare Function SSCE_NextBlockWord Lib "ssce5332.dll" (ByVal sid%, ByVal blkId%) As _
  Integer

Declare Function SSCE_OpenBlock Lib "ssce5332.dll" (ByVal sid%, ByVal block$, _
  ByVal blkLen&, ByVal blkSz&, ByVal copyBlock%) As Integer

Declare Function SSCE_OpenLex Lib "ssce5332.dll" (ByVal sid%, ByVal fileName$, _
  ByVal memBudget&) As Integer

Declare Function SSCE_OpenSession Lib "ssce5332.dll" () As Integer

Declare Function SSCE_ReplaceBlockWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal blkId%, ByVal word$) As Integer

Declare Function SSCE_ReplaceStringWord Lib "ssce5332.dll" (ByVal sid%, _
  ByVal str$, ByVal strSz&, ByVal cursor&, ByVal word$) As Long

Declare Function SSCE_SetBlockCursor Lib "ssce5332.dll" (ByVal sid%, _
  ByVal blkId%, ByVal cursor&) As Integer

Declare Sub SSCE_SetDebugFile Lib "ssce5332.dll" (ByVal debugFile$)

Declare Function SSCE_SetOption Lib "ssce5332.dll" (ByVal sid%, ByVal opt&, _
  ByVal optVal&) As Long
  
Declare Function SSCE_Suggest Lib "ssce5332.dll" (ByVal sid%, ByVal word$, _
  ByVal depth%, ByVal suggBfr$, ByVal suggBfrSz&, scores%, ByVal nScores%) As Integer

Declare Sub SSCE_Version Lib "ssce5332.dll" (ByVal version$, ByVal versionSz%)

' Functions in the Windows API:

Declare Function SSCE_CheckBlockDlg Lib "ssce5332.dll" (ByVal parent&, _
  ByVal block$, ByVal blkLen&, ByVal blkSz&, ByVal showContext%) As Long

Declare Function SSCE_CheckBlockDlgTmplt Lib "ssce5332.dll" (ByVal parent&, _
  ByVal block$, ByVal blkLen&, ByVal blkSz&, ByVal showContext%, _
  ByVal clientInst&, ByVal spellDlgTmplt$, ByVal dictDlgTmplt$, _
  ByVal optDlgTmplt$, ByVal newLexDlgTmplt$) As Long

Declare Function SSCE_CheckCtrlBackground Lib "ssce5332.dll" (ByVal ctrlWin&) _
  As Integer

Declare Function SSCE_CheckCtrlDlg Lib "ssce5332.dll" (ByVal parent&, _
  ByVal ctrlWin&, ByVal selTextOnly%) As Integer

Declare Function SSCE_CheckCtrlDlgTmplt Lib "ssce5332.dll" (ByVal parent&, _
  ByVal ctrlWin&, ByVal selTextOnly%, ByVal clientInst&, ByVal spellDlgTmplt$, _
  ByVal dictDlgTmplt$, ByVal optDlgTmplt$, ByVal newLexDlgTmplt$) As Integer

Declare Function SSCE_EditLexDlg Lib "ssce5332.dll" (ByVal parent&) As Integer

Declare Function SSCE_EditLexDlgTmplt Lib "ssce5332.dll" (ByVal parent&, _
  ByVal clientInst&, ByVal dictDlgTmplt$, ByVal newLexDlgTmplt$) As Integer

Declare Function SSCE_GetAutoCorrect Lib "ssce5332.dll" () As Integer

Declare Sub SSCE_GetHelpFile Lib "ssce5332.dll" (ByVal fileName$, _
  ByVal fileNameSz%)

Declare Function SSCE_GetLexId Lib "ssce5332.dll" (ByVal lexFileName$) As _
  Integer

Declare Sub SSCE_GetMainLexFiles Lib "ssce5332.dll" (ByVal fileList$, ByVal fileListSz%)

Declare Sub SSCE_GetMainLexPath Lib "ssce5332.dll" (ByVal path$, _
  ByVal pathSz%)

Declare Function SSCE_GetMinSuggestDepth Lib "ssce5332.dll" () As Integer

Declare Sub SSCE_GetRegTreeName Lib "ssce5332.dll" (ByVal regTreeName$, _
  ByVal regTreeNameSz%)

Declare Sub SSCE_GetSelUserLexFile Lib "ssce5332.dll" (ByVal fileName$, ByVal fileNameSz%)

Declare Function SSCE_GetSid Lib "ssce5332.dll" () As Integer

Declare Sub SSCE_GetStatistics Lib "ssce5332.dll" (wordsChecked&, wordsChanged&, errorsDetected&)

Declare Sub SSCE_GetStringTableName Lib "ssce5332.dll" (ByVal tableName$, _
  ByVal tableNameSz%)

Declare Sub SSCE_GetUserLexFiles Lib "ssce5332.dll" (ByVal fileList$, _
  ByVal fileListSz%)

Declare Sub SSCE_GetUserLexPath Lib "ssce5332.dll" (ByVal path$, ByVal pathSz%)

Declare Function SSCE_OptionsDlg Lib "ssce5332.dll" (ByVal parent&) As Integer

Declare Function SSCE_OptionsDlgTmplt Lib "ssce5332.dll" (ByVal parent&, _
  ByVal clientInst&, ByVal optDlgTmplt$) As Integer

Declare Function SSCE_ResetLex Lib "ssce5332.dll" () As Integer

Declare Function SSCE_SetAutoCorrect Lib "ssce5332.dll" (ByVal ac%) As Integer

Declare Sub SSCE_SetDialogOrigin Lib "ssce5332.dll" (ByVal x%, ByVal y%)

Declare Function SSCE_SetHelpFile Lib "ssce5332.dll" (ByVal helpFile$) As _
  Integer

Declare Function SSCE_SetIniFile Lib "ssce5332.dll" (ByVal iniFile$) As Integer

Declare Function SSCE_SetKey Lib "ssce5332.dll" (ByVal key&) As Integer

Declare Function SSCE_SetMainLexFiles Lib "ssce5332.dll" (ByVal fileList$) As _
  Integer

Declare Function SSCE_SetMainLexPath Lib "ssce5332.dll" (ByVal path$) As _
  Integer

Declare Function SSCE_SetMinSuggestDepth Lib "ssce5332.dll" (ByVal depth%) As _
  Integer

Declare Function SSCE_SetRegTreeName Lib "ssce5332.dll" (ByVal regTreeName$) _
  As Integer

Declare Function SSCE_SetSelUserLexFile Lib "ssce5332.dll" (ByVal fileName$) As Integer

Declare Function SSCE_SetStringTableName Lib "ssce5332.dll" (ByVal tableName$) _
  As Integer

Declare Function SSCE_SetUserLexFiles Lib "ssce5332.dll" (ByVal fileList$) As _
  Integer

Declare Function SSCE_SetUserLexPath Lib "ssce5332.dll" (ByVal path$) As _
Integer

#Else

' Win16 declarations:

Declare Function SSCE_AddToLex Lib "ssce5316.dll" (ByVal sid%, ByVal lexId%, _
  ByVal word$, ByVal action%, ByVal otherWord$) As Integer

Declare Function SSCE_CheckBlock Lib "ssce5316.dll" (ByVal sid%, _
  ByVal blkId%, ByVal errWord$, ByVal errWordSz%, ByVal otherWord$, _
  ByVal otherWordSz%) As Integer

Declare Function SSCE_CheckString Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$, cursor&, ByVal errWord$, ByVal errWordSz%, _
  ByVal otherWord$, ByVal otherWordSz%) As Integer

Declare Function SSCE_CheckWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal word$, ByVal otherWord$, ByVal otherWordSz%) As Integer

Declare Function SSCE_ClearLex Lib "ssce5316.dll" (ByVal sid%, ByVal lexId%) _
  As Integer

Declare Function SSCE_CloseBlock Lib "ssce5316.dll" (ByVal sid%, ByVal blkId%) _
  As Integer

Declare Function SSCE_CloseLex Lib "ssce5316.dll" (ByVal sid%, ByVal lexId%) _
  As Integer

Declare Function SSCE_CloseSession Lib "ssce5316.dll" (ByVal sid%) As Integer

Declare Sub SSCE_CompressLexAbort Lib "ssce5316.dll" (ByVal sid%)

Declare Function SSCE_CompressLexEnd Lib "ssce5316.dll" (ByVal sid%) As Integer

Declare Function SSCE_CompressLexFile Lib "ssce5316.dll" (ByVal sid%, _
  ByVal fileName$, errLine&) As Integer
  
Declare Function SSCE_CompressLexInit Lib "ssce5316.dll" (ByVal sid%, _
  ByVal lexFileName$, ByVal suffixFileName, ByVal langId%, errLine&) As Integer

Declare Function SSCE_CountStringWords Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$) As Long

Declare Function SSCE_CreateLex Lib "ssce5316.dll" (ByVal sid%, _
  ByVal fileName$, ByVal lang%) As Integer

Declare Function SSCE_DelBlockText Lib "ssce5316.dll" (ByVal sid%, _
  ByVal blkId%, ByVal numChars&) As Integer

Declare Function SSCE_DelBlockWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal blkId%, ByVal delText$, ByVal delTextSz%) As Long

Declare Function SSCE_DelFromLex Lib "ssce5316.dll" (ByVal sid%, ByVal lexId%, _
  ByVal word$) As Integer

Declare Function SSCE_DelStringText Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$, ByVal cursor&, ByVal numChars&) As Long

Declare Function SSCE_DelStringWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$, ByVal cursor&, ByVal delText$, ByVal delTextSz&) As Long

Declare Function SSCE_FindLexWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal lexId%, ByVal word$, ByVal otherWord$, ByVal otherWordSz%) As Integer

Declare Function SSCE_GetBlock Lib "ssce5316.dll" (ByVal sid%, ByVal blkId%, _
  ByVal block$, ByVal blkSz&) As Long

Declare Function SSCE_GetBlockInfo Lib "ssce5316.dll" (ByVal sid%, ByVal blkId%, _
  blkLen&, blkSz&, curPos&, wordCount&) As Integer

Declare Function SSCE_GetBlockWord Lib "ssce5316.dll" (ByVal sid%, ByVal blkId%, _
  ByVal word$, ByVal wordSz%) As Integer

Declare Function SSCE_GetLex Lib "ssce5316.dll" (ByVal sid%, ByVal lexId%, _
  ByVal lexBfr$, ByVal lexBfrSz&) As Long

Declare Function SSCE_GetLexInfo Lib "ssce5316.dll" (ByVal sid%, ByVal lexId%, _
  lexSz&, lexFormat%, lang%) As Integer

Declare Function SSCE_GetOption Lib "ssce5316.dll" (ByVal sid%, ByVal opt&) As Long

Declare Function SSCE_GetStringWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$, ByVal cursor&, ByVal word$, ByVal wordSz%) As Long

Declare Function SSCE_InsertBlockText Lib "ssce5316.dll" (ByVal sid%, ByVal blkId%, _
  ByVal text$) As Integer

Declare Function SSCE_InsertStringText Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$, ByVal strSz&, ByVal cursor&, ByVal text$) As Long

Declare Function SSCE_NextBlockWord Lib "ssce5316.dll" (ByVal sid%, ByVal blkId%) As _
  Integer

Declare Function SSCE_OpenBlock Lib "ssce5316.dll" (ByVal sid%, ByVal block$, _
  ByVal blkLen&, ByVal blkSz&, ByVal copyBlock%) As Integer

Declare Function SSCE_OpenLex Lib "ssce5316.dll" (ByVal sid%, ByVal fileName$, _
  ByVal memBudget&) As Integer

Declare Function SSCE_OpenSession Lib "ssce5316.dll" () As Integer

Declare Function SSCE_ReplaceBlockWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal blkId%, ByVal word$) As Integer

Declare Function SSCE_ReplaceStringWord Lib "ssce5316.dll" (ByVal sid%, _
  ByVal str$, ByVal strSz&, ByVal cursor&, ByVal word$) As Long

Declare Function SSCE_SetBlockCursor Lib "ssce5316.dll" (ByVal sid%, _
  ByVal blkId%, ByVal cursor&) As Integer

Declare Sub SSCE_SetDebugFile Lib "ssce5316.dll" (ByVal debugFile$)

Declare Function SSCE_SetOption Lib "ssce5316.dll" (ByVal sid%, ByVal opt&, _
  ByVal optVal&) As Long
  
Declare Function SSCE_Suggest Lib "ssce5316.dll" (ByVal sid%, ByVal word$, _
  ByVal depth%, ByVal suggBfr$, ByVal suggBfrSz&, scores%, ByVal nScores%) As Integer

Declare Sub SSCE_Version Lib "ssce5316.dll" (ByVal version$, ByVal versionSz%)

' Functions in the Windows API:

Declare Function SSCE_CheckBlockDlg Lib "ssce5316.dll" (ByVal parent%, _
  ByVal block$, ByVal blkLen&, ByVal blkSz&, ByVal showContext%) As Long

Declare Function SSCE_CheckBlockDlgTmplt Lib "ssce5316.dll" (ByVal parent%, _
  ByVal block$, ByVal blkLen&, ByVal blkSz&, ByVal showContext%, _
  ByVal clientInst%, ByVal spellDlgTmplt$, ByVal dictDlgTmplt$, _
  ByVal optDlgTmplt$, ByVal newLexDlgTmplt$) As Long

Declare Function SSCE_CheckCtrlDlg Lib "ssce5316.dll" (ByVal parent%, _
  ByVal ctrlWin%, ByVal selTextOnly%) As Integer

Declare Function SSCE_CheckCtrlDlgTmplt Lib "ssce5316.dll" (ByVal parent%, _
  ByVal ctrlWin%, ByVal selTextOnly%, ByVal clientInst%, ByVal spellDlgTmplt$, _
  ByVal dictDlgTmplt$, ByVal optDlgTmplt$, ByVal newLexDlgTmplt$) As Integer

Declare Function SSCE_EditLexDlg Lib "ssce5316.dll" (ByVal parent%) As Integer

Declare Function SSCE_EditLexDlgTmplt Lib "ssce5316.dll" (ByVal parent%, _
  ByVal clientInst%, ByVal dictDlgTmplt$, ByVal newLexDlgTmplt$) As Integer

Declare Function SSCE_GetAutoCorrect Lib "ssce5316.dll" () As Integer

Declare Sub SSCE_GetHelpFile Lib "ssce5316.dll" (ByVal fileName$, _
  ByVal fileNameSz%)

Declare Function SSCE_GetLexId Lib "ssce5316.dll" (ByVal lexFileName$) As _
  Integer

Declare Sub SSCE_GetMainLexFiles Lib "ssce5316.dll" (ByVal fileList$, ByVal fileListSz%)

Declare Sub SSCE_GetMainLexPath Lib "ssce5316.dll" (ByVal path$, _
  ByVal pathSz%)

Declare Function SSCE_GetMinSuggestDepth Lib "ssce5316.dll" () As Integer

Declare Sub SSCE_GetRegTreeName Lib "ssce5316.dll" (ByVal regTreeName$, _
  ByVal regTreeNameSz%)

Declare Sub SSCE_GetSelUserLexFile Lib "ssce5316.dll" (ByVal fileName$, ByVal fileNameSz%)

Declare Function SSCE_GetSid Lib "ssce5316.dll" () As Integer

Declare Sub SSCE_GetStatistics Lib "ssce5316.dll" (wordsChecked&, wordsChanged&, errorsDetected&)

Declare Sub SSCE_GetStringTableName Lib "ssce5316.dll" (ByVal tableName$, _
  ByVal tableNameSz%)

Declare Sub SSCE_GetUserLexFiles Lib "ssce5316.dll" (ByVal fileList$, _
  ByVal fileListSz%)

Declare Sub SSCE_GetUserLexPath Lib "ssce5316.dll" (ByVal path$, ByVal pathSz%)

Declare Function SSCE_OptionsDlg Lib "ssce5316.dll" (ByVal parent%) As Integer

Declare Function SSCE_OptionsDlgTmplt Lib "ssce5316.dll" (ByVal parent%, _
  ByVal clientInst%, ByVal optDlgTmplt$) As Integer

Declare Function SSCE_ResetLex Lib "ssce5316.dll" () As Integer

Declare Function SSCE_SetAutoCorrect Lib "ssce5316.dll" (ByVal ac%) As Integer

Declare Sub SSCE_SetDialogOrigin Lib "ssce5316.dll" (ByVal x%, ByVal y%)

Declare Function SSCE_SetHelpFile Lib "ssce5316.dll" (ByVal helpFile$) As _
  Integer

Declare Function SSCE_SetIniFile Lib "ssce5316.dll" (ByVal iniFile$) As Integer

Declare Function SSCE_SetKey Lib "ssce5316.dll" (ByVal key&) As Integer

Declare Function SSCE_SetMainLexFiles Lib "ssce5316.dll" (ByVal fileList$) As _
  Integer

Declare Function SSCE_SetMainLexPath Lib "ssce5316.dll" (ByVal path$) As _
  Integer

Declare Function SSCE_SetMinSuggestDepth Lib "ssce5316.dll" (ByVal depth%) As _
  Integer

Declare Function SSCE_SetRegTreeName Lib "ssce5316.dll" (ByVal regTreeName$) _
  As Integer

Declare Function SSCE_SetSelUserLexFile Lib "ssce5316.dll" (ByVal fileName$) As Integer

Declare Function SSCE_SetStringTableName Lib "ssce5316.dll" (ByVal tableName$) _
  As Integer

Declare Function SSCE_SetUserLexFiles Lib "ssce5316.dll" (ByVal fileList$) As _
  Integer

Declare Function SSCE_SetUserLexPath Lib "ssce5316.dll" (ByVal path$) As _
Integer

#End If
