package hashtable

import (
    "fmt"
)

type EntryState int

const (
    EMPTY EntryState = iota
    OCCUPIED
    DELETED
)

type Entry struct {
    Key   string
    Value int
    State EntryState
}

type HashTable struct {
    Table    []Entry
    Capacity int
    Size     int
}

const DEFAULT_CAPACITY = 10

func NewHashTable(cap int) *HashTable {
    if cap <= 0 {
        cap = DEFAULT_CAPACITY
    }

    t := &HashTable{
        Table:    make([]Entry, cap),
        Capacity: cap,
        Size:     0,
    }

    for i := range t.Table {
        t.Table[i].State = EMPTY
    }

    return t
}

func hashFunction(key string, cap int) int {
    hash := 0
    for _, c := range key {
        hash = hash*31 + int(c)
    }
    return hash % cap
}

func (h *HashTable) Insert(key string, value int) bool {
    if h.Size >= h.Capacity {
        return false
    }

    index := hashFunction(key, h.Capacity)
    attempt := 0

    for attempt < h.Capacity {
        current := (index + attempt) % h.Capacity

        if h.Table[current].State == EMPTY || h.Table[current].State == DELETED {
            h.Table[current].Key = key
            h.Table[current].Value = value
            h.Table[current].State = OCCUPIED
            h.Size++
            return true
        }

        if h.Table[current].State == OCCUPIED && h.Table[current].Key == key {
            h.Table[current].Value = value
            return true
        }

        attempt++
    }

    return false
}

func (h *HashTable) Find(key string) (int, bool) {
    index := hashFunction(key, h.Capacity)
    attempt := 0

    for attempt < h.Capacity {
        current := (index + attempt) % h.Capacity

        if h.Table[current].State == EMPTY {
            return 0, false
        }

        if h.Table[current].State == OCCUPIED && h.Table[current].Key == key {
            return h.Table[current].Value, true
        }

        attempt++
    }

    return 0, false
}

func (h *HashTable) Remove(key string) bool {
    index := hashFunction(key, h.Capacity)
    attempt := 0

    for attempt < h.Capacity {
        current := (index + attempt) % h.Capacity

        if h.Table[current].State == EMPTY {
            return false
        }

        if h.Table[current].State == OCCUPIED && h.Table[current].Key == key {
            h.Table[current].State = DELETED
            h.Size--
            return true
        }

        attempt++
    }

    return false
}

func (h *HashTable) Contains(key string) bool {
    _, ok := h.Find(key)
    return ok
}

func (h *HashTable) PrintAll() {
    hasElements := false

    for _, e := range h.Table {
        if e.State == OCCUPIED {
            fmt.Printf("%d ", e.Value)
            hasElements = true
        }
    }

    if !hasElements {
        fmt.Println("Hash Table is empty")
    } else {
        fmt.Println()
    }
}

func (h *HashTable) GetAllElements() []struct {
    Key   string
    Value int
} {
    result := []struct {
        Key   string
        Value int
    }{}

    for _, e := range h.Table {
        if e.State == OCCUPIED {
            result = append(result, struct {
                Key   string
                Value int
            }{e.Key, e.Value})
        }
    }

    return result
}


