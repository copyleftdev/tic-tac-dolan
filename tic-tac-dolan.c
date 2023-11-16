#include <ncurses.h>

#define BOARD_SIZE 3

// Function declarations
void displaySplashScreen();
void initializeGame(char board[BOARD_SIZE][BOARD_SIZE], int *currentPlayer);
void drawBoard(char board[BOARD_SIZE][BOARD_SIZE], int cursorX, int cursorY);
int updateGame(char board[BOARD_SIZE][BOARD_SIZE], int *cursorX, int *cursorY, int ch, int *currentPlayer);
int checkWinner(char board[BOARD_SIZE][BOARD_SIZE]);

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();

    // Display the splash screen
    displaySplashScreen();

    // Game variables
    char board[BOARD_SIZE][BOARD_SIZE];
    int currentPlayer = 0;
    int cursorX = 0, cursorY = 0;
    int winner = -1;

    // Initialize the game board
    initializeGame(board, &currentPlayer);

    // Game loop
    int ch;
    while ((ch = getch()) != 'q') {
        clear();
        if (updateGame(board, &cursorX, &cursorY, ch, &currentPlayer)) {
            winner = checkWinner(board);
            if (winner != -1) break;
        }
        drawBoard(board, cursorX, cursorY);
        refresh();
    }

    // Display the winner
    clear();
    if (winner == -1) {
        printw("Game Drawn!\n");
    } else {
        printw("Player %d Wins!\n", winner + 1);
    }
    printw("Press any key to exit.");
    refresh();
    getch();

    // End ncurses mode
    endwin();
    return 0;
}

void displaySplashScreen() {
    clear();
    printw("Welcome to Tic-Tac-Toe!\n");
    printw("Use arrow keys to move.\n");
    printw("Press Space to toggle between O and X.\n");
    printw("Press 'q' to quit.\n");
    printw("Press any key to start...");
    refresh();
    getch();
}

void initializeGame(char board[BOARD_SIZE][BOARD_SIZE], int *currentPlayer) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = ' ';
    *currentPlayer = 0;
}

void drawBoard(char board[BOARD_SIZE][BOARD_SIZE], int cursorX, int cursorY) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (i == cursorY && j == cursorX) {
                attron(A_REVERSE);
                printw(" %c ", board[i][j]);
                attroff(A_REVERSE);
            } else {
                printw(" %c ", board[i][j]);
            }
            if (j < BOARD_SIZE - 1) printw("|");
        }
        if (i < BOARD_SIZE - 1) {
            printw("\n---+---+---\n");
        }
    }
}

int updateGame(char board[BOARD_SIZE][BOARD_SIZE], int *cursorX, int *cursorY, int ch, int *currentPlayer) {
    int updated = 0;
    switch (ch) {
        case KEY_UP:
            *cursorY = (*cursorY - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case KEY_DOWN:
            *cursorY = (*cursorY + 1) % BOARD_SIZE;
            break;
        case KEY_LEFT:
            *cursorX = (*cursorX - 1 + BOARD_SIZE) % BOARD_SIZE;
            break;
        case KEY_RIGHT:
            *cursorX = (*cursorX + 1) % BOARD_SIZE;
            break;
        case ' ':
            if (board[*cursorY][*cursorX] == ' ') {
                board[*cursorY][*cursorX] = (*currentPlayer == 0) ? 'X' : 'O';
                *currentPlayer = (*currentPlayer + 1) % 2;
                updated = 1;
            }
            break;
    }
    return updated;
}

int checkWinner(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0] == 'X' ? 0 : 1;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i] == 'X' ? 0 : 1;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0] == 'X' ? 0 : 1;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2] == 'X' ? 0 : 1;

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ')
                return -1;

    return -1; // Game drawn
}
