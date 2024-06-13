#ifndef clox_vm_h
#define clox_vm_h
#include "chunk.h"
#include "value.h"
#define STACK_MAX 256

typedef struct {
    Chunk* chunk;               // The current chunk of bytecode being executed.
    uint8_t* ip;                // The instruction pointer.
    Value stack[STACK_MAX];     // The operand stack.
    Value* stackTop;            // Pointer to the top of the stack.
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
