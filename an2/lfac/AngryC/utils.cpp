#include "./utils.h"

int nrVars, nrVectors, nrFunctions, nrStructs, nextVarId, nextFunctionId, nextStructId;
struct variable vars[MAX_VARS];
struct Vector vectors[MAX_VARS];
struct Function functions[MAX_VARS];
struct Struct structs[MAX_VARS];
bool varDeclared[MAX_VARS];

bool haveError;
char errorMessage[MAX_ERROR];
struct Parameter parameters[MAX_PARAMETERS];
int nrParams;
char campuri[MAX_VARS][MAX_VAR_NAME];
int nrCampuri;

void MallocMemoryForVector(struct Vector *);
bool AlreadyHaveVariableOrVectorName(char *);

void init()
{
    nrVars = nrVectors = nrFunctions = nrCampuri = 0;
    nextVarId = nextFunctionId = 0;
    haveError = false;
    errorMessage[0] = 0;
    bzero(varDeclared, sizeof(varDeclared));
}

void AddNewFunction(int dataType, char *fName)
{
    bool good;
    if (AlreadyHaveVariableOrVectorName(fName))
    {
        good = false;
        for (int i = 0; i < nrFunctions; ++i)
            if (strcmp(functions[i].functionName, fName) == 0)
            {
                if (functions[i].nrParams != 0)
                    good = true;
                break;
            }

        if (!good)
            return;
        else
            haveError = false;
    }

    strcpy(functions[nrFunctions].functionName, fName);
    functions[nrFunctions].dataType = dataType;
    functions[nrFunctions].idFunction = nextFunctionId++;
    functions[nrFunctions].nrParams = 0;
    functions[nrFunctions].isDefined = false;
    ++nrFunctions;
}

void AddNewFunctionWithParameters(int dataType, char *fName)
{
    bool good;
    if (AlreadyHaveVariableOrVectorName(fName))
    {
        good = false;
        for (int i = 0; i < nrFunctions; ++i)
            if (strcmp(functions[i].functionName, fName) == 0)
            {
                if (functions[i].nrParams != nrParams)
                    good = true;
                else
                    for (int j = 0; j < nrParams; ++j)
                        if (parameters[j].dataType != functions[i].parameters[j])
                            good = true;
                break;
            }

        if (!good)
            return;
        else
            haveError = false;
    }

    strcpy(functions[nrFunctions].functionName, fName);
    functions[nrFunctions].dataType = dataType;
    functions[nrFunctions].idFunction = nextFunctionId++;
    functions[nrFunctions].nrParams = nrParams;
    functions[nrFunctions].isDefined = false;
    for (int i = 0; i < nrParams; ++i)
        functions[nrFunctions].parameters[i] = parameters[i].dataType;
    ++nrFunctions;
}

bool WordIsReserved(char *word)
{
    if (strcmp(word, "yell") == 0)
        return true;
    if (strcmp(word, "const") == 0)
        return true;
    if (strcmp(word, "if") == 0)
        return true;
    if (strcmp(word, "for") == 0)
        return true;
    if (strcmp(word, "while") == 0)
        return true;
    if (strcmp(word, "else") == 0)
        return true;
    if (strcmp(word, "struct") == 0)
        return true;
    return false;
}

bool AlreadyHaveVariableOrVectorName(char *name)
{
    int i;
    for (i = 0; i < nrVectors; ++i)
    {
        if (strcmp(vectors[i].vectorName, name) == 0)
        {
            haveError = true;
            strcpy(errorMessage, "you idiot, you ALREADY HAVE THIS VECTOR");
            return true;
        }
    }

    for (i = 0; i < nrVars; ++i)
    {
        if (strcmp(vars[i].varName, name) == 0)
        {
            haveError = true;
            strcpy(errorMessage, "Ugh... YOU ALREADY USED THAT NAME");
            return true;
        }
    }

    for (i = 0; i < nrFunctions; ++i)
    {
        if (strcmp(functions[i].functionName, name) == 0)
        {
            haveError = true;
            strcpy(errorMessage, "Wrong name... YOU ALREADY USED THAT NAME");
            return true;
        }
    }

    for (i = 0; i < nrStructs; ++i)
    {
        if (strcmp(structs[i].structName, name) == 0)
        {
            haveError = true;
            strcpy(errorMessage, "Wrong name... YOU ALREADY USED THAT NAME");
            return true;
        }
    }

    return false;
}

