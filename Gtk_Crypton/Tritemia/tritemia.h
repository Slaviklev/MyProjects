#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void print_matrix(unsigned int row, unsigned int col, char matrix[row][col]) {
    for (unsigned int i=0; i<row; i++) {
        printf("|");
        for (unsigned int j=0; j<col; j++) {
            printf(" %c", matrix[i][j]);
        }
        printf(" |\n");
    }
}

void matrixCreator(unsigned int row, unsigned int col, char matrix[row][col], const char *alfabet) {
    for (unsigned int i=0; i < row; i++) {
        for (unsigned int c=0, j=i; c < col; c++) {
            matrix[i][c] = alfabet[j];
            if (j == strlen(alfabet)-1) {
                j = 0;
            } else {
                j++;
            }
        }
    }
}
void encrypt(unsigned int row, unsigned int col, char matrix[row][col], const char *textfile, const char *encryptfile) {
    FILE *tfile;
    FILE *efile;
    tfile = fopen(textfile, "r");
    efile = fopen(encryptfile, "w");
    char ch;
    unsigned int i = 0;
    unsigned int t = 0;
    while ((ch = fgetc(tfile)) != EOF) {
        for (unsigned int j=0; j < col; j++) {
            if (ch == matrix[i][j]) {
                if (i == row-1) {
                    fputc(matrix[0][j], efile);
                } else {
                    fputc(matrix[i+1][j], efile);
                }
            }
        }
        if (i == row-1) {
            i = 0;
        } else {
            i++;
        }
        t++;
    }
    fclose(tfile);
    fclose(efile);
}
void decrypt(unsigned int row, unsigned int col, char matrix[row][col], const char *encryptfile, const char *decryptfile) {
    FILE *efile;
    FILE *dfile;
    efile = fopen(encryptfile, "r");
    dfile = fopen(decryptfile, "w");
    char ch;
    unsigned int i = 0;
    unsigned int t = 0;

    while ((ch = fgetc(efile)) != EOF) {
        for (unsigned int j=0; j < col; j++) {
            if (ch == matrix[i][j]) {
                if (i == 0) {
                    fputc(matrix[row-1][j], dfile);
                } else {
                    fputc(matrix[i-1][j], dfile);
                }
            }
        }
        if (i == row-1) {
            i = 0;
        } else {
            i++;
        }
        t++;
    }
    fclose(efile);
    fclose(dfile);
}