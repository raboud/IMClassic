<SCRIPT LANGUAGE="VBScript" RUNAT="Server">

Option Explicit

' Sentry Spelling Checker Engine Windows SDK
' ASP Example1: Display misspelled words and suggestions
'
' Copyright © 2000 Wintertree Software Inc.
' http://www.wintertree-software.com
'
' $Id: default.asp,v 5.14 2000/06/28 18:03:51 wsi Exp wsi $

' Spell-check result masks. Note that these will always result in a
' positive value.
Const SSCE_MISSPELLED_WORD_RSLT = &H1
Const SSCE_AUTO_CHANGE_WORD_RSLT = &H2
Const SSCE_CONDITIONALLY_CHANGE_WORD_RSLT = &H4
Const SSCE_UNCAPPED_WORD_RSLT = &H8
Const SSCE_MIXED_CASE_WORD_RSLT = &H10
Const SSCE_MIXED_DIGITS_WORD_RSLT = &H20
Const SSCE_END_OF_TEXT_RSLT = &H40
Const SSCE_DOUBLED_WORD_RSLT = &H80

' Determine what to do based on button used to submit the form.
Dim action
action = Request.Form("action")
Select Case action
Case ""
	Call displayEntryForm("")
Case "Check Spelling"
	Call checkSpelling
Case "Submit"
	Call submitForm
End Select

' Check the spelling of text in textArea1 and display any misspelled
' words found plus suggestions.
Sub checkSpelling
	Dim spellChecker, sid, results, misspelledWords, cursor, text, done
	Dim suggestions(16), scores(16), suggestionStr
	Set spellChecker = Server.CreateObject("SentryASC.SpellChecker")

	results = "<H1>Spelling check results:</H1>"

	' Create a Dictionary object (NOT a spelling dictionary!) to hold
	' misspelled words and suggestions. We'll call this a "collection"
	' from now on to avoid confusion.
	Set misspelledWords = CreateObject("Scripting.Dictionary")
	misspelledWords.CompareMode = vbBinaryCompare ' case insensitive

	' Check the words in the text area.
	text = Request.Form("textArea1")
	done = False
	cursor = 0

	sid = Application("SSCESid")
	If (sid < 0) Then
		Response.Write("Error creating a Sentry session.<BR>Did you set your license key in global.asa?<P>")
		Exit Sub
	End If

	' Keep checking until the end of the text is reached.
	cursor = 0
	While (Not done)
		Dim word, otherWord, result
		Application.Lock
		result = spellChecker.CheckString(CInt(sid), CStr(text), cursor, word, otherWord)
		Application.Unlock
		If (result < 0) Then
			Response.Write("CheckString returned " & result & " cursor: " & cursor & " word: " & word & "<BR>")
			done = True
		ElseIf ((result And SSCE_END_OF_TEXT_RSLT) <> 0) Then
			' End of text reached.
			done = True
		Else
			' We found a misspelled word (word). If we haven't encountered
			' this word before, add it along with suggested replacements
			' to the misspelledWord collection.
			If (Not misspelledWords.Exists(word)) Then

				' Get suggested replacements for the misspelling. Use depth
				' 50, which is a good compromise between accuracy and speed.
				Application.Lock
				Call spellChecker.Suggest(CInt(sid), CStr(word), CInt(50), suggestions, scores, CInt(16))
				Application.Unlock

				' Format the suggestions as a comma-separated string.
				suggestionStr = ""
				For i = 0 to (16 - 1)
					If (suggestions(i) <> "") Then
						If (suggestionStr <> "") Then
							suggestionStr = suggestionStr & ", "
						End If
						suggestionStr = suggestionStr & suggestions(i)
					End If
				Next

				' Add the misspelled word and suggestions to the collection.
				misspelledWords.Add word, suggestionStr
				suggestionStr = ""
			End If

			' Skip over this word (i.e., advance the cursor past
			' the word). If we don't do this, CheckString will keep
			' reporting this word over and over.
			cursor = cursor + Len(word)
		End If
	Wend

	' We've checked all the words in the text.
	' Present the misspelled words and suggestions.
	Dim words, suggestionList
	words = misspelledWords.Keys
	suggestionList = misspelledWords.Items
	If misspelledWords.Count > 0 Then
		results = results & "<P>The following misspelled words were found:"
		Dim i
		For i = 0 to misspelledWords.Count - 1
			results = results & "<P><B>" & words(i) & ":</B> " & "<I>Suggestions:</I> " & Replace(suggestionList(i), ",", ", ")
		Next
	Else
		results = results & "No misspelled words found!"
	End If

	' Present the form with spelling results to the user.
	Call displayEntryForm(results)
	Set spellChecker = Nothing
End Sub

' displayEntryForm:
' Respond with an HTML form containing a text area used to enter text which
' can be spell-checked.
' @param results HTML spelling-check results
Sub displayEntryForm(results)
	Dim fso, formFile, path, i, formFileName, formLine

	Set fso = CreateObject("Scripting.FileSystemObject")
	path = Request.ServerVariables("PATH_TRANSLATED")
	i = InstrRev(path, "\")
	If (i >= 0) Then
	   path = Left(path, i)  ' leave on trailing "\"
	End If
	formFileName = path & "form.html"
	Set formFile = fso.OpenTextFile(formFileName)
	While (Not formFile.AtEndOfStream)
		formLine = formFile.ReadLine

		formLine = Replace(formLine, "!!TEXT!!", Request.Form("textArea1"))
		formLine = Replace(formLine, "!!RESULTS!!", results)

		Response.Write(formLine & vbCrLf)
	Wend
	formFile.Close
End Sub

' Perform whatever steps are needed to submit the form.
Sub submitForm
	' This is just a stub. In reality, your form-submission processing
	' would go here.
	Response.write("<H1>Form submitted!</H1>")
	Response.write("<P>Thank you for your submission!")
End Sub

</SCRIPT>
