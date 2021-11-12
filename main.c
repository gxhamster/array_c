#define A_IMPL
#include "Array.h"


void callback(ArrayElement *e, int idx)
{
    if (e->data.dataInt == 100000)
        printf("Found %d at %d\n", e->data.dataInt, idx);
}

int main(void)
{
    int size = 10000000;
    Array *a = Array_new(size);
    int n = 100000;
    char *str = "Hello again i am from a new world";
    for (int i = 0; i < size; i++) {
        Array_push(a, INT, &i);
    }
    Array_find(a, &n, callback);
    //Array_fill(a, INT, &n);

}
