#include <stdlib.h>
#include "memory.h"
#include "vm.h"
#include "object.h"

VM vm;

void* reallocate(void* pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
    free(pointer);
    return NULL;
    }
    void* result = realloc(pointer, newSize);
    if(result == NULL) exit(1);
    return result;
}

static void freeObject(Obj* object){                        //freeing memory of all the obj once used
    switch(object->type){
        case OBJ_FUNCTION: {
            ObjFunction* function = (ObjFunction*)object;
            freeChunk(&function->chunk);
            FREE(ObjFunction, object);
            break;
        }
        case OBJ_NATIVE: {
            FREE(ObjNative, object);
            break;
        }
        case OBJ_STRING:{
            ObjString* string = (ObjString*)object;
            FREE_ARRAY(char, string->chars, string->length+1);
            FREE(ObjString, object);
            break;
        }
    }
}

void freeObjects(){
    Obj* object = vm.objects;           //points to start of ll
    while(object->next != NULL){        //null is end of ll, so it traverses till end
        Obj* next = object->next;       //next is initialized and pointed to next node in ll
        freeObject(object);             //frees current obj
        object = next;                  //object now points to the next node in ll
    }
}