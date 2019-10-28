package game_utils;

public class Timekeeper implements Runnable {
    long startTime = System.nanoTime();
    private boolean running = true;

    public void run() {
        while (running) {
            System.out.println("Current time: " + (double)(System.nanoTime() - startTime)/1000000000.0);
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }

    public void terminate() {
        running = false;
    }
}
