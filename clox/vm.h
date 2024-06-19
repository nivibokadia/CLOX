#ifndef clox_vm_h
#define clox_vm_h
#include "object.h"
#include "table.h"
#include "value.h"
#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
 ObjFunction* function;
 uint8_t* ip;
 Value* slots;
} CallFrame;

typedef struct {
    CallFrame frames[FRAMES_MAX];  //has its own pointer and ip
    int frameCount;                
    Value stack[STACK_MAX];     // The operand stack.
    Value* stackTop;
    Table globals;  
    Table strings;
    Obj* objects;          // Pointer to the top of the stack.
} VM;

typedef enum {                  //shows the state of VM
 INTERPRET_OK,
 INTERPRET_COMPILE_ERROR,
 INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();

InterpretResult interpret(const char* source);  //func to set up VM and start executing bytecode
void push(Value value);
Value pop();

#endif
