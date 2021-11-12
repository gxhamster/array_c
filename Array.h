#ifndef ARRAY_H_
#define ARRAY_H_

/*
 * An Array implementaion that can handle multiple data types
 * Most similar to javascript arrays
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define NULL_CHECK(a) { if (a == NULL) exit(-1);}
#define VOID_P(p) (void *)p
#define A_CALLBACK_P(p) void (*p)(ArrayElement elem, int idx)

#define DEBUG(msg) fprintf(stderr, "DEBUG: %s", msg)

#define RETURN_ERR -1
#define RETURN_SUCCESS 0

typedef enum {
   EMPTY,
   CHAR,
   INT,
   FLOAT,
   STRING,
} ArrayType;

typedef union {
    char *dataString;
    char dataChar;
    int dataInt;
    float dataFloat;
} ArrayData;

typedef struct {
    ArrayData data;
    ArrayType type;
} ArrayElement;

typedef struct {
    ArrayElement *elements;
    size_t length;
    size_t max_size;
} Array;

Array *Array_new(size_t max_size);
size_t Array_push(Array *a, ArrayType type, void *src);
ArrayElement *Array_pop(Array *a);
ArrayElement *Array_find(Array *a, void *src,
                         void (*callback)(ArrayElement *element, int index, Array *a));
// Calls the callback function for every element and passes element
// and its index
void Array_foreach(Array *a,
                   void (*callback)(ArrayElement *element, int index));

#endif

/* Array implementation starts here */

#ifdef A_IMPL

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
            a->elements[a->length].data.dataChar = *(char *)src;
            a->elements[a->length].type = type;
            break;
        case INT:
            a->elements[a->length].data.dataInt = *(int *)src;
            a->elements[a->length].type = type;
            break;
        case FLOAT:
            a->elements[a->length].data.dataFloat = *(float *)src;
            a->elements[a->length].type = type;
            break;
        case STRING:
            strcpy(str, (char *)src);
            a->elements[a->length].data.dataString = str;
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


ArrayElement *Array_pop(Array *a)
{
    NULL_CHECK(a);
    if (a->length <= 0) {
        fprintf(stderr, "ERROR: array length is 0 ");
        return NULL;
    }

    // Make a copy of the element (to return)
    ArrayElement *val = (ArrayElement *)malloc(sizeof(ArrayElement));
    memcpy(val, &a->elements[a->length - 1], sizeof(ArrayElement));

    // Remove the element from array
    memset(&a->elements[a->length -1], 0, sizeof(ArrayElement));
    // Decrease size of array by 1
    a->length -= 1;

    return val;
}


void Array_foreach(Array *a,
                   void (*callback)(ArrayElement *element, int index))
{
    NULL_CHECK(callback);

    size_t i;
    for (i = 0; i < a->length; i++) {
        (*callback)(&a->elements[i], i);
    }
}


ArrayElement *Array_find(Array *a, void *src,
                         void (*callback)(ArrayElement *element, int index, Array *a))
{
    size_t i;

    for (i = 0; i < a->length; i++) {
        // Call callback function
        (*callback)(&a->elements[i], i, a);

        if (a->elements[i].type == INT) {
          if (a->elements[i].data.dataInt == *(int *)src) {
            DEBUG("It is an int\n");
            return &a->elements[i];
          }
        } else if (a->elements[i].type == STRING) {
            if (strcmp(a->elements[i].data.dataString, (char *)src) == 0) {
                DEBUG("It is a string\n");
                return &a->elements[i];
            }
        } else if (a->elements[i].type == FLOAT) {
            if (a->elements[i].data.dataFloat == *(float *)src) {
                DEBUG("It is a float\n");
                return &a->elements[i];
            }
        }

    }
    return NULL;
}

#endif
