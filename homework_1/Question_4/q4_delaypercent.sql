---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_4

select CompanyName,round(DelayDate*100.0/TotalDate, 2) as Precentage
from(
	select ShipVia,count(*) as DelayDate
	from 'Order'
	where ShippedDate > RequiredDate
	group by ShipVia
	) as Delay
inner join(
	select ShipVia,count(*) as TotalDate
	from 'Order'
	group by ShipVia
	) as Total on Delay.ShipVia = Total.ShipVia
inner join shipper on shipper.Id = Total.ShipVia
order by Precentage DESC;
