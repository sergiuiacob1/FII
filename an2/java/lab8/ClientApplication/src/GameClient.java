import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.Scanner;

public class GameClient {
    private final static String SERVER_ADDRESS = "127.0.0.1";
    private final static int PORT = 8100;
    private static BufferedReader in;
    private PrintWriter out;

    public static void main(String[] args) {
        GameClient client = new GameClient();
        while (true) {
            String request = client.readFromKeyboard();
            if (request.equalsIgnoreCase("exit")) {
                break;
            } else {
                client.sendRequestToServer(request);
                checkForServerResponse();
            }
        }
    }

    private static void checkForServerResponse() {
        String response = null;
        try {
            response = in.readLine();
        } catch (SocketTimeoutException e) {
            System.out.println("Server timeout, exiting.");
            System.exit(0);
        } catch (IOException e) {
            e.printStackTrace();
        }
        if (response != null)
            System.out.println(response);
        else
            System.out.println("No response from server");
    }

    private GameClient() {
        try {
            Socket socket = new Socket(SERVER_ADDRESS, PORT);
            out = new PrintWriter(socket.getOutputStream(), true);
            in = new BufferedReader(new InputStreamReader(socket.getInputStream())); //client -> server stream
            socket.setSoTimeout(5 * 1000);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    //Implement the sendRequestToServer method
    private void sendRequestToServer(String request) {
        out.println(request);
        out.flush();
    }

    private String readFromKeyboard() {
        Scanner scanner = new Scanner(System.in);
        return scanner.next();
    }
}