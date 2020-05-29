#ifndef INTERPRETER_HELPERS_H
#define INTERPRETER_HELPERS_H

#define Verbose 0
unsigned long lineNUM;
void COLOR(int color);
void ERROR(char *c, ...);
void VERBOSE(char *c, ...);
long countFileLines(FILE* f);
char* removeSpaces(char* str);

#endif //INTERPRETER_HELPERS_H
