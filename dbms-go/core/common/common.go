// Пакет common — общее

package common

import (
	"fmt"
	"os"
	"strconv"
)

// Fail — напечатать ошибку и сразу завершить программу.
// Файл с данными при этом НЕ сохраняется, поэтому он не портится.
func Fail(message string) {
	fmt.Println("Ошибка:", message)
	os.Exit(1)
}

// NeedArgs — проверить, что у команды нужное число аргументов
func NeedArgs(args []string, count int, format string) {
	if len(args) != count {
		Fail("неверное число аргументов, формат: " + format)
	}
}

// ToIndex — перевести строку в номер (индекс). Допускаются только цифры.
func ToIndex(text string) int {
	if text == "" || len(text) > 9 {
		Fail("'" + text + "' — не индекс")
	}
	for _, c := range text {
		if c < '0' || c > '9' {
			Fail("'" + text + "' — не индекс")
		}
	}
	number, _ := strconv.Atoi(text)
	return number
}
