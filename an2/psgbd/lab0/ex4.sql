select * from (select s1.grupa, (select count(*) from prieteni p1
    where p1.id_student1 in (select id from studenti where grupa = s1.grupa)
    and p1.id_student2 in (select id from studenti where grupa = s1.grupa))/
    (select count(*) from studenti s2 where s1.grupa = s2.grupa) "raport"
from studenti s1
group by s1.grupa
order by 2 desc)