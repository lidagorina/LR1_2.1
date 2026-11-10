// interface.go — то, что пакет queue показывает наружу (для main.go)

package queue

import (
	"dbms-go/core/common"
)

// Load — заполнить структуру элементами из файла
func Load(q *Queue, items []string) {
	for _, item := range items {
		push(q, item)
	}
}

// Print — вывод на экран (команда PRINT)
func Print(q *Queue) string { return toString(q) }

// ToText — строка для файла
func ToText(q *Queue) string { return toText(q) }

// Command — выполнить команду и вернуть ответ
func Command(q *Queue, cmd string, args []string) string {
	switch cmd {
	case "QPUSH":
		common.NeedArgs(args, 1, "QPUSH имя значение")
		push(q, args[0])
		return args[0]
	case "QPOP":
		common.NeedArgs(args, 0, "QPOP имя")
		return pop(q)
	}
	common.Fail("неизвестная команда " + cmd)
	return ""
}
