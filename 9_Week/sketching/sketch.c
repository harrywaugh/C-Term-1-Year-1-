#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "display.h"
#include <math.h>
#define PI 3.14159265358979323846

struct instructByte{  int opcode; int operand; };
struct state{  int x0; int y0; int x1; int y1; bool penDown; int rgba; };
struct point{  double x; double y; };
typedef struct instructByte InstructByte;
typedef struct state State;
typedef struct point Point;

// TODO: upgrade the run function, adding functions to support it.

void changex(State *State, int x2, int bits){
  if(x2 > (1<<(bits-1))-1 && x2 > 0){
    x2 -= 1<<bits;
  }
  State->x0 = State->x1;
  State->x1 += x2;
}

void changey(State *State, int y2, display *d, int bits){
  if(y2 > (1<<(bits-1))-1 && y2 > 0){
    y2 -= 1<<bits;
  }
  State->y0 = State->y1;
  State->y1 += y2;
  if(State->penDown==true && State->rgba==0xFF){
    line(d, State->x0, State->y0, State->x1, State->y1);
  }else if(State->penDown==true){
    cline(d, State->x0, State->y0, State->x1, State->y1, State->rgba);
  }
  State->y0 = State->y1;
  State->x0 = State->x1;
}

void togglePen(State *State){
  if(State->penDown==true){
    State->penDown=false;
    return;
  }
  State->penDown = true;
}

void changeRGBA(State *State, int newRGBA){
  State->rgba=newRGBA;
}

void drawPolygon(State *State, int sides, display *d){
  Point pointArr[sides];
  double theta = 0;
  for(int i=0; i < sides; i++){
    pointArr[i].x = 75 * sin(theta*(PI/180));
    pointArr[i].y = 75 * cos(theta*(PI/180));
    theta = ((i+1)*360) / sides;
  }
  for(int i = 0; i < sides; i++){
    cline(d, State->x1+pointArr[i].x, State->y1+pointArr[i].y, State->x1+pointArr[(i+1) % sides].x, State->y1+pointArr[(i+1) % sides].y, State->rgba);
  }
}

void interpretExtended(display *d, State *State, unsigned char *b, int currentIndex){
  int extraBytes=(b[currentIndex] & 0x30) >> 4;
  if(extraBytes==3){
    extraBytes++;
  }
  InstructByte instruction;
  instruction.opcode = (b[currentIndex] & 0x0f);
  instruction.operand=0;
  for(int i=1; i<extraBytes+1; i++){
    instruction.operand+=b[currentIndex+i] << ((extraBytes-i)*8);
  }

  if(instruction.opcode == 0){
    changex(State, instruction.operand, extraBytes*8);
  }
  else if(instruction.opcode == 1){
    changey(State, instruction.operand, d, extraBytes*8);
  }
  else if(instruction.opcode == 2){
    pause(d, instruction.operand);
  }
  else if(instruction.opcode == 3){
    togglePen(State);
  }
  else if(instruction.opcode == 4){
    clear(d);
  }
  else if(instruction.opcode == 5){
    key(d);
  }
  else if(instruction.opcode == 6){
    changeRGBA(State, instruction.operand);
  }
  else if(instruction.opcode == 7){
    drawPolygon(State, instruction.operand, d);
  }
}

//Interpret function takes in bytes and creates opcodes and operands.
void interpret(FILE *in, display *d) {
  unsigned char b[1024];
  b[0] = fgetc(in);
  int iCount = 1;
  while (! feof(in))  {
    b[iCount] = fgetc(in);
    iCount++;
  }
  int amountOfBytes = iCount-1;
  int extraBytes=0;
  InstructByte instructions[amountOfBytes];
  State currentState = {0, 0, 0, 0, false, 0xFF};
  State *ptrState = &currentState;

  for(int i = 0; i < amountOfBytes; i++){
    instructions[i].opcode = (b[i] & 0xc4) >> 6;
    instructions[i].operand = b[i] & 0x3f;

    if(instructions[i].opcode == 0){
      changex(ptrState, instructions[i].operand, 6);
    }
    else if(instructions[i].opcode == 1){
      changey(ptrState, instructions[i].operand, d, 6);
    }
    else if(instructions[i].opcode == 2){
      pause(d, instructions[i].operand);
    }
    else{
      extraBytes=(b[i] & 0x30) >> 4;
      if(extraBytes==3){
        extraBytes++;
      }
      interpretExtended(d, ptrState, b, i);
      i+=extraBytes;
    }
  }
}

