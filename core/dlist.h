// dlist.h — двусвязный список (команды на букву L).
#ifndef DLIST_H
#define DLIST_H

#include "common.h"

// Узел: значение + ссылка на СЛЕДУЮЩИЙ и на ПРЕДЫДУЩИЙ узел. 
struct DNode {
    string value;
    DNode* next;
    DNode* prev;
};

struct DList {
    DNode* head = nullptr;
    DNode* tail = nullptr;
    int size = 0;
};

// Добавление (4 способа)
void dlistPushHead(DList& list, const string& value);
void dlistPushTail(DList& list, const string& value);
void dlistInsertBefore(DList& list, const string& target, const string& value);
void dlistInsertAfter(DList& list, const string& target, const string& value);

// Удаление (4 способа + по значению)
string dlistDelHead(DList& list);
string dlistDelTail(DList& list);
string dlistDelBefore(DList& list, const string& target);
string dlistDelAfter(DList& list, const string& target);
string dlistDelValue(DList& list, const string& value);

// Поиск и чтение
int dlistFind(const DList& list, const string& value);
string dlistGet(const DList& list, int index);
string dlistPrint(const DList& list);         // с начала:  1 <-> 2 <-> 3
string dlistPrintReverse(const DList& list);  // с конца:   3 <-> 2 <-> 1

string dlistToText(const DList& list);
void dlistFree(DList& list);

string dlistCommand(DList& list, const string& cmd, const vector<string>& args);

#endif
