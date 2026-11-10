// interface.go — то, что пакет array показывает наружу (для main.go)

package array

import (
	"strconv"

	"dbms-go/core/common"
)

// Load — заполнить массив элементами из файла
func Load(a *Array, items []string) {
	for _, item := range items {
		push(a, item)
	}
}

// Print — вывод на экран (команда PRINT):  [a, b, c]
func Print(a *Array) string { return toString(a) }

// ToText — строка для файла:  a b c
func ToText(a *Array) string { return toText(a) }

// Command — выполнить команду M... и вернуть ответ
func Command(a *Array, cmd string, args []string) string {
	switch cmd {
	case "MCREATE":
		common.NeedArgs(args, 0, "MCREATE имя")
		return "OK"
	case "MPUSH":
		common.NeedArgs(args, 1, "MPUSH имя значение")
		push(a, args[0])
		return args[0]
	case "MINSERT":
		common.NeedArgs(args, 2, "MINSERT имя индекс значение")
		insert(a, common.ToIndex(args[0]), args[1])
		return args[1]
	case "MGET":
		common.NeedArgs(args, 1, "MGET имя индекс")
		return get(a, common.ToIndex(args[0]))
	case "MSET":
		common.NeedArgs(args, 2, "MSET имя индекс значение")
		set(a, common.ToIndex(args[0]), args[1])
		return args[1]
	case "MDEL":
		common.NeedArgs(args, 1, "MDEL имя индекс")
		return remove(a, common.ToIndex(args[0]))
	case "MLEN":
		common.NeedArgs(args, 0, "MLEN имя")
		return strconv.Itoa(a.size)
	}
	common.Fail("неизвестная команда " + cmd)
	return ""
}
