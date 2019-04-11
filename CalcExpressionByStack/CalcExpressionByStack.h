#ifndef CalcExpression_h
#define CalcExpression_h

#include <stdbool.h>
#include "ReversePolishNotation.h"

//////////////////////////////////////////////////
#define CE_LENGTH_OF_ANSWER 64

typedef enum CEOption {
    CE_OPTION_NONE,
    CE_OPTION_WITH_ELEMENT
} CE_OPTION_e;

typedef struct CalcToken {
    char *string;
    double value;
} CT_t;

//////////////////////////////////////////////////
char *calcExpression(char *expression);
CT_t *createCalcToken(char *string);
bool destroyCalcToken(CT_t *calcToken, CE_OPTION_e option);
CT_t *calcPOWER(Stack_t *S);
CT_t *calcMINUS(Stack_t *S);
CT_t *calcREMAINDER(Stack_t *S);
CT_t *calcDIVIDE(Stack_t *S);
CT_t *calcMULTIPLY(Stack_t *S);
CT_t *calcSUBTRACT(Stack_t *S);
CT_t *calcADD(Stack_t *S);
CT_t *calcEQUAL(Stack_t *S);
CT_t *calcTokenTransform(CT_t* token);

#endif
