// dlist.cpp — двусвязный список.


#include "dlist.h"


static DNode* findNode(const DList& list, const string& value) {
    for (DNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur->value == value) return cur;
    }
    error("элемент - " + value + " - не найден");
}

// Вставить новый узел сразу после node
static void insertAfterNode(DList& list, DNode* node, const string& value) {
    DNode* fresh = new DNode;
    fresh->value = value;
    fresh->prev = node;
    fresh->next = node->next;
    if (node->next != nullptr) {
        node->next->prev = fresh;
    } else {
        list.tail = fresh;
    }
    node->next = fresh;
    list.size++;
}

// Убрать узел из списка
static string removeNode(DList& list, DNode* node) {
    if (node->prev != nullptr) {
        node->prev->next = node->next;
    } else {
        list.head = node->next;
    }
    if (node->next != nullptr) {
        node->next->prev = node->prev;
    } else {
        list.tail = node->prev;
    }
    string value = node->value;
    delete node;
    list.size--;
    return value;
}

// Добавление

void dlistPushHead(DList& list, const string& value) {
    DNode* node = new DNode;
    node->value = value;
    node->prev = nullptr;
    node->next = list.head;
    if (list.head != nullptr) {
        list.head->prev = node;
    } else {
        list.tail = node;
    }
    list.head = node;
    list.size++;
}

void dlistPushTail(DList& list, const string& value) {
    if (list.tail == nullptr) {
        dlistPushHead(list, value);
    } else {
        insertAfterNode(list, list.tail, value);
    }
}

void dlistInsertBefore(DList& list, const string& target, const string& value) {
    DNode* node = findNode(list, target);
    if (node->prev == nullptr) {
        dlistPushHead(list, value);
    } else {
        insertAfterNode(list, node->prev, value);
    }
}

void dlistInsertAfter(DList& list, const string& target, const string& value) {
    insertAfterNode(list, findNode(list, target), value);
}

// Удаление

string dlistDelHead(DList& list) {
    if (list.head == nullptr) error("список пуст");
    return removeNode(list, list.head);
}

string dlistDelTail(DList& list) {
    if (list.head == nullptr) error("список пуст");
    return removeNode(list, list.tail);
}

string dlistDelBefore(DList& list, const string& target) {
    DNode* node = findNode(list, target);
    if (node->prev == nullptr) error("перед '" + target + "' нет элементов");
    return removeNode(list, node->prev);
}

string dlistDelAfter(DList& list, const string& target) {
    DNode* node = findNode(list, target);
    if (node->next == nullptr) error("после '" + target + "' нет элементов");
    return removeNode(list, node->next);
}

string dlistDelValue(DList& list, const string& value) {
    return removeNode(list, findNode(list, value));
}

// Поиск и чтение
int dlistFind(const DList& list, const string& value) {
    int index = 0;
    for (DNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur->value == value) return index;
        index++;
    }
    return -1;
}

string dlistGet(const DList& list, int index) {
    if (index >= list.size) {
        error("индекс " + to_string(index) + " вне списка (длина " + to_string(list.size) + ")");
    }
    DNode* cur = list.head;
    for (int i = 0; i < index; i++) {
        cur = cur->next;
    }
    return cur->value;
}

string dlistPrint(const DList& list) {
    if (list.head == nullptr) return "(пусто)";
    string result;
    for (DNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur != list.head) result += " <-> ";
        result += cur->value;
    }
    return result;
}

// Идём с хвоста по ссылкам prev
string dlistPrintReverse(const DList& list) {
    if (list.tail  == nullptr) return "(пусто)";
    string result;
    for (DNode* cur = list.tail; cur != nullptr; cur = cur->prev) {
        if (cur != list.tail) result += " <-> ";
        result += cur->value;
    }
    return result;
}

string dlistToText(const DList& list) {
    string result;
    for (DNode* cur = list.head; cur != nullptr; cur = cur->next) {
        if (cur != list.head) result += " ";
        result += cur->value;
    }
    return result;
}

void dlistFree(DList& list) {
    while (list.head != nullptr) {
        DNode* next = list.head->next;
        delete list.head;
        list.head = next;
    }
    list.tail = nullptr;
    list.size = 0;
}

// Команды

string dlistCommand(DList& list, const string& cmd, const vector<string>& args) {
    if (cmd == "LPUSHHEAD") {
        needArgs(args, 1, "LPUSHHEAD имя значение");
        dlistPushHead(list, args[0]);
        return args[0];
    }
    if (cmd == "LPUSH" || cmd == "LPUSHTAIL") {
        needArgs(args, 1, cmd + " имя значение");
        dlistPushTail(list, args[0]);
        return args[0];
    }
    if (cmd == "LINSERTBEFORE") {
        needArgs(args, 2, "LINSERTBEFORE имя цель значение");
        dlistInsertBefore(list, args[0], args[1]);
        return args[1];
    }
    if (cmd == "LINSERTAFTER") {
        needArgs(args, 2, "LINSERTAFTER имя цель значение");
        dlistInsertAfter(list, args[0], args[1]);
        return args[1];
    }
    if (cmd == "LDELHEAD") {
        needArgs(args, 0, "LDELHEAD имя");
        return dlistDelHead(list);
    }
    if (cmd == "LDELTAIL") {
        needArgs(args, 0, "LDELTAIL имя");
        return dlistDelTail(list);
    }
    if (cmd == "LDELBEFORE") {
        needArgs(args, 1, "LDELBEFORE имя цель");
        return dlistDelBefore(list, args[0]);
    }
    if (cmd == "LDELAFTER") {
        needArgs(args, 1, "LDELAFTER имя цель");
        return dlistDelAfter(list, args[0]);
    }
    if (cmd == "LDEL") {
        needArgs(args, 1, "LDEL имя значение");
        return dlistDelValue(list, args[0]);
    }
    if (cmd == "LFIND") {
        needArgs(args, 1, "LFIND имя значение");
        return to_string(dlistFind(list, args[0]));
    }
    if (cmd == "LGET") {
        needArgs(args, 1, "LGET имя индекс");
        return dlistGet(list, toIndex(args[0]));
    }
    if (cmd == "LPRINTREV") {
        needArgs(args, 0, "LPRINTREV имя");
        return dlistPrintReverse(list);
    }
    error("неизвестная команда " + cmd);
}
