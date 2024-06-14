#ifndef clox_object_h
#define clox_object_h
#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)
#define IS_STRING(value) isObjType(value, OBJ_STRING)
#define AS_STRING(value) ((ObjString*)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString*)AS_OBJ(value))->chars)


typedef enum{
    OBJ_STRING
}ObjType;

struct Obj {            //values in heap 
    ObjType type;
    struct Obj* next;
}; 

struct ObjString {      //values in heap that are string (need to store it seperately since 
    Obj obj;            //they need an array to be represented)
    int length;
    char* chars;
    uint32_t hash;
}; 

ObjString* takeString(char* chars, int length);
ObjString* copyString(const char* chars, int length);
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type){
    return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif