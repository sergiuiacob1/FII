from enum import Enum


class Difficulty(Enum):
    EASY = 0
    MEDIUM = 1
    HARD = 2


class Variable:
    def __init__(self, line, column):
        self.line, self.column = line, column
        self.domain = [i for i in range(1, 10)]
        self.value = None


class Sudoku:
    def __init__(self, difficulty=Difficulty.MEDIUM):
        self.board, self.variables = Sudoku.get_initial_board(difficulty)

    def check_consistency(self):
        ...

    def print_board(self):
        for i in range(0, 9):
            for j in range(0, 9):
                print(self.board[i][j], end=' ')
                if j % 3 == 2:
                    print('|', end=' ')
            if i % 3 == 2:
                print('')
                print('- ' * 12)
            else:
                print('')
        print('\n')

    def solve(self):
        ...

    @staticmethod
    def get_initial_board(difficulty):
        board = [None] * 9
        variables = []
        # this is a list with indexes for variables that don't have a value assigned
        unassigned_variables = []

        for i in range(0, 9):
            # board[i] = [0 for _ in range(0, 9)]
            for j in range(0, 9):
                board[i][j] = 0
                unassigned_variables.append()
                variables.append(Variable(i, j))

        if difficulty == Difficulty.EASY:
            no_of_completed_cells = 70
        elif difficulty == Difficulty.MEDIUM:
            no_of_completed_cells = 50
        else:
            no_of_completed_cells = 25

        for i in range(0, no_of_completed_cells):
            # pick a random

        return board, variables
