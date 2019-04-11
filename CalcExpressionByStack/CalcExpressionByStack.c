#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "CalcExpressionByStack.h"

//////////////////////////////////////////////////
char *calcExpression(char *expression) {
    QUEUE_t *tokenQ = convertQueueToRPN(expression);
    QUEUE_t *calcQ = createQueue();
    CT_t *calcToken = NULL;
    while (!isEmptyQueue(tokenQ)) {
        char *string = deQueue(tokenQ);
        calcToken = createCalcToken(string);
        enQueue(calcQ, calcToken);
    }
    destroyQueue(tokenQ, QUEUE_OPTION_WITH_ELEMENT);
    
    char *ans = calloc(CE_LENGTH_OF_ANSWER, sizeof(char));
    Stack_t *S = createStack();
    while (!isEmptyQueue(calcQ)) {
        CT_t *calcToken = deQueue(calcQ);
        if (strcmp(calcToken->string, OPERATOR_ADD) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcADD(S);
            pushStack(S, calcToken);
        }
        else if (strcmp(calcToken->string, OPERATOR_SUBTRACT) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcSUBTRACT(S);
            pushStack(S, calcToken);
        }
        else if (strcmp(calcToken->string, OPERATOR_MULTIPLY) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcMULTIPLY(S);
            pushStack(S, calcToken);
        }
        else if (strcmp(calcToken->string, OPERATOR_DIVIDE) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcDIVIDE(S);
            pushStack(S, calcToken);
        }
        else if (strcmp(calcToken->string, OPERATOR_MINUS) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcMINUS(S);
            pushStack(S, calcToken);
        }
        else if (strcmp(calcToken->string, OPERATOR_POWER) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcPOWER(S);
            pushStack(S, calcToken);
        }
        else if (strcmp(calcToken->string, OPERATOR_EQUAL) == 0) {
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
            calcToken = calcEQUAL(S);
            strcpy(ans, calcToken->string);
            destroyCalcToken(calcToken, CE_OPTION_WITH_ELEMENT);
        }
        else {
            pushStack(S, calcToken);
        }
    }
    destroyStack(S, STACK_OPTION_WITH_ELEMENT);
    destroyQueue(calcQ, QUEUE_OPTION_WITH_ELEMENT);
    
    return ans;
}

CT_t *createCalcToken(char *string) {
    CT_t *calcToken = calloc(1, sizeof(CT_t));
    calcToken->string = string;
    return calcToken;
}

bool destroyCalcToken(CT_t *calcToken, CE_OPTION_e option) {
    // Block illegal parameters.
    if (calcToken == NULL) return false;
    if ((option == CE_OPTION_WITH_ELEMENT) &&
        (calcToken->string != NULL)) {
        free(calcToken->string);
    }
    free(calcToken);
    return true;
}

CT_t *calcPOWER(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    token1 = calcTokenTransform(token1);
    token1->value = pow(token1->value, token2->value);
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcMINUS(Stack_t *S) {
    CT_t *token1 = popStack(S);
    token1 = calcTokenTransform(token1);
    token1->value = -1.0 * token1->value;
    return token1;
}

CT_t *calcREMAINDER(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    token1 = calcTokenTransform(token1);
    token1->value = (int)token1->value % (int)token2->value;
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcDIVIDE(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    token1 = calcTokenTransform(token1);
    token1->value = token1->value / token2->value;
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcMULTIPLY(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    token1 = calcTokenTransform(token1);
    token1->value = token1->value * token2->value;
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcSUBTRACT(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    token1 = calcTokenTransform(token1);
    token1->value = token1->value - token2->value;
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcADD(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    token1 = calcTokenTransform(token1);
    token1->value = token1->value + token2->value;
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcEQUAL(Stack_t *S) {
    CT_t *token2 = popStack(S);
    CT_t *token1 = popStack(S);
    token2 = calcTokenTransform(token2);
    char *equal = calloc(CE_LENGTH_OF_ANSWER, sizeof(char));
    int spaceSize = CE_LENGTH_OF_ANSWER - (int)strlen(token1->string) - 3;
    int halfSize = (spaceSize - 1) / 2;
    char *format = calloc(128, sizeof(char));
    sprintf(format, "%%s = %%-%d.%dlf", halfSize, halfSize);
    snprintf(equal, CE_LENGTH_OF_ANSWER - 1, format, token1->string, token2->value);
    free(format);
    free(token1->string);
    token1->string = equal;
    destroyCalcToken(token2, CE_OPTION_WITH_ELEMENT);
    return token1;
}

CT_t *calcTokenTransform(CT_t* calcToken) {
    if (calcToken->string != NULL) {
        calcToken->value = strtod(calcToken->string, NULL);
        free(calcToken->string);
        calcToken->string = NULL;
    }
    return calcToken;
}
