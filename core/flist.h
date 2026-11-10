// flist.h — односвязный список (команды на букву F).
#ifndef FLIST_H
#define FLIST_H

#include "common.h"

// Узел: значение + ссылка на след узел
struct FNode {
    string value;
    FNode* next;
};

// Список: первый узел, последний узел, количество
struct FList {
    FNode* head = nullptr;
    FNode* tail = nullptr;
    int size = 0; // для проверки индекса без обхода
};

// Добавление (4 способа)
void flistPushHead(FList& list, const string& value);
void flistPushTail(FList& list, const string& value);
void flistInsertBefore(FList& list, const string& target, const string& value);
void flistInsertAfter(FList& list, const string& target, const string& value);

// Удаление (4 способа + по значению)
string flistDelHead(FList& list);
string flistDelTail(FList& list);
string flistDelBefore(FList& list, const string& target);
string flistDelAfter(FList& list, const string& target);
string flistDelValue(FList& list, const string& value);

// Поиск и чтение
int flistFind(const FList& list, const string& value);  // номер
string flistGet(const FList& list, int index);          // по номеру
string flistPrint(const FList& list);                   // с начала:  A -> B -> C
string flistPrintReverse(const FList& list);            // с конца:   C -> B -> A

string flistToText(const FList& list);  // для файла
void flistFree(FList& list);            // освободить память

string flistCommand(FList& list, const string& cmd, const vector<string>& args);

#endif
