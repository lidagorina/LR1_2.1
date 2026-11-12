// tree.h — Complete Binary Tree (команды на букву T).

// Дерево хранится в обычном массиве (Array):
//  левый потомок в ячейке 2*i+1,
//  правый потомок в ячейке 2*i+2,
//  родитель в ячейке (i-1)/2

#ifndef TREE_H
#define TREE_H

#include "common.h"

struct TNode {
    string value;
    TNode* left = nullptr;   // левый потомок
    TNode* right = nullptr;  // правый потомок
};

struct Tree {
    TNode* root = nullptr;
};

void treeInsert(Tree& t, const string& value);               
void treeInsertAt(Tree& t, int index, const string& value);  
bool treeContains(const Tree& t, const string& value);       
bool treeIsComplete(const Tree& t);  
bool treeIsFull(const Tree& t);      

string treeDrawUpright(const Tree& t);  
string treePrint(const Tree& t);        
string treeToText(const Tree& t);       
void treeLoad(Tree& t, const vector<string>& items);  
void treeFree(Tree& t);                 

string treeCommand(Tree& t, const string& cmd, const vector<string>& args);



// void treeInsert(Tree& t, const string& value);               // в первое свободное место
// void treeInsertAt(Tree& t, int index, const string& value);  // в заданную ячейку
// bool treeContains(const Tree& t, const string& value);       // есть ли элемент
// bool treeIsComplete(const Tree& t);  // все уровни полные, последний — слева направо
// bool treeIsFull(const Tree& t);      // у каждого узла 0 или 2 потомка
// string treeDrawUpright(const Tree& t); 

// string treePrint(const Tree& t);
// string treeToText(const Tree& t);
// void treeFree(Tree& t);

// string treeCommand(Tree& t, const string& cmd, const vector<string>& args);

#endif
