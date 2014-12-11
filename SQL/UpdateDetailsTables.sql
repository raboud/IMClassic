BEGIN TRANSACTION
SET QUOTED_IDENTIFIER ON
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
SET ARITHABORT ON
SET NUMERIC_ROUNDABORT OFF
SET CONCAT_NULL_YIELDS_NULL ON
SET ANSI_NULLS ON
SET ANSI_PADDING ON
SET ANSI_WARNINGS ON
COMMIT
BEGIN TRANSACTION
ALTER TABLE dbo.Orders ADD
	Reviewed bit NOT NULL CONSTRAINT DF_Orders_Reviewed DEFAULT 0,
	ReviewedBy int NULL,
	ReviewedDate datetime NULL
GO

ALTER TABLE dbo.OrderBasicLaborDetails ADD
	Reviewed bit NOT NULL CONSTRAINT DF_OrderBasicLaborDetails_Reviewed DEFAULT 0,
	ReviewedBy int NULL,
	ReviewedDate datetime NULL
GO

ALTER TABLE dbo.OrderCustomDetails ADD
	Reviewed bit NOT NULL CONSTRAINT DF_OrderCustomDetails_Reviewed DEFAULT 0,
	ReviewedBy int NULL,
	ReviewedDate datetime NULL
GO

ALTER TABLE dbo.[Order Options Details] ADD
	Reviewed bit NOT NULL CONSTRAINT [DF_Order Options Details_Reviewed] DEFAULT 0,
	ReviewedBy int NULL,
	ReviewedDate datetime NULL
GO
ALTER TABLE dbo.OrderSOMerchandiseDetails ADD
	Reviewed bit NOT NULL CONSTRAINT [DF_OrderSOMerchandiseDetails_Reviewed] DEFAULT 0,
	ReviewedBy int NULL,
	ReviewedDate datetime NULL
GO
ALTER TABLE dbo.OrderRegMerchandiseDetails ADD
	Reviewed bit NOT NULL CONSTRAINT [DF_OrderRegMerchandiseDetails_Reviewed] DEFAULT 0,
	ReviewedBy int NULL,
	ReviewedDate datetime NULL
GO
ALTER TABLE dbo.Discrepancies ADD CONSTRAINT
	DF_Discrepancies_PONumber DEFAULT '' FOR PONumber
GO
ALTER TABLE dbo.Discrepancies ADD CONSTRAINT
	DF_Discrepancies_CustOrStoreID DEFAULT -1 FOR CustOrStoreID
GO
UPDATE Orders SET Reviewed = 1
GO
UPDATE [Order Options Details] SET Reviewed = 1
GO
UPDATE OrderCustomDetails SET Reviewed = 1
GO
UPDATE OrderBasicLaborDetails SET Reviewed = 1
GO
UPDATE OrderSOMerchandiseDetails SET Reviewed = 1
GO
UPDATE OrderRegMerchandiseDetails SET Reviewed = 1
GO
ALTER TABLE dbo.Discrepancies ADD 
	OrderID int NOT NULL CONSTRAINT DF_Discrepancies_OrderID DEFAULT -1, 
	DetailID int DEFAULT NULL, 
	Reviewed bit NOT NULL CONSTRAINT DF_Discrepancies_Reviewed DEFAULT 0, 
	ReviewedBy int NOT NULL CONSTRAINT DF_Discrepancies_ReviewedBy DEFAULT -1, 
	DateReviewed datetime NULL
GO
COMMIT
