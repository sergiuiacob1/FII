SET SERVEROUTPUT ON;

CREATE OR REPLACE PACKAGE facultate AS
    nume_facultate VARCHAR2(50);
    CURSOR lista_studenti IS SELECT nr_matricol, nume, prenume, grupa, an FROM studenti ORDER BY nume;
    PROCEDURE varsta_student (p_id_stud IN INT, v_ani OUT INT, v_luni OUT INT, v_zile OUT INT);
    PROCEDURE adauga_student_random;
    PROCEDURE sterge_student (p_id_stud IN INT);
    PROCEDURE info_student (p_id_stud IN INT);
END facultate;
/

CREATE OR REPLACE PACKAGE BODY facultate AS
    PROCEDURE info_student (p_id_stud IN INT) IS
        v_line studenti%ROWTYPE;
        v_prieteni_line studenti%ROWTYPE;
        v_ani INT;
        v_luni INT;
        v_zile INT;
        CURSOR note_stud (p_id_stud IN INT) IS SELECT * from note where id_student = p_id_stud;
        v_note_line note_stud%ROWTYPE;
        v_titlu_curs cursuri.titlu_curs%TYPE;
        v_medie NUMBER;
        v_rank NUMBER;
    BEGIN
        select * into v_line from studenti where id = p_id_stud;
        DBMS_OUTPUT.PUT_LINE ('Student ' || v_line.nume || ' ' || v_line.prenume || ' in anul ' || v_line.an || ' cu nr matricol ' || v_line.nr_matricol);
        varsta_student (p_id_stud, v_ani, v_luni, v_zile);
        DBMS_OUTPUT.PUT_LINE (v_ani || ' ani ' || v_luni || ' luni ' || v_zile || ' zile.');
        
        DBMS_OUTPUT.PUT_LINE ('Note student: ');
        OPEN note_stud(p_id_stud);
        LOOP
            FETCH note_stud into v_note_line;
            EXIT WHEN note_stud%NOTFOUND;
            SELECT titlu_curs INTO v_titlu_curs FROM cursuri WHERE id = v_note_line.id_curs;
            DBMS_OUTPUT.PUT_LINE (v_note_line.valoare || ' la materia ' || v_titlu_curs);
        END LOOP;
        CLOSE note_stud;
        
        select avg(valoare) into v_medie from note where id_student = p_id_stud;
        DBMS_OUTPUT.PUT_LINE ('Medie: ' || v_medie);
        
        SELECT (count(*) + 1) INTO v_rank from
            (select studenti.id from studenti JOIN note on studenti.id = note.id_student
            where (studenti.grupa = v_line.grupa AND studenti.an = v_line.an)
            group by studenti.id
            having avg(note.valoare) > v_medie);
        DBMS_OUTPUT.PUT_LINE ('Rank in grupa: ' || v_rank);
        
        DBMS_OUTPUT.PUT_LINE ('Prieteni: ');
        FOR v_prieteni_line in (SELECT * FROM studenti
            WHERE studenti.id in (select id_student1 from prieteni where id_student2 = p_id_stud) 
            OR studenti.id in (select id_student2 from prieteni where id_student1 = p_id_stud))
        LOOP
            DBMS_OUTPUT.PUT_LINE (v_prieteni_line.nume || ' ' || v_prieteni_line.prenume);
        END LOOP;
        
        /*SELECT ROWNUM INTO v_rank FROM
            (SELECT studenti.id as "id_stud" from studenti JOIN note on studenti.id = note.id_student
                where (studenti.grupa = v_line.grupa AND studenti.an = v_line.an)
                group by studenti.id
                order by avg(note.valoare))
        where studenti.id = p_id_stud;*/
        
    END info_student;

    PROCEDURE sterge_student (p_id_stud IN INT) IS
    BEGIN
        delete from prieteni where id_student1 = p_id_stud OR id_student2 = p_id_stud;
        delete from note where id_student = p_id_stud;
        delete from studenti where id = p_id_stud;
    END sterge_student;

    PROCEDURE varsta_student (p_id_stud IN INT, v_ani OUT INT, v_luni OUT INT, v_zile OUT INT) IS
        v_data_nastere DATE;
    BEGIN
        SELECT data_nastere INTO v_data_nastere FROM studenti where id = p_id_stud;
        
        select ABS ((EXTRACT (day from sysdate) - EXTRACT (day from to_date(v_data_nastere, 'DD-MM-YYYY')))) into v_zile from dual;
        select TRUNC(months_between (sysdate, v_data_nastere)/12) into v_ani from dual;
        select ABS((extract (Month from v_data_nastere) - extract(Month from sysdate))) into v_luni from dual;
    END varsta_student;
    
    PROCEDURE adauga_note_random (p_id IN studenti.id%TYPE) AS
        v_cursuri_line cursuri%ROWTYPE;
        v_an studenti.an%TYPE;
        v_nota_valoare note.valoare%TYPE;
        v_nota_data_notare note.data_notare%TYPE;
        v_nota_id note.id%TYPE;
        v_nota_id_curs note.id_curs%TYPE;
    BEGIN
        SELECT an INTO v_an from studenti where id = p_id;
        
        FOR v_cursuri_line in (SELECT * FROM cursuri) LOOP
            IF (v_cursuri_line.an < v_an) THEN
                --trebuie sa aibe 2 note
                select (max (id) + 1) into v_nota_id from note;
                SELECT TRUNC (DBMS_RANDOM.VALUE (1, 11)) into v_nota_valoare from dual;
                SELECT * INTO v_nota_data_notare FROM (SELECT data_notare from note where extract (Month from data_notare) = 2 ORDER BY DBMS_RANDOM.VALUE) WHERE ROWNUM = 1;
                
                DBMS_OUTPUT.PUT_LINE ('Adaugat nota pentru ' || p_id || ' cu ' || v_nota_id || ' ' || v_nota_valoare || ' ' || v_nota_data_notare);
                INSERT INTO note VALUES (v_nota_id, p_id, v_cursuri_line.id, v_nota_valoare, v_nota_data_notare, sysdate, sysdate);
                
                v_nota_id := v_nota_id  + 1;
                SELECT * INTO v_nota_data_notare FROM (SELECT data_notare from note where extract (Month from data_notare) = 7 ORDER BY DBMS_RANDOM.VALUE) WHERE ROWNUM = 1;
                DBMS_OUTPUT.PUT_LINE ('Adaugat nota pentru ' || p_id || ' cu ' || v_nota_id || ' ' || v_nota_valoare || ' ' || v_nota_data_notare);
                insert into note VALUES (v_nota_id, p_id, v_cursuri_line.id, v_nota_valoare, v_nota_data_notare, sysdate, sysdate);
            END IF;
        END LOOP;
    END adauga_note_random;
    
    PROCEDURE adauga_student_random IS
        v_nume studenti.nume%TYPE;
        v_prenume studenti.prenume%TYPE;
        v_an studenti.an%TYPE;
        v_email studenti.email%TYPE;
        v_grupa studenti.grupa%TYPE;
        v_bursa studenti.bursa%TYPE;
        v_bursa_min studenti.bursa%TYPE;
        v_bursa_max studenti.bursa%TYPE;
        v_data_nastere studenti.data_nastere%TYPE;
        v_nr_matricol studenti.nr_matricol%TYPE;
        v_id studenti.id%TYPE;
    BEGIN
        select (max(studenti.id) + 1) into v_id from studenti;
        select * into v_nume from (select nume from studenti order by DBMS_RANDOM.VALUE) where ROWNUM = 1;
        select * into v_prenume from (select prenume from studenti order by DBMS_RANDOM.VALUE) where ROWNUM = 1;
        select (TRUNC(DBMS_RANDOM.VALUE (0, 3)) + 1) into v_an from dual;
        IF (DBMS_RANDOM.VALUE (1, 10) <= 5) THEN
            SELECT ('A' || to_char (TRUNC(DBMS_RANDOM.VALUE (0, 7) + 1))) into v_grupa from dual;
        ELSE
            SELECT ('B' || to_char (TRUNC(DBMS_RANDOM.VALUE (0, 7) + 1))) into v_grupa from dual;
        END IF;
        
        IF (DBMS_RANDOM.VALUE (0, 5) <= 1) THEN
            v_bursa := null;
        ELSE
            SELECT MIN(bursa) INTO v_bursa_min from studenti where bursa is not null;
            SELECT MAX(bursa) INTO v_bursa_max from studenti where bursa is not null;
            v_bursa := TRUNC(DBMS_RANDOM.VALUE (v_bursa_min, v_bursa_max));
        END IF;
        
        SELECT (lower(v_prenume) || lower(v_nume) || '@info.uaic.ro') into v_email from dual;
        SELECT ((select * from (select data_nastere from studenti order by DBMS_RANDOM.VALUE) where ROWNUM = 1) + TRUNC (DBMS_RANDOM.VALUE (1, 10000))) into v_data_nastere from dual;
        
        FOR v_i in 1..6 LOOP
            IF (DBMS_RANDOM.VALUE (1, 10) <= 5) THEN
                --cifra
                v_nr_matricol := concat (v_nr_matricol, to_char (TRUNC (DBMS_RANDOM.VALUE (0, 10))));
            ELSE
                --litera
                v_nr_matricol := concat (v_nr_matricol, CHR(TRUNC(dbms_random.value(65, 70))));
            END IF;
        END LOOP;
        
        DBMS_OUTPUT.PUT_LINE ('Adaugat studentul ' || v_id || ' ' || v_nume || ' ' || v_prenume || ' ' || v_an || ' ' || v_grupa || ' ' || v_bursa || ' ' || v_email || ' ' || v_data_nastere || ' ' || v_nr_matricol);
        INSERT INTO studenti VALUES(v_id, v_nr_matricol, v_nume, v_prenume, v_an, v_grupa, v_bursa, v_data_nastere, v_email, sysdate, sysdate);
        
        adauga_note_random (v_id);
    END adauga_student_random;
END facultate;
/

DECLARE
v_zile INT;
v_luni INT;
v_ani INT;
BEGIN
    --facultate.nume_facultate := 'Facultatea de Info Iasi';
    --facultate.varsta_student (81, v_ani, v_luni, v_zile);a
    --DBMS_OUTPUT.PUT_LINE (v_ani || ' ' || v_luni || ' ' || v_zile);
    --facultate.adauga_student_random();
   -- facultate.info_student (81);
    facultate.sterge_student (1);
    --facultate.info_student(1);
    --delete from note where id_student > 1025;
    --delete from studenti where id > 1025;
END;