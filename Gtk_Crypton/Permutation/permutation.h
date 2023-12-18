#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void wordmatrix(unsigned int row, unsigned int col, const char *str) {
    char matrix[row][col];
    memset(matrix, '0', sizeof(matrix));
    for (unsigned int j=0; j < col; j++) {
        matrix[0][j] = str[j];
    }
}

void createNumMatrix(unsigned int row, unsigned int col, unsigned int matrix[row][col], const char *key) {
    for (unsigned int i=0; i < row; i++) {
        if (i == 0) {
            for (unsigned int j=0; j < col; j++) {
                matrix[i][j] = j;
            }
        }
        if (i == 1) {
            for (unsigned int j=0; j < col; j++) {
                const char ch = key[j];
                matrix[i][j] = atoi(&ch) - 1;
            }
        } 
    }
}

unsigned int fsize(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    unsigned int len=0;
    while ((fgetc(file)) != EOF) {
        len++;
    }
    return len;
}

void cptext(char *text, unsigned int size, const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    char ch;
    unsigned int i=0;
    while ((ch = fgetc(file)) != EOF && i < size) {
        text[i] = ch;
        i++;
    }
    fclose(file);
}

void wtext(char *text, unsigned int size, const char *filename, bool end) {
    FILE *file;
    file = fopen(filename, "w");
    if (end == false) {
        for (unsigned int i=0; i < size; i++) {
            fputc(text[i], file);
        }
    }
    if (end == true) {
        char ch;
        unsigned int i=0;
        while (text[i] != '\0' && i < size) {
            fputc(text[i], file);
            i++;
        }
    }
    fclose(file);
}

void encrypt(unsigned int row, unsigned int col, unsigned int matrix[row][col], const char *textfile, const char *encryptfile) {
    unsigned int len = fsize(textfile);
    unsigned int simb = col - len % col;
    if (simb == col) {
        simb = 0;
    }

    char text[len];
    memset(text, '\0', sizeof(text));
    cptext(text, len, textfile);
    char encryptedtext[len + simb];
    memset(encryptedtext, '\0', sizeof(encryptedtext));
    char text1[col];
    unsigned int l = 0;


    for (unsigned int t=0, c=0; c < len; c+=col, t++) {
        for (unsigned int i=0, j=c; i < col; i++, j++) {
            if (j == len + simb) {
                break;  
            }
            if (j >= len) {
                text1[i] = 0;
            } else {
                text1[i] = text[j];
            }
        }
        
        for (unsigned int i=0; i < col; i++) {
            for (unsigned int j=0; j < col; j++) {
                if (matrix[row-2][i] == matrix[row-1][j]) {
                    encryptedtext[i+c] = text1[j];
                    break;
                }
            }
        }
    }

    wtext(encryptedtext, len+simb, encryptfile, false);
}

void decrypt(unsigned int row, unsigned int col, unsigned int matrix[row][col], const char *encryptfile, const char *decryptfile) {
    unsigned int len = fsize(encryptfile);
    char encryptedtext[len];
    char decryptedtext[len];
    memset(encryptedtext, '\0', sizeof(encryptedtext));
    memset(decryptedtext, '\0', sizeof(decryptedtext));

    cptext(encryptedtext, len, encryptfile);
    char text[col];
    
    for (unsigned int t=0, c=0; c < len; c+=col, t++) {
        for (unsigned int i=0, j=c; i < col; i++, j++) {
            text[i] = encryptedtext[j];
        }
        
        for (unsigned int i=0; i < col; i++) {
            for (unsigned int j=0; j < col; j++) {
                if (matrix[row-2][i] == matrix[row-1][j]) {
                    decryptedtext[j+c] = text[i];
                    break;
                }
            }
        }
        
    }

    wtext(decryptedtext, len, decryptfile, true);
}