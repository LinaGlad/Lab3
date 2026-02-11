package hashtable_test

import (
    "dbms-go/hashtable"
    "testing"
)

func BenchmarkHashTableInsert(b *testing.B) {
    for i := 0; i < b.N; i++ {
        h := hashtable.NewHashTable(1000)
        for j := 0; j < 1000; j++ {
            h.Insert("x", j)
        }
    }
}

func BenchmarkHashTableSearch(b *testing.B) {
    h := hashtable.NewHashTable(1000)
    for j := 0; j < 10000; j++ {
        h.Insert("x", j)
    }

    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        h.Contains("x")
    }
}

func BenchmarkHashTableRemove(b *testing.B) {
    h := hashtable.NewHashTable(1000)
    for j := 0; j < 10000; j++ {
        h.Insert("x", j)
    }

    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        h.Remove("x")
    }
}
