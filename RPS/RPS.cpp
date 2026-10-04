#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//#define CHOICE_ROCK        0
//#define CHOICE_PAPER       1
//#define CHOICE_SCICCORS    2

enum CHOICES
{
    ROCK , PAPER , SCICCORS
};

// Get a valid choice from the player
char getPlayerChoice()
{
    char choice;

    do
    {
        cout << "ENTER : \nr. (Rock) \np. (Paper) \ns. (Scissors)\nchoice :  ";
        cin >> choice;

        if (choice != 'r' && choice != 'p' && choice != 's')
        {
            cout << "INVALID CHOICE. TRY AGAIN.\n";
        }

    } while (choice != 'r' && choice != 'p' && choice != 's');

    return choice;
}


// Generate the computer's choice
char getComputerChoice()
{
    int randomChoice = rand() % 3;

    if (randomChoice == 0)
        //return  CHOICE_ROCK;
        return 'r';
    else if (randomChoice == 1)
        return 'p';
    else
        return 's';
}

// Generate the computer's choice
char getComputerChoice()
{
    int randomChoice = rand() % 3;

    if (randomChoice == 0)
    //return  CHOICE_ROCK;
        return 'r'; 
    else if (randomChoice == 1)
        return 'p';
    else
        return 's';
}


// Determine who won the round
int determineWinner(char player, char computer)
{
    if (player == computer)
    {
        return 0;
    }

    if (
        (player == 'r' && computer == 's') ||
        (player == 'p' && computer == 'r') ||
        (player == 's' && computer == 'p')
        )
    {
        return 1;
    }

    return -1;
}


// Print the result of the round
void printRoundResult(int result)
{
    if (result == 1)
        cout << "YOU WIN THIS ROUND!\n";
    else if (result == -1)
        cout << "COMPUTER WINS THIS ROUND!\n";
    else
        cout << "IT'S A TIE!\n";
}


// Print the final result
void printFinalResult(int playerScore, int computerScore)
{
    cout << "\n====================\n";
    cout << "FINAL SCORE\n";
    cout << "====================\n";
    cout << "YOU: " << playerScore << endl;
    cout << "COMPUTER: " << computerScore << endl;

    if (playerScore > computerScore)
        cout << "OVERALL RESULT: \nYOU WIN !\n";
    else if (computerScore > playerScore)
        cout << "OVERALL RESULT: \nCOMPUTER WINS !\n";
    else
        cout << "OVERALL RESULT: \nIT'S TIE !\n";
}


int main()
{
    srand(time(0));

    int rounds;
    int playerScore = 0;
    int computerScore = 0;

    cout << "\n======================= " << endl;
    cout << "  ROCK PAPER SCICCORS " << endl;
    cout << "======================= " << endl << endl;
    
    cout << "How many rounds do you want to play? ";
    cin >> rounds;


    for (int i = 1; i <= rounds; i++)
    {
                     
        cout << "\n============ " << endl;
        cout << "ROUND " << i << endl;
        cout << "============ " << endl;

        // Get choices
        char player = getPlayerChoice();
        char computer = getComputerChoice();

        // Show choices
        cout << "\nYOU CHOSE : " << player << endl;
        cout << "\nCOMPUTER CHOSE : " << computer << endl;

        // Determine winner
        int result = determineWinner(player, computer);

        // Update score
        if (result == 1)
            playerScore++;
        else if (result == -1)
            computerScore++;

        // Show round result
        printRoundResult(result);

        // Show running score
        cout << "SCORE: YOU " << playerScore
            << " - " << computerScore << " COMPUTER\n";
       
    }


    printFinalResult(playerScore, computerScore);

    return 0;
}