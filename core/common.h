// common.h — общее, которое нужно всем файлам.
#ifndef COMMON_H
#define COMMON_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Напечатать ошибку и сразу завершить программу.
[[noreturn]] inline void error(const string& message) {
    cout << "Ошибка: " << message << endl;
    exit(1);
}

// у команды нужное число аргументов
inline void needArgs(const vector<string>& args, int count, const string& format) {
    if (int(args.size()) != count) {
        error("неверное число аргументов, формат: " + format);
    }
}

// Перевести строку в номер/индекс
inline int toIndex(const string& text) {
    if (text.empty() || text.size() > 9) error("'" + text + "' — не индекс");
    for (char c : text) {
        if (c < '0' || c > '9') error("'" + text + "' — не индекс");
    }
    return stoi(text);
}

#endif
