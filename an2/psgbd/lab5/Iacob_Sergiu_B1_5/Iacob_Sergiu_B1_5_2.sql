SET SERVEROUTPUT ON;

CREATE OR REPLACE PACKAGE exceptii
AS
    limita_bursa_depasita EXCEPTION;
    PRAGMA EXCEPTION_INIT(limita_bursa_depasita, -20001);
END exceptii;
/

CREATE OR REPLACE PROCEDURE mareste_bursa (p_id_stud IN studenti.id%TYPE) AS
    v_new_bursa studenti.bursa%TYPE;
BEGIN
    SELECT bursa INTO v_new_bursa FROM studenti WHERE id = p_id_stud;
    v_new_bursa := v_new_bursa + v_new_bursa * 0.5;
    UPDATE studenti SET bursa = v_new_bursa WHERE id = p_id_stud;
    
    IF (v_new_bursa > 3000) THEN
        v_new_bursa := 3000;
        UPDATE studenti SET bursa = v_new_bursa WHERE id = p_id_stud;
        raise exceptii.limita_bursa_depasita;
    END IF;
END mareste_bursa;
/

CREATE OR REPLACE PROCEDURE bursa_exceptie (p_id_stud IN studenti.id%TYPE) AS
    v_bursa studenti.bursa%TYPE;
    v_new_istoric studenti.istoric_burse%TYPE;
BEGIN
    SELECT bursa INTO v_bursa FROM studenti WHERE id = p_id_stud;
    SELECT istoric_burse INTO v_new_istoric FROM studenti WHERE id = p_id_stud;
    v_new_istoric.extend();
    v_new_istoric(v_new_istoric.COUNT) := v_bursa;
    UPDATE studenti SET istoric_burse = v_new_istoric WHERE id = p_id_stud;
    
    mareste_bursa (p_id_stud);
    
    SELECT bursa INTO v_bursa FROM studenti WHERE id = p_id_stud;
    DBMS_OUTPUT.PUT_LINE ('Studentul ' || p_id_stud || ' primeste bursa ' || v_bursa);
    EXCEPTION
    WHEN exceptii.limita_bursa_depasita THEN
        DBMS_OUTPUT.PUT_LINE ('Studentul ' || p_id_stud || ' a depasit bursa de 3000 de lei. I-au fost dati doar 3000 de lei, ii ajunge');
END bursa_exceptie;
/

CREATE OR REPLACE PROCEDURE top_10 AS
    v_line studenti%ROWTYPE;
    v_bursa studenti.bursa%TYPE;
    v_last_bursa studenti.bursa%TYPE;
    v_marire NUMBER;
    v_i INT;
BEGIN
    v_i := 1;
    FOR v_line IN (SELECT * FROM studenti ORDER BY bursa DESC) LOOP
        CONTINUE WHEN v_line.bursa IS NULL;
        EXIT WHEN v_i > 10;
        v_i := v_i + 1;
        v_bursa := v_line.bursa;
        IF (v_line.istoric_burse.COUNT > 0)
        THEN
            v_last_bursa := v_line.istoric_burse(v_line.istoric_burse.COUNT);
            v_marire := (v_bursa - v_last_bursa)/v_last_bursa;
        ELSE
            v_last_bursa := 0;
            v_marire := 0;
        END IF;
        DBMS_OUTPUT.PUT_LINE ('Stud ' || v_line.id || ' are bursa ' || v_bursa || ' si avea ' || v_last_bursa || ' deci a avut o marire de ' || v_marire);
    END LOOP;
END top_10;
/

DECLARE
    v_bursa studenti.bursa%TYPE;
BEGIN
    FOR i in 81..181 LOOP
        bursa_exceptie (i);
    END LOOP;
    
    --top_10();
END;