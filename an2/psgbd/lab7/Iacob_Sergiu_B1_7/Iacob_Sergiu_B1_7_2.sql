set serveroutput on;
--
--create table log_table(
--    id INT,
--    nr_updated INT,
--    data DATE
--);
--/

create or replace trigger trigger_update_note
FOR UPDATE on note
compound trigger
    v_nextId INT;
    v_totalUpdated INT;
    
BEFORE STATEMENT IS
BEGIN
    v_totalUpdated := 0;
END BEFORE STATEMENT;

BEFORE EACH ROW IS
BEGIN
    if (:NEW.valoare <= :OLD.valoare) then
        :NEW.valoare := :OLD.valoare;
    else
        v_totalUpdated := v_totalUpdated + 1;
    END IF;
END BEFORE EACH ROW;

AFTER STATEMENT IS
BEGIN
    select count (*) + 1 into v_nextId from log_table;
    insert into log_table values (v_nextId, v_totalUpdated, sysdate);
END AFTER STATEMENT;
END trigger_update_note;
/

begin
    update note set valoare = 5 where id < 100;
    select * from log_table;
end;