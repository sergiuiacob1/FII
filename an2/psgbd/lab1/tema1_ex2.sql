set serveroutput on;
<<global>>
DECLARE
    c_data_nastere CONSTANT VARCHAR(20) := '07-07-1978';
    v_nr_zile int;
    v_nr_luni int;
    v_zi VARCHAR(20);
BEGIN
    select (EXTRACT (day from sysdate) - EXTRACT (day from to_date(c_data_nastere, 'DD-MM-YYYY'))) into v_nr_zile from dual;
    select TRUNC(months_between (sysdate, to_date(c_data_nastere, 'DD-MM-YYYY'))) into v_nr_luni from dual;
    select to_char (to_date (c_data_nastere, 'DD-MM-YYYY'), 'Day') into v_zi from dual;

    DBMS_OUTPUT.PUT_LINE('Au trecut ' || v_nr_zile || ' zile');
    DBMS_OUTPUT.PUT_LINE('Au trecut ' || v_nr_luni || ' luni');
    DBMS_OUTPUT.PUT_LINE('Ziua a fost ' || v_zi);
END;