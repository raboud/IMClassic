Attribute VB_Name = "SSCEVB"
' Sentry Spelling Checker Engine
' SSCEVB: Functions and subroutines to make SSCE easier to use from Visual Basic.
'
' Copyright (c) 1997 Wintertree Software Inc.
' www.wintertree-software.com
'
' $Id: sscevb.bas,v 5.14 2000/06/28 17:33:00 wsi Exp wsi $

Option Explicit

Private Function CStringToVBString(cstring As String) As String
    Dim nullPos As Long
    
    nullPos = InStr(cstring, Chr$(0))
    If nullPos <> 0 Then
        CStringToVBString = Left$(cstring, nullPos - 1)
    Else
        CStringToVBString = cstring
    End If
End Function

Sub SSCEVB_GetSelUserLexFile(fileName$)
    Dim fn As String
    
    fn = String$(256, Chr$(0))
    Call SSCE_GetSelUserLexFile(fn, Len(fn))
    fileName = CStringToVBString(fn)
End Sub

Sub SSCEVB_GetMainLexFiles(fileList$)
    Dim fl As String
    
    fl = String$(512, Chr$(0))
    Call SSCE_GetMainLexFiles(fl, Len(fl))
    fileList = CStringToVBString(fl)
End Sub

Function SSCEVB_CheckBlockDlg(ByVal parent&, block$, ByVal blkLen&, _
  ByVal blkSz&, ByVal showContext%) As Long
    Dim n As Long
    
    ' 1 extra character is required to hold the terminating null.
    ' VB automatically appends a terminating null for parameters
    ' in DLL functions typed "byval string", so it's safe to
    ' specify the block size as 1 larger than the block length.
    If (blkSz = blkLen) Then
        blkSz = blkSz + 1
    End If
    n = SSCE_CheckBlockDlg(parent, block, blkLen, blkSz, showContext)
    If (n >= 0) Then
        block = Left$(block, n)
    End If
    SSCEVB_CheckBlockDlg = n
End Function

Function SSCEVB_CheckCtrlBackground(ByVal ctrlWin&) As Integer
    SSCEVB_CheckCtrlBackground = SSCE_CheckCtrlBackground(ctrlWin)
End Function

Function SSCEVB_CheckCtrlDlg(ByVal parent&, ByVal ctrlWin&, _
  ByVal selTextOnly%) As Integer
    SSCEVB_CheckCtrlDlg = SSCE_CheckCtrlDlg(parent, ctrlWin, selTextOnly)
End Function

Function SSCEVB_EditLexDlg(ByVal parent&) As Integer
    SSCEVB_EditLexDlg = SSCE_EditLexDlg(parent)
End Function

Function SSCEVB_GetAutoCorrect() As Integer
    SSCEVB_GetAutoCorrect = SSCE_GetAutoCorrect
End Function

Function SSCEVB_GetMinSuggestDepth() As Integer
    SSCEVB_GetMinSuggestDepth = SSCE_GetMinSuggestDepth
End Function

Sub SSCEVB_GetHelpFile(fileName$)
    Dim fn As String
    
    fn = String$(256, Chr$(0))
    Call SSCE_GetHelpFile(fn, Len(fn))
    fileName = CStringToVBString(fn)
End Sub

Function SSCEVB_GetLexId(ByVal lexFileName$) As Integer
    SSCEVB_GetLexId = SSCE_GetLexId(lexFileName)
End Function

Sub SSCEVB_GetMainLexPath(path As String)
    Dim p As String
    
    p = String$(256, Chr$(0))
    Call SSCE_GetMainLexPath(p, Len(p))
    path$ = CStringToVBString(p)
End Sub

Function SSCEVB_GetSid() As Integer
    SSCEVB_GetSid = SSCE_GetSid()
End Function

Sub SSCEVB_GetStatistics(wordsChecked&, wordsChanged&, errorsDetected&)
    Call SSCE_GetStatistics(wordsChecked, wordsChanged, errorsDetected)
End Sub

Sub SSCEVB_GetRegTreeName(regTreeName$)
    Dim tn As String
    
    tn = String$(256, Chr$(0))
    Call SSCE_GetRegTreeName(tn, Len(tn))
    regTreeName = CStringToVBString(tn)
End Sub

Sub SSCEVB_GetStringTableName(tableName$)
    Dim tn As String
    
    tn = String$(256, Chr$(0))
    Call SSCE_GetStringTableName(tn, Len(tn))
    tableName = CStringToVBString(tn)
End Sub

Sub SSCEVB_GetUserLexPath(path$)
    Dim p As String
    
    p = String(256, Chr$(0))
    Call SSCE_GetUserLexPath(p, Len(p))
    path = CStringToVBString(p)
End Sub

