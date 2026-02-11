package doublelist

import (
    "encoding/gob"
    "encoding/json"
    "os"
    "fmt"
)

type DoubleNode struct {
    Key  string
    Next *DoubleNode
    Prev *DoubleNode
}

type DoubleList struct {
    Head *DoubleNode
    Tail *DoubleNode
}

type jsonDoubleList struct {
    Elements []string
}

func NewDoubleList() *DoubleList {
    return &DoubleList{}
}

func (list *DoubleList) AddHead(value string) {
    newNode := &DoubleNode{
        Key:  value,
        Next: list.Head,
        Prev: nil,
    }

    if list.Head != nil {
        list.Head.Prev = newNode
    } else {
        list.Tail = newNode
    }

    list.Head = newNode
}

func (list *DoubleList) AddTail(value string) {
    newNode := &DoubleNode{
        Key:  value,
        Prev: list.Tail,
        Next: nil,
    }

    if list.Tail != nil {
        list.Tail.Next = newNode
    } else {
        list.Head = newNode
    }

    list.Tail = newNode
}

func (list *DoubleList) AddAfter(ptr *DoubleNode, value string) {
    if ptr == nil {
        return
    }

    newNode := &DoubleNode{
        Key:  value,
        Next: ptr.Next,
        Prev: ptr,
    }

    if ptr.Next != nil {
        ptr.Next.Prev = newNode
    } else {
        list.Tail = newNode
    }

    ptr.Next = newNode
}

func (list *DoubleList) AddBefore(ptr *DoubleNode, value string) {
    if ptr == nil {
        return
    }

    newNode := &DoubleNode{
        Key:  value,
        Prev: ptr.Prev,
        Next: ptr,
    }

    if ptr.Prev != nil {
        ptr.Prev.Next = newNode
    } else {
        list.Head = newNode
    }

    ptr.Prev = newNode
}

func (list *DoubleList) DeleteNode(ptr *DoubleNode) string {
    if ptr == nil {
        return ""
    }

    value := ptr.Key

    if ptr.Prev != nil {
        ptr.Prev.Next = ptr.Next
    } else {
        list.Head = ptr.Next
    }

    if ptr.Next != nil {
        ptr.Next.Prev = ptr.Prev
    } else {
        list.Tail = ptr.Prev
    }

    return value
}

func (list *DoubleList) DeleteHead() string {
    if list.Head == nil {
        return ""
    }
    return list.DeleteNode(list.Head)
}

func (list *DoubleList) DeleteTail() string {
    if list.Tail == nil {
        return ""
    }
    return list.DeleteNode(list.Tail)
}

func (list *DoubleList) FindByValue(value string) (*DoubleNode, int) {
    current := list.Head
    pos := 0

    for current != nil {
        if current.Key == value {
            return current, pos
        }
        current = current.Next
        pos++
    }

    return nil, -1
}

func (list *DoubleList) Contains(value string) bool {
    ptr, _ := list.FindByValue(value)
    return ptr != nil
}

func (list *DoubleList) AddBeforeValue(value, element string) {
    ptr, _ := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return
    }
    list.AddBefore(ptr, value)
}

func (list *DoubleList) AddAfterValue(value, element string) {
    ptr, _ := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return
    }
    list.AddAfter(ptr, value)
}

func (list *DoubleList) DeleteBeforeValue(element string) string {
    ptr, _ := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return ""
    }

    if ptr.Prev == nil {
        fmt.Println("No element before the first.")
        return ""
    }

    return list.DeleteNode(ptr.Prev)
}

func (list *DoubleList) DeleteAfterValue(element string) string {
    ptr, _ := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return ""
    }

    if ptr.Next == nil {
        fmt.Printf("No element after %s.\n", element)
        return ""
    }

    return list.DeleteNode(ptr.Next)
}

func (list *DoubleList) DeleteByValue(value string) string {
    ptr, _ := list.FindByValue(value)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", value)
        return ""
    }
    return list.DeleteNode(ptr)
}

func (list *DoubleList) Display() {
    fmt.Print("Forward: ")
    for cur := list.Head; cur != nil; cur = cur.Next {
        fmt.Printf("%s ", cur.Key)
    }
    fmt.Println()

    fmt.Print("Backward: ")
    for cur := list.Tail; cur != nil; cur = cur.Prev {
        fmt.Printf("%s ", cur.Key)
    }
    fmt.Println()
}

func (list *DoubleList) SaveToFile(filename string) error {
    var elements []string
    for cur := list.Head; cur != nil; cur = cur.Next {
        elements = append(elements, cur.Key)
    }

    data, err := json.MarshalIndent(jsonDoubleList{Elements: elements}, "", "  ")
    if err != nil {
        return err
    }

    return os.WriteFile(filename, data, 0644)
}

func (list *DoubleList) LoadFromFile(filename string) error {
    data, err := os.ReadFile(filename)
    if err != nil {
        return err
    }

    var j jsonDoubleList
    if err := json.Unmarshal(data, &j); err != nil {
        return err
    }

    list.Head = nil
    list.Tail = nil

    for _, val := range j.Elements {
        list.AddTail(val)
    }

    return nil
}

func (list *DoubleList) SaveBinary(filename string) error {
    f, err := os.Create(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    enc := gob.NewEncoder(f)

    var elements []string
    for cur := list.Head; cur != nil; cur = cur.Next {
        elements = append(elements, cur.Key)
    }

    return enc.Encode(elements)
}

func (list *DoubleList) LoadBinary(filename string) error {
    f, err := os.Open(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    dec := gob.NewDecoder(f)

    var elements []string
    if err := dec.Decode(&elements); err != nil {
        return err
    }

    list.Head = nil
    list.Tail = nil

    for _, val := range elements {
        list.AddTail(val)
    }

    return nil
}
