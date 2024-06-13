#ifndef clox_value_h 
#define clox_value_h 
#include "common.h" 

typedef enum{          //to differentiate diff types of values
    VAL_BOOL,
    VAL_NIL,
    VAL_NUMBER,
}ValueType;

typedef struct{
    ValueType type;
    union{
        bool boolean;
        double number;
    }as;
}Value;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define AS_BOOL(value) ((value).as.boolean)     //to get the value back in C
#define AS_NUMBER(value) ((value).as.number)
#define BOOL_VAL(value)     ((Value){VAL_BOOL, {.boolean = value}})     //produces Value from appropiate c value
#define NIL_VALUE           ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value)   ((Value)){VAL_NUMBER, {.number = value}}

typedef struct{
    int capacity;
    int count;
    Value* values;
}ValueArray;

bool valuesEqual(Value a, Value b);
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value values);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif
