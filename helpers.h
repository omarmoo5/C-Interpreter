#ifndef INTERPRETER_HELPERS_H
#define INTERPRETER_HELPERS_H

#define Verbose 0
unsigned long lineNUM;
void COLOR(int color);
void ERROR(char *c, ...);
//Verbose function used in debugging and tracing the flow in the stack.
void VERBOSE(char *c, ...);
char* removeSpaces(char* str);

#endif //INTERPRETER_HELPERS_H
