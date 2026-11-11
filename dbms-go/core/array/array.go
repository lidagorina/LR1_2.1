// array —  массив (команды на букву M)

package array

import (
	"strconv"
	"strings"

	"dbms-go/core/common"
)

// data — сколько поместится, size — сколько занято.
type Array struct {
	data []string
	size int
}

// Увеличить память
func grow(a *Array) {
	newCapacity := len(a.data) * 2
	if newCapacity == 0 {
		newCapacity = 4
	}
	newData := make([]string, newCapacity)
	for i := 0; i < a.size; i++ {
		newData[i] = a.data[i]
	}
	a.data = newData
}

func checkIndex(a *Array, index int) {
	if index >= a.size {
		common.Fail("индекс " + strconv.Itoa(index) + " вне массива - длина " + strconv.Itoa(a.size))
	}
}

// O(1) в среднем: обычно просто кладём в свободную ячейку
func push(a *Array, value string) {
	if a.size == len(a.data) {
		grow(a)
	}
	a.data[a.size] = value
	a.size++
}

// O(n): элементы правее индекса сдвигаются вправо
func insert(a *Array, index int, value string) {
	if index > a.size {
		common.Fail("индекс " + strconv.Itoa(index) + " вне массива - длина " + strconv.Itoa(a.size))
	}
	if a.size == len(a.data) {
		grow(a)
	}
	for i := a.size; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = value
	a.size++
}

// O(1)
func get(a *Array, index int) string {
	checkIndex(a, index)
	return a.data[index]
}

// O(1)
func set(a *Array, index int, value string) {
	checkIndex(a, index)
	a.data[index] = value
}

// O(n): элементы правее индекса сдвигаются влево
func remove(a *Array, index int) string {
	checkIndex(a, index)
	removed := a.data[index]
	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.size--
	return removed
}

func toString(a *Array) string {
	return "[" + strings.Join(a.data[:a.size], ", ") + "]"
}

func toText(a *Array) string {
	return strings.Join(a.data[:a.size], " ")
}
