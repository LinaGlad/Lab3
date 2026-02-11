package stack_test

import (
    "dbms-go/stack"
    "os"
    "testing"
)

func TestStack(t *testing.T) {
    s := stack.NewStack(5)

    s.Push("A")
    s.Push("B")

    if s.Pop() != "B" {
        t.Fatalf("Pop failed")
    }

    if s.Pop() != "A" {
        t.Fatalf("Pop failed")
    }
}

func TestStackOverflow(t *testing.T) {
    s := stack.NewStack(1)
    s.Push("A")
    res := s.Push("B")
    if res != "" {
        t.Fatalf("Expected overflow empty string")
    }
}

func TestStackUnderflow(t *testing.T) {
    s := stack.NewStack(1)
    res := s.Pop()
    if res != "" {
        t.Fatalf("Expected empty pop on underflow")
    }
}

func TestStackDisplay(t *testing.T) {
    s := stack.NewStack(5)
    s.Display()
    s.Push("A")
    s.Push("B")
    s.Push("C")
    s.Display()
}

func TestStack_JSONSerialization(t *testing.T) {
    s := stack.NewStack(5)
    s.Push("A")
    s.Push("B")
    s.Push("C")

    err := s.SaveToFile("test_stack.json")
    if err != nil {
        t.Fatalf("SaveToFile failed: %v", err)
    }

    restored := stack.NewStack(1)
    err = restored.LoadFromFile("test_stack.json")
    if err != nil {
        t.Fatalf("LoadFromFile failed: %v", err)
    }

    expected := []string{"C", "B", "A"}
    for i := 0; i < 3; i++ {
        val := restored.Pop()
        if val != expected[i] {
            t.Fatalf("Mismatch at pop %d: expected %s, got %s", i, expected[i], val)
        }
    }

    os.Remove("test_stack.json")
}

func TestStack_BinarySerialization(t *testing.T) {
    s := stack.NewStack(4)
    s.Push("X")
    s.Push("Y")
    s.Push("Z")

    err := s.SaveBinary("test_stack.gob")
    if err != nil {
        t.Fatalf("SaveBinary failed: %v", err)
    }

    restored := stack.NewStack(1)
    err = restored.LoadBinary("test_stack.gob")
    if err != nil {
        t.Fatalf("LoadBinary failed: %v", err)
    }

    expected := []string{"Z", "Y", "X"}
    for i := 0; i < 3; i++ {
        val := restored.Pop()
        if val != expected[i] {
            t.Fatalf("Mismatch at pop %d: expected %s, got %s", i, expected[i], val)
        }
    }

    os.Remove("test_stack.gob")
}
