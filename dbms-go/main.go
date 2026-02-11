package main

import (
    "dbms-go/array"
    "dbms-go/doublelist"
    "dbms-go/hashtable"
    "dbms-go/queue"
    "dbms-go/singlylist"
    "dbms-go/stack"
    "dbms-go/storage"
    "dbms-go/tree"
    "dbms-go/utils"
    "fmt"
    "os"
    "strconv"
    "strings"
)

func printUsage() {
    fmt.Println("Usage: ./dbms --file <filename> --query '<command>'")
    fmt.Println()
    fmt.Println("Universal Commands:")
    fmt.Println("  PRINT <name>")
    fmt.Println()
    fmt.Println("Array Commands (M):")
    fmt.Println("  MCREATE <array> <length>")
    fmt.Println("  MPUSH_BY_INDEX <array> <index> <value>")
    fmt.Println("  MPUSH_END <array> <value>")
    fmt.Println("  MGET_BY_INDEX <array> <index>")
    fmt.Println("  MGET <array>")
    fmt.Println("  MDEL_BY_INDEX <array> <index>")
    fmt.Println("  MREPLACE <array> <index> <value>")
    fmt.Println("  MLENGTH <array>")
    fmt.Println()
    fmt.Println("Singly List Commands (F):")
    fmt.Println("  FPUSH_BEFORE <list> <target> <value>")
    fmt.Println("  FPUSH_AFTER <list> <target> <value>")
    fmt.Println("  FPUSH_HEAD <list> <value>")
    fmt.Println("  FPUSH_TAIL <list> <value>")
    fmt.Println("  FDEL_BEFORE <list> <target>")
    fmt.Println("  FDEL_AFTER <list> <target>")
    fmt.Println("  FDEL_HEAD <list>")
    fmt.Println("  FDEL_TAIL <list>")
    fmt.Println("  FDEL_BY_VALUE <list> <value>")
    fmt.Println("  FGET <list>")
    fmt.Println("  FSEARCH <list> <value>")
    fmt.Println()
    fmt.Println("Double List Commands (L):")
    fmt.Println("  LPUSH_BEFORE <list> <target> <value>")
    fmt.Println("  LPUSH_AFTER <list> <target> <value>")
    fmt.Println("  LPUSH_HEAD <list> <value>")
    fmt.Println("  LPUSH_TAIL <list> <value>")
    fmt.Println("  LDEL_BEFORE <list> <target>")
    fmt.Println("  LDEL_AFTER <list> <target>")
    fmt.Println("  LDEL_HEAD <list>")
    fmt.Println("  LDEL_TAIL <list>")
    fmt.Println("  LDEL_BY_VALUE <list> <value>")
    fmt.Println("  LGET <list>")
    fmt.Println("  LSEARCH <list> <value>")
    fmt.Println()
    fmt.Println("Stack Commands (S):")
    fmt.Println("  SPUSH <stack> <value>")
    fmt.Println("  SPOP <stack>")
    fmt.Println("  SGET <stack>")
    fmt.Println()
    fmt.Println("Queue Commands (Q):")
    fmt.Println("  QPUSH <queue> <value>")
    fmt.Println("  QPOP <queue>")
    fmt.Println("  QGET <queue>")
    fmt.Println()
    fmt.Println("Tree Commands (T):")
    fmt.Println("  TINSERT <tree> <value>")
    fmt.Println("  TGET <tree>")
    fmt.Println("  TSEARCH <tree> <value>")
    fmt.Println("  TISFULL <tree>")
    fmt.Println()
    fmt.Println("HashTable Commands (H):")
    fmt.Println("  HINSERT <table> <key> <value>")
    fmt.Println("  HGET <table>")
    fmt.Println("  HSEARCH <table> <key>")
    fmt.Println("  HREMOVE <table> <key>")
}

