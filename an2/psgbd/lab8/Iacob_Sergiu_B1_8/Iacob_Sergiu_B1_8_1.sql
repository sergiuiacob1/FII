set serveroutput on;

create or replace procedure write_studs as
    v_fisier UTL_FILE.FILE_TYPE; 
    v_line_stud studenti%ROWTYPE;
BEGIN
    v_fisier := UTL_FILE.FOPEN('MYDIR', 'stud.txt', 'W');
      FOR v_line_stud in (select * from studenti) loop
        utl_file.put_line(v_fisier, v_line_stud.id);
        utl_file.put_line(v_fisier, v_line_stud.nr_matricol);
        utl_file.put_line(v_fisier, v_line_stud.nume);
        utl_file.put_line(v_fisier, v_line_stud.prenume);
        utl_file.put_line(v_fisier, v_line_stud.an);
        utl_file.put_line(v_fisier, v_line_stud.grupa);
        utl_file.put_line(v_fisier, nvl(v_line_stud.bursa, 0));
        utl_file.put_line(v_fisier, v_line_stud.data_nastere);
        utl_file.put_line(v_fisier, v_line_stud.email);
        utl_file.put_line(v_fisier, v_line_stud.created_at);
        utl_file.put_line(v_fisier, v_line_stud.updated_at);
--        utl_file.fflush(v_fisier);
      end loop;
  UTL_FILE.FCLOSE(v_fisier);
END write_studs;
/

create or replace procedure write_prieteni as
    v_fisier UTL_FILE.FILE_TYPE; 
    v_line_prieteni prieteni%ROWTYPE;
BEGIN
    v_fisier := UTL_FILE.FOPEN('MYDIR', 'prieteni.txt', 'W');
        FOR v_line_prieteni in (select * from prieteni) loop
        utl_file.put_line(v_fisier, v_line_prieteni.id);
        utl_file.put_line(v_fisier, v_line_prieteni.id_student1);
        utl_file.put_line(v_fisier, v_line_prieteni.id_student2);
        utl_file.put_line(v_fisier, v_line_prieteni.created_at);
        utl_file.put_line(v_fisier, v_line_prieteni.updated_at);
--        utl_file.fflush(v_fisier);
        end loop;
    UTL_FILE.FCLOSE(v_fisier);
END write_prieteni;
/

BEGIN
    write_studs();
    write_prieteni();
END;
/