// stack.h — стек (команды на букву S).

#ifndef STACK_H
#define STACK_H

#include "common.h"

struct SNode {
    string value;
    SNode* next;  // элемент, который лежит ниже
};

struct Stack {
    SNode* top = nullptr;  // верхний элемент
};

void stackPush(Stack& s, const string& value);  // положить наверх
string stackPop(Stack& s);                      // снять верхний

string stackPrint(const Stack& s);
string stackToText(const Stack& s);  // для файла: от вершины ко дну
void stackFree(Stack& s);

string stackCommand(Stack& s, const string& cmd, const vector<string>& args);

#endif
