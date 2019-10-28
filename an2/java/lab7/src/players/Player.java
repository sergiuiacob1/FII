package players;

import game_utils.Game;

import java.util.List;

public abstract class Player implements Runnable {
    protected String name;
    protected Game game;
    protected int score = 0;
    private int timesLost = 0;

    Player(String _name) {
        name = _name;
    }

    private boolean createSubmitWord() throws InterruptedException {
        List extracted = game.getBag().extractLetters((int) (Math.random() * 8) + 1);
        Integer wordScore;
        if (extracted.isEmpty()) {
            return false;
        }

        StringBuilder word = new StringBuilder();
        for (Object anExtracted : extracted) {
            word.append(anExtracted);
        }

        String goodWord = generateStringFromDictionary(word.toString());
        wordScore = game.getBoard().addWord(this, goodWord);
        if (wordScore != 0){
            score += wordScore;
            System.out.println(name + " now has score " + score);
            timesLost = 0;
        }
        else{
            ++timesLost;
        }
        Thread.sleep(10);
        return true;
    }

    abstract String generateStringFromDictionary(String letters);

    public synchronized void run() {
        Boolean rez;
        while (true) {
            try {
                wait();
                rez = createSubmitWord();
                if (rez && timesLost <= 5)
                    notifyNextPlayer();
                if (!rez || timesLost > 5){
                    game.playerIsDone(this);
                    break;
                }
            } catch (InterruptedException e) {
                System.out.println("failed to run player");
                e.printStackTrace();
            }
        }
    }

    private void notifyNextPlayer() {
        game.notifyNextPlayer(this);
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Game getGame() {
        return game;
    }

    public void setGame(Game game) {
        this.game = game;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    @Override
    public String toString() {
        return "players.Player{" +
                "name='" + name + '\'' +
                ", game=" + game +
                ", score=" + score +
                '}';
    }
}