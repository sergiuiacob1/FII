package lab4;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class PlayCommand {
    public void run(String path) throws IOException {
        Desktop desktop = Desktop.getDesktop();
        try {
            desktop.open(new File(path));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
