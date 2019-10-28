import com.jcraft.jsch.JSchException;
import com.jcraft.jsch.SftpException;

import java.io.*;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ClientThread extends Thread {
    private BufferedReader in;
    private PrintWriter out;
    private Socket socket;
    private final GameServer server;
    private GuessingGame guessingGame;
    private Boolean running;
    private StringBuilder HTML = new StringBuilder("<!DOCTYPE html><html>");

    // Create the constructor that receives a reference to the server and to the client socket
    ClientThread(GameServer server, Socket socket) {
        this.server = server;
        this.socket = socket;
        try {
            in = new BufferedReader(new InputStreamReader(socket.getInputStream())); //client -> server stream
            out = new PrintWriter(socket.getOutputStream()); //server -> client stream
            socket.setSoTimeout(10 * 1000);
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(666013);
        }
        running = true;
    }

    public void run() {
        System.out.println("New connection!");
        while (running) {
            try {
                String request;
                request = in.readLine();
                String response = execute(request);
                out.println(response);
                out.flush();
                HTML.append("<p>").append(request).append("</br></p>");
                HTML.append("<p>").append(response).append("</br></p>");
            } catch (SocketTimeoutException e) {
                System.out.println("Client inactive, disconnecting");
                break;
            } catch (IOException e) {
                e.printStackTrace();
                break;
            }
        }
        try {
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String execute(String request) {
        if (request == null) {
            running = false;
            return "Client disconnected.";
        }

        System.out.println("Server received request: " + request);
        switch (request) {
            case "html":
                createHTMLPage();
                return "Page created.";
            case "create":
                String playerName = null;
                String maxNr = null;
                try {
                    out.println("Enter player name:");
                    out.flush();
                    playerName = in.readLine();
                    out.println("Enter maximum number:");
                    out.flush();
                    maxNr = in.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                    System.exit(42);
                }
                guessingGame = new GuessingGame(playerName, Integer.parseInt(maxNr));
                return "Game created successfully";

            case "submit":
                String guess = null;
                try {
                    if (guessingGame == null) {
                        return "You must first create the game!";
                    }
                    out.println("Enter number value:");
                    out.flush();
                    guess = in.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                    System.exit(43);
                }
                return guessingGame.submitGuess(Integer.parseInt(guess)) + " Total number of attempts: " + guessingGame.getNrOfAttempts();

            case "quit":
                if (guessingGame == null) {
                    return "You must first create the game!";
                }
                return "Loser, the number was: " + guessingGame.getGeneratedNumber();
        }

        return "Invalid request";
    }

    private void createHTMLPage() {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter("index.html"));
            writer.write(HTML.toString());
            writer.write("</html>");
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
            CopyToRemoteHost copy = new CopyToRemoteHost("fenrir.info.uaic.ro", "sergiu.iacob", "rwAdreq32");
            Path srcFile = Paths.get("index.html").toAbsolutePath();
            System.out.println(srcFile);
            copy.cp(srcFile, "public_html/");
        } catch (JSchException | SftpException | IOException e) {
            e.printStackTrace();
        }
    }
}