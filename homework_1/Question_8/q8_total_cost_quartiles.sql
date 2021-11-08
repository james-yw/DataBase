---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_8

select CompanyName,CustomerId,totalExpenditure
from(
	select*
	,NTILE(4) OVER (ORDER BY totalExpenditure ASC) as quartile
	from(
		select ifnull(CompanyName,'MISSING_NAME') as CompanyName
		,CustomerId
		,round(sum(UnitPrice * Quantity),2) as totalExpenditure
		from 'Order' 
		inner join OrderDetail on 'Order'.Id = OrderDetail.OrderId
		left join Customer on Customer.Id = 'Order'.CustomerId
		group by CustomerId
		)
	)
where quartile=1
order by totalExpenditure ASC;
