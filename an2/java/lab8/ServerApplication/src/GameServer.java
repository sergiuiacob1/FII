import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketException;

public class GameServer {
    private static final int PORT = 8100;
    private ServerSocket serverSocket;
    private boolean running = false;
    private int nrOfConnections = 0;

    public static void main(String[] args) {
        GameServer server = new GameServer();

        try {
            server.init();
            server.waitForClients();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Implement the waitForClients() method: while running is true, create a new socket for every incoming client and start a ClientThread to execute its request.
    private void waitForClients() throws IOException {
        while (running) {
            try {
                Socket socket = serverSocket.accept();
                new ClientThread(this, socket).start();
                ++nrOfConnections;
            } catch (SocketException e) {
                System.out.println("Socket closed. Not accepting any more clients");
            } catch (IOException e) {
                e.printStackTrace();
            }
            if (nrOfConnections == 3){
                this.stop();
            }
        }
        serverSocket.close();
    }

    // Implement the init() method: create the serverSocket and set running to true
    private void init() throws IOException {
        serverSocket = new ServerSocket(PORT);
        running = true;
    }

    public void stop() throws IOException {
        this.running = false;
        serverSocket.close();
    }
}

