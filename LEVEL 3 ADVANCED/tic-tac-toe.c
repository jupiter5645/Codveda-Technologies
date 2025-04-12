#include <stdio.h>

#define SIZE 3

void print_board(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) printf("---|---|---\n");
    }
    printf("\n");
}

char check_winner(char board[SIZE][SIZE]) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' ';
}

int is_draw(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ')
                return 0; // Not a draw
        }
    }
    return 1; // It's a draw
}

int main() {
    char board[SIZE][SIZE] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    char current_player = 'X';
    int row, col;

    while (1) {
        print_board(board);
        printf("Player %c, enter your move (row and column): ", current_player);
        scanf("%d %d", &row, &col);

        // Validate input
        if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }

        board[row][col] = current_player;

        char winner = check_winner(board);
        if (winner != ' ') {
            print_board(board);
            printf("Player %c wins!\n", winner);
            break;
        }

        if (is_draw(board)) {
            print_board(board);
            printf("The game is a draw!\n");
            break;
        }

        // Switch player
        current_player = (current_player == 'X') ? 'O' : 'X';
    }

    return 0;
}
