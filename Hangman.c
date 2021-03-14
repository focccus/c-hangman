#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "printHang.h"

#define WORD_NUM 26


char *genWord() {
    char *words[WORD_NUM] = {
      "abruptly",
      "phlegm",
      "jelly",
      "quartz",
      "microwave",
      "jackpot winner",
      "whomever",
      "vaporize",
      "voyeurism",
      "you got cake",
      "razzmatazz",
      "numbskull",
      "pneumonoultramicroscopicsilicovolcanoconiosis",
      "Kickshaw",
      "Elon Musk",
      "zombie apocalypse",
      "wristwatch",
      "thumbscrew",
      "twelfths",
      "quixotic",
      "jaywalk",
      "jawbreaker",
      "blizzard storm",
      "jumbo",
      "fjord",
      "dizzying"
    };

    srand(time(NULL));
    return words[rand() % WORD_NUM];
}

short isElem(char e, char *arr) {
    while(*arr) {
        if (*arr == e){
            return 1;
        }

        arr++;
    }

    return 0;
}

void getWord(char *word, short *guessed, char *out) {
    for(char *pw = word; *pw; pw++) {
        if(*pw == ' ') {
            *out = ' ';
        } else if (guessed[tolower(*pw) - 'a']) {
            *out = *pw;
        } else {
            *out = '-';
        }

        out++;
    }
    out = '\0';
}

void printWrong(short *wrong) {
    printf("Falsche Buchstaben: ");
    for (int i = 0; i < 26; i++) {
        if(wrong[i]) {
            printf("%c, ", i + 'a');
        }
    }
    printf("\n\n");
}

void start() {
    char *word = genWord();
    short guessed[26];
    short wrong[26];
    int attempts = 0;
    
    for (int i = 0; i < 26; i++) {
        guessed[i] = 0;
        wrong[i] = 0;
    }
    
    char *out = (char *) malloc(strlen(word) + 1);
    strcpy(out,word);
    char input;

    while(1) {

        getWord(word, guessed, out);

        // Hangman ausgeben
        printf("Versuche: %d\n", 10 - attempts);
        printHangman(attempts);
        printf("\n");

        if(attempts > 0) printWrong(wrong);
        printf("\n");
        printf("%s\n", out);

        if(strcmp(word,out) == 0) {
            printf("Du hast gewonnen! Das Wort war: %s\n\n", word);
            return;
        }
        // inputs lesen------------------------------
        printf("Gib einen Buchstaben ein: ");

        input = getchar();
        fflush(stdin);
        printf("\n");

        // Chars zum Abbrechen prüfen
        if(input == '0') return;
        if(input == '1')  {
            printf("Das Wort war %s\n", word);
            return;
        }
        
        // Überprüfen, ob Eingabe ein Buchstabe ist
        input = tolower(input);
        if(input < 'a' || input > 'z'){
            printf("Bitte waehle einen Buchstaben von a bis z\n");
            printf("Gib [0] ein, um das Spiel zu beenden\n");
            printf("Gib [1] ein, um das Wort zu zeigen\n");
            continue;
        }
    
        if(guessed[input - 'a']) {
            printf("Der Buchstabe wurde bereits verwendet\n");
            continue;
        }

        guessed[input - 'a'] = 1;

        
        // Ist der Buchstabe im Wort?
        if(!isElem(input, word)) {
            wrong[input - 'a'] = 1;
            attempts += 1;
        }

        if(attempts > 9) {
            printf("Du hast verloren! Das Wort war: %s\n\n", word);
            return;
        }

    }
    


    printf("%s\n",out);
    printf("%s\n",word);
}
// -----------------------------------------


int main(void) {

   

    printf("HANGMAN\n\n");
    printHangman(11);
    printf("\n");
    printf("Spielregeln:\n");
    printf("- Es wird fuer dich ein Wort generiert, dass du erraten musst indem du einzelne Buchstaben eingibst\n");
    printf("- Das Spiel ueberprueft die Buchstaben und zeigt dir immer mehr von dem Wort\n");
    printf("- Du hast gewonnen, wenn das Wort komplett ist\n");
    printf("- Wenn der Galgenmann allerdings vollständig gemalt wurde, hast du verloren!\n\n");

    char input;

    while(1) {
        printf("Gib [s] ein um zu spielen\n");
        printf("Gib [q] ein um das Spiel zu beenden\n");

        input = getchar();
        fflush(stdin);
        printf("\n");

        if(input == 's') {
            start();
        } else if(input == 'q') {
            break;
        }
    }
    
    return 0;
}