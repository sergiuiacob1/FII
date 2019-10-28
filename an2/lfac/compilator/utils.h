#ifndef UTILS_H
#define UTILS_H
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_VARS 1000
#define MAX_VAR_NAME 256
#define MAX_ERROR 1000

#define BOOL_t -1
#define CHAR_t -2
#define SHORT_t -3
#define INT_t -4
#define LONG_t -5
#define FLOAT_t -6
#define DOUBLE_t -7
#define STRING_t -8
#define VOID_t -9
#define INVALID_t -10

struct data
{
  int intVal;
  double doubleVal;
  bool boolVal;
  char charVal;
  char *stringVal;
};

struct variable
{
  int dataType, idVar;
  char varName[MAX_VAR_NAME];
  struct data value;
};

int nrVars, nextVarId;
struct variable vars[MAX_VARS];
bool varDeclared[MAX_VARS];

//extern bool haveError;
char errorMessage[MAX_ERROR];

void init();
int SetDataType(const char *);
bool HaveDifferentTypes(struct variable, struct variable);
struct variable OperatorFunction(char *, const char *, char *);
struct variable SumFunction(struct variable, struct variable);
struct variable MinusFunction(struct variable, struct variable);
struct variable TimesFunction(struct variable, struct variable);
struct variable FractionFunction(struct variable, struct variable);

void AddNewVariable(int, char *);
struct variable GetVariable(char *);

void CheckAssign(char *, int);
void AssignValue(char *, int);
void AssignVarValue(char *, struct variable);

void Yell(char *);
void YellString(char *);
#endif