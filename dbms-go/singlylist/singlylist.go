package singlylist

import (
    "fmt"
    "encoding/gob"
    "encoding/json"
    "os"
)


type SinglyNode struct {
    Key  string
    Next *SinglyNode
}

type ForwardList struct {
    Head *SinglyNode
}

func NewForwardList() *ForwardList {
    return &ForwardList{Head: nil}
}

type jsonForwardList struct {
    Elements []string
}

func (list *ForwardList) AddHead(value string) {
    newNode := &SinglyNode{
        Key:  value,
        Next: list.Head,
    }
    list.Head = newNode
}

func (list *ForwardList) AddAfter(ptr *SinglyNode, value string) {
    if ptr == nil {
        return
    }
    newNode := &SinglyNode{
        Key:  value,
        Next: ptr.Next,
    }
    ptr.Next = newNode
}

func (list *ForwardList) AddTail(value string) {
    if list.Head == nil {
        list.AddHead(value)
        return
    }

    current := list.Head
    for current.Next != nil {
        current = current.Next
    }

    current.Next = &SinglyNode{Key: value}
}

func (list *ForwardList) DeleteHead() string {
    if list.Head == nil {
        return ""
    }
    deleted := list.Head.Key
    list.Head = list.Head.Next
    return deleted
}

func (list *ForwardList) DeleteAfter(ptr *SinglyNode) string {
    if ptr == nil || ptr.Next == nil {
        return ""
    }
    deleted := ptr.Next.Key
    ptr.Next = ptr.Next.Next
    return deleted
}

func (list *ForwardList) FindByValue(value string) (*SinglyNode, int) {
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

func (list *ForwardList) AddBefore(value, element string) {
    ptr, pos := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return
    }

    if pos == 0 {
        list.AddHead(value)
        return
    }

    current := list.Head
    for i := 1; i < pos; i++ {
        current = current.Next
    }

    list.AddAfter(current, value)
}

func (list *ForwardList) AddAfterValue(value, element string) {
    ptr, _ := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return
    }
    list.AddAfter(ptr, value)
}

func (list *ForwardList) DeleteBefore(element string) string {
    ptr, pos := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return ""
    }

    if pos == 0 {
        fmt.Println("No elements before the first.")
        return ""
    }

    if pos == 1 {
        return list.DeleteHead()
    }

    current := list.Head
    for i := 1; i < pos-1; i++ {
        current = current.Next
    }

    return list.DeleteAfter(current)
}

func (list *ForwardList) DeleteAfterValue(element string) string {
    ptr, _ := list.FindByValue(element)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", element)
        return ""
    }

    if ptr.Next == nil {
        fmt.Printf("No element after %s.\n", element)
        return ""
    }

    return list.DeleteAfter(ptr)
}

func (list *ForwardList) DeleteTail() string {
    if list.Head == nil {
        fmt.Println("List is empty!")
        return ""
    }

    if list.Head.Next == nil {
        return list.DeleteHead()
    }

    current := list.Head
    for current.Next.Next != nil {
        current = current.Next
    }

    return list.DeleteAfter(current)
}

func (list *ForwardList) DeleteByValue(value string) string {
    ptr, pos := list.FindByValue(value)
    if ptr == nil {
        fmt.Printf("Element %s not found.\n", value)
        return ""
    }

    if pos == 0 {
        return list.DeleteHead()
    }

    current := list.Head
    for i := 1; i < pos; i++ {
        current = current.Next
    }

    return list.DeleteAfter(current)
}

func (list *ForwardList) Display() {
    fmt.Print("List (iterative): ")
    current := list.Head
    for current != nil {
        fmt.Printf("%s ", current.Key)
        current = current.Next
    }
    fmt.Println()

    fmt.Print("List (recursive): ")
    list.displayRecursive(list.Head)
    fmt.Println()
}

func (list *ForwardList) displayRecursive(node *SinglyNode) {
    if node == nil {
        return
    }
    fmt.Printf("%s ", node.Key)
    list.displayRecursive(node.Next)
}

func (list *ForwardList) Contains(value string) bool {
    ptr, _ := list.FindByValue(value)
    return ptr != nil
}

func (l *ForwardList) SaveToFile(filename string) error {
    var elements []string
    for cur := l.Head; cur != nil; cur = cur.Next {
        elements = append(elements, cur.Key)
    }

    data, err := json.MarshalIndent(jsonForwardList{Elements: elements}, "", "  ")
    if err != nil {
        return err
    }

    return os.WriteFile(filename, data, 0644)
}

func (l *ForwardList) LoadFromFile(filename string) error {
    data, err := os.ReadFile(filename)
    if err != nil {
        return err
    }

    var j jsonForwardList
    if err := json.Unmarshal(data, &j); err != nil {
        return err
    }

    l.Head = nil
    for _, val := range j.Elements {
        l.AddTail(val)
    }

    return nil
}

func (l *ForwardList) SaveBinary(filename string) error {
    f, err := os.Create(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    enc := gob.NewEncoder(f)

    var elements []string
    for cur := l.Head; cur != nil; cur = cur.Next {
        elements = append(elements, cur.Key)
    }

    return enc.Encode(elements)
}

func (l *ForwardList) LoadBinary(filename string) error {
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

    l.Head = nil
    for _, val := range elements {
        l.AddTail(val)
    }

    return nil
}