Function SSCEVB_OpenBlock(ByVal sid%, ByVal block$, ByVal blkLen&, _
  ByVal blkSz&, ByVal copyBlock%) As Integer
    If (blkSz = blkLen) Then
        ' 1 extra character is required to hold the terminating null.
        ' VB automatically appends a terminating null for parameters
        ' in DLL functions typed "byval string", so it's safe to
        ' specify the block size as 1 larger than the block length.
        blkSz = blkLen + 1
    End If
    SSCEVB_OpenBlock = SSCE_OpenBlock(sid, block, blkLen, blkSz, copyBlock)
End Function

Function SSCEVB_GetLexInfo(ByVal sid%, ByVal lexId%, lexSz&, lexFormat%, _
  lang%) As Integer
    SSCEVB_GetLexInfo = SSCE_GetLexInfo(sid, lexId, lexSz, lexFormat, _
      lang)
End Function

Function SSCEVB_CloseBlock(ByVal sid%, ByVal blkId%) As Integer
    SSCEVB_CloseBlock = SSCE_CloseBlock(sid, blkId)
End Function

Function SSCEVB_CheckWord(ByVal sid%, ByVal word$, otherWord$) As Integer
    Dim ow As String
    
    ow = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_CheckWord = SSCE_CheckWord(sid, word, ow, Len(ow))
    otherWord = CStringToVBString(ow)
End Function

Function SSCEVB_CheckBlock(ByVal sid%, ByVal blkId%, errWord$, otherWord$) As _
  Integer
    Dim ew As String
    Dim ow As String
    
    ew = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    ow = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_CheckBlock = SSCE_CheckBlock(sid, blkId, ew, Len(ew), ow, Len(ow))
    errWord = CStringToVBString(ew)
    otherWord = CStringToVBString(ow)
End Function

Function SSCEVB_AddToLex(ByVal sid%, ByVal lexId%, ByVal word$, _
  ByVal action%, ByVal otherWord$) As Integer
    SSCEVB_AddToLex = SSCE_AddToLex(sid, lexId, word, action, otherWord)
End Function

Function SSCEVB_ClearLex(ByVal sid%, ByVal lexId%) As Integer
    SSCEVB_ClearLex = SSCE_ClearLex(sid, lexId)
End Function

Function SSCEVB_CloseLex(ByVal sid%, ByVal lexId%) As Integer
    SSCEVB_CloseLex = SSCE_CloseLex(sid, lexId)
End Function

Function SSCEVB_CloseSession(ByVal sid%) As Integer
    SSCEVB_CloseSession = SSCE_CloseSession(sid)
End Function

Sub SSCEVB_CompressLexAbort(ByVal sid%)
    Call SSCE_CompressLexAbort(sid)
End Sub

Function SSCEVB_CompressLexEnd(ByVal sid%) As Integer
    SSCEVB_CompressLexEnd = SSCE_CompressLexEnd(sid)
End Function

Function SSCEVB_CompressLexFile(ByVal sid%, ByVal fileName$, errLine&) As _
  Integer
    SSCEVB_CompressLexFile = SSCE_CompressLexFile(sid, fileName, errLine)
End Function

Function SSCEVB_CompressLexInit(ByVal sid%, ByVal lexFileName$, _
  ByVal suffixFileName$, ByVal langId%, errLine&) As Integer
    SSCEVB_CompressLexInit = SSCE_CompressLexInit(sid, lexFileName, _
      suffixFileName, langId, errLine)
End Function

Function SSCEVB_CreateLex(ByVal sid%, ByVal fileName$, ByVal lang%) As Integer
    SSCEVB_CreateLex = SSCE_CreateLex(sid, fileName, lang)
End Function

Function SSCEVB_DelBlockText(ByVal sid%, ByVal blkId%, ByVal numChars&) As _
  Integer
    SSCEVB_DelBlockText = SSCE_DelBlockText(sid, blkId, numChars)
End Function

Function SSCEVB_DelBlockWord(ByVal sid%, ByVal blkId%, delText$) As Long
    Dim dt As String
    
    dt = String(256, Chr$(0))
    SSCEVB_DelBlockWord = SSCE_DelBlockWord(sid, blkId, dt, Len(dt))
    delText = CStringToVBString(dt)
End Function

Function SSCEVB_DelFromLex(ByVal sid%, ByVal lexId%, ByVal word$) As Integer
    SSCEVB_DelFromLex = SSCE_DelFromLex(sid, lexId, word)
End Function

Function SSCEVB_GetBlock(ByVal sid%, ByVal blkId%, block$) As Long
    Dim b As String
    Dim blkLen As Long
    Dim blkSz As Long

    Call SSCE_GetBlockInfo(sid, blkId, blkLen, blkSz, 0, 0)
    b = String$(blkSz, Chr$(0))
    Call SSCE_GetBlock(sid, blkId, b, blkSz)
    block = Left(b, blkLen)
    SSCEVB_GetBlock = blkLen
