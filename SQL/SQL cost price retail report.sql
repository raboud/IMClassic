CREATE VIEW dbo.vwBasicLaborCostPriceRetailSums
AS
SELECT     dbo.OrderBasicLaborDetails.OrderID, SUM(dbo.OrderBasicLaborDetails.InstallQuantity) AS Total, 
                      SUM(dbo.OrderBasicLaborDetails.InstallQuantity * dbo.OrderBasicLaborDetails.UnitCost) AS TotalCost, 
                      SUM(dbo.OrderBasicLaborDetails.InstallQuantity * dbo.OrderBasicLaborDetails.UnitPrice) AS TotalPrice, 
                      SUM(dbo.OrderBasicLaborDetails.InstallQuantity * dbo.OrderBasicLaborDetails.UnitRetail) AS TotalRetail, dbo.BasicLabor.UnitOfMeasureID
FROM         dbo.OrderBasicLaborDetails INNER JOIN
                      dbo.BasicLabor ON dbo.OrderBasicLaborDetails.BasicLaborID = dbo.BasicLabor.BasicLaborID
WHERE     dbo.OrderBasicLaborDetails.Deleted = 0
GROUP BY dbo.OrderBasicLaborDetails.OrderID, dbo.BasicLabor.UnitOfMeasureID


CREATE VIEW dbo.vwOptionalLaborCostPriceRetailSums
AS
SELECT     dbo.[Order Options Details].OrderID, SUM(dbo.[Order Options Details].Quantity) AS Total, 
                      SUM(dbo.[Order Options Details].Quantity * dbo.[Order Options Details].UnitCost) AS TotalCost, 
                      SUM(dbo.[Order Options Details].Quantity * dbo.[Order Options Details].UnitPrice) AS TotalPrice, 
                      SUM(dbo.[Order Options Details].Quantity * dbo.[Order Options Details].UnitRetail) AS TotalRetail, dbo.Options.UnitOfMeasureID
FROM         dbo.[Order Options Details] INNER JOIN
                      dbo.Options ON dbo.[Order Options Details].OptionID = dbo.Options.OptionID
WHERE     (dbo.[Order Options Details].Deleted = 0)
GROUP BY dbo.[Order Options Details].OrderID, dbo.Options.UnitOfMeasureID


CREATE VIEW dbo.vwCustomLaborCostPriceRetailSums
AS
SELECT     dbo.OrderCustomDetails.OrderID, SUM(dbo.OrderCustomDetails.Quanity) AS Total, 
                      SUM(dbo.OrderCustomDetails.Quanity * dbo.OrderCustomDetails.UnitCost) AS TotalCost, 
                      SUM(dbo.OrderCustomDetails.Quanity * dbo.OrderCustomDetails.UnitPrice) AS TotalPrice, 
                      SUM(dbo.OrderCustomDetails.Quanity * dbo.OrderCustomDetails.RetailPrice) AS TotalRetail, dbo.OrderCustomDetails.UnitOfMeasureID
FROM         dbo.OrderCustomDetails
WHERE     dbo.OrderCustomDetails.Deleted = 0
GROUP BY dbo.OrderCustomDetails.OrderID, dbo.OrderCustomDetails.UnitOfMeasureID


CREATE VIEW dbo.vwBasicOptionCustomCostPriceRetailSums
AS
SELECT     TOP 100 PERCENT OrderID, SUM(Total) AS Total, SUM(TotalCost) AS TotalCost, SUM(TotalPrice) AS TotalPrice, SUM(TotalRetail) AS TotalRetail, 
                      UnitOfMeasureID
FROM         (SELECT     *
                       FROM          vwBasicLaborCostPriceRetailSums
                       UNION ALL
                       SELECT     *
                       FROM         vwOptionalLaborCostPriceRetailSums
			UNION ALL
			SELECT    *
			FROM        vwCustomLaborCostPriceRetailSums) iv1
GROUP BY OrderID, UnitOfMeasureID
ORDER BY OrderID


CREATE VIEW vwCostPriceRetail AS
SELECT		dbo.MaterialType.ShortName, 
		DATEPART(YYYY, ISNULL(dbo.Orders.DateEntered, dbo.Orders.OrderDate)) AS [Year], 
		DATEPART(wk, ISNULL(dbo.Orders.DateEntered, dbo.Orders.OrderDate)) AS [Week], 
		SUM(ISNULL(dbo.vwBasicOptionCustomCostPriceRetailSums.TotalCost, 0)) AS TotalCost, 
		SUM(ISNULL(dbo.vwBasicOptionCustomCostPriceRetailSums.TotalPrice, 0)) AS TotalPrice, 
		SUM(ISNULL(dbo.vwBasicOptionCustomCostPriceRetailSums.TotalRetail, 0)) AS TotalRetail, 
		dbo.Market.MarketName, 
		dbo.Division.Division,
		dbo.Stores.StoreNumber
