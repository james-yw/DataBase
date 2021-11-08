---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_7

select Id,OrderDate,PreOrderDate,round(julianday(OrderDate)-julianday(PreOrderDate),2) as DifferentDate
from(
	select Id,OrderDate,lag(OrderDate,1,OrderDate) over (order by OrderDate ASC) as PreOrderDate
	from 'Order'
	where CustomerId = 'BLONP'
)
order by OrderDate ASC
limit 10;

