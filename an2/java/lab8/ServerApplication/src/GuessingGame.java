import java.util.concurrent.ThreadLocalRandom;

public class GuessingGame {
    String player;
    Integer maxNumber, generatedNumber, nrOfAttempts;

    GuessingGame(String player, Integer maxNumber) {
        this.player = player;
        this.maxNumber = maxNumber;
        nrOfAttempts = 0;
        generatedNumber = ThreadLocalRandom.current().nextInt(1, maxNumber + 1);
    }

    public String submitGuess(Integer guess) {
        ++nrOfAttempts;
        if (guess.equals(generatedNumber)) {
            return "You got it!";
        }
        if (guess < generatedNumber) {
            return "Too small.";
        }
        return "Too big.";
    }

    public String getPlayer() {
        return player;
    }

    public void setPlayer(String player) {
        this.player = player;
    }

    public Integer getMaxNumber() {
        return maxNumber;
    }

    public void setMaxNumber(Integer maxNumber) {
        this.maxNumber = maxNumber;
    }

    public Integer getGeneratedNumber() {
        return generatedNumber;
    }

    public void setGeneratedNumber(Integer generatedNumber) {
        this.generatedNumber = generatedNumber;
    }

    public Integer getNrOfAttempts() {
        return nrOfAttempts;
    }

    public void setNrOfAttempts(Integer nrOfAttempts) {
        this.nrOfAttempts = nrOfAttempts;
    }
}
