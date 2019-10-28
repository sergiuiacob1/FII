set serveroutput on;

CREATE OR REPLACE PROCEDURE http_request(p_url VARCHAR2, p_filename VARCHAR2)
IS
    v_file UTL_FILE.file_type;
    v_buffer VARCHAR2(32000);
    v_connection UTL_TCP.CONNECTION;
BEGIN
    v_connection := UTL_TCP.OPEN_CONNECTION(
                    REMOTE_HOST   => p_url,
                    REMOTE_PORT   => 80,
                    charset       => 'UTF-8'
                );
                
    v_file := UTL_FILE.FOPEN('MYDIR', p_filename, 'W', 33000);

    UTL_TCP.write_line(v_connection, 'GET / HTTP/1.0');
    UTL_TCP.write_line(v_connection);
    
    BEGIN
        LOOP
            v_buffer := UTL_TCP.get_line(v_connection, true);
            UTL_FILE.put_line(v_file, v_buffer);
            UTL_FILE.fflush(v_file);
        END LOOP;
        
    EXCEPTION
        WHEN OTHERS THEN
                UTL_TCP.close_connection(v_connection);
                UTL_FILE.FCLOSE(v_file);
    END;
    
    UTL_TCP.close_connection(v_connection);
    UTL_FILE.FCLOSE(v_file);
  
END;
/


DECLARE
    v_file_name VARCHAR2(100) := 'google_index.html';
BEGIN
    http_request('www.google.ro',v_file_name);
END;

