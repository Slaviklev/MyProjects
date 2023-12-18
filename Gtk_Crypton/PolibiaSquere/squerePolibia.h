#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isChar(const char ch, const char *str) {
    for (unsigned int i=0; i < strlen(str); i++) {
        if (str[i] == ch) {
            return true;
            break;
        }
    }
    return false;
}

struct Cord {
    unsigned int i;
    unsigned int j;
};

struct Cord cordinates(char ch, unsigned int row, unsigned int col, char matrix[row][col]) {
    struct Cord cord;
    for (unsigned int i=0; i < row; i++) {
        for (unsigned int j=0; j < col; j++) {
            if (matrix[i][j] == ch) {
                cord.i = i;
                cord.j = j;
                return cord;
            }
        }
    }
}

void encrypt(unsigned int row, unsigned int col, char matrix[row][col], const char *textfile, const char *encryptfile) {
    FILE *file;
    FILE *efile;
    file  = fopen(textfile, "r");
    efile = fopen(encryptfile, "w");

    struct Cord cord;
    char   ch;

    while ((ch = fgetc(file)) != EOF) {
        cord = cordinates(ch, row, col, matrix);
        if (cord.i+1 == row || matrix[cord.i+1][cord.j] == '\0') {
            fputc(matrix[0][cord.j], efile);
        } else {
            fputc(matrix[cord.i+1][cord.j], efile);
        }
    }
    fclose(file);
    fclose(efile);
}

void decrypt(unsigned int row, unsigned int col, char matrix[row][col], const char *encryptfile, const char *decryptfile) {
    FILE *efile;
    FILE *dfile;
    efile = fopen(encryptfile, "r");
    dfile = fopen(decryptfile, "w");

    struct Cord cord;
    char ch;

    while ((ch = fgetc(efile)) != EOF) {
        cord = cordinates(ch, row, col, matrix);
        if (cord.i == 0) {
            if (matrix[row-1][cord.j] != '\0') {
                fputc(matrix[row-1][cord.j], dfile);
            } else {
                fputc(matrix[row-2][cord.j], dfile);
            }
        } else {
            fputc(matrix[cord.i-1][cord.j], dfile);
        }
    }
    fclose(efile);
    fclose(dfile);
}

unsigned int calc_rows(const char *key, const char *alfabet) {
    unsigned int len     = strlen(key) + strlen(alfabet);
    unsigned int counter = 0;
    for (unsigned int i=0; i<strlen(alfabet); i++) {
        for (unsigned int j=0; j<strlen(key); j++) {
            if(alfabet[i] == key[j]) {
                counter++;
                break;
            }
        }
    }
    
    return (len - counter)/4 + 1;
}

void squere(const char *alfabet, const char *key, unsigned int row, unsigned int col, char matrix[row][col]) {
    unsigned int keyCounter     = 0;
    unsigned int alfabetCounter = 0;

    for (unsigned int i=0; i < row; i++) {
        for (unsigned int j=0; j < col; j++) {
            if (keyCounter < strlen(key)) {
                matrix[i][j] = key[keyCounter];
                keyCounter++;
            } else if (alfabetCounter < strlen(alfabet)) {
                if (isChar(alfabet[alfabetCounter], key) == 0) {
                    matrix[i][j] = alfabet[alfabetCounter];
                    alfabetCounter++;
                } else {
                    for (; (alfabetCounter < strlen(alfabet)) && (isChar(alfabet[alfabetCounter], key) != 0); alfabetCounter++);
                    matrix[i][j] = alfabet[alfabetCounter];
                    alfabetCounter++;
                }
            } else {
                break;
            }
        }
    }
}














/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COL 4

void print_matrix(char matrix[][COL], unsigned int row) {
    for (unsigned int i=0; i<row; i++) {
        printf("|");
        for (unsigned int j=0; j<COL; j++) {
            printf(" %c", matrix[i][j]);
        }
        printf(" |\n");
    }
}