FROM         dbo.Orders INNER JOIN
                      dbo.MaterialType ON dbo.Orders.MaterialTypeID = dbo.MaterialType.MaterialTypeID INNER JOIN
                      dbo.Stores ON dbo.Orders.StoreID = dbo.Stores.StoreID INNER JOIN
                      dbo.Market ON dbo.Stores.MarketId = dbo.Market.MarketId INNER JOIN
                      dbo.Division ON dbo.MaterialType.DivisionID = dbo.Division.DivisionID FULL OUTER JOIN
                      dbo.vwBasicOptionCustomCostPriceRetailSums ON dbo.Orders.OrderID = dbo.vwBasicOptionCustomCostPriceRetailSums.OrderID
WHERE     (dbo.Orders.Cancelled = 0) AND (dbo.Orders.Warrenty = 0) AND (dbo.Orders.Invoice = 0) AND (dbo.Orders.Deleted = 0) AND (MaterialType.ShortName = 'CARPET' OR MaterialType.ShortName = 'F&I CARPET' OR MaterialType.ShortName = 'CERAMIC' OR MaterialType.ShortName = 'LAMINATE' OR MaterialType.ShortName = 'HARDWOOD' OR MaterialType.ShortName = 'F&I HARDWOOD' OR MaterialType.ShortName = 'VINYL')
GROUP BY dbo.MaterialType.ShortName, DATEPART(YYYY, ISNULL(dbo.Orders.DateEntered, dbo.Orders.OrderDate)), DATEPART(wk, 
                      ISNULL(dbo.Orders.DateEntered, dbo.Orders.OrderDate)), dbo.Market.MarketName, dbo.Division.Division, dbo.Stores.StoreNumber
HAVING      (DATEPART(YYYY, ISNULL(dbo.Orders.DateEntered, dbo.Orders.OrderDate)) = DATEPART(YYYY, CURRENT_TIMESTAMP))


CREATE VIEW dbo.vwWeekMaterialStores
AS
SELECT DISTINCT TOP 100 PERCENT dbo.Weeks.Weeks as [Week], dbo.MaterialType.ShortName, dbo.Division.Division, dbo.Market.MarketName, dbo.stores.storenumber
FROM         dbo.MaterialType INNER JOIN
                      dbo.Division ON dbo.MaterialType.DivisionID = dbo.Division.DivisionID INNER JOIN
                      dbo.MarketAndMaterialTypes ON dbo.MaterialType.MaterialTypeID = dbo.MarketAndMaterialTypes.MaterialTypeID INNER JOIN
                      dbo.Market ON dbo.MarketAndMaterialTypes.MarketID = dbo.Market.MarketId INNER JOIN
		      dbo.Stores ON dbo.Market.MarketID = dbo.Stores.MarketID CROSS JOIN
                      dbo.Weeks
WHERE     (dbo.Weeks.Weeks <= DATEPART(wk, CURRENT_TIMESTAMP)) AND dbo.stores.active = 1 AND (MaterialType.ShortName = 'CARPET' OR MaterialType.ShortName = 'F&I CARPET' OR MaterialType.ShortName = 'CERAMIC' OR MaterialType.ShortName = 'LAMINATE' OR MaterialType.ShortName = 'HARDWOOD' OR MaterialType.ShortName = 'F&I HARDWOOD' OR MaterialType.ShortName = 'VINYL')
ORDER BY storenumber, dbo.MaterialType.ShortName, dbo.Market.MarketName


CREATE VIEW vwWeekCostPriceRetail AS
SELECT     TOP 100 PERCENT dbo.vwWeekMaterialStores.Week, dbo.vwWeekMaterialStores.StoreNumber, dbo.vwWeekMaterialStores.ShortName,  
                      ISNULL(dbo.vwCostPriceRetail.[Year], DATEPART(YYYY, CURRENT_TIMESTAMP)) AS [Year], 
		      ISNULL(dbo.vwCostPriceRetail.TotalCost, 0) AS TotalCost,
			ISNULL(dbo.vwCostPriceRetail.TotalPrice, 0) AS TotalPrice,
			ISNULL(dbo.vwCostPriceRetail.TotalRetail, 0) AS TotalRetail,
		      dbo.vwWeekMaterialStores.Division, dbo.vwWeekMaterialStores.MarketName
FROM         dbo.vwWeekMaterialStores 
LEFT OUTER JOIN
dbo.vwCostPriceRetail ON dbo.vwWeekMaterialStores.MarketName = dbo.vwCostPriceRetail.MarketName
AND 
dbo.vwWeekMaterialStores.Division = dbo.vwCostPriceRetail.Division
AND
dbo.vwWeekMaterialStores.ShortName = dbo.vwCostPriceRetail.ShortName
AND
dbo.vwWeekMaterialStores.Week = dbo.vwCostPriceRetail.Week
AND
dbo.vwWeekMaterialStores.StoreNumber = dbo.vwCostPriceRetail.StoreNumber
order by vwCostPriceRetail.MarketName, vwCostPriceRetail.StoreNumber, vwCostPriceRetail.Division, vwCostPriceRetail.ShortName, vwCostPriceRetail.Week

