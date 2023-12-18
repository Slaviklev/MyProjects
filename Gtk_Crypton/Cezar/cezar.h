#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void encrypt(const char *alfabet, unsigned int key, const char *textfile, const char *encryptfile) {
    FILE *tfile;
    FILE *efile;
    tfile = fopen(textfile, "r");
    efile = fopen(encryptfile, "w");
    char ch;
    
    while ((ch = fgetc(tfile)) != EOF) {
        for (unsigned int j=0; j < strlen(alfabet); j++) {
            if (ch == alfabet[j]) {
                unsigned int k = j;
                for (unsigned int c=0; c < key; c++) {
                    if (alfabet[k] == alfabet[strlen(alfabet)-1]) {
                        k = 0;
                    } else {
                        k++;
                    }               
                }
                fputc(alfabet[k], efile);
            }
        }
    }
    fclose(tfile);
    fclose(efile);
}

void decrypt(const char *alfabet, unsigned int key, const char *encryptfile, const char *decryptfile) {
    FILE *efile;
    FILE *dfile;
    efile = fopen(encryptfile, "r");
    dfile = fopen(decryptfile, "w");
    char ch;

    while ((ch = fgetc(efile)) != EOF) {
        for (unsigned int j=0; j < strlen(alfabet); j++) {
            if (ch == alfabet[j]) {
                unsigned int k = j;
                for (unsigned int c=0; c < key; c++) {
                    if (alfabet[k] == alfabet[0]) {
                        k = strlen(alfabet)-1;
                    } else {
                        k--;
                    }               
                }
                fputc(alfabet[k], dfile);
            }
        }
    }
    fclose(efile);
    fclose(dfile);
}