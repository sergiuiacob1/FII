import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

import static java.lang.Thread.sleep;

public class Main {

    public static void main(String[] args) throws IOException {
        ServerSocket listener1, listener2;
        Socket socket1, socket2;
        String inputLine1 = "", inputLine2 = "";

        listener1 = new ServerSocket(8010);
        listener2 = new ServerSocket(8011);
        try {

            System.out.println("Waiting client 1...");
            socket1 = listener1.accept();
            System.out.println("Received client 1...");

            System.out.println("Waiting client 2...");
            socket2 = listener2.accept();
            System.out.println("Received client 2...");

            BufferedReader in1 = new BufferedReader(new InputStreamReader(socket1.getInputStream()));
            BufferedReader in2 = new BufferedReader(new InputStreamReader(socket2.getInputStream()));
            PrintWriter out1 = new PrintWriter(socket1.getOutputStream(), true);
            PrintWriter out2 = new PrintWriter(socket2.getOutputStream(), true);

            do {
                try {
                    if (in1.ready())
                        inputLine1 = in1.readLine();
                    else
                        inputLine1 = null;
                    if (inputLine1 != null) {
                        inputLine1 = "Mark: " + inputLine1;
                    }
                } catch (SocketException e) {
                    System.out.println("Socket 1 has no more data");
                }
                try {
                    if (in2.ready())
                        inputLine2 = in2.readLine();
                    else
                        inputLine2 = null;
                    if (inputLine2 != null) {
                        inputLine2 = "Allen: " + inputLine2;
                    }
                } catch (SocketException e) {
                    System.out.println("Socket 2 has no more data");
                }

                System.out.println("Client1: " + inputLine1);
                System.out.println("Client2: " + inputLine2);

                if (inputLine1 != null) {
                    out1.println(inputLine1);
                    out2.println(inputLine1);
                }
                if (inputLine2 != null) {
                    out1.println(inputLine2);
                    out2.println(inputLine2);
                }

            }
            while (inputLine1 != null || inputLine2 != null);
            out1.close();
            out2.close();
        } finally {
            listener1.close();
            listener2.close();
        }
    }
}