// tree.cpp — Complete Binary Tree на массиве
#include "tree.h"
#include <queue>


static const string EMPTY = "#";  // пустая ячейка

// Создать новый узел
static TNode* nodeAt(const Tree& t, int i) {
    if (i == 0) return t.root;
    TNode* parent = nodeAt(t, (i - 1) / 2);
    if (parent == nullptr) return nullptr;
    return (i % 2 == 1) ? parent->left : parent->right;  // вернуть левого ребёнка родителя или правого
}

// Есть ли узел в ячейке i
static bool has(const Tree& t, int i) {
    return nodeAt(t, i) != nullptr;
}

// Самый большой номер узла в поддереве
static int lastIndex(TNode* node, int i) {
    if (node == nullptr) return -1;
    int best = i;
    int l = lastIndex(node->left, 2 * i + 1);
    int r = lastIndex(node->right, 2 * i + 2);
    if (l > best) best = l;
    if (r > best) best = r;
    return best;
}

// размер
static int count(const Tree& t) {
    return lastIndex(t.root, 0) + 1;
}

//новый узел на место с номером i 
static void attach(Tree& t, int i, const string& value) {
    TNode* node = new TNode;
    node->value = value;
    if (i == 0) {
        t.root = node;
    } else if (i % 2 == 1) {
        nodeAt(t, (i - 1) / 2)->left = node; //нечётный - левый ребёнок родителя
    } else {
        nodeAt(t, (i - 1) / 2)->right = node; // чётный  правый ребёнок родителя
    }
    
}


// Вставка в первую свободную ячейку (по уровням, слева направо)
void treeInsert(Tree& t, const string& value) {
    if (value == EMPTY) error("значение '#' занято под пустые ячейки");
    for (int i = 0; i <= count(t); i++) {
        if (!has(t, i) && (i == 0 || has(t, (i - 1) / 2))) {
            attach(t, i, value);
            return;
        }
    }
}

// Вставка на конкретное место
void treeInsertAt(Tree& t, int index, const string& value) {
    if (value == EMPTY) error("значение '#' занято под пустые ячейки");
    if (has(t, index)) error("ячейка " + to_string(index) + " уже занята");
    if (index > 0 && !has(t, (index - 1) / 2)) {
        error("у ячейки " + to_string(index) + " нет родителя");
    }
    attach(t, index, value);
}

// O(n)
bool treeContains(const Tree& t, const string& value) {
    for (int i = 0; i < count(t); i++) {
        if (has(t, i) && nodeAt(t, i)->value == value) return true;
    }
    return false;
}


bool treeIsComplete(const Tree& t) {
    bool emptySeen = false;
    for (int i = 0; i < count(t); i++) {
        if (!has(t, i)) {
            emptySeen = true;
        } else if (emptySeen) {
            return false;
        }
    }
    return true;
}


bool treeIsFull(const Tree& t) {
    for (int i = 0; i < count(t); i++) {
        if (has(t, i) && has(t, 2 * i + 1) != has(t, 2 * i + 2)) {
            return false;
        }
    }
    return true;
}


// Рисуем дерево
string treeDrawUpright(const Tree& t) {
    if (!has(t, 0)) return "(пусто)";

    int height = 0;                       // число уровней
    while ((1 << height) - 1 < count(t)) height++;

    int width = 1;                        // ширина самого длинного значения
    for (int i = 0; i < count(t); i++)
        if (has(t, i) && (int)nodeAt(t, i)->value.size() > width) width = nodeAt(t, i)->value.size();
    int slot = width + 2;                 // ширина клетки чтобы все было видно
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
            const string& v = nodeAt(t, i)->value;
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
    string out = t.root->value + " [0]\n";
    out += "\n" + treeDrawUpright(t);
    return out + "По уровням: " + treeToText(t);
}


string treeToText(const Tree& t) {
    string result;
    for (int i = 0; i < count(t); i++) {
        if (i > 0) result += " ";
        result += has(t, i) ? nodeAt(t, i)->value : EMPTY;
    }
    return result;
}

void treeLoad(Tree& t, const vector<string>& items) {
    for (size_t i = 0; i < items.size(); i++) {
        if (items[i] != EMPTY) treeInsertAt(t, int(i), items[i]);
    }
}

static void freeNode(TNode* node) {
    if (node == nullptr) return;
    freeNode(node->left);
    freeNode(node->right);
    delete node;
}

void treeFree(Tree& t) {
    freeNode(t.root);
    t.root = nullptr;
}


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
