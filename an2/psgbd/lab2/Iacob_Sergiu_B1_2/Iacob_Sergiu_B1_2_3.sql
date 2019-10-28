select T1.id, T1.nume, T1.prenume, T1.an, c.titlu_curs, n.valoare, T1."avg" from ( select * from (select  s.id, s.nume, s.prenume, s.an, 
avg(n.valoare) as "avg" from studenti s join note n on n.id_student=s.id group by s.id, s.nume, s.prenume, s.an, s.nume, s.prenume
having count(n.valoare) >= 3 order by avg(n.valoare) desc, s.an desc, s.nume asc, s.prenume asc ) where rownum = 1) T1 join note n on
n.id_student = T1.id join cursuri c on c.id = n.id_curs;

/*SET SERVEROUTPUT ON;
DECLARE
    v_stud_line studenti%ROWTYPE;
    v_best_stud_line studenti%ROWTYPE;
    v_stud_average NUMBER;
    v_best_stud_average NUMBER;
    v_sum_note INT;
    v_count_note INT;
    v_note_line note%ROWTYPE;
    v_titlu_curs cursuri.titlu_curs%TYPE;
    
BEGIN
    v_best_stud_average := 0;
    FOR v_stud_line in (SELECT * FROM studenti ORDER BY nume, prenume) LOOP --aici tratez cazul in care amandoi sunt egali, il iau pe primul in ord. alfabetica
        v_count_note := 0;
        v_sum_note :=0;
        FOR v_note_line in (SELECT * FROM note WHERE id_student = v_stud_line.id) LOOP
            v_count_note := v_count_note + 1;
            v_sum_note := v_sum_note + v_note_line.valoare;
        END LOOP;
        
        v_stud_average := v_sum_note / v_count_note;
        IF ((v_stud_average = v_best_stud_average AND v_stud_line.an > v_best_stud_line.an)
            OR (v_count_note >= 3 AND v_stud_average > v_best_stud_average)) THEN
            v_best_stud_line := v_stud_line;
            v_best_stud_average := v_stud_average;
        END IF;
    END LOOP;
    
    FOR v_note_line in (SELECT * FROM note WHERE id_student = v_best_stud_line.id) LOOP
        SELECT titlu_curs INTO v_titlu_curs from cursuri where v_note_line.id_curs = cursuri.id;
        DBMS_OUTPUT.PUT_LINE (v_best_stud_line.nume || ' ' || v_best_stud_line.prenume || ' ' || v_best_stud_line.an || ' ' ||  v_note_line.valoare || ' ' || v_titlu_curs);
    END LOOP;
END;
*/