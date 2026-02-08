package stack

import "fmt"

type Stack struct {
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

