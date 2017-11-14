/* Performs the viginiere cipher for a given message and keyword */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 1000
//Checks whether a string is valid, makes sure it only contains letters.
bool valid(const char str[]){
  int iStrLen=strlen(str);
  for(int iCount=0; iCount<iStrLen; iCount++){
    if(isalpha(str[iCount])==0){
      return false;
    }
  }
  return true;
}

//Converts all lower case letters to upper case.
void toUpper(char str[]){
  int iStrLen=strlen(str);
  for(int iCount=0; iCount<iStrLen; iCount++){
    if(str[iCount]>96){
      str[iCount]-=32;
    }
  }
}

//Encrypts the message
void viginiere(char sMsg[], char sKey[]){
  int iMsgLen=strlen(sMsg);
  for(int iCount=0; iCount<iMsgLen; iCount++){
    sMsg[iCount]-='A';
    sMsg[iCount]+=sKey[iCount % strlen(sKey)]-'A';
    sMsg[iCount]=sMsg[iCount] % 26;
    sMsg[iCount]+='A';
  }
}

//Decrypts the message
void unviginiere(char sMsg[], char sKey[]){
  int iMsgLen=strlen(sMsg);
  for(int iCount=0; iCount<iMsgLen; iCount++){
    sMsg[iCount]-='A';
    sMsg[iCount]+=26-(sKey[iCount % strlen(sKey)]-'A');
    sMsg[iCount]=sMsg[iCount] % 26;
    sMsg[iCount]+='A';
  }
}

//Controls checking of valid, upper case functions and actual viginiere cipher
int control(char sKey[], char sMsg[], char sMethod[]){
  if(valid(sKey) && valid(sMsg)){
    toUpper(sKey);
    toUpper(sMsg);
    if(strcmp(sMethod,"E")==0){
      viginiere(sMsg, sKey);
      return 1;
    }
    else if(strcmp(sMethod,"D")==0){
      unviginiere(sMsg, sKey);
      return 1;
    }
  }
  strcpy(sMsg, "Error!");
  return 0;
}

//Checks if there is a difference between the attempted ouput and the actual output
bool checkResult(char *attempt, char *actual, int testNumber){
  if(strcmp(attempt,actual)==0){
    return true;
  }
  printf("Test %d fails.\nProgram returned %s instead of %s.\n", testNumber, attempt, actual);
  return false;
}

//Runs a serious of tests to check if program is outputting correct resultss
int test(){
  int testNumber=1;

  char str[3][MAXLEN]={"key", "message", "E"};
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "WIQCEEO", testNumber )==false)  return 0;
  testNumber++;

  strcpy(str[0],"key");  strcpy(str[1],"meetmebythebridge");   strcpy(str[2],"E");
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "WICDQCLCRRIZBMBQI", testNumber )==false)  return 0;
  testNumber++;

  strcpy(str[0],"KEY");  strcpy(str[1],"WICDQCLCRRIZBMBQI");   strcpy(str[2],"D");
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "MEETMEBYTHEBRIDGE", testNumber )==false)  return 0;
  testNumber++;

  strcpy(str[0],"key");  strcpy(str[1],"Wiqceeo");   strcpy(str[2],"D");
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "MESSAGE", testNumber )==false)  return 0;
  testNumber++;

  strcpy(str[0],"key with spaces");  strcpy(str[1],"message");   strcpy(str[2],"E");
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "Error!", testNumber )==false)  return 0;
  testNumber++;

  strcpy(str[0],"key");  strcpy(str[1],"m3ssage w1th invalid characters");   strcpy(str[2],"D");
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "Error!", testNumber )==false)  return 0;
  testNumber++;

  strcpy(str[0],"key");  strcpy(str[1],"m3ssage w1th invalid characters");   strcpy(str[2],"D");
  control(str[0], str[1], str[2]);
  if(checkResult(str[1], "Error!", testNumber )==false)  return 0;
  testNumber++;

  printf("All tests passed.\n");

  return 0;
}

//Controls when to test, run viginiere cipher, and handles printing to the screen
int main(int argc, char **argv){
  if(argc == 4){
    control(argv[1], argv[2], argv[3]);
    if(strcmp(argv[2],"Error!")!=0){
          printf("%s\n", argv[2]);
          return 0;
    }
  }
  else if(argc==1){
    test();
    return 0;
  }
  printf("Run program in the form ./viginiere keyword message E"
          ". Where: \n\t-keyword is the word used to encrypt/decrypt the message."
          "\n\t-message is the string you wish to encrypt/decrypt."
          "\n\t-'E' or 'D' is used to decide whether to encrypt or decrypt.\n");
  return 0;
}
