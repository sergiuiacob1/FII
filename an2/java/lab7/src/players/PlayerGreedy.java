package players;

import java.util.HashMap;

public class PlayerGreedy extends PlayerAuto {
    public PlayerGreedy (String name) {
        super(name);
    }

    @Override
    protected String buildWord(String[] words, String letters, HashMap<Character, Integer> frecv1){
        String bestWord = "";
        for (String dictWord : words) {
            if (dictWord.length() != letters.length()) continue;
            if (wordsHaveSameLetters(frecv1, dictWord)){
                if (game.getBoard().getWordValue(dictWord) > game.getBoard().getWordValue(bestWord)){
                    bestWord = dictWord;
                }
            }
        }

        if (bestWord.equals(""))
            return letters;
        return bestWord;
    }
}
