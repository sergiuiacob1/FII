set serveroutput on;

create or replace procedure read_stud as
    v_fisier UTL_FILE.FILE_TYPE;
    v_line_stud studenti%ROWTYPE;
BEGIN
    v_fisier := UTL_FILE.FOPEN('MYDIR', 'stud.txt', 'R');
    LOOP
    BEGIN
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.id);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.nr_matricol);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.nume);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.prenume);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.an);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.grupa);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.bursa);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.data_nastere);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.email);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.created_at);
        UTL_FILE.GET_LINE(v_fisier, v_line_stud.updated_at);
        insert into studenti values v_line_stud;
        commit;
    EXCEPTION
         WHEN DUP_VAL_ON_INDEX then
            dbms_output.put_line ('Student already exists. will not insert this one');
    END;
    END LOOP;
    
    EXCEPTION
        WHEN NO_DATA_FOUND then
            dbms_output.put_line ('wrote studs to table');
            UTL_FILE.FCLOSE(v_fisier);
            COMMIT;
END read_stud;
/

create or replace procedure read_prieteni as
    v_fisier UTL_FILE.FILE_TYPE;
    v_line_prieteni prieteni%ROWTYPE;
BEGIN
    v_fisier := UTL_FILE.FOPEN('MYDIR', 'prieteni.txt', 'R');
    LOOP
    begin
        UTL_FILE.GET_LINE(v_fisier, v_line_prieteni.id);
        UTL_FILE.GET_LINE(v_fisier, v_line_prieteni.id_student1);
        UTL_FILE.GET_LINE(v_fisier, v_line_prieteni.id_student2);
        UTL_FILE.GET_LINE(v_fisier, v_line_prieteni.created_at);
        UTL_FILE.GET_LINE(v_fisier, v_line_prieteni.updated_at);
        insert into prieteni values v_line_prieteni;
        commit;
        EXCEPTION
            WHEN DUP_VAL_ON_INDEX then
                dbms_output.put_line ('Friendship already exists. will not insert this one');
            WHEN OTHERS then
                dbms_output.put_line ('One of the students doesn''t exist. Won''t insert this row');
    end;
    END LOOP;
    
    EXCEPTION
        WHEN NO_DATA_FOUND then
            dbms_output.put_line ('wrote prieteni to table');
            UTL_FILE.FCLOSE(v_fisier);
            COMMIT;
END read_prieteni;
/

BEGIN
    read_stud();
    read_prieteni();
END;
/

--delete from prieteni;
--/
--delete from studenti;
--/

select * from studenti;
select * from prieteni;