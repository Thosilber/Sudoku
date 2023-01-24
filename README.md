# Sudoku
CS211 final project consisting of building a Sudoku game using C++ and the ge211 game engine


SPECS:

1. The game opens on a selection page where the user can select whether to play an easy or hard game. Easy being a board whose pre inputted numbers make it easier to solve. By clicking on each button, the board will show up on the screen and the user will be able to play.

2. When a player hovers over a specific box that can be played (all boxes except the ones that are automatically generated when starting the game), it should get highlighted in blue. 

3. To select what number 1-9 a player wants to input into a box, they press the respective key into their keyboard and then click on the box they want to make the move in.

4. The program confirms the input is a valid entry by checking it is not present in the current row, column, or bounding 3x3 box. In this case the number is displayed on the screen and “good job” is displayed below the board.

5. If an input is invalid (input is already present in the current row, column, or bounding 3x3 box),  the input box will be highlighted in red and the rest of the board will be blurred until the invalid move is deleted. “Try Again!” Will also be displayed below the board.

6. The user can delete a number they input by clicking shift on their keyboard and then pressing on the cell they want to make empty again.

7. While playing the game the user can generate no errors. If the user attempts to add in a keyboard value not 1-9, the game shows no error. Additionally, the user can attempt to delete an already blank cell with no error.

8. If the board is successfully completed, all cells will turn green and a message will appear saying you won.

9. The game will compute a score for a board once completed. The score will be based on the number of moves (clicks) to reach the solution whereas a message with either "excellent", "good", or "okay" will appear on the final screen when the game is finished depending on the amount of clicks that the user did.

10. The user can click a start over button on the game completed screen which will allow the user to return to the menu page and play again.
