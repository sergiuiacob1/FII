set serveroutput on;

create or replace procedure create_table (p_fisier IN UTL_FILE.FILE_TYPE, p_nume_tabela in varchar2) as
    v_cursor_id NUMBER;
    v_ok number;
    v_rec_tab     DBMS_SQL.DESC_TAB;
    v_nr_col     NUMBER;
    v_total_coloane     NUMBER;
    v_col_type VARCHAR2(100);
    v_col_is_null varchar2(100);
    v_primary_col varchar2(100);
    v_i INT;
    v_data_length INT;
    v_data_precision INT;
    v_data_scale INT;
    v_col_name VARCHAR2(100);
    CURSOR v_constraints(p_nume_tabela in VARCHAR2) IS SELECT a.table_name, a.column_name, a.constraint_name, c.owner, 
       -- referenced pk
       c.r_owner, c_pk.table_name r_table_name, c_pk.constraint_name r_pk
      FROM all_cons_columns a
      JOIN all_constraints c ON a.owner = c.owner
                            AND a.constraint_name = c.constraint_name
      JOIN all_constraints c_pk ON c.r_owner = c_pk.owner
                               AND c.r_constraint_name = c_pk.constraint_name
     WHERE c.constraint_type = 'R'
       AND a.table_name = upper(trim(p_nume_tabela));
begin
    v_cursor_id  := DBMS_SQL.OPEN_CURSOR;
    DBMS_SQL.PARSE(v_cursor_id , 'SELECT * FROM ' || p_nume_tabela, DBMS_SQL.NATIVE);
    v_ok := DBMS_SQL.EXECUTE(v_cursor_id );
    DBMS_SQL.DESCRIBE_COLUMNS(v_cursor_id, v_total_coloane, v_rec_tab);
    
    SELECT cols.column_name
    INTO v_primary_col
    FROM all_constraints cons, all_cons_columns cols
    WHERE cols.table_name = upper(trim(p_nume_tabela))
    AND cons.constraint_type = 'P'
    AND cons.constraint_name = cols.constraint_name
    AND cons.owner = cols.owner;
    
    utl_file.putf (p_fisier, 'drop table ' || p_nume_tabela || ' cascade constraints\n/\n\n');
    
    utl_file.putf (p_fisier, 'create table ');
    utl_file.putf (p_fisier, p_nume_tabela);
    utl_file.put_line (p_fisier, '(');
    v_nr_col := v_rec_tab.first;
    v_i := 0;
    IF (v_nr_col IS NOT NULL) THEN
        LOOP
            if (v_i > 0) then
                utl_file.put_line (p_fisier, ',');
            end if;
            utl_file.putf (p_fisier, v_rec_tab(v_nr_col).col_name || ' ');
            SELECT data_type into v_col_type FROM DBA_TAB_COLUMNS where owner = 'STUDENT' and table_name = upper(trim(p_nume_tabela)) and column_name = upper(trim(v_rec_tab(v_nr_col).col_name));
            utl_file.putf (p_fisier, v_col_type);
            SELECT data_precision into v_data_precision FROM DBA_TAB_COLUMNS where owner = 'STUDENT' and table_name = upper(trim(p_nume_tabela)) and column_name = upper(trim(v_rec_tab(v_nr_col).col_name));
            if (v_data_precision IS NULL) then
                SELECT data_length into v_data_length FROM DBA_TAB_COLUMNS where owner = 'STUDENT' and table_name = upper(trim(p_nume_tabela)) and column_name = upper(trim(v_rec_tab(v_nr_col).col_name));
                if (v_col_type <> 'DATE') then
                    utl_file.putf (p_fisier, '(' || v_data_length || ')');
                end if;
            else
                utl_file.putf (p_fisier, '(' || v_data_precision);
                SELECT data_scale into v_data_scale FROM DBA_TAB_COLUMNS where owner = 'STUDENT' and table_name = upper(trim(p_nume_tabela)) and column_name = upper(trim(v_rec_tab(v_nr_col).col_name));
                utl_file.putf (p_fisier, ',' || v_data_scale || ')');
            end if;
            select nullable into v_col_is_null from DBA_TAB_COLUMNS where owner = 'STUDENT' and table_name = upper(trim(p_nume_tabela)) and column_name = upper(trim(v_rec_tab(v_nr_col).col_name));
            if (v_col_is_null = 'N') then
                utl_file.putf (p_fisier, ' NOT NULL');
            end if;
            if (v_primary_col = v_rec_tab(v_nr_col).col_name) then
                utl_file.putf (p_fisier, ' PRIMARY KEY');
            end if;
            v_nr_col := v_rec_tab.next(v_nr_col);
            EXIT WHEN (v_nr_col IS NULL);
            v_i := v_i + 1;
        END LOOP;
    END IF;
    
    for v_line in v_constraints(p_nume_tabela) loop
        utl_file.putf (p_fisier, ',\nCONSTRAINT ' || v_line.constraint_name || ' FOREIGN KEY (' || v_line.column_name || ') REFERENCES ' || v_line.r_table_name);
        select column_name into v_col_name from all_cons_columns where constraint_name = v_line.r_pk;
        utl_file.putf (p_fisier, '(' || v_col_name || ')');
    end loop;
    
    utl_file.putf (p_fisier, '\n)\n');
    utl_file.put_line (p_fisier, '/');
    DBMS_SQL.CLOSE_CURSOR(v_cursor_id);
