// interface.go — то, что пакет flist показывает наружу (для main.go).

package flist

import (
	"strconv"

	"dbms-go/core/common"
)

// заполнить структуру элементами из файла
func Load(list *FList, items []string) {
	for _, item := range items {
		pushTail(list, item)
	}
}

// Print — вывод на экран (команда PRINT)
func Print(list *FList) string { return toString(list) }

// ToText — строка для файла
func ToText(list *FList) string { return toText(list) }

// Command — выполнить команду и вернуть ответ
func Command(list *FList, cmd string, args []string) string {
	switch cmd {
	case "FPUSHHEAD":
		common.NeedArgs(args, 1, "FPUSHHEAD имя значение")
		pushHead(list, args[0])
		return args[0]
	case "FPUSH", "FPUSHTAIL":
		common.NeedArgs(args, 1, cmd+" имя значение")
		pushTail(list, args[0])
		return args[0]
	case "FINSERTBEFORE":
		common.NeedArgs(args, 2, "FINSERTBEFORE имя цель значение")
		insertBefore(list, args[0], args[1])
		return args[1]
	case "FINSERTAFTER":
		common.NeedArgs(args, 2, "FINSERTAFTER имя цель значение")
		insertAfter(list, args[0], args[1])
		return args[1]
	case "FDELHEAD":
		common.NeedArgs(args, 0, "FDELHEAD имя")
		return delHead(list)
	case "FDELTAIL":
		common.NeedArgs(args, 0, "FDELTAIL имя")
		return delTail(list)
	case "FDELBEFORE":
		common.NeedArgs(args, 1, "FDELBEFORE имя цель")
		return delBefore(list, args[0])
	case "FDELAFTER":
		common.NeedArgs(args, 1, "FDELAFTER имя цель")
		return delAfter(list, args[0])
	case "FDEL":
		common.NeedArgs(args, 1, "FDEL имя значение")
		return delValue(list, args[0])
	case "FFIND":
		common.NeedArgs(args, 1, "FFIND имя значение")
		return strconv.Itoa(find(list, args[0]))
	case "FGET":
		common.NeedArgs(args, 1, "FGET имя индекс")
		return get(list, common.ToIndex(args[0]))
	case "FPRINTREV":
		common.NeedArgs(args, 0, "FPRINTREV имя")
		return printReverse(list)
	}
	common.Fail("неизвестная команда " + cmd)
	return ""
}
