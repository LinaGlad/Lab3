package hashtable_test

import (
    "dbms-go/hashtable"
    "os"
    "testing"
)

func TestHashTableBasic(t *testing.T) {
    h := hashtable.NewHashTable(10)

    h.Insert("a", 1)
    h.Insert("b", 2)

    if !h.Contains("a") {
        t.Fatalf("Contains failed")
    }

    if !h.Remove("a") {
        t.Fatalf("Remove failed")
    }

    if h.Contains("a") {
        t.Fatalf("Expected a to be removed")
    }
}

func TestHashTableInsertDuplicate(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.Insert("a", 1)
    ok := h.Insert("a", 2) 
    if !ok {
        t.Fatalf("Expected true on duplicate insert (overwrite)")
    }

    val, found := h.Find("a")
    if !found || val != 2 {
        t.Fatalf("Expected updated value 2, got %d", val)
    }
}

func TestHashTableRemoveMissing(t *testing.T) {
    h := hashtable.NewHashTable(10)
    ok := h.Remove("zzz")
    if ok {
        t.Fatalf("Expected false on missing remove")
    }
}

func TestHashTablePrintAll(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.PrintAll() 

    h.Insert("a", 1)
    h.Insert("b", 2)
    h.PrintAll() 
}

func TestHashTableSearchMissing(t *testing.T) {
    h := hashtable.NewHashTable(10)
    if h.Contains("zzz") {
        t.Fatalf("Expected false")
    }
}

func TestHashTableGetAllElements(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.Insert("x", 100)
    h.Insert("y", 200)

    elems := h.GetAllElements()
    if len(elems) != 2 {
        t.Fatalf("Expected 2 elements")
    }

    found := false
    for _, e := range elems {
        if e.Key == "x" && e.Value == 100 {
            found = true
        }
    }
    if !found {
        t.Fatalf("Expected to find key x with value 100")
    }
}

func TestHashTableSizeAndCapacity(t *testing.T) {
    h := hashtable.NewHashTable(5)
    if h.Capacity != 5 {
        t.Fatalf("Expected capacity 5")
    }

    h.Insert("a", 1)
    h.Insert("b", 2)

    if h.Size != 2 {
        t.Fatalf("Expected size 2")
    }
}

func TestHashTable_JSONSerialization(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.Insert("a", 1)
    h.Insert("b", 2)
    h.Insert("c", 3)

    err := h.SaveToFile("test_ht.json")
    if err != nil {
        t.Fatalf("SaveToFile failed: %v", err)
    }

    restored := hashtable.NewHashTable(1)
    err = restored.LoadFromFile("test_ht.json")
    if err != nil {
        t.Fatalf("LoadFromFile failed: %v", err)
    }

    expected := map[string]int{"a": 1, "b": 2, "c": 3}
    for k, v := range expected {
        val, ok := restored.Find(k)
        if !ok || val != v {
            t.Fatalf("Expected %s → %d, got %d (ok=%v)", k, v, val, ok)
        }
    }

    os.Remove("test_ht.json")
}

func TestHashTable_BinarySerialization(t *testing.T) {
    h := hashtable.NewHashTable(10)
    h.Insert("x", 10)
    h.Insert("y", 20)
    h.Insert("z", 30)

    err := h.SaveBinary("test_ht.gob")
    if err != nil {
        t.Fatalf("SaveBinary failed: %v", err)
    }

    restored := hashtable.NewHashTable(1)
    err = restored.LoadBinary("test_ht.gob")
    if err != nil {
        t.Fatalf("LoadBinary failed: %v", err)
    }

    expected := map[string]int{"x": 10, "y": 20, "z": 30}
    for k, v := range expected {
        val, ok := restored.Find(k)
        if !ok || val != v {
            t.Fatalf("Expected %s → %d, got %d (ok=%v)", k, v, val, ok)
        }
    }

    os.Remove("test_ht.gob")
}
