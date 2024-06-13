#ifndef clox_value_h 
#define clox_value_h 
#include "common.h" 

typedef struct Obj Obj;
typedef struct ObjString ObjString;

typedef enum{          //to differentiate diff types of values
    VAL_BOOL,
    VAL_NIL,
    VAL_OBJ,
    VAL_NUMBER,
}ValueType;

typedef struct{        //union of double and bool datatype
    ValueType type;
    union{
        bool boolean;
        double number;
        Obj* obj;
    }as;
}Value;

#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value).type == VAL_NUMBER)
#define AS_BOOL(value) ((value).as.boolean)                         //to get the value back in C
#define AS_NUMBER(value) ((value).as.number)
#define IS_OBJ(value)     ((value).type == VAL_OBJ)
#define AS_OBJ(value)     ((value).as.obj)
#define BOOL_VAL(value)   ((Value){VAL_BOOL, {.boolean = value}})   //produces Value from appropiate c value
#define NIL_VALUE         ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})
#define OBJ_VAL(object) ((Value){VAL_OBJ, {.obj = (Obj*)object}})


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
