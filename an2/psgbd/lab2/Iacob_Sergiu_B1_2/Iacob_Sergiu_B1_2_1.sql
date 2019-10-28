DROP TABLE aux_table CASCADE CONSTRAINTS
/

CREATE TABLE aux_table
(
    col1 NUMBER(10) PRIMARY KEY,
    col2 NUMBER(2) NOT NULL
)
/

SET SERVEROUTPUT ON;
DECLARE
    c_number CONSTANT NUMBER(10) := 5;
    v_isPrime NUMBER(2);
    v_div NUMBER (10);

BEGIN
    FOR v_A in 1..10000 LOOP
        /*suma cifrelor modulo 9 este de fapt valoarea numarului modulo 9*/
        CONTINUE WHEN (v_A MOD 9 <> c_number);
        
        v_isPrime := 1;
        v_div := 2;
        <<checkPrime>>
        WHILE v_div <= FLOOR(SQRT(v_A)) LOOP
            IF (v_A MOD v_div = 0) THEN
                v_isPrime := 0;
                EXIT checkPrime;
            END IF;
            v_div := v_div + 1;
        END LOOP;
        INSERT INTO aux_table VALUES (v_A, v_isPrime);
        
    END LOOP;
    COMMIT;
    
    FOR v_line in (SELECT * FROM aux_table) LOOP
        DBMS_OUTPUT.PUT_LINE (v_line.col1 || ' ' || v_line.col2);
    END LOOP;
END;