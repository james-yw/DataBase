---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_10
select GROUP_CONCAT(ProductName, ',') as ProductName 
from(
	select ProductName
	from Customer
		inner join 'Order' on Customer.Id = CustomerId
		inner join OrderDetail on 'Order'.Id = OrderId
		inner join Product on Product.Id = ProductId
	where Customer.Companyname = 'Queen Cozinha'
		and substr(OrderDate,0,instr(OrderDate,' ')) = '2014-12-25'
	order by ProductId ASC
);




