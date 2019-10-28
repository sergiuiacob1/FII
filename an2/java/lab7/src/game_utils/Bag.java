package game_utils;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

public class Bag {
    private static final StringBuilder letters = new StringBuilder();

    private void addLettersToBag (int howMany, Character ... chars){
        for (int i = 0; i < howMany; ++i){
            for (Character character: chars){
                letters.append (character);
            }
        }
    }

    Bag() {
        //letter distribution
        addLettersToBag (12, 'e');
        addLettersToBag (9, 'a', 'i');
        addLettersToBag (8, 'o');
        addLettersToBag (6, 'n', 'r', 't');
        addLettersToBag (4, 'l', 's', 'u', 'd');
        addLettersToBag (3, 'g');
        addLettersToBag (2, 'b', 'c', 'm', 'p', 'f', 'h', 'v', 'w', 'y', ' ');
        addLettersToBag (1, 'k', 'j', 'x', 'q', 'z');
    }

    public synchronized List<Character> extractLetters(int howMany) {
        // Replace the dots so that the bag is thread-safe
        Integer randomPos;
        List<Character> extracted = new ArrayList<>();
        for (int i = 0; i < howMany; i++) {
            if (letters.toString().isEmpty()) break;
            randomPos = ThreadLocalRandom.current().nextInt(0, letters.length());
            extracted.add(letters.charAt(randomPos));
            letters.deleteCharAt(randomPos);
        }
        return extracted;
    }
}