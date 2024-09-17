//==============================================================================
// Written by Taemin Lee
// March 24th 2024
//
// 3DTicTacToe.cpp
// 
// This program manages a 3D Tic-Tac-Toe game on a 3x3x3 board. 
// It allows two or three players to play the game by marking their tokens in the 3D grid. 
// The program takes the input of the board's state and determines the winner by checking all possible winning combinations.
//
// The game board is represented as a 3D array, and the program evaluates numerous winning conditions, including:
// - Rows, columns, and layers
// - Diagonals within each layer
// - 3D diagonals across layers
//
// The program ensures that player tokens are valid and provides feedback for invalid inputs. 
// It also handles the end of the game by announcing the winner or declaring a draw.
//==============================================================================
#include <iostream>
#include <string>
#include <limits>

using namespace std;

// 3x3x3 array
const int SIZE = 3;
// total number of board (27)
const int GRIDSIZE = SIZE * SIZE * SIZE; 
// Set to three so that each players can have same chance of filling the token 
// (27 divisible by 3, 9 chances total)
const int MAXPLAYER = 3; 

char playerTokens(int);
void populateBoard(char [][SIZE][SIZE]);

bool winningBoard(char [][SIZE][SIZE], char);

int row(char [][SIZE][SIZE], int, int, char);
int col(char [][SIZE][SIZE], int, int, char);
int layer(char [][SIZE][SIZE], int, int, char);

int diag(char [][SIZE][SIZE], int, char);
int oppDiag(char [][SIZE][SIZE], int, char);

bool acrossStair(char [][SIZE][SIZE], char);
bool acrossDiag(char [][SIZE][SIZE], char);

//================================================
// main 
// 
// This function populates the 3D game board from
// input prints out the board. Then, it checks 
// and prints out which player has won or draw. 
//
// Parameters: none
// Return value: none (Output message generated)
//================================================
int main() {
    char board[SIZE][SIZE][SIZE] = {
                                    {
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '}
                                    },
                                    {
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '}
                                    },
                                    {
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '},
                                        {' ', ' ', ' '}
                                    }
                                   };
    // Welcome message
    cout << "Welcome to 3D Tic-Tac-Toe!" << endl;

    // Set the number of players
    int numPlayers;
    cout <<"Enter number of Players: " << endl;
    cin >> numPlayers;
    bool correctNumPlayers = false;

    // checks the valid number of players
    while (correctNumPlayers != true){
        if (numPlayers > MAXPLAYER){
            cout << "This game can only be played with players up to 4!" << endl;
            cout << "Enter number of Players: " << endl;
            cin >> numPlayers;
        } else if (numPlayers < 2){
            cout << "Who are you playing with? Check behind you!" << endl;
            cout << "Enter number of Players: " << endl;
            cin >> numPlayers;
        } else {
            correctNumPlayers = true;
        }
    }

    // Set the token of each players
    char PlayerToken[numPlayers];
    int nthPlayer = 1;
    for (; nthPlayer <= numPlayers; nthPlayer++){
        PlayerToken[nthPlayer-1] = playerTokens(nthPlayer);
    }
    nthPlayer = 0;
    
    // Start playing the game
    int row, col, lay;
    bool validPosition = false;
    bool winnerFound = false;
    int gridCounter = 0;
    // Loop until winner is found or the grid is fill
    while (winnerFound == false && gridCounter < GRIDSIZE) {
        populateBoard(board);

        // Place the player's token in a grid
        while (validPosition == false){
            cout << "Player " << PlayerToken[nthPlayer] << ", enter the position for row, column, and layer (0 ~ 2): " << endl;
            cout << "Row: ";
            cin >> row; 
            cout << "Column: ";
            cin >> col;
            cout << "Layer: ";
            cin >> lay;
            // checks whether the input position for each players are valid or not
            if (board[row][col][lay] != ' ' ||
                row > 2 || row < 0 || 
                col > 2 || col < 0 ||
                lay > 2 || lay < 0 ) {
                cout << "Invalid position. Try again.";
            } else {
                board[row][col][lay] = PlayerToken[nthPlayer];
                validPosition = true;
            }
        }

        // Check for the winner
        if (winningBoard(board, PlayerToken[nthPlayer])) {
            populateBoard(board);
            cout << "Player " << PlayerToken[nthPlayer] << " wins!" << endl;
            winnerFound = true;
        } 
        
        // update the number of grid that are marked
        gridCounter++;

        // Exit the loop when winner is found
        if (gridCounter == GRIDSIZE && !winningBoard(board, PlayerToken[nthPlayer])) {
            cout << "It's a draw!" << endl;
        }

        // Update the order of each player
        nthPlayer++;
        nthPlayer%=numPlayers;
        validPosition = false;
    }


    return 0;
}