End Function

Function SSCEVB_GetBlockInfo(ByVal sid%, ByVal blkId%, blkLen&, blkSz&, _
  curPos&, wordCount&) As Integer
    SSCEVB_GetBlockInfo = SSCE_GetBlockInfo(sid, blkId, blkLen, blkSz, _
      curPos, wordCount)
End Function

Function SSCEVB_GetBlockWord(ByVal sid%, ByVal blkId%, word$) As Integer
    Dim w As String
    
    w = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_GetBlockWord = SSCE_GetBlockWord(sid, blkId, w, Len(w))
    word = CStringToVBString(w)
End Function

Function SSCEVB_GetLex(ByVal sid%, ByVal lexId%, lexBfr$) As Long
    Dim lb As String
    Dim lexBfrSz As Long
    
    Call SSCE_GetLexInfo(sid, lexId, lexBfrSz, 0, 0)
    lb = String$(lexBfrSz, Chr$(0))
    Call SSCE_GetLex(sid, lexId, lb, Len(lb))
    lexBfr = Left$(lb, lexBfrSz)
    SSCEVB_GetLex = lexBfrSz
End Function

Function SSCEVB_GetOption(ByVal sid%, ByVal opt&) As Long
    SSCEVB_GetOption = SSCE_GetOption(sid, opt)
End Function

Function SSCEVB_InsertBlockText(ByVal sid%, ByVal blkId%, ByVal text$) As _
  Integer
    SSCEVB_InsertBlockText = SSCE_InsertBlockText(sid, blkId, text)
End Function

Function SSCEVB_NextBlockWord(ByVal sid%, ByVal blkId%) As Integer
    SSCEVB_NextBlockWord = SSCE_NextBlockWord(sid, blkId)
End Function

Function SSCEVB_OpenLex(ByVal sid%, ByVal fileName$, ByVal memBudget&) As _
  Integer
    SSCEVB_OpenLex = SSCE_OpenLex(sid, fileName, memBudget)
End Function

Function SSCEVB_OpenSession() As Integer
    SSCEVB_OpenSession = SSCE_OpenSession
End Function

Function SSCEVB_OptionsDlg(ByVal parent&) As Integer
    SSCEVB_OptionsDlg = SSCE_OptionsDlg(parent)
End Function

Function SSCEVB_ReplaceBlockWord(ByVal sid%, ByVal blkId%, ByVal word$) As _
  Integer
    SSCEVB_ReplaceBlockWord = SSCE_ReplaceBlockWord(sid, blkId, word)
End Function

Function SSCEVB_ResetLex() As Integer
    SSCEVB_ResetLex = SSCE_ResetLex()
End Function

Function SSCEVB_SetAutoCorrect(ByVal autoCorrect%) As Integer
    SSCEVB_SetAutoCorrect = SSCE_SetAutoCorrect(autoCorrect)
End Function

Function SSCEVB_SetMinSuggestDepth(ByVal depth%) As Integer
    SSCEVB_SetMinSuggestDepth = SSCE_SetMinSuggestDepth(depth)
End Function

Function SSCEVB_SetBlockCursor(ByVal sid%, ByVal blkId%, ByVal cursor&) As _
  Integer
    SSCEVB_SetBlockCursor = SSCE_SetBlockCursor(sid, blkId, cursor)
End Function

Sub SSCEVB_SetDebugFile(ByVal debugFile$)
    Call SSCE_SetDebugFile(debugFile)
End Sub

Sub SSCEVB_SetDialogOrigin(ByVal x%, ByVal y%)
    Call SSCE_SetDialogOrigin(x, y)
End Sub

Function SSCEVB_SetHelpFile(ByVal helpFile$) As Integer
    SSCEVB_SetHelpFile = SSCE_SetHelpFile(helpFile)
End Function

Function SSCEVB_SetIniFile(ByVal iniFile$) As Integer
    SSCEVB_SetIniFile = SSCE_SetIniFile(iniFile)
End Function

Function SSCEVB_SetMainLexFiles(ByVal fileList$) As Integer
    SSCEVB_SetMainLexFiles = SSCE_SetMainLexFiles(fileList)
End Function

Function SSCEVB_SetMainLexPath(ByVal path$) As Integer
    SSCEVB_SetMainLexPath = SSCE_SetMainLexPath(path)
End Function

Function SSCEVB_SetOption(ByVal sid%, ByVal opt&, ByVal optVal&) As Long
    SSCEVB_SetOption = SSCE_SetOption(sid, opt, optVal)
End Function

