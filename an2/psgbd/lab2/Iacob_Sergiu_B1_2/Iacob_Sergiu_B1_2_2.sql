DECLARE
    CURSOR cursor_update IS
        SELECT * from aux_table FOR UPDATE OF col2 NOWAIT;
    TYPE int_list IS VARRAY (100) of NUMBER(10);
    v_fib_numbers int_list := int_list(0, 1);
    v_index NUMBER(5);
    v_aux_table_line aux_table%ROWTYPE;
    v_updated NUMBER(10);
BEGIN
    v_index := 3;
    WHILE (v_fib_numbers(v_index - 1) < 10000) LOOP
        v_fib_numbers.extend;
        v_fib_numbers(v_index) := v_fib_numbers(v_index - 1) + v_fib_numbers(v_index - 2);
        v_index := v_index + 1;
    END LOOP;
    
    v_updated := 0;
    FOR v_line in cursor_update LOOP
        IF (v_fib_numbers.exists (v_line.col1))
        THEN
            IF (v_line.col2 = 0)
            THEN
                v_updated := v_updated + 1;
            END IF;
            UPDATE aux_table SET col2 = 1 WHERE CURRENT OF cursor_update;
        ELSE
            IF (v_line.col2 = 1)
            THEN
                v_updated := v_updated + 1;
            END IF;
            UPDATE aux_table SET col2 = 0 WHERE CURRENT OF cursor_update;
        END IF;
    END LOOP;
    
    COMMIT;
    
    /*FOR v_aux_table_line in (SELECT * FROM aux_table) LOOP
        DBMS_OUTPUT.PUT_LINE (v_aux_table_line.col1 || ' ' || v_aux_table_line.col2);
    END LOOP;*/
    DBMS_OUTPUT.PUT_LINE ('Am facut update la  ' || v_updated || ' numere.');
END;