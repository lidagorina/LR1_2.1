// Пакет queue — очередь (команды на букву Q).

package queue

import (
	"dbms-go/core/common"
)

type QNode struct {
	value string
	next  *QNode
}

type Queue struct {
	head *QNode // начало очереди — отсюда забираем
	tail *QNode // конец очереди — сюда добавляем
}

// O(1): новый узел цепляем за последний
func push(q *Queue, value string) {
	node := &QNode{value: value}
	if q.tail == nil {
		q.head = node
	} else {
		q.tail.next = node
	}
	q.tail = node
}

// O(1): забираем первый узел
func pop(q *Queue) string {
	if q.head == nil {
		common.Fail("очередь пуста")
	}
	value := q.head.value
	q.head = q.head.next
	if q.head == nil {
		q.tail = nil
	}
	return value
}

func toString(q *Queue) string {
	if q.head == nil {
		return "(пусто)"
	}
	result := "начало -> "
	for cur := q.head; cur != nil; cur = cur.next {
		if cur != q.head {
			result += " | "
		}
		result += cur.value
	}
	return result + " <- конец"
}

// Для файла
func toText(q *Queue) string {
	result := ""
	for cur := q.head; cur != nil; cur = cur.next {
		if cur != q.head {
			result += " "
		}
		result += cur.value
	}
	return result
}
