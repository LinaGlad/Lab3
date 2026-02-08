package utils

import "strings"

func SplitQuery(query string) []string {
	return strings.Fields(query)
}
