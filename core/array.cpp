// array.cpp —  массив
#include "array.h"

// Увеличить память в 2 раза
static void grow(Array& a) {
    int newCapacity = (a.capacity == 0) ? 4 : a.capacity * 2;
    string* newData = new string[newCapacity];
    for (int i = 0; i < a.size; i++) {
        newData[i] = a.data[i];
    }
    delete[] a.data;
    a.data = newData;
    a.capacity = newCapacity;
}

static void checkIndex(const Array& a, int index) {
    if (index >= a.size) {
        error("индекс " + to_string(index) + " вне массива - длина " + to_string(a.size));
    }
}

// O(1) в среднем: обычно просто кладём в свободную ячейку
void arrayPush(Array& a, const string& value) {
    if (a.size == a.capacity) grow(a);
    a.data[a.size] = value;
    a.size++;
}

// O(n): элементы правее индекса сдвигаются на одну ячейку вправо
void arrayInsert(Array& a, int index, const string& value) {
    if (index > a.size) {
        error("индекс " + to_string(index) + " вне массива - длина " + to_string(a.size));
    }
    if (a.size == a.capacity) grow(a);
    for (int i = a.size; i > index; i--) {
        a.data[i] = a.data[i - 1];
    }
    a.data[index] = value;
    a.size++;
}

// O(1): сразу берём ячейку по номеру
string arrayGet(const Array& a, int index) {
    checkIndex(a, index);
    return a.data[index];
}

// O(1)
void arraySet(Array& a, int index, const string& value) {
    checkIndex(a, index);
    a.data[index] = value;
}

// O(n): элементы правее индекса сдвигаются на одну ячейку влево
string arrayDelete(Array& a, int index) {
    checkIndex(a, index);
    string removed = a.data[index];
    for (int i = index; i < a.size - 1; i++) {
        a.data[i] = a.data[i + 1];
    }
    a.size--;
    return removed;
}

string arrayPrint(const Array& a) {
    string result = "[";
    for (int i = 0; i < a.size; i++) {
        if (i > 0){
            result += ", ";
        }
        result += a.data[i];
    }
    return result + "]" + " - красивый вывод";
}

string arrayToText(const Array& a) {
    string result;
    for (int i = 0; i < a.size; i++) {
        if (i > 0) result += " ";
        result += a.data[i];
    }
    return result;
}

void arrayFree(Array& a) {
    delete[] a.data;
    a.data = nullptr;
    a.size = 0;
    a.capacity = 0;
}

string arrayCommand(Array& a, const string& cmd, const vector<string>& args) {
    if (cmd == "MCREATE") {
        needArgs(args, 0, "MCREATE имя");
        return "OK - создали";
    }
    if (cmd == "MPUSH") {
        needArgs(args, 1, "MPUSH имя значение");
        arrayPush(a, args[0]);
        return args[0];
    }
    if (cmd == "MINSERT") {
        needArgs(args, 2, "MINSERT имя индекс значение");
        arrayInsert(a, toIndex(args[0]), args[1]);
        return args[1];
    }
    if (cmd == "MGET") {
        needArgs(args, 1, "MGET имя индекс");
        return arrayGet(a, toIndex(args[0]));
    }
    if (cmd == "MSET") {
        needArgs(args, 2, "MSET имя индекс значение");
        arraySet(a, toIndex(args[0]), args[1]);
        return args[1];
    }
    if (cmd == "MDEL") {
        needArgs(args, 1, "MDEL имя индекс");
        return arrayDelete(a, toIndex(args[0]));
    }
    if (cmd == "MLEN") {
        needArgs(args, 0, "MLEN имя");
        return to_string(a.size);
    }
    error("неизвестная команда " + cmd);
}
