// queue.cpp — очередь на связном списке
#include "queue.h"

// O(1): новый узел цепляем за последний
void queuePush(Queue& q, const string& value) {
    QNode* node = new QNode;
    node->value = value;
    node->next = nullptr;
    if (q.tail == nullptr) {
        q.head = node;  
    } else {
        q.tail->next = node;
    }
    q.tail = node;
}

// O(1): забираем первый узел
string queuePop(Queue& q) {
    if (q.head == nullptr) error("очередь пуста");
    QNode* old = q.head;
    string value = old->value;
    q.head = old->next;
    if (q.head == nullptr) q.tail = nullptr;  
    delete old;
    return value;
}

string queuePrint(const Queue& q) {
    if (q.head == nullptr) return "(пусто)";
    string result = "начало - ";
    for (QNode* cur = q.head; cur != nullptr; cur = cur->next) {
        if (cur != q.head) result += " | ";
        result += cur->value;
    }
    return result + " - конец";
}

string queueToText(const Queue& q) {
    string result;
    for (QNode* cur = q.head; cur != nullptr; cur = cur->next) {
        if (cur != q.head) result += " ";
        result += cur->value;
    }
    return result;
}

void queueFree(Queue& q) {
    while (q.head != nullptr) {
        QNode* next = q.head->next;
        delete q.head;
        q.head = next;
    }
    q.tail = nullptr;
}

string queueCommand(Queue& q, const string& cmd, const vector<string>& args) {
    if (cmd == "QPUSH") {
        needArgs(args, 1, "QPUSH имя значение");
        queuePush(q, args[0]);
        return args[0];
    }
    if (cmd == "QPOP") {
        needArgs(args, 0, "QPOP имя");
        return queuePop(q);
    }
    error("неизвестная команда " + cmd);
}
