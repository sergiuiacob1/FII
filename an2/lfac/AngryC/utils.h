#ifndef UTILS_H
#define UTILS_H
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define MAX_VARS 1000
#define MAX_VAR_NAME 256
#define MAX_ERROR 1000
#define MAX_STRVAL 10000
#define MAX_PARAMETERS 100

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
  bool isConstant, isInitialized;
  struct data value;
};

struct Parameter
{
  char parName[MAX_VAR_NAME];
  int dataType;
  bool isFunction;
};

struct Function
{
  int dataType, idFunction;
  char functionName[MAX_VAR_NAME];
  int parameters[MAX_PARAMETERS], nrParams;
  bool isDefined;
};

struct Vector
{
  char vectorName[MAX_VAR_NAME];
  int dataType, idVector;
  int size;
  struct data *values;
};

struct Struct
{
  char structName[MAX_VAR_NAME];
  int idStruct;
  struct variable vars[MAX_VARS];
};

extern bool haveError;
extern char errorMessage[MAX_ERROR];
extern struct Parameter parameters[MAX_PARAMETERS];
extern int nrParams;
extern char campuri[MAX_VARS][MAX_VAR_NAME];
extern int nrCampuri;

void init();
int SetDataType(const char *);
bool HaveDifferentTypes(struct variable, struct variable);
struct variable OperatorFunction(struct variable, const char *, struct variable);
struct variable SumFunction(struct variable, struct variable);
struct variable MinusFunction(struct variable, struct variable);
struct variable TimesFunction(struct variable, struct variable);
struct variable FractionFunction(struct variable, struct variable);
struct variable ModFunction(struct variable a, struct variable b);
struct variable AndFunction(struct variable a, struct variable b);
struct variable OrFunction(struct variable a, struct variable b);
struct variable LeFunction(struct variable a, struct variable b);
struct variable LsFunction(struct variable a, struct variable b);
struct variable GrFunction(struct variable a, struct variable b);
struct variable GeFunction(struct variable a, struct variable b);
struct variable EqFunction(struct variable a, struct variable b);
struct variable NeqFunction(struct variable a, struct variable b);

void Incr(char *);

void AddNewVariable(int, char *);
struct variable GetVariable(char *);

void AddNewFunctionWithParameters(int, char *);
void AddNewFunction(int, char *);

void CheckAssign(char *, int);
void AssignValue(char *, int);
void AssignValue(char *, double);
void AssignValue(char *, char *);
void AssignVarValue(char *, struct variable);
void AssignVectorValue(char *vecName, int pos, struct variable);
void AssignVecValue(char *vecName, int pos, char *strVal);
void AssignVecValue(char *vecName, int pos, double val);
void AssignVecValue(char *vecName, int pos, int val);

void YellVec(char *, int);
void Yell(char *);
void YellString(char *);
void YellVarOp (struct variable);

void CopyNumberToString(char *, int);
void FunctionCallNoParameters(char *);
void FunctionCallWithParameters(char *);
struct Function GetFunction(char *);

void DeclareVector(int, char *, int);
void ExtractVectorName(char *, char *);

void AddNewConstant(int, char *, int);
void AddNewConstant(int, char *, double);
void AddNewConstant(int, char *, char *);

void AddNewStruct(char *);

bool WordIsReserved(char *);
#endif