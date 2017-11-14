#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAX_GUESSES 8
#define MAX_INPUT 1024

//Converts char array to uppercase
void chsToUpper(char chs[]){
  for(int i = 0; i < strlen(chs); i++)
  chs[i]=toupper(chs[i]);
}

//Checks to see if a character is within a string
bool contains(char ch, char chs[]){
  for(int i = 0; i < strlen(chs); i++){
    if(chs[i] == ch){
      return true;
    }
  }
  return false;
}

//Handles string formatting and prints out guesses remaining and, where guessed
//letters are within the secret word
void display(char sGuessedLetters[], char sKeyword[], int iIncorrectGuesses){
  printf("**************************************************************************\n");
  printf("Incorrect Guesses = %d\n", iIncorrectGuesses);
  printf("%d Incorrect Guesses Remaining\n\n", MAX_GUESSES - iIncorrectGuesses);
  for(int i = 0; i <= 'Z' - 'A'; i++){
    if(contains(i + 'A', sGuessedLetters))        printf("# ");
    else                                    printf("%c ", i + 'A');
  }
  printf("\n");

  for(int i = 0; i < strlen(sKeyword); i++){
    if(contains(sKeyword[i], sGuessedLetters))       printf("%c ", sKeyword[i]);
    else                                             printf("_  ");
  }
  printf("\n\n");
}

//Checks if an entire string is made up just letters
bool valid(const char chs[]){
  for(int i=0; i<strlen(chs); i++){
    if(isalpha(chs[i])==0){
      return false;
    }
  }
  return true;
}

//Stores input from the user, finds out the next letter they guess
void getAnswer(char answer[], char sGuessedLetters[]){
  answer[0]=' ';
  while(!isalpha(answer[0])){
    printf("Enter letter: ");
    if (fgets(answer, MAX_INPUT, stdin)==NULL){
      answer[0]=' ';
    }
  }
  answer[0]=toupper(answer[0]);
}

//checks if all 'secret word' letters have been guessed, and therefor the
//player has won
bool won(char sKeyword[], char sGuessedLetters[]){
  for(int i = 0; i < strlen(sKeyword); i++){
    if(!contains(sKeyword[i], sGuessedLetters)){
      return false;
    }
  }
  return true;
}

//Handles calls, and order of functions. M
void control(char sKeyword[]){
  char chs[MAX_INPUT];
  char sGuessedLetters[26];
  int iIncorrectGuesses=0;
  int iGuessedCount=0;
  chsToUpper(sKeyword);
  while(iIncorrectGuesses < 8 && !won(sKeyword, sGuessedLetters)){
    getAnswer(chs, sGuessedLetters);
    sGuessedLetters[iGuessedCount]=chs[0];
    iGuessedCount++;
    if(contains(chs[0], sKeyword)){
      display(sGuessedLetters, sKeyword, iIncorrectGuesses);
    }
    else{
      iIncorrectGuesses++;
      display(sGuessedLetters, sKeyword, iIncorrectGuesses);
    }
  }
  if(won(sKeyword, sGuessedLetters))  printf("Congratulations, you won!\n");
  else                                printf("Unlucky, you failed...miserably.\n");
}

//Checks if two boolean values are the same
bool eqBool(bool b1, bool b2, int testNumber ){
  if(b1==b2){
    return true;
  }
  printf("Error: Test %d had failed.\n", testNumber);
  return false;
}

//checks if two string values are the same
bool eqChs(char chs1[], char chs2[], int testNumber){
  if(strcmp(chs1, chs2)==0){
    return true;
  }
  printf("Error: Test %d had failed.\n", testNumber);
  return false;
}

//Test if all other functions are working
void test(){
  //Tests the contain function
  if(!eqBool(contains('c', "abc"), true, 1)) return;
  if(!eqBool(contains('c', "ABC"), false, 2)) return;
  if(!eqBool(contains('#', "abc"), false, 3)) return;

  //Tests the valid function
  if(!eqBool(valid("abc"), true, 4)) return;
  if(!eqBool(valid("GIF"), true, 5)) return;
  if(!eqBool(valid("LotR"), true, 6)) return;
  if(!eqBool(valid("666beasT"), false, 7)) return;
  if(!eqBool(valid("[][asd]]"), false, 8)) return;
  if(!eqBool(valid("#!"), false, 9)) return;

  //Tests the won function
  if(!eqBool(won("key","aeiouky"), true, 10)) return;
  if(!eqBool(won("msg","asdmsg"), true, 11)) return;
  if(!eqBool(won("key","aeiou"), false, 12)) return;
  if(!eqBool(won("msg","string"), false, 13)) return;

  //Tests the chsToUpper function
  char testChs[]="abcd";  chsToUpper(testChs);
  if(!eqChs(testChs, "ABCD", 14));
  printf("All tests passed.\n");
}

//Is responsible for choosing whether to call test or the control function
int main(int n, char *args[n]) {
    setbuf(stdout, NULL);
    if (n == 1)        test();
    else if (n == 2 && valid(args[1]))  control(args[1]);
    else               fprintf(stderr, "Use: ./hangman  OR  ./hangman keyword, make sure keyword only contains letters\n");
    return 0;
}
