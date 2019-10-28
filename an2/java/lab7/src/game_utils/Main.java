package game_utils;

import players.PlayerAuto;
import players.PlayerGreedy;
import players.PlayerRandom;

public class Main {
    public static void main(String args[]) {
        Game game = new Game();
        game.setBag(new Bag());
        game.setBoard(new Board(game));
        game.addPlayer(new PlayerRandom("players.Player 1"));
        game.addPlayer(new PlayerAuto("players.Player 2"));
        game.addPlayer(new PlayerGreedy("players.Player 3"));
        game.start();
    }
}