void AddNewStruct(char *structName)
{
    if (AlreadyHaveVariableOrVectorName(structName))
        return;

    strcpy(structs[nrStructs].structName, structName);
    structs[nrStructs].idStruct = nextStructId++;
    ++nrStructs;
}

void AddNewConstant(int dataType, char *varName, int value)
{
    int i;
    if (AlreadyHaveVariableOrVectorName(varName))
        return;

    vars[nrVars].dataType = dataType;
    strcpy(vars[nrVars].varName, varName);
    vars[nrVars].idVar = ++nextVarId;
    vars[nrVars].isInitialized = true;
    ++nrVars;
    AssignValue(varName, value);
    if (haveError)
        --nrVars;
    vars[nrVars - 1].isConstant = true;
    return;
}

void AddNewConstant(int dataType, char *varName, double value)
{
    int i;
    if (AlreadyHaveVariableOrVectorName(varName))
        return;

    vars[nrVars].dataType = dataType;
    strcpy(vars[nrVars].varName, varName);
    vars[nrVars].idVar = ++nextVarId;
    vars[nrVars].isInitialized = true;
    ++nrVars;
    AssignValue(varName, value);
    if (haveError)
        --nrVars;
    vars[nrVars - 1].isConstant = true;
    return;
}

void AddNewConstant(int dataType, char *varName, char *strVal)
{
    int i;
    if (AlreadyHaveVariableOrVectorName(varName))
        return;

    vars[nrVars].dataType = dataType;
    strcpy(vars[nrVars].varName, varName);
    vars[nrVars].idVar = ++nextVarId;
    vars[nrVars].isInitialized = true;
    ++nrVars;
    AssignValue(varName, strVal);
    if (haveError)
        --nrVars;
    vars[nrVars - 1].isConstant = true;
    return;
}

void ExtractVectorName(char *where, char *fromWhere)
{
    char *aux, copy;
    aux = strchr(fromWhere, '[');
    do
    {
        --aux;
    } while (*aux == ' ' || *aux == '\t');

    ++aux;
    copy = *aux;
    *aux = 0;
    strcpy(where, fromWhere);
    *aux = copy;
}

void DeclareVector(int vectorType, char *vName, int vSize)
{
    int i;
    if (AlreadyHaveVariableOrVectorName(vName))
        return;

    strcpy(vectors[nrVectors].vectorName, vName);
    vectors[nrVectors].dataType = vectorType;
    vectors[nrVectors].size = vSize;
    vectors[nrVectors].idVector = nextVarId++;
    MallocMemoryForVector(&vectors[nrVectors]);
    ++nrVectors;
}

void MallocMemoryForVector(struct Vector *vector)
{
    vector->values = (struct data *)malloc(vector->size * sizeof(struct data));
}

void CopyNumberToString(char *s, int nr)
{
    int nrc, aux, i;

    s[0] = 0;
    if (nr == 0)
    {
        s[0] = '0';
        s[1] = 0;
        return;
    }
    aux = nr;
    while (nr)
    {
        ++nrc;
        nr /= 10;
    }
    for (i = nrc - 1; i >= 0; --i)
    {
        s[i] = aux % 10 + '0';
        aux /= 10;
    }
    s[nrc] = 0;
}

void FunctionCallNoParameters(char *fId)
{
    Function f;
    f = GetFunction(fId);
    if (haveError)
        return;

    if (f.nrParams != 0)
    {
        haveError = true;
        strcpy(errorMessage, "function needs to receive parameters... GET OUT");
        return;
    }
}

void FunctionCallWithParameters(char *fId)
{
    Function f;
    f = GetFunction(fId);
    if (haveError)
        return;
    //verific parametrii

    if (nrParams != f.nrParams)
    {
        haveError = true;
        strcpy(errorMessage, "wrong number of parameters");
        return;
    }

    for (int i = 0; i < f.nrParams; ++i)
    {
        if (f.parameters[i] != parameters[i].dataType)
        {
            haveError = true;
            strcpy(errorMessage, "parameters have different types! who taught you how to code?!");
            return;
        }
    }
}