//====================================================
// playerTokens 
// 
// This function determines the token of each player
// and returns its token.
// 
// Parameter:
//      - player in order (integer)
// Return value: 
//      - token (char)
//====================================================

char playerTokens(int nthplayer){
    string input;
    char playerToken;
    bool correctToken = false;

    while (correctToken != true){
        cout << "Enter your token as a single character (Player " << nthplayer << "): " << endl;
        cin >> input;

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // checks whether the input is valid or not
        if (input.length() == 1){
            playerToken = input[0];
            correctToken = true;
            cout << "Enter your token as a single character(Player " << nthplayer << "): " << endl;
        } else {
            cout << "Enter a valid token (It must be a single character!)" << endl;
        }
    }

    return playerToken;
}

//====================================================
// populateBoard 
// 
// This function populates the 3x3x3 game board
// with Based on number of player.
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
// Return value: void
//====================================================

void populateBoard(char board[][SIZE][SIZE]){

    for (int i = 0; i < SIZE; i++){
        if (i == 0){
            cout << "First layer:" << endl;
        } else if (i == 1) {
            cout << "Second layer:" << endl;
        } else {
            cout << "Third layer:" << endl;
        }
        cout << "----------" << endl; 
        for (int j = 0; j < SIZE; j++){
            cout << "| ";
            for (int k = 0; k < SIZE; k++){
                cout << board[i][j][k] << "| ";
            }
            cout << "\n----------" << endl;
        }
    }

}

//========================================================
// winningBoard 
// 
// This function checks the possible combinations in any
// direction in 3-d game board that determines winner.
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  player - a character which indicates the player (X/O)
//
// Return value: T/F
//========================================================

bool winningBoard(char board[][SIZE][SIZE], char player) {
    bool hasWon = false;
    int countRow, countCol, countLayer, countDiag, countOppDiag;

    // row, col and layer check
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            countRow = row(board, i, j, player);
            countCol = col(board, i, j, player);
            countLayer = layer(board, i, j, player);
            if (countRow == 3 || countCol == 3 || countLayer == 3){
                hasWon = true;
            }
        }
    }

    // Diagonals check (w/o layer)
    for (int i = 0; i < SIZE; i++){
        countDiag = diag(board, i, player);
        countOppDiag = oppDiag(board, i, player);
        if (countDiag == 3 || countOppDiag == 3){
            hasWon = true;
        }
    }
        
    // 3D layer combination check
    bool foundStair = acrossStair(board, player);
    bool foundLayerDiag = acrossDiag(board, player);

    if (foundStair){
        hasWon = true;
    }

    if (foundLayerDiag){
        hasWon = true;
    }

    return hasWon;
}

//==========================================================
// row 
// 
// This function checks how many times each players(X/O)
// appear in a row based on the parameter (char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  layerIndex - an integer that determines the layer index
//  rowIndex - an integer that determines the row index
//  player - a character that indicates a player ('X'/'O')
//
// Return value:
//  - integer (# of player's appearance in a row)
//==========================================================

int row (char board[][SIZE][SIZE], int layerIndex, int rowIndex, char player){
    int count = 0;
    for (int i = 0; i < SIZE; i++){
        if (board[layerIndex][rowIndex][i] == player){
            count++;
        }
    }

    return count;
}