// Read sketch instructions from the given file.  If test is NULL, display the
// result in a graphics window, else check the graphics calls made.
void run(char *filename, char *test[]) {
    FILE *in = fopen(filename, "rb");
    if (in == NULL) {
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }
    display *d = newDisplay(filename, 200, 200, test);
    interpret(in, d);
    end(d);
    fclose(in);
}

// ----------------------------------------------------------------------------
// Nothing below this point needs to be changed.
// ----------------------------------------------------------------------------

// Forward declaration of test data.
char **lineTest, **squareTest, **boxTest, **oxoTest, **diagTest, **crossTest,
     **clearTest, **keyTest, **pausesTest, **fieldTest, **lawnTest;

void testSketches() {
    // Stage 1
    run("line.sketch", lineTest);
    run("square.sketch", squareTest);
    run("box.sketch", boxTest);
    run("oxo.sketch", oxoTest);

    // Stage 2
    run("diag.sketch", diagTest);
    run("cross.sketch", crossTest);

    // Stage 3
    run("clear.sketch", clearTest);
    run("key.sketch", keyTest);

    // Stage 4
    run("pauses.sketch", pausesTest);
    run("field.sketch", fieldTest);
    run("lawn.sketch", lawnTest);
}

int main(int n, char *args[n]) {
    if (n == 1) testSketches();
    else if (n == 2) run(args[1], NULL);
    else {
        fprintf(stderr, "Usage: sketch [file.sketch]");
        exit(1);
    }
}

// Each test is a series of calls, stored in a variable-length array of strings,
// with a NULL terminator.

// The calls that should be made for line.sketch.
char **lineTest = (char *[]) {
    "line(d,30,30,60,30)", NULL
};

// The calls that should be made for square.sketch.
char **squareTest = (char *[]) {
    "line(d,30,30,60,30)", "line(d,60,30,60,60)",
    "line(d,60,60,30,60)","line(d,30,60,30,30)", NULL
};

