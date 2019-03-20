#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int duplicate(int**);
int checkRow(int**, int, int);
int checkColumn(int**, int, int);
int checkGrid(int**, int, int, int);
int check(int**, int, int, int, int, int);

int main(int argc, char** argv) {
    FILE* fp;
    char c[5];
    int i = 0, j, val;

    int** matrix = (int**) malloc(9 * sizeof(int *));
    for(i = 0; i < 9; i++){
        matrix[i] = (int*) malloc(9 * sizeof(int));
    }

    if(argc != 2){
        return 0;
    }
    if(!(fp = fopen(argv[1], "r"))){
        printf("0\n");
        return 0;
    }else{
        fp = fopen(argv[1], "r");
    }

    i = 0;
    j = 0;
    while(fscanf(fp, "%s", c) != EOF && i < 9){
        if(strcmp(c, "-") == 0){
            val = 0;
        }else{
            val = atoi(c);
        }
        matrix[i][j] = val;
        j++;
        if(j >= 9){
            j = 0;
            i++;
        }
    }
    fclose(fp);

    //CHECKS IF THERE ARE DUPLICATES IN THE INCOMPLETE MATRIX
    //CHECKS IF THE MATRIX IS VALID FOR SOLVING
    if(duplicate(matrix) == 1){
        for(i = 0; i < 9; i++){
            free(matrix[i]);
        }
        free(matrix);
        printf("no-solution\n");
        return 0;
    }

    int complete = 0;
    int found = 1;
    while(complete == 0){
        complete = 1;
        if(found != 1){
            for(i = 0; i < 9; i++){
                free(matrix[i]);
            }
            free(matrix);
            printf("no-solution\n");
            return 0;
        }
        found = 0;
        for(i = 0; i < 9; i++){
            for(j = 0; j < 9; j++){
                if(matrix[i][j] == 0){
                    complete = 0;
                    int potential = 0;
                    int entry = 0;
                    int k;
                    int startR = (i - i % 3);
                    int startC = (j - j % 3);
                    for(k = 1; k <= 9; k++){
                        if(check(matrix, i, j, startR, startC, k) == 0){
                            potential++;
                            entry = k;
                        }
                    }
                    if(potential == 1){
                        found = 1;
                        matrix[i][j] = entry;
                        if(duplicate(matrix) == 1){
                            for(i = 0; i < 9; i++){
                                free(matrix[i]);
                            }
                            free(matrix);
                            printf("no-solution\n");
                            return 0;
                        }
                    }
                }
            }
        }
    }

    //PRINTS ANSWER MATRIX
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(j == 8){
                printf("%d", matrix[i][j]);
            }else{
                printf("%d\t", matrix[i][j]);
            }
        }
        printf("\n");
    }

    for(i = 0; i < 9; i++){
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}

int duplicate(int** matrix){
    int i, j;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(matrix[i][j] != 0){
                int startRow = i - (i % 3);
                int startCol = j - (j % 3);
                int val = matrix[i][j];
                matrix[i][j] = 0;
                if(check(matrix, i, j, startRow, startCol, val) != 0){
                    matrix[i][j] = val;
                    return 1;
                }
                matrix[i][j] = val;
            }
        }
    }
    return 0;
}

int check(int** matrix, int row, int col, int startRow, int startCol, int value){
    return checkGrid(matrix, startRow, startCol, value) + checkRow(matrix, row, value) + checkColumn(matrix, col, value);
}

int checkRow(int** matrix, int row, int value){
    int i;
    for(i = 0; i < 9; i++){
        if(matrix[row][i] == value){
            return 1; //FOUND
        }
    }
    return 0; //NOT FOUND
}

int checkColumn(int** matrix, int col, int value){
    int i;
    for(i = 0; i < 9; i++){
        if(matrix[i][col] == value){
            return 1; //FOUND
        }
    }
    return 0; //NOT FOUND
}

int checkGrid(int** matrix, int startRow, int startCol ,int value){
    int i, j;
    int endRow = startRow + 3;
    int endCol = startCol + 3;
    for(i = startRow; i < endRow; i++){
        for(j = startCol; j < endCol; j++){
            if(matrix[i][j] == value){
                return 1; //FOUND
            }
        }
    }
    return 0; //NOT FOUND
}
