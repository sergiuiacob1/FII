set serveroutput on;
--create table producers(
--    id_producer int primary key,
--    nume VARCHAR2(20)
--);
--/
--
--create table items(
--    id_item INT primary key,
--    value INT,
--    id_p INT,
--    foreign key(id_p) references producers(id_producer)
--);
--/
--
--create view t_view as
--select p.id_producer, p.nume, i.id_item, i.value from producers p join items i on p.id_producer = i.id_p;
--/

create or replace trigger insert_view instead of insert on t_view
DECLARE
    v_count INT;
begin
    select count(*) into v_count from producers where id_producer = :new.id_producer;
    IF (v_count = 0) THEN
        insert into producers values (:new.id_producer, :new.nume);
    END IF;
    
    select count(*) into v_count from items where id_item = :new.id_item;
    IF (v_count = 0) THEN
        insert into items values (:new.id_item, :new.value, :new.id_producer);
    END IF;
    
end insert_view;
/

create or replace trigger update_view instead of update on t_view
begin
    update items set value = :NEW.value;
end update_view;
/

create or replace trigger delete_view instead of delete on t_view
begin
    delete from items where id_item = :OLD.id_item or id_p = :OLD.id_producer;
    delete from producers where id_producer = :OLD.id_producer;
end update_view;
/

begin
    insert into t_view values (10, 'Ion', 1, 100);
    insert into t_view values (11, 'Gheorghe', 2, 200);
    delete from t_view where id_producer = 10;
    select * from producers;
    select * from items;
    select * from t_view;
    update t_view set id_item = 3 where id_producer = 11;
end;