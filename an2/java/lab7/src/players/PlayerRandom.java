package players;

import java.util.concurrent.ThreadLocalRandom;

public class PlayerRandom extends Player {
    public PlayerRandom(String name) {
        super(name);
    }

    @Override
    String generateStringFromDictionary(String letters) {
        Character aux;
        Integer randomPos1, randomPos2;
        char[] charLetters;
        for (int i = 0; i < 100; ++i){
            charLetters = letters.toCharArray();
            randomPos1 = ThreadLocalRandom.current().nextInt(0, letters.length());
            randomPos2 = ThreadLocalRandom.current().nextInt(0, letters.length());
            aux = charLetters[randomPos1];
            charLetters[randomPos1] = charLetters[randomPos2];
            charLetters[randomPos2] = aux;
            letters = String.valueOf(charLetters);
        }
        return letters;
    }
}
