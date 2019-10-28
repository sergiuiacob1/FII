SET SERVEROUTPUT ON;
create or replace package global_package is
    TYPE t_array is varray(1000030) of INT;
    ciurArray t_array;
    primes t_array;
    nr_primes INT;
end;
/

create or replace procedure ciur as
    v_i INT;
    v_j INT;
begin
    global_package.nr_primes := 0;
    global_package.ciurArray := global_package.t_array();
    global_package.primes := global_package.t_array();
    global_package.ciurArray.extend();
    global_package.ciurArray(1) := 0;
    global_package.ciurArray.extend(1000010, 1);
    global_package.primes.extend(100000);
    v_i := 2;
    while (v_i <= 1000000) loop
        if (global_package.ciurArray(v_i) = 0) then
            global_package.nr_primes := global_package.nr_primes + 1;
            global_package.primes(global_package.nr_primes) := v_i;
            v_j := v_i;
            while (v_i * v_j <= 1000000) loop
                global_package.ciurArray(v_i * v_j) := 1;
                v_j := v_j + 1;
            end loop;
        end if;
        v_i := v_i + 1;
    end loop;
end ciur;
/

create or replace procedure populeaza_tabele as
    v_i int;
    v_x number (6, 2);
    v_y number (6, 2);
    v_h number (6);
begin
    for v_i in 1..10000000 loop
        v_x := trunc ((DBMS_RANDOM.VALUE (0, 4001)), 2);
        v_y := trunc ((DBMS_RANDOM.VALUE (0, 4001)), 2);
        v_h := trunc (DBMS_RANDOM.VALUE (0, 4001));
        insert into padure values (v_x, v_y, v_h);
    end loop;

    for v_i in 1..10 loop
        v_x := trunc ((DBMS_RANDOM.VALUE (0, 4001)), 2);
        v_y := trunc ((DBMS_RANDOM.VALUE (0, 4001)), 2);
        insert into pozitii values (v_x, v_y);
    end loop;

end populeaza_tabele;

create or replace procedure sterge_tot as
begin
--  delete * from padure;
--  delete * from pozitii;
    null;
end sterge_tot;

--CREATE TABLE padure(x NUMBER(6,2), y NUMBER(6,2), h NUMBER(6))
--/
--CREATE TABLE pozitii(x NUMBER(6,2), y NUMBER(6,2))
--/

BEGIN
    ciur();
    populeaza_tabele();

    sterge_tot();
END;
