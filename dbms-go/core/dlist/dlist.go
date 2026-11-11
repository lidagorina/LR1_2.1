// dlist — двусвязный список (команды на букву L)

// искать его с начала не нужно (O(1) вместо O(n)).
package dlist

import (
	"strconv"

	"dbms-go/core/common"
)

// DNode — узел: значение + ссылка на след и на пред узел
type DNode struct {
	value string
	next  *DNode
	prev  *DNode
}

type DList struct {
	head *DNode
	tail *DNode
	size int
}

func findNode(list *DList, value string) *DNode {
	for cur := list.head; cur != nil; cur = cur.next {
		if cur.value == value {
			return cur
		}
	}
	common.Fail("элемент '" + value + "' не найден")
	return nil
}

// Вставить новый узел сразу после node
func insertAfterNode(list *DList, node *DNode, value string) {
	fresh := &DNode{value: value, prev: node, next: node.next}
	if node.next != nil {
		node.next.prev = fresh
	} else {
		list.tail = fresh
	}
	node.next = fresh
	list.size++
}

// Убрать узел
func removeNode(list *DList, node *DNode) string {
	if node.prev != nil {
		node.prev.next = node.next
	} else {
		list.head = node.next
	}
	if node.next != nil {
		node.next.prev = node.prev
	} else {
		list.tail = node.prev
	}
	list.size--
	return node.value
}

// Добавление

func pushHead(list *DList, value string) {
	node := &DNode{value: value, next: list.head}
	if list.head != nil {
		list.head.prev = node
	} else {
		list.tail = node
	}
	list.head = node
	list.size++
}

func pushTail(list *DList, value string) {
	if list.tail == nil {
		pushHead(list, value)
	} else {
		insertAfterNode(list, list.tail, value)
	}
}

func insertBefore(list *DList, target, value string) {
	node := findNode(list, target)
	if node.prev == nil {
		pushHead(list, value)
	} else {
		insertAfterNode(list, node.prev, value)
	}
}

func insertAfter(list *DList, target, value string) {
	insertAfterNode(list, findNode(list, target), value)
}

// Удаление

func delHead(list *DList) string {
	if list.head == nil {
		common.Fail("список пуст")
	}
	return removeNode(list, list.head)
}

func delTail(list *DList) string {
	if list.head == nil {
		common.Fail("список пуст")
	}
	return removeNode(list, list.tail)
}

func delBefore(list *DList, target string) string {
	node := findNode(list, target)
	if node.prev == nil {
		common.Fail("перед - " + target + " - нет элементов")
	}
	return removeNode(list, node.prev)
}

func delAfter(list *DList, target string) string {
	node := findNode(list, target)
	if node.next == nil {
		common.Fail("после '" + target + "' нет элементов")
	}
	return removeNode(list, node.next)
}

func delValue(list *DList, value string) string {
	return removeNode(list, findNode(list, value))
}

// Поиск и чтение

func find(list *DList, value string) int {
	index := 0
	for cur := list.head; cur != nil; cur = cur.next {
		if cur.value == value {
			return index
		}
		index++
	}
	return -1
}

func get(list *DList, index int) string {
	if index >= list.size {
		common.Fail("индекс " + strconv.Itoa(index) + " вне списка - длина " + strconv.Itoa(list.size))
	}
	cur := list.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	return cur.value
}

func toString(list *DList) string {
	if list.head == nil {
		return "(пусто)"
	}
	result := ""
	for cur := list.head; cur != nil; cur = cur.next {
		if cur != list.head {
			result += " <-> "
		}
		result += cur.value
	}
	return result
}

// Идём с хвоста по ссылкам prev
func printReverse(list *DList) string {
	if list.tail == nil {
		return "(пусто)"
	}
	result := ""
	for cur := list.tail; cur != nil; cur = cur.prev {
		if cur != list.tail {
			result += " <-> "
		}
		result += cur.value
	}
	return result
}

func toText(list *DList) string {
	result := ""
	for cur := list.head; cur != nil; cur = cur.next {
		if cur != list.head {
			result += " "
		}
		result += cur.value
	}
	return result
}
