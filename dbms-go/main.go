// main.go — главный файл Go-версии (массив, списки, стек, очередь).

// Запуск:  ./dbms --file file.data --query 'SPUSH mystack item'

package main

import (
	"bufio"
	"flag"
	"fmt"
	"os"
	"sort"
	"strings"

	"dbms-go/core/array"
	"dbms-go/core/common"
	"dbms-go/core/dlist"
	"dbms-go/core/flist"
	"dbms-go/core/queue"
	"dbms-go/core/stack"
)

// Все структуры хранятся по именам: имя -> структура
var arrays = map[string]*array.Array{}
var flists = map[string]*flist.FList{}
var dlists = map[string]*dlist.DList{}
var stacks = map[string]*stack.Stack{}
var queues = map[string]*queue.Queue{}

var treeLines []string

// Какого типа структура с таким именем
func typeOf(name string) string {
	if arrays[name] != nil {
		return "ARRAY"
	}
	if flists[name] != nil {
		return "FLIST"
	}
	if dlists[name] != nil {
		return "DLIST"
	}
	if stacks[name] != nil {
		return "STACK"
	}
	if queues[name] != nil {
		return "QUEUE"
	}
	return ""
}

// Работа с файлом

func loadFile(fileName string) {
	file, err := os.Open(fileName)
	if err != nil {
		return
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		w := strings.Fields(scanner.Text()) // w[0] — тип, w[1] — имя
		if len(w) < 2 {
			continue
		}
		name := w[1]
		switch w[0] {
		case "ARRAY":
			arrays[name] = &array.Array{}
			array.Load(arrays[name], w[2:])
		case "FLIST":
			flists[name] = &flist.FList{}
			flist.Load(flists[name], w[2:])
		case "DLIST":
			dlists[name] = &dlist.DList{}
			dlist.Load(dlists[name], w[2:])
		case "STACK":
			stacks[name] = &stack.Stack{}
			stack.Load(stacks[name], w[2:])
		case "QUEUE":
			queues[name] = &queue.Queue{}
			queue.Load(queues[name], w[2:])
		case "TREE":
			treeLines = append(treeLines, scanner.Text())
		}
	}
}

// "ТИП имя элементы"
func makeLine(typeName, name, data string) string {
	if data == "" {
		return typeName + " " + name + "\n"
	}
	return typeName + " " + name + " " + data + "\n"
}

// Всё содержимое базы в виде текста (точто запишется в файл)
func allToText() string {
	lines := []string{}
	for name, a := range arrays {
		lines = append(lines, makeLine("ARRAY", name, array.ToText(a)))
	}
	for name, f := range flists {
		lines = append(lines, makeLine("FLIST", name, flist.ToText(f)))
	}
	for name, d := range dlists {
		lines = append(lines, makeLine("DLIST", name, dlist.ToText(d)))
	}
	for name, s := range stacks {
		lines = append(lines, makeLine("STACK", name, stack.ToText(s)))
	}
	for name, q := range queues {
		lines = append(lines, makeLine("QUEUE", name, queue.ToText(q)))
	}
	for _, line := range treeLines {
		lines = append(lines, line+"\n")
	}
	// Словарь в Go обходится в случайном порядке — сортируем строки,

	// чтобы файл всегда выглядел одинаково
	sort.Strings(lines)
	return strings.Join(lines, "")
}

func saveFile(fileName string) {
	os.WriteFile(fileName, []byte(allToText()), 0644)
}

// Выполнение команды

func runCommand(query string) string {
	words := strings.Fields(query)
	if len(words) < 2 {
		common.Fail("запрос должен быть: КОМАНДА имя [аргументы]")
	}
	cmd := strings.ToUpper(words[0]) //  SPUSH
	name := words[1]                 // имя
	args := words[2:]                // аргументы
	typeName := typeOf(name)         // есть ли  такая структура

	if cmd == "ISMEMBER" || cmd[0] == 'T' {
		common.Fail("деревья реализованы в C++ версии")
	}

	// PRINT — для любой структуры
	if cmd == "PRINT" {
		common.NeedArgs(args, 0, "PRINT имя")
		switch typeName {
		case "ARRAY":
			return array.Print(arrays[name])
		case "FLIST":
			return flist.Print(flists[name])
		case "DLIST":
			return dlist.Print(dlists[name])
		case "STACK":
			return stack.Print(stacks[name])
		case "QUEUE":
			return queue.Print(queues[name])
		}
		common.Fail("структура '" + name + "' не найдена")
	}

	// Первая буква команды
	cmdType := ""
	switch cmd[0] {
	case 'M':
		cmdType = "ARRAY"
	case 'F':
		cmdType = "FLIST"
	case 'L':
		cmdType = "DLIST"
	case 'S':
		cmdType = "STACK"
	case 'Q':
		cmdType = "QUEUE"
	default:
		common.Fail("неизвестная команда " + cmd)
	}

	if typeName == "" {

		adds := strings.Contains(cmd, "PUSH") || strings.Contains(cmd, "INSERT") || cmd == "MCREATE"
		if !adds {
			common.Fail("структура '" + name + "' не найдена")
		}
	} else if typeName != cmdType {
		common.Fail("'" + name + "' имеет тип " + typeName + ", команда " + cmd + " к нему не подходит")
	} else if cmd == "MCREATE" {
		common.Fail("массив '" + name + "' уже существует")
	}

	// Передаём команду нужной структуре
	switch cmdType {
	case "ARRAY":
		if arrays[name] == nil {
			arrays[name] = &array.Array{}
		}
		return array.Command(arrays[name], cmd, args)
	case "FLIST":
		if flists[name] == nil {
			flists[name] = &flist.FList{}
		}
		return flist.Command(flists[name], cmd, args)
	case "DLIST":
		if dlists[name] == nil {
			dlists[name] = &dlist.DList{}
		}
		return dlist.Command(dlists[name], cmd, args)
	case "STACK":
		if stacks[name] == nil {
			stacks[name] = &stack.Stack{}
		}
		return stack.Command(stacks[name], cmd, args)
	default: // QUEUE
		if queues[name] == nil {
			queues[name] = &queue.Queue{}
		}
		return queue.Command(queues[name], cmd, args)
	}
}

func main() {
	fileName := flag.String("file", "", "файл с данными")
	query := flag.String("query", "", "запрос, например 'SPUSH mystack item'")
	flag.Parse()

	if *fileName == "" || *query == "" {
		fmt.Println("Запуск: ./dbms --file file.data --query 'SPUSH mystack item'")
		os.Exit(1)
	}

	loadFile(*fileName)
	before := allToText() // как было до команды
	answer := runCommand(*query)
	if allToText() != before { // записываем файлтолько если что-то изменилось
		saveFile(*fileName)
	}
	fmt.Println(answer)
}