int SetDataType(const char *text)
{
    if (strcmp(text, "int") == 0)
        return INT_t;
    if (strcmp(text, "double") == 0)
        return DOUBLE_t;
    if (strcmp(text, "char") == 0)
        return CHAR_t;
    if (strcmp(text, "string") == 0)
        return STRING_t;
    if (strcmp(text, "void") == 0)
        return VOID_t;
    if (strcmp(text, "bool") == 0)
        return BOOL_t;

    return INVALID_t;
}

struct variable OperatorFunction(struct variable var1, const char *op, struct variable var2)
{
    struct variable rez;
    rez.isInitialized = false;
    strcpy(rez.varName, "tempRez");
    //struct variable var1, var2;
    //var1 = GetVariable(a);
    //var2 = GetVariable(b);

    if (HaveDifferentTypes(var1, var2))
    {
        haveError = true;
        strcpy(errorMessage, "variables have different data types, you blittering idiot!");
        return rez;
    }

    if (var1.isInitialized == false || var2.isInitialized == false)
    {
        haveError = true;
        strcpy(errorMessage, "you have used an UNINITIALIZED VARIABLE");
        return rez;
    }

    if (strcmp(op, "+=") == 0)
        rez = SumFunction(var1, var2);
    if (strcmp(op, "+") == 0)
        rez = SumFunction(var1, var2);
    if (strcmp(op, "-") == 0)
        rez = MinusFunction(var1, var2);
    if (strcmp(op, "*") == 0)
        rez = TimesFunction(var1, var2);
    if (strcmp(op, "/") == 0)
        rez = FractionFunction(var1, var2);
    if (strcmp(op, "%") == 0)
        rez = ModFunction(var1, var2);
    if (strcmp(op, "&&") == 0)
        rez = AndFunction(var1, var2);
    if (strcmp(op, "||") == 0)
        rez = OrFunction(var1, var2);
    if (strcmp(op, "<=") == 0)
        rez = LeFunction(var1, var2);
    if (strcmp(op, ">=") == 0)
        rez = GeFunction(var1, var2);
    if (strcmp(op, "==") == 0)
        rez = EqFunction(var1, var2);
    if (strcmp(op, "!=") == 0)
        rez = NeqFunction(var1, var2);
    if (strcmp(op, "<") == 0)
        rez = LsFunction(var1, var2);
    if (strcmp(op, ">") == 0)
        rez = GrFunction(var1, var2);
    strcpy(rez.varName, "tempRez");
    rez.isInitialized = true;
    return rez;
}

bool HaveDifferentTypes(struct variable a, struct variable b)
{
    return false;
    if (a.dataType != b.dataType)
        return true;
    return false;
}

struct variable SumFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.intVal = a.value.intVal + b.value.intVal;
        res.dataType = INT_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.doubleVal = a.value.doubleVal + b.value.doubleVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.doubleVal = a.value.doubleVal + b.value.intVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
        res = SumFunction(b, a);

    if (a.dataType == CHAR_t && b.dataType == CHAR_t)
    {
        res.value.stringVal = (char *)malloc(3);
        res.value.stringVal[0] = a.value.charVal;
        res.value.stringVal[1] = b.value.charVal;
        res.value.stringVal[2] = 0;
        res.dataType = STRING_t;
    }

    if (a.dataType == STRING_t && b.dataType == CHAR_t)
    {
        res.value.stringVal = (char *)malloc(strlen(a.value.stringVal) + 2);
        strcpy(res.value.stringVal, a.value.stringVal);
        res.value.stringVal[strlen(res.value.stringVal)] = b.value.charVal;
        res.value.stringVal[sizeof(res.value.stringVal) - 1] = 0;
        res.dataType = STRING_t;
    }

    if (a.dataType == CHAR_t && b.dataType == STRING_t)
        res = SumFunction(b, a);

    if (a.dataType == STRING_t && b.dataType == STRING_t)
    {
        res.value.stringVal = (char *)malloc(strlen(a.value.stringVal) + strlen(b.value.stringVal) + 1);
        strcpy(res.value.stringVal, a.value.stringVal);
        strcat(res.value.stringVal, b.value.stringVal);
        res.dataType = STRING_t;
    }
    return res;
}

