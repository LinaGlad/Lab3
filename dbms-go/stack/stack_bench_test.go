package stack_test

import (
    "dbms-go/stack"
    "testing"
)

func BenchmarkStackPush(b *testing.B) {
    for i := 0; i < b.N; i++ {
        s := stack.NewStack(1000)
        for j := 0; j < 1000; j++ {
            s.Push("x")
        }
    }
}

func BenchmarkStackPop(b *testing.B) {
    s := stack.NewStack(1000)
    
    b.ResetTimer()
    for i := 0; i < b.N; i++ {
        if s.Top == 0 {
            for j := 0; j < 1000; j++ {
                s.Push("x")
            }
        }
        s.Pop()
    }
}