func processPrintCommand(tokens []string, s *storage.Storage) {
    if len(tokens) != 2 {
        fmt.Println("Invalid PRINT command! Usage: PRINT <name>")
        return
    }

    name := tokens[1]

    if arr, ok := s.Arrays[name]; ok {
        arr.DisplayAll()
        return
    }

    if list, ok := s.SinglyLists[name]; ok {
        list.Display()
        return
    }

    if list, ok := s.DoubleLists[name]; ok {
        list.Display()
        return
    }

    if st, ok := s.Stacks[name]; ok {
        st.Display()
        return
    }

    if q, ok := s.Queues[name]; ok {
        q.Display()
        return
    }

    if t, ok := s.Trees[name]; ok {
        fmt.Print("Inorder recursive: ")
        t.PrintInOrder()
        fmt.Print("Inorder iterative: ")
        t.PrintInOrderIterative()
        fmt.Print("Preorder: ")
        t.PrintPreOrder()
        fmt.Print("Postorder: ")
        t.PrintPostOrder()
        fmt.Print("Level order: ")
        t.PrintLevelOrder()
        return
    }

    if h, ok := s.HashTables[name]; ok {
        h.PrintAll()
        return
    }

    fmt.Printf("Structure '%s' not found!\n", name)
}

func processArrayCommand(tokens []string, s *storage.Storage, filename string) {
    switch tokens[0] {
    case "MCREATE":
        name := tokens[1]
        length, _ := strconv.Atoi(tokens[2])
        s.Arrays[name] = array.NewArray(length)
        s.SaveToFile(filename)
        fmt.Println("OK")

    case "MPUSH_BY_INDEX":
        name := tokens[1]
        index, _ := strconv.Atoi(tokens[2])
        value := tokens[3]
        fmt.Println(s.Arrays[name].AddByIndex(index, value))
        s.SaveToFile(filename)

    case "MPUSH_END":
        name := tokens[1]
        value := tokens[2]
        fmt.Println(s.Arrays[name].AddToEnd(value))
        s.SaveToFile(filename)

    case "MGET_BY_INDEX":
        name := tokens[1]
        index, _ := strconv.Atoi(tokens[2])
        s.Arrays[name].GetByIndex(index)

    case "MGET":
        s.Arrays[tokens[1]].DisplayAll()

    case "MDEL_BY_INDEX":
        name := tokens[1]
        index, _ := strconv.Atoi(tokens[2])
        fmt.Println(s.Arrays[name].DeleteByIndex(index))
        s.SaveToFile(filename)

    case "MREPLACE":
        name := tokens[1]
        index, _ := strconv.Atoi(tokens[2])
        value := tokens[3]
        fmt.Println(s.Arrays[name].ReplaceByIndex(index, value))
        s.SaveToFile(filename)

    case "MLENGTH":
        s.Arrays[tokens[1]].GetLength()
    }
}

func processSinglyListCommand(tokens []string, s *storage.Storage, filename string) {
    get := func(name string) *singlylist.ForwardList {
        if l, ok := s.SinglyLists[name]; ok {
            return l
        }
        s.SinglyLists[name] = singlylist.NewForwardList()
        return s.SinglyLists[name]
    }

    switch tokens[0] {
    case "FPUSH_BEFORE":
        list := get(tokens[1])
        list.AddBefore(tokens[3], tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[3])

    case "FPUSH_AFTER":
        list := get(tokens[1])
        list.AddAfterValue(tokens[3], tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[3])

    case "FPUSH_HEAD":
        list := get(tokens[1])
        list.AddHead(tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[2])

    case "FPUSH_TAIL":
        list := get(tokens[1])
        list.AddTail(tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[2])

    case "FDEL_BEFORE":
        list := get(tokens[1])
        fmt.Println(list.DeleteBefore(tokens[2]))
        s.SaveToFile(filename)

    case "FDEL_AFTER":
        list := get(tokens[1])
        fmt.Println(list.DeleteAfterValue(tokens[2]))
        s.SaveToFile(filename)

    case "FDEL_HEAD":
        list := get(tokens[1])
        fmt.Println(list.DeleteHead())
        s.SaveToFile(filename)

    case "FDEL_TAIL":
        list := get(tokens[1])
        fmt.Println(list.DeleteTail())
        s.SaveToFile(filename)

    case "FDEL_BY_VALUE":
        list := get(tokens[1])
        fmt.Println(list.DeleteByValue(tokens[2]))
        s.SaveToFile(filename)

    case "FGET":
        s.SinglyLists[tokens[1]].Display()

    case "FSEARCH":
        if s.SinglyLists[tokens[1]].Contains(tokens[2]) {
            fmt.Println("TRUE")
        } else {
            fmt.Println("FALSE")
        }
    }
}

