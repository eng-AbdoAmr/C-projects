#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <algorithm>
#include <string>

using namespace std;


// ============================================================
// CONSTANTS
// ============================================================

// Starting value for the hard computer's best score
#define INIT_BEST_SCORE -1000



// ============================================================
// BOARD FUNCTIONS
// ============================================================

// Fill every board position with an empty space
void initializeBoard(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}



// ============================================================
// PRINT BOARD
// ============================================================

// Display game board and position guide side by side
void printBoard(char board[3][3])
{
    // Clear previous screen
    cout << "\033[2J\033[H";

    cout << "\n";

    // Titles
    cout << "          GAME BOARD                 POSITION GUIDE\n";

    // Top borders
    cout << "       +-----+-----+-----+        +-----+-----+-----+\n";

    // Row 1
    cout << "       |  " << board[0][0] << "  |  "
        << board[0][1] << "  |  "
        << board[0][2] << "  |";

    cout << "        |  1  |  2  |  3  |\n";

    // Separator
    cout << "       +-----+-----+-----+        +-----+-----+-----+\n";

    // Row 2
    cout << "       |  " << board[1][0] << "  |  "
        << board[1][1] << "  |  "
        << board[1][2] << "  |";

    cout << "        |  4  |  5  |  6  |\n";

    // Separator
    cout << "       +-----+-----+-----+        +-----+-----+-----+\n";

    // Row 3
    cout << "       |  " << board[2][0] << "  |  "
        << board[2][1] << "  |  "
        << board[2][2] << "  |";

    cout << "        |  7  |  8  |  9  |\n";

    // Bottom borders
    cout << "       +-----+-----+-----+        +-----+-----+-----+\n";

    cout << "\n";
}



// ============================================================
// WIN / DRAW CHECKS
// ============================================================

// Check rows, columns, and diagonals for a winner
bool checkWinner(char board[3][3], char player)
{
    // Check rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player &&
            board[i][1] == player &&
            board[i][2] == player)
        {
            return true;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player &&
            board[1][i] == player &&
            board[2][i] == player)
        {
            return true;
        }
    }

    // Check main diagonal
    if (board[0][0] == player &&
        board[1][1] == player &&
        board[2][2] == player)
    {
        return true;
    }

    // Check other diagonal
    if (board[0][2] == player &&
        board[1][1] == player &&
        board[2][0] == player)
    {
        return true;
    }

    // No winning line found
    return false;
}



// Check whether the board is completely full
bool checkDraw(char board[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Empty position means game is not a draw
            if (board[i][j] == ' ')
            {
                return false;
            }
        }
    }

    // No empty positions
    return true;
}



// ============================================================
// PLAYER MOVE
// ============================================================

// Get and validate player's position
void playerMove(char board[3][3], char player)
{
    int position;

    while (true)
    {
        cout << "Player " << player
            << ", choose a position (1-9): ";

        cin >> position;

        // Handle non-numeric input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Invalid input. Enter a number from 1 to 9.\n";
            continue;
        }

        // Check range
        if (position < 1 || position > 9)
        {
            cout << "Choose a number from 1 to 9.\n";
            continue;
        }

        // Convert position 1-9 into row and column
        int row = (position - 1) / 3;
        int col = (position - 1) % 3;

        // Check whether position is already occupied
        if (board[row][col] != ' ')
        {
            cout << "That position is already occupied.\n";
            continue;
        }

        // Place player's symbol
        board[row][col] = player;

        break;
    }
}



// ============================================================
// EASY COMPUTER
// ============================================================

// Choose a random empty position
void easyComputerMove(char board[3][3])
{
    int row;
    int col;

    do
    {
        // Generate random row and column
        row = rand() % 3;
        col = rand() % 3;

    } while (board[row][col] != ' ');

    // Place computer's symbol
    board[row][col] = 'O';

    // Show selected position
    cout << "Computer chose position "
        << row * 3 + col + 1 << ".\n";
}



// ============================================================
// MINIMAX
// HARD COMPUTER
// ============================================================

