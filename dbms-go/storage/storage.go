package storage

import (
    "encoding/gob"
    "encoding/json"
    "os"

    "dbms-go/array"
    "dbms-go/doublelist"
    "dbms-go/hashtable"
    "dbms-go/queue"
    "dbms-go/singlylist"
    "dbms-go/stack"
    "dbms-go/tree"
)

type JSONSinglyList struct {
    Elements []string
}

type JSONDoubleList struct {
    Elements []string
}

type JSONStack struct {
    Length   int
    Top      int
    Elements []string
}

type JSONQueue struct {
    Length   int
    Head     int
    Tail     int
    Elements []string
}

type JSONStorage struct {
    SinglyLists map[string]JSONSinglyList
    DoubleLists map[string]JSONDoubleList
    Stacks      map[string]JSONStack
    Queues      map[string]JSONQueue
    HashTables  map[string][]struct {
        Key   string
        Value int
    }

    Arrays map[string][]string
    Trees  map[string][]int
}

type Storage struct {
    SinglyLists map[string]*singlylist.ForwardList
    DoubleLists map[string]*doublelist.DoubleList
    Stacks      map[string]*stack.Stack
    Queues      map[string]*queue.Queue
    HashTables  map[string]*hashtable.HashTable

    Arrays map[string]*array.Array
    Trees  map[string]*tree.Tree
}

func NewStorage() *Storage {
    return &Storage{
        SinglyLists: make(map[string]*singlylist.ForwardList),
        DoubleLists: make(map[string]*doublelist.DoubleList),
        Stacks:      make(map[string]*stack.Stack),
        Queues:      make(map[string]*queue.Queue),
        HashTables:  make(map[string]*hashtable.HashTable),

        Arrays: make(map[string]*array.Array),
        Trees:  make(map[string]*tree.Tree),
    }
}

func (s *Storage) SaveToFile(filename string) error {
    jsonStorage := JSONStorage{
        SinglyLists: make(map[string]JSONSinglyList),
        DoubleLists: make(map[string]JSONDoubleList),
        Stacks:      make(map[string]JSONStack),
        Queues:      make(map[string]JSONQueue),
        HashTables:  make(map[string][]struct{ Key string; Value int }),
        Arrays:      make(map[string][]string),
        Trees:       make(map[string][]int),
    }

    for name, list := range s.SinglyLists {
        var elements []string
        cur := list.Head
        for cur != nil {
            elements = append(elements, cur.Key)
            cur = cur.Next
        }
        jsonStorage.SinglyLists[name] = JSONSinglyList{Elements: elements}
    }

    for name, list := range s.DoubleLists {
        var elements []string
        cur := list.Head
        for cur != nil {
            elements = append(elements, cur.Key)
            cur = cur.Next
        }
        jsonStorage.DoubleLists[name] = JSONDoubleList{Elements: elements}
    }

    for name, st := range s.Stacks {
        elements := make([]string, st.Top)
        copy(elements, st.Arr[:st.Top])
        jsonStorage.Stacks[name] = JSONStack{
            Length:   st.Length,
            Top:      st.Top,
            Elements: elements,
        }
    }

    for name, q := range s.Queues {
        jsonStorage.Queues[name] = JSONQueue{
            Length:   q.Length,
            Head:     q.Head,
            Tail:     q.Tail,
            Elements: q.Arr,
        }
    }

    for name, ht := range s.HashTables {
        jsonStorage.HashTables[name] = ht.GetAllElements()
    }

    for name, arr := range s.Arrays {
        jsonStorage.Arrays[name] = arr.Arr[:arr.Length]
    }

    for name, t := range s.Trees {
        jsonStorage.Trees[name] = t.Serialize()
    }

    data, err := json.MarshalIndent(jsonStorage, "", "  ")
    if err != nil {
        return err
    }

    return os.WriteFile(filename, data, 0644)
}

func (s *Storage) LoadFromFile(filename string) error {
    data, err := os.ReadFile(filename)
    if err != nil {
        return err
    }

    var jsonStorage JSONStorage
    if err := json.Unmarshal(data, &jsonStorage); err != nil {
        return err
    }

    for name, j := range jsonStorage.SinglyLists {
        list := singlylist.NewForwardList()
        for _, el := range j.Elements {
            list.AddTail(el)
        }
        s.SinglyLists[name] = list
    }

    for name, j := range jsonStorage.DoubleLists {
        list := doublelist.NewDoubleList()
        for _, el := range j.Elements {
            list.AddTail(el)
        }
        s.DoubleLists[name] = list
    }

    for name, j := range jsonStorage.Stacks {
        st := stack.NewStack(j.Length)
        for _, el := range j.Elements {
            st.Push(el)
        }
        s.Stacks[name] = st
    }

    for name, j := range jsonStorage.Queues {
        q := queue.NewQueue(j.Length)
        q.Head = j.Head
        q.Tail = j.Tail
        copy(q.Arr, j.Elements)
        s.Queues[name] = q
    }

    for name, arr := range jsonStorage.HashTables {
        ht := hashtable.NewHashTable(10)
        for _, e := range arr {
            ht.Insert(e.Key, e.Value)
        }
        s.HashTables[name] = ht
    }

    for name, elems := range jsonStorage.Arrays {
        a := array.NewArray(len(elems))
        for i, v := range elems {
            a.AddByIndex(i, v)
        }
        s.Arrays[name] = a
    }

    for name, elems := range jsonStorage.Trees {
        t := tree.NewTree()
        for _, v := range elems {
            t.Insert(v)
        }
        s.Trees[name] = t
    }

    return nil
}

func (s *Storage) SaveBinary(filename string) error {
    f, err := os.Create(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    enc := gob.NewEncoder(f)
    return enc.Encode(s)
}

func (s *Storage) LoadBinary(filename string) error {
    f, err := os.Open(filename)
    if err != nil {
        return err
    }
    defer f.Close()

    dec := gob.NewDecoder(f)
    return dec.Decode(s)
}
