Module sscevbnet
    ' Sentry Spelling Checker Engine
    ' SSCEVBNet: Functions and subroutines to make SSCE easier to use from VB.NET
    '
    ' Copyright (c) 2002 Wintertree Software Inc.
    ' www.wintertree-software.com
    '
    ' $Id: sscevbnet.vb,v 5.14.12 2002/06/26 17:33:00 wsi Exp wsi $

    Private Function CStringToVBString(ByVal cstring As String) As String
        Dim nullPos As Long

        nullPos = InStr(cstring, Chr(0))
        If nullPos <> 0 Then
            CStringToVBString = Left$(cstring, nullPos - 1)
        Else
            CStringToVBString = cstring
        End If
    End Function

    Function SSCEVB_AddToLex(ByVal sid As Short, ByVal lexId As Short, ByVal word$, _
      ByVal action As Short, ByVal otherWord$) As Short
        SSCEVB_AddToLex = SSCE_AddToLex(sid, lexId, word, action, otherWord)
    End Function

    Function SSCEVB_CheckBlock(ByVal sid As Short, ByVal blkId As Short, ByRef errWord$, _
      ByRef otherWord$) As Short
        Dim ew As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)
        Dim ow As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)

        SSCEVB_CheckBlock = SSCE_CheckBlock(sid, blkId, ew, Len(ew), ow, Len(ow))
        errWord = CStringToVBString(ew)
        otherWord = CStringToVBString(ow)
    End Function

    Function SSCEVB_CheckBlockDlg(ByVal parent As IntPtr, ByRef block$, _
      ByVal blkLen As Integer, ByVal blkSz As Integer, ByVal showContext As Short) As Integer
        Dim n As Long

        ' 1 extra character is required to hold the terminating null.
        ' VB automatically appends a terminating null for parameters
        ' in DLL functions typed "ByVal String", so it's safe to
        ' specify the block size as 1 larger than the block length.
        If (blkSz = blkLen) Then
            blkSz = blkSz + 1
        End If
        n = SSCE_CheckBlockDlg(parent.ToInt32, block, blkLen, blkSz, showContext)
        If (n >= 0) Then
            block = Left$(block, n)
        End If
        SSCEVB_CheckBlockDlg = n
    End Function

    Function SSCEVB_CheckCtrlBackground(ByVal ctrlWin As IntPtr) As Short
        SSCEVB_CheckCtrlBackground = SSCE_CheckCtrlBackground(ctrlWin.ToInt32)
    End Function

    Function SSCEVB_CheckCtrlDlg(ByVal parent As IntPtr, ByVal ctrlWin As IntPtr, _
      ByVal selTextOnly As Short) As Short
        SSCEVB_CheckCtrlDlg = SSCE_CheckCtrlDlg(parent.ToInt32, ctrlWin.ToInt32, selTextOnly)
    End Function

    Public Function SSCEVB_CheckString(ByVal sid As Short, ByRef str$, ByRef cursor As Integer, _
      ByRef errWord$, ByRef otherWord$) As Short
        Dim w As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)
        Dim ow As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)

        SSCEVB_CheckString = SSCE_CheckString(sid, str, cursor, w, Len(w), ow, Len(ow))
        errWord = CStringToVBString(w)
        otherWord = CStringToVBString(ow)
    End Function

    Function SSCEVB_CheckWord(ByVal sid As Short, ByVal word$, ByRef otherWord$) As Short
        Dim ow As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)

        SSCEVB_CheckWord = SSCE_CheckWord(sid, word, ow, Len(ow))
        otherWord = CStringToVBString(ow)
    End Function

    Function SSCEVB_ClearLex(ByVal sid As Short, ByVal lexId As Short) As Short
        SSCEVB_ClearLex = SSCE_ClearLex(sid, lexId)
    End Function

    Function SSCEVB_CloseBlock(ByVal sid As Short, ByVal blkId As Short) As Short
        SSCEVB_CloseBlock = SSCE_CloseBlock(sid, blkId)
    End Function

    Function SSCEVB_CloseLex(ByVal sid As Short, ByVal lexId As Short) As Short
        SSCEVB_CloseLex = SSCE_CloseLex(sid, lexId)
    End Function

    Function SSCEVB_CloseSession(ByVal sid As Short) As Short
        SSCEVB_CloseSession = SSCE_CloseSession(sid)
    End Function

    Sub SSCEVB_CompressLexAbort(ByVal sid As Short)
        Call SSCE_CompressLexAbort(sid)
    End Sub

    Function SSCEVB_CompressLexEnd(ByVal sid As Short) As Short
        SSCEVB_CompressLexEnd = SSCE_CompressLexEnd(sid)
    End Function

    Function SSCEVB_CompressLexFile(ByVal sid As Short, ByVal fileName$, _
      ByVal errLine As Integer) As Integer
        SSCEVB_CompressLexFile = SSCE_CompressLexFile(sid, fileName, errLine)
    End Function

    Function SSCEVB_CompressLexInit(ByVal sid As Short, ByVal lexFileName$, _
      ByVal suffixFileName$, ByVal langId As Short, ByVal errLine As Integer) As Short
        SSCEVB_CompressLexInit = SSCE_CompressLexInit(sid, lexFileName, _
          suffixFileName, langId, errLine)
    End Function

    Public Function SSCEVB_CountStringWords(ByVal sid As Short, ByVal str$) As Integer
        SSCEVB_CountStringWords = SSCE_CountStringWords(sid, str)
    End Function

    Function SSCEVB_CreateLex(ByVal sid As Short, ByVal fileName$, ByVal lang As Short) As Integer
        SSCEVB_CreateLex = SSCE_CreateLex(sid, fileName, lang)
    End Function

    Function SSCEVB_DelBlockText(ByVal sid As Short, ByVal blkId As Short, _
      ByVal numChars As Integer) As Integer
        SSCEVB_DelBlockText = SSCE_DelBlockText(sid, blkId, numChars)
    End Function

    Function SSCEVB_DelBlockWord(ByVal sid As Short, ByVal blkId As Short, _
      ByRef delText$) As Integer
        Dim dt As String = New String(CChar(" "), 512)

        SSCEVB_DelBlockWord = SSCE_DelBlockWord(sid, blkId, dt, Len(dt))
        delText = CStringToVBString(dt)
    End Function

    Function SSCEVB_DelFromLex(ByVal sid As Short, ByVal lexId As Short, ByVal word$) As Short
        SSCEVB_DelFromLex = SSCE_DelFromLex(sid, lexId, word)
    End Function

    Public Function SSCEVB_DelStringText(ByVal sid As Short, ByRef str$, _
      ByVal cursor As Integer, ByVal numChars As Integer) As Integer
        SSCEVB_DelStringText = SSCE_DelStringText(sid, str, cursor, numChars)
        str = CStringToVBString(str)
    End Function

    Public Function SSCEVB_DelStringWord(ByVal sid As Short, ByRef str$, _
      ByVal cursor As Integer, ByRef delText$) As Integer
        Dim dt As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)

        SSCEVB_DelStringWord = SSCE_DelStringWord(sid, str, cursor, dt, Len(dt))
        delText = CStringToVBString(dt)
        str = CStringToVBString(str)
    End Function

    Function SSCEVB_EditLexDlg(ByVal parent As IntPtr) As Short
        SSCEVB_EditLexDlg = SSCE_EditLexDlg(parent.ToInt32)
    End Function

    Function SSCEVB_GetAutoCorrect() As Short
        SSCEVB_GetAutoCorrect = SSCE_GetAutoCorrect
    End Function

    Function SSCEVB_GetBlock(ByVal sid As Short, ByVal blkId As Short, ByRef block$) As Integer
        Dim b As String
        Dim blkLen As Integer
        Dim blkSz As Integer

        Call SSCE_GetBlockInfo(sid, blkId, blkLen, blkSz, 0, 0)
        b = New String(CChar(" "), blkSz)
        Call SSCE_GetBlock(sid, blkId, b, blkSz)
        block = Left(b, blkLen)
        SSCEVB_GetBlock = blkLen
    End Function

    Function SSCEVB_GetBlockInfo(ByVal sid As Short, ByVal blkId As Short, _
      ByRef blkLen As Integer, ByRef blkSz As Integer, ByRef curPos As Integer, _
      ByRef wordCount As Integer) As Short
        SSCEVB_GetBlockInfo = SSCE_GetBlockInfo(sid, blkId, blkLen, blkSz, _
          curPos, wordCount)
    End Function

    Function SSCEVB_GetBlockWord(ByVal sid As Short, ByVal blkId As Short, ByRef word$) As Integer
        Dim w As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)

        SSCEVB_GetBlockWord = SSCE_GetBlockWord(sid, blkId, w, Len(w))
        word = CStringToVBString(w)
    End Function

    Sub SSCEVB_GetHelpFile(ByRef fileName$)
        Dim fn As String = New String(CChar(" "), 512)

        Call SSCE_GetHelpFile(fn, Len(fn))
        fileName = CStringToVBString(fn)
    End Sub

    Function SSCEVB_GetLex(ByVal sid As Short, ByVal lexId As Short, ByRef lexBfr$) As Integer
        Dim lb As String
        Dim lexBfrSz As Integer

        Call SSCE_GetLexInfo(sid, lexId, lexBfrSz, 0, 0)
        lb = New String(CChar(" "), lexBfrSz)
        Call SSCE_GetLex(sid, lexId, lb, Len(lb))
        lexBfr = Left$(lb, lexBfrSz)
        SSCEVB_GetLex = lexBfrSz
    End Function

    Function SSCEVB_GetLexId(ByVal lexFileName$) As Short
        SSCEVB_GetLexId = SSCE_GetLexId(lexFileName)
    End Function

    Function SSCEVB_GetLexInfo(ByVal sid As Short, ByVal lexId As Short, _
      ByRef lexSz As Integer, ByRef lexFormat As Short, ByRef lang As Short) As Short
        SSCEVB_GetLexInfo = SSCE_GetLexInfo(sid, lexId, lexSz, lexFormat, lang)
    End Function

    Sub SSCEVB_GetMainLexFiles(ByVal fileList$)
        Dim fl As String = New String(CChar(" "), 1024)

        Call SSCE_GetMainLexFiles(fl, Len(fl))
        fileList = CStringToVBString(fl)
    End Sub

    Sub SSCEVB_GetMainLexPath(ByRef path As String)
        Dim p As String = New String(CChar(" "), 512)

        Call SSCE_GetMainLexPath(p, Len(p))
        path$ = CStringToVBString(p)
    End Sub

    Function SSCEVB_GetMinSuggestDepth() As Short
        SSCEVB_GetMinSuggestDepth = SSCE_GetMinSuggestDepth
    End Function

    Function SSCEVB_GetOption(ByVal sid As Short, ByVal opt As Integer) As Integer
        SSCEVB_GetOption = SSCE_GetOption(sid, opt)
    End Function

    Sub SSCEVB_GetRegTreeName(ByRef regTreeName$)
        Dim tn As String = New String(CChar(" "), 512)

        Call SSCE_GetRegTreeName(tn, Len(tn))
        regTreeName = CStringToVBString(tn)
    End Sub

    Sub SSCEVB_GetSelUserLexFile(ByVal fileName$)
        Dim fn As String = New String(CChar(" "), 512)

        Call SSCE_GetSelUserLexFile(fn, Len(fn))
        fileName = CStringToVBString(fn)
    End Sub

    Function SSCEVB_GetSid() As Short
        SSCEVB_GetSid = SSCE_GetSid()
    End Function

    Sub SSCEVB_GetStatistics(ByRef wordsChecked As Integer, ByRef wordsChanged As Integer, _
      ByRef errorsDetected As Integer)
        Call SSCE_GetStatistics(wordsChecked, wordsChanged, errorsDetected)
    End Sub

    Sub SSCEVB_GetStringTableName(ByRef tableName$)
        Dim tn As String = New String(CChar(" "), 256)

        Call SSCE_GetStringTableName(tn, Len(tn))
        tableName = CStringToVBString(tn)
    End Sub

    Public Function SSCEVB_GetStringWord(ByVal sid As Short, ByVal str$, _
      ByVal cursor As Integer, ByRef word$) As Integer
        Dim w As String = New String(CChar(" "), SSCE_MAX_WORD_SZ)

        SSCEVB_GetStringWord = SSCE_GetStringWord(sid, str, cursor, w, Len(w))
        word = CStringToVBString(w)
    End Function

    Public Sub SSCEVB_GetUserLexFiles(ByRef files$)
        Dim p As String = New String(CChar(" "), 512)

        Call SSCE_GetUserLexFiles(p, Len(p))
        files = CStringToVBString(p)
    End Sub

    Sub SSCEVB_GetUserLexPath(ByRef path$)
        Dim p As String = New String(CChar(" "), 512)

        Call SSCE_GetUserLexPath(p, Len(p))
        path = CStringToVBString(p)
    End Sub

    Function SSCEVB_InsertBlockText(ByVal sid As Short, ByVal blkId As Short, ByVal text$) As _
      Short
        SSCEVB_InsertBlockText = SSCE_InsertBlockText(sid, blkId, text)
    End Function

    Public Function SSCEVB_InsertStringText(ByVal sid As Short, ByRef str$, _
      ByVal cursor As Integer, ByVal text$) As Integer

        ' SSCE_InsertStringText isn't used because the string buffer size
        ' isn't known.
        str = str.Substring(0, cursor) & text & str.Substring(cursor)
        SSCEVB_InsertStringText = 0
    End Function

    Function SSCEVB_NextBlockWord(ByVal sid As Short, ByVal blkId As Short) As Short
        SSCEVB_NextBlockWord = SSCE_NextBlockWord(sid, blkId)
    End Function

    Function SSCEVB_OpenBlock(ByVal sid As Short, ByVal block$, ByVal blkLen As Integer, _
      ByVal blkSz As Integer, ByVal copyBlock As Short) As Short
        If (blkSz = blkLen) Then
            ' 1 extra character is required to hold the terminating null.
            ' VB automatically appends a terminating null for parameters
            ' in DLL functions typed "byval string", so it's safe to
            ' specify the block size as 1 larger than the block length.
            blkSz = blkLen + 1
        End If
        SSCEVB_OpenBlock = SSCE_OpenBlock(sid, block, blkLen, blkSz, copyBlock)
    End Function

    Function SSCEVB_OpenLex(ByVal sid As Short, ByVal fileName$, ByVal memBudget As Integer) As _
      Integer
        SSCEVB_OpenLex = SSCE_OpenLex(sid, fileName, memBudget)
    End Function

    Function SSCEVB_OpenSession() As Short
        SSCEVB_OpenSession = SSCE_OpenSession
    End Function

    Function SSCEVB_OptionsDlg(ByVal parent As Integer) As Short
        SSCEVB_OptionsDlg = SSCE_OptionsDlg(parent)
    End Function

    Function SSCEVB_ReplaceBlockWord(ByVal sid As Short, ByVal blkId As Short, ByVal word$) As _
      Short
        SSCEVB_ReplaceBlockWord = SSCE_ReplaceBlockWord(sid, blkId, word)
    End Function

    Public Function SSCEVB_ReplaceStringWord(ByVal sid As Short, ByRef str$, _
      ByVal cursor As Integer, ByVal word$) As Integer
        Dim w As String

        Call SSCEVB_GetStringWord(sid, str, cursor, w)

        ' SSCE_ReplaceStringWord isn't used because string buffer length isn't known.
        str = str.Substring(0, cursor) & word & str.Substring(cursor + w.Length)

        SSCEVB_ReplaceStringWord = 0
    End Function

    Function SSCEVB_ResetLex() As Short
        SSCEVB_ResetLex = SSCE_ResetLex()
    End Function

    Function SSCEVB_SetAutoCorrect(ByVal autoCorrect As Short) As Short
        SSCEVB_SetAutoCorrect = SSCE_SetAutoCorrect(autoCorrect)
    End Function

    Function SSCEVB_SetBlockCursor(ByVal sid As Short, ByVal blkId As Short, _
      ByVal cursor As Integer) As Short
        SSCEVB_SetBlockCursor = SSCE_SetBlockCursor(sid, blkId, cursor)
    End Function

    Sub SSCEVB_SetDebugFile(ByVal debugFile$)
        Call SSCE_SetDebugFile(debugFile)
    End Sub

    Sub SSCEVB_SetDialogOrigin(ByVal x As Short, ByVal y As Short)
        Call SSCE_SetDialogOrigin(x, y)
    End Sub

    Function SSCEVB_SetHelpFile(ByVal helpFile$) As Short
        SSCEVB_SetHelpFile = SSCE_SetHelpFile(helpFile)
    End Function

    Function SSCEVB_SetIniFile(ByVal iniFile$) As Short
        SSCEVB_SetIniFile = SSCE_SetIniFile(iniFile)
    End Function

    Public Function SSCEVB_SetKey(ByVal key As Integer) As Short
        SSCEVB_SetKey = SSCE_SetKey(key)
    End Function

    Function SSCEVB_SetMainLexFiles(ByVal fileList$) As Short
        SSCEVB_SetMainLexFiles = SSCE_SetMainLexFiles(fileList)
    End Function

    Function SSCEVB_SetMainLexPath(ByVal path$) As Short
        SSCEVB_SetMainLexPath = SSCE_SetMainLexPath(path)
    End Function

    Function SSCEVB_SetMinSuggestDepth(ByVal depth As Short) As Short
        SSCEVB_SetMinSuggestDepth = SSCE_SetMinSuggestDepth(depth)
    End Function

    Function SSCEVB_SetOption(ByVal sid As Short, ByVal opt As Integer, _
      ByVal optVal As Integer) As Integer
        SSCEVB_SetOption = SSCE_SetOption(sid, opt, optVal)
    End Function

    Function SSCEVB_SetRegTreeName(ByVal regTreeName$) As Short
        SSCEVB_SetRegTreeName = SSCE_SetRegTreeName(regTreeName)
    End Function

    Function SSCEVB_SetSelUserLexFile(ByVal fileName$) As Short
        SSCEVB_SetSelUserLexFile = SSCE_SetSelUserLexFile(fileName)
    End Function

    Function SSCEVB_SetStringTableName(ByVal tableName$) As Short
        SSCEVB_SetStringTableName = SSCE_SetStringTableName(tableName)
    End Function

    Function SSCEVB_SetUserLexFiles(ByVal fileList$) As Short
        SSCEVB_SetUserLexFiles = SSCE_SetUserLexFiles(fileList)
    End Function

    Function SSCEVB_SetUserLexPath(ByVal path$) As Short
        SSCEVB_SetUserLexPath = SSCE_SetUserLexPath(path)
    End Function

    Function SSCEVB_Suggest(ByVal sid As Short, ByVal word$, ByVal depth As Short, _
    ByRef suggestions$(), ByRef scores() As Short, ByVal nSuggestions As Short) As Short
        Dim s As Integer
        Dim e As Integer
        Dim i As Integer
        Dim done As Boolean
        Dim suggBfr As String = New String(CChar(" "), nSuggestions * SSCE_MAX_WORD_SZ)

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
        End While
    End Function

    Sub SSCEVB_Version(ByRef version$)
        Dim vs As String = New String(CChar(" "), 20)

        Call SSCE_Version(vs, Len(vs))
        version = CStringToVBString(vs)
    End Sub

End Module
