#include <unistd.h>
//#define checkMemoryLeak

#include <stdio.h>
#include <stdlib.h>
#include "ReversePolishNotation.h"
#include "CalcExpressionByStack.h"

//////////////////////////////////////////////////
void test(void);

//////////////////////////////////////////////////
int main(int argc, const char * argv[]) {
    
#ifdef checkMemoryLeak
    while (true) {
        test();
        sleep(1);
    }
#else
    test();
#endif
    
    return EXIT_SUCCESS;
}

void test() {
    char *expression = "f=(1+2*3)/(~4+5*6)";
    //    char *expression = "f=1/3";
    printf("Expression              : %s\n", expression);
    
    char *rpn = convertToRPN(expression, " ");
    printf("Reverse Polish Notation : %s\n", rpn);
    free(rpn);
    
    char *ans = calcExpression(expression);
    printf("Answer                  : %s\n", ans);
    free(ans);
}
