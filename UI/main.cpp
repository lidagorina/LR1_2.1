// UI/main.cpp — интерфейс командной строки (главный файл программы)


// Запуск:  ./dbms --file file.data --query 'SPUSH mystack item'

// программа делает
//   1. читает аргументы --file и --query;
//   2. загружает все структуры из файла;
//   3. по первой букве команды выбирает структуру и выполняет команду;
//   4. если данные изменились, записывает файл заново;
//   5. печатает ответ.

// Формат файла — одна структура на строку:  ТИП имя элемент1 элемент2 ...
#include <cctype>
#include <fstream>
#include <map>
#include <sstream>

#include "../core/array.h"
#include "../core/dlist.h"
#include "../core/flist.h"
#include "../core/queue.h"
#include "../core/stack.h"
#include "../core/tree.h"

// Все структуры хранятся по именам: имя - структура
map<string, Array> arrays;
map<string, FList> flists;
map<string, DList> dlists;
map<string, Stack> stacks;
map<string, Queue> queues;
map<string, Tree> trees;


vector<string> split(const string& line) {
    vector<string> words;
    istringstream in(line);
    string word;
    while (in >> word) words.push_back(word);
    return words;
}


string toUpper(string text) {
    for (char& c : text) c = char(toupper((unsigned char)c));
    return text;
}

// типа структура с таким именем 
string typeOf(const string& name) {
    if (arrays.count(name)) return "ARRAY";
    if (flists.count(name)) return "FLIST";
    if (dlists.count(name)) return "DLIST";
    if (stacks.count(name)) return "STACK";
    if (queues.count(name)) return "QUEUE";
    if (trees.count(name)) return "TREE";
    return "";
}

// Работа с файлом 

void loadFile(const string& fileName) {
    ifstream file(fileName);  
    string line;
    while (getline(file, line)) {
        vector<string> w = split(line);  // w[0] — тип, w[1] — имя
        if (w.size() < 2) continue;
        string type = w[0];
        string name = w[1];

        if (type == "ARRAY") {
            Array& a = arrays[name];  // [name] создаёт пустую структуру
            for (size_t i = 2; i < w.size(); i++) arrayPush(a, w[i]);
        } else if (type == "FLIST") {
            FList& f = flists[name];
            for (size_t i = 2; i < w.size(); i++) flistPushTail(f, w[i]);
        } else if (type == "DLIST") {
            DList& d = dlists[name];
            for (size_t i = 2; i < w.size(); i++) dlistPushTail(d, w[i]);
        } else if (type == "STACK") {
            Stack& s = stacks[name];
            // стек записан от вершины ко дну, поэтому кладём с конца
            for (size_t i = w.size(); i > 2; i--) stackPush(s, w[i - 1]);
        } else if (type == "QUEUE") {
            Queue& q = queues[name];
            for (size_t i = 2; i < w.size(); i++) queuePush(q, w[i]);
        } else if (type == "TREE") {
            Tree& t = trees[name];
            for (size_t i = 2; i < w.size(); i++) arrayPush(t.cells, w[i]);
        }
    }
}

// строка в файл: "ТИП имя элементы"
string makeLine(const string& type, const string& name, const string& data) {
    if (data.empty()) return type + " " + name + "\n";
    return type + " " + name + " " + data + "\n";
}


string allToText() {
    string text;
    for (auto& it : arrays) text += makeLine("ARRAY", it.first, arrayToText(it.second));
    for (auto& it : flists) text += makeLine("FLIST", it.first, flistToText(it.second));
    for (auto& it : dlists) text += makeLine("DLIST", it.first, dlistToText(it.second));
    for (auto& it : stacks) text += makeLine("STACK", it.first, stackToText(it.second));
    for (auto& it : queues) text += makeLine("QUEUE", it.first, queueToText(it.second));
    for (auto& it : trees) text += makeLine("TREE", it.first, treeToText(it.second));
    return text;
}

void saveFile(const string& fileName) {
    ofstream file(fileName);
    file << allToText();
}


void freeAll() {
    for (auto& it : arrays) arrayFree(it.second);
    for (auto& it : flists) flistFree(it.second);
    for (auto& it : dlists) dlistFree(it.second);
    for (auto& it : stacks) stackFree(it.second);
    for (auto& it : queues) queueFree(it.second);
    for (auto& it : trees) treeFree(it.second);
}

// Выполнение команды 

string runCommand(const string& query) {
    vector<string> words = split(query);
    if (words.size() < 2) error("запрос должен быть: КОМАНДА имя [аргументы]");

    string cmd = toUpper(words[0]);              // например SPUSH
    if (cmd == "ISMEMBER") cmd = "TGET";         // примере из методички
    string name = words[1];                      // имя
    vector<string> args(words.begin() + 2, words.end());  // аргументы
    string type = typeOf(name);                  // есть ли  такая структура

 
    if (cmd == "PRINT") {
        needArgs(args, 0, "PRINT имя");
        if (type == "ARRAY") return arrayPrint(arrays[name]);
        if (type == "FLIST") return flistPrint(flists[name]);
        if (type == "DLIST") return dlistPrint(dlists[name]);
        if (type == "STACK") return stackPrint(stacks[name]);
        if (type == "QUEUE") return queuePrint(queues[name]);
        if (type == "TREE") return treePrint(trees[name]);
        error("структура " + name + " не найдена");
    }

    
    string cmdType;
    switch (cmd[0]) {
        case 'M': cmdType = "ARRAY"; break;
        case 'F': cmdType = "FLIST"; break;
        case 'L': cmdType = "DLIST"; break;
        case 'S': cmdType = "STACK"; break;
        case 'Q': cmdType = "QUEUE"; break;
        case 'T': cmdType = "TREE"; break;
        default: error("неизвестная команда " + cmd);
    }

    if (type == "") {
       
        bool adds = cmd.find("PUSH") != string::npos ||
                    cmd.find("INSERT") != string::npos || cmd == "MCREATE";
        if (!adds) error("структура - " + name + "- не найдена");
    } else if (type != cmdType) {
        error("имя - " + name + " имеет тип " + type + " команда " + cmd + " к нему не подходит");
    } else if (cmd == "MCREATE") {
        error("массив - " + name + " - уже существует");
    }

   
    if (cmdType == "ARRAY") return arrayCommand(arrays[name], cmd, args);
    if (cmdType == "FLIST") return flistCommand(flists[name], cmd, args);
    if (cmdType == "DLIST") return dlistCommand(dlists[name], cmd, args);
    if (cmdType == "STACK") return stackCommand(stacks[name], cmd, args);
    if (cmdType == "QUEUE") return queueCommand(queues[name], cmd, args);
    return treeCommand(trees[name], cmd, args);
}



int main(int argc, char* argv[]) {
    string fileName;
    string query;

    // Аргументы идут парами: --file имя_файла --query 'запрос'
    for (int i = 1; i + 1 < argc; i += 2) {
        string key = argv[i];
        if (key == "--file") fileName = argv[i + 1];
        if (key == "--query") query = argv[i + 1];
    }
    if (fileName.empty() || query.empty()) {
        cout << "Запуск: ./dbms --file file.data --query 'SPUSH mystack item'" << endl;
        return 1;
    }

    
    atexit(freeAll);

    loadFile(fileName);
    string before = allToText();       // как было до команды
    string answer = runCommand(query);
    if (allToText() != before) {       // записываем файл, только если что-то изменилось
        saveFile(fileName);
    }
    cout << answer << endl;
    return 0;
}
