__doc__ = "Solves Sudoku using fancy strategies"

from sudoku import Sudoku, Difficulty

if __name__ == '__main__':
    sudoku = Sudoku(difficulty=Difficulty.HARD)
    sudoku.print_board()
    # sudoku.solve()
    # sudoku.print_board()