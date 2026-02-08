package array_test

import (
    "dbms-go/array"
    "testing"
)

func BenchmarkArrayAddToEnd(b *testing.B) {
    for i := 0; i < b.N; i++ {
        a := array.NewArray(1000)
        for j := 0; j < 1000; j++ {
            a.AddToEnd("x")
        }
    }
}

func BenchmarkArrayAddByIndex(b *testing.B) {
    for i := 0; i < b.N; i++ {
        a := array.NewArray(1000)
        for j := 0; j < 1000; j++ {
            a.AddByIndex(0, "x")
        }
    }
}

func BenchmarkArrayDelete(b *testing.B) {
    for i := 0; i < b.N; i++ {
        a := array.NewArray(1000)
        for j := 0; j < 1000; j++ {
            a.AddToEnd("x")
        }
        for j := 0; j < 1000; j++ {
            a.DeleteByIndex(0)
        }
    }
}
