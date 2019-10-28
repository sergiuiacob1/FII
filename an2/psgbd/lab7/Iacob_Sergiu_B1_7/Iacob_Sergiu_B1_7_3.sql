 set serveroutput on;
--
--create table log_destruction(
--    id INT,
--    username VARCHAR2(100),
--    data DATE
--);
--/

create or replace procedure insereaza_in_log is
PRAGMA AUTONOMOUS_TRANSACTION;
    v_nextId INT;
    v_username VARCHAR2(100);
begin
    select count(*) + 1 into v_nextId from log_destruction;
    select user into v_username from dual;
    insert into log_destruction values (v_nextId, v_username, sysdate);
    COMMIT;
end insereaza_in_log;
/

CREATE OR REPLACE TRIGGER trigger_drop_raise BEFORE DROP ON DATABASE
BEGIN
    insereaza_in_log();
    RAISE_APPLICATION_ERROR (
      num => -20000,
      msg => 'You can''t drop tables. Disable trigger trigger_drop_raise to do so.');
end trigger_drop_raise;
/

CREATE OR REPLACE TRIGGER trigger_truncate_raise BEFORE TRUNCATE ON DATABASE
BEGIN
    insereaza_in_log();
    RAISE_APPLICATION_ERROR (
      num => -20001,
      msg => 'You can''t truncate tables. Disable trigger trigger_truncate_raise to do so.');
end trigger_truncate_raise;
/

CREATE OR REPLACE TRIGGER trigger_alter_raise BEFORE ALTER ON DATABASE
BEGIN
    insereaza_in_log();
    RAISE_APPLICATION_ERROR (
      num => -20002,
      msg => 'You can''t alter tables. Disable trigger trigger_alter_raise to do so.');
end trigger_alter_raise;
/

drop table aux_table;
truncate table aux_table;

select * from log_destruction order by data;