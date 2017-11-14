/* From the input of three integers, this program
will verify if they are a pythagorean triple*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//  Checks whether the input for the program is properly formatted.
bool valid(const char *sideLength){
  int iStrLen=strlen(sideLength);
  for(int iCount=0; iCount<iStrLen; iCount++){
    if(!isdigit(sideLength[iCount]))  return false;
  }
  return true;
}

//  Checks if 3 arguments form a pythagoreanTriple
bool verify(char *arg1, char *arg2, char *arg3){
  int iA=atoi(arg1);
  int iB=atoi(arg2);
  int iC=atoi(arg3);
  int hyp,adj,opp;
  if(iA<=iB){
    if(iB<=iC){
      hyp=iC;
      opp=iB;
      adj=iA;
    }
    else{
      hyp=iB;
      opp=iC;
      adj=iA;
    }
  }
  else{
    if(iA<=iC){
      hyp=iC;
      opp=iB;
      adj=iA;
    }
    else{
      hyp=iA;
      opp=iC;
      adj=iB;
    }
  }
  if((opp*opp) + (adj*adj) == (hyp*hyp)){
    return true;
  }
  return false;
}

//Deals with inputs and outputs, will call the verify and valid functions
int main(int n, char *args[n]){
  setbuf(stdout, NULL);
  if (n==4){
    if(valid(args[1]) && valid(args[2]) && valid(args[3])){
      printf("It is ");
      printf(verify(args[1], args[2], args[3]) ? "true" : "false");
      printf(" that the input forms pythagorean triple.\n");
    }
    else{
      printf("Error: invalid input. \n");
    }

  }
  else{
    printf("To run program properly, enter in the form ./pythagoreanTriple a b c\n");
  }

}
