SET SERVEROUTPUT ON;
CREATE OR REPLACE PACKAGE lab5 AS
    TYPE t_record IS RECORD(
        id_stud studenti.id%TYPE,
        procent INT
    );
    TYPE t_list_record IS TABLE OF t_record INDEX BY BINARY_INTEGER;
    PROCEDURE mareste_bursa (p_lista_studs IN t_list_record);
    PROCEDURE afiseaza_istoric;
END lab5;
/

CREATE OR REPLACE PACKAGE BODY lab5 AS
    PROCEDURE mareste_bursa(p_lista_studs IN t_list_record) AS
        v_new_istoric_burse studenti.istoric_burse%TYPE;
        v_new_bursa studenti.bursa%TYPE;
    BEGIN
        FOR i in 1..p_lista_studs.COUNT LOOP
            UPDATE studenti SET bursa = 100 WHERE bursa IS NULL AND studenti.id = p_lista_studs(i).id_stud;
        END LOOP;
        
        FOR i in 1..p_lista_studs.COUNT LOOP
            UPDATE studenti SET bursa = TRUNC((bursa + (bursa * p_lista_studs(i).procent/100))) WHERE studenti.id = p_lista_studs(i).id_stud;
            SELECT istoric_burse INTO v_new_istoric_burse FROM studenti WHERE studenti.id = p_lista_studs(i).id_stud;
            
            SELECT bursa INTO v_new_bursa FROM studenti WHERE studenti.id = p_lista_studs(i).id_stud;
            v_new_istoric_burse.extend();
            v_new_istoric_burse (v_new_istoric_burse.COUNT) := v_new_bursa;
            
            UPDATE studenti SET istoric_burse = v_new_istoric_burse WHERE studenti.id = p_lista_studs(i).id_stud;
        END LOOP;
    END mareste_bursa;
    
    PROCEDURE afiseaza_istoric IS
        --CURSOR are_istoric IS SELECT nume, prenume FROM studenti WHERE studenti.istoric_burse.COUNT > 0;
        v_stud_line studenti%ROWTYPE;
    BEGIN
        FOR v_stud_line IN (SELECT * FROM studenti) LOOP
            CONTINUE WHEN v_stud_line.istoric_burse.COUNT = 0;
             DBMS_OUTPUT.PUT_LINE ('Istoric bursa pentru ' || v_stud_line.nume || ' ' || v_stud_line.prenume);
             FOR i in v_stud_line.istoric_burse.first..v_stud_line.istoric_burse.last LOOP
                DBMS_OUTPUT.PUT_LINE (i || ' ' || v_stud_line.istoric_burse(i));
             END LOOP;
        END LOOP;
    
        /*OPEN are_istoric;
        LOOP
             FETCH are_istoric INTO v_stud_line;
             EXIT WHEN are_istoric%NOTFOUND;
             DBMS_OUTPUT.PUT_LINE ('Istoric bursa pentru ' || v_stud_line.nume || ' ' || v_stud_line.prenume);
             /*FOR i in v_stud_line.istoric_burse.first..v_stud_line.istoric_burse.last LOOp
                DBMS_OUTPUT.PUT_LINE (i || ' ' || v_stud_line.istoric_burse(i));
             END LOOP;
        END LOOP;
        CLOSE are_istoric;
        */
    END afiseaza_istoric;
END lab5;
/

/*CREATE OR REPLACE TYPE t_array_burse IS TABLE OF NUMBER(6,2);
/
ALTER TABLE studenti ADD istoric_burse t_array_burse NESTED TABLE istoric_burse STORE AS istoric_burse_studenti;
/*/

--ALTER TABLE studenti DROP COLUMN istoric_burse;

/*UPDATE studenti
set istoric_burse = t_array_burse();
/*/
DECLARE
    v_lista_studs lab5.t_list_record;
BEGIN
    v_lista_studs(1).id_stud := 82;
    v_lista_studs(1).procent := 10;
    v_lista_studs(2).id_stud := 81;
    v_lista_studs(2).procent := 10;
    
    --select * from studenti where id in (12, 11);
    lab5.mareste_bursa (v_lista_studs);
    lab5.afiseaza_istoric();
END;