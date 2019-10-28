package players;

import java.util.HashMap;

public class PlayerAuto extends Player {
    public PlayerAuto(String name) {
        super(name);
    }

    @Override
    String generateStringFromDictionary(String letters) {
        String[] words = game.getDictionary().getWords().toArray(new String[0]);
        HashMap<Character, Integer> frecv1 = new HashMap<>();

        for (int i = 0; i < letters.length(); ++i) {
            if (frecv1.containsKey(letters.charAt(i))) {
                frecv1.put(letters.charAt(i), frecv1.get(letters.charAt(i)) + 1);
            } else {
                frecv1.put(letters.charAt(i), 1);
            }
        }

        return buildWord(words, letters, frecv1);
    }

    protected String buildWord(String[] words, String letters, HashMap<Character, Integer> frecv1){
        for (String dictWord : words) {
            if (dictWord.length() != letters.length()) continue;
            if (wordsHaveSameLetters(frecv1, dictWord))
                return dictWord;
        }

        return letters;
    }

    protected boolean wordsHaveSameLetters(HashMap<Character, Integer> frecv1, String dictWord) {
        HashMap<Character, Integer> frecv2 = new HashMap<>();
        for (int i = 0; i < dictWord.length(); ++i) {
            if (frecv2.containsKey(dictWord.charAt(i))) {
                frecv2.put(dictWord.charAt(i), frecv2.get(dictWord.charAt(i)) + 1);
            } else {
                frecv2.put(dictWord.charAt(i), 1);
            }
        }

        if (frecvHaveSameCount(frecv2, frecv1)) return false;
        if (frecvHaveSameCount(frecv1, frecv2)) return false;
        return true;
    }

    private boolean frecvHaveSameCount(HashMap<Character, Integer> frecv1, HashMap<Character, Integer> frecv2) {
        for (Character frecv2Char : frecv2.keySet()) {
            if (!frecv1.containsKey(frecv2Char)) return true;
            if (!frecv1.get(frecv2Char).equals(frecv2.get(frecv2Char))) return true;
        }
        return false;
    }
}
