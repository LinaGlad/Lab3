package queue_test

import (
    "dbms-go/queue"
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
