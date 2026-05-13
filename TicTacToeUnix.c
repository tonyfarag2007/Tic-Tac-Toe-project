#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#define MAX_SIZE 10 // Maximum board size

//Global struct and enums to allow easy access by multiple functions

// Struct for game stats that tracks game and draw counts, and win types
typedef struct {
    int gamesPlayed;
    int draws;
    int verticalWins;
    int horizontalWins;
    int diagonalWins;
    int antiDiagonalWins;
} GameStats;
    GameStats stats;

// Win-based enum that is used by checkWin(), which returns the win type and is used to create game stats
    typedef enum{
        NO_WIN,
        HORIZONTAL_WIN,
        VERTICAL_WIN,
        DIAGONAL_WIN,
        ANTI_DIAGONAL_WIN
    } WinResult;

// Draw-based enum used by checkDraw()
    typedef enum{
        NO_DRAW,
        DRAW
    }DrawResult;
typedef enum {
    PVP = 1,
    PVAI = 2
} GameMode;
int size;
GameMode mode;
char board[MAX_SIZE][MAX_SIZE]; // tic-tac-toe board
void gameLoop();

// Initializes a 2D array with empty spaces. @param size: sets the dimensions for the N x N grid (3-10).
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size){
printf("\nGAME STARTED!\n\n");
for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
        board[i][j] = ' ';
        printf("[%c]", board[i][j]);
    }
    printf("\n");
}
}

// Prints the updated board
void updateBoard(char board[MAX_SIZE][MAX_SIZE], int size){
system("clear"); // Clears the console screen
printf("\n");
for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
        printf("[%c]", board[i][j]);
    }
    printf("\n");
}
}

/*Evaluates the current board state and
  returns a WinResult enum to identify the specific win pattern detected.
  Tracking different win types is important for statistics*/
WinResult checkWin(char board[MAX_SIZE][MAX_SIZE], int size){
    // Horizontal win detector
for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
        if(board[i][j] != board[i][0] || board[i][j] == ' '){
            break;
    }
    if(j == size-1){
    return HORIZONTAL_WIN;
}
}
}
// Vertical win detector
for(int i = 0; i<size; i++){
    for(int j = 0; j<size; j++){
        if(board[j][i] != board[0][i] || board[j][i] == ' '){
            break;
        }
        if(j == size-1){
    return VERTICAL_WIN;
}
    }
}
// Diagonal win detector
for(int i = 0, j = 0; i<size && j<size; i++, j++){
    if(board[i][j] != board[0][0] || board[i][j] == ' '){
        break;
    }

if(j == size - 1){
    return DIAGONAL_WIN;
}
}
// Anti-diagonal win detector
for(int i = 0, j = size-1; i <size && j >=0; i++, j--){
    if(board[i][j] != board[0][size - 1] || board[i][j] == ' '){
        break;
    }
    if(i == size - 1){
        return ANTI_DIAGONAL_WIN;
    }
}
return NO_WIN; // Does not return a win if no win is detected
}
void updateScore(char winner);
void createGameStats();
void printGameStats();

/*Manual exception handling for different types of errors
    such as invalid cell locations, invalid input type, etc*/

