package stack

import (
    "fmt"
    "encoding/gob"
    "encoding/json"
    "os"
)

type Stack struct {
    Arr    []string
    Top    int
    Length int
}

type jsonStack struct {
    Arr    []string
    Top    int
    Length int
}

func NewStack(length int) *Stack {
    return &Stack{
        Arr:    make([]string, length),
        Length: length,
        Top:    0,
    }
}

func (s *Stack) Push(x string) string {
    if s.Top >= s.Length {
        fmt.Println("Stack overflow!")
        return ""
    }
    s.Arr[s.Top] = x
    s.Top++
    return x
}

func (s *Stack) Pop() string {
    if s.Top == 0 {
        fmt.Println("Stack is empty!")
        return ""
    }
    s.Top--
    return s.Arr[s.Top]
}

func (s *Stack) Display() {
    if s.Top == 0 {
        fmt.Println("Stack is empty!")
        return
    }

    fmt.Print("Stack elements (from top to bottom): ")
    for i := s.Top - 1; i >= 0; i-- {
        fmt.Printf("%s ", s.Arr[i])
    }
    fmt.Println()
}

func (s *Stack) SaveToFile(filename string) error {
    data, err := json.MarshalIndent(jsonStack{
        Arr:    s.Arr[:s.Top],
        Top:    s.Top,
        Length: s.Length,
    }, "", "  ")
    if err != nil {
        return err
    }
    return os.WriteFile(filename, data, 0644)
}

func (s *Stack) LoadFromFile(filename string) error {
    data, err := os.ReadFile(filename)
    if err != nil {
        return err
    }

    var j jsonStack
    if err := json.Unmarshal(data, &j); err != nil {
        return err
    }

    s.Length = j.Length
    s.Top = j.Top
    s.Arr = make([]string, s.Length)
    copy(s.Arr, j.Arr)

    return nil
}

func (s *Stack) SaveBinary(filename string) error {
    f, err := os.Create(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    enc := gob.NewEncoder(f)
    return enc.Encode(jsonStack{
        Arr:    s.Arr[:s.Top],
        Top:    s.Top,
        Length: s.Length,
    })
}

func (s *Stack) LoadBinary(filename string) error {
    f, err := os.Open(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    dec := gob.NewDecoder(f)

    var j jsonStack
    if err := dec.Decode(&j); err != nil {
        return err
    }

    s.Length = j.Length
    s.Top = j.Top
    s.Arr = make([]string, s.Length)
    copy(s.Arr, j.Arr)

    return nil
}
