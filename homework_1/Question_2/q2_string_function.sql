---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_2

select distinct shipName,substr(ShipName,0,instr(ShipName,'-')) as ShipNames
from 'Order'
where ShipName like '%-%'
order by shipName ASC;
