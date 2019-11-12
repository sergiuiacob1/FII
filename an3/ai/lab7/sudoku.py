from enum import Enum
import random
from itertools import product


class Difficulty(Enum):
    EASY = 0
    MEDIUM = 1
    HARD = 2


class Variable:
    def __init__(self, line, column):
        self.line, self.column = line, column
        self.domain = set([i for i in range(1, 10)])
        self.value = None

    def __str__(self):
        return f'Variable({self.line + 1, self.column + 1}), value: {self.value}'


class Sudoku:
    def __init__(self, difficulty=Difficulty.MEDIUM):
        self.build_initial_board(difficulty)

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

    def forward_checking(self, variable: Variable, value_added=None, value_removed=None):
        """We suppose that `variable` was just updated. So we must update the domain for the rest of variables

        If `value_added is not None`, then our `variable` has been updated to take on that value.
        So for all the 'neigbours' of `variable`, we update their domains and exclude `value_added`

        if `value_removed is not None`, then our `variable` was unassigned and its neighbours can now take the `value_removed`
        """
        neighbours = self.get_variable_neighbours(variable)

        if value_added is not None:
            variable.value = value_added
            variable.domain.remove(value_added)
            for neighbour in neighbours:
                neighbour.domain.discard(value_added)
        elif value_removed is not None:
            variable.value = None
            variable.domain.append(value_removed)
            for neighbour in neighbours:
                neighbour.domain.add(value_added)

    def get_variable_neighbours(self, variable: Variable):
        """A neighbour is a position that is on the same line, column or mini-square as my given `variable`"""
        neighbours = []
        variable_square = self.get_variable_square(variable)
        for neighbour in self.variables:
            neighbour_square = self.get_variable_square(neighbour)
            if neighbour.line == variable.line or neighbour.column == variable.column or neighbour_square == variable_square:
                neighbours.append(neighbour)
        return neighbours

    def get_variable_square(self, variable: Variable):
        """Returns the mini-square for this variable

        The first mini-square (top left, 3x3) is number 0. The next one (top center, 3x3) is number 1 and so on."""
        return (variable.line // 3) * 3 + (variable.column // 3)

    def build_initial_board(self, difficulty):
        self.board = [None] * 9
        self.variables = [Variable(pos[0], pos[1])
                          for pos in list(product([i for i in range(0, 9)], repeat=2))]

        # this is a list with indexes for variables that don't have a value assigned
        unassigned_variables = [i for i in range(0, len(self.variables))]

        if difficulty == Difficulty.EASY:
            no_of_completed_cells = 50
        elif difficulty == Difficulty.MEDIUM:
            no_of_completed_cells = 30
        else:
            no_of_completed_cells = 20

        for i in range(0, no_of_completed_cells):
            # pick a random variable unassigned variable and assign it
            choice = random.choice(unassigned_variables)
            unassigned_variables.remove(choice)
            value_assigned = random.choice(
                tuple(self.variables[choice].domain))
            self.forward_checking(
                self.variables[choice], value_added=value_assigned)

        for i in range(0, 9):
            self.board[i] = [0 for _ in range(0, 9)]
        for i in range(0, len(self.variables)):
            if self.variables[i].value is not None:
                self.board[self.variables[i].line][self.variables[i]
                                                   .column] = self.variables[i].value
