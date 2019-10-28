set serveroutput on;
<<global>>
DECLARE
    v_nume_familie studenti.nume%TYPE := '&nume_familie';
    v_nr_results int;
    v_id studenti.id%TYPE;
    v_prenume studenti.prenume%TYPE;
    v_nota_min note.valoare%TYPE;
    v_nota_max note.valoare%TYPE;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Se cauta numele de familie ' || global.v_nume_familie);
    select count(*) into v_nr_results from studenti where nume = global.v_nume_familie;
    IF (v_nr_results = 0)
        THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun student cu numele ' || global.v_nume_familie);
        ELSE
            DBMS_OUTPUT.PUT_LINE('S-au gasit ' || v_nr_results || ' cu acest nume');
            select id, prenume into v_id, v_prenume from (select id, prenume from studenti where nume = global.v_nume_familie order by prenume) where ROWNUM = 1;
            DBMS_OUTPUT.PUT_LINE('Primul studenti are id-ul ' || v_id || ' si prenumele ' || v_prenume);
            select min(valoare), max(valoare) into v_nota_min, v_nota_max
            from studenti join note on studenti.id = note.id_student
            where studenti.id = v_id
            group by studenti.id;
            DBMS_OUTPUT.PUT_LINE('Nota min: ' || v_nota_min || ' si nota max: ' || v_nota_max);
            DBMS_OUTPUT.PUT_LINE('Exponentiere: ' || v_nota_max ** v_nota_min);
    END IF;
END;