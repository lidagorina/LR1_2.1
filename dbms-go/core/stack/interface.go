package stack

import (
	"dbms-go/core/common"
)

// В файле стек записан от вершины ко дну, поэтому кладём с конца.
func Load(s *Stack, items []string) {
	for i := len(items) - 1; i >= 0; i-- {
		push(s, items[i])
	}
}

func Print(s *Stack) string { return toString(s) }

func ToText(s *Stack) string { return toText(s) }

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
