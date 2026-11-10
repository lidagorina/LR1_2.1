// interface.go — то, что пакет dlist показывает наружу (для main.go)

package dlist

import (
	"strconv"

	"dbms-go/core/common"
)

// заполнить структуру элементами из файла
func Load(list *DList, items []string) {
	for _, item := range items {
		pushTail(list, item)
	}
}

// Print — вывод на экран (команда PRINT)
func Print(list *DList) string { return toString(list) }

// ToText — строка для файла
func ToText(list *DList) string { return toText(list) }

// Command — выполнить команду и вернуть ответ
func Command(list *DList, cmd string, args []string) string {
	switch cmd {
	case "LPUSHHEAD":
		common.NeedArgs(args, 1, "LPUSHHEAD имя значение")
		pushHead(list, args[0])
		return args[0]
	case "LPUSH", "LPUSHTAIL":
		common.NeedArgs(args, 1, cmd+" имя значение")
		pushTail(list, args[0])
		return args[0]
	case "LINSERTBEFORE":
		common.NeedArgs(args, 2, "LINSERTBEFORE имя цель значение")
		insertBefore(list, args[0], args[1])
		return args[1]
	case "LINSERTAFTER":
		common.NeedArgs(args, 2, "LINSERTAFTER имя цель значение")
		insertAfter(list, args[0], args[1])
		return args[1]
	case "LDELHEAD":
		common.NeedArgs(args, 0, "LDELHEAD имя")
		return delHead(list)
	case "LDELTAIL":
		common.NeedArgs(args, 0, "LDELTAIL имя")
		return delTail(list)
	case "LDELBEFORE":
		common.NeedArgs(args, 1, "LDELBEFORE имя цель")
		return delBefore(list, args[0])
	case "LDELAFTER":
		common.NeedArgs(args, 1, "LDELAFTER имя цель")
		return delAfter(list, args[0])
	case "LDEL":
		common.NeedArgs(args, 1, "LDEL имя значение")
		return delValue(list, args[0])
	case "LFIND":
		common.NeedArgs(args, 1, "LFIND имя значение")
		return strconv.Itoa(find(list, args[0]))
	case "LGET":
		common.NeedArgs(args, 1, "LGET имя индекс")
		return get(list, common.ToIndex(args[0]))
	case "LPRINTREV":
		common.NeedArgs(args, 0, "LPRINTREV имя")
		return printReverse(list)
	}
	common.Fail("неизвестная команда " + cmd)
	return ""
}
