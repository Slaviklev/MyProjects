#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define SIZE 26

struct Text {
    char   simbol;
    double frequency;
};

struct RText {
    char   simbol;
    unsigned int frequency;
};

struct Text simbols[SIZE] = {
    {'A', 0.0856}, {'B', 0.0139}, {'C', 0.0279},
    {'D', 0.0378}, {'E', 0.1304}, {'F', 0.0289},
    {'G', 0.0199}, {'H', 0.0528}, {'I', 0.0627},
    {'J', 0.0013}, {'K', 0.0042}, {'L', 0.0339},
    {'M', 0.0249}, {'N', 0.0707}, {'O', 0.0797},
    {'P', 0.0199}, {'Q', 0.0012}, {'R', 0.0677},
    {'S', 0.0607}, {'T', 0.1045}, {'U', 0.0249},
    {'V', 0.0092}, {'W', 0.0149}, {'X', 0.0017},
    {'Y', 0.0199}, {'Z', 0.0008}
};

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

void bubbleSortR(struct RText *text, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (text[j].frequency > text[j + 1].frequency) {
                struct RText temp;
                temp.frequency        = text[j].frequency;
                temp.simbol           = text[j].simbol;
                text[j].frequency     = text[j + 1].frequency;
                text[j].simbol        = text[j + 1].simbol;
                text[j + 1].frequency = temp.frequency;
                text[j + 1].simbol    = temp.simbol;
            }
        }
    }
}

void bubbleSortT(struct Text *text, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (text[j].frequency > text[j + 1].frequency) {
                struct Text temp;
                temp.frequency        = text[j].frequency;
                temp.simbol           = text[j].simbol;
                text[j].frequency     = text[j + 1].frequency;
                text[j].simbol        = text[j + 1].simbol;
                text[j + 1].frequency = temp.frequency;
                text[j + 1].simbol    = temp.simbol;
            }
        }
    }
}

void frequencyAnalysis(const char *text, const char *decryptfile) {
    char restext[strlen(text)];
    struct RText rtext[SIZE];
    for (unsigned int i=0; i < SIZE; i++) {
        rtext[i].simbol    = simbols[i].simbol;
        rtext[i].frequency = 0;
    }
    
    for (unsigned int i=0; i < strlen(text); i++) {
        for (unsigned int j=0; j < SIZE; j++) {
            if (text[i] == tolower(rtext[j].simbol)) {
                rtext[j].frequency++;
            }
        }
    }
    bubbleSortR(rtext, SIZE);
    bubbleSortT(simbols, SIZE);
    
    for (unsigned int i=0; i < strlen(text); i++) {
        for (int j=SIZE-1; j > -1; j--) {
            if (text[i] == tolower(rtext[j].simbol)) {
                if (j == SIZE - 1) {
                    restext[i] = ' ';
                } else {
                    restext[i] = tolower(simbols[j].simbol);
                }
            }
        }
    }
    wtext(restext, strlen(restext), decryptfile, false);
}