void processMove(int size, int *row, int *column) {
    char buffer[100];
    bool isValidInput = false;
    do {
        fgets(buffer, sizeof(buffer), stdin);
        if(sscanf(buffer, "%d %d", row, column) != 2){
            printf("Please enter at least two numbers for the row and column: ");
        }
        else if(*row > size || *column > size || *row < 1 || *column < 1){
            printf("Invalid cell location, try again: ");
        }
        else if(board[*row - 1][*column -1] != ' '){
            printf("Cell already occupied, try again: ");
        }
        else {
            isValidInput = true;
        }
    }while (!isValidInput);
}
// Draw detector, returns a draw if checkWin() does not return a win and all cells are occupied
DrawResult checkDraw(char board[MAX_SIZE][MAX_SIZE], int size){
    if (checkWin(board, size)!= NO_WIN) {
        return NO_DRAW;
    }
    for(int r = 0; r<size; r++){
        for(int s = 0; s<size; s++){
            if(board[r][s] == ' '){
                return NO_DRAW;
            }
        }
    }
    return DRAW;
}
void pvpMode(char board[MAX_SIZE][MAX_SIZE], int size);
void pvaiMode(char board[MAX_SIZE][MAX_SIZE], int size);
// Replay function that prompts user to play again, return to main menu, or exit the program
void playAgain(GameMode mode){
    char choice;
    printf("\nY. Play again \n");
    printf("M. Return to main menu \n");
    printf("N. Exit\n");
    char buffer[100];
    // Reads an entire line via fgets() and sscanf() and reprompting the user if the input is invalid until they input anything valid
    fgets(buffer, sizeof(buffer), stdin);
     sscanf(buffer, " %c", &choice);
    while(choice != 'Y' && choice != 'N' && choice != 'M' && choice != 'y' && choice != 'n' && choice!= 'm'){
        printf("Invalid input, try again: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, " %c", &choice);
    }
    if(choice == 'Y' || choice == 'y'){
        if(mode == PVP){
        system("clear");
        initializeBoard(board, size);
        pvpMode(board, size);
        }
        else if(mode == PVAI){
            system("clear");
            initializeBoard(board, size);
            pvaiMode(board, size);
        }
    }
    else if(choice == 'N' || choice == 'n'){
        printf("Thanks for playing!");
        sleep(1);
        exit(0);
    }
    else{
        system("clear");
        gameLoop();
    }
}
int main(){
    srand(time(NULL));
    gameLoop();
    return 0;
    }
    // gameLoop() handles main menu logic such as starting a new game, viewing game stats, and exiting
    void gameLoop(){
        printf("TIC TAC TOE GAME\n");
        printf("\n||-- MAIN MENU --||\n");
    printf("\n1. NEW GAME (Player vs Player)\n");
    printf("\n2. NEW GAME (Player vs AI)\n");
    printf("\n3. Game Statistics\n");
    printf("\n4. Exit\n");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
    int temp;
    sscanf(buffer, "%d", &temp);

    while(temp != 1 && temp != 2 && temp != 3 && temp != 4){
        printf("Invalid input, try again: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &temp);
        }
        system("clear");
    if (temp == 1){
        printf("\nPlayer vs Player selected, enter the board size (3-10): ");
    }
    else if(temp == 2){
        printf("\nPlayer vs AI selected, enter the board size (3-10): ");
    }
    else if(temp == 3){
        printGameStats();
        printf("\n1. Return to Main Menu");
        printf("\n2. Save File\n");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &temp);
        while(temp != 1 && temp != 2){
            printf("Invalid input, try again: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &temp);
        }
        if(temp == 1){
        system("clear");
        gameLoop();
        }
        else{
            FILE *statistics = fopen("stats.txt", "w"); // creates a new file that stores game stats
            if(statistics == NULL){
                printf("File not found");
            }
            else{
                fprintf(statistics, "||-- GAME STATS --||\n");
                fprintf(statistics, "Games Played: %d\n", stats.gamesPlayed);
                fprintf(statistics, "Vertical Wins: %d\n", stats.verticalWins);
                fprintf(statistics, "Horizontal Wins: %d\n", stats.horizontalWins);
                fprintf(statistics, "Diagonal Wins: %d\n", stats.diagonalWins);
                fprintf(statistics, "Anti Diagonal Wins: %d\n", stats.antiDiagonalWins);
                fprintf(statistics, "Draws: %d\n", stats.draws);
                printf("File saved successfully!");
                fclose(statistics);
            }
        }
        sleep(1);
        system("clear");
        gameLoop();
    }
    else{
        printf("Thanks for playing!");
        exit(0);
    }
    fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &size);
    while(size < 3 || size > 10){
        printf("Invalid board size, try again: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &size);
    }
    if(size>=3 && size<=10){
        system("clear");
    initializeBoard(board, size);
    }
    mode = (GameMode)temp;
    if(mode == PVP){
        pvpMode(board, size);
    }
    else{
        pvaiMode(board, size);
    }
    }
    // Handles gameplay logic in Pvp mode
    void pvpMode(char board[MAX_SIZE][MAX_SIZE], int size){
    int row, column;
    char currentPlayer = 'X';
    while(1){
    printf("\nPlayer %c's turn\n", currentPlayer);
    printf("Enter row and column (1-%d): ", size);
        processMove(size, &row, &column);
    board[row - 1][column - 1] = currentPlayer;
    updateBoard(board, size); // Updates board based on player input

    // Win checks after each turn
    if(checkWin(board, size) != NO_WIN){
        sleep(1);
        printf("\nGame over, player %c won!\n", currentPlayer);
        sleep(1);
        updateScore(currentPlayer);
        break;
    }
    // Draw checks after each turn
    if(checkDraw(board, size) == DRAW){
        sleep(1);
        printf("\nThe game is a draw!\n");
        sleep(1);
        updateScore('N');
        break;
    }
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Switch between X and O players
}
    }
    // Score tracker that supports both game modes
    void updateScore(char winner){
    static int xScorePvp = 0, oScorePvp = 0, xScorePvai = 0, oScorePvai = 0;
    if(mode == PVP){
        if(winner == 'X'){
            xScorePvp++;
        }
        else if (winner == 'O'){
            oScorePvp++;
        }
        printf("\nThe current score is\n");
    printf("\nX: %d vs O: %d\n", xScorePvp, oScorePvp);
    createGameStats();
    playAgain(mode);
    }
    else{
        if(winner == 'X'){
            xScorePvai++;
        }
        else if(winner == 'O'){
            oScorePvai++;
        }
        printf("\nThe current score is\n");
    printf("\nPlayer: %d vs AI: %d\n", xScorePvai, oScorePvai);
    createGameStats();
    playAgain(mode);
    }

}
// Handles gameplay logic in PvAI mode
void pvaiMode(char board[MAX_SIZE][MAX_SIZE], int size){
    int row, column;
    while(1){
    printf("\nPlayer's turn\n");
    printf("Enter row and column (1-%d): ", size);
        processMove(size, &row, &column);
    board[row - 1][column - 1] = 'X'; // Placing 'X' based on user input
    updateBoard(board, size);
    // Check win after each player move
    if(checkWin(board, size) != NO_WIN){
        sleep(1);
        printf("\nGame over, player won!\n");
        sleep(1);
        updateScore('X');
        break;
    }
    // Check draw after each player move
    if(checkDraw(board, size) == DRAW){
        sleep(1);
        printf("\nThe game is a draw!\n");
        sleep(1);
        updateScore('N');
        break;
    }
    printf("\nAI's turn\nthinking ...\n");
        /* Artificial delay to improve UX by
        simulating a "thinking" phase for the computer opponent*/
    int aiThink = rand() % 4 + 1;
    sleep(aiThink);

    /* AI decision-making hierarchical logic (Win > Block > Random, a basic look-ahead search):
    - Plays the winning move if available (Win-player algorithm)
    - Blocks player from winning if available (Win blocking algorithm)
    - Plays random move (random move algorithm)
    */

    // Win-player algorithm
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(board[i][j] == ' '){
                /* Iterates through each empty cell and temporary places 'O' to check if AI can win in the next turn.
                If valid, AI plays that move and wins*/
                board[i][j] = 'O';
                if(checkWin(board, size) != NO_WIN){
                    updateBoard(board, size);
                    sleep(1);
                    printf("\nGame over, AI won!\n");
                    sleep(1);
                    updateScore('O');
                    return;
                }
                board[i][j] = ' '; // If no winning move is possible, replace 'O' with empty char to restore old board
            }
        }
    }

    // Win blocking algorithm
    for(int i = 0; i<size; i++){
        for(int j = 0; j<size; j++){
            if(board[i][j] == ' '){
            /* Iterate through each empty cell and temporary place 'X' to check if player would win if it's played,
            then AI places 'O' on that exact cell to prevent player from winning*/
            board[i][j] = 'X';
            if(checkWin(board, size) != NO_WIN){
                board[i][j] = 'O';
                updateBoard(board, size);
                goto after_ai_move;
                }
                board[i][j] = ' '; // If no win-blocking moves are possible, replaces 'X' with empty char to restore old board

            }
        }
        }

    // Random move algorithm
    while(1){
    int rng1 = rand() % size;
    int rng2 = rand() % size;
        if(board[rng1][rng2] == ' '){
            board[rng1][rng2] = 'O';
            break;
        }
    }

    updateBoard(board, size);
    after_ai_move:
    // Check win after each AI move
    if(checkWin(board, size) != NO_WIN){
        sleep(1);
        printf("\nGame over, AI won!\n");
        sleep(1);
        updateScore('O');
        break;
    }
    // Check draw after each AI move
    if(checkDraw(board, size) == DRAW){
        sleep(1);
        printf("The game is a draw!\n");
        sleep(1);
        updateScore('N');
        break;
    }
}
}
// Printing stats created by createGameStats()
void printGameStats(){
    printf("\n||-- GAME STATS --||\n");
    printf("Games Played: %d\n", stats.gamesPlayed);
    printf("Vertical Wins: %d\n", stats.verticalWins);
    printf("Horizontal Wins: %d\n", stats.horizontalWins);
    printf("Diagonal Wins: %d\n", stats.diagonalWins);
    printf("Anti Diagonal Wins: %d\n", stats.antiDiagonalWins);
    printf("Draws: %d\n", stats.draws);
}
// Stats creator, it tracks games played, win types, and draw count
void createGameStats(){
    WinResult win = checkWin(board, size);
    DrawResult draw = checkDraw(board, size);
    stats.gamesPlayed++;
    if(draw == DRAW){
        stats.draws++;
    }
    else if(win == HORIZONTAL_WIN){
    stats.horizontalWins++;
    }
    else if(win == VERTICAL_WIN){
        stats.verticalWins++;
    }
    else if(win == DIAGONAL_WIN){
    stats.diagonalWins++;
    }
    else if(win == ANTI_DIAGONAL_WIN){
    stats.antiDiagonalWins++;
    }
}