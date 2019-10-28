SET SERVEROUTPUT ON
CLEAR SCREEN

--create or replace procedure connect_to_host (p_hostname IN VARCHAR2) as
declare
    CONN            UTL_TCP.CONNECTION;
    RETVAL          PLS_INTEGER;
    L_RESPONSE      VARCHAR2(30000) := '';
    L_TEXT          VARCHAR2(10000);
    v_fisier UTL_FILE.FILE_TYPE; 
BEGIN
     v_fisier := UTL_FILE.FOPEN('MYDIR', 'index.html', 'W', 32700);
    --Deschidem conexiunea...
    CONN := UTL_TCP.OPEN_CONNECTION(
        REMOTE_HOST   => 'www.google.ro',
        REMOTE_PORT   => 80,
        charset       => 'US7ASCII'
    );
    
    L_TEXT := 'GET / HTTP/1.0';
    RETVAL := UTL_TCP.WRITE_LINE(CONN, L_TEXT);
    RETVAL := UTL_TCP.WRITE_LINE(CONN);
    
    BEGIN
        LOOP
            utl_file.put_line(v_fisier, utl_tcp.get_line(CONN, TRUE));  -- read result
            utl_file.fflush(v_fisier);
        END LOOP;
    EXCEPTION
        WHEN UTL_TCP.END_OF_INPUT THEN
            NULL;
    END;
    
    UTL_TCP.CLOSE_CONNECTION(CONN);
    UTL_FILE.FCLOSE(v_fisier);
EXCEPTION
    WHEN OTHERS THEN
        dbms_output.put_line ('FAIL');
        RAISE_APPLICATION_ERROR(-20101, SQLERRM);
        UTL_TCP.CLOSE_CONNECTION(CONN);
--END connect_to_host;
END;
/

--begin
--    connect_to_host('www.google.ro');
--end;
--/

----
--BEGIN
--  DBMS_NETWORK_ACL_ADMIN.ASSIGN_ACL(acl  => 'example.xml',
--                                    host => '127.0.0.1');
--END;
--/


-- 
--BEGIN
--  DBMS_NETWORK_ACL_ADMIN.ADD_PRIVILEGE(acl       => 'example.xml',
--                                       principal => 'STUDENT2',
--                                       is_grant  => true,
--                                       privilege => 'resolve');
-- 
--  DBMS_NETWORK_ACL_ADMIN.ASSIGN_ACL(acl  => 'example.xml',
--                                    host => '127.0.0.1');
--END;
--/
--COMMIT;