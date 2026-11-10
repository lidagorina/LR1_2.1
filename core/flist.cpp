// flist.cpp — односвязный список
#include "flist.h"

// Создать новый узел
static FNode* newNode(const string& value, FNode* next) {
    FNode* node = new FNode;
    node->value = value;
    node->next = next;
    return node;
}

// Найти узел по значению
static FNode* findNode(const FList& list, const string& value) {
    for (FNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur->value == value) return cur;
    }
    error("элемент - " + value + " -  не найден");
}

// Найти узел, который стоит перед node
static FNode* prevOf(const FList& list, FNode* node) {
    FNode* cur = list.head;
    while (cur->next != node) {
        cur = cur->next;
    }
    return cur;
}

// Вставить новый узел сразу после node
static void insertAfterNode(FList& list, FNode* node, const string& value) {
    node->next = newNode(value, node->next);
    if (node == list.tail) list.tail = node->next;
    list.size++;
}

// Убрать узел node из списка, удалить его и вернуть значение
static string removeNode(FList& list, FNode* node) {
    if (node == list.head) {
        list.head = node->next;
        if (list.head == nullptr) list.tail = nullptr;
    } else {
        FNode* prev = prevOf(list, node);
        prev->next = node->next; 
        if (node == list.tail) list.tail = prev;
    }
    string value = node->value;
    delete node;
    list.size--;
    return value;
}

// Добавление

void flistPushHead(FList& list, const string& value) {
    list.head = newNode(value, list.head);
    if (list.tail == nullptr) list.tail = list.head;
    list.size++;
}

void flistPushTail(FList& list, const string& value) {
    if (list.tail == nullptr) {
        flistPushHead(list, value);
    } else {
        insertAfterNode(list, list.tail, value);
    }
}

void flistInsertBefore(FList& list, const string& target, const string& value) {
    FNode* node = findNode(list, target);
    if (node == list.head) {
        flistPushHead(list, value);
    } else {
        insertAfterNode(list, prevOf(list, node), value);
    }
}

void flistInsertAfter(FList& list, const string& target, const string& value) {
    insertAfterNode(list, findNode(list, target), value);
}

//  Удаление 

string flistDelHead(FList& list) {
    if (list.head == nullptr) error("список пуст");
    return removeNode(list, list.head);
}

string flistDelTail(FList& list) {
    if (list.head == nullptr) error("список пуст");
    return removeNode(list, list.tail);
}

string flistDelBefore(FList& list, const string& target) {
    FNode* node = findNode(list, target);
    if (node == list.head) error("перед - " + target + " -  нет элементов");
    return removeNode(list, prevOf(list, node));
}

string flistDelAfter(FList& list, const string& target) {
    FNode* node = findNode(list, target);
    if (node->next == nullptr) error("после - " + target + " -  нет элементов");
    return removeNode(list, node->next);
}

string flistDelValue(FList& list, const string& value) {
    return removeNode(list, findNode(list, value));
}

// Поиск и чтение 

int flistFind(const FList& list, const string& value) {
    int index = 0;
    for (FNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur->value == value) return index;
        index++;
    }
    return -1;
}

string flistGet(const FList& list, int index) {
    if (index >= list.size) {
        error("индекс " + to_string(index) + " вне списка - длина " + to_string(list.size));
    }
    FNode* cur = list.head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->value;
}

string flistPrint(const FList& list) {
    if (list.head == nullptr) return "(пусто)";
    string result;
    for (FNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur != list.head) result += " -> ";
        result += cur->value;
    }
    return result;
}

// сначала выводим всё, что после узла, потом сам узел
static void printBackwards(FNode* node, string& result) {
    if (node == nullptr) return;
    printBackwards(node->next, result);
    if (!result.empty()) result += " -> ";
    result += node->value;
}

string flistPrintReverse(const FList& list) {
    if (list.head == nullptr) return "(пусто)";
    string result;
    printBackwards(list.head, result);
    return result;
}

string flistToText(const FList& list) {
    string result;
    for (FNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur != list.head) result += " ";
        result += cur->value;
    }
    return result;
}

void flistFree(FList& list) {
    while (list.head != nullptr) {
        FNode* next = list.head->next;
        delete list.head;
        list.head = next;
    }
    list.tail = nullptr;
    list.size = 0;
}

// Команды
string flistCommand(FList& list, const string& cmd, const vector<string>& args) {
    if (cmd == "FPUSHHEAD") {
        needArgs(args, 1, "FPUSHHEAD имя значение");
        flistPushHead(list, args[0]);
        return args[0];
    }
    if (cmd == "FPUSH" || cmd == "FPUSHTAIL") {
        needArgs(args, 1, cmd + " имя значение");
        flistPushTail(list, args[0]);
        return args[0];
    }
    if (cmd == "FINSERTBEFORE") {
        needArgs(args, 2, "FINSERTBEFORE имя цель значение");
        flistInsertBefore(list, args[0], args[1]);
        return args[1];
    }
    if (cmd == "FINSERTAFTER") {
        needArgs(args, 2, "FINSERTAFTER имя цель значение");
        flistInsertAfter(list, args[0], args[1]);
        return args[1];
    }
    if (cmd == "FDELHEAD") {
        needArgs(args, 0, "FDELHEAD имя");
        return flistDelHead(list);
    }
    if (cmd == "FDELTAIL") {
        needArgs(args, 0, "FDELTAIL имя");
        return flistDelTail(list);
    }
    if (cmd == "FDELBEFORE") {
        needArgs(args, 1, "FDELBEFORE имя цель");
        return flistDelBefore(list, args[0]);
    }
    if (cmd == "FDELAFTER") {
        needArgs(args, 1, "FDELAFTER имя цель");
        return flistDelAfter(list, args[0]);
    }
    if (cmd == "FDEL") {
        needArgs(args, 1, "FDEL имя значение");
        return flistDelValue(list, args[0]);
    }
    if (cmd == "FFIND") {
        needArgs(args, 1, "FFIND имя значение");
        return to_string(flistFind(list, args[0]));
    }
    if (cmd == "FGET") {
        needArgs(args, 1, "FGET имя индекс");
        return flistGet(list, toIndex(args[0]));
    }
    if (cmd == "FPRINTREV") {
        needArgs(args, 0, "FPRINTREV имя");
        return flistPrintReverse(list);
    }
    error("неизвестная команда " + cmd);
}
