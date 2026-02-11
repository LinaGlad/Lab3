package tree_test

import (
    "dbms-go/tree"
    "testing"
)

func BenchmarkTreeInsert(b *testing.B) {
    for i := 0; i < b.N; i++ {
        t1 := tree.NewTree()
        for j := 0; j < 1000; j++ {
            t1.Insert(j)
        }
    }
}

func BenchmarkTreeSearch(b *testing.B) {
    t1 := tree.NewTree()
    for j := 0; j < 10000; j++ {
        t1.Insert(j)
    }

    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        t1.Search(5000)
    }
}
