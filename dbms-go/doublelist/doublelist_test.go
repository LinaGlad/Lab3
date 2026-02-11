package doublelist_test

import (
    "dbms-go/doublelist"
    "os"
    "testing"
)

func TestDoubleListBasicOperations(t *testing.T) {
    l := doublelist.NewDoubleList()

    l.AddHead("A")
    l.AddTail("B")
    l.AddAfterValue("C", "A")

    if !l.Contains("C") {
        t.Fatalf("Expected C in list")
    }

    if l.DeleteBeforeValue("C") != "A" {
        t.Fatalf("DeleteBeforeValue failed")
    }

    if l.DeleteByValue("C") != "C" {
        t.Fatalf("DeleteByValue failed")
    }
}

func TestDoubleListDeleteBeforeEdge(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddHead("A")
    res := l.DeleteBeforeValue("A")
    if res != "" {
        t.Fatalf("Expected empty delete-before on head")
    }
}

func TestDoubleListDeleteAfterEdge(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddHead("A")
    res := l.DeleteAfterValue("A")
    if res != "" {
        t.Fatalf("Expected empty delete-after on tail")
    }
}

func TestDoubleListAddBeforeNotFound(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddHead("A")
    l.AddBeforeValue("X", "Z") 
}

func TestDoubleListAddAfterNotFound(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddHead("A")
    l.AddAfterValue("X", "Z")
}

func TestDoubleListDisplay(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")
    l.AddTail("C")
    l.Display() 
}

func TestDoubleListFindByValue(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    _, pos := l.FindByValue("B")
    if pos != 1 {
        t.Fatalf("Wrong position")
    }

    _, pos2 := l.FindByValue("Z")
    if pos2 != -1 {
        t.Fatalf("Expected -1")
    }
}

func TestDoubleListDeleteAfterMissing(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    res := l.DeleteAfterValue("A")
    if res != "" {
        t.Fatalf("Expected empty")
    }
}

func TestDoubleListAddBeforeHead(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("B")

    ptr, _ := l.FindByValue("B")
    l.AddBefore(ptr, "A")

    if l.Head.Key != "A" {
        t.Fatalf("AddBefore on head failed")
    }
    if l.Head.Next.Key != "B" {
        t.Fatalf("List structure broken after AddBefore")
    }
}

func TestDoubleListAddBeforeMiddle(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("C")

    ptr, _ := l.FindByValue("C")
    l.AddBefore(ptr, "B")

    if l.Head.Next.Key != "B" {
        t.Fatalf("AddBefore in middle failed")
    }
}

func TestDoubleListDeleteNodeHead(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    deleted := l.DeleteNode(l.Head)
    if deleted != "A" {
        t.Fatalf("DeleteNode(head) returned wrong value")
    }
    if l.Head.Key != "B" {
        t.Fatalf("Head not updated after DeleteNode")
    }
}

func TestDoubleListDeleteNodeTail(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    deleted := l.DeleteNode(l.Tail)
    if deleted != "B" {
        t.Fatalf("DeleteNode(tail) returned wrong value")
    }
    if l.Tail.Key != "A" {
        t.Fatalf("Tail not updated after DeleteNode")
    }
}

func TestDoubleListDeleteHead(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    deleted := l.DeleteHead()
    if deleted != "A" {
        t.Fatalf("DeleteHead returned wrong value")
    }
    if l.Head.Key != "B" {
        t.Fatalf("Head not updated after DeleteHead")
    }
}

func TestDoubleListDeleteTail(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    deleted := l.DeleteTail()
    if deleted != "B" {
        t.Fatalf("DeleteTail returned wrong value")
    }
    if l.Tail.Key != "A" {
        t.Fatalf("Tail not updated after DeleteTail")
    }
}

func TestDoubleListDeleteAfterValueMiddle(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")
    l.AddTail("C")

    deleted := l.DeleteAfterValue("A")
    if deleted != "B" {
        t.Fatalf("DeleteAfterValue failed, expected B")
    }

    if l.Head.Next.Key != "C" {
        t.Fatalf("List structure broken after DeleteAfterValue")
    }
}

func TestDoubleListDeleteBeforeValue_NotFound(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    res := l.DeleteBeforeValue("Z") 
    if res != "" {
        t.Fatalf("Expected empty string when element not found")
    }
}

func TestDoubleListDeleteAfterValue_NotFound(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    res := l.DeleteAfterValue("Z") 
    if res != "" {
        t.Fatalf("Expected empty string when element not found")
    }
}

func TestDoubleListDeleteByValue_NotFound(t *testing.T) {
    l := doublelist.NewDoubleList()
    l.AddTail("A")
    l.AddTail("B")

    res := l.DeleteByValue("Z") 
    if res != "" {
        t.Fatalf("Expected empty string when element not found")
    }
}

func TestDoubleList_SaveAndLoad_JSON(t *testing.T) {
    list := doublelist.NewDoubleList()
    list.AddTail("alpha")
    list.AddTail("beta")
    list.AddTail("gamma")

    err := list.SaveToFile("test_dl.json")
    if err != nil {
        t.Fatalf("SaveToFile failed: %v", err)
    }

    restored := doublelist.NewDoubleList()
    err = restored.LoadFromFile("test_dl.json")
    if err != nil {
        t.Fatalf("LoadFromFile failed: %v", err)
    }

    expected := []string{"alpha", "beta", "gamma"}
    cur := restored.Head
    for i, want := range expected {
        if cur == nil || cur.Key != want {
            t.Fatalf("JSON mismatch at %d: expected %s, got %v", i, want, cur)
        }
        cur = cur.Next
    }

    os.Remove("test_dl.json")
}

func TestDoubleList_SaveAndLoad_Binary(t *testing.T) {
    list := doublelist.NewDoubleList()
    list.AddTail("red")
    list.AddTail("green")
    list.AddTail("blue")

    err := list.SaveBinary("test_dl.gob")
    if err != nil {
        t.Fatalf("SaveBinary failed: %v", err)
    }

    restored := doublelist.NewDoubleList()
    err = restored.LoadBinary("test_dl.gob")
    if err != nil {
        t.Fatalf("LoadBinary failed: %v", err)
    }

    expected := []string{"red", "green", "blue"}
    cur := restored.Head
    for i, want := range expected {
        if cur == nil || cur.Key != want {
            t.Fatalf("GOB mismatch at %d: expected %s, got %v", i, want, cur)
        }
        cur = cur.Next
    }

    os.Remove("test_dl.gob")
}
