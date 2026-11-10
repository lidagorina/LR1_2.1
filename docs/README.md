# LR1_2.1 — Абстрактные структуры данных


# Простой интерфейс структур данных

Лабораторная работа №1. Реализованы динамический массив, односвязный и двусвязный списки, стек, очередь и Complete Binary Tree (вариант 3). Программа на C++11 и Go-версия (все структуры, кроме дерева).

## Структура проекта

```text
LR1_2.1/
  CMakeLists.txt        сборка C++ версии
  test_commands.txt     тесты C++ версии
  example.data          пример файла с данными
  UI/
    main.cpp            интерфейс: --file, --query, чтение и запись файла
  core/                 структуры данных (struct + функции)
    common.h            ошибки, проверка аргументов, индекс
    array.h  array.cpp  массив (M)
    flist.h  flist.cpp  односвязный список (F)
    dlist.h  dlist.cpp  двусвязный список (L)
    stack.h  stack.cpp  стек (S)
    queue.h  queue.cpp  очередь (Q)
    tree.h   tree.cpp   Complete Binary Tree (T)
  dbms-go/              Go версия
    go.mod
    main.go
    test_commands.txt
    core/
      common/  array/  flist/  dlist/  stack/  queue/
  docs/
    README.md
```

## Сборка

C++ через CMake:

```bash
cmake -S . -B build
cmake --build build
cd build
./dbms --file file.data --query 'SPUSH mystack item'
```

C++ через g++ (из корня проекта):

```bash
g++ -std=c++11 -Wall -Wextra UI/main.cpp core/*.cpp -o dbms
```

Go (из папки `dbms-go`):

```bash
cd dbms-go
go build -o dbms .
```

## Запуск

```bash
./dbms --file file.data --query 'MPUSH numbers 10'
```

- `--file` задаёт путь к файлу данных.
- `--query` задаёт один запрос.
- `numbers` — имя структуры.
- `10` — значение элемента.

Весь запрос заключается в кавычки, чтобы оболочка передала его как один аргумент.

```text
argv[0] = ./dbms
argv[1] = --file
argv[2] = file.data
argv[3] = --query
argv[4] = MPUSH numbers 10
argc    = 5
```

Первая буква команды — тип структуры. Регистр команды не важен (`spush` = `SPUSH`), имя структуры сохраняется как введено. Структура создаётся первой командой добавления. Файл перезаписывается только если данные изменились.

## Правила и команды

### Массив

| Команда | Действие |
|---|---|
| `MCREATE name` | Создать пустой массив |
| `MPUSH name value` | Добавить в конец |
| `MINSERT name index value` | Вставить по индексу |
| `MGET name index` | Получить элемент |
| `MSET name index value` | Заменить значение |
| `MDEL name index` | Удалить элемент |
| `MLEN name` | Получить длину |

### Односвязный список

| Команда | Действие |
|---|---|
| `FPUSH name value` | Добавить в конец (то же, что `FPUSHTAIL`) |
| `FPUSHHEAD name value` | Добавить в начало |
| `FINSERTBEFORE name target value` | Добавить перед элементом `target` |
| `FINSERTAFTER name target value` | Добавить после элемента `target` |
| `FDELHEAD name` | Удалить голову |
| `FDELTAIL name` | Удалить хвост |
| `FDELBEFORE name target` | Удалить элемент перед `target` |
| `FDELAFTER name target` | Удалить элемент после `target` |
| `FDEL name value` | Удалить по значению |
| `FFIND name value` | Найти: индекс или -1 |
| `FGET name index` | Прочитать по индексу |
| `FPRINTREV name` | Вывести с конца |

### Двусвязный список

Те же команды с буквой `L`: `LPUSH`, `LPUSHHEAD`, `LINSERTBEFORE`, `LINSERTAFTER`, `LDELHEAD`, `LDELTAIL`, `LDELBEFORE`, `LDELAFTER`, `LDEL`, `LFIND`, `LGET`, `LPRINTREV`.

### Очередь, стек и дерево

| Команда | Действие |
|---|---|
| `QPUSH name value` | Добавить в конец очереди |
| `QPOP name` | Прочитать и удалить первый элемент |
| `SPUSH name value` | Добавить на вершину стека |
| `SPOP name` | Прочитать и удалить вершину |
| `TINSERT name value` | Вставить в дерево (в первую свободную ячейку) |
| `TINSERTAT name index value` | Вставить в заданную ячейку массива дерева |
| `TGET name value` | Проверить наличие значения (то же, что `ISMEMBER`) |
| `TISCOMPLETE name` | Проверка на Complete: `TRUE` / `FALSE` |
| `TISFULL name` | Проверка на Full: `TRUE` / `FALSE` |

### Печать

```text
PRINT name
```

## Формат файла

Одна строка — одна структура: `ТИП имя элементы`.

```text
ARRAY array 10 30 40
FLIST forward 5 20
DLIST list 65 53
STACK stack 200 100
QUEUE queue 15 20
TREE gap A B C # E
TREE tree 10 20 30 40 50 60
```

Стек записывается от вершины ко дну, очередь и списки — от начала к концу. Дерево — содержимое массива, `#` — пустая ячейка.

## Тесты

```bash
bash test_commands.txt              # C++ (из папки, где лежит dbms)
cd dbms-go && bash test_commands.txt # Go
```

Под каждой командой в файле записан ожидаемый ответ.


// rm -f file.data