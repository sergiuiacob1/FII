SET SERVEROUTPUT ON
CLEAR SCREEN

create or replace procedure connect_to_java (p_hostname IN varchar2, p_port in PLS_INTEGER, p_file in varchar2) as
    CONN            UTL_TCP.CONNECTION;
    RETVAL          BINARY_INTEGER;
    L_RESPONSE      VARCHAR2(1000) := '';
    L_TEXT          VARCHAR2(1000);
    v_fisier UTL_FILE.FILE_TYPE;
BEGIN
    v_fisier := UTL_FILE.FOPEN('MYDIR', p_file, 'R');
    --Deschidem conexiunea...
    CONN := UTL_TCP.OPEN_CONNECTION(
        REMOTE_HOST   => p_hostname,
        REMOTE_PORT   => p_port,
        TX_TIMEOUT    => 10
    );
    
    LOOP
        UTL_FILE.GET_LINE(v_fisier, l_text);
        RETVAL := UTL_TCP.WRITE_LINE(CONN,L_TEXT);
    END LOOP;
    EXCEPTION WHEN NO_DATA_FOUND then NULL;
    UTL_TCP.FLUSH(CONN);
    
    --Verificam daca am primit ceva si citim raspunsul din socket...
    BEGIN
        WHILE UTL_TCP.AVAILABLE(CONN, 10) > 0 LOOP
            L_RESPONSE := UTL_TCP.GET_LINE(CONN, TRUE);
            dbms_output.put_line (l_response);
        END LOOP;
    EXCEPTION
        WHEN UTL_TCP.END_OF_INPUT THEN
            NULL;
    END;
    UTL_FILE.FCLOSE(v_fisier);
    UTL_TCP.CLOSE_CONNECTION(CONN);
END connect_to_java;
/

begin
    connect_to_java('127.0.0.1', 8010, 'f1.txt');
--    connect_to_java('127.0.0.1', 8011, 'f2.txt');
end;

--import java.io.BufferedReader;
--import java.io.IOException;
--import java.io.InputStreamReader;
--import java.io.PrintWriter;
--import java.net.ServerSocket;
--import java.net.Socket;
--import java.net.SocketException;
--
--import static java.lang.Thread.sleep;
--
--public class Main {
--
--    public static void main(String[] args) throws IOException {
--        ServerSocket listener1, listener2;
--        Socket socket1, socket2;
--        String inputLine1 = "", inputLine2 = "";
--
--        listener1 = new ServerSocket(8010);
--        listener2 = new ServerSocket(8011);
--        try {
--
--            System.out.println("Waiting client 1...");
--            socket1 = listener1.accept();
--            System.out.println("Received client 1...");
--
--            System.out.println("Waiting client 2...");
--            socket2 = listener2.accept();
--            System.out.println("Received client 2...");
--
--            BufferedReader in1 = new BufferedReader(new InputStreamReader(socket1.getInputStream()));
--            BufferedReader in2 = new BufferedReader(new InputStreamReader(socket2.getInputStream()));
--            PrintWriter out1 = new PrintWriter(socket1.getOutputStream(), true);
--            PrintWriter out2 = new PrintWriter(socket2.getOutputStream(), true);
--
--            do {
--                try {
--                    if (in1.ready())
--                        inputLine1 = in1.readLine();
--                    else
--                        inputLine1 = null;
--                    if (inputLine1 != null) {
--                        inputLine1 = "Mark: " + inputLine1;
--                    }
--                } catch (SocketException e) {
--                    System.out.println("Socket 1 has no more data");
--                }
--                try {
--                    if (in2.ready())
--                        inputLine2 = in2.readLine();
--                    else
--                        inputLine2 = null;
--                    if (inputLine2 != null) {
--                        inputLine2 = "Allen: " + inputLine2;
--                    }
--                } catch (SocketException e) {
--                    System.out.println("Socket 2 has no more data");
--                }
--
--                System.out.println("Client1: " + inputLine1);
--                System.out.println("Client2: " + inputLine2);
--
--                if (inputLine1 != null) {
--                    out1.println(inputLine1);
--                    out2.println(inputLine1);
--                }
--                if (inputLine2 != null) {
--                    out1.println(inputLine2);
--                    out2.println(inputLine2);
--                }
--
--            }
--            while (inputLine1 != null || inputLine2 != null);
--            out1.close();
--            out2.close();
--        } finally {
--            listener1.close();
--            listener2.close();
--        }
--    }
--}