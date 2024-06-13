#include <stdio.h>
#include "value.h"
#include "memory.h"

void initValueArray(ValueArray* array){
    array->values = NULL;
    array->count = 0;
    array->capacity = 0; 
}   

void writeValueArray(ValueArray* array, Value value){
    if(array->capacity < array->count + 1){
        int oldCapacity = array->capacity;
        int newCapacity = oldCapacity + array->count+1;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, newCapacity);
    }
    array->values[array->count] = value;
    array->count++;
}

void freeValueArray(ValueArray* array) {
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}

void printValue(Value value){
    printf("%g", AS_NUMBER(value));
}

bool valuesEqual(Value a , Value b){
    if(a.type != b.type){
        return false;
    }
    switch(a.type){
        case VAL_BOOL: return AS_BOOL(a) == AS_BOOL(b);
        case VAL_NIL: return true;
        case VAL_NUMBER: return AS_NUMBER(a) == AS_NUMBER(b);
        default: return false;
    }
}