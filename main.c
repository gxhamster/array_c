#include "Array.h"

int main(void)
{
    Array *a = Array_new(10);
    int n = 5;
    float n1 = 2.32;
    char *s = "hello";
    char c = 'i';
    Array_push(a, INT, VOID_P(&n));
    Array_push(a, CHAR, VOID_P(&c));
    Array_push(a, STRING, VOID_P(s));

    printf("%p\n", "fagag");
}