// Calculate the best possible score from a board position
int minimax(char board[3][3], bool isComputerTurn)
{
    // Computer wins
    if (checkWinner(board, 'O'))
    {
        return 10;
    }

    // Player wins
    if (checkWinner(board, 'X'))
    {
        return -10;
    }

    // Draw
    if (checkDraw(board))
    {
        return 0;
    }


    // --------------------------------------------------------
    // COMPUTER TURN
    // Maximize score
    // --------------------------------------------------------

    if (isComputerTurn)
    {
        int bestScore = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Find empty position
                if (board[i][j] == ' ')
                {
                    // Try computer move
                    board[i][j] = 'O';

                    // Simulate player's response
                    int score = minimax(board, false);

                    // Undo move
                    board[i][j] = ' ';

                    // Keep highest score
                    bestScore = max(bestScore, score);
                }
            }
        }

        return bestScore;
    }


    // --------------------------------------------------------
    // PLAYER TURN
    // Minimize score
    // --------------------------------------------------------

    else
    {
        int bestScore = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                // Find empty position
                if (board[i][j] == ' ')
                {
                    // Try player's move
                    board[i][j] = 'X';

                    // Simulate computer response
                    int score = minimax(board, true);

                    // Undo move
                    board[i][j] = ' ';

                    // Keep lowest score
                    bestScore = min(bestScore, score);
                }
            }
        }

        return bestScore;
    }
}



// ============================================================
// HARD COMPUTER MOVE
// ============================================================

