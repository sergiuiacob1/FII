set serveroutput on;

CREATE or REPLACE PROCEDURE Write_mime_header (p_conn  IN OUT nocopy utl_smtp.connection, p_name  IN VARCHAR2, p_value IN VARCHAR2) IS 
BEGIN 
    utl_smtp.Write_data (p_conn, p_name || ': ' || p_value || utl_tcp.crlf); 
END Write_mime_header;
/

create or replace procedure send_mail (p_hostname IN varchar2, p_port in PLS_INTEGER) AS 
    l_conn            utl_smtp.connection; 
    nls_charset       VARCHAR2(255); 
    v_password        varchar2(100);
    v_smtp_domain     VARCHAR2 (256) := 'gmail.com'; 
    v_mailer_id       CONSTANT VARCHAR2 (256) := 'Mailer by Oracle UTL_SMTP';
    v_sender varchar2(100) := 'PL/SQL';
    v_fisier UTL_FILE.FILE_TYPE; 
BEGIN
    v_fisier := UTL_FILE.FOPEN('MYDIR', 'temp.txt', 'R', 32700);
    UTL_FILE.GET_LINE(v_fisier, v_password);
    UTL_FILE.FCLOSE(v_fisier);
    -- get characterset 
    SELECT value INTO nls_charset FROM   nls_database_parameters WHERE  parameter = 'NLS_CHARACTERSET'; 
    -- establish connection and autheticate 
    l_conn := utl_smtp.Open_connection (p_hostname, p_port); 
    utl_smtp.Ehlo(l_conn, v_smtp_domain); 
    utl_smtp.Command(l_conn, 'auth login'); 
    utl_smtp.Command(l_conn, 
    utl_raw.Cast_to_varchar2( 
    utl_encode.Base64_encode( 
    utl_raw.Cast_to_raw('sergiu.iacob1@gmail.com')))); 
    utl_smtp.Command(l_conn, utl_raw.Cast_to_varchar2(utl_encode.Base64_encode(utl_raw.Cast_to_raw(v_password)))); 
    utl_smtp.Command(l_conn, 'MAIL FROM: <' ||v_sender ||'>'); 
    utl_smtp.Command(l_conn, 'RCPT TO: <' || 'sergiu.iacob1@gmail.com' || '>'); 
    
    -- write mime headers 
    utl_smtp.Open_data (l_conn); 
    Write_mime_header (l_conn, 'From', v_sender); 
    Write_mime_header (l_conn, 'To', 'sergiu.iacob1@gmail.com'); 
    Write_mime_header (l_conn, 'Subject', SYSDATE); 
    Write_mime_header (l_conn, 'Content-Type', 'text/plain'); 
    Write_mime_header (l_conn, 'X-Mailer', v_mailer_id); 
    utl_smtp.Write_data (l_conn, utl_tcp.crlf); 
    -- write message body 
    utl_smtp.Write_data (l_conn, 'Domn'' profesor, va rog sa-mi dati 15 puncte ca sa iau nota 10 ca am muncit mult la tema asta :('); 
    utl_smtp.Close_data (l_conn); 
    -- end connection 
    utl_smtp.Quit (l_conn);
    dbms_output.put_line ('Mail Sent!');
EXCEPTION 
    WHEN OTHERS THEN
        Raise_application_error(-20000, 'FAIL: ' || SQLERRM); 
        BEGIN
            utl_smtp.Quit(l_conn); 
        EXCEPTION 
            WHEN OTHERS THEN NULL; 
        END;
END send_mail; 
/ 

BEGIN 
    send_mail ('127.0.0.1', 1925);
END; 