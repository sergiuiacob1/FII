set serveroutput on;

create or replace procedure create_catalog (p_cline IN cursuri%ROWTYPE) as
    v_cursor_id NUMBER;
    v_ok number;
    v_rec_tab     DBMS_SQL.DESC_TAB;
    v_nr_col     NUMBER;
    v_total_coloane     NUMBER;
    v_stud_nume VARCHAR2(100);
    v_stud_prenume VARCHAR2(100);
    v_stud_nr_matricol varchar2(100);
    v_nline note%ROWTYPE;
    v_id INT;
begin
    v_cursor_id  := DBMS_SQL.OPEN_CURSOR;
    DBMS_SQL.PARSE(v_cursor_id , 'drop table catalog_' || p_cline.id || ' cascade constraints', DBMS_SQL.NATIVE);
    v_ok := DBMS_SQL.EXECUTE(v_cursor_id );
    
    DBMS_SQL.PARSE(v_cursor_id , 'create table catalog_' || p_cline.id || ' ( id int primary key, valoare number(2), data_notare date, nume varchar2(100), prenume varchar2(100), nr_matricol varchar2(10))', DBMS_SQL.NATIVE);
    v_ok := DBMS_SQL.EXECUTE (v_cursor_id);    
    dbms_sql.close_cursor (v_cursor_id);
end create_catalog;
/

create or replace procedure insert_note as
     v_cursor_id NUMBER;
    v_ok number;
    v_rec_tab     DBMS_SQL.DESC_TAB;
    v_nr_col     NUMBER;
    v_total_coloane     NUMBER;
    v_stud_nume VARCHAR2(100);
    v_stud_prenume VARCHAR2(100);
    v_stud_nr_matricol varchar2(100);
    v_nline note%ROWTYPE;
    v_id INT;
begin
    v_cursor_id  := DBMS_SQL.OPEN_CURSOR;
    v_id := 1;
    for v_nline in (select * from note) loop
        select nume into v_stud_nume from studenti where id = v_nline.id_student;
        select prenume into v_stud_prenume from studenti where id = v_nline.id_student;
        select nr_matricol into v_stud_nr_matricol from studenti where id = v_nline.id_student;
        dbms_output.put_line ('insert into catalog_' || v_nline.id_curs || ' values (' || v_id || ',' || v_nline.valoare || ',''' || v_nline.data_notare || ''',''' || v_stud_nume || ''',''' || v_stud_prenume || ''',''' || v_stud_nr_matricol || ''')');
        DBMS_SQL.PARSE(v_cursor_id, 'insert into catalog_' || v_nline.id_curs || ' values (' || v_id || ',' || v_nline.valoare || ',''' || v_nline.data_notare || ''',''' || v_stud_nume || ''',''' || v_stud_prenume || ''',''' || v_stud_nr_matricol || ''')', DBMS_SQL.NATIVE);
        v_ok := DBMS_SQL.EXECUTE(v_cursor_id );
        v_id := v_id + 1;
    end loop;
    DBMS_SQL.CLOSE_CURSOR(v_cursor_id);
end insert_note;
/

create or replace procedure create_catalogs as
    v_cline cursuri%ROWTYPE;
begin
    for v_cline in (select * from cursuri) loop
        create_catalog (v_cline);
    end loop;
    
    insert_note();
end create_catalogs;
/

begin
    create_catalogs();
end;