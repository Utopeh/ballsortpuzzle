#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h> 
#include "ballsortpuzzle.h"

void shuffle(char *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void generator(const int rows, const int columns, char field[rows][columns])
{
    int EmptyCol1 = rand() % columns;
    int EmptyCol2 = rand() % columns;

    while (EmptyCol2 == EmptyCol1) {
        EmptyCol2 = rand() % columns;  
    }

    int AsciiIndex = 33;
    char str[rows * (columns-2)+1];
    int strIndex = 0;

    for(int i = 0; i < columns-2; i++) {
        for(int j = 0; j < rows; j++) {
            str[strIndex] = (char)AsciiIndex;
            strIndex++;
        }
        AsciiIndex++;
    }
    str[strIndex] = '\0';

    shuffle(str, strIndex);

    strIndex = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            if (col == EmptyCol1 || col == EmptyCol2) {
                field[row][col] = ' ';
            } else {
                field[row][col] = str[strIndex++];
            }
        }
    }


}

void down_possible(const int rows, const int columns, char field[rows][columns], int x, int y)
{
    if(field[rows-1][x-1] == ' ') {
        printf("\nX column is empty\n\n");
        return;
    }
    if(field[0][y-1] != ' ') {
        printf("\nY column is full\n\n");
    }

    char temp;
    int index;
    for(int i = 0; i < rows; i++) {
        if(field[i][x-1] != ' ') {
            temp = field[i][x-1];
            index = i;
            break;
        }
    }

    if(field[rows-1][y-1] == ' ') {
        field[rows-1][y-1] = temp;
        field[index][x-1] = ' ';
    } else {
        for(int i = rows-2; i >= 0; i--) {
            if(field[i][y-1] == ' ') {
                if(field[i+1][y-1] == temp) {
                    field[i][y-1] = temp;
                    field[index][x-1] = ' ';
                    break;
                }
            }
        }
    }
}

bool check(const int rows, const int columns, char field[rows][columns])
{
    for (int col = 0; col < columns; col++) {
        char symbol = field[0][col];

        bool isEmpty = true;
        for (int row = 0; row < rows; row++) {
            if (field[row][col] != ' ') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty) continue;

        for (int row = 0; row < rows; row++) {
            if (field[row][col] != symbol || symbol == ' ') {
                return false;
            }
        }
    }

    return true;
}

void game_field(const int rows, const int columns, char field[rows][columns])
{
    for (int row = 0; row < rows; row++) {
        printf("%d ", row + 1);
        for (int col = 0; col < columns; col++) {
            printf("| %c ", field[row][col]);
        }
        printf("|\n");
    }
    printf("  ");
    for (int col = 0; col < columns; col++) {
        printf("----");
    }
    printf("\n  ");

    for (int col = 0; col < columns; col++) {
        printf("  %d ", col + 1);
    }
    printf("\n");
}

void ball_sort_puzzle()
{
    const int rows = 4;
    const int columns = 6;
    int x, y;
    char field[rows][columns];
    srand(time(NULL));

    generator(rows, columns, field);

    while(!check(rows, columns, field)) {
        game_field(rows, columns, field);
        printf("\nEnter what: ");
        if(scanf("%d", &x) <= 0) {
            printf("\nWrong input");
            return;
        }

        printf("Enter where: ");
        if(scanf("%d", &y) <= 0) {
            printf("\nWrong input");
            return;
        }
        if(x == y) {
            printf("\nU can`t choose the same column\n");
            continue;
        }

        down_possible(rows, columns, field, x, y);
        }
    if(check(rows, columns, field)) {
        game_field(rows, columns, field);
        printf("\nПобеда!\n");
    }
}