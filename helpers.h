#ifndef INTERPRETER_HELPERS_H
#define INTERPRETER_HELPERS_H

#define Verbose 1
unsigned long lineNUM;

//----------------------------------
//----------------- Change The Color
void COLOR(int color);

//-----------------------------------------------------
//------ Displaying Errors For Users - Existing the Code
void ERROR(char *c, ...);

//-----------------------------------------------------
//--------------- Debugging & Tracing The Flow In Stack
void VERBOSE(char *c, ...);

//-----------------------------------------------------
//--------------------------- Remove Spaces From String
char* removeSpaces(char* str);

#endif //INTERPRETER_HELPERS_H
