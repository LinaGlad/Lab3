package array

import "fmt"

type Array struct {
    Arr    []string
    Length int
    Size   int
}

func NewArray(length int) *Array {
    return &Array{
        Arr:    make([]string, length),
        Length: length,
        Size:   0,
    }
}

func (a *Array) AddByIndex(index int, value string) string {
    if index < 0 || index > a.Size {
        return "Invalid index!"
    }
    if a.Size >= a.Length {
        return "Array is full!"
    }

    for i := a.Size; i > index; i-- {
        a.Arr[i] = a.Arr[i-1]
    }

    a.Arr[index] = value
    a.Size++
    return value
}

func (a *Array) AddToEnd(value string) string {
    if a.Size >= a.Length {
        return "Array is full!"
    }
    a.Arr[a.Size] = value
    a.Size++
    return value
}

func (a *Array) GetByIndex(index int) {
    if index < 0 || index >= a.Size {
        fmt.Println("Invalid index!")
        return
    }
    fmt.Println(a.Arr[index])
}

func (a *Array) DeleteByIndex(index int) string {
    if index < 0 || index >= a.Size {
        fmt.Println("Invalid index!")
        return ""
    }

    deleted := a.Arr[index]

    for i := index; i < a.Size-1; i++ {
        a.Arr[i] = a.Arr[i+1]
    }

    a.Size--
    return deleted
}

func (a *Array) ReplaceByIndex(index int, value string) string {
    if index < 0 || index >= a.Size {
        return "Invalid index!"
    }

    old := a.Arr[index]
    a.Arr[index] = value
    return fmt.Sprintf("%s -> %s", old, value)
}

func (a *Array) GetLength() {
    fmt.Printf("Size: %d\n", a.Size)
}

func (a *Array) DisplayAll() {
    for i := 0; i < a.Size; i++ {
        fmt.Printf("%d: %s\n", i, a.Arr[i])
    }
}
