import os
import sys
import random


def lottery(max_nr, draw_size, no_players):
    randoms = [[random.randint(1, max_nr) for _ in range(0, draw_size)]
               for _ in range(0, no_players)]
    guesses = []
    for player in range(0, no_players):
        options = input(
            f'Player {player + 1}, please enter {draw_size} numbers between 1 and {max_nr}: ')
        options = [int(x) for x in options.split(' ')]
        guesses.append(options)
    print('\n')
    for player in range(0, no_players):
        no_guessed = sum(
            [1 if x == y else 0 for x, y in zip(randoms[player], guesses[player])])
        print(f'Generated: {randoms[player]}')
        print(f'Guesses: {guesses[player]}')
        print(f'Player {player + 1} guessed {no_guessed} numbers\n')


if __name__ == '__main__':
    max_nr = int(sys.argv[1])
    draw_size = int(sys.argv[2])
    no_players = int(sys.argv[3])
    lottery(max_nr, draw_size, no_players)
