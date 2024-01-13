#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    IDENTIFICATOR,
    OPERATOR_ARITMETIC,
    SPECIAL_CHAR,
    CUVANT_CHEIE,
    EROARE_LEXICALA,
    EOF_TOKEN
} TipToken;

typedef struct {
    TipToken tip;
    char valoare[100];
} Token;

const char *cuvinteCheie[] = {"int", "void", "char", "main", "return"};

int esteCuvantCheie(char *cuvant) {
    int numarCuvinteCheie = sizeof(cuvinteCheie) / sizeof(cuvinteCheie[0]);

    for (int i = 0; i < numarCuvinteCheie; i++) {
        if (strcmp(cuvant, cuvinteCheie[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

int esteOperatorAritmetic(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>';
}

int esteCaracterValidPentruIdentificator(char c) {
    return isalnum(c) || c == '_';
}

int esteCaracterSpecial(char c) {
    return c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']' || c == ',' || c == ';' || c == '#' ||
           c == '\'' || c == '\"' || c == '!' || c == '.' || c == '&';
}

int esteSeparator(char c) {
    return c == ' ' || c == '\n';
}

Token analizaLexicala(FILE *fisier) {
    Token token;
    int stare = 0;
    char caracter;
    char buffer[100];
    int index = 0;
   

    while (1) {
        caracter = fgetc(fisier);

        switch (stare) {
            case 0:
                if (esteCaracterValidPentruIdentificator(caracter)) {
                    stare = 1;
                    buffer[index++] = caracter;
                } else if (esteOperatorAritmetic(caracter)) {
                    stare = 2;
                    buffer[index++] = caracter;
                } else if (esteCaracterSpecial(caracter)) {
                    stare = 3;
                    buffer[index++] = caracter;
                } else if (esteSeparator(caracter)==0) {
                    stare = 4;
                    fseek(fisier, -1, SEEK_CUR);
                    token.tip = EROARE_LEXICALA;
                    strcpy(token.valoare, "");
                    return token;
                }
                break;

            case 1:
                if (esteCaracterValidPentruIdentificator(caracter)) {
                    buffer[index++] = caracter;
                } else {
                    buffer[index] = '\0';
                    if (esteCuvantCheie(buffer)) {
                        token.tip = CUVANT_CHEIE;
                    } else {
                        token.tip = IDENTIFICATOR;
                    }
                    strcpy(token.valoare, buffer);
                    fseek(fisier, -1, SEEK_CUR);
                    return token;
                }
                break;

            case 2:
                if (esteOperatorAritmetic(caracter)) {
                    buffer[index++] = caracter;
                } else {
                    buffer[index] = '\0';
                    token.tip = OPERATOR_ARITMETIC;
                    strcpy(token.valoare, buffer);
                    fseek(fisier, -1, SEEK_CUR);
                    return token;
                }
                break;

            case 3:
                if (esteCaracterSpecial(caracter)) {
                    buffer[index++] = caracter;
                } else {
                    buffer[index] = '\0';
                    token.tip = SPECIAL_CHAR;
                    strcpy(token.valoare, buffer);
                    fseek(fisier, -1, SEEK_CUR);
                    return token;
                }
                break;

            case 4:
                if (esteSeparator(caracter) == 0) {
                    stare = 0;
                    fseek(fisier, -1, SEEK_CUR);
                    token.tip = EROARE_LEXICALA;
                    strcpy(token.valoare, "");
                    return token;
                }
                break;
        }
    }

    if (caracter == EOF) {
        token.tip = EOF_TOKEN;
        strcpy(token.valoare, "EOF");
    }

    return token;
}

int main() {
    FILE *fisier;
    fisier = fopen("test.txt", "r");

    if (fisier == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return 1;
    }

    Token token;
    do {
        token = analizaLexicala(fisier);

        switch (token.tip) {
            case IDENTIFICATOR:
                printf("Identificator: %s\n", token.valoare);
                break;

            case OPERATOR_ARITMETIC:
                printf("Operator aritmetic: %s\n", token.valoare);
                break;

            case SPECIAL_CHAR:
                printf("Caracter special: %s\n", token.valoare);
                break;

            case CUVANT_CHEIE:
                printf("Cuvant cheie: %s\n", token.valoare);
                break;

            case EROARE_LEXICALA:
                printf("Analiza lexicala oprita din cauza erorii.\n");
                break;

            case EOF_TOKEN:
                printf("Sfarsit de fisier.\n");
                break;
        }
    } while (token.tip != EROARE_LEXICALA && token.tip != EOF_TOKEN);

    fclose(fisier);

    return 0;
}

