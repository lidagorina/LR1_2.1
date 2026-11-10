// stack.cpp — стек на связном списке
#include "stack.h"

// O(1): новый узел становится вершиной, а старая вершина — под ним
void stackPush(Stack& s, const string& value) {
    SNode* node = new SNode;
    node->value = value;
    node->next = s.top;
    s.top = node;
}

// O(1): снимаем вершину, следующий узел становится новой вершиной
string stackPop(Stack& s) {
    if (s.top == nullptr) error("стек пуст");
    SNode* old = s.top;
    string value = old->value;
    s.top = old->next;
    delete old;
    return value;
}

string stackPrint(const Stack& s) {
    if (s.top == nullptr) return "(пусто)";
    string result = "вершина - ";
    for (SNode* cur = s.top; cur != nullptr; cur = cur->next) {
        if (cur != s.top) result += " | ";
        result += cur->value;
    }
    return result;
}

string stackToText(const Stack& s) {
    string result;
    for (SNode* cur = s.top; cur != nullptr; cur = cur->next) {
        if (cur != s.top) result += " ";
        result += cur->value;
    }
    return result;
}

void stackFree(Stack& s) {
    while (s.top != nullptr) {
        SNode* next = s.top->next;
        delete s.top;
        s.top = next;
    }
}

string stackCommand(Stack& s, const string& cmd, const vector<string>& args) {
    if (cmd == "SPUSH") {
        needArgs(args, 1, "SPUSH имя значение");
        stackPush(s, args[0]);
        return args[0];
    }
    if (cmd == "SPOP") {
        needArgs(args, 0, "SPOP имя");
        return stackPop(s);
    }
    error("неизвестная команда " + cmd);
}
