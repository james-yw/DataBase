---------------------------
-- Student_name:YangWen
-- Student_Id:2019141460358
---------------------------

--Question_9

select RegionDescription,FirstName,LastName,max(BirthDate) as BirthDay
from Employee
	inner join EmployeeTerritory on Employee.Id = EmployeeId
	inner join Territory on Territory.Id = TerritoryId
	inner join Region on Region.Id = RegionId
group by RegionId
order by RegionId;
