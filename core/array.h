// array.h —  массив (команды на букву M).
#ifndef ARRAY_H
#define ARRAY_H

#include "common.h"


struct Array {
    string* data = nullptr;  //  элементы
    int size = 0;            // сколько элементов сейчас
    int capacity = 0;        // сколько поместится без расширения
};

void arrayPush(Array& a, const string& value);               // добавить в конец
void arrayInsert(Array& a, int index, const string& value);  // добавить по индексу
string arrayGet(const Array& a, int index);                  // получить по индексу
void arraySet(Array& a, int index, const string& value);     // заменить по индексу
string arrayDelete(Array& a, int index);                     // удалить по индексу

string arrayPrint(const Array& a);   // для экрана:  [a, b, c]
string arrayToText(const Array& a);  // для файла:   a b c
void arrayFree(Array& a);            // освободить память

// Выполнить команду M
string arrayCommand(Array& a, const string& cmd, const vector<string>& args);

#endif
