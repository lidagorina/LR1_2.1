// interface.go — то, что пакет stack показывает наружу (для main.go)
package stack

import (
	"dbms-go/core/common"
)

// Load — заполнить стек элементами из файла.

// В файле стек записан от вершины ко дну, поэтому кладём с конца.
func Load(s *Stack, items []string) {
	for i := len(items) - 1; i >= 0; i-- {
		push(s, items[i])
	}
}

// Print — вывод на экран (команда PRINT)
func Print(s *Stack) string { return toString(s) }

// ToText — строка для файла
func ToText(s *Stack) string { return toText(s) }

// Command — выполнить команду и вернуть ответ
func Command(s *Stack, cmd string, args []string) string {
	switch cmd {
	case "SPUSH":
		common.NeedArgs(args, 1, "SPUSH имя значение")
		push(s, args[0])
		return args[0]
	case "SPOP":
		common.NeedArgs(args, 0, "SPOP имя")
		return pop(s)
	}
	common.Fail("неизвестная команда " + cmd)
	return ""
}