func processDoubleListCommand(tokens []string, s *storage.Storage, filename string) {
    get := func(name string) *doublelist.DoubleList {
        if l, ok := s.DoubleLists[name]; ok {
            return l
        }
        s.DoubleLists[name] = doublelist.NewDoubleList()
        return s.DoubleLists[name]
    }

    switch tokens[0] {
    case "LPUSH_BEFORE":
        list := get(tokens[1])
        list.AddBeforeValue(tokens[3], tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[3])

    case "LPUSH_AFTER":
        list := get(tokens[1])
        list.AddAfterValue(tokens[3], tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[3])

    case "LPUSH_HEAD":
        list := get(tokens[1])
        list.AddHead(tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[2])

    case "LPUSH_TAIL":
        list := get(tokens[1])
        list.AddTail(tokens[2])
        s.SaveToFile(filename)
        fmt.Println(tokens[2])

    case "LDEL_BEFORE":
        list := get(tokens[1])
        fmt.Println(list.DeleteBeforeValue(tokens[2]))
        s.SaveToFile(filename)

    case "LDEL_AFTER":
        list := get(tokens[1])
        fmt.Println(list.DeleteAfterValue(tokens[2]))
        s.SaveToFile(filename)

    case "LDEL_HEAD":
        list := get(tokens[1])
        fmt.Println(list.DeleteHead())
        s.SaveToFile(filename)

    case "LDEL_TAIL":
        list := get(tokens[1])
        fmt.Println(list.DeleteTail())
        s.SaveToFile(filename)

    case "LDEL_BY_VALUE":
        list := get(tokens[1])
        fmt.Println(list.DeleteByValue(tokens[2]))
        s.SaveToFile(filename)

    case "LGET":
        s.DoubleLists[tokens[1]].Display()

    case "LSEARCH":
        if s.DoubleLists[tokens[1]].Contains(tokens[2]) {
            fmt.Println("TRUE")
        } else {
            fmt.Println("FALSE")
        }
    }
}

func processStackCommand(tokens []string, s *storage.Storage, filename string) {
    get := func(name string) *stack.Stack {
        if st, ok := s.Stacks[name]; ok {
            return st
        }
        s.Stacks[name] = stack.NewStack(100)
        return s.Stacks[name]
    }

    switch tokens[0] {
    case "SPUSH":
        st := get(tokens[1])
        fmt.Println(st.Push(tokens[2]))
        s.SaveToFile(filename)

    case "SPOP":
        if st, ok := s.Stacks[tokens[1]]; ok {
            fmt.Println(st.Pop())
            s.SaveToFile(filename)
        }

    case "SGET":
        if st, ok := s.Stacks[tokens[1]]; ok {
            st.Display()
        }
    }
}

func processQueueCommand(tokens []string, s *storage.Storage, filename string) {
    get := func(name string) *queue.Queue {
        if q, ok := s.Queues[name]; ok {
            return q
        }
        s.Queues[name] = queue.NewQueue(100)
        return s.Queues[name]
    }

    switch tokens[0] {
    case "QPUSH":
        q := get(tokens[1])
        fmt.Println(q.Push(tokens[2]))
        s.SaveToFile(filename)

    case "QPOP":
        if q, ok := s.Queues[tokens[1]]; ok {
            fmt.Println(q.Pop())
            s.SaveToFile(filename)
        }

    case "QGET":
        if q, ok := s.Queues[tokens[1]]; ok {
            q.Display()
        }
    }
}