struct variable MinusFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.intVal = a.value.intVal - b.value.intVal;
        res.dataType = INT_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.doubleVal = a.value.doubleVal - b.value.doubleVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.doubleVal = a.value.doubleVal - b.value.intVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.doubleVal = a.value.intVal - b.value.doubleVal;
        res.dataType = DOUBLE_t;
    }
    return res;
}

struct variable TimesFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.intVal = a.value.intVal * b.value.intVal;
        res.dataType = INT_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.doubleVal = a.value.doubleVal * b.value.doubleVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.doubleVal = a.value.doubleVal * b.value.intVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
        res = TimesFunction(b, a);
    return res;
}

struct variable FractionFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.intVal = a.value.intVal / b.value.intVal;
        res.dataType = INT_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.doubleVal = a.value.doubleVal / b.value.doubleVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.doubleVal = a.value.doubleVal / b.value.intVal;
        res.dataType = DOUBLE_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.doubleVal = a.value.intVal / b.value.doubleVal;
        res.dataType = DOUBLE_t;
    }
    return res;
}

struct variable ModFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.intVal = a.value.intVal % b.value.intVal;
        res.dataType = INT_t;
        return res;
    }
}

struct variable AndFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal && b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal && b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal && b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
        res = AndFunction(b, a);

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal && b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal && b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal && b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal && b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal && b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

struct variable OrFunction(struct variable a, struct variable b)
{
    struct variable res;
    res.dataType = BOOL_t;
    if (a.dataType == INT_t && b.dataType == INT_t)
        res.value.boolVal = a.value.intVal || b.value.intVal;

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
        res.value.boolVal = a.value.doubleVal || b.value.doubleVal;

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
        res.value.boolVal = a.value.doubleVal || b.value.intVal;

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
        res = OrFunction(b, a);

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
        res.value.boolVal = a.value.boolVal || b.value.boolVal;

    if (a.dataType == BOOL_t && b.dataType == INT_t)
        res.value.boolVal = a.value.boolVal || b.value.intVal;

    if (a.dataType == INT_t && b.dataType == BOOL_t)
        res.value.boolVal = a.value.intVal || b.value.boolVal;

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
        res.value.boolVal = a.value.boolVal || b.value.doubleVal;

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
        res.value.boolVal = a.value.doubleVal || b.value.boolVal;
    return res;
}

struct variable LeFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal <= b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal <= b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal <= b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.intVal <= b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal <= b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal <= b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal <= b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal <= b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal <= b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

struct variable GeFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal >= b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal >= b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal >= b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.intVal >= b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal >= b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal >= b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal >= b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal >= b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal >= b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

struct variable EqFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal == b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal == b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal == b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.intVal == b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal == b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal == b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal == b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal == b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal == b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

struct variable NeqFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal != b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal != b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal != b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.intVal != b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal != b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal != b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal != b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal != b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal != b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

struct variable LsFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal < b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal < b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal < b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.intVal < b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal < b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal < b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal < b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal < b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal < b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

struct variable GrFunction(struct variable a, struct variable b)
{
    struct variable res;
    if (a.dataType == INT_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.intVal > b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.doubleVal > b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.doubleVal > b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = (a.value.intVal > b.value.doubleVal);
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.boolVal > b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == INT_t)
    {
        res.value.boolVal = a.value.boolVal > b.value.intVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == INT_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.intVal > b.value.boolVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == BOOL_t && b.dataType == DOUBLE_t)
    {
        res.value.boolVal = a.value.boolVal > b.value.doubleVal;
        res.dataType = BOOL_t;
    }

    if (a.dataType == DOUBLE_t && b.dataType == BOOL_t)
    {
        res.value.boolVal = a.value.doubleVal > b.value.boolVal;
        res.dataType = BOOL_t;
    }
    return res;
}

