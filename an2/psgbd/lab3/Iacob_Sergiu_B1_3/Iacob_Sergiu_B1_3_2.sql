SET SERVEROUTPUT on;
CREATE OR REPLACE PROCEDURE make_indexes AS
BEGIN
     DBMS_UTILITY.EXEC_DDL_STATEMENT('CREATE INDEX idx_note_id_stud ON note(id_student)');
END make_indexes;
/

CREATE OR REPLACE FUNCTION medie (p_id IN studenti.id%TYPE) RETURN NUMBER AS
    v_medie NUMBER;
BEGIN
    SELECT avg(note.valoare) INTO v_medie
    FROM note
    WHERE note.id_student = p_id;
    RETURN TRUNC(v_medie);
END medie;
/

CREATE OR REPLACE PROCEDURE friends AS
    v_medie1 NUMBER;
    v_medie2 NUMBER;
    v_nr_stud INT;
    v_id studenti.id%TYPE;
    v_friend_line prieteni%ROWTYPE;
    type t_array is varray(3000) of NUMBER;
    v_medii t_array := t_array();
BEGIN
    SELECT COUNT(*) INTO v_nr_stud FROM studenti;
    v_medii.extend(v_nr_stud + 1);
    
    FOR v_id IN (SELECT id FROM studenti) LOOP
        SELECT medie(v_id.id) INTO v_medii(v_id.id) FROM dual;
    END LOOP;
    
    FOR v_friend_line IN (SELECT * FROM prieteni)
    LOOP
        v_medie1 := v_medii(v_friend_line.id_student1);
        v_medie2 := v_medii(v_friend_line.id_student2);
        IF (v_medie1 = v_medie2) THEN
            DBMS_OUTPUT.PUT_LINE (v_friend_line.id_student1 || ' ' || v_friend_line.id_student2);
        END IF;
    END LOOP;
END friends;
/

BEGIN
    --make_indexes();
    --COMMIT;
    friends();
    
    --executa urmatoarele pt a face curatenia de primavara
    /*
    DBMS_UTILITY.EXEC_DDL_STATEMENT('DROP INDEX idx_note_id_stud');
    DBMS_UTILITY.EXEC_DDL_STATEMENT('DROP PROCEDURE make_indexes');
    DBMS_UTILITY.EXEC_DDL_STATEMENT('DROP FUNCTION medie');
    DBMS_UTILITY.EXEC_DDL_STATEMENT('DROP PROCEDURE friends');
    */
END;