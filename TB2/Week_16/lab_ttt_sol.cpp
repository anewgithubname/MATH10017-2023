#include <stdio.h>
#include <stdlib.h>
#include <climits>
#include <utility>

class matrix
{
    //   num_rows: integer, stores the number of rows
    //   num_cols: integer, stores the number of columns
    //   elements: integer pointer, pointing to a contiguous memory stores a row-major matrix.

    int num_rows;
    int num_cols;
    int *elements;

    // all functions below must be PUBLIC!
public:

    int get_num_rows() { return num_rows; }
    int get_num_cols() { return num_cols; }

    void set_elem(int i, int j, int value)
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
        }
        else
        {
            elements[i * num_cols + j] = value;
        }
    }

    int get_elem(int i, int j)
    {
        if (i < 0 || i >= num_rows || j < 0 || j >= num_cols)
        {
            printf("invalid indices!\n");
            return 'N';
        }
        else
        {
            return elements[i * num_cols + j];
        }
    }

    matrix(int nrow, int ncol)
    {
        if (nrow <= 0 || ncol <= 0)
        {
            printf("invalid dimensions!\n");
        }
        else
        {
            num_rows = nrow;
            num_cols = ncol;
            // printf("allocating memory for the matrix...\n");
            elements = (int *)malloc(num_rows * num_cols * sizeof(int));
        }
    }

    ~matrix()
    {
        // printf("freeing the matrix...\n");
        free(elements);
    }

    // print all elements in the matrix
    void print()
    {
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                printf("%d ", get_elem(i, j));
            }
            printf("\n");
        }
    }

};

class tictactoe{
    matrix board; //[1]

    int pieces_at_row(int i, char player){
        int count = 0;
        for(int j = 0; j < 3; j++){
            if(board.get_elem(i, j) == player) count++;
        }
        return count;
    }
    int pieces_at_col(int j, char player){
        int count = 0;
        for(int i = 0; i < 3; i++){
            if(board.get_elem(i, j) == player) count++;
        }
        return count;
    }

    int pieces_at_diag(char player){
        int count = 0;
        for(int i = 0; i < 3; i++){
            if(board.get_elem(i, i) == player) count++;
        }
        return count;
    }
    int pieces_at_anti_diag(char player){
        int count = 0;
        for(int i = 0; i < 3; i++){
            if(board.get_elem(i, 2-i) == player) count++;
        }
        return count;
    }

    // evaluate the current move using greedy algorithm, 
    // the higher the score is, the better the move is
    int evaluate(int i, int j, char player){
        // who is player? who is opponent? 
        char opponent;
        if (player == 'X')
            opponent = 'O';
        else
            opponent = 'X';

        // evaluate the situiation after the move
        // the higher the score is, the better the move is
        int f_ij = 0;

        f_ij += pieces_at_row(i, player);
        f_ij -= pieces_at_row(i, opponent);
        f_ij += pieces_at_col(j, player);
        f_ij -= pieces_at_col(j, opponent);

        if(i == j){
            f_ij += pieces_at_diag(player);
            f_ij -= pieces_at_diag(opponent);
        }
        if(i + j == 2){
            f_ij += pieces_at_anti_diag(player);
            f_ij -= pieces_at_anti_diag(opponent);
        }

        return f_ij;
    }

    int isplayable(int i, int j) {
        if (board.get_elem(i, j) == '*') {
            return 1;
        }
        return 0;
    }

public:
    tictactoe(): board(3,3) { //[1]
        //initialize the board
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board.set_elem(i, j, '*'); //[2]
            }
        }
    }
    
    void play(int i, int j, char player) {
        if(isplayable(i, j)) {
            board.set_elem(i, j, player);
        }
    }

    void play(char player){
        //play the best move
        int i_max = 0;
        int j_max = 0;
        int max_score = -100;
        // search over all possible moves
        for (int i =0; i < 3; i++){ 
            for (int j =0; j < 3; j++){
                if(isplayable(i, j)){
                    int s = evaluate(i, j, player);
                    if(s > max_score){
                        max_score = s;
                        i_max = i;
                        j_max = j;
                    }
                }
            }
        }
        play(i_max, j_max, player); //[3]
    }

    void print() { 
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                printf("%c ", board.get_elem(i, j)); //[4]
            }
            printf("\n");
        }
    }

};

int main()
{
    //initialize a random tictactoe board
    tictactoe game;
    game.play(0, 0, 'X');
    game.play(0, 1, 'O');
    game.print();

    printf("AI plays...\n");
    game.play('X');
    game.print();

    printf("AI plays...\n");
    game.play('O');
    game.print();

    printf("AI plays...\n");
    game.play('X');
    game.print();

    printf("AI plays...\n");
    game.play('O');
    game.print();

    printf("AI plays...\n");
    game.play('X');
    game.print();

}