func processTreeCommand(tokens []string, s *storage.Storage, filename string) {
    get := func(name string) *tree.Tree {
        if t, ok := s.Trees[name]; ok {
            return t
        }
        s.Trees[name] = tree.NewTree()
        return s.Trees[name]
    }

    switch tokens[0] {
    case "TINSERT":
        t := get(tokens[1])
        value, _ := strconv.Atoi(tokens[2])
        if t.Insert(value) {
            fmt.Println(value)
            s.SaveToFile(filename)
        } else {
            fmt.Println("Value already exists")
        }

    case "TGET":
        if t, ok := s.Trees[tokens[1]]; ok {
            fmt.Print("Inorder recursive: ")
            t.PrintInOrder()
            fmt.Print("Inorder iterative: ")
            t.PrintInOrderIterative()
            fmt.Print("Preorder: ")
            t.PrintPreOrder()
            fmt.Print("Postorder: ")
            t.PrintPostOrder()
            fmt.Print("Level order: ")
            t.PrintLevelOrder()
        }

    case "TSEARCH":
        if t, ok := s.Trees[tokens[1]]; ok {
            value, _ := strconv.Atoi(tokens[2])
            if t.Search(value) {
                fmt.Println("TRUE")
            } else {
                fmt.Println("FALSE")
            }
        }

    case "TISFULL":
        if t, ok := s.Trees[tokens[1]]; ok {
            if t.IsFull() {
                fmt.Println("TRUE")
            } else {
                fmt.Println("FALSE")
            }
        }
    }
}

func processHashTableCommand(tokens []string, s *storage.Storage, filename string) {
    get := func(name string) *hashtable.HashTable {
        if h, ok := s.HashTables[name]; ok {
            return h
        }
        s.HashTables[name] = hashtable.NewHashTable(10)
        return s.HashTables[name]
    }

    switch tokens[0] {
    case "HINSERT":
        h := get(tokens[1])
        key := tokens[2]
        value, _ := strconv.Atoi(tokens[3])
        if h.Insert(key, value) {
            fmt.Println(value)
            s.SaveToFile(filename)
        }

    case "HGET":
        if h, ok := s.HashTables[tokens[1]]; ok {
            h.PrintAll()
        }

    case "HSEARCH":
        if h, ok := s.HashTables[tokens[1]]; ok {
            if h.Contains(tokens[2]) {
                fmt.Println("TRUE")
            } else {
                fmt.Println("FALSE")
            }
        }

    case "HREMOVE":
        if h, ok := s.HashTables[tokens[1]]; ok {
            if h.Remove(tokens[2]) {
                fmt.Println(tokens[2])
                s.SaveToFile(filename)
            } else {
                fmt.Println("Key not found")
            }
        }
    }
}

func main() {
    if len(os.Args) != 5 || os.Args[1] != "--file" || os.Args[3] != "--query" {
        printUsage()
        return
    }

    filename := os.Args[2]
    query := os.Args[4]

    s := storage.NewStorage()
    s.LoadFromFile(filename)

    tokens := utils.SplitQuery(query)
    if len(tokens) == 0 {
        fmt.Println("Empty command")
        return
    }

    cmd := tokens[0]

    switch {
    case cmd == "PRINT":
        processPrintCommand(tokens, s)

    case strings.HasPrefix(cmd, "M"):
        processArrayCommand(tokens, s, filename)

    case strings.HasPrefix(cmd, "F"):
        processSinglyListCommand(tokens, s, filename)

    case strings.HasPrefix(cmd, "L"):
        processDoubleListCommand(tokens, s, filename)

    case strings.HasPrefix(cmd, "S"):
        processStackCommand(tokens, s, filename)

    case strings.HasPrefix(cmd, "Q"):
        processQueueCommand(tokens, s, filename)

    case strings.HasPrefix(cmd, "T"):
        processTreeCommand(tokens, s, filename)

    case strings.HasPrefix(cmd, "H"):
        processHashTableCommand(tokens, s, filename)

    default:
        fmt.Println("Unknown command type!")
        printUsage()
    }
}

    