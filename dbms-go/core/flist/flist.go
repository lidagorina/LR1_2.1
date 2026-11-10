// Пакет flist — односвязный список (команды на букву F)

package flist

import (
	"strconv"

	"dbms-go/core/common"
)

// значение + ссылка на след узел
type FNode struct {
	value string
	next  *FNode
}

// FList — первый узел, последний узел, количество
type FList struct {
	head *FNode
	tail *FNode
	size int
}

// Найти узел по значению
func findNode(list *FList, value string) *FNode {
	for cur := list.head; cur != nil; cur = cur.next {
		if cur.value == value {
			return cur
		}
	}
	common.Fail("элемент '" + value + "' не найден")
	return nil
}

// Найти узел перед node. идём с начала, O(n)
func prevOf(list *FList, node *FNode) *FNode {
	cur := list.head
	for cur.next != node {
		cur = cur.next
	}
	return cur
}

// Вставить новый узел сразу после node
func insertAfterNode(list *FList, node *FNode, value string) {
	node.next = &FNode{value: value, next: node.next}
	if node == list.tail {
		list.tail = node.next
	}
	list.size++
}

// Убрать узел из списка и вернуть его значение.
// Удалять память вручную не нужно — это делает сборщик мусора Go.
func removeNode(list *FList, node *FNode) string {
	if node == list.head {
		list.head = node.next
		if list.head == nil {
			list.tail = nil
		}
	} else {
		prev := prevOf(list, node)
		prev.next = node.next
		if node == list.tail {
			list.tail = prev
		}
	}
	list.size--
	return node.value
}

// Добавление

func pushHead(list *FList, value string) {
	list.head = &FNode{value: value, next: list.head}
	if list.tail == nil {
		list.tail = list.head
	}
	list.size++
}

func pushTail(list *FList, value string) {
	if list.tail == nil {
		pushHead(list, value)
	} else {
		insertAfterNode(list, list.tail, value)
	}
}

func insertBefore(list *FList, target, value string) {
	node := findNode(list, target)
	if node == list.head {
		pushHead(list, value)
	} else {
		insertAfterNode(list, prevOf(list, node), value)
	}
}

func insertAfter(list *FList, target, value string) {
	insertAfterNode(list, findNode(list, target), value)
}

// Удаление

func delHead(list *FList) string {
	if list.head == nil {
		common.Fail("список пуст")
	}
	return removeNode(list, list.head)
}

func delTail(list *FList) string {
	if list.head == nil {
		common.Fail("список пуст")
	}
	return removeNode(list, list.tail)
}

func delBefore(list *FList, target string) string {
	node := findNode(list, target)
	if node == list.head {
		common.Fail("перед '" + target + "' нет элементов")
	}
	return removeNode(list, prevOf(list, node))
}

func delAfter(list *FList, target string) string {
	node := findNode(list, target)
	if node.next == nil {
		common.Fail("после '" + target + "' нет элементов")
	}
	return removeNode(list, node.next)
}

func delValue(list *FList, value string) string {
	return removeNode(list, findNode(list, value))
}

// Поиск и чтение

func find(list *FList, value string) int {
	index := 0
	for cur := list.head; cur != nil; cur = cur.next {
		if cur.value == value {
			return index
		}
		index++
	}
	return -1
}

func get(list *FList, index int) string {
	if index >= list.size {
		common.Fail("индекс " + strconv.Itoa(index) + " вне списка (длина " + strconv.Itoa(list.size) + ")")
	}
	cur := list.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	return cur.value
}

func toString(list *FList) string {
	if list.head == nil {
		return "(пусто)"
	}
	result := ""
	for cur := list.head; cur != nil; cur = cur.next {
		if cur != list.head {
			result += " -> "
		}
		result += cur.value
	}
	return result
}

// сначала выводим всё, что после узла, потом сам узел
func printBackwards(node *FNode, result *string) {
	if node == nil {
		return
	}
	printBackwards(node.next, result)
	if *result != "" {
		*result += " -> "
	}
	*result += node.value
}

func printReverse(list *FList) string {
	if list.head == nil {
		return "(пусто)"
	}
	result := ""
	printBackwards(list.head, &result)
	return result
}

func toText(list *FList) string {
	result := ""
	for cur := list.head; cur != nil; cur = cur.next {
		if cur != list.head {
			result += " "
		}
		result += cur.value
	}
	return result
}
