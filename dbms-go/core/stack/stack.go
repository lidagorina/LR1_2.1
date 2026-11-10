// Пакет stack — стек (команды на букву S).

package stack

import (
	"dbms-go/core/common"
)

type SNode struct {
	value string
	next  *SNode // элемент, который лежит ниже
}

type Stack struct {
	top *SNode // верхний элемент
}

// O(1): новый узел становится вершиной, а старая вершина — под ним
func push(s *Stack, value string) {
	s.top = &SNode{value: value, next: s.top}
}

// O(1): снимаем вершину
func pop(s *Stack) string {
	if s.top == nil {
		common.Fail("стек пуст")
	}
	value := s.top.value
	s.top = s.top.next
	return value
}

func toString(s *Stack) string {
	if s.top == nil {
		return "(пусто)"
	}
	result := "вершина -> "
	for cur := s.top; cur != nil; cur = cur.next {
		if cur != s.top {
			result += " | "
		}
		result += cur.value
	}
	return result
}

// Для файла: от вершины ко дну
func toText(s *Stack) string {
	result := ""
	for cur := s.top; cur != nil; cur = cur.next {
		if cur != s.top {
			result += " "
		}
		result += cur.value
	}
	return result
}
