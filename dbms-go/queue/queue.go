package queue

import (
    "fmt"
    "encoding/gob"
    "encoding/json"
    "os"
)

type Queue struct {
    Arr    []string
    Head   int
    Tail   int
    Length int
}

func NewQueue(length int) *Queue {
    return &Queue{
        Arr:    make([]string, length+1), 
        Length: length,
        Head:   1,
        Tail:   1,
    }
}

func (q *Queue) IsEmpty() bool {
    return q.Head == q.Tail
}

func (q *Queue) IsFull() bool {
    return (q.Tail%q.Length + 1) == q.Head
}

func (q *Queue) Push(x string) string {
    if q.IsFull() {
        fmt.Println("Queue overflow!")
        return ""
    }

    q.Arr[q.Tail] = x

    if q.Tail == q.Length {
        q.Tail = 1
    } else {
        q.Tail++
    }

    return x
}

func (q *Queue) Pop() string {
    if q.IsEmpty() {
        fmt.Println("Queue is empty!")
        return ""
    }

    value := q.Arr[q.Head]

    if q.Head == q.Length {
        q.Head = 1
    } else {
        q.Head++
    }

    return value
}

func (q *Queue) Display() {
    if q.IsEmpty() {
        fmt.Println("Queue is empty!")
        return
    }

    fmt.Print("Queue elements: ")

    if q.Head < q.Tail {
        for i := q.Head; i < q.Tail; i++ {
            fmt.Printf("%s ", q.Arr[i])
        }
    } else {
        for i := q.Head; i <= q.Length; i++ {
            fmt.Printf("%s ", q.Arr[i])
        }
        for i := 1; i < q.Tail; i++ {
            fmt.Printf("%s ", q.Arr[i])
        }
    }

    fmt.Println()
}

type jsonQueue struct {
    Arr    []string
    Head   int
    Tail   int
    Length int
}

func (q *Queue) SaveToFile(filename string) error {
    data, err := json.MarshalIndent(jsonQueue{
        Arr:    q.Arr,
        Head:   q.Head,
        Tail:   q.Tail,
        Length: q.Length,
    }, "", "  ")
    if err != nil {
        return err
    }
    return os.WriteFile(filename, data, 0644)
}

func (q *Queue) LoadFromFile(filename string) error {
    data, err := os.ReadFile(filename)
    if err != nil {
        return err
    }

    var j jsonQueue
    if err := json.Unmarshal(data, &j); err != nil {
        return err
    }

    q.Arr = j.Arr
    q.Head = j.Head
    q.Tail = j.Tail
    q.Length = j.Length

    return nil
}

func (q *Queue) SaveBinary(filename string) error {
    f, err := os.Create(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    enc := gob.NewEncoder(f)
    return enc.Encode(jsonQueue{
        Arr:    q.Arr,
        Head:   q.Head,
        Tail:   q.Tail,
        Length: q.Length,
    })
}

func (q *Queue) LoadBinary(filename string) error {
    f, err := os.Open(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    dec := gob.NewDecoder(f)

    var j jsonQueue
    if err := dec.Decode(&j); err != nil {
        return err
    }

    q.Arr = j.Arr
    q.Head = j.Head
    q.Tail = j.Tail
    q.Length = j.Length

    return nil
}
