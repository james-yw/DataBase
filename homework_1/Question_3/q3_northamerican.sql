---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_3

select Id,ShipCountry,
	case
		when ShipCountry in ('USA','Mexico','Canada')
		then 'NorthAmerica'
		else 'OtherPlace'
	end
	as area
from 'Order'
where Id >=15445
order by Id Asc
limit 20;
