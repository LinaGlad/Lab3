package singlylist_test

import (
    "dbms-go/singlylist"
    "testing"
)

func BenchmarkSinglyListAddTail(b *testing.B) {
    for i := 0; i < b.N; i++ {
        l := singlylist.NewForwardList()
        for j := 0; j < 1000; j++ {
            l.AddTail("x")
        }
    }
}

func BenchmarkSinglyListFind(b *testing.B) {
    l := singlylist.NewForwardList()
    for j := 0; j < 10000; j++ {
        l.AddTail("x")
    }

    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        l.Contains("x")
    }
}

func BenchmarkSinglyListDelete(b *testing.B) {
    for i := 0; i < b.N; i++ {
        l := singlylist.NewForwardList()
        for j := 0; j < 1000; j++ {
            l.AddTail("x")
        }
        for j := 0; j < 1000; j++ {
            l.DeleteHead()
        }
    }
}
