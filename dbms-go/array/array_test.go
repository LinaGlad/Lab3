package array_test

import (
    "dbms-go/array"
    "testing"
)

func TestArrayOperations(t *testing.T) {
    a := array.NewArray(5)

    if a.AddToEnd("A") != "A" {
        t.Fatalf("AddToEnd failed")
    }

    if a.AddByIndex(0, "B") != "B" {
        t.Fatalf("AddByIndex failed")
    }

    if a.Size != 2 {
        t.Fatalf("Expected size 2, got %d", a.Size)
    }

    a.ReplaceByIndex(1, "C")
    if a.Arr[1] != "C" {
        t.Fatalf("ReplaceByIndex failed")
    }

    if a.DeleteByIndex(0) != "B" {
        t.Fatalf("DeleteByIndex failed")
    }
}

func TestArrayInvalidAddByIndex(t *testing.T) {
    a := array.NewArray(3)
    res := a.AddByIndex(5, "X")
    if res != "Invalid index!" {
        t.Fatalf("Expected invalid index")
    }
}

func TestArrayFullAdd(t *testing.T) {
    a := array.NewArray(1)
    a.AddToEnd("A")
    res := a.AddToEnd("B")
    if res != "Array is full!" {
        t.Fatalf("Expected full array error")
    }
}

func TestArrayInvalidGet(t *testing.T) {
    a := array.NewArray(2)
    a.AddToEnd("A")
    a.GetByIndex(5)
}

func TestArrayInvalidDelete(t *testing.T) {
    a := array.NewArray(2)
    res := a.DeleteByIndex(5)
    if res != "" {
        t.Fatalf("Expected empty result on invalid delete")
    }
}

func TestArrayDisplayAll(t *testing.T) {
    a := array.NewArray(5)
    a.AddToEnd("A")
    a.AddToEnd("B")
    a.DisplayAll()
}

func TestArrayGetLength(t *testing.T) {
    a := array.NewArray(5)
    a.AddToEnd("A")
    a.GetLength()
}

func TestArrayReplaceInvalid(t *testing.T) {
    a := array.NewArray(2)
    res := a.ReplaceByIndex(5, "X")
    if res != "Invalid index!" {
        t.Fatalf("Expected invalid index")
    }
}