void AddNewVariable(int type, char *varName)
{
    int i;
    if (AlreadyHaveVariableOrVectorName(varName))
        return;

    vars[nrVars].dataType = type;
    strcpy(vars[nrVars].varName, varName);
    vars[nrVars].idVar = nextVarId++;
    vars[nrVars].isConstant = false;
    vars[nrVars].isInitialized = false;
    ++nrVars;
}

struct variable GetVariable(char *varName)
{
    for (int i = 0; i < nrVars; ++i)
    {
        if (strcmp(vars[i].varName, varName) == 0)
            return vars[i];
    }

    //eroare
    haveError = true;
    strcpy(errorMessage, "DOES IT LOOK LIKE THIS VARIABLE EXISTS?!");
    return vars[0];
}

/*struct Function GetFunction(char *fName)
{
    for (int i = 0; i < nrFunctions; ++i)
    {
        if (strcmp(functions[i].functionName, fName) == 0)
            return functions[i];
    }

    //eroare
    haveError = true;
    strcpy(errorMessage, "DOES IT LOOK LIKE THIS FUNCTION EXISTS?!");
    return functions[0];
}*/

struct Function GetFunction(char *fName)
{
    bool good;
    for (int i = 0; i < nrFunctions; ++i)
    {
        good = true;
        if (strcmp(functions[i].functionName, fName) == 0 && nrParams == functions[i].nrParams)
        {
            for (int j = 0; j < nrParams; ++j)
                if (parameters[j].dataType != functions[i].parameters[j])
                    good = false;

            if (good)
                return functions[i];
        }
    }

    //eroare
    haveError = true;
    strcpy(errorMessage, "DOES IT LOOK LIKE THIS FUNCTION EXISTS?!");
    return functions[0];
}

void CheckAssign(char varName[], int val)
{
}

void AssignValue(char *varName, int val)
{
    int i;

    for (i = 0; i < nrVars; ++i)
        if (strcmp(varName, vars[i].varName) == 0)
        {
            if (vars[i].isConstant)
            {
                haveError = true;
                strcpy(errorMessage, "can't reinitialize a constant variable LIKE OH MY GOSH!");
                return;
            }

            if (vars[i].dataType == BOOL_t)
                if ((val != 0 && val != 1))
                {
                    haveError = true;
                    strcpy(errorMessage, "wrong value for bool");
                    return;
                }
                else
                {
                    vars[i].value.boolVal = val;
                    vars[i].isInitialized = true;
                }

            if (vars[i].dataType == VOID_t || vars[i].dataType == STRING_t)
            {
                haveError = true;
                strcpy(errorMessage, "dude, wrong assignment... ugh... does yo momma want you?");
                return;
            }
            switch (vars[i].dataType)
            {
            case DOUBLE_t:
                vars[i].value.doubleVal = val;
                vars[i].isInitialized = true;
                break;
            case INT_t:
                vars[i].value.intVal = val;
                vars[i].isInitialized = true;
                break;
            }
            return;
        }

    return;
}

void AssignValue(char *varName, double val)
{
    int i;
    for (i = 0; i < nrVars; ++i)
        if (strcmp(varName, vars[i].varName) == 0)
        {
            if (vars[i].isConstant)
            {
                haveError = true;
                strcpy(errorMessage, "can't reinitialize a constant variable LIKE OH MY GOSH!");
                return;
            }

            if (vars[i].dataType != DOUBLE_t)
            {
                haveError = true;
                strcpy(errorMessage, "dude, wrong assignment... ugh... does yo momma want you?");
                return;
            }
            vars[i].value.doubleVal = val;
            vars[i].isInitialized = true;
            return;
        }

    return;
}

