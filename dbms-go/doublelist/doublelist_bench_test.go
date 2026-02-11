package doublelist_test

import (
    "dbms-go/doublelist"
    "testing"
)

func BenchmarkDoubleListAddTail(b *testing.B) {
    for i := 0; i < b.N; i++ {
        l := doublelist.NewDoubleList()
        for j := 0; j < 1000; j++ {
            l.AddTail("x")
        }
    }
}

func BenchmarkDoubleListFind(b *testing.B) {
    l := doublelist.NewDoubleList()
    for j := 0; j < 10000; j++ {
        l.AddTail("x")
    }

    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        l.Contains("x")
    }
}

func BenchmarkDoubleListDelete(b *testing.B) {
    for i := 0; i < b.N; i++ {
        l := doublelist.NewDoubleList()
        for j := 0; j < 1000; j++ {
            l.AddTail("x")
        }
        for j := 0; j < 1000; j++ {
            l.DeleteTail()
        }
    }
}
