// queue.h — очередь (команды на букву Q).
// «Первым пришёл — первым ушёл»
#ifndef QUEUE_H
#define QUEUE_H

#include "common.h"

struct QNode {
    string value;
    QNode* next;
};

struct Queue {
    QNode* head = nullptr;  // начало очереди
    QNode* tail = nullptr;  // конец очереди
};

void queuePush(Queue& q, const string& value);  // встать в конец
string queuePop(Queue& q);                      // забрать первого

string queuePrint(const Queue& q);
string queueToText(const Queue& q);  // для файла: от начала к концу
void queueFree(Queue& q);

string queueCommand(Queue& q, const string& cmd, const vector<string>& args);

#endif
