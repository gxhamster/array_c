#ifndef ARRAY_H_
#define ARRAY_H_

/* An Array implementaion that can handle multiple data types
 * Most similar to javascript arrays
 * */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NULL_CHECK(a) { if (a == NULL) exit(-1);}
#define VOID_P(p) (void *)p
#define RETURN_ERR -1
#define RETURN_SUCCESS 0

typedef enum {
   CHAR,
   INT,
   FLOAT,
   STRING,
} ArrayType;

typedef union {
    char *contentString;
    char contentChar;
    int contentInt;
    float contentFloat;
} ArrayContent;

typedef struct {
    ArrayContent content;
    ArrayType type;
} ArrayElement;

typedef struct {
    ArrayElement *elements;
    size_t length;
    size_t max_size;
} Array;

Array *Array_new(size_t max_size);
size_t Array_push(Array *a, ArrayType type, void *src);
ArrayContent Array_pop(Array *a);

Array *Array_new(size_t max_size)
{
    Array *a = (Array *)malloc(sizeof(Array));
    a->max_size = max_size;
    a->length = 0;
    ArrayElement *ae = (ArrayElement *)malloc( sizeof(ArrayElement) * max_size );
    a->elements = ae;

    return a;
}

#define STR_MAX 1024
size_t Array_push(Array *a, ArrayType type, void *src)
{
    NULL_CHECK(a);
    if (a->length >= a->max_size) {
        fprintf(stderr, "ERROR: Array length reached max size");
        return RETURN_ERR;
    }
    char *str = (char *)malloc(sizeof(STR_MAX));
    // Set new data
    switch (type) {
        case CHAR:
            a->elements[a->length].content.contentChar = *(char *)src;
            a->elements[a->length].type = type;
            break;
        case INT:
            a->elements[a->length].content.contentInt = *(int *)src;
            a->elements[a->length].type = type;
            break;
        case FLOAT:
            a->elements[a->length].content.contentFloat = *(float *)src;
            a->elements[a->length].type = type;
            break;
        case STRING:
            strcpy(str, (char *)src);
            a->elements[a->length].content.contentString = str;
            a->elements[a->length].type = type;
            break;
        default:
            fprintf(stderr, "ERROR: Nothing to push");
            free(str);
            return RETURN_ERR;
    }

    a->length += 1;

    return a->length;

}

ArrayContent Array_pop(Array *a)
{

}

#endif
