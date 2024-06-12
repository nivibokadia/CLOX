#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "compiler.h"
#include "scanner.h"

typedef struct{
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
}Parser;

Parser parser;

Chunk* compilingChunk;

static Chunk* currentChunk(){
    return compilingChunk;
}

static void errorAt(Token* token, const char* message) {
    if(parser.panicMode) return;
    parser.panicMode = true;
    fprintf(stderr, "[line %d] Error", token->line);
    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }
    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

static void error(const char* message){
    errorAt(&parser.previous, message);
}
static void errorAtCurrent(const char* message) {
 errorAt(&parser.current, message);
}


static void advance(){
    parser.previous = parser.current;
    for(;;){
        parser.current = scanToken();
        if(parser.current.type != TOKEN_ERROR) return;
    }
    errorAtCurrent(parser.current.start);
}

static void consume(TokenType type, const char* message){
    if(parser.current.type = type){
        advance();
        return;
    }
    errorAtCurrent(message);
}

static void emitByte(uint8_t byte) {
    writeChunk(currentChunk(), byte, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2){
    emitByte(byte1);
    emitByte(byte2);
}

static void emitReturn(){
    emitByte(OP_RETURN);
}

static uint8_t makeConstant(Value value) {
    int constant = addConstant(currentChunk(), value);
    if (constant > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
    }
    return (uint8_t)constant;
}

static void endCompiler(){
    emitReturn();
}

static void grouping(){
    consume(TOKEN_RIGHT_PAREN , "Expect ')' after expression.");
}

static void emitConstant(Value value){
    emitBytes(OP_CONSTANT, makeConstant(value));
}

static void number(){
    double value = strtod(parser.previous.start, NULL);
    emitConstant(value);
}

static void unary() {
 TokenType operatorType = parser.previous.type;
 expression();
 switch (operatorType) {
 case TOKEN_MINUS: emitByte(OP_NEGATE); break;
 default:
 return;
 }
}

static void expression(){

}

void compile(const char* source, Chunk* chunk){
    initScanner(source);
    compilingChunk = chunk;
    parser.hadError = false;
    parser.panicMode = false;
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression");
    endCompiler();
    return !parser.hadError;
}