//==========================================================
// col 
// 
// This function checks how many times each players(X/O)
// appear in a column based on the parameter (char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  layerIndex - an integer that determines the layer index
//  colIndex - an integer that determines the column index
//  player - a character that indicates a player ('X'/'O')
// 
// Return value:
//  - integer (# of player's appearance in a column)
//==========================================================

int col (char board[][SIZE][SIZE], int layerIndex, int colIndex, char player){
    int count = 0;
    for (int i = 0; i < SIZE; i++){
        if (board[layerIndex][i][colIndex] == player){
            count++;
        }
    }

    return count;
}

//==========================================================
// layer 
// 
// This function checks how many times each players(X/O)
// appear in a layer based on the parameter (char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  rowIndex - an integer that determines the row index
//  colIndex - an integer that determines the column index
//  player - a character that indicates a player ('X'/'O')
// 
// Return value:
//  - integer (# of player's appearance in a layer)
//==========================================================

int layer (char board[][SIZE][SIZE], int rowIndex, int colIndex , char player){
    int count = 0;
    for (int i = 0; i < SIZE; i++){
        if (board[i][rowIndex][colIndex] == player){
            count++;
        }
    }

    return count;
}

//==========================================================
// diag 
// 
// This function checks how many times each players(X/O)
// appear in a 2-d diagonal based on the parameter(char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  layerIndex - an integer that determines the layer index
//  player - a character that indicates a player ('X'/'O')
// 
// Return value:
//  - integer (# of player's appearance in a 2-d diagonal)
//==========================================================

int diag (char board[][SIZE][SIZE], int layerIndex, char player){
    int count = 0;
    for (int i = 0; i < SIZE; i++){
        if (board[layerIndex][i][i] == player){
            count++;
        }
    }

    return count;
}

//==========================================================
// oppDiag 
// 
// This function checks how many times each players(X/O)
// appear in a 2-d opposite diagonal based on the parameter
// (char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  layerIndex - an integer that determines the layer index
//  player - a character that indicates a player ('X'/'O')
// 
// Return value:
//  - integer (# of player's appearance in a 2-d opposite diagonal)
//==========================================================

int oppDiag (char board[][SIZE][SIZE], int layerIndex, char player){
    int count = 0;
    for (int i = 0; i < SIZE; i++){
        if (board[layerIndex][i][SIZE - i - 1] == player){
            count++;
        }
    }

    return count;
}

//==========================================================
// acrossStair 
// 
// This function checks how many times each players(X/O)
// appear in a 3-d stair based on the parameter(char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  player - a character that indicates a player ('X'/'O')
// 
// Return value:
//  - T/F
//==========================================================

bool acrossStair (char board[][SIZE][SIZE], char player){
    bool isFound = false;
    
    
    if (board[0][0][1] == player && board[1][1][1] == player && board[2][2][1] == player){
        isFound = true;
    } else if (board[0][1][2] == player && board[1][1][1] == player && board[2][1][0] == player){
        isFound = true;
    } else if (board[0][1][0] == player && board[1][1][1] == player && board[2][1][2] == player){
        isFound = true;
    } else if (board[0][2][1] == player && board[1][1][1] == player && board[2][0][1] == player){
        isFound = true;
    }

    return isFound;
}

//==========================================================
// acrossDiag
// 
// This function checks how many times each players(X/O)
// appear in a 3-d diagonal based on the parameter(char player)
// 
// Parameter:
//  board - 3d char array that is SIZE x SIZE x SIZE
//          containing X/O
//  player - a character that indicates a player ('X'/'O')
// 
// Return value:
//  - T/F
//==========================================================

bool acrossDiag (char board[][SIZE][SIZE], char player){
    bool isFound = false;
    
    if (board[0][0][0] == player && board[1][1][1] == player && board[2][2][2] == player){
        isFound = true;
    } else if (board[2][0][0] == player && board[1][1][1] == player && board[0][2][2] == player){
        isFound = true;
    } else if (board[0][0][2] == player && board[1][1][1] == player && board[2][2][0] == player){
        isFound = true;
    } else if (board[0][2][0] == player && board[1][1][1] == player && board[2][0][2] == player){
        isFound = true;
    }

    return isFound;
}