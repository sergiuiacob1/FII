package game_utils;

import players.Player;

import java.util.ArrayList;
import java.util.List;

public class Game {
    private final List<Player> players = new ArrayList<>();
    private Bag bag;
    private Board board;
    private Dictionary dictionary;
    private Integer playersActive = 0;
    private Timekeeper timekeeper = new Timekeeper();

    public void notifyNextPlayer(Player player) {
        Integer pos = players.indexOf(player);
        if (pos == players.size() - 1) {
            synchronized (players.get(0)) {
                players.get(0).notify();
            }
        } else
            synchronized (players.get(pos + 1)) {
                players.get(pos + 1).notify();
            }
    }

    void addPlayer(Player player) {
        players.add(player);
        player.setGame(this);
        ++playersActive;
    }

    public void start() {
        Thread timekeeperThread = new Thread(timekeeper);
        timekeeperThread.start();
        createDictionary();
        createPlayerThreads();
        synchronized (players.get(0)) {
            players.get(0).notify();//start game
        }
    }

    private void createDictionary() {
        dictionary = new Dictionary();
        dictionary.generateWords();
    }

    private void createPlayerThreads() {
        for (Player player : players) {
            Thread playerThread = new Thread(player);
            playerThread.start();
        }
    }

    public Bag getBag() {
        return bag;
    }

    public void setBag(Bag bag) {
        this.bag = bag;
    }

    public Board getBoard() {
        return board;
    }

    public void setBoard(Board board) {
        this.board = board;
    }

    public Dictionary getDictionary() {
        return dictionary;
    }

    public void setDictionary(Dictionary dictionary) {
        this.dictionary = dictionary;
    }

    public List<Player> getPlayers() {
        return players;
    }

    public synchronized void playerIsDone(Player player) throws InterruptedException {
        Player playerToNotify;
        playersActive--;
        System.out.println("Final score for " + player.getName() + ": " + player.getScore());
        if (players.indexOf(player) == players.size() - 1){
            playerToNotify = players.get(0);
        }
        else{
            playerToNotify = players.get(players.indexOf(player) + 1);
        }
        players.remove(player);
        if (playersActive == 0)
            timekeeper.terminate();
        else {
            synchronized (playerToNotify) {
                playerToNotify.notify();
            }
        }
    }

    //Create getters and setters
    //Create the method that will start the game: start one thread for each player
}