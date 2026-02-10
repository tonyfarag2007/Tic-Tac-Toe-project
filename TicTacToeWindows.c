#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define MAX_SIZE 10 // Maximum grid size

typedef struct {
    int games_played;
    int draws;
    int verticalWins;
    int horizontalWins;
    int diagonalWins;
    int antiDiagonalWins;
} GameStats;
    GameStats stats;
    typedef enum{
        NO_WIN,
        HORIZONTAL_WIN,
        VERTICAL_WIN,
        DIAGONAL_WIN,
        ANTIDIAGONAL_WIN
    } WinResult;
    typedef enum{
        NO_DRAW,
        DRAW
    }DrawResult;
int size, row, column, row2, column2, a, l, k, ai, pl;
char board[MAX_SIZE][MAX_SIZE];
void gameLoop();
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
void updateBoard(char board[MAX_SIZE][MAX_SIZE], int size){
system("cls");
printf("\n");
for(int m = 0; m<size; m++){
    for(int t = 0; t<size; t++){
        printf("[%c]", board[m][t]);
    }
    printf("\n");
}
}
WinResult checkWin(char board[MAX_SIZE][MAX_SIZE], int size){
    int x;
for(int i = 0; i<size; i++){
    for(x = 0; x<size; x++){
        if(board[i][x] != board[i][0] || board[i][x] == ' '){
            break;
    }
    if(x == size-1){
    return HORIZONTAL_WIN;
}
}
}
int b;
for(int u = 0; u<size; u++){
    for(b = 0; b<size; b++){
        if(board[b][u] != board[0][u] || board[b][u] == ' '){
            break;
        }
        if(b == size-1){
    return VERTICAL_WIN;
}
    }
}
int q;
for(int y = 0, q = 0; y<size && q<size; y++, q++){
    if(board[y][q] != board[0][0] || board[y][q] == ' '){
        break;
    }

if(q == size - 1){
    return DIAGONAL_WIN;
}
}
int z, c;
for(z = 0, c = size-1; z <size && c >=0; z++, c--){
    if(board[z][c] != board[0][size - 1] || board[z][c] == ' '){
        break;
    }
    if(z == size - 1){
        return ANTIDIAGONAL_WIN;
    }
}
return NO_WIN;
}
void updateScore(char winner);
void createGameStats();
void printGameStats();
DrawResult checkDraw(char board[MAX_SIZE][MAX_SIZE], int size){
    int r, s;
    WinResult win = checkWin(board, size);
    for(r = 0; r<size; r++){
        for(s = 0; s<size; s++){
            if(win != NO_WIN){
                return NO_DRAW;
            }
            if(board[r][s] == ' '){
                return NO_DRAW;
            }
        }
    }
    return DRAW;
}
void playerMove(char board[MAX_SIZE][MAX_SIZE], int size);
void aiMove(char board[MAX_SIZE][MAX_SIZE], int size);
void playAgain(int k){
    char again;
    printf("\nY. Play again \n");
    printf("M. Return to main menu \n");
    printf("N. Exit\n");
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
     sscanf(buffer, " %c", &again);
    while(again != 'Y' && again != 'N' && again != 'M' && again != 'y' && again != 'n' && again!= 'm'){
        printf("Invalid input, try again: ");
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, " %c", &again);
    }
    if(again == 'Y' || again == 'y'){
        if(k == 1){
        system("cls");
        initializeBoard(board, size);
        playerMove(board, size);
        }
        else if(k == 2){
            system("cls");
            initializeBoard(board, size);
            aiMove(board, size);
        }
    }
    else if(again == 'N' || again == 'n'){
        printf("Thanks for playing!");
        Sleep(1000);
        exit(0);
    }
    else{
        system("cls");
        gameLoop();
    }  
}
int main(){
    srand(time(NULL));
    gameLoop();
    return 0;
    }
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
        system("cls");
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
        system("cls");
        gameLoop();
        }
        else{
            FILE *statistics = fopen("stats.txt", "w");
            if(statistics == NULL){
                printf("File not found");
            }
            else{
                fprintf(statistics, "||-- GAME STATS --||\n");
                fprintf(statistics, "Games Played: %d\n", stats.games_played);
                fprintf(statistics, "Vertical Wins: %d\n", stats.verticalWins);
                fprintf(statistics, "Horizontal Wins: %d\n", stats.horizontalWins);
                fprintf(statistics, "Diagonal Wins: %d\n", stats.diagonalWins);
                fprintf(statistics, "Anti Diagonal Wins: %d\n", stats.antiDiagonalWins);
                fprintf(statistics, "Draws: %d\n", stats.draws);
                printf("File saved succesfully!");
                fclose(statistics);
            }
        }
        Sleep(1000);
        system("cls");
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
        system("cls");
    initializeBoard(board, size);
    }
    k = temp;
    if(k == 1){
        playerMove(board, size);
    }
    else{
        aiMove(board, size);
    }
    }
    void playerMove(char board[MAX_SIZE][MAX_SIZE], int size){
    while(1){
    printf("\nPlayer X's turn\n");
    printf("Enter row and column (1-%d): ", size);
    invalid_moveX:
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
       if(sscanf(buffer, "%d %d", &row, &column)!=2){
        printf("Please enter at least two numbers for the row and column: ");
        goto invalid_moveX;
       }
    
    if(row > size || column > size || row < 1 || column < 1){
        printf("Invalid cell location, try again: ");
        goto invalid_moveX;
    }
    if(board[row - 1][column -1] != ' '){
         printf("Cell already occupied, try again: ");
        goto invalid_moveX;
            }
    board[row - 1][column - 1] = 'X';
    updateBoard(board, size);
    if(checkWin(board, size) != NO_WIN){
        printf("\nGame over, player X won!\n");
        updateScore('X');
        break;
    }
    if(checkDraw(board, size) == DRAW){
        printf("\nGame is a draw!\n");
        updateScore('N');
        break;
    }
    printf("\nPlayer O's turn\n");
    printf("Enter row and column (1-%d): ", size);
    invalid_moveO:
    fgets(buffer, sizeof(buffer), stdin);
        if(sscanf(buffer, "%d %d", &row2, &column2)!=2){
            printf("Please enter at least two numbers for the row and column: ");
            goto invalid_moveO;
        }
    if(row2 > size || column2 > size || row2 < 1 || column2 < 1){
        printf("Invalid cell location, try again: ");
        goto invalid_moveO;
    }
    if(board[row2 - 1][column2 - 1] != ' '){
                printf("Cell already occupied, try again: ");
                goto invalid_moveO;
            }
    board[row2 - 1][column2 - 1] = 'O';
    updateBoard(board, size);
    if(checkWin(board, size) != NO_WIN){
        printf("\nGame over, player O won!\n");
        updateScore('O');
        break;
    }
    if(checkDraw(board, size) == DRAW){
        printf("\nThe game is a draw!\n");
        updateScore('N');
        break;
    }
}
    }
    void updateScore(char winner){
    if(k == 1){
        if(winner == 'N'){
            goto no_win;
        }
        if(winner == 'X'){
            a++;
        }
        if(winner == 'O'){
            l++;
        }   
        no_win:
        printf("\nThe current score is\n");
    printf("\nX: %d vs O: %d\n", a, l);
    createGameStats();
    playAgain(k);
    }
    else{
        if(winner == 'N'){
            goto no_win1;
        }
        if(winner == 'X'){
            pl++;
        }
        if(winner == 'O'){
            ai++;
        }
        no_win1:
        printf("\nThe current score is\n");
    printf("\nPlayer: %d vs AI: %d\n", pl, ai);
    createGameStats();
    playAgain(k);
    }
    
}
void aiMove(char board[MAX_SIZE][MAX_SIZE], int size){
    while(1){
    printf("\nPlayer's turn\n");
    printf("Enter row and column (1-%d): ", size);
    invalid:
    char buffer[100];
    fgets(buffer, sizeof(buffer), stdin);
        if(sscanf(buffer, "%d %d", &row, &column) != 2){
            printf("Please enter at least two numbers for the row and column: ");
            goto invalid;
        }
    
    if(row > size || column > size || row < 1 || column < 1){
        printf("Invalid cell location, try again: ");
        goto invalid;
    }
    if(board[row - 1][column -1] != ' '){
                printf("Cell already occupied, try again: ");
                goto invalid;
            }
    board[row - 1][column - 1] = 'X';
    updateBoard(board, size);
    if(checkWin(board, size) != NO_WIN){
        printf("\nGame over, player won!\n");
        updateScore('X');
        break;
    }
    if(checkDraw(board, size) == DRAW){
        printf("\nThe game is a draw!\n");
        updateScore('N');
        break;
    }
    printf("\nAI's turn\nAI is thinking ...\n");
    int aiThink = rand() % 4000 + 1;
    Sleep(aiThink);
    for(int u = 0; u<size; u++){
        for(int t = 0; t<size; t++){
            if(board[u][t] == ' '){
                board[u][t] = 'O';
                if(checkWin(board, size) != NO_WIN){
                    board[u][t] = 'O';
                    updateBoard(board, size);
                    printf("\nGame over, AI won!\n");
                    updateScore('O');
                    return;
                }
                board[u][t] = ' ';
            }
        }
    }
    for(int x = 0; x<size; x++){
        for(int q = 0; q<size; q++){
            if(board[x][q] == ' '){
            board[x][q] = 'X';
            if(checkWin(board, size) != NO_WIN){
                board[x][q] = 'O';
                updateBoard(board, size);
                goto after_ai_move;
                }
                board[x][q] = ' ';

            }
        }
        }
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
    if(checkWin(board, size) != NO_WIN){
        printf("\nGame over, AI won!\n");
        updateScore('O');
        break;
    }
    if(checkDraw(board, size) == DRAW){
        printf("The game is a draw!\n");
        updateScore('N');
}
}
}
void printGameStats(){
    printf("\n||-- GAME STATS --||\n");
    printf("Games Played: %d\n", stats.games_played);
    printf("Vertical Wins: %d\n", stats.verticalWins);
    printf("Horizontal Wins: %d\n", stats.horizontalWins);
    printf("Diagonal Wins: %d\n", stats.diagonalWins);
    printf("Anti Diagonal Wins: %d\n", stats.antiDiagonalWins);
    printf("Draws: %d\n", stats.draws);
}
void createGameStats(){
    WinResult win = checkWin(board, size);
    DrawResult draw = checkDraw(board, size);
    stats.games_played++;
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
    else if(win == ANTIDIAGONAL_WIN){
    stats.antiDiagonalWins++;
    }
}

