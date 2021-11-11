#define A_IMPL

#include "Array.h"

int main(void)
{
    Array *a = Array_new(10);
    char *str = "Hello World";
    char *str1 = "Hello World Again";
    Array_push(a, STRING, VOID_P(str));
    Array_push(a, STRING, VOID_P(str1));
    Array_pop(a);

}
