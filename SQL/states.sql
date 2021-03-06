if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[FK_tblCompany_tblStateNames]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [dbo].[tblCompany] DROP CONSTRAINT FK_tblCompany_tblStateNames
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[FK_tblMembers_tblStateNames]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [dbo].[tblMembers] DROP CONSTRAINT FK_tblMembers_tblStateNames
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[tblStateNames]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[tblStateNames]
GO

CREATE TABLE [dbo].[tblStateNames] (
	[ID] [smallint] NOT NULL ,
	[Name] [varchar] (25) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[Abbreviation] [char] (2) COLLATE SQL_Latin1_General_CP1_CI_AS NULL 
) ON [PRIMARY]
GO

