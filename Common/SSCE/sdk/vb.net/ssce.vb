Module ssce
    ' SSCE: Sentry Spelling Checker Engine
    ' VB.NET Interface
    ' Copyright (c) 1994-2002 Wintertree Software Inc.
    ' www.wintertree-software.com
    '
    ' Use, duplication, and disclosure of this file is governed by
    ' a license agreement between Wintertree Software Inc. and
    ' the licensee.
    '
    ' $Id: ssce.vb,v 5.14.12 2002/06/28 17:33:00 wsi Exp wsi $

    Public Const SSCE_MAX_WORD_LEN = 63
    Public Const SSCE_MAX_WORD_SZ = (SSCE_MAX_WORD_LEN + 1)
    Public Const SSCE_MAX_SUGGEST_DEPTH = 100

    ' Error codes. Note that these are always negative.
    Public Const SSCE_TOO_MANY_SESSIONS_ERR = (-1)
    Public Const SSCE_BAD_SESSION_ID_ERR = (-2)
    Public Const SSCE_WORD_NOT_FOUND_ERR = (-3)
    Public Const SSCE_FILE_NOT_FOUND_ERR = (-4)
    Public Const SSCE_TOO_MANY_LEXICONS_ERR = (-5)
    Public Const SSCE_UNKNOWN_ACTION_ERR = (-6)
    Public Const SSCE_BAD_LEXICON_ID_ERR = (-7)
    Public Const SSCE_BUFFER_TOO_SMALL_ERR = (-8)
    Public Const SSCE_READ_ONLY_LEXICON_ERR = (-9)
    Public Const SSCE_OUT_OF_MEMORY_ERR = (-12)
    Public Const SSCE_UNSUPPORTED_ACTION_ERR = (-13)
    Public Const SSCE_LEXICON_EXISTS_ERR = (-14)
    Public Const SSCE_TOO_MANY_BLOCKS_ERR = (-15)
    Public Const SSCE_BAD_BLOCK_ID_ERR = (-16)
    Public Const SSCE_CANCEL_ERR = (-17)
    Public Const SSCE_INVALID_WORD_ERR = (-19)
    Public Const SSCE_WORD_OUT_OF_SEQUENCE_ERR = (-20)
    Public Const SSCE_FILE_READ_ERR = (-22)
    Public Const SSCE_FILE_WRITE_ERR = (-23)
    Public Const SSCE_FILE_OPEN_ERR = (-24)
    Public Const SSCE_BUSY_ERR = (-25)
    Public Const SSCE_UNKNOWN_LEX_FORMAT_ERR = (-26)

    ' Spell-check result masks. Note that these will always result in a
    ' positive value.
    Public Const SSCE_OK_RSLT = &H0
    Public Const SSCE_MISSPELLED_WORD_RSLT = &H1
    Public Const SSCE_AUTO_CHANGE_WORD_RSLT = &H2
    Public Const SSCE_CONDITIONALLY_CHANGE_WORD_RSLT = &H4
    Public Const SSCE_UNCAPPED_WORD_RSLT = &H8
    Public Const SSCE_MIXED_CASE_WORD_RSLT = &H10
    Public Const SSCE_MIXED_DIGITS_WORD_RSLT = &H20
    Public Const SSCE_END_OF_BLOCK_RSLT = &H40
    Public Const SSCE_END_OF_TEXT_RSLT = SSCE_END_OF_BLOCK_RSLT
    Public Const SSCE_DOUBLED_WORD_RSLT = &H80

    ' Options.
    Public Const SSCE_IGNORE_CAPPED_WORD_OPT = &H1&
    Public Const SSCE_IGNORE_MIXED_CASE_OPT = &H2&
    Public Const SSCE_IGNORE_MIXED_DIGITS_OPT = &H4&
    Public Const SSCE_IGNORE_ALL_CAPS_WORD_OPT = &H8&
    Public Const SSCE_REPORT_UNCAPPED_OPT = &H10&
    Public Const SSCE_REPORT_MIXED_CASE_OPT = &H20&
    Public Const SSCE_REPORT_MIXED_DIGITS_OPT = &H40&
    Public Const SSCE_REPORT_SPELLING_OPT = &H80&
    Public Const SSCE_REPORT_DOUBLED_WORD_OPT = &H100&
    Public Const SSCE_CASE_SENSITIVE_OPT = &H200&
    Public Const SSCE_SPLIT_HYPHENATED_WORDS_OPT = &H400&
    Public Const SSCE_SPLIT_CONTRACTED_WORDS_OPT = &H800&
    Public Const SSCE_SPLIT_WORDS_OPT = &H1000&
    Public Const SSCE_SUGGEST_SPLIT_WORDS_OPT = &H2000&
    Public Const SSCE_SUGGEST_PHONETIC_OPT = &H4000&
    Public Const SSCE_SUGGEST_TYPOGRAPHICAL_OPT = &H8000&
    Public Const SSCE_STRIP_POSSESSIVES_OPT = &H10000
    Public Const SSCE_IGNORE_NON_ALPHA_WORD_OPT = &H20000
    Public Const SSCE_IGNORE_DOMAIN_NAME_OPT = &H40000
    Public Const SSCE_ALLOW_ACCENTED_CAPS_OPT = &H80000
    Public Const SSCE_IGNORE_HTML_MARKUPS_OPT = &H200000
    Public Const SSCE_LANGUAGE_OPT = &H80000002

    ' Lexicon formats:
    Public Const SSCE_COMPRESSED_LEX_FMT = 0
    Public Const SSCE_TEXT_LEX_FMT = 1

    ' Actions associated with words in text lexicons.
    Public Const SSCE_AUTO_CHANGE_ACTION = 97               ' "a"
    Public Const SSCE_AUTO_CHANGE_PRESERVE_CASE_ACTION = 65 ' "A"
    Public Const SSCE_CONDITIONAL_CHANGE_ACTION = 99        ' "c"
    Public Const SSCE_CONDITIONAL_CHANGE_PRESERVE_CASE_ACTION = 67 ' "C"
    Public Const SSCE_EXCLUDE_ACTION = 101                  ' "e"
    Public Const SSCE_IGNORE_ACTION = 105                   ' "i"

    ' Language ids:
    Public Const SSCE_ANY_LANG = 30840                      ' "xx"
    Public Const SSCE_AMER_ENGLISH_LANG = 24941             ' "am"
    Public Const SSCE_BRIT_ENGLISH_LANG = 25202             ' "br"
    Public Const SSCE_CANADIAN_ENGLISH_LANG = 25441         ' "ca"
    Public Const SSCE_CATALAN_LANG = 29539                  ' "sc"
    Public Const SSCE_CZECH_LANG = 25466                    ' "cz"
    Public Const SSCE_DANISH_LANG = 25697                   ' "da"
    Public Const SSCE_DUTCH_LANG = 25717                    ' "du"
    Public Const SSCE_FINNISH_LANG = 26217                  ' "fi"
    Public Const SSCE_FRENCH_LANG = 26226                   ' "fr"
    Public Const SSCE_GERMAN_LANG = 26469                   ' "ge"
    Public Const SSCE_HUNGARIAN_LANG = 26741                ' "hu"
    Public Const SSCE_ITALIAN_LANG = 26996                  ' "it"
    Public Const SSCE_NORWEGIAN_BOKMAL_LANG = 25442         ' "cb"
    Public Const SSCE_NORWEGIAN_NYNORSK_LANG = 25444        ' "cd"
    Public Const SSCE_POLISH_LANG = 28780                   ' "pl"
    Public Const SSCE_PORTUGUESE_BRAZIL_LANG = 28770        ' "pb"
    Public Const SSCE_PORTUGUESE_IBERIAN_LANG = 28783       ' "po"
    Public Const SSCE_RUSSIAN_LANG = 29301                  ' "ru"
    Public Const SSCE_SPANISH_LANG = 29552                  ' "sp"
    Public Const SSCE_SWEDISH_LANG = 29559                  ' "sw"

    ' Character sets.
    Public Const SSCE_LATIN1_CHARSET = 1
    Public Const SSCE_UNICODE_CHARSET = 2

    ' Functions in the basic SSCE API

    Declare Function SSCE_AddToLex Lib "ssce5332.dll" (ByVal sid As Short, ByVal lexId As Short, _
      ByVal word$, ByVal action As Short, ByVal otherWord$) As Short

    Declare Function SSCE_CheckBlock Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal errWord$, ByVal errWordSz As Short, ByVal otherWord$, _
      ByVal otherWordSz As Short) As Short

    Declare Function SSCE_CheckString Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$, ByRef cursor As Integer, ByVal errWord$, ByVal errWordSz As Short, _
      ByVal otherWord$, ByVal otherWordSz As Short) As Short

    Declare Function SSCE_CheckWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal word$, ByVal otherWord$, ByVal otherWordSz As Short) As Short

    Declare Function SSCE_ClearLex Lib "ssce5332.dll" (ByVal sid As Short, ByVal lexId As Short) _
      As Short

    Declare Function SSCE_CloseBlock Lib "ssce5332.dll" (ByVal sid As Short, ByVal blkId As Short) _
      As Short

    Declare Function SSCE_CloseLex Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal lexId As Short) As Short

    Declare Function SSCE_CloseSession Lib "ssce5332.dll" (ByVal sid As Short) As Short

    Declare Sub SSCE_CompressLexAbort Lib "ssce5332.dll" (ByVal sid As Short)

    Declare Function SSCE_CompressLexEnd Lib "ssce5332.dll" (ByVal sid As Short) As Short

    Declare Function SSCE_CompressLexFile Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal fileName$, ByVal errLine As Integer) As Short

    Declare Function SSCE_CompressLexInit Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal lexFileName$, ByVal suffixFileName$, ByVal langId As Short, _
      ByVal errLine As Integer) As Short

    Declare Function SSCE_CountStringWords Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$) As Integer

    Declare Function SSCE_CreateLex Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal fileName$, ByVal lang As Short) As Short

    Declare Function SSCE_DelBlockText Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal numChars As Integer) As Short

    Declare Function SSCE_DelBlockWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal delText$, ByVal delTextSz As Short) As Integer

    Declare Function SSCE_DelFromLex Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal lexId As Short, ByVal word$) As Short

    Declare Function SSCE_DelStringText Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$, ByVal cursor As Integer, ByVal numChars As Integer) As Integer

    Declare Function SSCE_DelStringWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$, ByVal cursor As Integer, ByVal delText$, ByVal delTextSz As Integer) As Integer

    Declare Function SSCE_FindLexWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal lexId As Short, ByVal word$, ByVal otherWord$, ByVal otherWordSz As Short) As Short

    Declare Function SSCE_GetBlock Lib "ssce5332.dll" (ByVal sid As Short, ByVal blkId As Short, _
      ByVal block$, ByVal blkSz As Integer) As Integer

    Declare Function SSCE_GetBlockInfo Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByRef blkLen As Integer, ByRef blkSz As Integer, _
      ByRef curPos As Integer, ByRef wordCount As Integer) As Short

    Declare Function SSCE_GetBlockWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal word$, ByVal wordSz As Short) As Short

    Declare Function SSCE_GetLex Lib "ssce5332.dll" (ByVal sid As Short, ByVal lexId As Short, _
      ByVal lexBfr$, ByVal lexBfrSz As Integer) As Integer

    Declare Function SSCE_GetLexInfo Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal lexId As Short, ByVal lexSz As Integer, ByVal lexFormat As Short, _
      ByVal lang As Short) As Short

    Declare Function SSCE_GetOption Lib "ssce5332.dll" (ByVal sid As Short, ByVal opt As Integer) As Integer

    Declare Function SSCE_GetStringWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$, ByVal cursor As Integer, ByVal word$, ByVal wordSz As Short) As Integer

    Declare Function SSCE_InsertBlockText Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal text$) As Short

    Declare Function SSCE_InsertStringText Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$, ByVal strSz As Integer, ByVal cursor As Integer, ByVal text$) As Integer

    Declare Function SSCE_NextBlockWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short) As Short

    Declare Function SSCE_OpenBlock Lib "ssce5332.dll" (ByVal sid As Short, ByVal block$, _
      ByVal blkLen As Integer, ByVal blkSz As Integer, ByVal copyBlock As Short) As Short

    Declare Function SSCE_OpenLex Lib "ssce5332.dll" (ByVal sid As Short, ByVal fileName$, _
      ByVal memBudget As Integer) As Short

    Declare Function SSCE_OpenSession Lib "ssce5332.dll" () As Short

    Declare Function SSCE_ReplaceBlockWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal word$) As Short

    Declare Function SSCE_ReplaceStringWord Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal str$, ByVal strSz As Integer, ByVal cursor As Integer, ByVal word$) As Integer

    Declare Function SSCE_SetBlockCursor Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal blkId As Short, ByVal cursor As Integer) As Short

    Declare Sub SSCE_SetDebugFile Lib "ssce5332.dll" (ByVal debugFile$)

    Declare Function SSCE_SetOption Lib "ssce5332.dll" (ByVal sid As Short, _
      ByVal opt As Integer, ByVal optVal As Integer) As Integer

    Declare Function SSCE_Suggest Lib "ssce5332.dll" (ByVal sid As Short, ByVal word$, _
      ByVal depth As Short, ByVal suggBfr$, ByVal suggBfrSz As Integer, ByRef scores As Short, _
      ByVal nScores As Short) As Short

    Declare Sub SSCE_Version Lib "ssce5332.dll" (ByVal version$, ByVal versionSz As Short)

    ' Functions in the Windows API:

    Declare Function SSCE_CheckBlockDlg Lib "ssce5332.dll" (ByVal parent As Integer, _
      ByVal block$, ByVal blkLen As Integer, ByVal blkSz As Integer, _
      ByVal showContext As Short) As Integer

    Declare Function SSCE_CheckBlockDlgTmplt Lib "ssce5332.dll" (ByVal parent As Integer, _
      ByVal block$, ByVal blkLen As Integer, ByVal blkSz As Integer, ByVal showContext As Short, _
      ByVal clientInst As Integer, ByVal spellDlgTmplt$, ByVal dictDlgTmplt$, _
      ByVal optDlgTmplt$, ByVal newLexDlgTmplt$) As Integer

    Declare Function SSCE_CheckCtrlBackground Lib "ssce5332.dll" (ByVal ctrlWin As Integer) _
       As Short

    Declare Function SSCE_CheckCtrlDlg Lib "ssce5332.dll" (ByVal parent As Integer, _
      ByVal ctrlWin As Integer, ByVal selTextOnly As Short) As Short

    Declare Function SSCE_CheckCtrlDlgTmplt Lib "ssce5332.dll" (ByVal parent As Integer, _
      ByVal ctrlWin As Integer, ByVal selTextOnly As Short, ByVal clientInst As Integer, _
      ByVal spellDlgTmplt$, ByVal dictDlgTmplt$, ByVal optDlgTmplt$, _
      ByVal newLexDlgTmplt$) As Short

    Declare Function SSCE_EditLexDlg Lib "ssce5332.dll" (ByVal parent As Integer) As Short

    Declare Function SSCE_EditLexDlgTmplt Lib "ssce5332.dll" (ByVal parent As Integer, _
      ByVal clientInst As Integer, ByVal dictDlgTmplt$, ByVal newLexDlgTmplt$) As Short

    Declare Function SSCE_GetAutoCorrect Lib "ssce5332.dll" () As Short

    Declare Sub SSCE_GetHelpFile Lib "ssce5332.dll" (ByVal fileName$, _
      ByVal fileNameSz As Short)

    Declare Function SSCE_GetLexId Lib "ssce5332.dll" (ByVal lexFileName$) As Short

    Declare Sub SSCE_GetMainLexFiles Lib "ssce5332.dll" (ByVal fileList$, _
      ByVal fileListSz As Short)

    Declare Sub SSCE_GetMainLexPath Lib "ssce5332.dll" (ByVal path$, _
      ByVal pathSz As Short)

    Declare Function SSCE_GetMinSuggestDepth Lib "ssce5332.dll" () As Short

    Declare Sub SSCE_GetRegTreeName Lib "ssce5332.dll" (ByVal regTreeName$, _
      ByVal regTreeNameSz As Short)

    Declare Sub SSCE_GetSelUserLexFile Lib "ssce5332.dll" (ByVal fileName$, _
      ByVal fileNameSz As Short)

    Declare Function SSCE_GetSid Lib "ssce5332.dll" () As Short

    Declare Sub SSCE_GetStatistics Lib "ssce5332.dll" (ByVal wordsChecked As Integer, _
      ByVal wordsChanged As Integer, ByVal errorsDetected As Integer)

    Declare Sub SSCE_GetStringTableName Lib "ssce5332.dll" (ByVal tableName$, _
      ByVal tableNameSz As Short)

    Declare Sub SSCE_GetUserLexFiles Lib "ssce5332.dll" (ByVal fileList$, _
      ByVal fileListSz As Short)

    Declare Sub SSCE_GetUserLexPath Lib "ssce5332.dll" (ByVal path$, ByVal pathSz As Short)

    Declare Function SSCE_OptionsDlg Lib "ssce5332.dll" (ByVal parent As Integer) As Short

    Declare Function SSCE_OptionsDlgTmplt Lib "ssce5332.dll" (ByVal parent As Integer, _
      ByVal clientInst As Integer, ByVal optDlgTmplt$) As Short

    Declare Function SSCE_ResetLex Lib "ssce5332.dll" () As Short

    Declare Function SSCE_SetAutoCorrect Lib "ssce5332.dll" (ByVal ac As Short) As Short

    Declare Sub SSCE_SetDialogOrigin Lib "ssce5332.dll" (ByVal x As Short, ByVal y As Short)

    Declare Function SSCE_SetHelpFile Lib "ssce5332.dll" (ByVal helpFile$) As Short

    Declare Function SSCE_SetIniFile Lib "ssce5332.dll" (ByVal iniFile$) As Short

    Declare Function SSCE_SetKey Lib "ssce5332.dll" (ByVal key As Integer) As Short

    Declare Function SSCE_SetMainLexFiles Lib "ssce5332.dll" (ByVal fileList$) As Short

    Declare Function SSCE_SetMainLexPath Lib "ssce5332.dll" (ByVal path$) As Short

    Declare Function SSCE_SetMinSuggestDepth Lib "ssce5332.dll" (ByVal depth As Short) As Short

    Declare Function SSCE_SetRegTreeName Lib "ssce5332.dll" (ByVal regTreeName$) As Short

    Declare Function SSCE_SetSelUserLexFile Lib "ssce5332.dll" (ByVal fileName$) As Short

    Declare Function SSCE_SetStringTableName Lib "ssce5332.dll" (ByVal tableName$) As Short

    Declare Function SSCE_SetUserLexFiles Lib "ssce5332.dll" (ByVal fileList$) As Short

    Declare Function SSCE_SetUserLexPath Lib "ssce5332.dll" (ByVal path$) As Short

End Module