void AssignValue(char *varName, char *strVal)
{
    int i;
    for (i = 0; i < nrVars; ++i)
        if (strcmp(varName, vars[i].varName) == 0)
        {
            if (vars[i].isConstant)
            {
                haveError = true;
                strcpy(errorMessage, "can't reinitialize a constant variable LIKE OH MY GOSH!");
                return;
            }

            if (vars[i].dataType != CHAR_t && vars[i].dataType != STRING_t)
            {
                haveError = true;
                strcpy(errorMessage, "dude, wrong assignment... ugh...");
                return;
            }

            switch (vars[i].dataType)
            {
            case CHAR_t:
                if (strlen(strVal) > 1)
                {
                    haveError = true;
                    strcpy(errorMessage, "can't assign string to char!");
                    return;
                }
                vars[i].value.charVal = strVal[0];
                vars[i].isInitialized = true;
                break;

            case STRING_t:
                if (vars[i].value.stringVal != NULL)
                    delete vars[i].value.stringVal;

                vars[i].value.stringVal = new char[strlen(strVal) + 1];
                strcpy(vars[i].value.stringVal, strVal);
                vars[i].isInitialized = true;
                break;
            }
            return;
        }
}

void AssignVarValue(char *varName1, struct variable var2)
{
    int i = -1;
    for (i = 0; i < nrVars; ++i)
        if (strcmp(varName1, vars[i].varName) == 0)
            break;

    if (i == nrVars)
    {
        haveError = true;
        strcpy(errorMessage, "YOU DON'T HAVE THAT VARIABLE!!!!");
        return;
    }

    switch (var2.dataType)
    {
    case INT_t:
        AssignValue(varName1, var2.value.intVal);
        break;
    case DOUBLE_t:
        AssignValue(varName1, var2.value.doubleVal);
        break;
    case CHAR_t:
        char strTemp[2];
        strTemp[0] = var2.value.charVal;
        strTemp[1] = 0;
        AssignValue(varName1, strTemp);
        break;
    case STRING_t:
        AssignValue(varName1, var2.value.stringVal);
        break;
    case BOOL_t:
        AssignValue(varName1, (int)var2.value.boolVal);
        break;
    }
}

void YellVec(char *vecName, int pos)
{
    int i;
    for (i = 0; i < nrVectors; ++i)
        if (strcmp(vecName, vectors[i].vectorName) == 0)
            break;

    if (i == nrVectors)
    {
        haveError = true;
        strcpy(errorMessage, "YOU DON'T HAVE THAT VECTOR!!!!");
        return;
    }

    switch (vectors[i].dataType)
    {
    case INT_t:
        printf("%d", vectors[i].values[pos].intVal);
        break;
    case DOUBLE_t:
        printf("%lf", vectors[i].values[pos].doubleVal);
        break;
    case CHAR_t:
        printf("%c", vectors[i].values[pos].charVal);
        break;
    case STRING_t:
        printf("%s", vectors[i].values[pos].stringVal);
        break;
    case BOOL_t:
        printf("%s", vectors[i].values[pos].boolVal ? "true" : "false");
        break;
    }
}

void YellVarOp(struct variable var)
{
    switch (var.dataType)
    {
    case INT_t:
        printf("%d", var.value.intVal);
        break;
    case DOUBLE_t:
        printf("%lf", var.value.doubleVal);
        break;
    case CHAR_t:
        printf("%c", var.value.charVal);
        break;
    case STRING_t:
        printf("%s", var.value.stringVal);
        break;
    case BOOL_t:
        printf("%s", var.value.boolVal ? "true" : "false");
        break;
    }
}

void Yell(char *varName)
{
    struct variable var;
    var = GetVariable(varName);

    if (haveError)
        return;

    if (var.isInitialized == false)
    {
        haveError = true;
        strcpy(errorMessage, "variable uninitialized");
        return;
    }

    switch (var.dataType)
    {
    case INT_t:
        printf("%d", var.value.intVal);
        break;
    case CHAR_t:
        printf("%c", var.value.charVal);
        break;
    case STRING_t:
        printf("%s", var.value.stringVal);
        break;
    case DOUBLE_t:
        printf("%lf", var.value.doubleVal);
        break;
    case BOOL_t:
        printf("%s", var.value.boolVal ? "true" : "false");
        break;
    }
}

void YellString(char *text)
{
    if (strcmp(text, "\\n") == 0)
    {
        printf("\n");
    }
    else
        printf("%s", text);
}

