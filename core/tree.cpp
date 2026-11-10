// tree.cpp — Complete Binary Tree на массиве
#include "tree.h"

static const string EMPTY = "#";  // пустая ячейка

// Есть ли узел в ячейке i
static bool has(const Tree& t, int i) {
    return i < t.cells.size && t.cells.data[i] != EMPTY;
}

// Вставка в первую свободную ячейку (по уровням, слева направо)
void treeInsert(Tree& t, const string& value) {
    if (value == EMPTY) error("значение '#' занято под пустые ячейки");
    for (int i = 0; i < t.cells.size; i++) {
        if (!has(t, i) && (i == 0 || has(t, (i - 1) / 2))) {
            t.cells.data[i] = value;
            return;
        }
    }
    arrayPush(t.cells, value);
}

// Вставка в конкретную ячейку
void treeInsertAt(Tree& t, int index, const string& value) {
    if (value == EMPTY) error("значение '#' занято под пустые ячейки");
    if (has(t, index)) error("ячейка " + to_string(index) + " уже занята");
    if (index > 0 && !has(t, (index - 1) / 2)) {
        error("у ячейки " + to_string(index) + " нет родителя");
    }
    while (t.cells.size <= index) {
        arrayPush(t.cells, EMPTY);  // дополняем массив пустыми 
    }
    t.cells.data[index] = value;
}

// O(n)
bool treeContains(const Tree& t, const string& value) {
    for (int i = 0; i < t.cells.size; i++) {
        if (has(t, i) && t.cells.data[i] == value) return true;
    }
    return false;
}

// Complete: в массиве после первой пустой ячейки не должно быть узлов
bool treeIsComplete(const Tree& t) {
    bool emptySeen = false;
    for (int i = 0; i < t.cells.size; i++) {
        if (!has(t, i)) {
            emptySeen = true;
        } else if (emptySeen) {
            return false;
        }
    }
    return true;
}

// Full: у каждого узла либо оба потомка, либо ни одного
bool treeIsFull(const Tree& t) {
    for (int i = 0; i < t.cells.size; i++) {
        if (has(t, i) && has(t, 2 * i + 1) != has(t, 2 * i + 2)) {
            return false;
        }
    }
    return true;
}


// дерево
string treeDrawUpright(const Tree& t) {
    if (!has(t, 0)) return "(пусто)";

    int height = 0;                       // число уровней
    while ((1 << height) - 1 < t.cells.size) height++;

    int width = 1;                        // ширина самого длинного значения
    for (int i = 0; i < t.cells.size; i++)
        if (has(t, i) && (int)t.cells.data[i].size() > width) width = t.cells.data[i].size();
    int slot = width + 2;                 // ширина клетки чтобы вмсе было видно
    int lineLen = (1 << (height - 1)) * slot;
    string out;
    for (int level = 0; level < height; level++) {
        int first = (1 << level) - 1;          // номер первого узла уровня
        int span = 1 << (height - 1 - level);  // сколько листьев под узлом
        string values(lineLen, ' ');
        string branches(lineLen, ' ');
        for (int j = 0; j < (1 << level); j++) {
            int i = first + j;
            if (!has(t, i)) continue;
            int center = (2 * j + 1) * span * slot / 2;
            const string& v = t.cells.data[i];
            values.replace(center - (int)v.size() / 2, v.size(), v);
            int step = span * slot / 4;        // ребенок в середине половины участка
            if (has(t, 2 * i + 1)) branches[center - step] = '/';
            if (has(t, 2 * i + 2)) branches[center + step] = '\\';
        }
        while (!values.empty() && values.back() == ' ') values.pop_back();
        while (!branches.empty() && branches.back() == ' ') branches.pop_back();
        out += values + "\n";
        if (level + 1 < height && !branches.empty()) out += branches + "\n";
    }
    return out;
}

string treePrint(const Tree& t) {
    if (!has(t, 0)) return "(пусто)";
    string out = t.cells.data[0] + " [0]\n";
    out += "\n" + treeDrawUpright(t);    
    return out + "Массив: " + arrayPrint(t.cells);
}

string treeToText(const Tree& t) { return arrayToText(t.cells); }

void treeFree(Tree& t) { arrayFree(t.cells); }

string treeCommand(Tree& t, const string& cmd, const vector<string>& args) {
    if (cmd == "TINSERT") {
        needArgs(args, 1, "TINSERT имя значение");
        treeInsert(t, args[0]);
        return args[0];
    }
    if (cmd == "TDRAW") {
    needArgs(args, 0, "TDRAW имя");
    return treeDrawUpright(t);
    }   
    if (cmd == "TINSERTAT") {
        needArgs(args, 2, "TINSERTAT имя индекс значение");
        treeInsertAt(t, toIndex(args[0]), args[1]);
        return args[1];
    }
    if (cmd == "TGET") {
        needArgs(args, 1, "TGET имя значение");
        return treeContains(t, args[0]) ? "TRUE" : "FALSE";
    }
    if (cmd == "TISCOMPLETE") {
        needArgs(args, 0, "TISCOMPLETE имя");
        return treeIsComplete(t) ? "TRUE" : "FALSE";
    }
    if (cmd == "TISFULL") {
        needArgs(args, 0, "TISFULL имя");
        return treeIsFull(t) ? "TRUE" : "FALSE";
    }
    error("неизвестная команда " + cmd);
}
