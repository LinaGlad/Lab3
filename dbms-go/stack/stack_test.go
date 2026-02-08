package stack_test

import (
    "dbms-go/stack"
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
    s.Push("A")
    s.Push("B")
    s.Push("C")
    s.Display()
}
