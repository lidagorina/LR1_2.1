package queue

import (
	"dbms-go/core/common"
)

// заполнить структуру элементами из файла
func Load(q *Queue, items []string) {
	for _, item := range items {
		push(q, item)
	}
}

func Print(q *Queue) string { return toString(q) }

func ToText(q *Queue) string { return toText(q) }

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