// Find and play the move with the highest minimax score
void hardComputerMove(char board[3][3])
{
    // Best score found so far
    int bestScore = INIT_BEST_SCORE;

    // Best move coordinates
    int bestRow = -1;
    int bestCol = -1;


    // Test every empty position
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == ' ')
            {
                // Temporarily make the move
                board[i][j] = 'O';

                // Calculate result of this move
                int score = minimax(board, false);

                // Undo temporary move
                board[i][j] = ' ';


                // Save better move
                if (score > bestScore)
                {
                    bestScore = score;

                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    // Make the best move
    board[bestRow][bestCol] = 'O';

    // Display selected position
    cout << "Computer chose position "
        << bestRow * 3 + bestCol + 1 << ".\n";
}



// ============================================================
// PLAYER VS PLAYER
// ============================================================

// Run Player vs Player games
void playerVsPlayer()
{
    // Player names are entered only once
    string player1Name;
    string player2Name;

    cout << "\nENTER PLAYER 1 NAME (X): ";
    getline(cin >> ws, player1Name);

    cout << "ENTER PLAYER 2 NAME (O): ";
    getline(cin, player2Name);


    // Keep playing PvP until the user chooses N
    while (true)
    {
        // Create a fresh board for every new game
        char board[3][3];

        initializeBoard(board);

        char currentPlayer = 'X';


        // ----------------------------------------------------
        // GAME LOOP
        // ----------------------------------------------------

        while (true)
        {
            printBoard(board);

            // Show correct player name
            if (currentPlayer == 'X')
            {
                cout << "Player 1 - "
                    << player1Name
                    << "'s turn (X)\n";
            }
            else
            {
                cout << "Player 2 - "
                    << player2Name
                    << "'s turn (O)\n";
            }

            playerMove(board, currentPlayer);


            // Check winner
            if (checkWinner(board, currentPlayer))
            {
                printBoard(board);

                if (currentPlayer == 'X')
                {
                    cout << "\n GAME OVER !! PLAYER 1 - "
                        << player1Name
                        << " WINS!\n";
                }
                else
                {
                    cout << "\n GAME OVER !! PLAYER 2 - "
                        << player2Name
                        << " WINS!\n";
                }

                break;
            }


            // Check draw
            if (checkDraw(board))
            {
                printBoard(board);

                cout << "\n IT'S A DRAW!\n";

                break;
            }


            // Switch players
            if (currentPlayer == 'X')
            {
                currentPlayer = 'O';
            }
            else
            {
                currentPlayer = 'X';
            }
        }


        // ----------------------------------------------------
        // PLAY AGAIN
        // ----------------------------------------------------

        char choice;

        while (true)
        {
            cout << "\n PLAY AGAIN IN PLAYER VS PLAYER MODE? (y/n): ";
            cin >> choice;

            // Y = start another PvP game
            if (choice == 'y' || choice == 'Y')
            {
                break;
            }

            // N = leave PvP and return to main menu
            if (choice == 'n' || choice == 'N')
            {
                return;
            }

            // Anything else is invalid
            cout << "INVALID CHOICE. PLEASE ENTER y OR n.\n";
        }
    }
}



// ============================================================
// PLAYER VS COMPUTER
// ============================================================

// Run Player vs Computer games
void playerVsComputer(int difficulty)
{
    // Keep playing PvC until the user chooses N
    while (true)
    {
        // Create a fresh board for every new game
        char board[3][3];

        initializeBoard(board);


        // ----------------------------------------------------
        // GAME LOOP
        // ----------------------------------------------------

        while (true)
        {
            // ------------------------------------------------
            // PLAYER TURN
            // ------------------------------------------------

            printBoard(board);

            // Player is always X
            playerMove(board, 'X');


            // Check player win
            if (checkWinner(board, 'X'))
            {
                printBoard(board);

                cout << "\n GAME OVER !! YOU WIN! \n";

                break;
            }


            // Check draw
            if (checkDraw(board))
            {
                printBoard(board);

                cout << "\n IT'S A DRAW !\n";

                break;
            }


            // ------------------------------------------------
            // COMPUTER TURN
            // ------------------------------------------------

            cout << "\nComputer's turn...\n";


            // Choose computer difficulty
            if (difficulty == 1)
            {
                // Random move
                easyComputerMove(board);
            }
            else
            {
                // Minimax move
                hardComputerMove(board);
            }


            // Check computer win
            if (checkWinner(board, 'O'))
            {
                printBoard(board);

                cout << "\n GAME OVER !! YOU LOSE!\n";

                break;
            }


            // Check draw
            if (checkDraw(board))
            {
                printBoard(board);

                cout << "\n IT'S A DRAW !\n";

                break;
            }
        }


        // ----------------------------------------------------
        // PLAY AGAIN
        // ----------------------------------------------------

        char choice;

        while (true)
        {
            cout << "\nPLAY AGAIN IN PLAYER VS COMPUTER MODE? (y/n): ";
            cin >> choice;

            // Y = start another PvC game
            // Same difficulty is kept
            if (choice == 'y' || choice == 'Y')
            {
                break;
            }

            //leave PvC and return to main menu
            if (choice == 'n' || choice == 'N')
            {
                return;
            }

            // Anything else is invalid
            cout << "INVALID CHOICE. PLEASE ENTER y OR n.\n";
        }
    }
}



// ============================================================
// MAIN MENU
// ============================================================

int main()
{
    // Initialize random number generator
    srand(time(0));


    // Keep showing menu until exit
    while (true)
    {
        // Clear previous screen
        cout << "\033[2J\033[H";
        
        cout << "\n=========================\n";
        cout << "       TIC TAC TOE\n";
        cout << "=========================\n";

        cout << "1. PLAYER VS PLAYER\n";
        cout << "2. PLAYER VS COMPUTER\n";
        cout << "3. EXIT\n";

        cout << "CHOOSE: ";


        int mode;
        cin >> mode;


        // ----------------------------------------------------
        // EXIT
        // ----------------------------------------------------

        if (mode == 3)
        {
            cout << "GOODBYE!\n";
            break;
        }


        // ----------------------------------------------------
        // PLAYER VS PLAYER
        // ----------------------------------------------------

        if (mode == 1)
        {
            playerVsPlayer();
        }


        // ----------------------------------------------------
        // PLAYER VS COMPUTER
        // ----------------------------------------------------

        else if (mode == 2)
        {
            cout << "\n CHOOSE DIFFICULTY:\n";
            cout << "1. EASY\n";
            cout << "2. HARD\n";

            cout << "CHOOSE: ";


            int difficulty;
            cin >> difficulty;


            // Validate difficulty
            while (difficulty != 1 && difficulty != 2)
            {
                cout << "Choose 1 or 2: ";
                cin >> difficulty;
            }


            // Start Player vs Computer mode
            playerVsComputer(difficulty);
        }


        // ----------------------------------------------------
        // INVALID MENU OPTION
        // ----------------------------------------------------

        else
        {
            cout << "INVALID CHOICE.\n";
            continue;
        }


       
    }


    return 0;
}

