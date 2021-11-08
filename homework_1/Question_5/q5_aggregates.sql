---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_5

select CategoryName,count(*) as CategoryCount,
	round(avg(UnitPrice),2) as AveragePrice,
	min(UnitPrice) as MinUnitPrice,
	max(UnitPrice) as MaxUnitPrice,
	sum(UnitsOnOrder) as TotalUnitPrice
from Category inner join Product on Category.Id = Product.CategoryId
group by CategoryId
having CategoryCount > 10
order by CategoryId;