void Incr(char *varName1)
{
    int i = -1;
    for (i = 0; i < nrVars; ++i)
        if (strcmp(varName1, vars[i].varName) == 0)
            break;

    if (i == nrVars)
    {
        haveError = true;
        strcpy(errorMessage, "YOU DON'T HAVE THAT VARIABLE!!!!");
        return;
    }

    switch (vars[i].dataType)
    {
    case INT_t:
        vars[i].value.intVal += 1;
        break;
    case DOUBLE_t:
        vars[i].value.doubleVal += 1;
        break;
    }
}

void AssignVectorValue(char *vecName, int pos, struct variable var)
{
    int i;
    for (i = 0; i < nrVectors; ++i)
        if (strcmp(vecName, vectors[i].vectorName) == 0)
            break;

    if (i == nrVectors)
    {
        haveError = true;
        strcpy(errorMessage, "YOU DON'T HAVE THAT VECTOR!!!!");
        return;
    }

    switch (var.dataType)
    {
    case INT_t:
        AssignVecValue(vecName, pos, var.value.intVal);
        break;
    case DOUBLE_t:
        AssignVecValue(vecName, pos, var.value.doubleVal);
        break;
    case CHAR_t:
        char strTemp[2];
        strTemp[0] = var.value.charVal;
        strTemp[1] = 0;
        AssignVecValue(vecName, pos, strTemp);
        break;
    case STRING_t:
        AssignVecValue(vecName, pos, var.value.stringVal);
        break;
    case BOOL_t:
        AssignVecValue(vecName, pos, (int)var.value.boolVal);
        break;
    }
}

void AssignVecValue(char *vecName, int pos, int val)
{
    int i;

    for (i = 0; i < nrVectors; ++i)
        if (strcmp(vecName, vectors[i].vectorName) == 0)
        {
            if (vectors[i].dataType == BOOL_t)
                if ((val != 0 && val != 1))
                {
                    haveError = true;
                    strcpy(errorMessage, "wrong value for bool");
                    return;
                }
                else
                {
                    vectors[i].values[pos].boolVal = val;
                    //vectors[i].isInitialized = true;
                }

            if (vectors[i].dataType == VOID_t || vectors[i].dataType == STRING_t)
            {
                haveError = true;
                strcpy(errorMessage, "dude, wrong assignment... ugh... does yo momma want you?");
                return;
            }
            switch (vectors[i].dataType)
            {
            case DOUBLE_t:
                vectors[i].values[pos].doubleVal = val;
                //vars[i].isInitialized = true;
                break;
            case INT_t:
                vectors[i].values[pos].intVal = val;
                //vars[i].isInitialized = true;
                break;
            }
            return;
        }

    return;
}

void AssignVecValue(char *vecName, int pos, double val)
{
    int i;
    for (i = 0; i < nrVectors; ++i)
        if (strcmp(vecName, vectors[i].vectorName) == 0)
        {
            if (vectors[i].dataType != DOUBLE_t)
            {
                haveError = true;
                strcpy(errorMessage, "dude, wrong assignment... ugh... does yo momma want you?");
                return;
            }
            vectors[i].values[pos].doubleVal = val;
            //vars[i].isInitialized = true;
            return;
        }

    return;
}

void AssignVecValue(char *vecName, int pos, char *strVal)
{
    int i;
    for (i = 0; i < nrVectors; ++i)
        if (strcmp(vecName, vectors[i].vectorName) == 0)
        {

            if (vectors[i].dataType != CHAR_t && vectors[i].dataType != STRING_t)
            {
                haveError = true;
                strcpy(errorMessage, "dude, wrong assignment... ugh...");
                return;
            }

            switch (vectors[i].dataType)
            {
            case CHAR_t:
                if (strlen(strVal) > 1)
                {
                    haveError = true;
                    strcpy(errorMessage, "can't assign string to char!");
                    return;
                }
                vectors[i].values[pos].charVal = strVal[0];
                //vars[i].isInitialized = true;
                break;

            case STRING_t:
                if (vectors[i].values[pos].stringVal != NULL)
                    delete vectors[i].values[pos].stringVal;

                vectors[i].values[pos].stringVal = new char[strlen(strVal) + 1];
                strcpy(vectors[i].values[pos].stringVal, strVal);
                //vars[i].isInitialized = true;
                break;
            }
            return;
        }
}