end create_table;
/

CREATE OR REPLACE TYPE t_array IS VARRAY(10000) OF VARCHAR2 (200);
/

create or replace procedure insert_into_table (p_fisier IN UTL_FILE.FILE_TYPE, p_nume_tabela in VARCHAR2) as
    v_cursor_id NUMBER;
    v_ok        NUMBER;
    v_rec_tab     DBMS_SQL.DESC_TAB;
    v_nr_col     NUMBER;
    v_total_coloane     NUMBER;
    v_valori t_array;
    v_i INT;
BEGIN
    v_valori := t_array();
    v_i := 1;
    v_cursor_id  := DBMS_SQL.OPEN_CURSOR;
    DBMS_SQL.PARSE(v_cursor_id , 'SELECT * FROM ' || p_nume_tabela, DBMS_SQL.NATIVE);
    DBMS_SQL.DESCRIBE_COLUMNS(v_cursor_id, v_total_coloane, v_rec_tab);
    v_valori.extend(v_total_coloane + 1);
    v_nr_col := v_rec_tab.first;
    IF (v_nr_col IS NOT NULL) THEN
        LOOP
            DBMS_SQL.DEFINE_COLUMN(v_cursor_id, v_i, v_valori(v_i), 200);
            v_nr_col := v_rec_tab.next(v_nr_col);
            EXIT WHEN (v_nr_col IS NULL);
            v_i := v_i + 1;
        END LOOP;
    END IF;
    
    v_ok := DBMS_SQL.EXECUTE(v_cursor_id );
    LOOP 
        IF DBMS_SQL.FETCH_ROWS(v_cursor_id)>0 THEN 
            utl_file.putf (p_fisier, 'insert into ' || p_nume_tabela || ' values (');
            for v_j in 1..v_total_coloane LOOP
                DBMS_SQL.COLUMN_VALUE(v_cursor_id, v_j, v_valori(v_j));
                utl_file.putf (p_fisier, '''' || v_valori(v_j) || '''');
                if (v_j != v_total_coloane) then
                    utl_file.putf (p_fisier, ', ');
                end if;
            END LOOP;
            utl_file.putf (p_fisier, ')\n/\n');
        ELSE 
            EXIT; 
        END IF; 
    END LOOP; 
    DBMS_SQL.CLOSE_CURSOR(v_cursor_id);
END insert_into_table;
/

create or replace procedure export_depending_tables (p_fisier IN UTL_FILE.FILE_TYPE, p_nume_tabela in VARCHAR2) as
    CURSOR v_constraints(p_nume_tabela in VARCHAR2) IS SELECT a.table_name, a.column_name, a.constraint_name, c.owner, 
       -- referenced pk
       c.r_owner, c_pk.table_name r_table_name, c_pk.constraint_name r_pk
      FROM all_cons_columns a
      JOIN all_constraints c ON a.owner = c.owner
                            AND a.constraint_name = c.constraint_name
      JOIN all_constraints c_pk ON c.r_owner = c_pk.owner
                               AND c.r_constraint_name = c_pk.constraint_name
     WHERE c.constraint_type = 'R'
       AND a.table_name = upper(trim(p_nume_tabela));
begin
    for v_line in v_constraints(p_nume_tabela) loop
        redo_this_table_as_well (p_fisier, v_line.r_table_name);
        dbms_output.put_line (v_line.r_table_name);
    end loop;
end export_depending_tables;
/

create or replace procedure redo_table (p_fisier IN UTL_FILE.FILE_TYPE, p_nume_tabela in VARCHAR2) as
begin
    export_depending_tables (p_fisier, p_nume_tabela);
    create_table (p_fisier, p_nume_tabela);
    insert_into_table(p_fisier, p_nume_tabela);
end redo_table;
/

create or replace procedure redo_this_table_as_well (p_fisier IN UTL_FILE.FILE_TYPE, p_nume_tabela in VARCHAR2) as
begin
    create_table (p_fisier, p_nume_tabela);
    insert_into_table(p_fisier, p_nume_tabela);
end redo_this_table_as_well;
/

DECLARE
    v_fisier UTL_FILE.FILE_TYPE;
begin
    v_fisier := UTL_FILE.FOPEN('MYDIR', 'ex1.sql', 'W');
    redo_table (v_fisier, 'didactic');
    utl_file.putf (v_fisier, '\n\n');
    UTL_FILE.FCLOSE(v_fisier);
end;