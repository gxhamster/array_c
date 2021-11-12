#define A_IMPL

#include "Array.h"

void foo(ArrayElement elem, int idx)
{
    if (elem.type == STRING)
        printf("String: %s idx: %d\n", elem.data.dataString, idx);

}

int main(void)
{
    Array *a = Array_new(10);
    char *str = "Hello World";
    char *str1 = "Hello World Again";
    int n = 5;
    Array_push(a, INT, VOID_P(&n));
    Array_push(a, STRING, VOID_P(str));
    Array_push(a, STRING, VOID_P(str1));
    // Array_pop(a);

    A_CALLBACK_P(ptr) = &foo;
    Array_foreach(a, foo);

}
