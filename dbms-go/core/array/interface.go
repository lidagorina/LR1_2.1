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

// [a, b, c]
func Print(a *Array) string { return toString(a) }

// a b c
func ToText(a *Array) string { return toText(a) }

// выполнить команду M
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
