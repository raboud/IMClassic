CREATE PROCEDURE dbo.createstatusdetails
@storefilter char(5) = 'ALL'
AS

IF EXISTS(SELECT name FROM sysobjects  WHERE  name = N'StatusDetails' AND 	 type = 'U')
	DROP TABLE dbo.StatusDetails
CREATE TABLE dbo.StatusDetails (StoreNumber nvarchar(50) NOT NULL, PONumber char(8) NULL, POGroup int, DivisionID int, DivisionGroupID int, InsuranceReplacement bit, LineIndex int, LineString char(255) NULL)
DECLARE @storenum nvarchar(50)
DECLARE @ponumber char(8) 
DECLARE @lineindex integer 
DECLARE @orderid integer 
DECLARE @first_name nvarchar(50) 
DECLARE @last_name nvarchar(50) 
DECLARE @status nvarchar(50) 
DECLARE @materialtypename nvarchar(50) 
DECLARE @so_number char(8) 
DECLARE @style nvarchar(50) 
DECLARE @size float 
DECLARE @description nvarchar(50) 
DECLARE @schedule_details bit 
DECLARE @scheduledate_details datetime 
DECLARE @billed_details bit 
DECLARE @paid_details bit 
DECLARE @billeddate_details datetime 
DECLARE @line_string nvarchar(1024) 
DECLARE @temp_string nvarchar(1024) 
DECLARE @temp_action2_string nvarchar(1024) 
DECLARE @name_string nvarchar(100) 
DECLARE @temp_int integer 
DECLARE @last_po char(8) 
DECLARE @last_orderid integer 
DECLARE @ponumber_group integer 
DECLARE @print_notes integer 
DECLARE @div_id integer 
DECLARE @div_group integer  
DECLARE @ponumber_notes char(8) 
DECLARE @orderid_notes integer 
DECLARE @datetime_notes datetime 
DECLARE @action1_notes varchar(50) 
DECLARE @action2_notes varchar(50) 
DECLARE @other_notes varchar(50) 
DECLARE @comments_notes varchar(1024) 
DECLARE @scheduled_notes bit 
DECLARE @unscheduled_notes bit 
DECLARE @insurance_replacement bit  

SELECT @lineindex = 0  
IF (@storefilter = 'ALL') 
BEGIN 
	DECLARE curDetails SCROLL CURSOR FOR SELECT StoreNumber, PurchaseOrderNumber, OrderID, FirstName, LastName,  MaterialTypeName, Status, SONumber, Style, [Size], [Description], Scheduled, ScheduleDate, Billed, Paid, BilledDate, DivisionID, DivisionGroupID, InsuranceReplacement FROM vwStatusDetailed WHERE IncludeInStatusReportAll = 1  
END
ELSE 
BEGIN 
	DECLARE curDetails SCROLL CURSOR FOR SELECT StoreNumber, PurchaseOrderNumber, OrderID, FirstName, LastName,  MaterialTypeName, Status, SONumber, Style, [Size], [Description], Scheduled, ScheduleDate, Billed, Paid, BilledDate, DivisionID, DivisionGroupID, InsuranceReplacement FROM vwStatusDetailed WHERE StoreNumber = @storefilter 
END

OPEN curDetails
SET @last_po = '' 
SET @last_orderid = 0 
SET @ponumber_group = 0  

