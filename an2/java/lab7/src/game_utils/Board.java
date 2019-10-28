package game_utils;

import players.Player;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Board {
    private static List<String> words = new ArrayList<>();
    private static Map<Character, Integer> letterPoints = new HashMap<>();
    private static Game game;

    Board(Game game) {
        this.game = game;
        putPoints(0, ' ');
        putPoints(1, 'e', 'a', 'i', 'o', 'n', 'r', 't', 'l', 's', 'u');
        putPoints(2, 'd', 'g');
        putPoints(3, 'b', 'c', 'm', 'p');
        putPoints(4, 'f', 'h', 'v', 'w', 'y');
        putPoints(5, 'k');
        putPoints(8, 'j', 'x');
        putPoints(10, 'q', 'z');
    }

    private void putPoints(int points, Character... chars) {
        for (Character charVal : chars)
            letterPoints.put(charVal, points);
    }

    public synchronized Integer addWord(Player player, String word) {
        System.out.println(player.getName() + " submitted " + word);
        words.add(word);
        if (game.getDictionary().containsWord(word)) {
            return getWordValue(word);
        } else {
            System.out.println("Word " + word + " doesn't exist");
            return 0;
        }
    }

    public Integer getWordValue(String word) {
        Integer rez = 0;
        for (int i = 0; i < word.length(); ++i)
            rez += letterPoints.get(word.charAt(i));
        return rez;
    }
}