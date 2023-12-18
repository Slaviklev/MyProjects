#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

unsigned int fsize(const char *filename) {
    FILE *file;
    file = fopen(filename, "r");
    unsigned int len=0;
    while ((fgetc(file)) != EOF) {
        len++;
    }
    return len;
    fclose(file);
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

void encrypt(const char *alfabet, const char *key, const char *textfile, const char *encryptfile) {
    FILE *tfile;
    FILE *efile;
    tfile = fopen(textfile, "r");
    efile = fopen(encryptfile, "w");
    char ch;
    
    while ((ch = fgetc(tfile)) != EOF) {
        for (unsigned int j=0; j < strlen(alfabet); j++) {
            if (ch == alfabet[j]) {
                fputc(key[j], efile);
            }
        }
    }
    fclose(tfile);
    fclose(efile);
}

void decrypt(const char *alfabet, const char *key, const char *encryptfile, const char *decryptfile) {
    FILE *efile;
    FILE *dfile;
    efile = fopen(encryptfile, "r");
    dfile = fopen(decryptfile, "w");
    char ch;
    
    while ((ch = fgetc(efile)) != EOF) {
        for (unsigned int j=0; j < strlen(alfabet); j++) {
            if (ch == key[j]) {
                fputc(alfabet[j], dfile);
            }
        }
    }
    fclose(efile);
    fclose(dfile);
}