FETCH NEXT FROM curDetails INTO @storenum, @ponumber, @orderid, @first_name, @last_name, @materialtypename, @status, @so_number, @style, @size, @description, @schedule_details, @scheduledate_details, @billed_details, @paid_details, @billeddate_details, @div_id, @div_group, @insurance_replacement
WHILE (@@FETCH_STATUS <> -1)
BEGIN
	IF (@@FETCH_STATUS <> -2)
	BEGIN
		IF (@last_po != @ponumber)
		BEGIN
			SET @ponumber_group = @ponumber_group + 1
			SET @temp_string = RTRIM(@ponumber) + SPACE(9-LEN(RTRIM(@ponumber)))
			SET @name_string = RTRIM(@last_name) + ', ' + RTRIM(@first_name) 
			SET @line_string = @temp_string + ' - ' + @name_string + ' ' 
			SET @line_string = @line_string + SPACE(40-LEN(RTRIM(LEFT(@name_string, 40)))) + '- ' + RTRIM(@materialtypename)
			INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
			SET @lineindex = @lineindex + 1     
			SET @last_po = @ponumber 
			SET @last_orderid = @orderid 
		END 
		ELSE 
		IF ( LEN(@last_po) = 4 ) 
		BEGIN 
			IF (@last_orderid != @orderid) 
			BEGIN 
				SET @ponumber_group = @ponumber_group + 1 
				SET @temp_string = RTRIM(@ponumber) + SPACE(9-LEN(RTRIM(@ponumber))) 
				SET @name_string = RTRIM(@last_name) + ', ' + RTRIM(@first_name) 
				SET @line_string = @temp_string + ' - ' + @name_string + ' ' 
				SET @line_string = @line_string + SPACE(40-LEN(RTRIM(LEFT(@name_string, 40)))) + '- ' + RTRIM(@materialtypename) 
				INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
				SET @lineindex = @lineindex + 1     
				SET @last_po = @ponumber 
				SET @last_orderid = @orderid 
			END 
		END   
		SET @so_number = ISNULL(@so_number, '') 
		SET @style = ISNULL(@style, '') 
		SET @temp_string = @style + SPACE(40 - (LEN(LEFT(@style,40)))) 
		SET @line_string = '  ' + @so_number + ' ' + STR(@size,6,2) + ' ' + @description + ' ' + @temp_string + '- ' + @status 
		SET @line_string = ISNULL(@line_string, '') 
		IF ((LEN(@line_string) > 0)) 
		BEGIN 
			INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
			SET @lineindex = @lineindex + 1 
		END   
		FETCH NEXT FROM curDetails INTO @storenum, @ponumber, @orderid, @first_name,  @last_name, @materialtypename, @status, @so_number, @style, @size,  @description, @schedule_details, @scheduledate_details, @billed_details, @paid_details, @billeddate_details, @div_id, @div_group, @insurance_replacement  
		IF (@@FETCH_STATUS = -1) 
		BEGIN 
			SET @print_notes = 1 
		END 
		ELSE IF (@last_orderid != @orderid) 
		BEGIN 
			SET @print_notes = 1 
		END
		FETCH PRIOR FROM curDetails INTO @storenum, @ponumber, @orderid, @first_name, @last_name, @materialtypename, @status, @so_number, @style, @size, @description, @schedule_details, @scheduledate_details, @billed_details, @paid_details, @billeddate_details, @div_id, @div_group, @insurance_replacement
		IF (@print_notes = 1) 
		BEGIN 
			SET @print_notes = 0              
			IF (@billed_details = 1 AND @paid_details = 0) 
			BEGIN 
				SET @line_string = 'WAIVER SENT   - ' + CONVERT(nvarchar, @billeddate_details, 101) + ' - JOB COMPLETE - NOT PAID YET' 
				INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
				SET @lineindex = @lineindex + 1 
			END 
			ELSE IF (@schedule_details = 1) 
			BEGIN 
				SET @line_string = 'SCHEDULED FOR - ' + CONVERT(nvarchar, @scheduledate_details, 101) 
				INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
				SET @lineindex = @lineindex + 1 
			END 
			ELSE 
			BEGIN 
				SET @line_string = 'NOT SCHEDULED' 
				INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
				SET @lineindex = @lineindex + 1 
			END              
			DECLARE curNotes CURSOR FOR SELECT PurchaseOrderNumber, OrderID, DateTimeEntered, NoteTypeDescription, ContactName, SW_Text, NoteText, NoteScheduled, NoteUnscheduled FROM vwPONotesDetail WHERE OrderID = @last_orderid 	 
			OPEN curNotes 	 
			FETCH NEXT FROM curNotes INTO @ponumber_notes, @orderid_notes, @datetime_notes, @action1_notes, @other_notes, @action2_notes, @comments_notes, @scheduled_notes, @unscheduled_notes
			WHILE (@@FETCH_STATUS <> -1) 
			BEGIN 
				SET @action1_notes = ISNULL(@action1_notes, '') 
				SET @action2_notes = ISNULL(@action2_notes, '') 
				SET @comments_notes = ISNULL(@comments_notes, '') 
				SET @comments_notes = REPLACE(@comments_notes, CHAR(13), ' ') 
				SET @comments_notes = REPLACE(@comments_notes, CHAR(10), ' ') 
				SET @comments_notes = REPLACE(@comments_notes, '  ', ' ') 
				SET @comments_notes = RTRIM(@comments_notes) 
				SET @other_notes = ISNULL(@other_notes, '') 
				SET @temp_string = '  ' + CONVERT(nvarchar, @datetime_notes, 101) + ' - ' + SUBSTRING(CONVERT(nvarchar, @datetime_notes, 100), 13,5) + ' ' + RIGHT(CONVERT(nvarchar, @datetime_notes), 2) + ' - ' + @action1_notes 
				IF (@action2_notes = RTRIM('OTHER')) 
				BEGIN 
					SET @action2_notes = 'SPOKE WITH ' + @other_notes 
				END
				
				SET @line_string = @temp_string + ' - ' + SPACE(55 - LEN(@temp_string)) + @action2_notes 
				INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
				SET @lineindex = @lineindex + 1 	 
				IF (@scheduled_notes = 1) 
				BEGIN 
					SET @line_string = SPACE(10) + 'SCHEDULED' 
					INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
					SET @lineindex = @lineindex + 1 
				END 	 
				
				IF (@unscheduled_notes = 1) 
				BEGIN 
					SET @line_string = SPACE(10) + 'UNSCHEDULED' 
					INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @line_string) 
					SET @lineindex = @lineindex + 1 
				END 	 
				DECLARE @str_subcomment nvarchar(1024) 
				DECLARE @str_current nvarchar(1024) 
				DECLARE @int_spaceindex integer 
				DECLARE @int_maxindex integer 	       
				SET @str_current = @comments_notes 
				IF (LEN(@str_current) > 86) 
				BEGIN 
					WHILE (LEN(@str_current) > 86) 
					BEGIN 
						SET @str_subcomment = LEFT(@str_current, 86) 
						SET @int_spaceindex = CHARINDEX(' ', REVERSE(@str_subcomment)) 
						IF (@int_spaceindex > 0) 
						BEGIN 
							SET @int_maxindex = LEN(@str_subcomment) - @int_spaceindex + 1 
							SET @temp_string = SPACE(10) + LEFT(@str_subcomment, @int_maxindex ) 
							INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @temp_string)         
							SET @lineindex = @lineindex + 1 
							SET @temp_int = LEN(@str_current) 
							SET @temp_int = @temp_int - @int_maxindex 
							SET @str_current = RIGHT(@str_current, @temp_int) 
							SET @str_current = LTRIM(@str_current) 
						END 
						ELSE 
						BEGIN 
							SET @temp_string = SPACE(10) + @str_subcomment 
							INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @temp_string)                   
							SET @lineindex = @lineindex + 1 
							SET @temp_int = LEN(@str_current) - LEN(@str_subcomment)
							SET @str_current = RIGHT(@str_current, @temp_int)
						END   
					END 
				END 	 
				IF (LEN(@str_current) > 0) 
				BEGIN 
					SET @temp_string = SPACE(10) + @str_current 
					INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, @temp_string) 
					SET @temp_int = @@IDENTITY 
					SET @lineindex = @lineindex + 1 
				END 
				INSERT INTO StatusDetails VALUES (@storenum, @ponumber, @ponumber_group, @div_id, @div_group, @insurance_replacement, @lineindex, '') 
				SET @lineindex = @lineindex + 1 
				FETCH NEXT FROM curNotes INTO @ponumber_notes, @orderid_notes, @datetime_notes, @action1_notes, @other_notes, @action2_notes, @comments_notes, @scheduled_notes, @unscheduled_notes  
			END 	 
			CLOSE curNotes 
			DEALLOCATE curNotes 
		END
		FETCH NEXT FROM curDetails INTO @storenum, @ponumber, @orderid, @first_name,  @last_name, @materialtypename, @status, @so_number, @style, @size,  @description, @schedule_details, @scheduledate_details, @billed_details, @paid_details, @billeddate_details, @div_id, @div_group, @insurance_replacement       
	END 
END 
CLOSE curDetails 
DEALLOCATE curDetails
GO
