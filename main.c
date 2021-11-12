#define A_IMPL

#include "Array.h"

void foo(ArrayElement elem, int idx)
{
    if (elem.type == STRING)
        printf("String: %s idx: %d\n", elem.data.dataString, idx);

}

void callback(ArrayElement *e, int idx, Array *a)
{
    if (e->type == FLOAT)
        e->data.dataFloat = 100.0;
}

int main(void)
{
    Array *a = Array_new(10);
    char *str = "Hello World";
    int n = 5;
    float f = 200.4151;
    Array_push(a, INT, VOID_P(&n));
    Array_push(a, FLOAT, VOID_P(&f));
    Array_push(a, STRING, VOID_P(str));
    // Array_pop(a);

    Array_find(a, &f, callback);
    printf("%f\n", a->elements[1].data.dataString);

    //A_CALLBACK_P(ptr) = &foo;
    //Array_foreach(a, ptr);

}
