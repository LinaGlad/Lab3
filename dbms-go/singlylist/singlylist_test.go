package singlylist_test

import (
    "dbms-go/singlylist"
    "testing"
)

func TestSinglyListDeleteHead(t *testing.T) {
    l := singlylist.NewForwardList()

    if l.DeleteHead() != "" {
        t.Fatalf("Expected empty on empty list")
    }

    l.AddHead("A")
    if l.DeleteHead() != "A" {
        t.Fatalf("DeleteHead failed on single element")
    }

    l.AddTail("A")
    l.AddTail("B")
    if l.DeleteHead() != "A" {
        t.Fatalf("DeleteHead failed on multi-element list")
    }
}

func TestSinglyListAddBefore(t *testing.T) {
    l := singlylist.NewForwardList()

    l.AddBefore("X", "Z")

    l.AddTail("A")
    l.AddBefore("X", "A")
    if l.Head.Key != "X" {
        t.Fatalf("AddBefore failed at pos==0")
    }

    l.AddTail("B")
    l.AddTail("C")
    l.AddBefore("Y", "C")

    if l.Head.Next.Next.Next.Key != "Y" {
        t.Fatalf("AddBefore failed in middle")
    }
}

func TestSinglyListDeleteBefore(t *testing.T) {
    l := singlylist.NewForwardList()

    if l.DeleteBefore("Z") != "" {
        t.Fatalf("Expected empty when element not found")
    }

    l.AddTail("A")
    if l.DeleteBefore("A") != "" {
        t.Fatalf("Expected empty when deleting before head")
    }

    l.AddTail("B")
    if l.DeleteBefore("B") != "A" {
        t.Fatalf("Expected DeleteHead branch")
    }

    l.AddTail("A")
    l.AddTail("B")
    l.AddTail("C")
    if l.DeleteBefore("C") != "B" {
        t.Fatalf("Expected deletion of B before C")
    }
}

func TestSinglyListDeleteAfterValue(t *testing.T) {
    l := singlylist.NewForwardList()

    if l.DeleteAfterValue("Z") != "" {
        t.Fatalf("Expected empty when element not found")
    }

    l.AddTail("A")
    if l.DeleteAfterValue("A") != "" {
        t.Fatalf("Expected empty when no element after")
    }

    l.AddTail("B")
    l.AddTail("C")
    if l.DeleteAfterValue("A") != "B" {
        t.Fatalf("Expected deletion of B after A")
    }
}

func TestSinglyListDeleteTail(t *testing.T) {
    l := singlylist.NewForwardList()

    if l.DeleteTail() != "" {
        t.Fatalf("Expected empty on empty list")
    }

    l.AddTail("A")
    if l.DeleteTail() != "A" {
        t.Fatalf("DeleteTail failed on single element")
    }

    l.AddTail("A")
    l.AddTail("B")
    l.AddTail("C")
    if l.DeleteTail() != "C" {
        t.Fatalf("DeleteTail failed on multi-element list")
    }
}

func TestSinglyListDeleteByValue(t *testing.T) {
    l := singlylist.NewForwardList()

    if l.DeleteByValue("Z") != "" {
        t.Fatalf("Expected empty when element not found")
    }

    l.AddTail("A")
    if l.DeleteByValue("A") != "A" {
        t.Fatalf("Expected DeleteHead branch")
    }

    l.AddTail("A")
    l.AddTail("B")
    l.AddTail("C")
    if l.DeleteByValue("B") != "B" {
        t.Fatalf("Expected deletion of B")
    }
}

func TestSinglyListFindByValue(t *testing.T) {
    l := singlylist.NewForwardList()
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

func TestSinglyListContains(t *testing.T) {
    l := singlylist.NewForwardList()
    l.AddTail("A")

    if !l.Contains("A") {
        t.Fatalf("Contains failed")
    }
    if l.Contains("Z") {
        t.Fatalf("Contains should be false")
    }
}

func TestSinglyListDisplay(t *testing.T) {
    l := singlylist.NewForwardList()
    l.AddTail("A")
    l.AddTail("B")
    l.AddTail("C")
    l.Display()
}