Function SSCEVB_SetRegTreeName(ByVal regTreeName$) As Integer
    SSCEVB_SetRegTreeName = SSCE_SetRegTreeName(regTreeName)
End Function

Function SSCEVB_SetSelUserLexFile(fileName$) As Integer
    SSCEVB_SetSelUserLexFile = SSCE_SetSelUserLexFile(fileName)
End Function

Function SSCEVB_SetStringTableName(ByVal tableName$) As Integer
    SSCEVB_SetStringTableName = SSCE_SetStringTableName(tableName)
End Function

Function SSCEVB_SetUserLexFiles(ByVal fileList$) As Integer
    SSCEVB_SetUserLexFiles = SSCE_SetUserLexFiles(fileList)
End Function

Function SSCEVB_SetUserLexPath(ByVal path$) As Integer
    SSCEVB_SetUserLexPath = SSCE_SetUserLexPath(path)
End Function

Function SSCEVB_Suggest(ByVal sid%, ByVal word$, ByVal depth%, _
  suggestions$(), scores%(), ByVal nSuggestions%) As Integer
    Dim s As Integer
    Dim e As Integer
    Dim i As Integer
    Dim done As Boolean
    Dim suggBfr As String
    
    suggBfr = String$(nSuggestions * SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_Suggest = SSCE_Suggest(sid, word, depth, suggBfr, Len(suggBfr), _
      scores(0), nSuggestions)
    
    ' Copy each null-terminated suggestion to the suggestions array.
    s = 1
    i = 0
    done = False
    While Not done
        e = InStr(s, suggBfr, Chr(0))
        If e <> 0 And e > s Then
            suggestions(i) = Mid(suggBfr, s, e - s)
            i = i + 1
            s = e + 1
        Else
            done = True
        End If
    Wend
End Function

Sub SSCEVB_Version(version$)
    Dim vs As String
    
    vs = String$(20, Chr$(0))
    Call SSCE_Version(vs, Len(vs))
    version = CStringToVBString(vs)
End Sub

Public Sub SSCEVB_GetUserLexFiles(files$)
    Dim p As String
    
    p = String$(256, Chr$(0))
    Call SSCE_GetUserLexFiles(p, Len(p))
    files = CStringToVBString(p)
End Sub

Public Function SSCEVB_SetKey(ByVal key As Long) As Integer
    SSCEVB_SetKey = SSCE_SetKey(key)
End Function

Public Function SSCEVB_CheckString(ByVal sid%, ByVal str$, cursor&, errWord$, _
  otherWord$) As Integer
    Dim w As String
    Dim ow As String
    
    w = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    ow = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_CheckString = SSCE_CheckString(sid, str, cursor, w, Len(w), ow, Len(ow))
    errWord = CStringToVBString(w)
    otherWord = CStringToVBString(ow)
End Function

Public Function SSCEVB_DelStringText(ByVal sid%, str$, ByVal cursor&, _
  ByVal numChars&) As Long
    SSCEVB_DelStringText = SSCE_DelStringText(sid, str, cursor, numChars)
    str = CStringToVBString(str)
End Function

Public Function SSCEVB_DelStringWord(ByVal sid%, str$, ByVal cursor&, _
  delText$) As Long
    Dim dt As String
    
    dt = String$(SSCE_MAX_WORD_SZ * 2, Chr$(0))
    SSCEVB_DelStringWord = SSCE_DelStringWord(sid, str, cursor, dt, Len(dt))
    delText = CStringToVBString(dt)
    str = CStringToVBString(str)
End Function

Public Function SSCEVB_GetStringWord(ByVal sid%, str$, ByVal cursor&, _
  word$) As Long
    Dim w As String
    
    w = String$(SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_GetStringWord = SSCE_GetStringWord(sid, str, cursor, w, Len(w))
    word = CStringToVBString(w)
End Function

Public Function SSCEVB_InsertStringText(ByVal sid%, str$, ByVal cursor&, _
  ByVal text$) As Long
    Dim s As String
    
    s = str + String$(Len(text) + 1, Chr$(0))
    SSCEVB_InsertStringText = SSCE_InsertStringText(sid, s, Len(s), cursor, text)
    str = CStringToVBString(s)
End Function

Public Function SSCEVB_ReplaceStringWord(ByVal sid%, str$, ByVal cursor&, _
  ByVal word$) As Long
    Dim s As String
    
    s = str + String$(SSCE_MAX_WORD_SZ, Chr$(0))
    SSCEVB_ReplaceStringWord = SSCE_ReplaceStringWord(sid, s, Len(s), cursor, word)
    str = CStringToVBString(s)
End Function

Public Function SSCEVB_CountStringWords(ByVal sid%, str$) As Long
    SSCEVB_CountStringWords = SSCE_CountStringWords(sid, str)
End Function
