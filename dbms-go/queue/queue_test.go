package queue_test

import (
    "dbms-go/queue"
    "os"
    "testing"
)

func TestQueue(t *testing.T) {
    q := queue.NewQueue(5)

    q.Push("A")
    q.Push("B")

    if q.Pop() != "A" {
        t.Fatalf("Pop failed")
    }
}

func TestQueueOverflow(t *testing.T) {
    q := queue.NewQueue(1)
    q.Push("A")
    res := q.Push("B")
    if res != "" {
        t.Fatalf("Expected overflow empty string")
    }
}

func TestQueueUnderflow(t *testing.T) {
    q := queue.NewQueue(1)
    res := q.Pop()
    if res != "" {
        t.Fatalf("Expected empty pop on underflow")
    }
}

func TestQueueDisplay(t *testing.T) {
    q := queue.NewQueue(5)
    q.Display()    
    q.Push("A")
    q.Push("B")
    q.Push("C")
    q.Display()
}

func TestQueueWrapAround(t *testing.T) {
    q := queue.NewQueue(3)
    q.Push("A")
    q.Push("B")
    q.Pop()
    q.Push("C")
    q.Push("D") 
    q.Display()
}

func TestQueue_JSONSerialization(t *testing.T) {
    q := queue.NewQueue(5)
    q.Push("A")
    q.Push("B")
    q.Push("C")

    err := q.SaveToFile("test_queue.json")
    if err != nil {
        t.Fatalf("SaveToFile failed: %v", err)
    }

    restored := queue.NewQueue(1)
    err = restored.LoadFromFile("test_queue.json")
    if err != nil {
        t.Fatalf("LoadFromFile failed: %v", err)
    }

    got := []string{restored.Pop(), restored.Pop(), restored.Pop()}
    want := []string{"A", "B", "C"}

    for i := range want {
        if got[i] != want[i] {
            t.Fatalf("Mismatch at %d: expected %s, got %s", i, want[i], got[i])
        }
    }

    os.Remove("test_queue.json")
}

func TestQueue_BinarySerialization(t *testing.T) {
    q := queue.NewQueue(4)
    q.Push("X")
    q.Push("Y")
    q.Push("Z")

    err := q.SaveBinary("test_queue.gob")
    if err != nil {
        t.Fatalf("SaveBinary failed: %v", err)
    }

    restored := queue.NewQueue(1)
    err = restored.LoadBinary("test_queue.gob")
    if err != nil {
        t.Fatalf("LoadBinary failed: %v", err)
    }

    got := []string{restored.Pop(), restored.Pop(), restored.Pop()}
    want := []string{"X", "Y", "Z"}

    for i := range want {
        if got[i] != want[i] {
            t.Fatalf("Mismatch at %d: expected %s, got %s", i, want[i], got[i])
        }
    }

    os.Remove("test_queue.gob")
}
