---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_6

select ProductName,CompanyName,ContactName
from(
	select ProductName,CompanyName,ContactName,min(OrderDate)
	from Product
	inner join OrderDetail on OrderDetail.ProductId = Product.Id
	inner join 'Order' on 'Order'.Id = OrderDetail.OrderId
        inner join Customer on Customer.Id = 'Order'.CustomerId
        where discontinued !=0
        group by Product.Id
)
order by ProductName ASC;