bool isChar(const char ch, const char *str) {
    for (unsigned int i=0; i < strlen(str); i++) {
        if (str[i] == ch) {
            return true;
            break;
        }
    }
    return false;
}

struct Cord {
    unsigned int i;
    unsigned int j;
};

struct Cord cordinates(char ch, char matrix[][COL], unsigned int row) {
    struct Cord cord;
    for (unsigned int i=0; i < row; i++) {
        for (unsigned int j=0; j < COL; j++) {
            if (matrix[i][j] == ch) {
                cord.i = i;
                cord.j = j;
                return cord;
            }
        }
    }
}

void encrypt(char matrix[][COL], unsigned int row, const char *textfile, const char *encryptfile) {
    FILE *file;
    FILE *efile;
    file  = fopen(textfile, "r");
    efile = fopen(encryptfile, "w");

    struct Cord cord;
    char   ch;

    while ((ch = fgetc(file)) != EOF) {
        cord = cordinates(ch, matrix, row);
        if (cord.i+1 == row || matrix[cord.i+1][cord.j] == '\0') {
            fputc(matrix[0][cord.j], efile);
        } else {
            fputc(matrix[cord.i+1][cord.j], efile);
        }
    }
    fclose(file);
    fclose(efile);
}

void decrypt(char matrix[][COL], unsigned int row, const char *encryptfile, const char *decryptfile) {
    FILE *efile;
    FILE *dfile;
    efile = fopen(encryptfile, "r");
    dfile = fopen(decryptfile, "w");

    struct Cord cord;
    char ch;

    while ((ch = fgetc(efile)) != EOF) {
        cord = cordinates(ch, matrix, row);
        if (cord.i == 0) {
            if (matrix[row-1][cord.j] != '\0') {
                fputc(matrix[row-1][cord.j], dfile);
            } else {
                fputc(matrix[row-2][cord.j], dfile);
            }
        } else {
            fputc(matrix[cord.i-1][cord.j], dfile);
        }
    }
    fclose(efile);
    fclose(dfile);
}

unsigned int calc_rows(const char *key, const char *alfabet) {
    unsigned int len     = strlen(key) + strlen(alfabet);
    unsigned int counter = 0;
    for (unsigned int i=0; i<strlen(alfabet); i++) {
        for (unsigned int j=0; j<strlen(key); j++) {
            if(alfabet[i] == key[j]) {
                counter++;
                break;
            }
        }
    }
    
    return (len - counter)/4 + 1;
}

void squere(const char *alfabet, const char *key, char matrix[][COL], unsigned int row) {
    unsigned int keyCounter     = 0;
    unsigned int alfabetCounter = 0;

    for (unsigned int i=0; i < row; i++) {
        for (unsigned int j=0; j < COL; j++) {
            if (keyCounter < strlen(key)) {
                matrix[i][j] = key[keyCounter];
                keyCounter++;
            } else if (alfabetCounter < strlen(alfabet)) {
                if (isChar(alfabet[alfabetCounter], key) == 0) {
                    matrix[i][j] = alfabet[alfabetCounter];
                    alfabetCounter++;
                } else {
                    for (; (alfabetCounter < strlen(alfabet)) && (isChar(alfabet[alfabetCounter], key) != 0); alfabetCounter++);
                    matrix[i][j] = alfabet[alfabetCounter];
                    alfabetCounter++;
                }
            } else {
                break;
            }
        }
    }
}
*/
/*
int main() {
    const char  *key             = "CRYPTONUSVID";
    const char  *alfabet         = "ABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890.,?!<>";
    const unsigned int row = calc_rows(key, alfabet);
    char matrix[row][COL];
    memset(matrix, 0, sizeof(matrix));
    squere(alfabet, key, matrix, row);
    print_matrix(matrix, row);
    encrypt(matrix, row, "text.txt", "encrypted.txt");
    decrypt(matrix, row, "encrypted.txt", "decrypted.txt");
    return 0;
}
*/