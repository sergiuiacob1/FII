SET SERVEROUTPUT ON;
/*CREATE TABLE erasmus(
    nr_matricol VARCHAR2(6) NOT NULL PRIMARY KEY,
    tara INT NOT NULL
);
COMMIT;

CREATE UNIQUE INDEX idx_erasmus_nr_matricol ON erasmus(nr_matricol);
COMMIT;*/

CREATE OR REPLACE FUNCTION add_one_erasmus_stud (p_nr_matricol IN studenti.nr_matricol%TYPE, p_id_tara IN INT)
    RETURN INT
AS
BEGIN
    INSERT INTO erasmus VALUES (p_nr_matricol, p_id_tara);
    RETURN 1;
    
    EXCEPTION
    WHEN DUP_VAL_ON_INDEX THEN
        RETURN 0;
END add_one_erasmus_stud;
/

CREATE OR REPLACE PROCEDURE add_erasmus_studs AS
    v_id_tara INT;
    v_nr_matricol studenti.nr_matricol%TYPE;
BEGIN
    FOR i in 1..100 LOOP
        SELECT * INTO v_nr_matricol FROM (SELECT nr_matricol FROM studenti ORDER BY DBMS_RANDOM.VALUE) WHERE ROWNUM = 1;
        DBMS_OUTPUT.PUT_LINE (v_nr_matricol);
        v_id_tara := TRUNC(DBMS_RANDOM.VALUE (0, 100) + 1);
        IF (add_one_erasmus_stud (v_nr_matricol, v_id_tara) = 1) THEN
            DBMS_OUTPUT.PUT_LINE ('Studentul cu nr_matricol ' || v_nr_matricol || ' care s-a dus in tara cu ID-ul ' || v_id_tara || ' copiat cu succes.');
        ELSE
            DBMS_OUTPUT.PUT_LINE ('Studentul cu nr_matricol ' || v_nr_matricol || ' care s-a dus in tara cu ID-ul ' || v_id_tara || ' NU a fost inserat.');
        END IF;
    END LOOP;
END add_erasmus_studs;
/

BEGIN
    add_erasmus_studs();
END;