// The calls that should be made for box.sketch.
char **boxTest = (char *[]) {
    "line(d,30,30,32,30)", "pause(d,10)", "line(d,32,30,34,30)", "pause(d,10)",
    "line(d,34,30,36,30)", "pause(d,10)", "line(d,36,30,38,30)", "pause(d,10)",
    "line(d,38,30,40,30)", "pause(d,10)", "line(d,40,30,42,30)", "pause(d,10)",
    "line(d,42,30,44,30)", "pause(d,10)", "line(d,44,30,46,30)", "pause(d,10)",
    "line(d,46,30,48,30)", "pause(d,10)", "line(d,48,30,50,30)", "pause(d,10)",
    "line(d,50,30,52,30)", "pause(d,10)", "line(d,52,30,54,30)", "pause(d,10)",
    "line(d,54,30,56,30)", "pause(d,10)", "line(d,56,30,58,30)", "pause(d,10)",
    "line(d,58,30,60,30)", "pause(d,10)", "line(d,60,30,60,32)", "pause(d,10)",
    "line(d,60,32,60,34)", "pause(d,10)", "line(d,60,34,60,36)", "pause(d,10)",
    "line(d,60,36,60,38)", "pause(d,10)", "line(d,60,38,60,40)", "pause(d,10)",
    "line(d,60,40,60,42)", "pause(d,10)", "line(d,60,42,60,44)", "pause(d,10)",
    "line(d,60,44,60,46)", "pause(d,10)", "line(d,60,46,60,48)", "pause(d,10)",
    "line(d,60,48,60,50)", "pause(d,10)", "line(d,60,50,60,52)", "pause(d,10)",
    "line(d,60,52,60,54)", "pause(d,10)", "line(d,60,54,60,56)", "pause(d,10)",
    "line(d,60,56,60,58)", "pause(d,10)", "line(d,60,58,60,60)", "pause(d,10)",
    "line(d,60,60,58,60)", "pause(d,10)", "line(d,58,60,56,60)", "pause(d,10)",
    "line(d,56,60,54,60)", "pause(d,10)", "line(d,54,60,52,60)", "pause(d,10)",
    "line(d,52,60,50,60)", "pause(d,10)", "line(d,50,60,48,60)", "pause(d,10)",
    "line(d,48,60,46,60)", "pause(d,10)", "line(d,46,60,44,60)", "pause(d,10)",
    "line(d,44,60,42,60)", "pause(d,10)", "line(d,42,60,40,60)", "pause(d,10)",
    "line(d,40,60,38,60)", "pause(d,10)", "line(d,38,60,36,60)", "pause(d,10)",
    "line(d,36,60,34,60)", "pause(d,10)", "line(d,34,60,32,60)", "pause(d,10)",
    "line(d,32,60,30,60)", "pause(d,10)", "line(d,30,60,30,58)", "pause(d,10)",
    "line(d,30,58,30,56)", "pause(d,10)", "line(d,30,56,30,54)", "pause(d,10)",
    "line(d,30,54,30,52)", "pause(d,10)", "line(d,30,52,30,50)", "pause(d,10)",
    "line(d,30,50,30,48)", "pause(d,10)", "line(d,30,48,30,46)", "pause(d,10)",
    "line(d,30,46,30,44)", "pause(d,10)", "line(d,30,44,30,42)", "pause(d,10)",
    "line(d,30,42,30,40)", "pause(d,10)", "line(d,30,40,30,38)", "pause(d,10)",
    "line(d,30,38,30,36)", "pause(d,10)", "line(d,30,36,30,34)", "pause(d,10)",
    "line(d,30,34,30,32)", "pause(d,10)", "line(d,30,32,30,30)", "pause(d,10)",
    NULL
};

// The calls that should be made for box.sketch.
char **oxoTest = (char *[]) {
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,30,40,60,40)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,30,50,60,50)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,40,30,40,60)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "line(d,50,30,50,60)", NULL
};

// The calls that should be made for diag.sketch.
char **diagTest = (char *[]) {
    "line(d,30,30,60,60)", NULL
};

// The calls that should be made for cross.sketch.
char **crossTest = (char *[]) {
    "line(d,30,30,60,60)", "line(d,60,30,30,60)", NULL
};

// The calls that should be made for clear.sketch.
char **clearTest = (char *[]) {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
    "line(d,50,30,50,60)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "clear(d)", "line(d,30,30,60,60)",
    "line(d,60,30,30,60)", NULL
};

// The calls that should be made for key.sketch.
char **keyTest = (char *[]) {
    "line(d,30,40,60,40)", "line(d,30,50,60,50)", "line(d,40,30,40,60)",
    "line(d,50,30,50,60)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)", "pause(d,63)",
    "pause(d,63)", "pause(d,63)", "key(d)", "clear(d)", "line(d,30,30,60,60)",
    "line(d,60,30,30,60)", NULL
};

// The calls that should be made for diag.sketch.
char **pausesTest = (char *[]) {
    "pause(d,0)", "pause(d,0)", "pause(d,127)", "pause(d,128)", "pause(d,300)",
    "pause(d,0)", "pause(d,71469)", NULL
};

// The calls that should be made for field.sketch.
char **fieldTest = (char *[]) {
    "line(d,30,30,170,30)", "line(d,170,30,170,170)",
    "line(d,170,170,30,170)", "line(d,30,170,30,30)", NULL
};

// The calls that should be made for field.sketch.
char **lawnTest = (char *[]) {
    "cline(d,30,30,170,30,16711935)", "cline(d,170,30,170,170,16711935)",
    "cline(d,170,170,30,170,16711935)", "cline(d,30,170,30,30,16711935)",
    NULL
};
